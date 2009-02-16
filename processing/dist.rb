require "serialport"


begin
  sp = SerialPort.new "/dev/cu.usbserial", 9600
  # sp.clear
  sp.putc "!" unless ARGV[0] == "clear"
  while c = sp.gets
    print ARGV[0] == "clear" ? '.' : c
  end
rescue Interrupt => e
  sp.putc "*"
  sp.close
end
