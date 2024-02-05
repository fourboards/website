//Commands:
//  *00001#     -  Stop Rapid Fire
//  *00084553#  -  Begin Rapid Fire
//  *00004#     -  Single Measurement
//  #           -  Repeat Previous Command
//  r           -  Shuts Down
//  *001515#    -  Turns on Laser
//  *004747#    -  Turns off Laser

unsigned long readings[40];

void setup(){
Serial3.begin(115200); 
Serial.begin(115200);

}

void loop(){
  unsigned long timee=millis();
Serial.println(getDistance());//Timeout of 2000 in python
Serial.print("Time = ");Serial.println(millis()-timee);
delay(1000);
}


int getDistance(){
char inData[21];
int distance=0;
while(Serial3.available()){Serial3.read();}
Serial3.println("*00004#");//Rapid
while(Serial3.find("*")==0){}
if(Serial3.find("*")==1){
Serial3.readBytesUntil('#', inData,21);  
for(int i=0;i<21;i++){
 Serial.print(inData[i]); 
  Serial.print("  "); 
}
Serial.print("  -  "); 
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

