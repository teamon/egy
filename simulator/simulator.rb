require 'ruby-processing'
require 'socket'

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
    
    # ring
    fill 0.3
    rect 0, 0, 800, 800
    fill 0.9
    ellipse 400, 400, 770, 770
    fill 0
    ellipse 400, 400, 720, 720
    fill 0.1
    rect 450, 350, 10, 100
    rect 350, 350, 10, 100
    
    
    # menusy
    fill 0.4
    rect 800, 0, 200, 800
    
    # ledy
    fill 0.9
    text "LED", 820, 30
    
    
    @ground = []
    @switch1, @switch2 = 0, 0
    
    
    control_panel do |c|
      c.button :switch1
      c.button :switch2
    end
          
    text_size 15
  end
  
  def draw
    # puts @server.inspect
    8.times {|i|
      fill @ground[i] ? 0xFF57bd23 : 0.3
      text (i+1).to_s, 820 + i*20, 60
    }
  end

  def setup_server
    server_sock = TCPServer.new(30_000)
    puts "Server started"
    while true
      t = Thread.start(server_sock.accept) do |s|
        puts "#{s} is accepted"
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
    m1, m2, led = msg.split(":")
    
    # ledy
    leds = (led.to_i >> 8).to_s(2).reverse.split(//)
    8.times {|i| @ground[i] = (leds[i] == "1") }
    
    
    
    # generate output
    
    out = []
    
    # switch
    out << @switch1
    out << @switch2
    
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

