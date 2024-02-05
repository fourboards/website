#include "Wire.h"
#include <avr/wdt.h>
#define DS3231_I2C_ADDRESS 0x68

#define AA 2
#define AB 4
#define AC 5
#define AD 3

#define BA 6
#define BB 7
#define BC 9
#define BD 8

//#define A 10
//#define B 11
//#define C 12

byte digits[6];
int tube;
byte convert[10]={1,0,9,8,7,6,5,4,3,2};

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
DDRD = DDRD | B11111100;
DDRB = DDRB | B00111111;
PORTD = B00000000;
PORTB = B00000000;

cli();
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 300;//234 = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set  CS12 bits for 256 prescaler
  TCCR1B |= (1 << CS12); 
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  watchdogSetup();
  // DS3231 seconds, minutes, hours, day, date, month, year
 //setDS3231time(0,24,22,4,26,11,14);
}

void watchdogSetup(void)
{
cli();  // disable all interrupts
wdt_reset(); // reset the WDT timer
/*
 WDTCSR configuration:
 WDIE = 1: Interrupt Enable
 WDE = 1 :Reset Enable
 WDP3 = 0 :For 2000ms Time-out
 WDP2 = 1 :For 2000ms Time-out
 WDP1 = 1 :For 2000ms Time-out
 WDP0 = 1 :For 2000ms Time-out
*/
// Enter Watchdog Configuration mode:
WDTCSR |= (1<<WDCE) | (1<<WDE);
// Set Watchdog settings:
 WDTCSR = (0<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (0<<WDP0);
sei();
}

void loop() {
   byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
digits[0]=hour/10;
digits[1]=hour%10;
digits[2]=minute/10;
digits[3]=minute%10;
digits[4]=second/10;
digits[5]=second%10;
wdt_reset(); // reset the WDT timer
displayTime();
//Serial.print(digits[0]);Serial.print(digits[1]);Serial.print(":");Serial.print(digits[2]);Serial.print(digits[3]);Serial.print(":");Serial.print(digits[4]);Serial.println(digits[5]);
//Serial.println(millis());


}

ISR(TIMER1_COMPA_vect){
byte B,D;
switch(tube){
case 0:
B=4+(bitRead(convert[digits[0]],2)*2)+bitRead(convert[digits[0]],3);
D=(bitRead(convert[digits[5]],0)*4)+(bitRead(convert[digits[5]],1)*16)+(bitRead(convert[digits[5]],2)*32)+(bitRead(convert[digits[5]],3)*8)+(bitRead(convert[digits[0]],0)*64)+(bitRead(convert[digits[0]],1)*128);
PORTB = B;
PORTD = D;
break;
case 1:
B=8+(bitRead(convert[digits[1]],2)*2)+bitRead(convert[digits[1]],3);
D=(bitRead(convert[digits[4]],0)*4)+(bitRead(convert[digits[4]],1)*16)+(bitRead(convert[digits[4]],2)*32)+(bitRead(convert[digits[4]],3)*8)+(bitRead(convert[digits[1]],0)*64)+(bitRead(convert[digits[1]],1)*128);
PORTB = B;
PORTD = D;
break;
case 2:
B=16+(bitRead(convert[digits[2]],2)*2)+bitRead(convert[digits[2]],3);
D=(bitRead(convert[digits[3]],0)*4)+(bitRead(convert[digits[3]],1)*16)+(bitRead(convert[digits[3]],2)*32)+(bitRead(convert[digits[3]],3)*8)+(bitRead(convert[digits[2]],0)*64)+(bitRead(convert[digits[2]],1)*128);
PORTB = B;
PORTD = D;
break;
  
}
tube++;
if(tube>=3){tube=0;}
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}

