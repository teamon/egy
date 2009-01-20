require "rubygems"
require 'nxt_comm'

@nxt = NXTComm.new('/dev/tty.NXT-DevB-1')

us = Commands::UltrasonicSensor.new(@nxt)
us.mode = :centimeters
puts "Distance: #{us.distance}cm"
us.mode = :inches
puts "Distance: #{us.distance}in"

us.comparison = "<"
us.trigger_point = 5

while us.logic == false
  sleep(0.5)
  puts "Move #{us.comparison} #{us.trigger_point} #{us.mode} from the sensor..."
  puts "Distance: #{us.distance}in"
end
