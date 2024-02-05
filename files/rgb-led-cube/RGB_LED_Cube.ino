//To Delay():
//  start=milliSeconds;      
//  while(milliSeconds-start<1000){    }       // wait for a second

  #include "Tlc5940.h"

byte Red1[16];
byte Red2[16];
byte Red3[16];
byte Red4[16];

byte Blue1[16];
byte Blue2[16];
byte Blue3[16];
byte Blue4[16];

byte Green1[16];
byte Green2[16];
byte Green3[16];
byte Green4[16];

int Data[192];

int layer=1;

unsigned long layerTimer;

byte layers[4]={4,2,5,6};

byte address[48]={19,17,30,  29,16,31,  8,7,9,    14,10,15,  // x,1
                  24,23,20,  21,22,18,  6,46,47,  11,12,13,  // x,2
                  36,45,26,  28,27,25,  41,39,40, 3,4,5,     // x,3
                  33,32,34,  37,35,38,  44,42,43, 0,2,1};
                  
  //R(1,1),G(1,1),B(1,1),R(2,1),G(2,1),B(2,1)...
  
  int colours[64]={0,23, 46, 69, 92, 115, 138, 161, 184, 207, 230, 
253, 276, 299, 322, 345, 368, 391, 414, 437, 460, 
483, 506, 529, 552, 575, 598, 621, 644, 667, 690, 
713, 736, 759, 782, 805, 828, 851, 874, 897, 920, 
943, 966, 989, 1012, 1035, 1058, 1081, 1104, 1127, 1150, 
1173, 1196, 1219, 1242,1265, 1288, 1311, 1334, 1357, 1380, 
1403, 1426, 1449};

byte positions[64]={31,49,61,44,12,58,55,51,40,4,35,42,33,7,50,45,48,18,3,37,21,2,39,23,62,19,27,22,56,14,9,60,1,24,41,25,32,10,16,0,47,13,54,46,63,6,57,52,5,11,53,28,38,59,17,15,8,20,30,34,43,26,36,29};

int foldColour=0;


unsigned long milliSeconds;
unsigned long start;
unsigned long startTime;

void setup() {
  randomSeed(analogRead(0));
  Tlc.init();
  Serial.begin(9600);
  pinMode(2, OUTPUT);//2
  pinMode(4, OUTPUT);//1
  pinMode(5, OUTPUT);//3
  pinMode(6, OUTPUT);//4
  
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  
    cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 200;// = (16*10^6) / (2000*64) - 1 (must be <256)//85
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 256 prescaler
  TCCR0B |= (1 << CS02) ;   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  sei();//start interrupts
  
}

void loop() {
resetCube();   
    startTime=milliSeconds;
  while(milliSeconds-startTime<20000){fades();   }     
resetCube(); 
    startTime=milliSeconds;
  while(milliSeconds-startTime<20000){cubeFillingRain();   }    
 resetCube();  
      startTime=milliSeconds;
  while(milliSeconds-startTime<20000){individualFades();   }    
  resetCube(); 
    startTime=milliSeconds;
  while(milliSeconds-startTime<20000){cubeRain();   }     
resetCube();   
    startTime=milliSeconds;
  while(milliSeconds-startTime<20000){foldingCube();   }      

}


//==============================================================================================================
//Animations
//==============================================================================================================

void fades(){
  
byte XX=0,YY=0,ZZ=0;

for(int i=0;i<64;i++){
 colours[i]++;
if(colours[i]>=1529){colours[i]=0;} 

setLed(XX,YY,ZZ,colours[i]);
XX++;
if(XX==4){XX=0;YY++;}
if(YY==4){YY=0;ZZ++;}
}
updateCube();
delayMicroseconds(500);
   
}

void individualFades(){
  
byte XX=0,YY=0,ZZ=0;

for(int i=0;i<64;i++){
 colours[positions[i]]++;
if(colours[positions[i]]>=1529){colours[positions[i]]=0;} 

setLed(XX,YY,ZZ,colours[positions[i]]);
XX++;
if(XX==4){XX=0;YY++;}
if(YY==4){YY=0;ZZ++;}
}
updateCube();
delayMicroseconds(500);
   
}


void cubeFillingRain(){

byte randomX=random(0,4);
byte randomY=random(0,4);
int randomColour=random(0,1530);

setLed(randomX,randomY, 3,randomColour);
updateCube();
Delay(50);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY, 2,randomColour);
updateCube();
Delay(50);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY, 1,randomColour);
updateCube();
Delay(50);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY, 0,randomColour);
updateCube();
Delay(50);
}

void cubeRain(){

byte randomX=random(0,4);
byte randomY=random(0,4);
int randomColour=random(0,1530);

setLed(randomX,randomY, 3,randomColour);
updateCube();
Delay(75);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY, 3,1600);
setLed(randomX,randomY, 2,randomColour);
updateCube();
Delay(75);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY, 2,1600);
setLed(randomX,randomY, 1,randomColour);
updateCube();
Delay(75);
randomColour+=200;
if(randomColour>=1530){randomColour=0;}
setLed(randomX,randomY,1,1600);
setLed(randomX,randomY, 0,randomColour);
updateCube();
Delay(75);
}

