---
layout: post
hero-bg-color: '#FFFFFF'
uid: 8x8x8-rgb-led-cube
title:  '8x8x8 RGB LED Cube'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5465.JPG">
<img src = "{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5465.JPG">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  In 2013, fascinated by
  <a href="https://www.youtube.com/user/kdarrah1234" target="_blank">
   Kevin Darrah's
  </a>
  8x8x8 RGB LED Cube, I set out to build my own.  Around 4 years later and after a
  <a href="/rgb-led-cube">
   prototype 4x4x4 RGB LED cube
  </a>
  it was finished!  Here's how I went about it.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/schem.png">
<img src = "{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/schem.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The schematic for the control board may look complicated but is actually relatively simple.  Inspired by a
  <a href="http://www.hownottoengineer.com/projects/rgb-led-cube.html" target="_blank">
   hownottoengineer
  </a>
  article I chose to base the design on an STP16 LED driver IC.  These drivers act as SPI shift registers with a constant current sink feature set by a resistor connected to REXT.  The cube itself features 512 RGB LEDs so in total requires 1536 PWM channels, obviously this is not possible using just microcontroller IO pins (Also this would make wiring up the cube very difficult!).  Instead, to accomplish this the cube has to be multiplexed, meaning only when layer of the cube is ever on at once.  By dividing 1536 by the 8 layers you end up needing just 192 channels which can also divided by the 16 channels the STP16 offers, leaving the need for just 12 ICs.  Originally I planned to control 3 data lines each going to 4 STP16s with a common clock and chip select, but this turned out to be slower than a hardware SPI approach, more on this later.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Because the cube is multiplexed the control board needs to be able to turn on and off the individual layers.   For this I opted to use a transistor driving a P-Channel MOSFET because of its current drive capabilities.  In theory with all LEDs white a single MOSFET could have to drive almost 4A to a single layer, in practice it is much less than this but this is what I designed the circuit to be capable of.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The final part of the schematic is a standalone Arduino consisting of ATMEG328p and supporting circuitry.  Unfortunately this IC turned out to be too slow so it had to be removed and I had to connect up an Arduino DUE to the SPI and MOSFET control lines instead.  If I was doing this again I think I would just break out the control pins to a 0.1" header and handle everything else remotely (something to bear in mind if you want to build your own).  As well as the microcontroller programming header I added connections for a bluetooth module, I2C attachments and a couple of buttons, I never used them but they add a number of possibilites for control to the project.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/board.png">
