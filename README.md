# nano-can
This repository has the arduino code for use with nano can PCB.
<br>These were created as a cheap device for people to get into car hacking.
<br><br><b>I take no responsibility for any issues caused if using either the hardware or the code</b>
<br><br>Requires the use of the following Arduino library
<br><br>https://github.com/coryjfowler/MCP_CAN_lib
<br><br>The sketch is configured for the OBD2 port speed (500kbps) and will listen to the can bus starting with CAN ID 0x128. Both can be changed in the code.
<br>Whilst on the serial monitor it will show the changes between the messages
<br><br>u and d will change the CAN ID up or down by 1
<br>U and D will change the CAN ID up or down by 16
<br>h shows the above information

<br><b>Schematic</b>
![PCB Schematic](Schematic_nano-can-pcb.png)
Note:
<br>Arduino Nano goes on the top with the URL on.
![Arduino Nano](arduino-nano.jpg)
<br>MCP2515 Module goes on the bottom but DO NOT solder the Terminator Jumper or CAN pin headers to the PCB
<br>You may require a jumper on the Terminator resistor
![MCP2515](mcp2515.JPG)
<br>L goes to OBD2 pin 14
<br>H goes to OBD2 pin 6
<br><b>Completed Top</b>
![Completed TOP](top-complete.jpg)
<br><b>Completed Bottom</b>
![Completed BOTTOM](bottom-complete.jpg)
<br>,b>OBD2 connector</b>
![OBD2 connector](obd2-connector.jpg)
<br><b>PCB Top</b><br>
![PCB TOP](top-gerber.JPG)
<br><b>PCB Bottom</b><br>
![PCB BOTTOM](bottom-gerber.JPG)
