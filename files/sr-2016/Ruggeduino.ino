//To do:
//PID adjustments, braking?
//Alignment

#include <Arduino.h>
#include <PID_v1.h>
#include <AccelStepper.h>
#include <Servo.h>

#define SERIAL_BAUD 115200
#define FW_VER 0

#define GRAB_DISTANCE 500

#define WHEEL_SIZE 150

#define DIRECTION1_A 25
#define DIRECTION2_A 27
#define PWM1_A 2
#define PWM2_A 3

#define DIRECTION1_B 29
#define DIRECTION2_B 31
#define PWM1_B 4
#define PWM2_B 5
Servo rightArm;
Servo leftArm;

int value=0;

double SetpointA,SetpointB,MMS_A,MMS_B,OutputA,OutputB;//5,5,0
//double aggKp=20, aggKi=15, aggKd=0;
double aggKp=25, aggKi=20, aggKd=0;

PID motorA_PID(&MMS_A, &OutputA, &SetpointA, aggKp, aggKi, aggKd, DIRECT);
PID motorB_PID(&MMS_B, &OutputB, &SetpointB, aggKp, aggKi, aggKd, DIRECT);

AccelStepper lift(AccelStepper::DRIVER, A0, A1);
AccelStepper turntable(AccelStepper::DRIVER, A6, A7);
AccelStepper lidar(AccelStepper::DRIVER, 26, 28);
AccelStepper arms(AccelStepper::DRIVER, 46, 48);

const float Pi = 3.14159;

volatile unsigned long counterA = 0;//Counts rotations
volatile unsigned long counterB = 0;

unsigned long time;
unsigned long lastCounterA;
unsigned long lastCounterB;
 int data=0;
 
void setup() {
  Serial3.begin(115200); 
  Serial3.setTimeout(2000);
  Serial2.begin(SERIAL_BAUD);
  Serial.begin(SERIAL_BAUD);

 leftArm.attach(6);
 rightArm.attach(11);
 leftArm.write(85);//+=release 85   open = 105  close = 55
 rightArm.write(65);//-=relase 65   open = 45   close = 95
  motorA_PID.SetMode(AUTOMATIC);
  motorA_PID.SetOutputLimits(0,255);
  motorB_PID.SetMode(AUTOMATIC);
  motorB_PID.SetOutputLimits(0,255);
  
  lift.setEnablePin(38);//300 for spinning, 25 for drop,   585 for pickup
  lift.setPinsInverted(1,0,1);
  lift.setMaxSpeed(400.0);
  lift.setAcceleration(100.0);
  lift.disableOutputs();
  
  turntable.setEnablePin(A2);//800 steps per 90 degrees, positive = clockwise
  turntable.setPinsInverted(1,0,1);
  turntable.setMaxSpeed(300);//7000
  turntable.setAcceleration(5000.0);
  turntable.disableOutputs();

  arms.setEnablePin(A8);//800 steps per 90 degrees, positive = away from robot
  arms.setPinsInverted(0,0,0,0,1);
  arms.setMaxSpeed(12000.0);
  arms.setAcceleration(3000.0);
  arms.disableOutputs();

  attachInterrupt(2, countA, CHANGE);
  attachInterrupt(3, countA, CHANGE);
  attachInterrupt(4, countB, CHANGE);
  attachInterrupt(5, countB, CHANGE);
  pinMode(12,OUTPUT);
  pinMode(DIRECTION1_A,OUTPUT);
  pinMode(DIRECTION2_A,OUTPUT);
  pinMode(DIRECTION1_B,OUTPUT);
  pinMode(DIRECTION2_B,OUTPUT);

cli();//stop interrupts
//set timer1 interrupt at 1Hz
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR2A =50 ;//156 = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR2B |= (1 << WGM22);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS20);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

TCCR3B = TCCR3B & 0b11111000 | 0x02;
TCCR4B = TCCR4B & 0b11111000 | 0x02;
  sei();
  }

