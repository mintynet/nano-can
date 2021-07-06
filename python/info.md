#### gauge-sweep.py is for python3
#### gauge-sweep2.py is for python2

### Instructions
Download and install Thonny IDE
<br>Start Thonny IDE
<br>Goto tools, manage plugins, search for pyserial and install if not already installed
<br>Load the version of file for the version of python being used.
<br>You may need to change the COM port from /dev/ttyUSB0 to ?
<br>You may need to change the COM speed from 500000 to ?

Program to list serial ports on PC
<br>Paste the following into the IDE and it should list the current COM ports

```python
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))
```
