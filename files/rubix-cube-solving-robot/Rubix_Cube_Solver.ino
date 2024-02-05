#include <AccelStepper.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define PIN 22
#define STEPS_PER_REV 200

int s0 = 23;
int s1 = 24;
int s2 = 25;
int s3 = 26;

byte totalMoves;
int moves[100];
byte gCode[100];
int currentMove;
unsigned long scanTime;
unsigned long solveTime;


int redValues[9];
int blueValues[9];
int greenValues[9];

byte redScan = 255;
byte blueScan = 255;
byte greenScan = 255;
int soakTime=10;//7

byte sensorLocations[9]={1,3,5,9,7,10,11,13,15};
char face[9];

int redCalibration[27];
int greenCalibration[27];
int blueCalibration[27];
int yellowCalibration[27];
int orangeCalibration[27];
int whiteCalibration[27];

//Mux in "SIG" pin
int SIG_pin = 15;
int bluetoothStatusPin = 27;

int motorSpeed = 25000; //maximum steps per second (about 3rps / at 16 microsteps)10000
int motorAccel = 150000; //steps/second/second to accelerate 90000

int motor1DirPin = 13; //digital pin 2
int motor1StepPin = 12; //digital pin 3
int sleep_1 = 7; //digital pin 7

int motor2DirPin = 4; //digital pin 4
int motor2StepPin = 3; //digital pin 5
int sleep_2 = 2; //digital pin 7

//D6   -  A2 - 126
//D9   -  A1 - 140
//D10  -  A3 - 151
//D11  -  A4 - 134
//                                         
byte stepper1clock[36]={0,5,0,6,4,2,6,0,5,0,1,3,0,6,0,5,2,4,5,0,6,0,3,1,2,3,4,1,0,0,4,1,2,3,0,0};
byte stepper1anti[36]= {0,6,0,5,2,4,5,0,6,0,3,1,0,5,0,6,4,2,6,0,5,0,1,3,4,1,2,3,0,0,2,3,4,1,0,0};
byte stepper1full[36]= {0,4,0,2,6,5,3,0,1,0,6,5,0,4,0,2,6,5,3,0,1,0,6,5,3,4,1,2,0,0,3,4,1,2,0,0};

byte stepper2clock[36]={0,5,0,6,4,2,6,0,5,0,1,3,0,6,0,5,2,4,5,0,6,0,3,1,2,3,4,1,0,0,4,1,2,3,0,0};
byte stepper2anti[36]= {0,6,0,5,2,4,5,0,6,0,3,1,0,5,0,6,4,2,6,0,5,0,1,3,4,1,2,3,0,0,2,3,4,1,0,0};
byte stepper2full[36]= {0,4,0,2,6,5,3,0,1,0,6,5,0,4,0,2,6,5,3,0,1,0,6,5,3,4,1,2,0,0,3,4,1,2,0,0};

int stepper1ArmA = 11; 
int stepper1ArmB = 10;
int stepper2ArmA = 9; 
int stepper2ArmB = 6;
int scannerServo = 5;

int stepper1ArmAHome = 117; 
int stepper1ArmBHome = 134;
int stepper2ArmAHome = 123; 
int stepper2ArmBHome = 109;
int scannerServoHome = 148;

int countA;
int countB;

byte gripper1;
byte gripper2;

int wireTwistsA;
int wireTwistsB;
boolean gripperAPositionGood=true;
boolean gripperBPositionGood=true;

boolean stepperEnable = false;

int servoTune = A5;
int pressure=50; //value determining angle servos turn - 50
int servoOffset=15;//distance to move back once in home position
int stopForce = 540;//current sensor reading at max point
int slowPoint = 5;//15pressure-..........
int halfWay = 30;//Position to stop whilst solving

AccelStepper stepper1(1, motor1StepPin , motor1DirPin);//set up the accelStepper intances
AccelStepper stepper2(1, motor2StepPin, motor2DirPin);

Servo stepper1_armA;  // create servo object to control a servo 
Servo stepper1_armB;
Servo stepper2_armA;
Servo stepper2_armB;
Servo scanner_servo;

