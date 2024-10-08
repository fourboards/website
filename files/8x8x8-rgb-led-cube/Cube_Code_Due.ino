#include <SPI.h>
#include <DueTimer.h>/*
====================================================================
D0:   Tx            A0:   Layer 0
D1:   Rx            A1:   Layer 1
D2:   Button 1      A2:   Layer 2
D3:   Button 2      A3:   Layer 3
D4:   Layer 4       A4:   SDA
D5:   Layer 5       A5:   SCL
D6:   Layer 6       
D7:   Layer 7       
D8:   SDI Red       
D9:   SDI Green   
D10:  SDI Blue
D11:  OE
D12:  LE  
D13:  CLK
===================================================================
*/
const int redDataPin = 64;
const int greenDataPin = 62;
const int blueDataPin = 63;
const int enablePin = 65;//b20
const int latchPin = 67;//b16
const int clockPin =66;

  byte red[384]={63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
                 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
                 00,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
                 63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63};
  byte green[384]={00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
                 00,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
                 63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
                 63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
                 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,};
  byte blue[384]={00,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
                 63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
                 63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
                 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};  
                 
byte layer0bam0[24]; byte layer1bam0[24]; byte layer2bam0[24]; byte layer3bam0[24]; byte layer4bam0[24]; byte layer5bam0[24]; byte layer6bam0[24]; byte layer7bam0[24];
byte layer0bam1[24]; byte layer1bam1[24]; byte layer2bam1[24]; byte layer3bam1[24]; byte layer4bam1[24]; byte layer5bam1[24]; byte layer6bam1[24]; byte layer7bam1[24];
byte layer0bam2[24]; byte layer1bam2[24]; byte layer2bam2[24]; byte layer3bam2[24]; byte layer4bam2[24]; byte layer5bam2[24]; byte layer6bam2[24]; byte layer7bam2[24];
byte layer0bam3[24]; byte layer1bam3[24]; byte layer2bam3[24]; byte layer3bam3[24]; byte layer4bam3[24]; byte layer5bam3[24]; byte layer6bam3[24]; byte layer7bam3[24];
byte layer0bam4[24]; byte layer1bam4[24]; byte layer2bam4[24]; byte layer3bam4[24]; byte layer4bam4[24]; byte layer5bam4[24]; byte layer6bam4[24]; byte layer7bam4[24];
byte layer0bam5[24]; byte layer1bam5[24]; byte layer2bam5[24]; byte layer3bam5[24]; byte layer4bam5[24]; byte layer5bam5[24]; byte layer6bam5[24]; byte layer7bam5[24];
byte layer0bam6[24]; byte layer1bam6[24]; byte layer2bam6[24]; byte layer3bam6[24]; byte layer4bam6[24]; byte layer5bam6[24]; byte layer6bam6[24]; byte layer7bam6[24];
byte data[8][7][24];//layer,bam,register

byte tempData[24];
unsigned long startTime;
int bamCounter, bamBit;
int layer;
boolean update=0;

void setup() {

  SPI.begin();
   SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(2);
  SPI.setDataMode(SPI_MODE0);

 pinMode(redDataPin, OUTPUT);
 pinMode(greenDataPin, OUTPUT);  
 pinMode(blueDataPin, OUTPUT);
 pinMode(enablePin, OUTPUT);
 pinMode(latchPin, OUTPUT);  
 pinMode(clockPin, OUTPUT); 
 
 pinMode(54, OUTPUT);
 pinMode(55, OUTPUT);  
 pinMode(56, OUTPUT);
 pinMode(57, OUTPUT);
 pinMode(58, OUTPUT);  
 pinMode(59, OUTPUT);
 pinMode(60, OUTPUT);  
 pinMode(61, OUTPUT);
 
 //Serial.begin(115200);
 digitalWrite(enablePin,LOW);

  Timer5.attachInterrupt(updateCube);
  Timer5.start(25); //50Khz=20

}

void loop() {


RGBcube();
clean();
rainVersionTwo();
clean();
sinwaveTwo();
clean();
RGBcubeOrganised();
clean();
bouncyvTwo();
clean();
color_wheelTWO();
clean();
//dimmer();
//ledTest();
  //folder();
//folder();
//wipe_out();
//clean();
//harlem_shake();

}


void LED(int level, int row, int column, byte red, byte green, byte blue){//6 bit colour (0-63)
red=red*4;
green=green*4;
blue=blue*4;
 constrain(level,0,7);
 constrain(row,0,7);
 constrain(column,0,7);
 constrain(red,0,63);
 constrain(green,0,63);
 constrain(blue,0,63);

  //looking down on the cube, numbering procedure redArray[level][position]=value
  // 00 01 02 03 04 05 06 07
  // 08 09 10 11 12 13 14 15
  // 16 17 18 19 20 21 22 23
  // 24 25 26 27 28 29 30 31
  // 32 33 34 35 36 37 38 39
  // 40 41 42 43 44 45 46 47
  // 48 49 50 51 52 53 54 55
  // 56 57 58 59 60 61 62 63
  
column=7-column;
/*
for(int i=0;i<5;i++){
bitWrite(data[level][i][16+row],column,bitRead(red,i));
bitWrite(data[level][i][8+row],column,bitRead(green,i));
bitWrite(data[level][i][row],column,bitRead(blue,i));
}
*/
switch(level){
    case 0: bitWrite(layer0bam0[16+row],column,bitRead(red,0));bitWrite(layer0bam1[16+row],column,bitRead(red,1));bitWrite(layer0bam2[16+row],column,bitRead(red,2));bitWrite(layer0bam3[16+row],column,bitRead(red,3));bitWrite(layer0bam4[16+row],column,bitRead(red,4));bitWrite(layer0bam5[16+row],column,bitRead(red,5));bitWrite(layer0bam6[16+row],column,bitRead(red,6));
            bitWrite(layer0bam0[8+row],column,bitRead(green,0));bitWrite(layer0bam1[8+row],column,bitRead(green,1));bitWrite(layer0bam2[8+row],column,bitRead(green,2));bitWrite(layer0bam3[8+row],column,bitRead(green,3));bitWrite(layer0bam4[8+row],column,bitRead(green,4));bitWrite(layer0bam5[8+row],column,bitRead(green,5));bitWrite(layer0bam6[8+row],column,bitRead(green,6));
            bitWrite(layer0bam0[0+row],column,bitRead(blue,0));bitWrite(layer0bam1[0+row],column,bitRead(blue,1));bitWrite(layer0bam2[0+row],column,bitRead(blue,2));bitWrite(layer0bam3[0+row],column,bitRead(blue,3));bitWrite(layer0bam4[0+row],column,bitRead(blue,4));bitWrite(layer0bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer0bam6[0+row],column,bitRead(blue,6));
    case 1: bitWrite(layer1bam0[16+row],column,bitRead(red,0));bitWrite(layer1bam1[16+row],column,bitRead(red,1));bitWrite(layer1bam2[16+row],column,bitRead(red,2));bitWrite(layer1bam3[16+row],column,bitRead(red,3));bitWrite(layer1bam4[16+row],column,bitRead(red,4));bitWrite(layer1bam5[16+row],column,bitRead(red,5));bitWrite(layer1bam6[16+row],column,bitRead(red,6));
            bitWrite(layer1bam0[8+row],column,bitRead(green,0));bitWrite(layer1bam1[8+row],column,bitRead(green,1));bitWrite(layer1bam2[8+row],column,bitRead(green,2));bitWrite(layer1bam3[8+row],column,bitRead(green,3));bitWrite(layer1bam4[8+row],column,bitRead(green,4));bitWrite(layer1bam5[8+row],column,bitRead(green,5));bitWrite(layer1bam6[8+row],column,bitRead(green,6));
            bitWrite(layer1bam0[0+row],column,bitRead(blue,0));bitWrite(layer1bam1[0+row],column,bitRead(blue,1));bitWrite(layer1bam2[0+row],column,bitRead(blue,2));bitWrite(layer1bam3[0+row],column,bitRead(blue,3));bitWrite(layer1bam4[0+row],column,bitRead(blue,4));bitWrite(layer1bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer1bam6[0+row],column,bitRead(blue,6));
    case 2: bitWrite(layer2bam0[16+row],column,bitRead(red,0));bitWrite(layer2bam1[16+row],column,bitRead(red,1));bitWrite(layer2bam2[16+row],column,bitRead(red,2));bitWrite(layer2bam3[16+row],column,bitRead(red,3));bitWrite(layer2bam4[16+row],column,bitRead(red,4));bitWrite(layer2bam5[16+row],column,bitRead(red,5));bitWrite(layer2bam6[16+row],column,bitRead(red,6));
            bitWrite(layer2bam0[8+row],column,bitRead(green,0));bitWrite(layer2bam1[8+row],column,bitRead(green,1));bitWrite(layer2bam2[8+row],column,bitRead(green,2));bitWrite(layer2bam3[8+row],column,bitRead(green,3));bitWrite(layer2bam4[8+row],column,bitRead(green,4));bitWrite(layer2bam5[8+row],column,bitRead(green,5));bitWrite(layer2bam6[8+row],column,bitRead(green,6));
            bitWrite(layer2bam0[0+row],column,bitRead(blue,0));bitWrite(layer2bam1[0+row],column,bitRead(blue,1));bitWrite(layer2bam2[0+row],column,bitRead(blue,2));bitWrite(layer2bam3[0+row],column,bitRead(blue,3));bitWrite(layer2bam4[0+row],column,bitRead(blue,4));bitWrite(layer2bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer2bam6[0+row],column,bitRead(blue,6));
    case 3: bitWrite(layer3bam0[16+row],column,bitRead(red,0));bitWrite(layer3bam1[16+row],column,bitRead(red,1));bitWrite(layer3bam2[16+row],column,bitRead(red,2));bitWrite(layer3bam3[16+row],column,bitRead(red,3));bitWrite(layer3bam4[16+row],column,bitRead(red,4));bitWrite(layer3bam5[16+row],column,bitRead(red,5));bitWrite(layer3bam6[16+row],column,bitRead(red,6));
            bitWrite(layer3bam0[8+row],column,bitRead(green,0));bitWrite(layer3bam1[8+row],column,bitRead(green,1));bitWrite(layer3bam2[8+row],column,bitRead(green,2));bitWrite(layer3bam3[8+row],column,bitRead(green,3));bitWrite(layer3bam4[8+row],column,bitRead(green,4));bitWrite(layer3bam5[8+row],column,bitRead(green,5));bitWrite(layer3bam6[8+row],column,bitRead(green,6));
            bitWrite(layer3bam0[0+row],column,bitRead(blue,0));bitWrite(layer3bam1[0+row],column,bitRead(blue,1));bitWrite(layer3bam2[0+row],column,bitRead(blue,2));bitWrite(layer3bam3[0+row],column,bitRead(blue,3));bitWrite(layer3bam4[0+row],column,bitRead(blue,4));bitWrite(layer3bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer3bam6[0+row],column,bitRead(blue,6));
    case 4: bitWrite(layer4bam0[16+row],column,bitRead(red,0));bitWrite(layer4bam1[16+row],column,bitRead(red,1));bitWrite(layer4bam2[16+row],column,bitRead(red,2));bitWrite(layer4bam3[16+row],column,bitRead(red,3));bitWrite(layer4bam4[16+row],column,bitRead(red,4));bitWrite(layer4bam5[16+row],column,bitRead(red,5));bitWrite(layer4bam6[16+row],column,bitRead(red,6));
            bitWrite(layer4bam0[8+row],column,bitRead(green,0));bitWrite(layer4bam1[8+row],column,bitRead(green,1));bitWrite(layer4bam2[8+row],column,bitRead(green,2));bitWrite(layer4bam3[8+row],column,bitRead(green,3));bitWrite(layer4bam4[8+row],column,bitRead(green,4));bitWrite(layer4bam5[8+row],column,bitRead(green,5));bitWrite(layer4bam6[8+row],column,bitRead(green,6));
            bitWrite(layer4bam0[0+row],column,bitRead(blue,0));bitWrite(layer4bam1[0+row],column,bitRead(blue,1));bitWrite(layer4bam2[0+row],column,bitRead(blue,2));bitWrite(layer4bam3[0+row],column,bitRead(blue,3));bitWrite(layer4bam4[0+row],column,bitRead(blue,4));bitWrite(layer4bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer4bam6[0+row],column,bitRead(blue,6));
    case 5: bitWrite(layer5bam0[16+row],column,bitRead(red,0));bitWrite(layer5bam1[16+row],column,bitRead(red,1));bitWrite(layer5bam2[16+row],column,bitRead(red,2));bitWrite(layer5bam3[16+row],column,bitRead(red,3));bitWrite(layer5bam4[16+row],column,bitRead(red,4));bitWrite(layer5bam5[16+row],column,bitRead(red,5));bitWrite(layer5bam6[16+row],column,bitRead(red,6));
            bitWrite(layer5bam0[8+row],column,bitRead(green,0));bitWrite(layer5bam1[8+row],column,bitRead(green,1));bitWrite(layer5bam2[8+row],column,bitRead(green,2));bitWrite(layer5bam3[8+row],column,bitRead(green,3));bitWrite(layer5bam4[8+row],column,bitRead(green,4));bitWrite(layer5bam5[8+row],column,bitRead(green,5));bitWrite(layer5bam6[8+row],column,bitRead(green,6));
            bitWrite(layer5bam0[0+row],column,bitRead(blue,0));bitWrite(layer5bam1[0+row],column,bitRead(blue,1));bitWrite(layer5bam2[0+row],column,bitRead(blue,2));bitWrite(layer5bam3[0+row],column,bitRead(blue,3));bitWrite(layer5bam4[0+row],column,bitRead(blue,4));bitWrite(layer5bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer5bam6[0+row],column,bitRead(blue,6));
    case 6: bitWrite(layer6bam0[16+row],column,bitRead(red,0));bitWrite(layer6bam1[16+row],column,bitRead(red,1));bitWrite(layer6bam2[16+row],column,bitRead(red,2));bitWrite(layer6bam3[16+row],column,bitRead(red,3));bitWrite(layer6bam4[16+row],column,bitRead(red,4));bitWrite(layer6bam5[16+row],column,bitRead(red,5));bitWrite(layer6bam6[16+row],column,bitRead(red,6));
            bitWrite(layer6bam0[8+row],column,bitRead(green,0));bitWrite(layer6bam1[8+row],column,bitRead(green,1));bitWrite(layer6bam2[8+row],column,bitRead(green,2));bitWrite(layer6bam3[8+row],column,bitRead(green,3));bitWrite(layer6bam4[8+row],column,bitRead(green,4));bitWrite(layer6bam5[8+row],column,bitRead(green,5));bitWrite(layer6bam6[8+row],column,bitRead(green,6));
            bitWrite(layer6bam0[0+row],column,bitRead(blue,0));bitWrite(layer6bam1[0+row],column,bitRead(blue,1));bitWrite(layer6bam2[0+row],column,bitRead(blue,2));bitWrite(layer6bam3[0+row],column,bitRead(blue,3));bitWrite(layer6bam4[0+row],column,bitRead(blue,4));bitWrite(layer6bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer6bam6[0+row],column,bitRead(blue,6));
    case 7: bitWrite(layer7bam0[16+row],column,bitRead(red,0));bitWrite(layer7bam1[16+row],column,bitRead(red,1));bitWrite(layer7bam2[16+row],column,bitRead(red,2));bitWrite(layer7bam3[16+row],column,bitRead(red,3));bitWrite(layer7bam4[16+row],column,bitRead(red,4));bitWrite(layer7bam5[16+row],column,bitRead(red,5));bitWrite(layer7bam6[16+row],column,bitRead(red,6));
            bitWrite(layer7bam0[8+row],column,bitRead(green,0));bitWrite(layer7bam1[8+row],column,bitRead(green,1));bitWrite(layer7bam2[8+row],column,bitRead(green,2));bitWrite(layer7bam3[8+row],column,bitRead(green,3));bitWrite(layer7bam4[8+row],column,bitRead(green,4));bitWrite(layer7bam5[8+row],column,bitRead(green,5));bitWrite(layer7bam6[8+row],column,bitRead(green,6));
            bitWrite(layer7bam0[0+row],column,bitRead(blue,0));bitWrite(layer7bam1[0+row],column,bitRead(blue,1));bitWrite(layer7bam2[0+row],column,bitRead(blue,2));bitWrite(layer7bam3[0+row],column,bitRead(blue,3));bitWrite(layer7bam4[0+row],column,bitRead(blue,4));bitWrite(layer7bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer7bam6[0+row],column,bitRead(blue,6));

     }

}

