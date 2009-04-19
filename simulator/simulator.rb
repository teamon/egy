require 'ruby-processing'
require 'socket'

D = 100
include Math

class Robot
  attr_accessor :x, :y, :m1, :m2, :angle, :history, :coords
  
  def initialize
    # @x, @y = 60, -50
    @x, @y = 110, 0
    @m1, @m2 = 0, 0
    @angle = PI/2
    @history = []
  end    
  
  def move
    t = 0.1
    
    diff = @m2 - @m1
    
    if diff == 0
      s = @m1*t
      @x += -s * sin(@angle)
      @y += s * cos(@angle) 
    else
      beta = diff * t / D
      r = ((@m1 / diff)) * D
      
      @x += -r * (cos(@angle) - cos(@angle + beta))
      @y += r * (sin(@angle + beta) - sin(@angle))
            
      @angle += beta
    end
    
    refresh_coords
  end
  
  def on_line
    @coords.map {|e| touch_line?(e.first, e.last) ? 1 : 0 }
  end
  
  def touch_line?(x, y)
    x**2 + y**2 >= 360**2
  end
  
  def refresh_coords
    a = D * cos(@angle)
    b = D * sin(@angle)
  
    @history << [@x, @y]

    @coords = [
      [@x-(a+b)/2,    @y-(b-a)/2],
      [@x+(a-b)/2,    @y+(a+b)/2],
      [@x+(b-a)/2,    @y-(a+b)/2],
      [@x+(a+b)/2,    @y+(b-a)/2]
    ]
  end
end

class Simulator < Processing::App
  load_ruby_library "control_panel" 
  
  def setup
    @server = Thread.new { 
      setup_server 
    }
    color_mode RGB, 1.0
    frame_rate 30
    
    no_stroke
    
    @font = load_font "QuicksandBook.vlw"
    textFont @font, 20
    
    draw_ring    
    
    # menusy
    fill 0.4
    rect 800, 0, 200, 800
    
    control_panel do |c|
      c.button :switch1
      c.button :switch2
    end
    
    # ledy
    fill 0.9
    text "LED", 820, 30
    
    
    @led = []
    @switch1, @switch2 = 0, 0
    
    @robot = Robot.new
    @robot.refresh_coords
          
    text_size 15
  end
  
  def draw_ring
    fill 0.3
    rect 0, 0, 800, 800
    fill 0.9
    ellipse 400, 400, 770, 770
    fill 0
    ellipse 400, 400, 720, 720
    fill 0.1
    rect 450, 350, 10, 100
    rect 340, 350, 10, 100
  end
  
  def draw
    
    # ledy
    8.times {|i|
      fill @led[i] ? 0xFF57bd23 : 0.3
      text (i+1).to_s, 820 + i*20, 60
    }
    
    draw_ring
    
    fill 0.15
    @robot.history.each {|x,y| ellipse 400+x, 400-y, 3, 3 }
    
    fill 0xFFFF0000
    c = @robot.coords.map{|x| 
      [x.first+400, 400-x.last]
    }
    quad *[c[0], c[1], c[3], c[2]].flatten
    
    @robot.coords.each_with_index do |e, i|
      # fill 1
      # text i.to_s, 400+e.first, 400-e.last
      fill(@robot.touch_line?(e.first, e.last) ? 0xFF0FF900 : 0xFF000000)
      ellipse(400+e.first, 400-e.last, 10, 10)
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
    out << @switch1
    out << @switch2
    out += @robot.on_line
    # @robot.on_line
    
    @switch1 = 0 if @switch1 == 1
    @switch2 = 0 if @switch2 == 1
    
    out.join(":")
  end
  
  def switch1
    @switch1 = 1
  end
  
  def switch2
    @switch2 = 1
  end
end


Simulator.new :title => 'Egy simulator', :width => 1000, :height => 800