boolean stepper1Grip=true;
boolean stepper2Grip=true;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
 Serial.begin(115200);
 Serial1.begin(115200);
 
 for(int i=0;i<27;i++){
  redCalibration[i]=word(EEPROM.read((12*i)+1),EEPROM.read((12*i)+0));  
  greenCalibration[i]=word(EEPROM.read((12*i)+3),EEPROM.read((12*i)+2));  
  blueCalibration[i]=word(EEPROM.read((12*i)+5),EEPROM.read((12*i)+4));  
  whiteCalibration[i]=word(EEPROM.read((12*i)+7),EEPROM.read((12*i)+6));  
  yellowCalibration[i]=word(EEPROM.read((12*i)+9),EEPROM.read((12*i)+8));  
  orangeCalibration[i]=word(EEPROM.read((12*i)+11),EEPROM.read((12*i)+10));  
 }
 Serial.println("Colour Data recovered from EEPROM");
       
 stepper1_armA.attach(stepper1ArmA); 
 stepper1_armB.attach(stepper1ArmB); 
 stepper2_armA.attach(stepper2ArmA); 
 stepper2_armB.attach(stepper2ArmB); 
 scanner_servo.attach(scannerServo);  

servoHome(1);
servoHome(2);
 
  scanner_servo.write(25);
 delay(1000);
 scanner_servo.write(scannerServoHome );
 delay(1000);
 
 stepper1.setPinsInverted(false,false,true);
 stepper2.setPinsInverted(false,false,true);
 
 stepper1.setMaxSpeed(motorSpeed);
 stepper2.setMaxSpeed(motorSpeed);

 stepper1.setAcceleration(motorAccel);
 stepper2.setAcceleration(motorAccel);
 
 stepper1.setEnablePin(sleep_1);
 stepper1.disableOutputs();
 stepper2.setEnablePin(sleep_2);
 stepper2.disableOutputs();
 
 stepper1.setCurrentPosition(0);
 stepper2.setCurrentPosition(0);
 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
 
}

void loop(){

  // Fetch all commands that are in the buffer
  while (Serial.available()) {
    int selected_command = Serial.read();
    // Do something different based on what we got:
    switch (selected_command) {
//============================================================= Standard Commands 
      case 'a':
        grip(1,true,false);//controlling claws
        break;
      case 'b':
        grip(2,true,false);
        break;
      case 'c':
        servoHome(1);
        break;
      case 'd':
        servoHome(2);
        break;
      case 'e':
        twist(1,1,false);//turning cube
        break;
      case 'f':
        twist(2,1,false);
        break;
      case 'g':
        twist(1,-1,false);
        break;
      case 'h':
        twist(2,-1,false);
        break;
      case 'i':
        twist(1,1,true);//turning face
        break;
      case 'j':
        twist(2,1,true);
        break;
      case 'k':
        twist(1,-1,true);
        break;
      case 'l':
        twist(2,-1,true);
        break;
      case 'm':
        calibrate();
        break;
      case 's':
        if(stepperEnable==true){
         solve();
        }
        else{
         Serial.println("Stepper motors not enabled, please enable and try again"); 
        }
        break;
      case 't':
        if(bluetoothStatus()&&stepperEnable==true){
         scanner();
        }
        else{
         if(!bluetoothStatus()){
          Serial.println("CubeMate not connected, please connect and try again"); 
         }
         if(stepperEnable==false){
          Serial.println("Stepper motors not enabled, please enable and try again"); 
         }
        }
        break;
      case 'w':
        stepperSetup() ;   //adding cube    
        break;
      case 'x':
        grip(1,false,true);
        break;
      case 'y':
        grip(2,false,true);
        break;
      case 'z':
      if(!stepperEnable){//stepper enable/disable
       stepper1.enableOutputs();
       stepper2.enableOutputs();
       stepperEnable=true;
      }
      else{
       stepper1.disableOutputs();
       stepper2.disableOutputs();
       stepperEnable=false;
      }
        break;

    }
  }
}
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Solve - Controls the movements of the robot based on the solution provided
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