void LED6bit(int level, int row, int column, byte red, byte green, byte blue){//6 bit colour (0-63)

 constrain(level,0,7);
 constrain(row,0,7);
 constrain(column,0,7);
 constrain(red,0,63);
 constrain(green,0,63);
 constrain(blue,0,63);

  //looking down on the cube, numbering procedure redArray[level][position]=value
  // 00 01 02 03 04 05 06 07
  // 08 09 10 11 12 13 14 15
  // 16 17 18 19 20 21 22 23
  // 24 25 26 27 28 29 30 31
  // 32 33 34 35 36 37 38 39
  // 40 41 42 43 44 45 46 47
  // 48 49 50 51 52 53 54 55
  // 56 57 58 59 60 61 62 63
  
column=7-column;
/*
for(int i=0;i<5;i++){
bitWrite(data[level][i][16+row],column,bitRead(red,i));
bitWrite(data[level][i][8+row],column,bitRead(green,i));
bitWrite(data[level][i][row],column,bitRead(blue,i));
}
*/
switch(level){
    case 0: bitWrite(layer0bam0[16+row],column,bitRead(red,0));bitWrite(layer0bam1[16+row],column,bitRead(red,1));bitWrite(layer0bam2[16+row],column,bitRead(red,2));bitWrite(layer0bam3[16+row],column,bitRead(red,3));bitWrite(layer0bam4[16+row],column,bitRead(red,4));bitWrite(layer0bam5[16+row],column,bitRead(red,5));bitWrite(layer0bam6[16+row],column,bitRead(red,6));
            bitWrite(layer0bam0[8+row],column,bitRead(green,0));bitWrite(layer0bam1[8+row],column,bitRead(green,1));bitWrite(layer0bam2[8+row],column,bitRead(green,2));bitWrite(layer0bam3[8+row],column,bitRead(green,3));bitWrite(layer0bam4[8+row],column,bitRead(green,4));bitWrite(layer0bam5[8+row],column,bitRead(green,5));bitWrite(layer0bam6[8+row],column,bitRead(green,6));
            bitWrite(layer0bam0[0+row],column,bitRead(blue,0));bitWrite(layer0bam1[0+row],column,bitRead(blue,1));bitWrite(layer0bam2[0+row],column,bitRead(blue,2));bitWrite(layer0bam3[0+row],column,bitRead(blue,3));bitWrite(layer0bam4[0+row],column,bitRead(blue,4));bitWrite(layer0bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer0bam6[0+row],column,bitRead(blue,6));
    case 1: bitWrite(layer1bam0[16+row],column,bitRead(red,0));bitWrite(layer1bam1[16+row],column,bitRead(red,1));bitWrite(layer1bam2[16+row],column,bitRead(red,2));bitWrite(layer1bam3[16+row],column,bitRead(red,3));bitWrite(layer1bam4[16+row],column,bitRead(red,4));bitWrite(layer1bam5[16+row],column,bitRead(red,5));bitWrite(layer1bam6[16+row],column,bitRead(red,6));
            bitWrite(layer1bam0[8+row],column,bitRead(green,0));bitWrite(layer1bam1[8+row],column,bitRead(green,1));bitWrite(layer1bam2[8+row],column,bitRead(green,2));bitWrite(layer1bam3[8+row],column,bitRead(green,3));bitWrite(layer1bam4[8+row],column,bitRead(green,4));bitWrite(layer1bam5[8+row],column,bitRead(green,5));bitWrite(layer1bam6[8+row],column,bitRead(green,6));
            bitWrite(layer1bam0[0+row],column,bitRead(blue,0));bitWrite(layer1bam1[0+row],column,bitRead(blue,1));bitWrite(layer1bam2[0+row],column,bitRead(blue,2));bitWrite(layer1bam3[0+row],column,bitRead(blue,3));bitWrite(layer1bam4[0+row],column,bitRead(blue,4));bitWrite(layer1bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer1bam6[0+row],column,bitRead(blue,6));
    case 2: bitWrite(layer2bam0[16+row],column,bitRead(red,0));bitWrite(layer2bam1[16+row],column,bitRead(red,1));bitWrite(layer2bam2[16+row],column,bitRead(red,2));bitWrite(layer2bam3[16+row],column,bitRead(red,3));bitWrite(layer2bam4[16+row],column,bitRead(red,4));bitWrite(layer2bam5[16+row],column,bitRead(red,5));bitWrite(layer2bam6[16+row],column,bitRead(red,6));
            bitWrite(layer2bam0[8+row],column,bitRead(green,0));bitWrite(layer2bam1[8+row],column,bitRead(green,1));bitWrite(layer2bam2[8+row],column,bitRead(green,2));bitWrite(layer2bam3[8+row],column,bitRead(green,3));bitWrite(layer2bam4[8+row],column,bitRead(green,4));bitWrite(layer2bam5[8+row],column,bitRead(green,5));bitWrite(layer2bam6[8+row],column,bitRead(green,6));
            bitWrite(layer2bam0[0+row],column,bitRead(blue,0));bitWrite(layer2bam1[0+row],column,bitRead(blue,1));bitWrite(layer2bam2[0+row],column,bitRead(blue,2));bitWrite(layer2bam3[0+row],column,bitRead(blue,3));bitWrite(layer2bam4[0+row],column,bitRead(blue,4));bitWrite(layer2bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer2bam6[0+row],column,bitRead(blue,6));
    case 3: bitWrite(layer3bam0[16+row],column,bitRead(red,0));bitWrite(layer3bam1[16+row],column,bitRead(red,1));bitWrite(layer3bam2[16+row],column,bitRead(red,2));bitWrite(layer3bam3[16+row],column,bitRead(red,3));bitWrite(layer3bam4[16+row],column,bitRead(red,4));bitWrite(layer3bam5[16+row],column,bitRead(red,5));bitWrite(layer3bam6[16+row],column,bitRead(red,6));
            bitWrite(layer3bam0[8+row],column,bitRead(green,0));bitWrite(layer3bam1[8+row],column,bitRead(green,1));bitWrite(layer3bam2[8+row],column,bitRead(green,2));bitWrite(layer3bam3[8+row],column,bitRead(green,3));bitWrite(layer3bam4[8+row],column,bitRead(green,4));bitWrite(layer3bam5[8+row],column,bitRead(green,5));bitWrite(layer3bam6[8+row],column,bitRead(green,6));
            bitWrite(layer3bam0[0+row],column,bitRead(blue,0));bitWrite(layer3bam1[0+row],column,bitRead(blue,1));bitWrite(layer3bam2[0+row],column,bitRead(blue,2));bitWrite(layer3bam3[0+row],column,bitRead(blue,3));bitWrite(layer3bam4[0+row],column,bitRead(blue,4));bitWrite(layer3bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer3bam6[0+row],column,bitRead(blue,6));
    case 4: bitWrite(layer4bam0[16+row],column,bitRead(red,0));bitWrite(layer4bam1[16+row],column,bitRead(red,1));bitWrite(layer4bam2[16+row],column,bitRead(red,2));bitWrite(layer4bam3[16+row],column,bitRead(red,3));bitWrite(layer4bam4[16+row],column,bitRead(red,4));bitWrite(layer4bam5[16+row],column,bitRead(red,5));bitWrite(layer4bam6[16+row],column,bitRead(red,6));
            bitWrite(layer4bam0[8+row],column,bitRead(green,0));bitWrite(layer4bam1[8+row],column,bitRead(green,1));bitWrite(layer4bam2[8+row],column,bitRead(green,2));bitWrite(layer4bam3[8+row],column,bitRead(green,3));bitWrite(layer4bam4[8+row],column,bitRead(green,4));bitWrite(layer4bam5[8+row],column,bitRead(green,5));bitWrite(layer4bam6[8+row],column,bitRead(green,6));
            bitWrite(layer4bam0[0+row],column,bitRead(blue,0));bitWrite(layer4bam1[0+row],column,bitRead(blue,1));bitWrite(layer4bam2[0+row],column,bitRead(blue,2));bitWrite(layer4bam3[0+row],column,bitRead(blue,3));bitWrite(layer4bam4[0+row],column,bitRead(blue,4));bitWrite(layer4bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer4bam6[0+row],column,bitRead(blue,6));
    case 5: bitWrite(layer5bam0[16+row],column,bitRead(red,0));bitWrite(layer5bam1[16+row],column,bitRead(red,1));bitWrite(layer5bam2[16+row],column,bitRead(red,2));bitWrite(layer5bam3[16+row],column,bitRead(red,3));bitWrite(layer5bam4[16+row],column,bitRead(red,4));bitWrite(layer5bam5[16+row],column,bitRead(red,5));bitWrite(layer5bam6[16+row],column,bitRead(red,6));
            bitWrite(layer5bam0[8+row],column,bitRead(green,0));bitWrite(layer5bam1[8+row],column,bitRead(green,1));bitWrite(layer5bam2[8+row],column,bitRead(green,2));bitWrite(layer5bam3[8+row],column,bitRead(green,3));bitWrite(layer5bam4[8+row],column,bitRead(green,4));bitWrite(layer5bam5[8+row],column,bitRead(green,5));bitWrite(layer5bam6[8+row],column,bitRead(green,6));
            bitWrite(layer5bam0[0+row],column,bitRead(blue,0));bitWrite(layer5bam1[0+row],column,bitRead(blue,1));bitWrite(layer5bam2[0+row],column,bitRead(blue,2));bitWrite(layer5bam3[0+row],column,bitRead(blue,3));bitWrite(layer5bam4[0+row],column,bitRead(blue,4));bitWrite(layer5bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer5bam6[0+row],column,bitRead(blue,6));
    case 6: bitWrite(layer6bam0[16+row],column,bitRead(red,0));bitWrite(layer6bam1[16+row],column,bitRead(red,1));bitWrite(layer6bam2[16+row],column,bitRead(red,2));bitWrite(layer6bam3[16+row],column,bitRead(red,3));bitWrite(layer6bam4[16+row],column,bitRead(red,4));bitWrite(layer6bam5[16+row],column,bitRead(red,5));bitWrite(layer6bam6[16+row],column,bitRead(red,6));
            bitWrite(layer6bam0[8+row],column,bitRead(green,0));bitWrite(layer6bam1[8+row],column,bitRead(green,1));bitWrite(layer6bam2[8+row],column,bitRead(green,2));bitWrite(layer6bam3[8+row],column,bitRead(green,3));bitWrite(layer6bam4[8+row],column,bitRead(green,4));bitWrite(layer6bam5[8+row],column,bitRead(green,5));bitWrite(layer6bam6[8+row],column,bitRead(green,6));
            bitWrite(layer6bam0[0+row],column,bitRead(blue,0));bitWrite(layer6bam1[0+row],column,bitRead(blue,1));bitWrite(layer6bam2[0+row],column,bitRead(blue,2));bitWrite(layer6bam3[0+row],column,bitRead(blue,3));bitWrite(layer6bam4[0+row],column,bitRead(blue,4));bitWrite(layer6bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer6bam6[0+row],column,bitRead(blue,6));
    case 7: bitWrite(layer7bam0[16+row],column,bitRead(red,0));bitWrite(layer7bam1[16+row],column,bitRead(red,1));bitWrite(layer7bam2[16+row],column,bitRead(red,2));bitWrite(layer7bam3[16+row],column,bitRead(red,3));bitWrite(layer7bam4[16+row],column,bitRead(red,4));bitWrite(layer7bam5[16+row],column,bitRead(red,5));bitWrite(layer7bam6[16+row],column,bitRead(red,6));
            bitWrite(layer7bam0[8+row],column,bitRead(green,0));bitWrite(layer7bam1[8+row],column,bitRead(green,1));bitWrite(layer7bam2[8+row],column,bitRead(green,2));bitWrite(layer7bam3[8+row],column,bitRead(green,3));bitWrite(layer7bam4[8+row],column,bitRead(green,4));bitWrite(layer7bam5[8+row],column,bitRead(green,5));bitWrite(layer7bam6[8+row],column,bitRead(green,6));
            bitWrite(layer7bam0[0+row],column,bitRead(blue,0));bitWrite(layer7bam1[0+row],column,bitRead(blue,1));bitWrite(layer7bam2[0+row],column,bitRead(blue,2));bitWrite(layer7bam3[0+row],column,bitRead(blue,3));bitWrite(layer7bam4[0+row],column,bitRead(blue,4));bitWrite(layer7bam5[0+row],column,bitRead(blue,5));break;bitWrite(layer7bam6[0+row],column,bitRead(blue,6));

     }

}