void loop() {
//Serial.println(getDistance());
//delay(1000000);
//spinTurntable(-1,1);
//spin(0,1);
//drop();
  //spinTurntable(-1,1)  ;
//Serial.println(align());
//spin(1,0);
//motorControl(1,6,1,6,3000,0);
//delay(500000);
turntable.enableOutputs();
    turntable.move(1000000000);
     while( turntable.distanceToGo() != 0){
     turntable.run();
     }
 while (Serial2.available()) {
  int selected_command = Serial2.read();
   switch (selected_command) {
     case 'a':
     byte dataIna[11];
     Serial2.readBytesUntil(10, dataIna, 2);
     value = dataIna[0];
     if(value==255){value=-1;}
     if(spin(value,dataIna[1])){
     Serial2.print("Done");}
     else{Serial2.print("Fail");}
     break;

     case 'b':
     byte dataInb[11];
     Serial2.readBytesUntil(10, dataInb, 2);
     value = dataInb[0];
     if(value==255){value=-1;}
     if(spinTurntable(value,dataInb[1])){
     Serial2.print("Done");}
     else{Serial2.print("Fail");}
     break;

     case 'c':
     if(drop()){
     Serial2.print("Done");}
     else{Serial2.print("Fail");}
     break;

     case 'd':
     leftArm.write(105);//+=release 85   open = 105  close = 55
     rightArm.write(45);//-=relase 65   open = 45   close = 95
     lift.enableOutputs();
     lift.moveTo(585);
     while( lift.distanceToGo() != 0){
     lift.run();
     }
     Serial2.print("Done");
     break;

     case 'e':
     lift.enableOutputs();
     lift.moveTo(0);
     while( lift.distanceToGo() != 0){
     lift.run();
     }
     lift.disableOutputs();
     Serial2.print("Done");
     break;
     
    case 'm':
     byte dataIn[11];
     word distanceIn,angleIn;
     Serial2.readBytesUntil(10, dataIn, 8);
     distanceIn=word(dataIn[5],dataIn[4]);
     angleIn=word(dataIn[7],dataIn[6]);
     if(motorControl(dataIn[2],dataIn[3],dataIn[0],dataIn[1],distanceIn,angleIn)){
     Serial2.print("Done");}
     else{Serial2.print("Fail");}
     break;

    case 'p':
     if(align()){
     Serial2.print("Done");}
     else{Serial2.print("Fail");}
     break;
     
     case 'l':
     data=getDistance();
     Serial2.write(data&0xFF);
     Serial2.write((data >> 8)&0xFF);
     break;
     
    case 'v':
     Serial2.print("SRcustom:");
     Serial2.print(FW_VER);
     Serial2.print("\n");
     break;
    default: 
     break;
  }
 }
}


//========================================================================================================
boolean align(){
  
  unsigned long dataIn;
  dataIn=getDistance();
  Serial.println(dataIn);
  if(dataIn==0){
  motorControl(0,10,0,10,50,0);
  dataIn=getDistance();
    Serial.println(dataIn);
  }
  if(dataIn==0){
   return 0;
  }

  if(dataIn>=GRAB_DISTANCE||dataIn==0){
   Serial.println("not in sight");
     motorControl(0,5,0,0,0,45);//Backs off with just right
    dataIn=getDistance();

    if(dataIn>=GRAB_DISTANCE||dataIn==0){
      Serial.println("not in sight");
     motorControl(1,5,0,0,0,45);//Backs off with just right  
     motorControl(0,0,0,5,0,45);//Backs on left too
    dataIn=getDistance();
    if(dataIn>=GRAB_DISTANCE||dataIn==0){
      Serial.println("not in sight");
     motorControl(0,0,1,5,0,45);//Backs on left too
     return 0;
    }
    else{
    //realiggn for right
    Serial.println("on the Right");
    sortPosition(dataIn);
    }
    }
    else{
    //realiggn for left
    Serial.println("on the Left");
    sortPosition(dataIn);
    }
    
  }
  else{
  //realign middle
  sortPosition( dataIn);  
  }
return 1;
//GRAB_DISTANCE
  
}

