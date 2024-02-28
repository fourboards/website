---
layout: post
hero-bg-color: '#FFFFFF'
uid: rubix-cube-solving-robot
title:  'Rubix Cube Solving Robot'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/IMG_4858+-+Banner.jpg">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/IMG_4858+-+Banner.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  When I was young I spent a lot of time playing with LEGO.  Starting off with the standard bricks I soon moved on to LEGO technic and then combined this with LEGO Mindstorms too.  After many random contraptions later and 3 years of competing in a robotics competition called The First LEGO League, I had gained quite a lot of confidence in the design and programming of LEGO robots.  This was when I came across the website
  <a href="http://www.tiltedtwister.com" target="_blank">
   www.tiltedtwister.com
  </a>
  by Hans Anderson; he has designed robots that can mechanically display the time, solve sudokus and most impressively solve a rubix cube.  I had to make one of these.  I quickly built the robot from his instructions and then got down to the programming, I decided I wanted to write the code myself rather than use his source code from the original project.  However I faced a lot of problems and after several months of trying I deemed it not possible based on my hardware setup (although it must have been because he managed it!).
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Having learnt from my mistakes last time I set about making a new robot, this time not from LEGO but using the 3D printer I had just got my hands on; this has allowed me to create completely custom parts, much more suited to the task in hand.  I designed it in such a way that none of the previous problems I had encountered could possibly re-emerge, and I'm glad to say none of them did!  Here is the 'finished' robot solving a rubix cube in a mere 48 seconds.
 </p>
</div>


<iframe src="//www.youtube.com/embed/QOdQKW8wp44?wmode=opaque&enablejsapi=1" height="480" width="854" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Originally I did plan to fully enclose the system and give it a smart user interface etc. however having had so much success using just two claws, I don't want to stop there.  I have already started making plans for an upgraded version with 4 claws instead, using faster and more powerful digital servos and a quicker scanning system.  But that won't be happening for a while, so in the mean time here is my summary of the robot in its current state.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The biggest problem I had with the Lego robot was the lack of accuracy the robot had when turning faces of the rubix cube which lead to the cube getting jammed up and the robot trying to rip its self apart.  So this time during the design process I took steps to maximise the precision of the moving parts.  This resulted in me using NEMA 23 stepper motors to turn the faces of the cube and because they are significantly over powered for the task in hand they can achieve this with ease.  But even if the motor itself is accurate, problems will still arise if there is too much play in the mechanics of the gripper itself.  To ensure this was not the case I went for a design that sees the main arms pivoting on substantial 8mm ABEC 9 roller-skate bearings and controlled via secondary arms connected by linkages.  This removes the torsion from the flimsy servo horns and directs it straight to the 1/4" drive shaft.  For servos I went for metal gears to prevent slippage as well as the highest torque versions I could find.  To maximise gripping power I opted for two servos per claw, however this does lead to a difficulty when centering the cube and is something I might consider changing next time.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The other main part of the robot is the scanning system.  This is another thing that needs precise positioning to ensure repeatability.  To achieve this I opted for a mainly spring based system to enable small deviations in the cubes position and angle to be easily compensated for.  The main arm is sprung loaded so that it rests in the position shown in the renders below.  A servo underneath the ply base is connected to the main arm using a cord which allows the arm to be pulled away from the cube (against the force of the spring) during the solving process and in standby mode.  There are then 4 more, very light springs in the head of the scanner which act as a pivot for angle adjust and also allow for some slight depth adjustment.  Once again the arm pivots on ABEC 9 bearings for ultimate precision.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete5.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete5.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete1.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete1.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete3.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete3.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete4.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete4.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete2.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete2.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/Claw+Complete.jpg"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Various CAD):
  <a href="https://drive.google.com/open?id=0B2f5D6TncWHDS19LV2FJUXU1Z2M" target="_blank">
   CAD.zip
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  From the outset of this project I wanted to design the robot in such a way that eventually it could become a stand-alone device, capable of all the necessary processing and control functionality for the robot to operate.  Consequently I opted not to use a camera based cube scanning system as the microcontrollers I use doesn’t have the processing power to handle the huge data stream a camera produces.  I found some special colour sensors which would have done the job, but I needed 9 to make the process ever so slightly efficient and this was going to cost far too much.  Looking deeper I discovered a technique which uses an LDR and RGB LED to measure reflected light levels for different wavelengths of light and produces a colour reading based on some known colours and there matching reflection readings.  After some initial experiments I decided to base the scanning system on this principal.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-1.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-1.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Here is the final version (3rd revision) of the circuit board I have developed for the purpose.  As you cans see there is an LDR positioned in each section of the board along with a WS2812B RGB LED.  One of the main problems I faced with the design of this was limiting the number of connections which would need to be made to the arduino.  For the LEDs there was an easy fix, because the WS2812Bs can be daisy chained and only require 1 data line as well as power and ground.  The LDRs were harder as they were going to require 9 signal pins alone!  In the end I found the 74HC4067 (IC1) which allows for 16 analogue channels to be read using just 4 digital signals, 1 analogue input as well as power and ground.  The other components on the board are the 2x5 way header and the 10K 0603 pull down resistors for the LDR potential dividers.  Whilst I had several attempts at making this board at home I couldn't quite achieve the 0.65mm pin pitch for IC1 reliably enough, consequently I had the board professionally manufactured at
  <a href="http://www.ragworm.eu" target="_blank">
   Ragworm
  </a>
  .  From the renders above you can see how the board is sandwiched between two 3D prints to position it for scanning.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The idea is that by having the segmented 3D print on top of the board, all external light can be removed improving the accuracy of the results.  On my desk (in the video below), this works very well but when on the robot slight positioning errors seem to have a big effect on the accuracy of the scanner.  Below you can see it in action, going through the calibration process and then some example scans:
 </p>