void foldingCube(){

  int timer=50;
  int change=150;
  resetCube();
    foldColour+=change;
if(foldColour>1529){foldColour=0;}
for(int i=0;i<4;i++){
setLed(i,0,0,foldColour);
setLed(i,0,1,foldColour);
setLed(i,0,2,foldColour);
setLed(i,0,3,foldColour);
}  
updateCube();
Delay(timer);


for(int i=0;i<4;i++){setLed(i,1,3,foldColour);setLed(i,0,3,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,2,3,foldColour);setLed(i,1,3,1600);setLed(i,1,2,foldColour);setLed(i,0,2,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,3,3,foldColour);setLed(i,2,3,1600);setLed(i,2,2,foldColour);setLed(i,1,2,1600);setLed(i,1,1,foldColour);setLed(i,0,1,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,3,2,foldColour);setLed(i,3,3,1600);setLed(i,2,1,foldColour);setLed(i,2,2,1600);setLed(i,1,0,foldColour);setLed(i,1,1,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,3,1,foldColour);setLed(i,3,2,1600);setLed(i,2,0,foldColour);setLed(i,2,1,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,3,0,foldColour);setLed(i,3,1,1600);}  updateCube();Delay(timer);

for(int i=0;i<4;i++){setLed(0,i,1,foldColour);setLed(0,i,0,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,i,2,foldColour);setLed(0,i,1,1600);setLed(1,i,1,foldColour);setLed(1,i,0,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,i,3,foldColour);setLed(0,i,2,1600);setLed(1,i,2,foldColour);setLed(1,i,1,1600);setLed(2,i,1,foldColour);setLed(2,i,0,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(1,i,3,foldColour);setLed(0,i,3,1600);setLed(2,i,2,foldColour);setLed(1,i,2,1600);setLed(3,i,1,foldColour);setLed(2,i,1,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(2,i,3,foldColour);setLed(1,i,3,1600);setLed(3,i,2,foldColour);setLed(2,i,2,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,i,3,foldColour);setLed(2,i,3,1600);}  updateCube();Delay(timer);

for(int i=0;i<4;i++){setLed(2,0,i,foldColour);setLed(3,0,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(1,0,i,foldColour);setLed(2,0,i,1600);setLed(2,1,i,foldColour);setLed(3,1,i,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,0,i,foldColour);setLed(1,0,i,1600);setLed(1,1,i,foldColour);setLed(2,1,i,1600);setLed(2,2,i,foldColour);setLed(3,2,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,1,i,foldColour);setLed(0,0,i,1600);setLed(1,2,i,foldColour);setLed(1,1,i,1600);setLed(2,3,i,foldColour);setLed(2,2,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,2,i,foldColour);setLed(0,1,i,1600);setLed(1,3,i,foldColour);setLed(1,2,i,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,3,i,foldColour);setLed(0,2,i,1600);}  updateCube();Delay(timer);

for(int i=0;i<4;i++){setLed(i,2,0,foldColour);setLed(i,3,0,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,1,0,foldColour);setLed(i,2,0,1600);setLed(i,2,1,foldColour);setLed(i,3,1,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,0,0,foldColour);setLed(i,1,0,1600);setLed(i,1,1,foldColour);setLed(i,2,1,1600);setLed(i,2,2,foldColour);setLed(i,3,2,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,0,1,foldColour);setLed(i,0,0,1600);setLed(i,1,2,foldColour);setLed(i,1,1,1600);setLed(i,2,3,foldColour);setLed(i,2,2,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,0,2,foldColour);setLed(i,0,1,1600);setLed(i,1,3,foldColour);setLed(i,1,2,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(i,0,3,foldColour);setLed(i,0,2,1600);}  updateCube();Delay(timer);

for(int i=0;i<4;i++){setLed(3,i,2,foldColour);setLed(3,i,3,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,i,1,foldColour);setLed(3,i,2,1600);setLed(2,i,2,foldColour);setLed(2,i,3,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,i,0,foldColour);setLed(3,i,1,1600);setLed(2,i,1,foldColour);setLed(2,i,2,1600);setLed(1,i,2,foldColour);setLed(1,i,3,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(2,i,0,foldColour);setLed(3,i,0,1600);setLed(1,i,1,foldColour);setLed(2,i,1,1600);setLed(0,i,2,foldColour);setLed(1,i,2,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(1,i,0,foldColour);setLed(2,i,0,1600);setLed(0,i,1,foldColour);setLed(1,i,1,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(0,i,0,foldColour);setLed(1,i,0,1600);}  updateCube();Delay(timer);

for(int i=0;i<4;i++){setLed(1,3,i,foldColour);setLed(0,3,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(2,3,i,foldColour);setLed(1,3,i,1600);setLed(1,2,i,foldColour);setLed(0,2,i,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,3,i,foldColour);setLed(2,3,i,1600);setLed(2,2,i,foldColour);setLed(1,2,i,1600);setLed(1,1,i,foldColour);setLed(0,1,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,2,i,foldColour);setLed(3,3,i,1600);setLed(2,1,i,foldColour);setLed(2,2,i,1600);setLed(1,0,i,foldColour);setLed(1,1,i,1600);}  updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,1,i,foldColour);setLed(3,2,i,1600);setLed(2,0,i,foldColour);setLed(2,1,i,1600);} updateCube();Delay(timer);
for(int i=0;i<4;i++){setLed(3,0,i,foldColour);setLed(3,1,i,1600);}  updateCube();Delay(timer);


}

//==============================================================================================================
//Set an LED within the cube
//==============================================================================================================

void setLed(byte x,byte y,byte z,int colour){//colour 0-1530
byte red,green,blue;  

if(colour<=255){red=255;green=0;blue=colour;}
else if(colour<=510){blue=255;green=0;red=255-(colour-255);}
else if(colour<=765){blue=255;red=0;green=colour-510;}
else if(colour<=1020){green=255;red=0;blue=255-(colour-765);}
else if(colour<=1275){green=255;blue=0;red=colour-1020;}
else if(colour<=1530){red=255;blue=0;green=255-(colour-1275);}
else if(colour>1530){red=0;blue=0;green=0;}

switch(z){
case 0:  Red1[(y*4)+x]=red;Green1[(y*4)+x]=green;Blue1[(y*4)+x]=blue;  break;
case 1:  Red2[(y*4)+x]=red;Green2[(y*4)+x]=green;Blue2[(y*4)+x]=blue;  break;
case 2:  Red3[(y*4)+x]=red;Green3[(y*4)+x]=green;Blue3[(y*4)+x]=blue;  break;
case 3:  Red4[(y*4)+x]=red;Green4[(y*4)+x]=green;Blue4[(y*4)+x]=blue;  break;
}
}

//==============================================================================================================
//Delay - 0.003s resolution
//==============================================================================================================

void Delay(unsigned long time){
  start=milliSeconds;
  while(milliSeconds-start<time){delayMicroseconds(1);    }       // wait for a second 
}
//==============================================================================================================
//Reset cube
//==============================================================================================================

void resetCube(){
   for(int i=0;i<16;i++){
   Red1[i]=0;
   Blue1[i]=0;
   Green1[i]=0;
   
   Red2[i]=0;
   Blue2[i]=0;
   Green2[i]=0;
   
   Red3[i]=0;
   Blue3[i]=0;
   Green3[i]=0;
   
   Red4[i]=0;
   Blue4[i]=0;
   Green4[i]=0;
   }}  
  
//==============================================================================================================
//Update cube
//==============================================================================================================

void updateCube(){ 
 for(int i=0;i<16;i++){
Data[address[(i*3)]] = Red1[i]*16 ;  
Data[address[(i*3)+1]] = Green1[i]*16 ;  
Data[address[(i*3)+2]] = Blue1[i]*16 ;  

Data[address[(i*3)]+48] = Red2[i]*16 ;  
Data[address[(i*3)+1]+48] = Green2[i]*16 ;  
Data[address[(i*3)+2]+48] = Blue2[i]*16 ;  

Data[address[(i*3)]+96] = Red3[i]*16 ;  
Data[address[(i*3)+1]+96] = Green3[i]*16 ;  
Data[address[(i*3)+2]+96] = Blue3[i]*16 ;  

Data[address[(i*3)]+144] = Red4[i]*16 ;  
Data[address[(i*3)+1]+144] = Green4[i]*16 ;  
Data[address[(i*3)+2]+144] = Blue4[i]*16 ;  
 }

}

//==============================================================================================================
//Cube setting interrupt
//==============================================================================================================

ISR(TIMER0_COMPA_vect){//timer2 interrupt 250hZ
milliSeconds+=3;
     Tlc.clear();
     
 for(int i=0;i<48;i++){
Tlc.set(i,Data[((layer-1)*48)+i]);
 }
 

switch(layer){

case 1:    PORTD |= _BV(PD6); break;
case 2:    PORTD |= _BV(PD4); break;
case 3:    PORTD |= _BV(PD2); break;
case 4:    PORTD |= _BV(PD5); break;

} 
    
    Tlc.update();
delayMicroseconds(2000); 

switch(layer){

case 1:    PORTD &= ~_BV(PD4); break;
case 2:    PORTD &= ~_BV(PD2); break;
case 3:    PORTD &= ~_BV(PD5); break;
case 4:    PORTD &= ~_BV(PD6); break;

}

layer++;

if(layer==5){layer=1;}

}
//==============================================================================================================
//Test all LEDs in the cube
//==============================================================================================================
void testCube(){
   for(int a =0;a<4;a++){
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
    digitalWrite(layers[a],LOW);
  for(int i=0;i<48;i++){
    Tlc.set(address[0],0 );
    if(i>1){ Tlc.set(address[i-1],0 ); }
    Tlc.set(address[i],2000);                        //sets tlc's

  Tlc.update();                              //updates tlc's
  delay(50);
}
 Tlc.set(address[47],0 );
  } 
}
