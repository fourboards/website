import processing.serial.*;

Serial myPort;                     
int[] serialInArray = new int[3];
int[] xCoordinates = new int[361];
int[] yCoordinates = new int[361];
int[] xCoordinatesOld = new int[361];//{0,1,2,3,4,5,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-5,-4,-3,-2,-1};//
int[] yCoordinatesOld = new int[361];//{6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5};//
int[] dataIn = new int[24];
int[] arenaCorners = new int[10];//x1,y1,x2,y2,x3,y3,x4,y4,xCurrent,yCurrent

void setup(){
 size(900,900);
 printArray(Serial.list());
 String portName = Serial.list()[1];
 myPort = new Serial(this, portName, 115200);

}

void draw(){
updateDisplay();
serialRead();

}

void calculations(){
float[] pointToPoint = new float[360];
int[] xConsecutive = new int[360];
int[] yConsecutive = new int[360];
int[] segmants = new int[36];
int counter=0;
int mostCommon=0;
float offset=0;
int arenaWidth=570;//744mm
arenaCorners[8]=10000;
arenaCorners[9]=10000;

for(int i=0;i<360;i++){
xConsecutive[i]=0;
yConsecutive[i]=0;
 if(xCoordinatesOld[i]!=0||yCoordinatesOld[i]!=0){
      
  xConsecutive[counter]=xCoordinatesOld[i];
  yConsecutive[counter]=yCoordinatesOld[i];
  println(xConsecutive[counter],"  ",yConsecutive[counter],"  ");
  counter++;


 } 
 xCoordinatesOld[i]=0;
 yCoordinatesOld[i]=0;
}
byte gap=5;
for(int i=0;i<counter-gap;i++){ 
     if(xConsecutive[i]==xConsecutive[i+gap]&&yConsecutive[i]==yConsecutive[i+gap]){pointToPoint[i]=0;}
else if(xConsecutive[i]==xConsecutive[i+gap]){if(yConsecutive[i]>yConsecutive[i+gap]){pointToPoint[i]=(3*PI)/2;}if(yConsecutive[i]<yConsecutive[i+gap]){pointToPoint[i]=PI/2;}}
else if(yConsecutive[i]==yConsecutive[i+gap]){if(xConsecutive[i]>xConsecutive[i+gap]){pointToPoint[i]=PI;}if(xConsecutive[i]<xConsecutive[i+gap]){pointToPoint[i]=0;}}
else if(xConsecutive[i]<xConsecutive[i+gap]&&yConsecutive[i]>yConsecutive[i+gap]){pointToPoint[i]=(2*PI)-atan(1.0*(yConsecutive[i]-yConsecutive[i+gap])/(xConsecutive[i+gap]-xConsecutive[i]));}
else if(xConsecutive[i]>xConsecutive[i+gap]&&yConsecutive[i]>yConsecutive[i+gap]){pointToPoint[i]=((3*PI)/2)-atan(1.0*(xConsecutive[i]-xConsecutive[i+gap])/(yConsecutive[i]-yConsecutive[i+gap]));}
else if(xConsecutive[i]>xConsecutive[i+gap]&&yConsecutive[i]<yConsecutive[i+gap]){pointToPoint[i]=PI-atan(1.0*(yConsecutive[i+gap]-yConsecutive[i])/(xConsecutive[i]-xConsecutive[i+gap]));}
else if(xConsecutive[i]<xConsecutive[i+gap]&&yConsecutive[i]<yConsecutive[i+gap]){pointToPoint[i]=(PI/2)-atan(1.0*(xConsecutive[i+gap]-xConsecutive[i])/(yConsecutive[i+gap]-yConsecutive[i]));}
//println(pointToPoint[i]*(360/(2*PI)));
}

for(int i=0;i<36;i++){
  for(int j=0;j<counter-1;j++){ 
 if(pointToPoint[j]>=(PI/18)*i && pointToPoint[j]< (PI/18)+((PI/18)*i)){segmants[i]++;} 

}
if(segmants[i]>segmants[mostCommon]){mostCommon=i;}
  }
  println("###############");
  println(mostCommon);
  for(int j=0;j<counter-1;j++){ 
 if(pointToPoint[j]>=(PI/ 18)*mostCommon && pointToPoint[j]< (PI/18)+((PI/18)*mostCommon)){offset+=pointToPoint[j];} 
}
offset/=segmants[mostCommon];
println(offset);

if(offset<PI/2){offset=(PI/2)-offset;println("1/2");}
else if(offset<PI){offset=(PI)-offset;println("1");}
else if(offset<(3*PI)/2){offset=((3*PI)/2)-offset;println("2/3");}
else if(offset<2*PI){offset=(2*PI)-offset;println("2");}

println(offset);

for(int i=0;i<counter;i++){
xCoordinatesOld[i]=int((xConsecutive[i]*cos(1.0*offset))-(yConsecutive[i]*sin(1.0*offset)));
yCoordinatesOld[i]=int((xConsecutive[i]*sin(1.0*offset))+(yConsecutive[i]*cos(1.0*offset)));
println(xConsecutive[i],"  ",yConsecutive[i],"  ",xCoordinatesOld[i],"  ",yCoordinatesOld[i]);

}

for(int i=0;i<counter;i++){
 for(int j=0;j<counter;j++){
   if(xCoordinatesOld[i]>=0&&xCoordinatesOld[j]<=0||xCoordinatesOld[i]<=0&&xCoordinatesOld[j]>=0){
  if(abs(abs(xCoordinatesOld[i]-xCoordinatesOld[j])-arenaWidth)<arenaCorners[8]){
   arenaCorners[8]=abs(abs(xCoordinatesOld[i]-xCoordinatesOld[j])-arenaWidth);
   if(xCoordinatesOld[i]<xCoordinatesOld[j]){println("j>i - x");arenaCorners[0]=xCoordinatesOld[j];arenaCorners[2]=xCoordinatesOld[j];arenaCorners[4]=xCoordinatesOld[i];arenaCorners[6]=xCoordinatesOld[i];}
   else{println("i>j - x");arenaCorners[0]=xCoordinatesOld[i];arenaCorners[2]=xCoordinatesOld[i];arenaCorners[4]=xCoordinatesOld[j];arenaCorners[6]=xCoordinatesOld[j];}
  }
}
if(yCoordinatesOld[i]>=0&&yCoordinatesOld[j]<=0||yCoordinatesOld[i]<=0&&yCoordinatesOld[j]>=0){
  if(abs(abs(yCoordinatesOld[i]-yCoordinatesOld[j])-arenaWidth)<arenaCorners[9]){
   arenaCorners[9]=abs(abs(yCoordinatesOld[i]-yCoordinatesOld[j])-arenaWidth);
   if(yCoordinatesOld[i]<yCoordinatesOld[j]){println("j>i - y");arenaCorners[1]=yCoordinatesOld[j];arenaCorners[3]=yCoordinatesOld[i];arenaCorners[5]=yCoordinatesOld[i];arenaCorners[7]=yCoordinatesOld[j];}
   else{println("i>j - y");arenaCorners[1]=yCoordinatesOld[i];arenaCorners[3]=yCoordinatesOld[j];arenaCorners[5]=yCoordinatesOld[j];arenaCorners[7]=yCoordinatesOld[i];}
 
 }
}
 }  
}

println(arenaCorners[0],"  ",arenaCorners[1],"  ",arenaCorners[2],"  ",arenaCorners[3],"  ",arenaCorners[4],"  ",arenaCorners[5],"  ",arenaCorners[6],"  ",arenaCorners[7],"  ",arenaCorners[8],"  ",arenaCorners[9],"  ");

}