void solve(){
 halfWay = 30;
 solveTime = millis();
 for(int i=0;i<100;i++){
  gCode[i]=0;
 } 
 currentMove=0;
 for(int i=0;i<=totalMoves;i++){
   
 if(gripper1!=moves[2*i] && gripper2!=moves[2*i]){
  if(moves[2*i]==stepper2clock[(6*(gripper2-1))+(gripper1-1)]){gCode[currentMove]=1;gripper1=stepper2clock[(6*(gripper2-1))+(gripper1-1)];currentMove++;} //twist(2,1,false);
  else if(moves[2*i]==stepper1clock[(6*(gripper1-1))+(gripper2-1)]){gCode[currentMove]=2;gripper2=stepper1clock[(6*(gripper1-1))+(gripper2-1)];currentMove++;} //twist(1,1,false);
  else if(moves[2*i]==stepper2anti[(6*(gripper2-1))+(gripper1-1)]){gCode[currentMove]=3;gripper1=stepper2anti[(6*(gripper2-1))+(gripper1-1)];currentMove++;}//twist(2,-1,false);
  else if(moves[2*i]==stepper1anti[(6*(gripper1-1))+(gripper2-1)]){gCode[currentMove]=4;gripper2=stepper1anti[(6*(gripper1-1))+(gripper2-1)];currentMove++;}//twist(1,-1,false);
  else if(moves[2*i]==stepper2full[(6*(gripper2-1))+(gripper1-1)]){gCode[currentMove]=5;gripper1=stepper2full[(6*(gripper2-1))+(gripper1-1)];currentMove++;}//twist(2,2,false);
  else if(moves[2*i]==stepper1full[(6*(gripper1-1))+(gripper2-1)]){gCode[currentMove]=6;gripper2=stepper1full[(6*(gripper1-1))+(gripper2-1)];currentMove++;}//twist(1,2,false);
 }
 if(gripper1==moves[2*i]){gCode[currentMove]=7;currentMove++;} //twist(1,moves[(2*i)+1],true);
 if(gripper2==moves[2*i]){gCode[currentMove]=8;currentMove++;}//twist(2,moves[(2*i)+1],true);
 }
 gripper1=2;gripper2=6;
 totalMoves=currentMove;
 int faceMoves=0;
  for(int i=0;i<= totalMoves;i++){
   Serial.print(gCode[i]);
  }
  Serial.println();
 for(currentMove=0;currentMove<= totalMoves;currentMove++){
  Serial.print("Move ");Serial.print(currentMove+1);Serial.print(" out of ");Serial.println(totalMoves);
  if(gCode[currentMove]==1){twist(2,1,false);}
  else if(gCode[currentMove]==2){twist(1,1,false);}
  else if(gCode[currentMove]==3){twist(2,-1,false);}
  else if(gCode[currentMove]==4){twist(1,-1,false);}
  else if(gCode[currentMove]==5){twist(2,2,false);}
  else if(gCode[currentMove]==6){twist(1,2,false);}
  
  else if(gCode[currentMove]==7){twist(1,moves[(2*faceMoves)+1],true);faceMoves++;}
  else if(gCode[currentMove]==8){twist(2,moves[(2*faceMoves)+1],true);faceMoves++;}
 }
 
  for(int i=0;i<100;i++){
  gCode[i]=0;
 }
Serial.print((millis()-solveTime)/1000);Serial.println(" Seconds to solve   "); 
Serial.print((((millis()-solveTime)+scanTime)/1000)/60);Serial.print(" Minutes ");Serial.print((((millis()-solveTime)+scanTime)/1000)%60);Serial.println(" Seconds Overall!");
unTwist(1);
 grip(1,true,false);
 grip(2,true,false);
 stepper1.disableOutputs();
 stepper2.disableOutputs();
 stepperEnable=false;
 delay(2000);
 servoHome(1);
 servoHome(2);
}

//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Recieve - converts solution data to format understood by robot
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

void recieveSolution(){
 totalMoves=0;
 char inData[100];
 for(int i=0;i<100;i++){
  inData[i]=0;
  moves[i]=0;
 }
 while(!Serial1.available()){}
 Serial1.setTimeout(5000);
 Serial1.readBytesUntil(10, inData,100);

 if(inData[8]=='c'&&inData[9]=='u'&&inData[10]=='b'){Serial.println("invalid cube state");}
 else if(inData[8]=='n'&&inData[9]=='u'&&inData[10]=='m'){Serial.println("invalid number of colors");}
 else{
  for(int i=0;i<100;i++){
   if(inData[i]>0){totalMoves++;}
   Serial.print(inData[i]);
  }
 totalMoves/=3;
 Serial.print("  -  ");
 Serial.print(totalMoves);
 Serial.println();
  
 for(int i=0;i<totalMoves;i++){
  if(inData[i*3]=='F'){moves[i*2]=1;}
  else if(inData[i*3]=='R'){moves[i*2]=2;}
  else if(inData[i*3]=='B'){moves[i*2]=3;} 
  else if(inData[i*3]=='L'){moves[i*2]=4;}
  else if(inData[i*3]=='U'){moves[i*2]=5;}    
  else if(inData[i*3]=='D'){moves[i*2]=6;}
  
 if(inData[(i*3)+1]=='1'){moves[(i*2)+1]=1;}
  else if(inData[(i*3)+1]=='2'){moves[(i*2)+1]=2;}
  else if(inData[(i*3)+1]=='3'){moves[(i*2)+1]=-1;} 
  Serial.print(moves[i*2]);
  Serial.print(moves[(i*2)+1]);
  Serial.print(' ');    
 }
Serial.println();
}
}

