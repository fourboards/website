#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#define DS1307_I2C_ADDRESS 0x68





//QR code and display stufff
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 3;
int numberOfVerticalDisplays = 3;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

byte Data[26]={B00100000,B10000000};

unsigned long placedData[21];

unsigned long maskVariable[21];

int scores[8];
int mask;
char alphaNumeric[45]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','$','%','*','+','-','.','/',':'};

int    formatSrings[9]={13663,12392,16177,14854,9396,8579,11994,11245,0};
// Mask Number (EC - Q) |  0  |  1  |  2  |  3  | 4  | 5  |  6  |  7  |

//================================================================================================================
//Setup
//================================================================================================================

void setup() {


Wire.begin();  
delay(1000);
  Serial.begin(9600);


  matrix.setIntensity(6);
  matrix.setPosition(0, 0, 0); 
  matrix.setPosition(1, 1, 0); 
  matrix.setPosition(2, 2, 0);
  matrix.setPosition(3, 0, 1); 
  matrix.setPosition(4, 1, 1); 
  matrix.setPosition(5, 2, 1); 
  matrix.setPosition(6, 0, 2); 
  matrix.setPosition(7, 1, 2); 
  matrix.setPosition(8, 2, 2); 
  matrix.setRotation(0, 1);    
  matrix.setRotation(1, 1);    
  matrix.setRotation(2, 1);   
  matrix.setRotation(3, 1);
  matrix.setRotation(4, 1);   
  matrix.setRotation(5, 1);
  matrix.setRotation(6, 1);  
  matrix.setRotation(7,1);
  matrix.setRotation(8, 1);   

}

//================================================================================================================
//Loop
//================================================================================================================

void loop() {
  
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

    int Year=year;
    int Month=month;
    int Day=dayOfMonth;
    
    int Hour=hour;
    int Minute=minute;
    int Second = second;
  char info [17];      
 String test;
if(Hour<10){test +="0";}
test +=Hour;
test +=":";
if(Minute<10){test +="0";}
test +=Minute;
test +=":";
if(Second<10){test +="0";}
test +=Second;
test +=" - ";
if(Day<10){test +="0";}
test +=Day;
test +="/";
if(Month<10){test +="0";}
test +=Month;
//test +="/";
//test +=Year;
test.toCharArray(info,17) ;

generateQRcode(info);
data();
masking(mask);
format(mask);  
alignment();

writeToMatrix();

getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
while(second==Second){
 getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year); 
}

mask++;
if(mask==8){mask=0;}
}

//================================================================================================================
//Generate the message and error correction codewords
//================================================================================================================

