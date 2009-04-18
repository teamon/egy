require 'ruby-processing'
require 'socket'

class Simulator < Processing::App
  def setup
    Thread.new { setup_server }
    color_mode RGB, 1.0
    frame_rate 30
    
    no_stroke
    
    # ring
    fill 0.3
    rect 0, 0, 800, 800
    fill 1
    ellipse 400, 400, 770, 770
    fill 0
    ellipse 400, 400, 720, 720
    fill 0.1
    rect 450, 350, 10, 100
    rect 350, 350, 10, 100
    
    # menusy
    fill 0.4
    rect 800, 0, 200, 800
  end
  
  def draw
    
  end
  
  
  
  
  
  def setup_server
    server_sock = TCPServer.new(30_000)
    puts "Server started"
    loop do
      Thread.start(server_sock.accept) do |s|
        puts "#{s} is accepted"
        while input = s.recv(100)
          puts "input received: #{input}"
          output = [0,0,0,0].join(":")

          puts "sending output=#{output}"

          s.write(output)
        end
        s.close
      end
    end
  end
end


Simulator.new :title => 'Egy simulator', :width => 1000, :height => 800

