# nano-can
## If you would like a nano-can PCB feel free to contact me on Twitter @mintynet, I don't allow msgs if I do not follow you so just tweet asking me to follow back, I will send if you cover the cost of postage.
If you are looking for the BSides Scotland 2019 Badge please click the following link
<br>https://github.com/mintynet/BSidesScotland2019
<br>
<br>The sketches below will work but the specific build instructions are in the other repository
<br>
<br>This repository has the arduino code for use with nano can PCB.
<br>These were created as a cheap device for people to get into car hacking.
<br><br><b>I take no responsibility for any issues caused if using either the hardware or the code</b>
<br><br>Requires the use of the following Arduino library
<br><br>https://github.com/coryjfowler/MCP_CAN_lib
<br><br>The <b>can-receive-all</b> sketch is the receive example from the above library which will show all messages on the CAN bus. CAN speed can be changed from 500kbps.
<br>CAN messages are shown on the Serial Monitor
<br>This can be used to find interesting messages
<br><br>The <b>nano-can</b> sketch is configured for the OBD2 port speed (500kbps) and will listen to the can bus starting with CAN ID 0x128. Both can be changed in the code.
<br>Whilst on the Serial Monitor it will show the changes between the messages
<br><br>u and d will change the CAN ID up or down by 1
<br>U and D will change the CAN ID up or down by 16
<br>h shows the above information
<br><br>The <b>nano-slcan</b> sketch is slcan compatible software but the serial chip on the arduino boards I use will only run at 500000bps

<br><b>EASY EDA PCB Design files</b>
https://easyeda.com/minty2017/nano-can-2019

<br><b>Schematic</b>
![PCB Schematic](Schematic_nano-can-pcb.png)
Note:
<br><b>Arduino Nano</b> goes on the top with the URL on, <b>the square at one end denote the position of the USB connector</b>.
![Arduino Nano](arduino-nano.jpg)
<br><b>MCP2515 Module</b> goes on the bottom but <b>DO NOT</b> solder the Terminator Jumper or CAN pin headers to the PCB
<br>You may require a jumper on the Terminator resistor
<br>To solder the CAN module to the board, add extra solder to the back of the pins, then heat the pins and push through so that the pins are on the rear, then remove the plastic pin spacer left on the top and add extra solder to the pins. 
![MCP2515](mcp2515.JPG)
<br>L goes to OBD2 pin 14
<br>H goes to OBD2 pin 6
#### The PCB may look slightly different to the ones shown in this file, white square indicates the USB end of Nano.
<br><b>Completed v1.0 Top</b><br>
![Completed TOP](top-complete.jpg)
<br><b>Completed v1.0 Bottom</b><br>
![Completed BOTTOM](bottom-complete.jpg)
<br><b>OBD2 connector</b><br>
![OBD2 connector](obd2-connector.jpg)
#### The PCB may look slightly different to the ones shown in this file, white square indicates the USB end of Nano.
<br><b>v1.0 PCB Top</b><br>
![PCB TOP](top-gerber.JPG)
<br><b>v1.0 PCB Bottom</b><br>
![PCB BOTTOM](bottom-gerber.JPG)