void generateQRcode(char text[16]){

for(int a=0;a<26;a++){//reset data storage array
 Data[a]=0 ;
}
Data[0]=B00100000;//add mode indicator 
Data[1]=B10000000;//string length

int alphanumericData[8];//temporary storage of encoded data

for(int i=0;i<8;i++){//calculating encoded data
  
for(int j=0;j<45;j++){
if (text[2*i]==alphaNumeric[j]){
alphanumericData[i]=45*j;  
}
} 

for(int j=0;j<45;j++){
if (text[(2*i)+1]==alphaNumeric[j]){
alphanumericData[i] += j;  
}
}

}

//Move the bits into the right locations
for(int i=0;i<3;i++){bitWrite(Data[1],i,bitRead(alphanumericData[0],i+8));}//1
for(int i=0;i<8;i++){bitWrite(Data[2],i,bitRead(alphanumericData[0],i));}//1
for(int i=0;i<8;i++){bitWrite(Data[3],i,bitRead(alphanumericData[1],i+3));}//2
for(int i=0;i<5;i++){bitWrite(Data[4],i,bitRead(alphanumericData[2],i+6));}//3
for(int i=0;i<3;i++){bitWrite(Data[4],i+5,bitRead(alphanumericData[1],i));}//2
for(int i=0;i<2;i++){bitWrite(Data[5],i,bitRead(alphanumericData[3],i+9));}//4
for(int i=0;i<6;i++){bitWrite(Data[5],i+2,bitRead(alphanumericData[2],i));}//3
for(int i=0;i<8;i++){bitWrite(Data[6],i,bitRead(alphanumericData[3],i+1));}//4
for(int i=0;i<7;i++){bitWrite(Data[7],i,bitRead(alphanumericData[4],i+4));}//5
bitWrite(Data[7],7,bitRead(alphanumericData[3],0));//4
for(int i=0;i<4;i++){bitWrite(Data[8],i,bitRead(alphanumericData[5],i+7));}//6
for(int i=0;i<4;i++){bitWrite(Data[8],i+4,bitRead(alphanumericData[4],i));}//5
bitWrite(Data[9],0,bitRead(alphanumericData[6],10));//7
for(int i=0;i<7;i++){bitWrite(Data[9],i+1,bitRead(alphanumericData[5],i));}//6
for(int i=0;i<8;i++){bitWrite(Data[10],i,bitRead(alphanumericData[6],i+2));}//7
for(int i=0;i<6;i++){bitWrite(Data[11],i,bitRead(alphanumericData[7],i+5));}//8
for(int i=0;i<2;i++){bitWrite(Data[11],i+6,bitRead(alphanumericData[6],i));}//7
for(int i=0;i<5;i++){bitWrite(Data[12],i+3,bitRead(alphanumericData[7],i));}//8

/*
for(int i=0;i<13;i++){
  Serial.println(alphanumericData[i]);
}

Serial.println("=============="); 
for(int i=0;i<13;i++){
Serial.println(Data[i]);  
}
Serial.println("=============="); 
*/

int generator[15]={0,74,152,176,100,86,100,106,104,130,218,206,140,78};//generator polynomial

int XOR[15]={0,74,152,176,100,86,100,106,104,130,218,206,140,78,0};//two variables used for division
int leadTerm[15]={0,74,152,176,100,86,100,106,104,130,218,206,140,78,0};

//byte message[15]={Data[0],Data[1],Data[2],Data[3],Data[4],Data[5],Data[6],Data[7],
//                  Data[8],Data[9],Data[10],Data[11],Data[12],0,0};//holds data codewords 
/*
for(int i=0;i<13;i++){
Serial.print(message[i]);
Serial.print(",");
}
Serial.println("");

byte message[14]={136,25,236,95,71,165,2,5,123,234,24,253,62};
137,25,236,95,71,165,2,5,123,234,24,253,62
*/
//alphaa notation conversion arrays
//byte intToA[257]={1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1,0};
byte aToInt[257]={0,0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175,0};

//used to store divisor each time
byte divisor;

divisor=aToInt[Data[0]];//convert int to alpha notation
for(int i=0;i<14;i++){//step 1

XOR[i]+=divisor;//perform multiplication
if(XOR[i]>255){XOR[i]=XOR[i]%255;}//perform modulo if >255
if(XOR[i]==255){XOR[i]=0;}//255=0
//Serial.println(XOR[i]);
for(int a=0;a<257;a++){if(XOR[i]== aToInt[a]){XOR[i]=a;break;  }}//convert back to integar
if(XOR[i]==0){XOR[i]=1;}//0=1
//Serial.println(message[i]);
//Serial.println(XOR[i]);
XOR[i]=XOR[i]^Data[i];//perform XOR
//Serial.println(XOR[i]);
//Serial.println("=====================");
}
//Serial.println("==========================================");//remove lead 0 term bit
//remove lead 0 term bit
for(int i=0;i<14;i++){
XOR[i]=XOR[i+1];
//Serial.println(XOR[i]);
//Serial.println("=====================");
}

for(int b=0;b<12;b++){//reset lead term to generator bits
  for(int i=0;i<15;i++){
 leadTerm[i]=generator[i];
}
divisor=aToInt[XOR[0]];//convert int to alpha notation
for(int i=0;i<14;i++){//step 2
leadTerm[i]+=divisor;//perform multiplication
if(leadTerm[i]>255){leadTerm[i]=leadTerm[i]%255;}//perform modulo if >255
if(leadTerm[i]==255){leadTerm[i]=0;}//255=0
//Serial.println(leadTerm[i]);
for(int a=0;a<257;a++){if(leadTerm[i]== aToInt[a]){leadTerm[i]=a;break;  }}//convert back to integar
if(leadTerm[i]==0){leadTerm[i]=1;}//0=1
//Serial.println(leadTerm[i]);
//Serial.println(XOR[i]);
leadTerm[i]=leadTerm[i]^XOR[i];//perform XOR
//Serial.println(leadTerm[i]);
//Serial.println("=====================");
}
//Serial.println("==========================================");
//remove lead 0 term bit
for(int i=0;i<14;i++){
leadTerm[i]=leadTerm[i+1];
//Serial.println(leadTerm[i]);
XOR[i]=leadTerm[i];
//Serial.println("=====================");
}
}
//byte testing[13]={192,  31,  102,  176,  109,  191,  9,  140,  51,  160,  140,  165,  75};
for(int i=0;i<13;i++){
//Serial.println(leadTerm[i]);
//Serial.println("=====================");
 Data[i+13] =leadTerm[i];
//Data[i+13] =testing[i];
}

}