//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Twist - used to turn faces of the cube
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
void twist(byte stepper,int numberOfTurns,boolean type){//true = turning face, false = turning cube

makeItSafe(stepper);
 if(type){
  grip(1,true,false);
  grip(2,true,false);
  if(stepper==1){ 
   stepper1.moveTo(stepper1.currentPosition()-numberOfTurns*STEPS_PER_REV);
   while(stepper1.distanceToGo()!=0){
    stepper1.run(); 
   }
   wireTwistsA+=numberOfTurns;
  }
  else if(stepper==2){
   stepper2.moveTo(stepper2.currentPosition()+numberOfTurns*STEPS_PER_REV);
   while(stepper2.distanceToGo()!=0){
    stepper2.run(); 
   }
   wireTwistsB+=numberOfTurns;
  }
 }
 else{//turning cube not face!!!!
   if(stepper==1){
   grip(1,true,false);
   grip(2,false,false); 
   stepper1.moveTo(stepper1.currentPosition()-numberOfTurns*STEPS_PER_REV);
   while(stepper1.distanceToGo()!=0){
    stepper1.run(); 
   }
   if(numberOfTurns==1){gripper2=stepper1clock[(6*(gripper1-1))+(gripper2-1)];}
   else if(numberOfTurns==-1){gripper2=stepper1anti[(6*(gripper1-1))+(gripper2-1)];}
   else if(numberOfTurns==2||numberOfTurns==-2){gripper2=stepper1full[(6*(gripper1-1))+(gripper2-1)];}
   wireTwistsA+=numberOfTurns;
  }
  else if(stepper==2){
   grip(2,true,false);
   grip(1,false,false); 
   stepper2.moveTo(stepper2.currentPosition()+numberOfTurns*STEPS_PER_REV);
   while(stepper2.distanceToGo()!=0){
    stepper2.run(); 
   }
   if(numberOfTurns==1){gripper1=stepper2clock[(6*(gripper2-1))+(gripper1-1)];}
   else if(numberOfTurns==-1){gripper1=stepper2anti[(6*(gripper2-1))+(gripper1-1)];}
   else if(numberOfTurns==2||numberOfTurns==-2){gripper1=stepper2full[(6*(gripper2-1))+(gripper1-1)];}
   wireTwistsB+=numberOfTurns;
  }
      Serial.print("left = ");
   Serial.print(gripper2);
   Serial.print(" Right = ");
   Serial.println(gripper1); 
 }

unTwist(6);
}

void unTwist(int limit){

 if(wireTwistsA>=limit||wireTwistsA<=-limit){
   makeItSafe(1);
   grip(2,true,false);    
   grip(1,false,false); 
   stepper1.moveTo(stepper1.currentPosition()+wireTwistsA*STEPS_PER_REV);
   while(stepper1.distanceToGo()!=0){
    stepper1.run(); 
   }
   wireTwistsA=0;
  }
  if(wireTwistsB>=limit||wireTwistsB<=-limit){
   makeItSafe(2);
   grip(1,true,false);      
   grip(2,false,false);  
   stepper2.moveTo(stepper2.currentPosition()-wireTwistsB*STEPS_PER_REV);
   while(stepper2.distanceToGo()!=0){
    stepper2.run(); 
   }
   wireTwistsB=0;
  }
  Serial.println(wireTwistsA);
Serial.println(wireTwistsB); 
}

void makeItSafe(int stepper){

  if(stepper==2){
if(abs(wireTwistsA)==1||abs(wireTwistsA)==3||abs(wireTwistsA)==5){gripperAPositionGood=false;}
if(abs(wireTwistsA)==0||abs(wireTwistsA)==2||abs(wireTwistsA)==4){gripperAPositionGood=true;}
 if(!gripperAPositionGood){
   grip(2,true,false);
   grip(1,false,false); 
 if(wireTwistsA>0){
    stepper1.moveTo(stepper1.currentPosition()+1*STEPS_PER_REV);
   while(stepper1.distanceToGo()!=0){
    stepper1.run(); 
   }
   wireTwistsA-=1;
 }
  if(wireTwistsA<0){
    stepper1.moveTo(stepper1.currentPosition()-1*STEPS_PER_REV);
   while(stepper1.distanceToGo()!=0){
    stepper1.run(); 
   }
   wireTwistsA+=1;
 }
 }
}
else{
  if(abs(wireTwistsB)==1||abs(wireTwistsB)==3||abs(wireTwistsB)==5){gripperBPositionGood=false;}
if(abs(wireTwistsB)==0||abs(wireTwistsB)==2||abs(wireTwistsB)==4){gripperBPositionGood=true;}
  if(!gripperBPositionGood){
   grip(1,true,false);
   grip(2,false,false); 
 if(wireTwistsB>0){
    stepper2.moveTo(stepper2.currentPosition()-1*STEPS_PER_REV);
   while(stepper2.distanceToGo()!=0){
    stepper2.run(); 
   }
   wireTwistsB-=1;
 }
  if(wireTwistsB<0){
    stepper2.moveTo(stepper2.currentPosition()+1*STEPS_PER_REV);
   while(stepper2.distanceToGo()!=0){
    stepper2.run(); 
   }
   wireTwistsB+=1;
 }
 }
}
}
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Grip - controls the servos responsible for gripping the cubw
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

