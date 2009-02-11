require "serialport"

begin
  sp = SerialPort.new "/dev/tty.usbserial", 9600
  sp.putc "!"
  while c = sp.gets
    puts c
  end
rescue Interrupt => e
  sp.putc "!"
  sp.close
end
