import processing.serial.*;

PImage bg;
Serial port; // The serial port object
PFont myFont;

int lf = 10;    // Linefeed in ASCII
String string0 = null;
String string1 = null;
String string2 = null;
String string3 = null;
String string4 = null;
String string5 = null;
String string6 = null;
String string7 = null;
String string8 = null;
String string9 = null;
String string10 = null;
String string11 = null;
String string12 = null;
String string13 = null;
String string14 = null;
String string15 = null;
String string16 = null;
String string17 = null;
String string18 = null;
String string19 = null;
String string20 = null;
String string21 = null;
String string22 = null;
String string23 = null;
// The font must be located in the sketch's 
// "data" directory to load successfully


void setup() {
  size(600, 830);
  port = new Serial(this, Serial.list()[1], 115200); 

 myFont = createFont("Georgia",13);

}

void draw() {
background(255);
textFont(myFont);

buttons();
textSize(21); 
fill(0);
textAlign(LEFT, CENTER);
if (string0 != null) {text(string0, 10,360);}
if (string1 != null) {text(string1, 10,380);}
if (string2 != null) {text(string2, 10,400);}
if (string3 != null) {text(string3, 10,420);}
if (string4 != null) {text(string4, 10,440);}
if (string5 != null) {text(string5, 10,460);}
if (string6 != null) {text(string6, 10,480);}
if (string7 != null) {text(string7, 10,500);}
if (string8 != null) {text(string8, 10,520);}
if (string9 != null) {text(string9, 10,540);}
if (string10 != null) {text(string10, 10,560);}
if (string11 != null) {text(string11, 10,580);}
if (string12 != null) {text(string12, 10,600);}
if (string13 != null) {text(string13, 10,620);}
if (string14 != null) {text(string14, 10,640);}
if (string15 != null) {text(string15, 10,660);}
if (string16 != null) {text(string16, 10,680);}
if (string17 != null) {text(string17, 10,700);}
if (string18 != null) {text(string18, 10,720);}
if (string19 != null) {text(string19, 10,740);}
if (string20 != null) {text(string20, 10,760);}
if (string21 != null) {text(string21, 10,780);}
if (string22 != null) {text(string22, 10,800);}
if (string23 != null) {text(string23, 10,820);}

 while (port.available() > 0) {
string0=string1;
string1=string2;
string2=string3;
string3=string4;
string4=string5;
string5=string6;
string6=string7;
string7=string8;
string8=string9;
string9=string10;
string10=string11;
string11=string12;
string12=string13;
string13=string14;
string14=string15;
string15=string16;
string16=string17;
string17=string18;
string18=string19;
string19=string20;
string20=string21;
string21=string22;
string22=string23;
string23 = port.readStringUntil(lf);
}
}

void mouseClicked() {
if(mouseX>30 &&mouseX<80 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('r');}//red
if(mouseX>88 &&mouseX<138 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('g');}//green
if(mouseX>146 &&mouseX<196 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('b');}//blue
if(mouseX>204 &&mouseX<254 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('w');}//white
if(mouseX>262 &&mouseX<312 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('y');}//yellow
if(mouseX>320 &&mouseX<370 &&mouseY>78 &&mouseY<118 ){port.write('m');port.write('o');}//orange

if(mouseX>30 &&mouseX<109 &&mouseY>182 &&mouseY<222 ){port.write('w');port.write('d');port.write('e');}//
if(mouseX>117 &&mouseX<196 &&mouseY>182 &&mouseY<222 ){port.write('w');port.write('c');port.write('e');}//
if(mouseX>204 &&mouseX<283 &&mouseY>182 &&mouseY<222 ){port.write('w');port.write('b');port.write('e');}//
if(mouseX>291 &&mouseX<390 &&mouseY>182 &&mouseY<222 ){port.write('w');port.write('a');port.write('e');}//

if(mouseX>30 &&mouseX<109 &&mouseY>230 &&mouseY<270 ){port.write('y');}//
if(mouseX>117 &&mouseX<196 &&mouseY>230 &&mouseY<270 ){port.write('d');}//
if(mouseX>204 &&mouseX<283 &&mouseY>230 &&mouseY<270 ){port.write('x');}//
if(mouseX>291 &&mouseX<390 &&mouseY>230 &&mouseY<270 ){port.write('c');}//

if(mouseX>386 &&mouseX<570 &&mouseY>30 &&mouseY<70 ){port.write('z');}//
if(mouseX>386 &&mouseX<570 &&mouseY>78 &&mouseY<118 ){port.write('t');}//
if(mouseX>386 &&mouseX<570 &&mouseY>134 &&mouseY<270 ){port.write('s');}//

}

void buttons(){
  
//calibrate scanner
fill(153);
stroke(153);
rect(30, 30, 340, 40,7,7,0,0); 
fill(#000000);
textSize(26); 
textAlign(CENTER, CENTER);
text("Calibrate Scanner", 195,45);

fill(#FF0009);
stroke(#FF0009);
rect(30, 78, 50, 40,0,0,7,7); 

fill(#00FF0A);
stroke(#00FF0A);
rect(88, 78, 50, 40,0,0,7,7); 

fill(#0300FF);
stroke(#0300FF);
rect(146, 78, 50, 40,0,0,7,7); 

fill(#FFFFFF);
stroke(#000000);
rect(204, 78, 50, 40,0,0,7,7); 

fill(#FFF703);
stroke(#FFF703);
rect(262, 78, 50, 40,0,0,7,7); 

fill(#FF8503);
stroke(#FF8503);
rect(320, 78, 50, 40,0,0,7,7); 

//Adjust Left Stepper
fill(153);
stroke(153);
rect(30, 134, 166, 40,7,7,0,0); 
fill(#000000);
textSize(26);
text("Left Stepper", 115,149);

fill(#000000);
stroke(0);
rect(30, 182, 79, 40); 
rect(117, 182, 79, 40); 

fill(#FFFFFF);
textSize(40); 
text("+",159,195);
text("-",70,195);

//Adjust Stepper
fill(153);
stroke(153);
rect(205, 134, 166, 40,7,7,0,0); 
fill(#000000);
textSize(26); 
text("Right Stepper", 289,149);

fill(#000000);
stroke(0);
rect(205, 182, 79, 40); 
rect(292, 182, 79, 40); 

fill(#FFFFFF);
textSize(40); 
text("+",334,195);
text("-",245,195);
//Arm grab ungrab
fill(#000000);
stroke(0);
rect(205, 230, 79, 40,0,0,7,7); 
rect(292, 230, 79, 40,0,0,7,7); 

fill(#FFFFFF);
textSize(40); 
text("R",334,246);
text("G",245,246);

fill(#000000);
stroke(0);
rect(30, 230, 79, 40,0,0,7,7); 
rect(117, 230, 79, 40,0,0,7,7); 

fill(#FFFFFF);
textSize(40); 
text("R",159,246);
text("G",70,246);
//stepper enable
fill(#000000);
stroke(0);
rect(386, 30, 184, 40,7,7,7,7); 

fill(#FFFFFF);
textSize(25); 
text("Enable/Disable",477,46);

//Scan
fill(#000000);
stroke(0);
rect(386, 78, 184, 40,7,7,7,7); 

fill(#FFFFFF);
textSize(25); 
text("Scan",477,94);

//Solve
fill(#000000);
stroke(0);
rect(386, 134, 184, 136,7,7,7,7); 

fill(#FFFFFF);
textSize(60); 
text("Solve",477,195);

fill(#000000);
textSize(35); 
textAlign(CENTER,CENTER);
text("Cube Solver II - Jacob Burge",300,300);
}