void grip(byte stepper,boolean claw,boolean tune){  
//D6   -  A2 - 126
//D9   -  A1 - 140
//D10  -  A3 - 151
//D11  -  A4 - 134

 if(!tune){
  if(claw){
   if(stepper==1&&stepper1Grip==false){
    stepper1_armA.write(stepper1ArmAHome-servoOffset-pressure+slowPoint);
    stepper1_armB.write(stepper1ArmBHome-servoOffset-pressure+slowPoint);
    for(int i=0;i<slowPoint;i++){
     stepper1_armA.write(stepper1ArmAHome-servoOffset-pressure+slowPoint-i);
     stepper1_armB.write(stepper1ArmBHome-servoOffset-pressure+slowPoint-i);
     delay(100);
    } 
    stepper1Grip=true;
   }
   else if(stepper==2&&stepper2Grip==false){
    stepper2_armA.write(stepper2ArmAHome-servoOffset-pressure+slowPoint);
    stepper2_armB.write(stepper2ArmBHome-servoOffset-pressure+slowPoint);
    for(int i=0;i<slowPoint;i++){
     stepper2_armA.write(stepper2ArmAHome-servoOffset-pressure+slowPoint-i);
     stepper2_armB.write(stepper2ArmBHome-servoOffset-pressure+slowPoint-i);
     delay(100);
    } 
    stepper2Grip=true;
   }
  }
  else{
    if(stepper==1&&stepper1Grip==true){
    int a = stepper1ArmAHome-halfWay;
    int b = stepper1ArmBHome-halfWay;
    stepper1_armA.write(a);
    stepper1_armB.write(b);
    delay(300);
    stepper1Grip=false;
    }
   
   else if(stepper==2&&stepper2Grip==true){
    int a = stepper2ArmAHome-halfWay;
    int b = stepper2ArmBHome-halfWay;
    stepper2_armA.write(a);
    stepper2_armB.write(b);
    delay(300);
    stepper2Grip=false;
   } 
  } 
 }
 else{
  if(stepper==1){
   int servo = stepper1ArmAHome;
   while(analogRead(servoTune)>0){
    servo = map(analogRead(servoTune),0,1024,stepper1ArmAHome-servoOffset-pressure,stepper1ArmAHome-servoOffset);
    stepper1_armA.write(servo);
    servo = map(analogRead(servoTune),0,1024,stepper1ArmBHome-servoOffset-pressure,stepper1ArmBHome-servoOffset);
    stepper1_armB.write(servo);
   }
   gripper1=2;
   stepper1Grip=true;
   }
  else if(stepper==2){
   int servo = stepper2ArmAHome;
   while(analogRead(servoTune)>0){
    servo = map(analogRead(servoTune),0,1024,stepper2ArmAHome-servoOffset-pressure,stepper2ArmAHome-servoOffset);
    stepper2_armA.write(servo);
    servo = map(analogRead(servoTune),0,1024,stepper2ArmBHome-servoOffset-pressure,stepper2ArmBHome-servoOffset);
    stepper2_armB.write(servo);
   }
   gripper2=6;
   stepper2Grip=true;
  }
//     Serial.print("left = ");
//   Serial.print(gripper2);
//   Serial.print(" Right = ");
//   Serial.println(gripper1);  
 }
// Serial.println(stepper1Grip);
// Serial.println(stepper2Grip);
}

void servoHome(byte stepper){
    if(stepper==1&&stepper1Grip==true){
    int a = stepper1ArmAHome;
    int b = stepper1ArmBHome;
    stepper1_armA.write(a);
    stepper1_armB.write(b);
    delay(600);
    while(analogRead(A3)<stopForce||analogRead(A4)<stopForce){        
    if(analogRead(A4)<stopForce){
     stepper1_armA.write(a);  
     a++;
    }
    if(analogRead(A3)<stopForce){
     stepper1_armB.write(b);  
     b++;
    }
    delay(10);
    }
    stepper1_armA.write(a-servoOffset);
    stepper1_armB.write(b-servoOffset);
    stepper1Grip=false;
    }
   
   else if(stepper==2&&stepper2Grip==true){
    int a = stepper2ArmAHome;
    int b = stepper2ArmBHome;
    stepper2_armA.write(a);
    stepper2_armB.write(b);
    delay(600);
    while(analogRead(A1)<stopForce||analogRead(A2)<stopForce){        
    if(analogRead(A1)<stopForce){
     stepper2_armA.write(a);  
     a++;
    }
    if(analogRead(A2)<stopForce){
     stepper2_armB.write(b);  
     b++;
    }
    delay(10);
    }
    stepper2_armA.write(a-servoOffset);
    stepper2_armB.write(b-servoOffset);
    stepper2Grip=false;
   } 
}
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Used for fine tuning the steppers during setup
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