//================================================================================================================
//Mask the Data and Erroc Correction code words
//================================================================================================================

void masking(int maskValue){
  
for(int x=0;x<21;x++){
maskVariable[x]= placedData[x];
}

for(int x=0;x<21;x++){
for(int y=0;y<21;y++){

switch(maskValue){
  case 0:if((x+y)%2==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 1:if(y%2==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 2:if(x%3==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 3:if((x+y)%3==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 4:if(( 21*(y / 2) + 21*(x / 3) ) % 2 == 0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 5:if(((y * x) % 2) + ((y * x) % 3) ==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 6:if(( ((y * x) % 2) + ((y * x) % 3) ) % 2 ==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

case 7:if(( ((y + x) % 2) + ((y * x)% 3) ) % 2 ==0){if(bitRead(maskVariable[x],y)==0){bitSet(maskVariable[x],y);}else{bitClear(maskVariable[x],y);}}break;

}
}}
for(int x=0;x<21;x++){
placedData[x]=maskVariable[x];
}
}

//================================================================================================================
//Write unsigned long to matrix
//================================================================================================================

void writeToMatrix(){
for(int i=0;i<21;i++){
for(int j=0;j<21;j++){  
if(bitRead(placedData[i],j)==1){bitClear(placedData[i],j);}
else{bitSet(placedData[i],j);}
}
} 
 
  
  matrix.fillScreen(LOW);               //Clear Screen
matrix.drawLine(23, 0, 0,0,1 );  
matrix.drawLine(23, 0, 23,23,1 );

matrix.drawLine(23, 22, 0,22,1 );  
matrix.drawLine(23,23, 0,23,1 ); 

matrix.drawLine(0, 0, 0,23,1 );  
matrix.drawLine(1, 0, 1,23,1 ); 

for(int i=0;i<21;i++){
for(int j=0;j<21;j++){  
matrix.drawPixel(22-i, j+1, bitRead(placedData[i],j) );
}
}
matrix.write(); // Send bitmap to display 
}

//================================================================================================================
//Write alignment data to unsigned long
//================================================================================================================

void alignment(){
  
unsigned long alignmentDataSet[21]={2080895,1065025,1523805,1523805,1523805,1065025,2086271,0,8256,0,64,0,64,0,127,65,93,93,93,65,127};

for(int i=0;i<21;i++){
for(int j=0;j<21;j++){ 
if(bitRead(alignmentDataSet[i],j)==1){bitSet(placedData[i],j);}  
}
}
alignmentDataSet[0]=8320;
alignmentDataSet[1]=1024190;
alignmentDataSet[2]=565410;
alignmentDataSet[3]=565410;
alignmentDataSet[4]=565410;
alignmentDataSet[5]=1024190;
alignmentDataSet[6]=10880;
alignmentDataSet[7]=2089215;
alignmentDataSet[8]=0;
alignmentDataSet[9]=64;
alignmentDataSet[10]=0;
alignmentDataSet[11]=64;
alignmentDataSet[12]=0;
alignmentDataSet[13]=255;
alignmentDataSet[14]=128;
alignmentDataSet[15]=190;
alignmentDataSet[16]=162;
alignmentDataSet[17]=162;
alignmentDataSet[18]=162;
alignmentDataSet[19]=190;
alignmentDataSet[20]=128;

for(int i=0;i<21;i++){
for(int j=0;j<21;j++){ 
if(bitRead(alignmentDataSet[i],j)==1){bitClear(placedData[i],j);}  
}
}
}

//================================================================================================================
//Write format info to unsigned long
//================================================================================================================

void format(int format){

for(int i=0;i<6;i++){bitWrite(placedData[8],i,bitRead( formatSrings[format],i));}  
bitWrite(placedData[8],7,bitRead( formatSrings[format],6));
bitWrite(placedData[8],8,bitRead( formatSrings[format],7));
bitWrite(placedData[7],8,bitRead( formatSrings[format],8));
for(int i=0;i<6;i++){bitWrite(placedData[5-i],8,bitRead( formatSrings[format],i+9));}
for(int i=0;i<8;i++){bitWrite(placedData[20-i],8,bitRead( formatSrings[format],i));}
for(int i=0;i<7;i++){bitWrite(placedData[8],i+14,bitRead( formatSrings[format],i+8));}

}

//================================================================================================================
//Write data to unsigned long
//================================================================================================================

void data(){
/*  
  for(int i=0;i<26;i++){
Serial.println(Data[i],BIN);
}
*/ 
unsigned long temporaryStorage[9];

//right section
for(int a=0;a<5;a++){
temporaryStorage[a] = Data[(a*3)];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[(a*3)+1];  
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[(a*3)+2];
}
int x=20;
int y=20;

int storage = 0;

for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y--;
}

storage = 1;
y=9;
x=18;
for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y++;
}

storage = 2;
y=20;
x=16;
for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y--;
}

storage = 3;
y=9;
x=14;
for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y++;
}

storage = 4;
y=20;
x=12;
for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y--;
}

//middle section
int a=5;
int b=15;
temporaryStorage[a] = Data[b];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+1];  
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+2];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+3];

