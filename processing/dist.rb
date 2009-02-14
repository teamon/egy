require "serialport"


begin
  sp = SerialPort.new "/dev/cu.usbserial", 9600
  # sp.clear
  # sp.putc "!"
  while c = sp.gets
    print c
  end
rescue Interrupt => e
  # sp.putc "!"
  sp.close
end