void updateCube(){

bitClear(REG_PIOB_ODSR,16);

if(bamCounter==8){
bamBit++;}
else if(bamCounter==24){
bamBit++;}
else if(bamCounter==56){
bamBit++;}
else if(bamCounter==120){
bamBit++;}
else if(bamCounter==248){
bamBit++;}


bamCounter++;//Here is where we increment the BAM counter
  if(bamCounter==504){//504
  bamCounter=0;
  bamBit=0;}

switch(bamBit){
case 0:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam0[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam0[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam0[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam0[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam0[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam0[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam0[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam0[i];}break;
     }break;
case 1:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam1[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam1[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam1[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam1[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam1[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam1[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam1[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam1[i];}break;
     }break;
case 2:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam2[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam2[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam2[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam2[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam2[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam2[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam2[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam2[i];}break;
     }break;
case 3:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam3[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam3[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam3[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam3[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam3[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam3[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam3[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam3[i];}break;
    } break;
case 4:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam4[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam4[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam4[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam4[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam4[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam4[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam4[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam4[i];}break;
    } break;
case 5:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam5[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam5[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam5[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam5[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam5[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam5[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam5[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam5[i];}break;
    } break;
case 6:  switch(layer){
    case 0: for(int i=0;i<24;i++){tempData[i]=layer0bam6[i];}break;
    case 1: for(int i=0;i<24;i++){tempData[i]=layer1bam6[i];}break;
    case 2: for(int i=0;i<24;i++){tempData[i]=layer2bam6[i];}break;
    case 3: for(int i=0;i<24;i++){tempData[i]=layer3bam6[i];}break; 
    case 4: for(int i=0;i<24;i++){tempData[i]=layer4bam6[i];}break;
    case 5: for(int i=0;i<24;i++){tempData[i]=layer5bam6[i];}break;
    case 6: for(int i=0;i<24;i++){tempData[i]=layer6bam6[i];}break;    
    case 7: for(int i=0;i<24;i++){tempData[i]=layer7bam6[i];}break;
    } break;
}
/*
for(int i=0;i<24;i++){
  tempData[i]=data[layer][bamBit][i];
}
*/
bitSet(REG_PIOB_ODSR,20);
REG_PIOA_ODSR=0;
SPI.transfer(tempData,24);

  switch(layer){
    case 0: bitSet(REG_PIOA_ODSR,4);break;
    case 1: bitSet(REG_PIOA_ODSR,3);break;
    case 2: bitSet(REG_PIOA_ODSR,23);break;
    case 3: bitSet(REG_PIOA_ODSR,6);break; 
    case 4: bitSet(REG_PIOA_ODSR,2);break;
    case 5: bitSet(REG_PIOA_ODSR,22);break;
    case 6: bitSet(REG_PIOA_ODSR,24);break;    
    case 7: bitSet(REG_PIOA_ODSR,16);break;
    } 
bitClear(REG_PIOB_ODSR,20);

layer++;
if(layer==8){layer=0;}
  
bitSet(REG_PIOB_ODSR,16);

}


//*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HER
//*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE
//*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE
//*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE*+*+*+*+*+*+*+*+*+*+*+*+PUT ANIMATIONS DOWN HERE
void RGBcubeOrganised(){

  int number[512];                             
  int pause=50;
  int r=63,g=0,b=0;
int counter=0;
  for(int i=0;i<512;i++){
    number[i]=counter;
    counter++;
    if(counter>383){counter=0;}
  }
startTime=millis();
while(millis()-startTime<20000){
  
for(int i=0;i<8;i++){
for(int j=0;j<8;j++){
for(int k=0;k<8;k++){
  LED6bit(i,j,k,red[number[(i*64)+(j*8)+k]],green[number[(i*64)+(j*8)+k]],blue[number[(i*64)+(j*8)+k]]);
  number[(i*64)+(j*8)+k]++;
  if(number[(i*64)+(j*8)+k]>383){number[(i*64)+(j*8)+k]=0;}
}}}
}
}

void RGBcube(){

  int number[512];                             
  int pause=50;
  int r=63,g=0,b=0;
  randomSeed(analogRead(A8));
  for(int i=0;i<512;i++){
    number[i]=random(0,384);
  }
startTime=millis();
while(millis()-startTime<20000){
  
for(int i=0;i<8;i++){
for(int j=0;j<8;j++){
for(int k=0;k<8;k++){
  LED6bit(i,j,k,red[number[(i*64)+(j*8)+k]],green[number[(i*64)+(j*8)+k]],blue[number[(i*64)+(j*8)+k]]);
  number[(i*64)+(j*8)+k]++;
  if(number[(i*64)+(j*8)+k]>383){number[(i*64)+(j*8)+k]=0;}
}}}
delay(1);
}
}

void dimmer(){
  for(int i=0;i<63;i++){
    LED6bit(0,0,0,i,0,0);
    delay(50);
  }
    for(int i=63;i>0;i--){
    LED6bit(0,0,0,i,0,0);    
    delay(50);
  }

}
void ledTest(){
for(int i=0;i<8;i++){
for(int j=0;j<8;j++){
for(int k=0;k<8;k++){
LED6bit(i,j,k,15,0,0);
delay(50);
}}}
  clean();
for(int i=0;i<8;i++){
for(int j=0;j<8;j++){
for(int k=0;k<8;k++){
LED6bit(i,j,k,0,15,0);
delay(50);
}}}
  clean();
for(int i=0;i<8;i++){
for(int j=0;j<8;j++){
for(int k=0;k<8;k++){
LED6bit(i,j,k,0,0,15);
delay(50);
}}}
  clean();

}
void wipe_out(){//*****wipe_out*****wipe_out*****wipe_out*****wipe_out*****wipe_out*****wipe_out*****wipe_out*****wipe_out
  int xxx=0, yyy=0, zzz=0;
  int fx=random(8), fy=random(8), fz=random(8), direct, fxm=1, fym=1, fzm=1, fxo=0, fyo=0, fzo=0;
  int  ftx=random(8), fty=random(8), ftz=random(8), ftxm=1, ftym=1, ftzm=1, ftxo=0, ftyo=0, ftzo=0;
  int select, rr, gg, bb, rrt, ggt, bbt;
  for(xxx=0; xxx<8; xxx++){
  for(yyy=0; yyy<8; yyy++){
  for(zzz=0; zzz<8; zzz++){
  LED(xxx, yyy, zzz, 0, 0, 0);
  }}}
  
       select=random(3);
    if(select==0){
      rr=random(1, 16);
      gg=random(1, 16);
      bb=0;} 
     if(select==1){
      rr=random(1, 16);
      gg=0;
      bb=random(1, 16);}    
     if(select==2){
      rr=0;
      gg=random(1, 16);
      bb=random(1, 16);}
      
       select=random(3);
    if(select==0){
      rrt=random(1, 16);
      ggt=random(1, 16);
      bbt=0;} 
     if(select==1){
      rrt=random(1, 16);
      ggt=0;
      bbt=random(1, 16);}    
     if(select==2){
      rrt=0;
      ggt=random(1, 16);
      bbt=random(1, 16);}  
        startTime=millis();
      
  while(millis()-startTime<10000){
  
    //fx=random(8); fy=random(8); fz=random(8);

    LED(fxo, fyo, fzo, 0, 0, 0);
    LED(fxo, fyo, fzo+1, 0, 0, 0);
    LED(fxo, fyo, fzo-1, 0, 0, 0);
    LED(fxo+1, fyo, fzo, 0, 0, 0);
    LED(fxo-1, fyo, fzo, 0, 0, 0);
    LED(fxo, fyo+1, fzo, 0, 0, 0);
    LED(fxo, fyo-1, fzo, 0, 0, 0);
    
    LED(ftxo, ftyo, ftzo, 0, 0, 0);
    LED(ftxo, ftyo, ftzo+1, 0, 0, 0);
    LED(ftxo, ftyo, ftzo-1, 0, 0, 0);
    LED(ftxo+1, ftyo, ftzo, 0, 0, 0);
    LED(ftxo-1, ftyo, ftzo, 0, 0, 0);
    LED(ftxo, ftyo+1, ftzo, 0, 0, 0);
    LED(ftxo, ftyo-1, ftzo, 0, 0, 0);

    LED(ftx, fty, ftz, rr, gg, bb);
    LED(ftx, fty, ftz+1, rr, gg, bb);
    LED(ftx, fty, ftz-1,  rr, gg, bb);
    LED(ftx+1, fty, ftz, rr, gg, bb);
    LED(ftx-1, fty, ftz, rr, gg, bb);
    LED(ftx, fty+1, ftz, rr, gg, bb);
    LED(ftx, fty-1, ftz, rr, gg, bb);     
    
    LED(fx, fy, fz, rrt, ggt, bbt);
    LED(fx, fy, fz+1, rrt, ggt, bbt);
    LED(fx, fy, fz-1, rrt, ggt, bbt);
    LED(fx+1, fy, fz, rrt, ggt, bbt);
    LED(fx-1, fy, fz, rrt, ggt, bbt);
    LED(fx, fy+1, fz, rrt, ggt, bbt);
    LED(fx, fy-1, fz, rrt, ggt, bbt);  
    
    
     delay(30);
     
    fxo=fx;
    fyo=fy;
    fzo=fz; 
    
    ftxo=ftx;
    ftyo=fty;
    ftzo=ftz; 
 
    direct=random(3);
    if(direct==0)
    fx= fx+fxm;
    if(direct==1)
    fy= fy+fym;  
    if(direct==2)
    fz= fz+fzm;  
  if(fx<0){
    fx=0; fxm=1;}
  if(fx>7){
    fx=7; fxm=-1;}  
  if(fy<0){
    fy=0; fym=1;}
  if(fy>7){
    fy=7; fym=-1;}    
  if(fz<0){
    fz=0; fzm=1;}
  if(fz>7){
    fz=7; fzm=-1;}  
  
      direct=random(3);
    if(direct==0)
    ftx= ftx+ftxm;
    if(direct==1)
    fty= fty+ftym;  
    if(direct==2)
    ftz= ftz+ftzm;  
  if(ftx<0){
    ftx=0; ftxm=1;}
  if(ftx>7){
    ftx=7; ftxm=-1;}  
  if(fty<0){
    fty=0; ftym=1;}
  if(fty>7){
    fty=7; ftym=-1;}    
  if(ftz<0){
    ftz=0; ftzm=1;}
  if(ftz>7){
    ftz=7; ftzm=-1;} 
  }//while
    for(xxx=0; xxx<8; xxx++){
  for(yyy=0; yyy<8; yyy++){
  for(zzz=0; zzz<8; zzz++){
  LED(xxx, yyy, zzz, 0, 0, 0);
  }}}
  
}//wipeout


void rainVersionTwo(){//****rainVersionTwo****rainVersionTwo****rainVersionTwo****rainVersionTwo****rainVersionTwo
  int x[64], y[64], z[64], addr, leds=64, bright=1, ledcolor, colowheel;
  int xx[64], yy[64], zz[64], xold[64], yold[64], zold[64], slowdown;
  
  for(addr=0; addr<64; addr++){
    x[addr]=random(8);
    y[addr]=random(8);
    z[addr]=random(8);
    xx[addr]=random(16);
    yy[addr]=random(16);
    zz[addr]=random(16);     
  }
  startTime=millis();
  while(millis()-startTime<20000){
  //wipe_out();
  //for(addr=0; addr<leds; addr++)
  //LED(zold[addr], xold[addr], yold[addr], 0, 0, 0);
  
if(ledcolor<200){
  for(addr=0; addr<leds; addr++){
    LED(zold[addr], xold[addr], yold[addr], 0, 0, 0);
  if(z[addr]>=7)
  LED(z[addr], x[addr], y[addr], 0, 5, 15);
  if(z[addr]==6)
  LED(z[addr], x[addr], y[addr], 0, 1, 9);
   if(z[addr]==5)
  LED(z[addr], x[addr], y[addr], 0, 0, 10);
   if(z[addr]==4)
  LED(z[addr], x[addr], y[addr], 1, 0, 11); 
    if(z[addr]==3)
  LED(z[addr], x[addr], y[addr], 3, 0, 12);
    if(z[addr]==2)
  LED(z[addr], x[addr], y[addr], 10, 0, 15);
    if(z[addr]==1)
  LED(z[addr], x[addr], y[addr], 10, 0, 10);
    if(z[addr]<=0)
  LED(z[addr], x[addr], y[addr], 10, 0, 1);
}}//200

  if(ledcolor>=200&&ledcolor<300){
  for(addr=0; addr<leds; addr++){
    LED(zold[addr], xold[addr], yold[addr], 0, 0, 0);
  if(z[addr]>=7)
  LED(z[addr], x[addr], y[addr], 15, 15, 0);
  if(z[addr]==6)
  LED(z[addr], x[addr], y[addr], 10, 10, 0);
   if(z[addr]==5)
  LED(z[addr], x[addr], y[addr], 15, 5, 0);
   if(z[addr]==4)
  LED(z[addr], x[addr], y[addr], 15, 2, 0); 
    if(z[addr]==3)
  LED(z[addr], x[addr], y[addr], 15, 1, 0);
    if(z[addr]==2)
  LED(z[addr], x[addr], y[addr], 15, 0, 0);
    if(z[addr]==1)
  LED(z[addr], x[addr], y[addr], 12, 0, 0);
    if(z[addr]<=0)
  LED(z[addr], x[addr], y[addr], 10, 0, 0);
}}//300

    if(ledcolor>=300&&ledcolor<400){

  }
     if(ledcolor>=500&&ledcolor<600){

}
  
  
  ledcolor++;
if(ledcolor>=300)
ledcolor=0;
  
    for(addr=0; addr<leds; addr++){
    xold[addr]=x[addr];
    yold[addr]=y[addr];
    zold[addr]=z[addr];
   } 
  
  
  delay(25);
  
  //for(addr=0; addr<leds; addr++)
  //LED(z[addr], x[addr], y[addr], 0, 0, 0);
    for(addr=0; addr<leds; addr++){
      
      //slowdown = random(2);
      //if(bitRead(z[addr],0))
  z[addr] = z[addr]-1;
  
 // x[addr] = x[addr]+1;
 // y[addr] = y[addr]+1;
  if(z[addr]<random(-100,0)){
    x[addr]=random(8);
    y[addr]=random(8);
    int select=random(3);
    if(select==0){
    xx[addr]=0;
    zz[addr]=random(16);
    yy[addr]=random(16);
    //zz[addr]=0;
    }
    if(select==1){
    xx[addr]=random(16);
    zz[addr]=0;
    yy[addr]=random(16);
    //yy[addr]=0;
    }
    if(select==2){
    xx[addr]=random(16);
    zz[addr]=random(16);
    yy[addr]=0;
    
    
    }    
   z[addr]=7; 
   
  }//-check
  }//add

  
  }//while
 
}//rainv2

void folder(){//****folder****folder****folder****folder****folder****folder****folder****folder****folder
  int xx, yy, zz, pullback[16], state=0, backorfront=7;//backorfront 7 for back 0 for front
  
  int folderaddr[16], LED_Old[16], oldpullback[16], ranx=random(16), rany=random(16), ranz=random(16), ranselect;
  int bot=0, top=1, right=0, left=0, back=0, front=0, side=0, side_select;
  
  folderaddr[0]=-7;
  folderaddr[1]=-6;
  folderaddr[2]=-5;
  folderaddr[3]=-4;
  folderaddr[4]=-3;
  folderaddr[5]=-2;
  folderaddr[6]=-1;
  folderaddr[7]=0;
  
  for(xx=0; xx<8; xx++){
  oldpullback[xx]=0;
  pullback[xx]=0;
  }
  
  
  
  startTime=millis();
  while(millis()-startTime<10000){ 
    if(top==1){
      if(side==0){
   //top to left-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(7-LED_Old[yy], yy-oldpullback[yy],xx , 0, 0, 0);
  LED(7-folderaddr[yy], yy-pullback[yy],xx , ranx, rany, ranz);
  }}}
    if(side==2){
      //top to back-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(7-LED_Old[yy], xx, yy-oldpullback[yy], 0, 0, 0);
  LED(7-folderaddr[yy], xx, yy-pullback[yy], ranx, rany, ranz);
  }}}
  if(side==3){
      //top-side to front-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(7-LED_Old[7-yy], xx, yy+oldpullback[yy], 0, 0, 0);
  LED(7-folderaddr[7-yy], xx, yy+pullback[yy], ranx, rany, ranz);
  }}}
    if(side==1){
    //top-side to right
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(7-LED_Old[7-yy], yy+oldpullback[yy],xx , 0, 0, 0);
  LED(7-folderaddr[7-yy], yy+pullback[yy],xx , ranx, rany, ranz);
  }}}
    }//top
    
    if(right==1){
    if(side==4){
   //right-side to top
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy+oldpullback[7-yy],7-LED_Old[7-yy],xx , 0, 0, 0);
  LED( yy+pullback[7-yy],7-folderaddr[7-yy],xx , ranx, rany, ranz);
  }}}
    if(side==3){
    //right-side to front-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, 7-LED_Old[7-yy],yy+oldpullback[yy], 0, 0, 0);
  LED(xx,7-folderaddr[7-yy], yy+pullback[yy], ranx, rany, ranz);
  }}}
    if(side==2){
   //right-side to back-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, 7-LED_Old[yy],yy-oldpullback[yy], 0, 0, 0);
  LED(xx,7-folderaddr[yy], yy-pullback[yy], ranx, rany, ranz);
  }}}
    if(side==5){
    //right-side to bottom
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy-oldpullback[yy],7-LED_Old[yy],xx , 0, 0, 0);
  LED( yy-pullback[yy],7-folderaddr[yy],xx , ranx, rany, ranz);
  }}}
    }//right
    
 if(left==1){
    if(side==4){
   //left-side to top
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy+oldpullback[yy],LED_Old[7-yy],xx , 0, 0, 0);
  LED( yy+pullback[yy],folderaddr[7-yy],xx , ranx, rany, ranz);
  }}}
  if(side==3){
     //left-side to front-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, LED_Old[7-yy],yy+oldpullback[yy], 0, 0, 0);
  LED(xx,folderaddr[7-yy], yy+pullback[yy], ranx, rany, ranz);
  }}}
  if(side==2){
//left-side to back-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, LED_Old[yy],yy-oldpullback[yy], 0, 0, 0);
  LED(xx,folderaddr[yy], yy-pullback[yy], ranx, rany, ranz);
  }}}
  if(side==5){
  //left-side to bottom
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy-oldpullback[yy],LED_Old[yy],xx , 0, 0, 0);
  LED( yy-pullback[yy],folderaddr[yy],xx , ranx, rany, ranz);
  }}}
  }//left
  
  
   if(back==1){
    if(side==1){
  //back-side to right-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, yy+oldpullback[yy],LED_Old[7-yy], 0, 0, 0);
  LED(xx, yy+pullback[yy],folderaddr[7-yy], ranx, rany, ranz);
  }}}
  if(side==4){
  // back-side to top-side
    for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy+oldpullback[yy],xx,LED_Old[7-yy] , 0, 0, 0);
  LED( yy+pullback[yy],xx,folderaddr[7-yy] , ranx, rany, ranz);
  }}}
  if(side==5){
  // back-side to bottom
    for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy-oldpullback[yy],xx,LED_Old[yy] , 0, 0, 0);
  LED( yy-pullback[yy],xx,folderaddr[yy] , ranx, rany, ranz);
  }}}//state1
 if(side==0){
//back-side to left-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, yy-oldpullback[yy],LED_Old[yy], 0, 0, 0);
  LED(xx, yy-pullback[yy],folderaddr[yy], ranx, rany, ranz);
  }}}
   }//back
   if(bot==1){
    if(side==1){
    // bottom-side to right-side
      for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(LED_Old[7-yy], yy+oldpullback[yy],xx , 0, 0, 0);
  LED(folderaddr[7-yy], yy+pullback[yy],xx , ranx, rany, ranz);
  }}}
  if(side==3){
  //bottom to front-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(LED_Old[7-yy], xx, yy+oldpullback[yy], 0, 0, 0);
  LED(folderaddr[7-yy], xx, yy+pullback[yy], ranx, rany, ranz);
  }}}