<img src = "{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/board.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The schematic translated into the following PCB.  I believe it is a very compact way of providing this number of output channels.  In the future I would like to replace the ATMEGA328p with a slightly faster processor and provide a complete control board for anyone who wants to build an RGB LED cube, watch this space!  Once I had the PCB assembled it was time to start connecting the channels to there corresponding LEDs.  I opted to use 16 way IDC sockets to connect to the control board as it allows for boards to be easily switched in and out, I used a 10 way dupont connector for the anode (layer) connections.  Another thing that I might add to the PCB is a small relay for allowing the cube to be switched on and off using a lighter weight switch, I had to add this externally this time.  The PCB mounts with five M3 bolts leaving it nice and secure.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0160+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0160+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0161+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0161+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0181.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0181.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0131.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0131.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0175.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0175.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0150.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0150.jpg"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Eagle CAD):
  <a href="{{ site.url }}/files/8x8x8-rgb-led-cube/Control_Board.sch">
   Control Board.sch
  </a>
  <a href="{{ site.url }}/files/8x8x8-rgb-led-cube/Control_Board.brd">
   Control Board.brd
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Probably the biggest challenge in this project was the actual assembly of the cube.  I spent a long time thinking through exactly how it was going to work as I wanted to make it as neat as possible.  Previously with the 4x4x4 cube I had made each layer and then struggled to stack the layers together.  The results were not that pretty but they did work at least!  From reading other peoples experience's online I concluded it would be best to make the cube's columns first.  Then assemble vertical panels and finally connect them together from the middle outwards, here are the stages I went through:
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  1. I purchased 600 10mm LEDs from AliExpress.  It was worth buying almost 100 too many as a fair few of the LEDs were physically deformed, with the LED sunk into the epoxy off center.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  2. I tested each LED individually using a little test jig I put together.  It cycles through the red, green and blue elements of the LED to ensure it is fully functional.  There would be nothing worse than discovering a broken LED right in the middle of the cube!
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  3. The LEDs that passed quality control had there legs bent at predefined angles using the circular jig shown in the images below.  These angles were designed based on the leg starting location and three leg finishing positions which were separated by 120 degrees around a circle of set radius.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  4. Next I cut 22 SWG tinned copper wire into lengths to match the length of the column jig shown below.  I
  <a href="http://Beadalon Wire Straightener" target="_blank">
   used this tool
  </a>
  to straighten each wire which worked really well, and although it didn't end up perfectly straight once it was soldered into a column under tension it became straight.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  5. Now it was time to put the wire and the LEDs together and solder up the 64 columns that make up the cube.  I designed and built the jig shown below to make the process as easy as possible and to ensure the LEDs ended up at regular intervals.  To use the jig you first load and tension three wires.  Next you move the slider to the bottom and load an LED into it.  Having soldered that LED to the outer wires you move the slider to the next location and repeat the process.  The slider has a number of internal ball bearings spring loaded which locate in the notches on the 8mm hardened steel rod.  Once all 8 LEDs have been soldered the column can be cut out of the jig and then have the excess LED wires trimmed.  Each column is then tested to ensure all LEDs have been soldered in correctly.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  6. Sets of eight columns are now loaded into another jig which panelises them.  Horizontal anode connections join the eight columns together before the panel is cut out of the jig.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  7. The panels must now be joined together.  From experience I learnt it is best to do the final assembly in position as it becomes very difficult to line up all the LED connections once the cube is soldered together.  I used Jenga blocks and another jig to get the panels square to each other before soldering more horizontal anode connections to connect each panel to the next.  At this point I had used all the wire I needed with just inches to spare.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  And that's it, the cube was finished!  Below are all the CAD files I used, although the wooden jigs aren't included in this it is quite simple to make your own, the only real requirement is that the spacing remains at 40mm between each LED centre.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0038.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0038.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0113.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0113.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0042.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0042.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0054.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0054.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0057.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0057.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0118.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0118.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0086.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0086.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5450.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5450.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0035.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0035.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0120+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0120+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0032.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0032.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0053.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0053.jpg"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Various CAD):
  <a href="https://drive.google.com/open?id=0B2f5D6TncWHDTmVwMXVXcV9vTDg" target="_blank">
   CAD.zip
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I really liked the oak casing I made for the nixie clock so when it came to designing a case for the LED cube I already knew what to use.  I ended up using a solid oak plank, cut in half and glued together as the main structure of the case.  From here I milled out as much of the center as possible to allow for the electronics to fit inside.  Unfortunately I managed to break the corner off where the planks joined which rather effected the look.  To cover this I opted to use some sheet stainless steel, provided cut to size from ebay.  Whilst this looked amazing it was rather counter productive as I may as well have used these for the sides and then put thinner oak planks on top rather than milling away the majority of the plank.  I used some filler to level of the sides and then a small amount of gorilla glue to secure the stainless steel panels.  Finnally I used a template to drill the 200 holes required to pass all the connections through the case to the electronics and then started assembling the cube on top.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0068.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0068.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0100.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0100.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0123.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0123.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0070+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0070+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0109.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0109.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMAG0103.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMAG0103.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The code for the cube is not too complicated.  There are three main parts too it.  The most complicated is the interrupt which is regularly called and handles all of the cube multiplexing and bit angle modulation.  These two concepts are demonstrated by hownotoengineer's GIFs below.  As mentioned earlier the ATMEGA328 was not fast enough to produce more than a 4 bit PWM which only gives 16 different values.  With the Arduino DUE the cube will run in 6 bit PWM mode which allows 64 different values.  This is still something I want to improve.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/multiplex.gif">
<img src = "{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/multiplex.gif">
</a>


<a href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/bam.gif">
<img src = "{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/bam.gif">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  On top of this layer in the code is a function which fills an array with LED data based on the location and value that is parsed to it.  This makes writing animations very simple.  Whilst a couple of the animations in the software I have written myself the majority are from Kevin Darrah's project.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Arduino):
  <a href="{{ site.url }}/files/8x8x8-rgb-led-cube/Cube_Code_Due.ino">
   Cube_Code_Due
  </a>
 </p>
</div>


<hr>

<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5465.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5465.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5470.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5470.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5462.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5462.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5476.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5476.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5460.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5460.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/8x8x8-rgb-led-cube/IMG_5490.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/8x8x8-rgb-led-cube/IMG_5490.JPG"></a>
    </div>
  </li>
</ul>
<br>


<iframe src="//www.youtube.com/embed/Hrq32Xa9ejQ?wmode=opaque&enablejsapi=1" height="480" width="640" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

