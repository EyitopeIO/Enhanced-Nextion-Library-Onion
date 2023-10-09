# Bugs

- When launching the program with a baudrate of 115200, the program flows
  normally as though the serial port was successfully opened, but everything
  read from the serial port is zero. To reproduce, compile with a baudrate
  other than 9600 and observe