void stepperSetup(){
boolean done = false;
 while(!done){ 
  while (Serial.available()) {
    int selected_command = Serial.read();  
    switch (selected_command) {
      case 'a':
        stepper1.moveTo(stepper1.currentPosition()+4);
        while(stepper1.distanceToGo()!=0){
        stepper1.run();
        }
        break;
      case 'b':
        stepper1.moveTo(stepper1.currentPosition()-4);
        while(stepper1.distanceToGo()!=0){
        stepper1.run();
        }
        break;
      case 'c':
        stepper2.moveTo(stepper2.currentPosition()+4);
        while(stepper2.distanceToGo()!=0){
        stepper2.run();
        }
        break;
      case 'd':
        stepper2.moveTo(stepper2.currentPosition()-4);
        while(stepper2.distanceToGo()!=0){
        stepper2.run();
        }
        break;
      case 'e':
        done=true;
        break;
   } 
  }
 }
}
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Scanning system code
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================
//Scanner - scans the whole cube
//============================================================================================================================================================================================================================================================================================
//============================================================================================================================================================================================================================================================================================

void scanner(){
  halfWay = 20;
  char theCube[54];
   scanTime = millis();
//Top=======================================================
grip(2,false,false);
stepper1.moveTo(stepper1.currentPosition()-1*STEPS_PER_REV);
while(stepper1.distanceToGo()!=0){
 stepper1.run(); 
}
moveIn();
theCube[45]=face[7];theCube[46]=face[6];theCube[47]=face[5];
theCube[48]=face[8];theCube[49]=face[3];theCube[50]=face[4];
theCube[51]=face[0];theCube[52]=face[1];theCube[53]=face[2];

//Bottom=======================================================
stepper1.moveTo(stepper1.currentPosition()+2*STEPS_PER_REV);
while(stepper1.distanceToGo()!=0){
 stepper1.run(); 
}
moveIn();
theCube[27]=face[2];theCube[28]=face[1];theCube[29]=face[0];
theCube[30]=face[4];theCube[31]=face[3];theCube[32]=face[8];
theCube[33]=face[5];theCube[34]=face[6];theCube[35]=face[7];
//Left =======================================================
stepper1.moveTo(stepper1.currentPosition()-1*STEPS_PER_REV);
while(stepper1.distanceToGo()!=0){
 stepper1.run(); 
}
grip(2,true,false);
grip(1,false,false);
stepper2.moveTo(stepper2.currentPosition()-1*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}
moveIn();
theCube[36]=face[5];theCube[37]=face[4];theCube[38]=face[2];
theCube[39]=face[6];theCube[40]=face[3];theCube[41]=face[1];
theCube[42]=face[7];theCube[43]=face[8];theCube[44]=face[0];

//Right=======================================================
stepper2.moveTo(stepper2.currentPosition()+2*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}
moveIn();
theCube[9]=face[2];theCube[10]=face[1];theCube[11]=face[0];
theCube[12]=face[4];theCube[13]=face[3];theCube[14]=face[8];
theCube[15]=face[5];theCube[16]=face[6];theCube[17]=face[7];


//Back=======================================================
grip(1,true,false);
grip(2,false,false);
stepper2.moveTo(stepper2.currentPosition()-1*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}
grip(2,true,false);
grip(1,false,false);
stepper2.moveTo(stepper2.currentPosition()-1*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}

moveIn();
theCube[18]=face[2];theCube[19]=face[1];theCube[20]=face[0];
theCube[21]=face[4];theCube[22]=face[3];theCube[23]=face[8];
theCube[24]=face[5];theCube[25]=face[6];theCube[26]=face[7];


//Front=======================================================
stepper2.moveTo(stepper2.currentPosition()+2*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}
moveIn();
theCube[0]=face[2];theCube[1]=face[1];theCube[2]=face[0];
theCube[3]=face[4];theCube[4]=face[3];theCube[5]=face[8];
theCube[6]=face[5];theCube[7]=face[6];theCube[8]=face[7];

//Get Solution 
gripper2=6;
gripper1=4;
Serial.print("left = ");
Serial.print(gripper2);
Serial.print(" Right = ");
Serial.println(gripper1); 

Serial1.flush();
for(int i=0;i<54;i++){
 Serial.print(theCube[i]);
 Serial1.print(theCube[i]);
if(i!=54){Serial.print(" ");Serial1.print(" ");} 
}
Serial.print("\n");
Serial1.print("\n");
Serial1.flush();
//Home=======================================================
grip(1,true,false);
grip(2,false,false);
stepper2.moveTo(stepper2.currentPosition()-1*STEPS_PER_REV);
while(stepper2.distanceToGo()!=0){
 stepper2.run(); 
}
grip(2,true,false);

if(bluetoothStatus()){
 recieveSolution();
}
else{
 Serial.println("CubeMate not connected, please connect and try again"); 
}
 stepper1.disableOutputs();
 stepper2.disableOutputs();
 stepperEnable=false;
 Serial.print((millis()-scanTime)/1000);Serial.println(" Seconds to scan   "); 
 scanTime=millis()-scanTime;
}

