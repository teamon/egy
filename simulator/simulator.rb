require 'ruby-processing'
require 'socket'

K = 0.9 # skalowanie (bo mi sie na macy nie miesci calosc :P)
D = 100

include Math

class Button
  attr_accessor :x, :y, :width, :height, :pressed, :label
  def initialize(x, y, width, height, label)
    @x, @y, @width, @height, @label = x, y, width, height, label
  end
  
  def update(mouse_x, mouse_y)
    @pressed = (mouse_x >= @x && mouse_x <= @x+@width && mouse_y >= @y && mouse_y <= @y+@height)
  end
end

class Robot
  attr_accessor :x, :y, :m1, :m2, :angle, :history, :coords, :grounds
  
  def initialize
    @x, @y = 110, 0
    @m1, @m2 = 0, 0
    @angle = PI/2
    @history = []
    @grounds = []
  end    
  
  def move
    t = 0.1
    diff = (@m2 - @m1).to_f
    
    if diff == 0
      s = @m1*t
      @x += -s * sin(@angle)
      @y += s * cos(@angle) 
    else
      beta = diff * t / D
      r = ((@m1 / diff)) * D
      r += D/2
      
      @x += -r * (cos(@angle) - cos(@angle + beta))
      @y += r * (sin(@angle + beta) - sin(@angle))
            
      @angle += beta
    end
    
    refresh_coords
    on_line
  end
  
  def on_line
    @grounds = @coords.map {|e| touch_line?(e.first, e.last) ? 1 : 0 }
  end
  
  def touch_line?(x, y)
    x**2 + y**2 >= 360**2
  end
  
  def refresh_coords
    @history << [@x, @y]
    @history.shift if @history.size > 3000

    a = D * cos(@angle) / 2
    b = D * sin(@angle) / 2

    @coords = [
      [@x-a-b,  @y+a-b],
      [@x+a-b,  @y+a+b],
      [@x-a+b,  @y-a-b],
      [@x+a+b,  @y-a+b]
    ]
  end
end

class Simulator < Processing::App
  load_ruby_library "control_panel" 
  
  def mouse_pressed
    (@switch + [@reset_button]).each {|s| s.update(mouse_x, mouse_y)}
    
    if @reset_button.pressed
      # reset
      setup
      
      @reset_button.pressed = false
    end
  end
  
  def setup
    textAlign(LEFT) 
    smooth
    @server = Thread.new { setup_server }
    color_mode RGB, 1.0
    frame_rate 30
    no_stroke
    @font = load_font "QuicksandBook.vlw"
    textFont @font, K*20
    
    draw_ring    
    
    # menusy
    fill 0.4
    rect K*800, 0, K*200, K*800
    
    # ledy
    fill 0.9
    text "LED", K*820, K*30
    text "SWITCH", K*820, K*100
    
    @led = []
    @switch = [
      Button.new(K*820, K*110, K*70, K*40, "SW1"),
      Button.new(K*900, K*110, K*70, K*40, "SW2")
    ]
    @reset_button = Button.new(K*820, K*160, K*150, K*40, "RESET")
    
    @robot = Robot.new
    @robot.refresh_coords

    text_size K*15
    textAlign(CENTER)
  end
  
  def draw_ring
    fill 0.3
    rect 0, 0, K*800, K*800
    fill 0.9
    ellipse K*400, K*400, K*770, K*770
    fill 0
    ellipse K*400, K*400, K*720, K*720
    fill 0.1
    rect K*450, K*350, K*10, K*100
    rect K*340, K*350, K*10, K*100
  end
  
  def draw
    # guziki
    stroke 0.5
    (@switch + [@reset_button]).each {|s| 
      fill(s.pressed ? 0xFF57bd23 : 0.3)
      rect s.x, s.y, s.width, s.height
      fill 0.7
      text s.label, s.x+s.width/2, s.y+s.height/2+K*6
    }
    no_stroke
    
    # ledy
    8.times {|i|
      fill @led[i] ? 0xFF57bd23 : 0.3
      text (i+1).to_s, K*(820 + i*20), K*60
    }
    
    draw_ring
    
    # linia sledzaca
    fill 0.15
    @robot.history.each {|x,y| ellipse K*(400+x), K*(400-y), K*3, K*3 }

    # groundy
    fill 0xFF0FF900
    @robot.coords.each_with_index do |e, i|
      # fill 1
      # text i.to_s, 400+e.first, 400-e.last
      if @robot.grounds[i]==1
        ellipse(K*(400+e.first), K*(400-e.last), K*20, K*20)
      end
    end
    
    # robot
    fill 0xFFFF0000
    c = @robot.coords.map{|x| [K*(x.first+400), K*(400-x.last)] }
    quad *[c[0], c[1], c[3], c[2]].flatten
    
    # robot po prawej    
    fill 0xFFFF0000
    rect K*850, K*300, K*D, K*D
    fill 0
    rect K*850, K*330, K*40, K*40
    rect K*910, K*330, K*40, K*40
    fill 0.7
    text @robot.m1, K*870, K*355
    text @robot.m2, K*930, K*355
    
    # groundy po prawej
    fill 0xFF0FF900
    @robot.coords.each_with_index do |e, i|
      if @robot.grounds[i]==1
        rect K*(850+(i%2)*80), K*(300+i/2*80), K*20, K*20
      end
    end
  end

  def setup_server
    server_sock = TCPServer.new(30_000)
    puts "Server started"
    while true
      t = Thread.start(server_sock.accept) do |s|
        while input = s.recv(100)
          input = input.chomp
          output = parse_message(input)
          puts "#{input} => #{output}"
          s.write(output)
        end
        s.close
      end
      puts t.inspect
    end
  end
  
  def parse_message(msg)
    # M1:M2:LED
    m1, m2, led = msg.split(":").map{|e| e.to_i}
    
    # ledy
    leds = (led >> 8).to_s(2).reverse.split(//)
    8.times {|i| @led[i] = (leds[i] == "1") }
    
    # motorky
    @robot.m1 = m1
    @robot.m2 = m2
    @robot.move   
     
    # output
    out = []
    
    # switch
    @switch.each do |s|
      if s.pressed
        out << 1
        s.pressed = false
      else
        out << 0
      end
    end
    
    out += @robot.grounds
    out.join(":")
  end
end

Simulator.new :title => 'Egy simulator', :width => K*1000, :height => K*800
