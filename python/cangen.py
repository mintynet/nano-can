import serial
import time
import argparse
from random import seed
from random import randint

my_parser=argparse.ArgumentParser()
my_parser.version = '1.0'
#my_parser.add_argument('-bus',action='store',type=str,help='canbus',default='can0')
my_parser.add_argument('-comm',action='store',type=str,help='TTY port',default='/dev/ttyUSB0')
my_parser.add_argument('-commbaud',action='store',type=int,help='Comm Baudrate',default=500000)
my_parser.add_argument('-canbaud',action='store',type=int,help='CAN baud rate kbps',default=125)
my_parser.add_argument('-I',action='store',type=str,help='CAN ID i=inc,r=rnd,fz=fuzz',default='i')
my_parser.add_argument('-L',action='store',type=int,help='CAN length 0 to 8',choices=range(0,9),default=0)
my_parser.add_argument('-D',action='store',type=str,help='CAN Data i=inc,r=rnd,bw=bitwalk',default='')
my_parser.add_argument('-n',action='store',type=int,help='No of msgs',default=1)
my_parser.add_argument('-g',action='store',type=float,help='Msg interval ms',default=200)
my_parser.add_argument('-drv',action='store',type=str,help='ch=ch34x,cp=cp210x',default='cp')
my_parser.add_argument('-v',action='store_true',help='Show cansend command')
my_parser.add_argument('-vv',action='store_true',help='Show slcan command')
my_parser.add_argument('-slow',action='store',type=int,help='CR between messages 0=False,1=True',default=0)

args=my_parser.parse_args()
commport = args.comm
commbaud = args.commbaud
canbaud = args.canbaud
reqarbID = args.I
reqdata = args.D
reqlen = args.L
num = args.n
interval = args.g
driver = args.drv
vbose = args.v
xbose = args.vv
slowmode = args.slow

print ('Port ' + commport + ' speed ' + str(commbaud) + 'bps CAN baud rate ' + str(canbaud) + '000bps')
if canbaud == 1000:
    canbaudcmd = 'S8'
elif canbaud == 500:
    canbaudcmd = 'S6'
elif canbaud == 250:
    canbaudcmd = 'S5'
elif canbaud == 125:
    canbaudcmd = 'S4'
elif canbaud == 100:
    canbaudcmd = 'S3'
else:
    print("Unsupported CAN baud")
    exit()
ser = serial.Serial(commport, commbaud, timeout=0)
out = ser.read(100)
#print (out)
if driver == 'ch':
    var = input("Enter O to start: ")
else:
    var = 'O'
ser.write(canbaudcmd.encode())
ser.write('\r'.encode())
time.sleep(0.1)
ser.write(var.encode())
ser.write('\r'.encode())
time.sleep(0.1)
if driver == 'ch':
    time.sleep(0.9)
seed(1)

try:
    for i in range(0,num,1):
        if reqarbID == 'i':
            arbID = str(format(i%2048,'06x'))[-3:]
        elif reqarbID == 'fz':
            if i == 0:
                arbID = '000'
            else:
                if (reqlen == 0):
                    arbID = str(format(int(i),'06x'))[-3:]
                else:
                    if (int(i/(8*reqlen))) > 2047:
                        arbID = str(format(int(i/(8*reqlen))%2048,'06x'))[-3:]
                    else:
                        arbID = str(format(int(i/(8*reqlen)),'06x'))[-3:]
                if (arbID == '036' and reqlen == 8) or (arbID == '0b6' and reqlen == 8) or (arbID == '0f6' and reqlen == 8) or (arbID == '128' and reqlen == 8) or (arbID == '161' and reqlen == 7) or (arbID == '168'  and reqlen == 8) or (arbID == '276' and reqlen == 7):
                    pause = input("Press enter key")
        elif reqarbID == 'r':
            arbID = str(format(randint(0,2047),'06x'))[-3:]
        else:
            if len(reqarbID) == 1:
                arbID = '00' + reqarbID
            elif len(reqarbID) == 2:
                arbID = '0' + reqarbID
            else:
                arbID = reqarbID
        if reqdata == 'i':
            tempdata = str(format(i,'016x'))
            data = tempdata[-reqlen*2:]
        elif reqdata == 'r':
            tempdata = str(format(randint(0,pow(2,64)-1),'016x'))
            data = tempdata[-reqlen*2:]
        elif reqdata == ('bw' or 'fz'):
            if reqlen == 0:
                tempdata = ''
                data = ''
                #exit()
            else:
                tempdata = str(format(pow(2,i%(8*reqlen)),'016x'))
                bdata = tempdata[-reqlen*2:]
                dataarr = []
                #following swaps bytes around
                for i in range(0,16,2):
                    dataarr.insert(0,bdata[i:i+2])
                data = dataarr[0]+dataarr[1]+dataarr[2]+dataarr[3]+dataarr[4]+dataarr[5]+dataarr[6]+dataarr[7]
        else:
            data = reqdata
        if vbose == True:
            print(' ' + str(arbID) + '#' + str(data))
        datalen = int(len(data)/2)
        if datalen == reqlen:
            if reqarbID == 'fz':
                rpt = int(5)
            else:
                rpt = int(1)
            #print(tempdata[-2*reqlen:])
            #print(('0'*(reqlen-1)*2+'01'))
            if (reqdata == 'bw'):
                if (tempdata[-2*reqlen:] == ('0'*(reqlen-1)*2+'01')):
                    for i in range (0,rpt,1):
                        output='t' + str(arbID) + str(reqlen) + '00' * reqlen
                        if xbose == True:
                            print(output)
                        ser.write(output.encode())
                        ser.write('\r'.encode())
                    if slowmode == 1:
                        pause = input("Press enter key")
            for i in range (0,rpt,1):
                output='t' + str(arbID) + str(reqlen) + str(data)
                if xbose == True:
                    print(output)
                ser.write(output.encode())
                ser.write('\r'.encode())
            if slowmode == 1:
                pause = input("Press enter key")
            #print(('80'+'0'*(reqlen-1)*2))
            #print(tempdata[-2*reqlen:])
            if (reqdata == 'bw'):
                if (tempdata[-2*reqlen:] == ('80'+'0'*(reqlen-1)*2)):
                    for i in range (0,rpt,1):
                        output='t' + str(arbID) + str(reqlen) + 'FF' * reqlen
                        if xbose == True:
                            print(output)
                        ser.write(output.encode())
                        ser.write('\r'.encode())
                    if slowmode == 1:
                        pause = input("Press enter key")
                    #pause = input("Press enter key")
        else:
            print("Length of DATA field NOT correct")
            ser.write('C'.encode())
            ser.write('\r'.encode())
            break
        sleeptime=interval/1000
        time.sleep(sleeptime)
    ser.write('C'.encode())
    ser.write('\r'.encode())
    ser.close()

except KeyboardInterrupt:
    # CTRL-C detected, cleaning and quitting script
    ser.write('C'.encode())
    ser.write('\r'.encode())
    ser.close()
