---
layout: post
hero-bg-color: '#FFFFFF'
uid: z-probe-board
title:  'Z-Probe Board'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/z-probe-board/IMG_4807.JPG">
<img src = "{{ site.url }}/images/portfolio/z-probe-board/IMG_4807.JPG">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  In recent years consumer 3D printers have come on leaps and bounds, now producing high quality prints quickly and efficiently at a relatively low cost.  However one of the big problems that still limits the market is the ease of use of such machines.  While printers are much better now, they are still faced with the problems of print heads jamming, filament slipping, stepper motors missing steps and prints warping due to poor surface adhesion.  All these problems mean to operate a 3D printer you still have to be fairly technically minded, something which is preventing 3D printers from entering the mainstream.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Auto-bed levelling is one feature that has begun to appear on 3D printers; it involves the print bed being probed at the beginning of a print and then the printer automatically making adjustments to the height of the print head.  The main advantage of this system is the entire first layer will always print at the perfect height, which will ensure surface adhesion is optimal, and in theory reduce the effect of warping on the print.  This is a brilliant development for the industry as it means there is one less factor for the end user to worry about.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Whilst working at Active 3D I worked on a project which would allow auto bed levelling to be an easy upgrade for existing printers and a pre-installed feature for new ones.  Like many other printers on the market which offer this feature we used an inductive probe to detect the print bed.  These sensors are ideal for the purpose as they are highly accurate, work at a range of 2-4mm (meaning it stays out of the way of the print head) and are designed for industrial use so they are very rugged.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  At the time of starting this project Active 3D used 3 main types of control board, Rumba, Ramps and Melzi.  Unfortunately none of these boards have the facility to plug an inductive probe straight in, which meant a custom PCB was in order.  Below is the schematic for the PCB I ended up designing...
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/z-probe-board/image-asset.jpeg">
<img src = "{{ site.url }}/images/portfolio/z-probe-board/image-asset.jpeg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  BSS138 is an N-Channel Field Effect Transistor which makes a potential divider with LED1 and R1. This acts as a logic level shifter from the 12v output of the sensor to a 5v output which is safe to feed into the control board's microcontroller.  LED1 also acts as a visual indication to the user as to when the probe has detected the print surface.  SENSOR is a header which the probe plugs into.  The probe only has three pins, power, Vout and ground, but the header has four so a flying wire can be crimped into pin 1 to supply 12v to the sensor which is unavailable on some control board's expansion headers.  R3 is a current protection resistor for Q1 and R2 is pull down for its gate.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  SV1 is the socket which plugs onto the expansion headers on the existing control board.  This is a good solution as it prevents the need for random flying wires being soldered to various points on the control board as well as making the upgrade significantly easier.  However not all 3 control boards have the same pin out on there expansion headers.  To solve this problem I have used  solder jumpers which can be configured for the different expansion header layouts .  The signal is directly connected to one pin which is a digital IO on every expansion header, depending on the board being used the firmware can be changed accordingly to set that particular digital pin as the sensor input.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The PCB design was done in eagle CAD for which the download link is available below.  From the left here is the complete two sided board, then top and finally bottom layer.  On the left of the board are the SMD components (R1,R2,R3,Q1,LED1) and the inductive sensor header.  Down the middle are the solder jumpers with silkscreen labels depicting the configuration required for the three different control boards.  Finally on the right is the 2x5 header socket which plugs onto the control board's expansion header.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/z-probe-board/image-asset.png">
<img src = "{{ site.url }}/images/portfolio/z-probe-board/image-asset.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Eagle CAD):
  <a href="/s/Z-Probing-Add-on-Board.brd">
   Z-Probe add on board.brd
  </a>
  <a href="/s/Z-Probing-Add-on-Board.sch">
   Z-Probe add on board.sch
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Because this was a low volume prototype run I assembled these boards by hand. The first stage in the process was to apply the solder paste.  I do this manually using a syringe as it doesn't require a stencil to be made up and it reduces wastage of the paste itself.  Once I had pasted all the boards I put each component in place and then carefully transferred each of the boards across to my baking tray.  The baking tray goes in the toaster oven at roughly 100 degrees celsius for 30 seconds (I manually switch the oven on and off to maintain this temperature) and once it has had this initial preheat I leave the oven on continuously till all of the joints have reflowed.  Next the headers have to be soldered on manually and then I clean each of the boards up with Flu (PCB cleaning solvent).  Finally I set up a test procedure on a bread board and ensure each board is operating correctly; fortunately in this run they all worked first time so there was no need for any rework.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMAG0870+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMAG0870+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMAG0882.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMAG0882.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_4807+-+Banner.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_4807+-+Banner.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMAG0884+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMAG0884+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMAG0873+%281%29.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMAG0873+%281%29.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMAG0875.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMAG0875.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The board functions as intended and below is a video of the auto bed leveling in action on an Active X1 3D printer.  Because this is just a video demonstrating the auto bed leveling functionality, the printer isn't extruding any plastic and the print surface is temporarily a small piece of sheet metal (the inductive sensor does not work on 10mm perspex).
 </p>
</div>


<iframe src="//www.youtube.com/embed/NNZLVAwPn-Q?wmode=opaque&enablejsapi=1" height="480" width="854" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  From the video you can see that setup is simple as intended.  The probe itself must be attached to the print head and a metal print surface must be used.  The board can then be plugged into the expansion header and then the probe plugged into the board.  In this particular case a 12v supply (the yellow wire) is required as the expansion header does not have this broken out.  The header which the sensor plugs into has 4 pins, two of which are connected to make this easier.  Once this is done the LED on top of the probe lights up, this extinguishes when a metal object is present; the LED on the board does the opposite of this to show the level shifting is working.  Next the firmware for the printer has to be updated and modified to enable auto bed levelling.  In this case I used Marlin firmware which can be downloaded from the Git repository (https://github.com/MarlinFirmware/Marlin).   One line of G-code also has to be added to the start code, this is G29 which triggers the bed probing routine.  Once this is done the print can begin, you will see in the video the bed is measured in 9 places before printing commences, then throughout the print the height of the print head is continuously adjusted to make up for the imperfections in bed height.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This concludes my write up of the Z-Probe board.  Below are a number of close ups of the complete system.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5076.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5076.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5080.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5080.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5084.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5084.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5073.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5073.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5071.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5071.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/z-probe-board/IMG_5068.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/z-probe-board/IMG_5068.JPG"></a>
    </div>
  </li>
</ul>
<br>


