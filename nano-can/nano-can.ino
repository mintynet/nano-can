//
// Nano CAN sample
//
#include <mcp_can.h>                            // version 24/03/17 from https://github.com/coryjfowler/MCP_CAN_lib
#include <SPI.h>                                // version 1.0.0

long unsigned int rxId;
long unsigned int reqRxId;
unsigned char len = 0;
unsigned char rxBuf[8];
unsigned char prevrxBuf[8];
unsigned char change[8];
unsigned int counter = 0;

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

//----------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
  // 500kb/s is default OBD2 port speed other bus speeds are possible, take care NOT to connect wrong speed
  // errors will happen
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                     // Configuring pin for /INT input

  reqRxId = 0x128;
  
  Serial.println("MCP2515 Library Receive Example...");
  for(byte i = 0; i<len; i++){
    rxBuf[i]=0;
    prevrxBuf[i]=0;
  }
  dispHelp();
} //setup()

//----------------------------------------------------------------

void pars_CANID(char *buf) 
{
  long unsigned int calcRxId = 0;
  switch (buf[0])
  {
    case 'u':     // increase CANID by 1
      for (byte i = 0; i<len; i++) {
        rxBuf[i] = 0;
        prevrxBuf[i] = 0;
      }
      reqRxId++;
      Serial.print("ID:0x");
      Serial.println(reqRxId,HEX);
      break;
    case 'd':     // decrease CANID by 1
      for (byte i = 0; i<len; i++) {
        rxBuf[i] = 0;
        prevrxBuf[i] = 0;
      }
      reqRxId--;
      Serial.print("ID:0x");
      Serial.println(reqRxId,HEX);
      break;
    case 'U':     // increase CANID by 16
      for (byte i = 0; i<len; i++) {
        rxBuf[i] = 0;
        prevrxBuf[i] = 0;
      }
      reqRxId=reqRxId + 16;
      Serial.print("ID:0x");
      Serial.println(reqRxId,HEX);
      break;
    case 'D':     // decrease CANID by 16
      for (byte i = 0; i<len; i++) {
        rxBuf[i] = 0;
        prevrxBuf[i] = 0;
      }
      reqRxId=reqRxId - 16;
      Serial.print("ID:0x");
      Serial.println(reqRxId,HEX);
      break;
    case 'h':     // display help
      dispHelp();
      break;
    case '0':     // hex number
      buf[0] = '0';
      buf[1] = '0';
      calcRxId = strtol(buf, NULL, HEX);
      //Serial.print("calc:0x");
      //Serial.println(calcRxId);
      if (calcRxId == 0) {
        Serial.println("Error");
      } else if (calcRxId < 0x1FFFFFFF) {
        for (byte i = 0; i<len; i++) {
         rxBuf[i] = 0;
         prevrxBuf[i] = 0;
        }
        reqRxId=calcRxId;
        Serial.print("ID:0x");
        Serial.println(reqRxId,HEX);
      } else {
        Serial.println("Error");
        Serial.print("ID:0x");
        Serial.println(reqRxId,HEX);
      }
      break;
    case 'n':     // dec number
      buf[0] = '0';
      calcRxId = strtol(buf, NULL, DEC);
      //Serial.print("calc:0x");
      //Serial.println(calcRxId);
      if (calcRxId == 0) {
        Serial.println("Error");
      } else if (calcRxId < 0x1FFFFFFF) {
        for (byte i = 0; i<len; i++) {
         rxBuf[i] = 0;
         prevrxBuf[i] = 0;
        }
        reqRxId=calcRxId;
        Serial.print("ID:0x");
        Serial.println(reqRxId,HEX);
      } else {
        Serial.println("Error");
        Serial.print("ID:0x");
        Serial.println(reqRxId,HEX);
      }
    default:
      break;
  }
} //pars_CANID()

//----------------------------------------------------------------

static void dispHelp() {
  Serial.println(F("\n\tInstructions\n"));
  Serial.println(F("\td                 : CANID -1"));
  Serial.println(F("\tD                 : CANID -16"));
  Serial.println(F("\tu                 : CANID +1"));
  Serial.println(F("\tU                 : CANID +16"));
  Serial.println(F("\t0x1FFFFFFF(MAX)   : 29bit CANID in HEX"));
  Serial.println(F("\tn536870911(MAX)   : 29bit CANID in DEC"));
  Serial.println(F("\th                 : display help\n"));
  Serial.print(F("\tCANID: 0x"));
  if (reqRxId<16) {
    Serial.print(F("00"));
  } else if (reqRxId<256) {
    Serial.print(F("0"));
  }
  Serial.println(reqRxId,HEX);
} //dispHelp()