if(side==2){
  //bottom to back-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(LED_Old[yy], xx, yy-oldpullback[yy], 0, 0, 0);
  LED(folderaddr[yy], xx, yy-pullback[yy], ranx, rany, ranz);
  }}}
if(side==0){
  //bottom to left-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(LED_Old[yy], yy-oldpullback[yy],xx , 0, 0, 0);
  LED(folderaddr[yy], yy-pullback[yy],xx , ranx, rany, ranz);
  }}}
   }//bot
   
    if(front==1){
   if(side==0){
    //front-side to left-side
   for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, yy-oldpullback[yy],7-LED_Old[yy], 0, 0, 0);
  LED(xx, yy-pullback[yy],7-folderaddr[yy], ranx, rany, ranz);
  }}}
  if(side==5){
      // front-side to bottom
    for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy-oldpullback[yy],xx,7-LED_Old[yy] , 0, 0, 0);
  LED( yy-pullback[yy],xx,7-folderaddr[yy] , ranx, rany, ranz);
  }}}
  if(side==4){
      // front-side to top-side
    for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(yy+oldpullback[yy],xx,7-LED_Old[7-yy] , 0, 0, 0);
  LED( yy+pullback[yy],xx,7-folderaddr[7-yy] , ranx, rany, ranz);
  }}}
  if(side==1){
      //front-side to right-side
  for(yy=0; yy<8; yy++){
  for(xx=0; xx<8; xx++){
  LED(xx, yy+oldpullback[yy],7-LED_Old[7-yy], 0, 0, 0);
  LED(xx, yy+pullback[yy],7-folderaddr[7-yy], ranx, rany, ranz);
  }}}
    }//front

  


  delay(50);//               DELAY   DELAY  DELAY
  for(xx=0; xx<8; xx++){
  LED_Old[xx]=folderaddr[xx];
  oldpullback[xx]=pullback[xx];
  }
  

  
  
 
  if(folderaddr[7]==7){
   // pullback=8;
    for(zz=0; zz<8; zz++)
  pullback[zz] = pullback[zz]+1;
 
   if(pullback[7]==8){//finished with fold
   delay(100);
     //state++;
     //if(state==4)
     //state=0;
     
     ranselect= random(3);
     if(ranselect==0){
     ranx=0;
     rany=random(1,16);
     ranz=random(1,16);}
     if(ranselect==1){
     ranx=random(1,16);
     rany=0;
     ranz=random(1,16);}
     if(ranselect==2){
     ranx=random(1,16);
     rany=random(1,16);
     ranz=0;}     
     
     side_select=random(3);
     
     if(top==1){//                 TOP
     top=0; 
     if(side==0){//top to left
      left=1;
      if(side_select==0) side=2;
      if(side_select==1) side=3;
      //if(side_select==2) side=4;
      if(side_select==2) side=5;} else    
     if(side==1){//top to right
      right=1;
      if(side_select==0) side=5;
      if(side_select==1) side=2;
      if(side_select==2) side=3;
      //if(side_select==3) side=4;
    } else  
     if(side==2){//top to back
      back=1;
      if(side_select==0) side=0;
      if(side_select==1) side=1;
      if(side_select==2) side=5;
      //if(side_select==3) side=4;
    } else      
      if(side==3){//top to front
      front=1;
      if(side_select==0) side=0;
      if(side_select==1) side=1;
      if(side_select==2) side=5;
      //if(side_select==3) side=4;
    }   
     } else//top
     if(bot==1){//                 BOTTOM
     bot=0; 
     if(side==0){//bot to left
      left=1;
      if(side_select==0) side=2;
      if(side_select==1) side=3;
      if(side_select==2) side=4;
      //if(side_select==3) side=5;
    } else    
     if(side==1){//bot to right
      right=1;
      //if(side_select==0) side=5;
      if(side_select==0) side=2;
      if(side_select==1) side=3;
      if(side_select==2) side=4;} else  
     if(side==2){//bot to back
      back=1;
      if(side_select==0) side=0;
      if(side_select==1) side=1;
      //if(side_select==2) side=5;
      if(side_select==2) side=4;} else      
      if(side==3){//bot to front
      front=1;
      if(side_select==0) side=0;
      if(side_select==1) side=1;
      //if(side_select==2) side=5;
      if(side_select==2) side=4;}   
     } else//bot
          if(right==1){//                 RIGHT
     right=0; 
     if(side==4){//right to top
      top=1;
      if(side_select==0) side=2;
      if(side_select==1) side=3;
      if(side_select==2) side=0;
      //if(side_select==3) side=1;
    } else    
     if(side==5){//right to bot
      bot=1;
      if(side_select==0) side=0;
      if(side_select==1) side=2;
      if(side_select==2) side=3;
      //if(side_select==3) side=1;
    } 
      else  
     if(side==2){//right to back
      back=1;
      if(side_select==0) side=0;
      //if(side_select==1) side=1;
      if(side_select==1) side=5;
      if(side_select==2) side=4;} else      
      if(side==3){//right to front
      front=1;
      if(side_select==0) side=0;
      //if(side_select==1) side=1;
      if(side_select==1) side=5;
      if(side_select==2) side=4;}   
     } else//bot
              if(left==1){//                 LEFT
     left=0; 
     if(side==4){//left to top
      top=1;
      //if(side_select==0) side=2;
      if(side_select==0) side=3;
      if(side_select==1) side=2;
      if(side_select==2) side=1;} else    
     if(side==5){//left to bot
      bot=1;
      //if(side_select==0) side=0;
      if(side_select==0) side=2;
      if(side_select==1) side=3;
      if(side_select==2) side=1;} else  
     if(side==2){//left to back
      back=1;
      //if(side_select==0) side=0;
      if(side_select==0) side=1;
      if(side_select==1) side=5;
      if(side_select==2) side=4;} else      
      if(side==3){//left to front
      front=1;
      //if(side_select==0) side=0;
      if(side_select==0) side=1;
      if(side_select==1) side=5;
      if(side_select==2) side=4;}   
     } else//bot
              if(front==1){//                 front
     front=0; 
     if(side==4){//front to top
      top=1;
      if(side_select==0) side=2;
      //if(side_select==1) side=3;
      if(side_select==1) side=0;
      if(side_select==2) side=1;} else    
     if(side==5){//front to bot
      bot=1;
      if(side_select==0) side=0;
      if(side_select==1) side=2;
      //if(side_select==2) side=3;
      if(side_select==2) side=1;} else  
     if(side==0){//front to left
      left=1;
      if(side_select==0) side=2;
     // if(side_select==1) side=3;
      if(side_select==1) side=5;
      if(side_select==2) side=4;} else      
      if(side==1){//front to right
      right=1;
      if(side_select==0) side=2;
     // if(side_select==1) side=3;
      if(side_select==1) side=5;
      if(side_select==2) side=4;}   
     } else//bot
              if(back==1){//                 back
     back=0; 
     if(side==4){//back to top
      top=1;
      //if(side_select==0) side=2;
      if(side_select==0) side=3;
      if(side_select==1) side=0;
      if(side_select==2) side=1;} else    
     if(side==5){//back to bot
      bot=1;
      if(side_select==0) side=0;
      //if(side_select==1) side=2;
      if(side_select==1) side=3;
      if(side_select==2) side=1;} else  
     if(side==0){//back to left
      left=1;
      //if(side_select==0) side=2;
      if(side_select==0) side=3;
      if(side_select==1) side=5;
      if(side_select==2) side=4;} else      
      if(side==1){//back to right
      right=1;
      //if(side_select==0) side=2;
      if(side_select==0) side=3;
      if(side_select==1) side=5;
      if(side_select==2) side=4;}   
     } //bot

    
      // for(yy=0; yy<8; yy++)
  //for(xx=0; xx<8; xx++)
  //LED(LED_Old[yy], xx, yy-oldpullback[yy], 0, 0, 0);
  for(xx=0; xx<8; xx++){
  oldpullback[xx]=0;
  pullback[xx]=0;}
 
  folderaddr[0]=-8;
  folderaddr[1]=-7;
  folderaddr[2]=-6;
  folderaddr[3]=-5;
  folderaddr[4]=-4;
  folderaddr[5]=-3;
  folderaddr[6]=-2;
  folderaddr[7]=-1;

}//pullback==7
  }//folderaddr==7    

  if(folderaddr[7]!=7)
  for(zz=0; zz<8; zz++)
  folderaddr[zz] = folderaddr[zz]+1;
  
}//while
  
  
  
  
  
}//folder


