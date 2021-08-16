#### gauge-sweep.py is for python3
#### gauge-sweep2.py is for python2

### Instructions
Download and install Thonny IDE
<br>Start Thonny IDE
<br>Goto tools, manage plugins, search for pyserial and install if not already installed
<br>Load the version of file for the version of python being used.
<br>You may need to change the COM port from /dev/ttyUSB0 to ?
<br>You may need to change the COM speed from 500000 to ?

##########################################################################################
Program to list serial ports on PC
<br>Paste the following into the IDE and it should list the current COM ports

```python
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))
```
##########################################################################################

Slcan for linux also works use nano-slcan sketch

```bash
#can viewer -c port@speed -b CAN baud rate -i interface type
python3 -m can.viewer -b 125000 -i slcan -c /dev/ttyUSB0@500000
#can logger -c port@speed -b CAN baud rate -i interface type
python3 -m can.logger -b 125000 -i slcan -c /dev/ttyUSB0@500000
```

Sample send code
```python
import can

bus = can.interface.Bus(bustype='slcan', channel='/dev/ttyUSB0@500000', bitrate=125000)
msg = can.Message(arbitration_id=0x123,data=[1,2,3,4,5,6,7,8], is_extended_id=False)
try:
	bus.send(msg)
	print("Message send on {}".format(bus.channel_info))
except:
	print("Message NOT sent")
```