//----------------------------------------------------------------

void change_CANID()
{
  int ser_length;
  static char idbuf[12];
  static int ididx = 0;
  if ((ser_length = Serial.available()) > 0) {
    for (int i = 0; i < ser_length; i++) {
      char val = Serial.read();
      idbuf[ididx++] = val;
      if (ididx == 12)
      {
        ididx = 0;
        Serial.println("Data too long");
      } else if (val == '\r') {
        idbuf[ididx] = '\0';
        pars_CANID(idbuf);
        ididx = 0;
      }      
    }
  }
} // change_CANID()

//----------------------------------------------------------------

void loop()
{
  change_CANID();
  if(!digitalRead(CAN0_INT))                        // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);            // Read data: len = data length, buf = data byte(s)

    if(rxId == reqRxId){
      counter++;
      if ((rxBuf[0]!=prevrxBuf[0]) | (rxBuf[1]!=prevrxBuf[1]) | (rxBuf[2]!=prevrxBuf[2]) | (rxBuf[3]!=prevrxBuf[3]) | (rxBuf[4]!=prevrxBuf[4]) | (rxBuf[5]!=prevrxBuf[5]) | (rxBuf[6]!=prevrxBuf[6]) | (rxBuf[7]!=prevrxBuf[7])) {
        Serial.print("ID 0x");
        if (rxId<16) {
          Serial.print("00");
        } else if (rxId<256) {
          Serial.print("0");
        }
        Serial.print(rxId,HEX);
        Serial.print(" Len:");
        Serial.println(len);
        Serial.print("              ");
        for(byte i = 0; i<len; i++){
          Serial.print(" ");
          if (prevrxBuf[i]<2) {
            Serial.print("0000000");
          } else if (prevrxBuf[i]<4) {
            Serial.print("000000");
          } else if (prevrxBuf[i]<8) {
            Serial.print("00000");
          } else if (prevrxBuf[i]<16) {
            Serial.print("0000");
          } else if (prevrxBuf[i]<32) {
            Serial.print("000");
          } else if (prevrxBuf[i]<64) {
            Serial.print("00");
          } else if (prevrxBuf[i]<128) {
            Serial.print("0");
          }
          Serial.print(prevrxBuf[i],BIN);
        }
        Serial.println(" Previous");
        Serial.print("              ");
        for(byte i = 0; i<len; i++){
          Serial.print(" ");
          if (rxBuf[i]<2) {
            Serial.print("0000000");
          } else if (rxBuf[i]<4) {
            Serial.print("000000");
          } else if (rxBuf[i]<8) {
            Serial.print("00000");
          } else if (rxBuf[i]<16) {
            Serial.print("0000");
          } else if (rxBuf[i]<32) {
            Serial.print("000");
          } else if (rxBuf[i]<64) {
            Serial.print("00");
          } else if (rxBuf[i]<128) {
            Serial.print("0");
          }
          Serial.print(rxBuf[i],BIN);
          change[i]=prevrxBuf[i] ^ rxBuf[i];
        }
        Serial.print(" Current - count:");
        Serial.println(counter);
        counter=0;
        Serial.print("              ");
        for(byte i = 0; i<len; i++){
          Serial.print(" ");
          if (change[i]<2) {
            Serial.print("0000000");
          } else if (change[i]<4) {
            Serial.print("000000");
          } else if (change[i]<8) {
            Serial.print("00000");
          } else if (change[i]<16) {
            Serial.print("0000");
          } else if (change[i]<32) {
            Serial.print("000");
          } else if (change[i]<64) {
            Serial.print("00");
          } else if (change[i]<128) {
            Serial.print("0");
          }
          Serial.print(change[i],BIN);
        }
        Serial.println(" Difference");
      }
      for(byte i = 0; i<len; i++){
        prevrxBuf[i]=rxBuf[i];
      }
    }
  }
} //loop()
