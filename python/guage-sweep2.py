import serial
import time
ser = serial.Serial('/dev/ttyUSB0', 500000, timeout=0)
out = ser.read(100)
print (out)
var = raw_input("Enter O to start: ")
ser.write('S4')
ser.write('\r')
ser.write(var)
ser.write('\r')
time.sleep(0.1)
try:
    for i in range(9643990,9660000):
    #9653990 just before largest number
        rev = i
        speed = i
        fuel = i
        temp = i
        temp = temp >> 3
        #print(i)
        #print(format(i, '06x'))
        print('t0f6838' + str(format(temp, '06x'))[-2:] + format(i, '06x') + '000000')
        ser.write('t0f6838' + str(format(temp, '06x'))[-2:] + format(i, '06x') + '000000')
        ser.write('\r')
        rev = rev << 0
        speed = speed >> 2
        speed = speed & 0x7f
        fuel = fuel >> 2
        fuel = fuel & 0x7f
        print('t0b68' + str(format(rev, '06x'))[-2:] + '00' + str(format(speed, '06x'))[-2:] + '0000000000')
        ser.write('t0b68' + str(format(rev, '06x'))[-2:] + '00' + str(format(speed, '06x'))[-2:] + '0000000000')
        ser.write('\r')
        print('t127800b0000000000000')
        ser.write('t127800b0000000000000')
        ser.write('\r')
        print('t16170000FF' + str(format(fuel, '06x'))[-2:] + '0000FD')
        ser.write('t16170000FF' + str(format(fuel, '06x'))[-2:] + '0000FD')
        ser.write('\r')
        print('t16880000040100000000')
        ser.write('t16880000040100000000')
        ser.write('\r')
        time.sleep(0.01)
#        for i in range(16,255):
#            print('t0b68' + hex(i)[2:] + '00' + hex(i)[2:] + '0000000000')
#            ser.write('t0b68' + hex(i)[2:] + '00' + hex(i)[2:] + '0000000000')
#            ser.write('\r')
#            time.sleep(0.1)
#    except ser.SerialTimeoutException:
#        print('Data could not be read')
except KeyboardInterrupt:
    # CTRL-C detected, cleaning and quitting script
    ser.write('C')
    ser.write('\r')
    ser.close()