void sortPosition(unsigned long startDist){
  unsigned long dataIn=0;  
double angle=0;
Serial.println("       ");
Serial.println(startDist);
Serial.println(dataIn);
while(dataIn<startDist+500){
motorControl(0,5,0,0,0,15);//Backs off with just right
dataIn=getDistance();
Serial.println(dataIn);
}
angle=atan(125.0/(startDist-110))*(360.0/6.28);
Serial.println(angle);
motorControl(1,5,0,0,0,int(angle));
dataIn=getDistance();
lift.enableOutputs();
lift.moveTo(200);
while( lift.distanceToGo() != 0){
lift.run();
}
motorControlNOPID(1,5,1,5,dataIn+70,0);
delay(500);
motorControlNOPID(0,5,0,5,100,0);

}
bool motorControlNOPID(byte motorA_direction,int motorA_speed,byte motorB_direction,int motorB_speed,int distance,int degree){

counterA=0;
counterB=0;
  OutputA=0;
  OutputB=0;
if(distance==0&&degree!=0&&motorA_direction!=motorB_direction&&motorA_speed==motorB_speed){
distance=340.0*Pi*((degree*1.0)/360.0);
}
else if(distance==0&&degree!=0&&motorA_speed==0&&motorB_speed!=0||distance==0&&degree!=0&&motorB_speed==0&&motorA_speed!=0){
distance=340.0*Pi*((degree*1.0)/360.0);
}
if(distance==0){return 0;}
else if(motorA_direction>1||motorA_direction<0){return 0;}
else if(motorB_direction>1||motorB_direction<0){return 0;}
else if(motorA_speed==0&&motorB_speed==0){return 0;}
else{
  int enable_A=0;
  int enable_B=0;
  int compensationA=0;
  int compensationB=0;

if(motorA_direction==1){enable_A=PWM1_A;analogWrite(PWM2_A,0);if(motorA_speed>0){compensationA=5;}}else{enable_A=PWM2_A;analogWrite(PWM1_A,0);compensationA=0;}//13
if(motorB_direction==1){enable_B=PWM1_B;analogWrite(PWM2_B,0);compensationB=0;}else{enable_B=PWM2_B;analogWrite(PWM1_B,0);if(motorB_speed>0){compensationB=1;}}//7

digitalWrite(DIRECTION1_A,!motorA_direction);//
digitalWrite(DIRECTION2_A,motorA_direction);//!
digitalWrite(DIRECTION1_B,!motorB_direction);
digitalWrite(DIRECTION2_B,motorB_direction);//!

SetpointA=0;
SetpointB=0;

while((counterA/1800.0)*124.0*Pi<(distance/4)*3&&(counterB/1800.0)*124.0*Pi<(distance/4)*3){
motorA_PID.Compute();
motorB_PID.Compute();

analogWrite(enable_B,50+compensationB);
analogWrite(enable_A,50+compensationA);

}

analogWrite(PWM1_A,0);
analogWrite(PWM2_A,0);
analogWrite(PWM1_B,0);
analogWrite(PWM2_B,0);
digitalWrite(DIRECTION1_A,motorA_direction);
digitalWrite(DIRECTION2_A,!motorA_direction);
digitalWrite(DIRECTION1_B,motorB_direction);
digitalWrite(DIRECTION2_B,!motorB_direction);
if(motorA_speed>0){if(motorA_direction==1){analogWrite(PWM2_A,100);}else{analogWrite(PWM1_A,100);}}
if(motorB_speed>0){if(motorB_direction==1){analogWrite(PWM2_B,100);}else{analogWrite(PWM1_B,100);}}
delay(5);

analogWrite(PWM1_A,0);
analogWrite(PWM2_A,0);
analogWrite(PWM1_B,0);
analogWrite(PWM2_B,0);
digitalWrite(DIRECTION1_A,0);
digitalWrite(DIRECTION2_A,0);
digitalWrite(DIRECTION1_B,0);
digitalWrite(DIRECTION2_B,0);

return 1;
}
}