void moveIn(){
 scanner_servo.write(90);  
delay(300);
scanner_servo.write(25);
delay(350);
detect();
scanner_servo.write(scannerServoHome ); 
delay(200);
}

boolean bluetoothStatus(){
 byte timer=0;
 while(digitalRead(bluetoothStatusPin)==1&&timer<100){
  timer++;
  delay(2);
 }
 if(timer==100){
  return true;
 }
 else{
  return false;
 }
}

void detect(){
 scan();
for(int i=0;i<9;i++){
 int differences[18];
 differences[0]=abs(redValues[i]-redCalibration[3*i]);
 differences[1]=abs(greenValues[i]-redCalibration[(3*i)+1]);
 differences[2]=abs(blueValues[i]-redCalibration[(3*i)+2]);
 
 differences[3]=abs(redValues[i]-greenCalibration[3*i]);
 differences[4]=abs(greenValues[i]-greenCalibration[(3*i)+1]);
 differences[5]=abs(blueValues[i]-greenCalibration[(3*i)+2]);
 
 differences[6]=abs(redValues[i]-blueCalibration[3*i]);
 differences[7]=abs(greenValues[i]-blueCalibration[(3*i)+1]);
 differences[8]=abs(blueValues[i]-blueCalibration[(3*i)+2]);
 
 differences[9]=abs(redValues[i]-whiteCalibration[3*i]);
 differences[10]=abs(greenValues[i]-whiteCalibration[(3*i)+1]);
 differences[11]=abs(blueValues[i]-whiteCalibration[(3*i)+2]);
 
 differences[12]=abs(redValues[i]-yellowCalibration[3*i]);
 differences[13]=abs(greenValues[i]-yellowCalibration[(3*i)+1]);
 differences[14]=abs(blueValues[i]-yellowCalibration[(3*i)+2]);
 
 differences[15]=abs(redValues[i]-orangeCalibration[3*i]);
 differences[16]=abs(greenValues[i]-orangeCalibration[(3*i)+1]);
 differences[17]=abs(blueValues[i]-orangeCalibration[(3*i)+2]);
 int averages[6];
 for(int a=0;a<6;a++){
 averages[a]=(differences[3*a]+differences[(3*a)+1]+differences[(3*a)+2])/3  ;
 }
 int smallest=averages[0];
 byte actualSmallest=0;
 for(int a=0;a<6;a++){
  if(averages[a]<smallest){
    smallest=averages[a]; 
    actualSmallest=a;
 }
 }
if(actualSmallest==0){face[i]='R';}
else if(actualSmallest==1){face[i]='G';}
else if(actualSmallest==2){face[i]='B';}
else if(actualSmallest==3){face[i]='W';}
else if(actualSmallest==4){face[i]='Y';}
else if(actualSmallest==5){face[i]='O';}
else{face[i]=' ';}
}
Serial.println("=======");
Serial.print(face[2]);
Serial.print("  ");
Serial.print(face[1]);
Serial.print("  ");
Serial.print(face[0]);
Serial.println();
Serial.println();

Serial.print(face[4]);
Serial.print("  ");
Serial.print(face[3]);
Serial.print("  ");
Serial.print(face[8]);
Serial.println();
Serial.println();

Serial.print(face[5]);
Serial.print("  ");
Serial.print(face[6]);
Serial.print("  ");
Serial.print(face[7]);
Serial.println();
Serial.println();
}