void bouncyvTwo(){//****bouncyTwo****bouncyTwo****bouncyTwo****bouncyTwo****bouncyTwo****bouncyTwo****bouncyTwo
  int wipex, wipey, wipez, ranr, rang, ranb, select, oldx[50], oldy[50], oldz[50];
  int x[50], y[50], z[50], addr, ledcount=20, direct, direcTwo;
  int xx[50], yy[50], zz[50];
  int xbit=1, ybit=1, zbit=1;
   for(addr=0; addr<ledcount+1; addr++){
     oldx[addr]=0;
     oldy[addr]=0;
     oldz[addr]=0;
     x[addr]=0;
     y[addr]=0;
     z[addr]=0;
     xx[addr]=0;
     yy[addr]=0;
     zz[addr]=0;
 
   }
  
      startTime=millis();
      
  while(millis()-startTime<15000){
    direct = random(3);

for(addr=1; addr<ledcount+1; addr++){
LED(oldx[addr], oldy[addr],oldz[addr], 0,0,0);
LED(x[addr], y[addr], z[addr], xx[addr],yy[addr],zz[addr]);
}

for(addr=1; addr<ledcount+1; addr++){
oldx[addr]=x[addr];
oldy[addr]=y[addr];
oldz[addr]=z[addr];
}
delay(20);


//direcTwo=random(3);  
//if(direcTwo==1)



if(direct==0)
x[0]= x[0]+xbit;
if(direct==1)
y[0]= y[0]+ybit;
if(direct==2)
z[0]= z[0]+zbit;

if(direct==3)
x[0]= x[0]-xbit;
if(direct==4)
y[0]= y[0]-ybit;
if(direct==5)
z[0]= z[0]-zbit;





if(x[0]>7){
xbit=-1;
x[0]=7;
xx[0]=random(16);
yy[0]=random(16);
zz[0]=0;
//wipe_out();
}
if(x[0]<0){
xbit=1;
  x[0]=0;
xx[0]=random(16);
yy[0]=0;
zz[0]=random(16);
//wipe_out();
}
if(y[0]>7){
ybit=-1;
y[0]=7;
xx[0]=0;
yy[0]=random(16);
zz[0]=random(16);
//wipe_out();
}
if(y[0]<0){
ybit=1;
  y[0]=0;
  xx[0]=0;
yy[0]=random(16);
zz[0]=random(16);
//wipe_out();
}
if(z[0]>7){
zbit=-1;
z[0]=7;
xx[0]=random(16);
yy[0]=0;
zz[0]=random(16);
//wipe_out();
}
if(z[0]<0){
zbit=1;
  z[0]=0;
  xx[0]=random(16);
yy[0]=random(16);
zz[0]=0;
//wipe_out();
}

for(addr=ledcount; addr>0; addr--){
  x[addr]=x[addr-1];
  y[addr]=y[addr-1];
  z[addr]=z[addr-1];
  xx[addr]=xx[addr-1];
  yy[addr]=yy[addr-1];
  zz[addr]=zz[addr-1];
}


  }//while
  

  
  
  
}//bouncyv2
void sinwaveTwo(){//*****sinewaveTwo*****sinewaveTwo*****sinewaveTwo*****sinewaveTwo*****sinewaveTwo*****sinewaveTwo
    int sinewavearray[8], addr, sinemult[8], colselect, rr=0, gg=0, bb=15, addrt;
  int sinewavearrayOLD[8], select, subZ=-7, subT=7, multi=0;//random(-1, 2);
  sinewavearray[0]=0;
  sinemult[0]=1;
   sinewavearray[1]=1;
  sinemult[1]=1; 
    sinewavearray[2]=2;
  sinemult[2]=1;
    sinewavearray[3]=3;
  sinemult[3]=1;
    sinewavearray[4]=4;
  sinemult[4]=1;
    sinewavearray[5]=5;
  sinemult[5]=1;
    sinewavearray[6]=6;
  sinemult[6]=1;
    sinewavearray[7]=7;
  sinemult[7]=1;
  
      startTime=millis();
      
  while(millis()-startTime<15000){
  for(addr=0; addr<8; addr++){
    if(sinewavearray[addr]==7){
    sinemult[addr]=-1;
    }
    if(sinewavearray[addr]==0){
    sinemult[addr]=1;     
    }
    sinewavearray[addr] = sinewavearray[addr] + sinemult[addr];
}//addr
     if(sinewavearray[0]==7){
     select=random(3);
    if(select==0){
      rr=random(1, 16);
      gg=random(1, 16);
      bb=0;} 
     if(select==1){
      rr=random(1, 16);
      gg=0;
      bb=random(1, 16);}    
     if(select==2){
      rr=0;
      gg=random(1, 16);
      bb=random(1, 16);}
   /*
 if(multi==1)
 multi=0;
 else
 multi=1;
*/

 }    
   


      for(addr=0; addr<8; addr++){
    LED(sinewavearrayOLD[addr], addr, 0, 0, 0, 0);
    LED(sinewavearrayOLD[addr], 0, addr, 0, 0, 0);
    LED(sinewavearrayOLD[addr], subT-addr, 7, 0, 0, 0);
    LED(sinewavearrayOLD[addr], 7, subT-addr, 0, 0, 0);     
   LED(sinewavearray[addr], addr, 0, rr, gg, bb);
   LED(sinewavearray[addr], 0, addr, rr, gg, bb);
   LED(sinewavearray[addr], subT-addr,7, rr, gg, bb);
   LED(sinewavearray[addr], 7, subT-addr, rr, gg, bb);
    }//}
    
       for(addr=1; addr<7; addr++){   
    LED(sinewavearrayOLD[addr+multi*1], addr, 1, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*1], 1, addr, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*1], subT-addr, 6, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*1], 6, subT-addr, 0, 0, 0);  
   LED(sinewavearray[addr+multi*1], addr, 1, rr, gg, bb);
   LED(sinewavearray[addr+multi*1], 1, addr, rr, gg, bb);
   LED(sinewavearray[addr+multi*1], subT-addr,6, rr, gg, bb);
   LED(sinewavearray[addr+multi*1], 6, subT-addr, rr, gg, bb);
       }
 
        for(addr=2; addr<6; addr++){   
    LED(sinewavearrayOLD[addr+multi*2], addr, 2, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*2], 2, addr, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*2], subT-addr, 5, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*2], 5, subT-addr, 0, 0, 0);  
   LED(sinewavearray[addr+multi*2], addr, 2, rr, gg, bb);
   LED(sinewavearray[addr+multi*2], 2, addr, rr, gg, bb);
   LED(sinewavearray[addr+multi*2], subT-addr,5, rr, gg, bb);
   LED(sinewavearray[addr+multi*2], 5, subT-addr, rr, gg, bb);
       }  
             for(addr=3; addr<5; addr++){   
    LED(sinewavearrayOLD[addr+multi*3], addr, 3, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*3], 3, addr, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*3], subT-addr, 4, 0, 0, 0);
    LED(sinewavearrayOLD[addr+multi*3], 4, subT-addr, 0, 0, 0);  
   LED(sinewavearray[addr+multi*3], addr, 3, rr, gg, bb);
   LED(sinewavearray[addr+multi*3], 3, addr, rr, gg, bb);
   LED(sinewavearray[addr+multi*3], subT-addr,4, rr, gg, bb);
   LED(sinewavearray[addr+multi*3], 4, subT-addr, rr, gg, bb);
       }      
     
     for(addr=0; addr<8; addr++)
   sinewavearrayOLD[addr]=sinewavearray[addr];
    delay(15);

    
    
  }//while
  
  
}//SinewaveTwo