//=========================================================================================================
bool motorControl(byte motorA_direction,int motorA_speed,byte motorB_direction,int motorB_speed,int distance,int degree){
motorA_PID.SetOutputLimits(0, 255);
motorB_PID.SetOutputLimits(0, 255);
counterA=0;
counterB=0;
  OutputA=0;
  OutputB=0;
if(distance==0&&degree!=0&&motorA_direction!=motorB_direction&&motorA_speed==motorB_speed){
distance=340.0*Pi*((degree*1.0)/360.0);
}
else if(distance==0&&degree!=0&&motorA_speed==0&&motorB_speed!=0||distance==0&&degree!=0&&motorB_speed==0&&motorA_speed!=0){
distance=340.0*Pi*((degree*1.0)/360.0);
}
if(distance==0){return 0;}
else if(motorA_direction>1||motorA_direction<0){return 0;}
else if(motorB_direction>1||motorB_direction<0){return 0;}
else if(motorA_speed==0&&motorB_speed==0){return 0;}
else{
  int enable_A=0;
  int enable_B=0;
  int compensationA=0;
  int compensationB=0;

if(motorA_direction==1){enable_A=PWM1_A;analogWrite(PWM2_A,0);if(motorA_speed>0){compensationA=22;}}else{enable_A=PWM2_A;analogWrite(PWM1_A,0);compensationA=0;}//13
if(motorB_direction==1){enable_B=PWM1_B;analogWrite(PWM2_B,0);compensationB=0;}else{enable_B=PWM2_B;analogWrite(PWM1_B,0);if(motorB_speed>0){compensationB=3;}}//7

digitalWrite(DIRECTION1_A,!motorA_direction);//
digitalWrite(DIRECTION2_A,motorA_direction);//!
digitalWrite(DIRECTION1_B,!motorB_direction);
digitalWrite(DIRECTION2_B,motorB_direction);//!

SetpointA=0;
SetpointB=0;
unsigned long timer=millis()+100;

if(motorA_speed==0){motorA_PID.SetOutputLimits(0, 0.1);}
if(motorB_speed==0){motorB_PID.SetOutputLimits(0, 0.1);}
while((counterA/1800.0)*124.0*Pi<distance/2&&(counterB/1800.0)*124.0*Pi<distance/2&&SetpointA<= motorA_speed&&SetpointB<= motorB_speed){
motorA_PID.Compute();
motorB_PID.Compute();


analogWrite(enable_B,OutputB+compensationB);
analogWrite(enable_A,OutputA+compensationA);
if(timer<millis()){
timer=millis()+100;
if(SetpointA<motorA_speed){  SetpointA++;}
if(SetpointB<motorB_speed){ SetpointB++;}
}
}

while((counterA/1800.0)*124.0*Pi<distance&&(counterB/1800.0)*124.0*Pi<distance){//(distance/4)*3
motorA_PID.Compute();
motorB_PID.Compute();

analogWrite(enable_B,OutputB+compensationB);
analogWrite(enable_A,OutputA+compensationA);

}
/*
while((counterA/1800.0)*124.0*Pi<distance&&(counterB/1800.0)*124.0*Pi<distance){
motorA_PID.Compute();
motorB_PID.Compute();

analogWrite(enable_B,OutputB+compensationB);
analogWrite(enable_A,OutputA+compensationA);
if(timer<millis()){
timer=millis()+20;
if(SetpointA>1&&SetpointA!=0){  SetpointA--;}
if(SetpointB>1&&SetpointB!=0){ SetpointB--;}
}
}
*/
analogWrite(PWM1_A,0);
analogWrite(PWM2_A,0);
analogWrite(PWM1_B,0);
analogWrite(PWM2_B,0);
digitalWrite(DIRECTION1_A,motorA_direction);
digitalWrite(DIRECTION2_A,!motorA_direction);
digitalWrite(DIRECTION1_B,motorB_direction);
digitalWrite(DIRECTION2_B,!motorB_direction);
if(motorA_speed>0){if(motorA_direction==1){analogWrite(PWM2_A,255);}else{analogWrite(PWM1_A,255);}}
if(motorB_speed>0){if(motorB_direction==1){analogWrite(PWM2_B,255);}else{analogWrite(PWM1_B,255);}}
delay(10);

analogWrite(PWM1_A,0);
analogWrite(PWM2_A,0);
analogWrite(PWM1_B,0);
analogWrite(PWM2_B,0);
digitalWrite(DIRECTION1_A,0);
digitalWrite(DIRECTION2_A,0);
digitalWrite(DIRECTION1_B,0);
digitalWrite(DIRECTION2_B,0);

return 1;
}
}
//========================================================================================================
bool spinTurntable(int turns,int pickup){//1 away, -1 towards, 2 180, 1 for pickup puts on back
lift.enableOutputs();

lift.moveTo(585);
while( lift.distanceToGo() != 0){
lift.run();
if(lift.distanceToGo() <520){
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95
  }
}
leftArm.write(75);//+=release 85   open = 105  close = 55
rightArm.write(75);//-=relase 65   open = 45   close = 95
delay(1000);
leftArm.write(55);//+=release 85   open = 105  close = 55
rightArm.write(95);//-=relase 65   open = 45   close = 95  
arms.enableOutputs();
int done=0;

turntable.enableOutputs();
lift.moveTo(25);
while( lift.distanceToGo() != 0){
if(abs(lift.distanceToGo())<450&&done==0){arms.move(1129);done=1;}
lift.run();
arms.run();
}
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95  
arms.disableOutputs();  

lift.moveTo(300);
while( lift.distanceToGo() != 0){
lift.run();
}
turntable.move(800);
while(  turntable.distanceToGo() != 0){
turntable.run();
}
delay(200);

lift.moveTo(10);
while( lift.distanceToGo() != 0){
lift.run();
}
leftArm.write(55);//+=release 85   open = 105  close = 55
rightArm.write(95);//-=relase 65   open = 45   close = 95  
arms.enableOutputs();
turntable.disableOutputs();

lift.moveTo(300);
while( lift.distanceToGo() != 0){
lift.run();
}
if(turns==1&&pickup==0){turns=-329;}
else if(turns==1&&pickup==1){turns=800;}
else if(turns==-1&&pickup==0){turns=1271;}
else if(turns==-1&&pickup==1){turns=-800;}

arms.move(turns);
while(  arms.distanceToGo() != 0){
arms.run();
}

if(pickup){
lift.moveTo(25);
while( lift.distanceToGo() != 0){
lift.run();
} 
leftArm.write(85);//+=release 85   open = 105  close = 55
rightArm.write(65);//-=relase 65   open = 45   close = 95
lift.moveTo(0);
while( lift.distanceToGo() != 0){
lift.run();
} 
}
else{
lift.moveTo(560);
while(  lift.distanceToGo() != 0){
lift.run();
}
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95

lift.moveTo(0);
while( lift.distanceToGo() != 0){
lift.run();
if(abs(lift.distanceToGo()) <130){
leftArm.write(85);//+=release 85   open = 105  close = 55
rightArm.write(65);//-=relase 65   open = 45   close = 95  
  }
}
}
turntable.disableOutputs();
lift.disableOutputs();
arms.disableOutputs();
return 1;
}
//=================================================================================
bool spin(int turns,int pickup){//1 away, -1 towards, 2 180, 1 for pickup puts on back
lift.enableOutputs();

lift.moveTo(585);
while( lift.distanceToGo() != 0){
lift.run();
if(lift.distanceToGo() <520){
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95
  }
}
leftArm.write(75);//+=release 85   open = 105  close = 55
rightArm.write(75);//-=relase 65   open = 45   close = 95
delay(1000);
leftArm.write(55);//+=release 85   open = 105  close = 55
rightArm.write(95);//-=relase 65   open = 45   close = 95  
arms.enableOutputs();

lift.moveTo(400);
while( lift.distanceToGo() != 0){
lift.run();
}
if(turns==1&&pickup==0){turns=800;}
else if(turns==1&&pickup==1){turns=-1271;}
else if(turns==-1&&pickup==0){turns=-800;}
else if(turns==-1&&pickup==1){turns=329;}
else if(turns==2&&pickup==0){turns=1600;}
else if(turns==2&&pickup==1){turns=-471;}
else if(turns==0&&pickup==1){turns=1129;}

arms.move(turns);
while(  arms.distanceToGo() != 0){
arms.run();
}

if(pickup){
lift.moveTo(25);
while( lift.distanceToGo() != 0){
lift.run();
} 
leftArm.write(85);//+=release 85   open = 105  close = 55
rightArm.write(65);//-=relase 65   open = 45   close = 95
lift.moveTo(0);
while( lift.distanceToGo() != 0){
lift.run();
} 
}
else{
lift.moveTo(560);
while(  lift.distanceToGo() != 0){
lift.run();
}
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95

lift.moveTo(0);
while( lift.distanceToGo() != 0){
lift.run();
if(abs(lift.distanceToGo()) <130){
leftArm.write(85);//+=release 85   open = 105  close = 55
rightArm.write(65);//-=relase 65   open = 45   close = 95  
  }
}
}
turntable.disableOutputs();
lift.disableOutputs();
arms.disableOutputs();
return 1;
}
//=================================================================================