void calibrate(){
 int count[6]={0,0,0,0,0,0};
  while (count[0]==0||count[1]==0||count[2]==0||count[3]==0||count[4]==0||count[5]==0) {
    int selected_command = Serial.read();
    // Do something different based on what we got:
    switch (selected_command) {
      case 'r':
        scan();
        for(int i=0;i<9;i++){
         redCalibration[3*i]=redValues[i]; 
         redCalibration[(3*i)+1]=greenValues[i]; 
         redCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("Red scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(redCalibration[i]);Serial.print(",");}
        Serial.println();
        count[0]=1;
        break;
        
      case 'g':
        scan();
        for(int i=0;i<9;i++){
         greenCalibration[3*i]=redValues[i]; 
         greenCalibration[(3*i)+1]=greenValues[i]; 
         greenCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("Green scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(greenCalibration[i]);Serial.print(",");}
        Serial.println();
        count[1]=1;
        break;    
        
        case 'b':
        scan();
        for(int i=0;i<9;i++){
         blueCalibration[3*i]=redValues[i]; 
         blueCalibration[(3*i)+1]=greenValues[i]; 
         blueCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("Blue scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(blueCalibration[i]);Serial.print(",");}
        Serial.println();
        count[2]=1;
        break;    
              
        case 'w':
        scan();
        for(int i=0;i<9;i++){
         whiteCalibration[3*i]=redValues[i]; 
         whiteCalibration[(3*i)+1]=greenValues[i]; 
         whiteCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("White scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(whiteCalibration[i]);Serial.print(",");}
        Serial.println();
        count[3]=1;
        break;    
        
        case 'y':
        scan();
        for(int i=0;i<9;i++){
         yellowCalibration[3*i]=redValues[i]; 
         yellowCalibration[(3*i)+1]=greenValues[i]; 
         yellowCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("Yellow scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(yellowCalibration[i]);Serial.print(",");}
        Serial.println();
        count[4]=1;
        break;    
       
        case 'o':
        scan();
        for(int i=0;i<9;i++){
         orangeCalibration[3*i]=redValues[i]; 
         orangeCalibration[(3*i)+1]=greenValues[i]; 
         orangeCalibration[(3*i)+2]=blueValues[i]; 
        }
        Serial.println("Orange scan complete");
        for(int i=0;i<27;i++){if(i%3==0){Serial.print(",,");}Serial.print(orangeCalibration[i]);Serial.print(",");}
        Serial.println();
        count[5]=1;
        break;    
       }
 } 
Serial.println("Calibration Complete!");
for(int i=0;i<27;i++){
EEPROM.write(12*i,lowByte(redCalibration[i]));  
EEPROM.write((12*i)+1,highByte(redCalibration[i]));  

EEPROM.write((12*i)+2,lowByte(greenCalibration[i]));  
EEPROM.write((12*i)+3,highByte(greenCalibration[i]));  

EEPROM.write((12*i)+4,lowByte(blueCalibration[i]));  
EEPROM.write((12*i)+5,highByte(blueCalibration[i]));  

EEPROM.write((12*i)+6,lowByte(whiteCalibration[i]));  
EEPROM.write((12*i)+7,highByte(whiteCalibration[i]));  

EEPROM.write((12*i)+8,lowByte(yellowCalibration[i]));  
EEPROM.write((12*i)+9,highByte(yellowCalibration[i]));  

EEPROM.write((12*i)+10,lowByte(orangeCalibration[i]));  
EEPROM.write((12*i)+11,highByte(orangeCalibration[i]));  
}
Serial.println("Data Written to EEPROM!");
}

void scan(){

  for(int i=0;i<9;i++){
   strip.setPixelColor(i-1, 0,0,0);
   strip.setPixelColor(i, redScan,0,0);
   strip.show();  
   delay(soakTime);
   redValues[i]=readMux(sensorLocations[i]);
  }
  strip.setPixelColor(8, 0,0,0);
  for(int i=0;i<9;i++){
   strip.setPixelColor(i-1, 0,0,0);
   strip.setPixelColor(i, 0,greenScan,0);
   strip.show();  
   delay(soakTime);
   greenValues[i]=readMux(sensorLocations[i]);
  }  
  strip.setPixelColor(8, 0,0,0);
  for(int i=0;i<9;i++){
   strip.setPixelColor(i-1, 0,0,0);
   strip.setPixelColor(i, 0,0,blueScan);
   strip.show();  
   delay(soakTime);
   blueValues[i]=readMux(sensorLocations[i]);
  }
  strip.setPixelColor(8, 0,0,0);  
  strip.show(); 
}

void debug(){
  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  for(int i = 0; i < 16; i ++){
    Serial.print("   C");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(readMux(i));
  }
Serial.println();
delay(500);  
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}
