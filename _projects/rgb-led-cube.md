---
layout: post
uid: rgb-led-cube
title:  'RGB LED Cube'
tags: portfolio arrows
---

<div class="projects clearfix">
 <a href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4909.jpg">
  <img src = "{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4909.jpg">
 </a>
</div>
<br>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This idea came about when I was browsing the internet for an electronics project, I came across the concept of an LED cube and was amazed by the visual effect it gave.  Researching the idea further I discovered
  <a href="http://www.kevindarrah.com/?cat=99" target="_blank">
   Kevin Darrah's
  </a>
  8x8x8 RGB LED cube, which after seeing I just had to build.  Initially I had the full intention of diving straight in and building the 8x8x8 cube, however with the parts needed being quite expensive and my lack of experience, I spent a long time procrastinating about the daunting 'leap of faith' I would be making if I spent the money.  In the end though I decided to start small and order the items I would need for the 4x4x4 cube I am showing you now.  Therefor you could say the project isn't really finished yet, and I would agree.  This is how I went about the design and manufacture of  my prototype for the full 8x8x8 RGB LED Cube.
 </p>
</div>


<hr>

<div class="projects clearfix">
 <a href="{{ site.url }}/images/portfolio/rgb-led-cube/cube-layout.png">
  <img src = "{{ site.url }}/images/portfolio/rgb-led-cube/cube-layout.png">
 </a>
</div>
<br>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Being a 4x4x4 RGB LED Cube, there are 64 LEDs in total.  Each LED also contains 3 separate LEDs, Red, Green and Blue, which have a common anode and separate cathodes.  This makes for a total of 192 LEDs, which to give the best effect each need to be individually PWM controlled; allowing for the brightness of the red, green and blue components of each LED to be varied and mixed.
  <a href="http://www.kevindarrah.com/" target="_blank">
   Kevin Darrah
  </a>
  used a complex array of shift registers and transistors to control his cube, however I opted for a theoretically simpler option documented
  <a href="http://www.instructables.com/id/4x4x4-RGB-LED-Cube/" target="_blank">
   here
  </a>
  .   While the basic principles of control are the same, the vast number of PWM channels are produced using a 16 channel LED controller instead.  This particular IC is the TLC5940 which offers a 12 bit PWM resolution and can be controlled using just a few digital IO pins. As I mentioned earlier this did cause me a few problems, but Il go into more detail about that when we get to the code.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  For now I will concentrate on the circuit boards, this project consists of two stacking PCBs; the top board (to the right) is single sided and simply organises the connections between the legs of the cube and the PWM channel locations on the control board.  And the control board (to the left) is on the bottom of the stack which is double sided to ease the routing of power and data around the board.  This arrangement of PCBs allows the entirety of the control circuitry to sit underneath the cube in more or less its own footprint.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  As you can see there are 4 main ICs on the control board, 3 of these are TLC5940s making for a total of 48 PWM channels.  This is a quarter of the total number required which means the cube then has to be multiplexed layer by layer to achieve individual control of each LED.  This is done at such a frequency that the human eye can’t see the layers switching on and off, however if you try filming the cube at certain frame-rates the effect can be seen.  The TLCs are the 3 chips in the top left of the control board and are daisy chained to reduce the number of pins required t control them.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  MOSFETs are used to control the individual layers of the cube.  This is because of there fast switching speed compared to the option of a relay and there ability to handle the current draw of a layer with all the LEDs illuminated white (each element fully lit).  The FETs are used to source the current to each LEDs anode while the LED drivers sink current from the cathodes, this requires a P-channel FET to be used.  These components are positioned on the right hand side of the control board close to their header for connection to the cube as well as the main control IC.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I opted for an ATMEGA328 with an Arduino bootloader to control the functions of the cube.  This is because I used an Arduino Uno for much of the prototyping and it is the micro-controller I use most of the time.  Its 16 Mhz base clock is just about fast enough to write the data to the TLC5940s, however if I were to make an 8x8x8 cube it would be a little touch and go.  The Arduino sits in the bottom right of the board and you may notice a few of its legs are missing; this is because I ran out of space to wire the programming header in.  This was an essential feature for me on this project because the code was no were near finished, so I knew there would be a lot of programming to be done.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The only other parts of the board to point out are the filtering caps and large (probably oversized) traces on the rear of the board to deliver power throughout.  I also etched some text into the boards to fill in some of the gaps; this wasn’t silkscreen because I made the board at home.  For more information on my home PCB production, check out the
  <a href="{{ site.url }}/qr-code-clock">
   QR Code Clock
  </a>
  or my old
  <a href="{{ site.url }}/blog" target="_blank">
   Blog
  </a>
  .
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Eagle CAD):
  <a href="{{ site.url }}/files/rgb-led-cube/Bottom_Board.brd">
   BottomBoard.brd
  </a>
  <a href="{{ site.url }}/files/rgb-led-cube/Top_Board.brd">
   TopBoard.brd
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  When I built this cube it was always intended as a prototype, for that reason I never gave any consideration to producing a case for it.  However having dragged on for such a long time, and the completion of an 8x8x8 cube seeming a long way off, more recently I decided to smarten things up with a nice 3D printed casing.  Unfortunately because the cube was already soldered down to the PCB with 52 connections I had to make some compromises when it came to enclosing the cube.  If I had the option I would have had each leg going through its own hole, but this was no longer possible so instead I had to opt for a tight fitting square cut-out for the entire cube to slide through.  This part makes up most of the lid for the case which you can see from the renders below.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The bottom part of the case completes the cuboid shape of the casing and follows the curved edges of the lid.  Once the cube has been inserted into the lid, the combined assembly then sits in and on top of the bottom piece.  There are holes in each corner of the lid/base for magnets to hold the case shut in a semi-permanent fashion, allowing for easy maintenance and showing people the circuit boards involved in driving the cube.  After having designed and built a 4x4x4 RGB LED Cube I then failed at the primary school science part of the project by forgetting completely about magnet polarity; this lead to my first attempt at the case repelling its own lid!  But after removing the magnets and repositioning them it worked great.  At the back of the bottom part of the case is the hole for the panel mount DC power jack that powers the cube.  This is the only input on the case, giving it a very clean finish that does not distract from the cube itself but more compliments it.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/RGB.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/RGB.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/RGB3.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/RGB3.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/RGB2.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/RGB2.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/RGB1.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/RGB1.jpg"></a>
    </div>
  </li>