bool drop(){
  lift.enableOutputs();
lift.moveTo(10);
while( lift.distanceToGo() != 0){
lift.run();
}
leftArm.write(55);//+=release 85   open = 105  close = 55
rightArm.write(95);//-=relase 65   open = 45   close = 95  
arms.enableOutputs();

int done=0;
lift.moveTo(585);
while(  lift.distanceToGo() != 0){
if(abs(lift.distanceToGo())<500&&done==0){arms.move(-1129);done=1;}
lift.run();
arms.run();
}
leftArm.write(105);//+=release 85   open = 105  close = 55
rightArm.write(45);//-=relase 65   open = 45   close = 95  
  arms.disableOutputs(); 

lift.moveTo(0);
while( lift.distanceToGo() != 0){
lift.run();
if(abs(lift.distanceToGo()) <130){
leftArm.write(85);//+=release 85   open = 105  close = 55
rightArm.write(65);//-=relase 65   open = 45   close = 95  
  }
}
  turntable.disableOutputs();
lift.disableOutputs();
arms.disableOutputs();
return 1;
}
//=============================================================================


void countA()
{
 counterA++;
}

void countB()
{
 counterB++;
}

void read_count(){
 Serial3.println(counterA);
 Serial3.println(counterB);
 Serial3.println(MMS_A);
 Serial3.println(MMS_B);
}



