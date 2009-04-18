require 'socket'

server_sock = TCPServer.new(30000)
puts "Server started"
loop do
  Thread.start(server_sock.accept) do |s|
    puts "#{s} is accepted"
    while input = s.recv(100)
      puts "input received: #{input}"
      output = "you typed: #{input}"

      s.write(output)
    end
    s.close
  end
end
