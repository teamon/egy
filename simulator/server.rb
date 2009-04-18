require 'socket'
@ground = []
def process_message(msg)
  # M1:M2:LED
  m1, m2, led = msg.chomp.split(":")
  leds = (led.to_i >> 8).to_s(2).reverse.split(//)
  puts leds.inspect
  puts @ground.inspect
  8.times {|i|
    @ground[i] = (leds[i] == "1")
  }
  puts @ground.inspect
  puts "foooo"
end



server_sock = TCPServer.new(30_000)
puts "Server started"
loop do
  puts 'loop'
  Thread.start(server_sock.accept) do |s|
    puts "#{s} is accepted"
    while input = s.recv(100)
      puts "input received: #{input}"
      process_message input
      output = [0,0,0,0].join(":")

      puts "sending output=#{output}"

      s.write(output)
    end
    s.close
  end
end