void updateDisplay(){
 background(255); 
 strokeWeight(2);
 fill(0);stroke(0);
 line(0, 450, 900, 450);
 line(450, 0, 450, 900);
 for(int j=0;j<360;j++){
  fill(#FF0303);stroke(#FF0303);
  ellipse(xCoordinates[j]+450,900-(yCoordinates[j]+450),4,4); 
  fill(#1421FC);
  stroke(#1421FC); 
  ellipse(xCoordinatesOld[j]+450,900-(yCoordinatesOld[j]+450),2,2); 
 }
 fill(#0BFF00);
  stroke(#0BFF00); 
  ellipse(arenaCorners[0]+450,450-arenaCorners[1],10,10); 
  ellipse(arenaCorners[2]+450,450-arenaCorners[3],10,10); 
  ellipse(arenaCorners[4]+450,450-arenaCorners[5],10,10); 
  ellipse(arenaCorners[6]+450,450-arenaCorners[7],10,10); 
  line(arenaCorners[0]+450, 450-arenaCorners[1],arenaCorners[2]+450, 450-arenaCorners[3]);
  line(arenaCorners[2]+450, 450-arenaCorners[3],arenaCorners[4]+450, 450-arenaCorners[5]);
  line(arenaCorners[4]+450, 450-arenaCorners[5],arenaCorners[6]+450, 450-arenaCorners[7]);
  line(arenaCorners[6]+450, 450-arenaCorners[7],arenaCorners[0]+450, 450-arenaCorners[1]);


 fill(0);stroke(0);
 ellipse(450, 450, 20, 20);  
}

void serialRead(){
 if(myPort.read()=='*'){
  for(int i=0;i<23;i++){
   dataIn[i]=myPort.read();
   if(dataIn[i]<48){
    dataIn[i]=48;
   }
  }
  if(dataIn[0]=='C'){
   for(int i=0;i<360;i++){
     xCoordinatesOld[i]=0;
     yCoordinatesOld[i]=0;
    xCoordinatesOld[i]=xCoordinates[i];
    yCoordinatesOld[i]=yCoordinates[i];
    xCoordinates[i]=0;
    yCoordinates[i]=0;
   }
       calculations();
  }
  else{
   int angle;
   angle=(dataIn[10]-48)+((dataIn[9]-48)*10)+((dataIn[8]-48)*100);
   if(angle>360){
    angle=360;
   }
   xCoordinates[angle]=(dataIn[16]-48)+((dataIn[15]-48)*10)+((dataIn[14]-48)*100)+((dataIn[13]-48)*1000);
   xCoordinates[angle]-=1000;
   xCoordinates[angle]= int(map(xCoordinates[angle],-600,600,-450,450));
   yCoordinates[angle]=(dataIn[22]-48)+((dataIn[21]-48)*10)+((dataIn[20]-48)*100)+((dataIn[19]-48)*1000);
   yCoordinates[angle]-=1000;
   yCoordinates[angle]= int(map(yCoordinates[angle],-600,600,-450,450));
  }
 }  
}