</div>


<iframe src="//www.youtube.com/embed/xL93pM4YcC4?wmode=opaque&enablejsapi=1" height="480" width="854" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  whilst I wanted to write the rubix cube solving code myself I realised that this was going to significantly delay the project and being before exams I wanted to make some quick progress.  Therefor I turned to an android app called cubemate that is able to scan the cube and then produce a solution.  I contacted cubemate and asked if there was a possibility he could add the functionality to allow my robot to send the cube permutation over bluetooth and receive the solution back.  He was very helpful and we soon had a much simpler app with just the functionality and none of the GUI from the public version.  You can see from this part of
  <a href="https://youtu.be/sNkb2Si3838?t=1m13s" target="_blank">
   this video
  </a>
  the app in action.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  To allow the arduino to communicate with my phone I bought a cheap bluetooth module from ebay and then setup a software serial port on the arduino mega.  The app is very simple to use, all that has to be sent is a string containing the colour of each facelet of the cube, for example
  <em>
   “Y W Y W W Y W Y Y G B B B G B R G R W W W W Y Y Y Y W G O B R O R B R G O G G B B G O O B R R R O R O O G O\n”
  </em>
  .  The app will either then respond with
  <em>
   "Invalid cube state"
  </em>
  or a solution such as
  <em>
   “R3 F2 B3 L2 U3 F2 D3 R2 L3 U1 R2 D1\n”
  </em>
  .  The code for sending the data is very simple:
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-2.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-2.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  It occurs directly after scanning of the cube and in the same sub routine.  The facelets are already saved into the correct order (the order that the app is expecting) meaning the array can quickly be sent out over the software serial port.  Serial1 is the bluetooth and Serial is the terminal for debugging.  After each character is sent a space is also sent and then finally a carriage return is sent to signal the end of the message.  Once the permutation has been sent off the app is able to very quickly calculate a solution, this is then returned over bluetooth and is received by this code:
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-3.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-3.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Firstly the variables are define and reset, then there is a pause waiting for data to enter the serial buffer.  Once data is available it is read into the char array 'inData' until the carriage return character is identified or the string is longer than 100 characters.  The data is then checked for error messages of which there are two: invalid cube state which means the scanner has misread some colours or invalid number of colours meaning not all the sent data has been successfully received.  If none of these messages appear then it is assumed that all is well and the arduino begins reading in the solution. It first calculates the total moves based on the number of characters that have been read in, each move takes up 3 characters so the total number of characters is divided by 3.  Then each move is translated into numbers for ease of handling and put in the 'moves' array; this is then accessed later on to work out a sequence of moves for the claws to execute.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-4.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-4.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I had lots of problems with the servo motors in the prototyping phase of this project.  Being under load for extended periods of time whilst gripping the cube lead to the servo heating up, effecting the resistance of the control pot and therefore the positioning accuracy.  To solve this I decided to use come current sensors to detect the load they were under when returning to there home position and theoretically calculate a corrected position.  But because the current sensors where surface mount I decided it would be easier to make a PCB for testing.  It is a simple shield for an arduino mega which features 2 Big Easy Drivers, 4 servo headers with power supplied via current sensors, a potentiometer for claw control and a 12v DC power jack.    The board was a big success and I am still using to control the robot with the addition of some jumper wires into the mega headers which aren't covered by the shield.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  As you can probably appreciate there is quite a lot of code required to run such a machine, in fact in this case it is just over 1000 lines.  This means realistically I can’t go through the entirety of the operation of the code, however it is split into sub-routines labelled clearly with there function so if you are interested take a look.  It isn't the tidiest of code, but it does the job.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Arduino):
  <a href="{{ site.url }}/files/rubix-cube-solving-robot/Rubix_Cube_Solver.ino">
   Rubix_Cube_Solver.ino
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  If you open the code, you will see that the entirety of the functionality of the robot is controlled by sending characters to the arduino via the serial port.  This is an okay solution until you start getting over run with commands and there is no way you can remember what each of them do.  This is what happened to me, so I set about making a simple GUI to allow for easy control of the robot.  I used processing to create a  program  which provides buttons for every function as well as a serial monitor for debugging.  It has made operation much easier and makes the whole project more professional looking.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-5.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/image-asset-5.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Processing):
  <a href="{{ site.url }}/files/rubix-cube-solving-robot/GUI.pde">
   GUI.pde
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Originally the robot was never designed for speed, it was more a case of can the robot just solve a cube at all.  However having completed my main objective I soon set about seeing how fast I could get it to go!  The robot itself is quite quick when you ramp the speed of the steppers up and reduce the movement of the claws, although it does still have several limiting factors.  Firstly having only 2 claws to rotate 6 faces of the cube means some time is lost manoeuvring the cube into a position where a claw has access to the correct face.  Also the scanning system that I developed, while it requires very little processing power it isn’t the quickest, taking almost 1/3rd of the total time of the fastest solve yet (14 out of 48 seconds).  Finally I had lots of problems with operating the servos at higher speeds as they don’t cope with hot running conditions very well and quickly lose their accuracy.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Therefore I have started thinking about a few improvements that could be made to the robot in its current state.  The first problem has a very simple solution; more claws!  I think the optimum number is probably 4 as this would mean only 2 faces were not immediately accessible at any one time but there aren’t so many that they are constantly getting in each other’s way.  Scanning also has a simple fix…using a webcam would allow the scanning procedure to happen in a much more efficient way.  Seeing as I ended up using a computer in the last attempt anyway I think this time the entirety of robot control would be done using a computer.  This would allow for more complex colour recognition algorithms and more consideration given to efficient claw control.  And finally the servos, I already tried using current sensors to improve accuracy however this takes up a lot of time so I think this solution needs to be reconsidered.  Instead I think the answer lies in digital servos which offer higher torques and much better positioning accuracy.  But the problem with these is they don’t come cheap and I would be needing something like 8 of them.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  So as you can see I have many ideas for how the robot can be improved.   Now I just need to find the time and money to bring my ideas to the real world.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  So that's what's gone into the robot so far and some of the things I hope to add to it in the future.  Below is a render of what I hope the project will eventually develop into.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/rubix-cube-solving-robot/rubix-robot.png">
<img src = "{{ site.url }}/images/portfolio/rubix-cube-solving-robot/rubix-robot.png">
</a>