void color_wheel(){
  int xx, yy, zz, ww, rr=1, gg=1, bb=1, ranx, rany, swiper;
  
        startTime=millis();
      
  while(millis()-startTime<100000){
    swiper=random(3);
     ranx=random(16);
     rany=random(16);
     
    for(xx=0;xx<8;xx++){
    for(yy=0;yy<8;yy++){ 
    for(zz=0;zz<8;zz++){
      
     LED(xx, yy, zz,  ranx, 0, rany);
    }}
  delay(100);
}

     ranx=random(16);
     rany=random(16);
     
    for(xx=7;xx>=0;xx--){ 
    for(yy=0;yy<8;yy++){
    for(zz=0;zz<8;zz++){
    LED(xx,yy, zz, ranx, rany, 0);
    }}
  delay(100); 
  }
       ranx=random(16);
     rany=random(16);
    for(xx=0;xx<8;xx++){ 
    for(yy=0;yy<8;yy++){
    for(zz=0;zz<8;zz++){
      LED(xx,yy, zz, 0, ranx, rany);
    }}
    delay(100);
  }
    
     ranx=random(16);
     rany=random(16);
    for(xx=7;xx>=0;xx--){ 
    for(yy=0;yy<8;yy++){
    for(zz=0;zz<8;zz++){
    LED(xx,yy, zz, rany, ranx, 0);
    }}
  delay(100); 
  }
    
  }//while
    
}//color wheel