storage = 5;
y=8;
x=12;
for(int i=0;i<2;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],31-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],31-((i*2)+1)));
y--;
}
y=5;
x=12;
for(int i=0;i<6;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],27-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],27-((i*2)+1)));
y--;
}
y=0;
x=10;
for(int i=0;i<6;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],15-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],15-((i*2)+1)));
y++;
}
y=7;
x=10;
for(int i=0;i<2;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],3-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],3-((i*2)+1)));
y++;
}

 a=6;
 b=19;
temporaryStorage[a] = Data[b];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+1];  
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+2];

storage = 6;
y=9;
x=10;
for(int i=0;i<12;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y++;
}
//left section
 a=7;
b=22;
temporaryStorage[a] = Data[b];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+1];  
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+2];
temporaryStorage[a] = temporaryStorage[a] * 256 + Data[b+3];

storage = 7;
y=12;
x=8;
for(int i=0;i<4;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],31-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],31-((i*2)+1)));
y--;
}

y=9;
x=5;
for(int i=0;i<4;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],23-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],23-((i*2)+1)));
y++;
}

y=12;
x=3;
for(int i=0;i<4;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],15-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],15-((i*2)+1)));
y--;
}

y=9;
x=1;
for(int i=0;i<4;i++){
bitWrite(placedData[x],y,bitRead( temporaryStorage[storage],7-(i*2)));
bitWrite(placedData[x-1],y,bitRead( temporaryStorage[storage],7-((i*2)+1)));
y++;
}

}

byte decToBcd(byte val)
{
return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return ( (val/16*10) + (val%16) );
}
// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers
void setDateDs1307(byte second, // 0-59
byte minute, // 0-59
byte hour, // 1-23
byte dayOfWeek, // 1-7
byte dayOfMonth, // 1-28/29/30/31
byte month, // 1-12
byte year) // 0-99
{
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(0);
Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
Wire.write(decToBcd(minute));
Wire.write(decToBcd(hour));
Wire.write(decToBcd(dayOfWeek));
Wire.write(decToBcd(dayOfMonth));
Wire.write(decToBcd(month));
Wire.write(decToBcd(year));
Wire.write(0x10); // sends 0x10 (hex) 00010000 (binary) to control register - turns on square wave
Wire.endTransmission();
}
// Gets the date and time from the ds1307
void getDateDs1307(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
// Reset the register pointer
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(0);
Wire.endTransmission();
Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
// A few of these need masks because certain bits are control bits
*second = bcdToDec(Wire.read() & 0x7f);
*minute = bcdToDec(Wire.read());
*hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
*dayOfWeek = bcdToDec(Wire.read());
*dayOfMonth = bcdToDec(Wire.read());
*month = bcdToDec(Wire.read());
*year = bcdToDec(Wire.read());
}