int getDistance(){
char inData[21];
int distance=0;
while(Serial3.available()){Serial3.read();}
Serial3.println("*00004#");//Single
while(Serial3.find("*")==0){}
if(Serial3.find("*")==1){
Serial3.readBytesUntil('#', inData,21);  
for(int i=0;i<21;i++){
// Serial.print(inData[i]); 
 // Serial.print("  "); 
}
//Serial.print("  -  "); 
distance=(inData[13]-48) + ((inData[12]-48)*10) + ((inData[11]-48)*100)+ ((inData[10]-48)*1000) + ((inData[9]-48)*10000) + ((inData[8]-48)*100000)+ ((inData[7]-48)*1000000)+ ((inData[6]-48)*10000000); 
if(inData[0]=='p'&&inData[1]=='E'&&inData[2]=='r'&&inData[3]=='r'&&inData[4]=='o'&&inData[5]=='r'){distance=0;}
if(distance<0||distance>8000){distance=0;}
if(inData[3]=='2'&&inData[4]=='6'){distance=0;}
return(distance); 
}
else{
return(0);  
}
}

ISR(TIMER2_COMPA_vect){   
MMS_A=((counterA-lastCounterA));
lastCounterA=counterA;

MMS_B=((counterB-lastCounterB));
lastCounterB=counterB;
//Serial.print(MMS_A);Serial.print("            ");Serial.print(OutputA);Serial.print("            ");Serial.print(MMS_B);Serial.print("            ");Serial.println(OutputB);
}



