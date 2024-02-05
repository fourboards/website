#include <SPI.h>// SPI Library used to clock data out to the shift registers
#include <CapacitiveSensor.h>

int latchPin = 2;
int clockPin = 13;
int dataPin = 11;

int fets[10] = {14,15,16,17,18,6,5,1,3,4};
boolean LEDs[200];

int rowCount=0;
byte alphabets[][5] = {
{0, 0, 0, 0, 0},
{31, 36, 68, 36, 31},
{127, 73, 73, 73, 54},
{62, 65, 65, 65, 34},
{127, 65, 65, 34, 28},
{127, 73, 73, 65, 65},
{127, 72, 72, 72, 64},
{62, 65, 65, 69, 38},
{127, 8, 8, 8, 127},
{0, 65, 127, 65, 0},
{2, 1, 1, 1, 126},
{127, 8, 20, 34, 65},
{127, 1, 1, 1, 1},
{127, 32, 16, 32, 127},
{127, 32, 16, 8, 127},
{62, 65, 65, 65, 62},
{127, 72, 72, 72, 48},
{62, 65, 69, 66, 61},
{127, 72, 76, 74, 49},
{50, 73, 73, 73, 38},
{64, 64, 127, 64, 64},
{126, 1, 1, 1, 126},
{124, 2, 1, 2, 124},
{126, 1, 6, 1, 126},
{99, 20, 8, 20, 99},
{96, 16, 15, 16, 96},
{67, 69, 73, 81, 97},
};

CapacitiveSensor   cs_4_2 = CapacitiveSensor(7,8);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired


void setup() 
{
  randomSeed(analogRead(0));
  SPI.setBitOrder(MSBFIRST);//Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
   
  pinMode(latchPin, OUTPUT);//Latch
  pinMode(dataPin, OUTPUT);//MOSI DATA
  pinMode(clockPin, OUTPUT);//SPI Clock
  
  
  for(int i=0;i<10;i++){
  pinMode(fets[i], OUTPUT);
  digitalWrite(fets[i], LOW);
  }
  SPI.begin();//start up the SPI library

  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 400;// = (16*10^6) / (1*1024) - 1 (must be <65536)249
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  displayClear();
}
 
void loop() {
  long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
if(total1>=100){
wipeLeft();
  wipeRight();

displayString("THANKYOU MR GODDARD",19,400,1);
  wipeDown();
displayString("GOOD LUCK AT YOUR NEW SCHOOL",28,400,1);
wipeDown();
//wipeRight();
//wipeUp();
//wipeLeft();
while(true){
  randomDots();
}

}

 }
 
void randomDots(){
  int xRandom=random(0,20);
  int yRandom=random(0,10);
 setPixel(xRandom,yRandom,!readPixel(xRandom,yRandom));  
 delay(1);
} 
 
void displayString(char string[100],int length,int scrollSpeed,int yHeight){
int xCoordinate=20;
while(xCoordinate+(length*6)>=0){
displayClear();
for(int g=0;g<length;g++){
displayChar(string[g],xCoordinate+(6*g),yHeight);  
}  
delay(500-scrollSpeed);  
xCoordinate--;
}
}
 
void displayChar(int letter,int x,int y){
  if(letter==32){letter=0;}else{
letter-=64;  }
for(int i=0;i<5;i++){
for(int j=0;j<8;j++){
 setPixel(i+x,y+7-j,bitRead(alphabets[letter][i],7-j)); 
} 
}
}

void wipeRight(){
{for(int j=0;j<20;j++){
  for(int i=0;i<10;i++){
setPixel(j,i,true);
delay(5);  
}
 }  
}
{for(int j=0;j<20;j++){
  for(int i=0;i<10;i++){
setPixel(j,i,false);
delay(5);  
}
 }  
}
}

void wipeLeft(){
{for(int j=20;j>=0;j--){
  for(int i=0;i<10;i++){
setPixel(j,i,true);
delay(5);  
}
 }  
}
{for(int j=20;j>=0;j--){
  for(int i=0;i<10;i++){
setPixel(j,i,false);
delay(5);  
}
 }  
}
}

void wipeDown(){
{for(int j=9;j>=0;j--){
  for(int i=0;i<20;i++){
setPixel(i,j,true);
delay(5);  
}
 }  
}
{for(int j=9;j>=0;j--){
  for(int i=0;i<20;i++){
setPixel(i,j,false);
delay(5);  
}
 }  
}
}