</ul>
<br>
<br>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download:
  <a href="{{ site.url }}/files/rgb-led-cube/RGB-LED-Cube-STL-h62m.zip">
   RGB_LED_Cube_STL.zip
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Whilst I did work from the instructables tutorial that I mentioned earlier, the PCB design, casing and code are completely original and my own work.  Apart from the TLC5940 library that I used, the code has been written from scratch.  I decided to use the library because at the time of coding I couldn’t make head or tail of the how the chip worked, although with the knowledge I have acquired since then I would like to think I could do it without now.  Other than this the code is relatively simple, with the control code taking up just 200 lines; there are 2 other main elements of the code, the interface code and the animation code, here is how they all work and interface with each other.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The first thing that happens is a load of variables are defined.  The 16 byte arrays are used for storing the state of each RGB LED, the resolution of the PWM is 12 bit but I store the state as an 8 bit number losing some of the resolution, but saving a lot of memory.  The ‘layers’ and ‘address’ arrays are used for pin mappings and ‘colours’ is used to predefine some mixes of RGB that make real colours.  Next up everything is initiated and then a timer is set up on Timer 0 at 312 Hz.  This fires an interrupt every 3.21 ms which clears the TLCs, switches off the previous layer, writes the new data to the TLCs and then switches the next layer back on.  A variable ‘layer’ keeps track of which layer is to be switched on and off each time.  As you are already aware I had a problem with the frequency of the interrupt being too high for the data transfer to the TLCs, this was made difficult because if the frequency was to low then the layer switching became apparent to the human eye.  In the end I found a good compromise, but it’s an issue that has been flagged up to me for my 8x8x8 RGB LED cube.  This is the entirety of the control code, the interface code is then used for setting the colours of each LED.
 </p>
</div>


<div class="projects clearfix">
 <a href="{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-1.png">
  <img src = "{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-1.png">
 </a>
</div>
<br>

<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  Something that took me a long time to work out was why my cube was looking completely washed out.  Eventually I realised that I was selecting random amounts of red, green and blue rather than selecting a random colour.  This meant too much of each colour was present in each LED which generally produced a mostly white colour.  To solve this I wrote some code to simplify the process of setting the individual LEDs, this makes up the interface code.  The colour is now set using a value between 0 and 1530, where 0 is red with each of the other element colours 510 apart. This is done using the if statements in the code below.  From this no more than two LEDs can be on at any time, in
  <a href="http://www.jacoburge.co.uk/blog/2014/03/4x4x4-rgb-led-cube-finished.html" target="_blank">
   this blog post
  </a>
  I discuss this solution further.  Once the values for the red, green and blue elements has been decided they are saved in the appropriate byte array based on their layer.
 </p>
</div>


<div class="projects clearfix">
 <a href="{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-2.png">
  <img src = "{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-2.png">
 </a>
</div>
<br>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Animation code is then written using the ‘setLed’ command as well as the ‘updateCube’ which rearranges all of the byte arrays into a single array called ‘data’ based on the pinassignments defined in ‘address’.  There is also a subroutine for completely wiping the cube which simply sets the entire byte array to 0.  These sub routines are implemented in each of the animations which are then executed from the main loop.  This makes writing new animations and adding them to the playlist extremely easy.  One other problem I came up against was that using timer 0 effects the operation of the Delay() function.  Consequently I made my own delay function which uses the millis() function; whilst it isn’t required for most of the code it is quite useful in some of the animations.
 </p>
</div>


<div class="projects clearfix">
 <a href="{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-3.png">
  <img src = "{{ site.url }}/images/portfolio/rgb-led-cube/image-asset-3.png">
 </a>
</div>
<br>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Arduino):
  <a href="{{ site.url }}/files/rgb-led-cube/RGB_LED_Cube.ino">
   RGB_LED_Cube.ino
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  So there you have it, the prototype for the 8x8x8 RGB LED Cube.    Here are some pictures of the finished product.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4926.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4926.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4934.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4934.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4931.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4931.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4930.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4930.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4923.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4923.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/rgb-led-cube/IMG_4927.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/rgb-led-cube/IMG_4927.jpg"></a>
    </div>
  </li>
</ul>
<br>
<br>