void color_wheelTWO(){//*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo
  int xx, yy, zz, ww, rr=1, gg=1, bb=1, ranx, rany ,ranz, select, swiper;
  
        startTime=millis();
      
  while(millis()-startTime<10000){
    swiper=random(6);
    select=random(3);
    if(select==0){
     ranx=0;
     rany=random(16);
     ranz=random(16);}
    if(select==1){
     ranx=random(16);
     rany=0;
     ranz=random(16);}   
      if(select==2){
     ranx=random(16);
     rany=random(16);
     ranz=0;}  
    
     
    if(swiper==0){
    for(yy=0;yy<8;yy++){//left to right
    for(xx=0;xx<8;xx++){
    for(zz=0;zz<8;zz++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
  delay(30);
 }}
    if(swiper==1){//bot to top
    for(xx=0;xx<8;xx++){
    for(yy=0;yy<8;yy++){
    for(zz=0;zz<8;zz++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
  delay(30);
 }}  
    if(swiper==2){//back to front
    for(zz=0;zz<8;zz++){
    for(xx=0;xx<8;xx++){
    for(yy=0;yy<8;yy++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
  delay(30);
}}    
    if(swiper==3){
    for(yy=7;yy>=0;yy--){//right to left
    for(xx=0;xx<8;xx++){
    for(zz=0;zz<8;zz++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
  delay(30);
}}
    if(swiper==4){//top to bot
    for(xx=7;xx>=0;xx--){
    for(yy=0;yy<8;yy++){
    for(zz=0;zz<8;zz++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
 delay(30);
}}  
    if(swiper==5){//front to back
    for(zz=7;zz>=0;zz--){
    for(xx=0;xx<8;xx++){
    for(yy=0;yy<8;yy++){
    LED(xx, yy, zz,  ranx, ranz, rany);
    }}
  delay(30);
}}
  
  
  
  
  }//while
    
}//color wheel

//    Harlem Shake    Harlem Shake    Harlem Shake    Harlem Shake    Harlem Shake

void harlem_shake(){
  
  
  
int greenx = random(1,7),greeny = random(1,7),bluex = random(1,7),bluey = random(1,7),redx = random(1,7),redy = random(1,7);
int greenmult=1, bluemult=1, redmult=1;
int greenmulty=1, bluemulty=1, redmulty=1;
int oredx, oredy,obluex,obluey,ogreenx,ogreeny, cb1=15,cb2=0,cr1=15,cr2=0,cg1=15,cg2=0;
int time_counter=10, timemult=2;
int m;
int c1=1,c2=1,c3=1,xmult=1,ymult=1,zmult=1,x=4,y=4,z=4,color_select, xo, yo, zo;
int c21=1,c22=1,c23=1,x2mult=1,y2mult=1,z2mult=1,x2=2,y2=2,z2=2,color_select2, x2o, y2o, z2o;

int counter, i, j, k;
for(counter=0; counter<150; counter++){
  for(i=0; i<8; i++){
  LED(i,oredx,oredx,0,0,0);
  }
  for(i=0; i<8; i++){
  LED(i,redx,redx,15,0,0);
  }
  
  oredx=redx;
  oredy=redy;
  
for(i=100; i>time_counter; i--)
  delay(1);

  time_counter=time_counter+timemult;
  if(time_counter>100||time_counter<10)
  timemult=timemult*-1;


   if(redy>6 || redy<1){
  redmulty=redmulty*-1;  
  
  }
 
   if(redx>6 || redx<1){
  redmult=redmult*-1;  
  
  cr1=random(16);
  cr2=random(16);
   }

  redy=redy+redmulty;
  redx=redx+redmult;
}//counter


for(counter=0; counter<85; counter++){
  for(i=0; i<8; i++){
  LED(i,oredx,oredx,0,0,0);
  LED(ogreenx,i,ogreeny,0,0,0);
  }
  for(i=0; i<8; i++){
  LED(i,redx,redx,15,0,0);
  LED(greenx,i,greeny,0,15,0);
  }
  ogreenx=greenx;
  ogreeny=greeny;
  oredx=redx;
  oredy=redy;
  
for(i=100; i>time_counter; i--)
  delay(1);

  time_counter=time_counter+timemult;
  if(time_counter>100||time_counter<10)
  timemult=timemult*-1;

   
     if(greeny>6 || greeny<1)
  greenmulty=greenmulty*-1;

   if(redy>6 || redy<1){
  redmulty=redmulty*-1;  
  
  }
 
   
     if(greenx>6 || greenx<1){
  greenmult=greenmult*-1;
  greeny = greeny + greenmulty;
  cg1=random(16);
  cg2=random(16);
  }

   if(redx>6 || redx<1){
  redmult=redmult*-1;  
  
  cr1=random(16);
  cr2=random(16);
   }
  greenx=greenx+greenmult;
  
  redy=redy+redmulty;
  redx=redx+redmult;
}//counter


for(counter=0; counter<85; counter++){
  for(i=0; i<8; i++){
  LED(i,oredx,oredx,0,0,0);
  LED(obluey,obluex,i,0,0,0);
  LED(ogreenx,i,ogreeny,0,0,0);
  }
  for(i=0; i<8; i++){
  LED(i,redx,redx,15,0,0);
  LED(bluey,bluex,i,0,0,15);
  LED(greenx,i,greeny,0,15,0);
  }
  ogreenx=greenx;
  ogreeny=greeny;
  obluex=bluex;
  obluey=bluey;
  oredx=redx;
  oredy=redy;
  
for(i=100; i>time_counter; i--)
  delay(1);

  time_counter=time_counter+timemult;
  if(time_counter>100||time_counter<10)
  timemult=timemult*-1;

   
     if(greeny>6 || greeny<1)
  greenmulty=greenmulty*-1;

   if(bluey>6 || bluey<1)
  bluemulty=bluemulty*-1;

   if(redy>6 || redy<1){
  redmulty=redmulty*-1;  
  
  }
 
   
     if(greenx>6 || greenx<1){
  greenmult=greenmult*-1;
  greeny = greeny + greenmulty;
  cg1=random(16);
  cg2=random(16);
  }
   if(bluex>6 || bluex<1){
  bluemult=bluemult*-1;
  bluey=bluey+bluemulty;
  cb1=random(16);
  cb2=random(16);
   }
   if(redx>6 || redx<1){
  redmult=redmult*-1;  
  
  cr1=random(16);
  cr2=random(16);
   }
  greenx=greenx+greenmult;
  bluex=bluex+bluemult;
  redy=redy+redmulty;
  redx=redx+redmult;
}//counter



for(counter=0; counter<3; counter++){
  for(i=0; i<8; i++)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,15,15,15);
  delay(50);
  for(i=0; i<8; i++)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,0,0,0);
  delay(50);
}//counter

  for(m=0; m<1; m++){
    
    
  for(i=0; i<8; i++)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,0,random(16),random(16));

  for(i=7; i>=0; i--)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,random(16),0,random(16));

  for(i=0; i<8; i++)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,random(16),random(16),0);

  for(i=7; i>=0; i--)
  for(j=0; j<8; j++)
  for(k=0; k<8; k++)
  LED(i,j,k,random(16),0,random(16));
  }

clean();


for(m=0; m<3; m++){
    for(k=0; k<200; k++){
  LED(random(8),random(8),random(8),random(16),random(16),0);
  LED(random(8),random(8),random(8),random(16),0 ,random(16));
  LED(random(8),random(8),random(8),0, random(16),random(16));
   //   c1=random(8);
     // c2=random(8);
      //c3=random(8);
  //LED(c1,c2,c3,15,15,15);
  }
      for(k=0; k<200; k++){
  LED(random(8),random(8),random(8),0,0,0);
  }
  
}//m


  
  
clean();


color_select=random(0,3);
if(color_select==0){
c1 = 0;
c2 = random(0,16);
c3 = random(0,16);}
if(color_select==1){
c1 = random(0,16);
c2 = 0;
c3 = random(0,16);}
if(color_select==2){
c1 = random(0,16);
c2 = random(0,16);
c3 = 0;}


color_select2=random(0,3);
if(color_select2==0){
c21 = 0;
c22 = random(0,16);
c23 = random(0,16);}
if(color_select2==1){
c21 = random(0,16);
c22 = 0;
c23 = random(0,16);}
if(color_select2==2){
c21 = random(0,16);
c22 = random(0,16);
c23 = 0;}

for(counter=0; counter<200; counter++){

LED(xo,yo,zo,0,0,0);
LED(xo+1,yo,zo,0,0,0);
LED(xo+2,yo,zo,0,0,0);
LED(xo-1,yo,zo,0,0,0);
LED(xo-2,yo,zo,0,0,0);
LED(xo,yo+1,zo,0,0,0);
LED(xo,yo-1,zo,0,0,0);
LED(xo,yo+2,zo,0,0,0);
LED(xo,yo-2,zo,0,0,0);
LED(xo,yo,zo-1,0,0,0);
LED(xo,yo,zo+1,0,0,0);
LED(xo,yo,zo-2,0,0,0);
LED(xo,yo,zo+2,0,0,0);

LED(x2o,y2o,z2o,0,0,0);
LED(x2o+1,y2o,z2o,0,0,0);
LED(x2o+2,y2o,z2o,0,0,0);
LED(x2o-1,y2o,z2o,0,0,0);
LED(x2o-2,y2o,z2o,0,0,0);
LED(x2o,y2o+1,z2o,0,0,0);
LED(x2o,y2o-1,z2o,0,0,0);
LED(x2o,y2o+2,z2o,0,0,0);
LED(x2o,y2o-2,z2o,0,0,0);
LED(x2o,y2o,z2o-1,0,0,0);
LED(x2o,y2o,z2o+1,0,0,0);
LED(x2o,y2o,z2o-2,0,0,0);
LED(x2o,y2o,z2o+2,0,0,0);

LED(xo+1,yo+1,zo,0,0,0);
LED(xo+1,yo-1,zo,0,0,0);
LED(xo-1,yo+1,zo,0,0,0);
LED(xo-1,yo-1,zo,0,0,0);
LED(xo+1,yo+1,zo+1,0,0,0);
LED(xo+1,yo-1,zo+1,0,0,0);
LED(xo-1,yo+1,zo+1,0,0,0);
LED(xo-1,yo-1,zo+1,0,0,0);
LED(xo+1,yo+1,zo-1,0,0,0);
LED(xo+1,yo-1,zo-1,0,0,0);
LED(xo-1,yo+1,zo-1,0,0,0);
LED(xo-1,yo-1,zo-1,0,0,0);

LED(x2o+1,y2o+1,z2o,0,0,0);
LED(x2o+1,y2o-1,z2o,0,0,0);
LED(x2o-1,y2o+1,z2o,0,0,0);
LED(x2o-1,y2o-1,z2o,0,0,0);
LED(x2o+1,y2o+1,z2o+1,0,0,0);
LED(x2o+1,y2o-1,z2o+1,0,0,0);
LED(x2o-1,y2o+1,z2o+1,0,0,0);
LED(x2o-1,y2o-1,z2o+1,0,0,0);
LED(x2o+1,y2o+1,z2o-1,0,0,0);
LED(x2o+1,y2o-1,z2o-1,0,0,0);
LED(x2o-1,y2o+1,z2o-1,0,0,0);
LED(x2o-1,y2o-1,z2o-1,0,0,0);

LED(x,y,z,c1,c2,c3);
LED(x,y,z-1,c1,c2,c3);
LED(x,y,z+1,c1,c2,c3);
LED(x,y,z-2,c1,c2,c3);
LED(x,y,z+2,c1,c2,c3);
LED(x+1,y,z,c1,c2,c3);
LED(x-1,y,z,c1,c2,c3);
LED(x,y+1,z,c1,c2,c3);
LED(x,y-1,z,c1,c2,c3);
LED(x+2,y,z,c1,c2,c3);
LED(x-2,y,z,c1,c2,c3);
LED(x,y+2,z,c1,c2,c3);
LED(x,y-2,z,c1,c2,c3);
LED(x+1,y+1,z,c1,c2,c3);
LED(x+1,y-1,z,c1,c2,c3);
LED(x-1,y+1,z,c1,c2,c3);
LED(x-1,y-1,z,c1,c2,c3);
LED(x+1,y+1,z+1,c1,c2,c3);
LED(x+1,y-1,z+1,c1,c2,c3);
LED(x-1,y+1,z+1,c1,c2,c3);
LED(x-1,y-1,z+1,c1,c2,c3);
LED(x+1,y+1,z-1,c1,c2,c3);
LED(x+1,y-1,z-1,c1,c2,c3);
LED(x-1,y+1,z-1,c1,c2,c3);
LED(x-1,y-1,z-1,c1,c2,c3);

LED(x2,y2,z2,c21,c22,c23);
LED(x2,y2,z2-1,c21,c22,c23);
LED(x2,y2,z2+1,c21,c22,c23);
LED(x2,y2,z2-2,c21,c22,c23);
LED(x2,y2,z2+2,c21,c22,c23);
LED(x2+1,y2,z2,c21,c22,c23);
LED(x2-1,y2,z2,c21,c22,c23);
LED(x2,y2+1,z2,c21,c22,c23);
LED(x2,y2-1,z2,c21,c22,c23);
LED(x2+2,y2,z2,c21,c22,c23);
LED(x2-2,y2,z2,c21,c22,c23);
LED(x2,y2+2,z2,c21,c22,c23);
LED(x2,y2-2,z2,c21,c22,c23);
LED(x2+1,y2+1,z2,c21,c22,c23);
LED(x2+1,y2-1,z2,c21,c22,c23);
LED(x2-1,y2+1,z2,c21,c22,c23);
LED(x2-1,y2-1,z2,c21,c22,c23);
LED(x2+1,y2+1,z2+1,c21,c22,c23);
LED(x2+1,y2-1,z2+1,c21,c22,c23);
LED(x2-1,y2+1,z2+1,c21,c22,c23);
LED(x2-1,y2-1,z2+1,c21,c22,c23);
LED(x2+1,y2+1,z2-1,c21,c22,c23);
LED(x2+1,y2-1,z2-1,c21,c22,c23);
LED(x2-1,y2+1,z2-1,c21,c22,c23);
LED(x2-1,y2-1,z2-1,c21,c22,c23);





x2o=x2;
y2o=y2;
z2o=z2;

xo=x;
yo=y;
zo=z;

delay(45);

x = x+xmult;
y= y+ymult;
z= z+zmult;

x2 = x2+x2mult;
y2= y2+y2mult;
z2= z2+z2mult;

if(x>=7){
//x=7;
xmult=random(-1,1);
}
if(y>=7){
//y=7;
ymult=random(-1,1);}
if(z>=7){
//z=7;
zmult=random(-1,1);}
if(x<=0){
//x=0;
xmult=random(0,2);}
if(y<=0){
//y=0;
ymult=random(0,2);}
if(z<=0){
//z=0;
zmult=random(0,2);
}

if(x2>=7){
//x=7;
x2mult=random(-1,1);
}
if(y2>=7){
//y=7;
y2mult=random(-1,1);}
if(z2>=7){
//z=7;
z2mult=random(-1,1);}
if(x2<=0){
//x=0;
x2mult=random(0,2);}
if(y2<=0){
//y=0;
y2mult=random(0,2);}
if(z<=0){
//z=0;
z2mult=random(0,2);
}




}//counter  counter counter counter counter



for(counter=0; counter<15; counter++){
  color_select=random(0,3);
if(color_select==0){
c1 = 0;
c2 = random(0,16);
c3 = random(0,16);}
if(color_select==1){
c1 = random(0,16);
c2 = 0;
c3 = random(0,16);}
if(color_select==2){
c1 = random(0,16);
c2 = random(0,16);
c3 = 0;}
  
  
int num1=-1, num2=-4, num3=-6, num4=-10;
for(m=0; m<20; m++){
  
num1++;
num2++;
num3++;
num4++;


for(i=3; i<5; i++){
LED(num1, i,3,0,0,0);
LED(num1, 3,i,0,0,0);
LED(num1, 4,i,0,0,0);
LED(num1, i,4,0,0,0);
}
for(i=3; i<5; i++){
LED(num1+1, i,4,c1,c2,c3);
LED(num1+1, 4,i,c1,c2,c3);
LED(num1+1, 3,i,c1,c2,c3);
LED(num1+1, i,3,c1,c2,c3);
}
for(i=2; i<6; i++){
LED(num2, i,2,0,0,0);
LED(num2, 2,i,0,0,0);
LED(num2, 5,i,0,0,0);
LED(num2, i,5,0,0,0);
}
for(i=2; i<6; i++){
LED(num2+1, i,2,c1,c2,c3);
LED(num2+1, 2,i,c1,c2,c3);
LED(num2+1, 5,i,c1,c2,c3);
LED(num2+1, i,5,c1,c2,c3);
}
for(i=1; i<7; i++){
LED(num3, i,1,0,0,0);
LED(num3, 1,i,0,0,0);
LED(num3, 6,i,0,0,0);
LED(num3, i,6,0,0,0);
}
for(i=1; i<7; i++){
LED(num3+1, i,1,c1,c2,c3);
LED(num3+1, 1,i,c1,c2,c3);
LED(num3+1, 6,i,c1,c2,c3);
LED(num3+1, i,6,c1,c2,c3);
}
for(i=0; i<8; i++){
LED(num4, i,0,0,0,0);
LED(num4, 0,i,0,0,0);
LED(num4, 7,i,0,0,0);
LED(num4, i,7,0,0,0);
}
for(i=0; i<8; i++){
LED(num4+1, i,0,c1,c2,c3);
LED(num4+1, 0,i,c1,c2,c3);
LED(num4+1, 7,i,c1,c2,c3);
LED(num4+1, i,7,c1,c2,c3);
}
//delay(1);
}//m

num1=8;
num2=11;
num3=13;
num4=17;

for(m=0; m<20; m++){
num1--;
num2--;
num3--;
num4--;
for(i=3; i<5; i++){
LED(num1, i,3,0,0,0);
LED(num1, 3,i,0,0,0);
LED(num1, 4,i,0,0,0);
LED(num1, i,4,0,0,0);
}
for(i=3; i<5; i++){
LED(num1-1, i,4,0,0,15);
LED(num1-1, 4,i,0,0,15);
LED(num1-1, 3,i,0,0,15);
LED(num1-1, i,3,0,0,15);
}
for(i=2; i<6; i++){
LED(num2, i,2,0,0,0);
LED(num2, 2,i,0,0,0);
LED(num2, 5,i,0,0,0);
LED(num2, i,5,0,0,0);
}
for(i=2; i<6; i++){
LED(num2-1, i,2,0,0,15);
LED(num2-1, 2,i,0,0,15);
LED(num2-1, 5,i,0,0,15);
LED(num2-1, i,5,0,0,15);
}
for(i=1; i<7; i++){
LED(num3, i,1,0,0,0);
LED(num3, 1,i,0,0,0);
LED(num3, 6,i,0,0,0);
LED(num3, i,6,0,0,0);
}
for(i=1; i<7; i++){
LED(num3-1, i,1,0,0,15);
LED(num3-1, 1,i,0,0,15);
LED(num3-1, 6,i,0,0,15);
LED(num3-1, i,6,0,0,15);
}
for(i=0; i<8; i++){
LED(num4, i,0,0,0,0);
LED(num4, 0,i,0,0,0);
LED(num4, 7,i,0,0,0);
LED(num4, i,7,0,0,0);
}
for(i=0; i<8; i++){
LED(num4-1, i,0,0,0,15);
LED(num4-1, 0,i,0,0,15);
LED(num4-1, 7,i,0,0,15);
LED(num4-1, i,7,0,0,15);
}
//delay(1);
}//m

}//counter

}//harlem SHake

void clean(){
  int ii, jj, kk;
    for(ii=0; ii<8; ii++)
  for(jj=0; jj<8; jj++)
  for(kk=0; kk<8; kk++)
  LED(ii,jj,kk,0,0,0);
  
}