void wipeUp(){
{for(int j=0;j<=9;j++){
  for(int i=0;i<20;i++){
setPixel(i,j,true);
delay(5);  
}
 }  
}
{for(int j=0;j<=9;j++){
  for(int i=0;i<20;i++){
setPixel(i,j,false);
delay(5);  
}
 }  
}
}

void displayClear(){
for(int i=0;i<200;i++){
LEDs[i]=0;
}  
}

void setPixel(byte x,byte y, boolean state){
if(x>=0&&x<=19&&y>=0&&y<=9){
switch(y){
case 0:y=8;break;
case 1:y=7;break;
case 2:y=6;break;
case 3:y=5;break;
case 4:y=4;break;
case 5:y=3;break;
case 6:y=2;break;
case 7:y=1;break;
case 8:y=0;break;
case 9:y=9;break;
}

LEDs[(20*y)+x]=state;
}
}

boolean readPixel(byte x,byte y){
if(x>=0&&x<=19&&y>=0&&y<=9){
switch(y){
case 0:y=8;break;
case 1:y=7;break;
case 2:y=6;break;
case 3:y=5;break;
case 4:y=4;break;
case 5:y=3;break;
case 6:y=2;break;
case 7:y=1;break;
case 8:y=0;break;
case 9:y=9;break;
}

return(LEDs[(20*y)+x]);
}

}

ISR(TIMER1_COMPA_vect){
switch(rowCount){
case 0:PORTD &= ~(1<<4);break;
case 1:PORTC &= ~(1<<0);break;
case 2:PORTC &= ~(1<<1);break;
case 3:PORTC &= ~(1<<2);break;
case 4:PORTC &= ~(1<<3);break;
case 5:PORTC &= ~(1<<4);break;
case 6:PORTD &= ~(1<<6);break;
case 7:PORTD &= ~(1<<5);break;
case 8:PORTD &= ~(1<<1);break;
case 9:PORTD &= ~(1<<3);break;
}

byte register0=0;
byte register1=0;
byte register2=0;

bitWrite(register0,5,LEDs[(20*rowCount)+0]);
bitWrite(register0,4,LEDs[(20*rowCount)+1]);
bitWrite(register0,3,LEDs[(20*rowCount)+2]);
bitWrite(register0,2,LEDs[(20*rowCount)+3]);
bitWrite(register0,1,LEDs[(20*rowCount)+4]);
bitWrite(register1,7,LEDs[(20*rowCount)+5]);
bitWrite(register1,6,LEDs[(20*rowCount)+6]);
bitWrite(register1,5,LEDs[(20*rowCount)+7]);
bitWrite(register1,4,LEDs[(20*rowCount)+8]);
bitWrite(register1,3,LEDs[(20*rowCount)+9]);
bitWrite(register1,2,LEDs[(20*rowCount)+10]);
bitWrite(register1,1,LEDs[(20*rowCount)+11]);
bitWrite(register1,0,LEDs[(20*rowCount)+12]);
bitWrite(register2,7,LEDs[(20*rowCount)+13]);
bitWrite(register2,6,LEDs[(20*rowCount)+14]);
bitWrite(register2,5,LEDs[(20*rowCount)+15]);
bitWrite(register2,4,LEDs[(20*rowCount)+16]);
bitWrite(register2,3,LEDs[(20*rowCount)+17]);
bitWrite(register2,2,LEDs[(20*rowCount)+18]);
bitWrite(register2,1,LEDs[(20*rowCount)+19]);


PORTD |= 1<<latchPin;//Latch pin HIGH
SPI.transfer(register0);
SPI.transfer(register1);
SPI.transfer(register2);
PORTD &= ~(1<<latchPin);//Latch pin LOW


switch(rowCount){
case 0:PORTC |= 1<<0;break;
case 1:PORTC |= 1<<1;break;
case 2:PORTC |= 1<<2;break;
case 3:PORTC |= 1<<3;break;
case 4:PORTC |= 1<<4;break;
case 5:PORTD |= 1<<6;break;
case 6:PORTD |= 1<<5;break;
case 7:PORTD |= 1<<1;break;
case 8:PORTD |= 1<<3;break;
case 9:PORTD |= 1<<4;break;
}
rowCount++;
if(rowCount>=10){rowCount=0;}


}

