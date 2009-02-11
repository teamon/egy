require "rubygems"
require "ruby-processing"
require "serialport"


class Graph < Processing::App
  
  def setup
    background 100
    color_mode RGB
    frame_rate 50
    no_loop
    fill(0,0,0)
    
    @data = [[],[]]
    @i = 0
  end
  
  def draw
    begin
      sp = SerialPort.new "/dev/tty.usbserial", 9600
      sp.putc "!"
      while c = sp.gets
        c = c.split(':').map {|e| e.to_i}
        case c.first
        when 4 # dist
          @data[c[1]] << c[2] # powinno dzialac - nie testowalem bo sie kabel rozjebal
        when 2 #ground
          
        end
        paint
      end
    rescue Interrupt => e
      sp.putc "!"
      sp.close
    end
  end

  def paint
    no_stroke
    fill 74
    rect 10, 10, 780, 580
    
    (0..@i).each do |i|
      if i%2 == 0
        stroke 226, 37, 0
      else
        stroke 161, 55, 33
      end
      x = 789-@i+i
      line x, 589, x, 590 - @data[i] if x > 10
    end
    
    @i += 1
  end

end

Graph.new :title => "Graph", :width => 800, :height => 600