require "rubygems"
require "ruby-processing"

class Graph < Processing::App
  
  def setup
    background 100
    color_mode RGB
    frame_rate 50
    fill(0,0,0)
    
    @data = File.read('data.txt').split("\n").map {|e| e.to_i}
    @i = 0
  end

  def draw
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