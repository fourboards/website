---
layout: post
hero-bg-color: '#FFFFFF'
uid: qr-code-clock
title:  'QR Code Clock'
tags: portfolio
---

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_4904.JPG">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  For most this would appear to be one of the most pointless devices in existence today.  As the name suggests it is a clock, but rather than presenting the usual information in a conventional way it produces a QR code which must be scanned to reveal the time.  After getting my phone out many times to demonstrate this, every time ignoring the huge clock presented to me at the lock screen, I can see where they might be coming from.  But for me it has lots of point, this project was my first venture into surface mount technology and one of my early DIY PCB experiences.
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Work started with the PCB design.  For some reason that is no longer apparent to me I chose not to produce a schematic, instead diving straight into component placement and trace routing.  My aim with this design was to more or less fit all the electronics required under the display and confined to its width and height.  This would have required a 4 layer board and not wanting to pay for a commercially produced PCB I opted for two, stacking, double sided boards.   In hindsight splashing out on a commercial board would have made assemble significantly easier, but then where's the fun in that!
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/qr-code-clock/image-asset.png">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  After trying many different arrangements of driver ICs and displays I settled for the one above.  This design uses 9 SOIC MAX7219 LED matrix driver ICs, 9 xxxmm LED matrix's an Arduino Nano for control and a DS1307 real time clock module for keeping track of time.  The top board (to the right) has all 9 displays fixed too it as well as 3, 2x24 way sockets.  The traces on the board are identical under each display and simply rearrange the pin out of the displays to reduce congestion on the bottom board (to the left).
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The bottom board then has all the other components as well as 3, 2x24 way headers for interfacing with the top board.  Because I was making the boards at home I didn't have the luxury of plated through holes and therefor connecting the vias becomes very time consuming.  Consequently I wanted to limit the number of vias as much as possible.  This meant I ended up designing the PCB so that the headers would be soldered into place and then the driver chips soldered on top of these solder joints.  Whilst it wasn't an ideal solution it did allow me to make the best possible use of space and save a significant amount of money in the long run.  The MAX7219's are then daisy chained together and connected to the Arduino Nano.  The real time clock module slots into headers on the main PCB that are connected to the necessary power ground and data lines.  The SDA and SCl from the i2c bus, used for communication with the real time clock, are given 4K7 pull up resistors.  Finally a 2.1mm power jack is fitted and some wide tracks are routed to the various power hungry locations on the board.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Eagle CAD):
  <a href="/s/Through-Hole-Driver.brd">
   Through Hole Driver.brd
  </a>
  <a href="/s/Through-Hole.brd">
   Through Hole.brd
  </a>
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Being one of my early home made PCB projects, and the first double sided board I had to do a bit of experimenting.  I started out trying to work out a way of aligning the two acetates so I could expose both sides in such a way that the vias would line up.  At first I tried using 4 vias, 1 in each corner that I pre drilled and then stuck wire through to hold the acetates in place.  However this was fiddly and did not produce accurate enough results.  Next I made a jig out of 5mm clear perspex.  For this I taped one acetate in place, lined the other one up and then closed the jig, sticking the second acetate to the top part of the jig.  Once this alignment had been done it could be easily checked and then jig could be opened up and the board inserted.  I then taped the jig shut and exposed one side at a time.  This technique seemed to work very well and is actually the same method I use now.  Unfortunately the original jig is no longer clear enough to produce high quality boards because the tape I use seems to degrade very quickly in the UV light and the sticky residue is impossible to get off.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Once this had all been worked out I was able to proceed with production.  I used doubled up acetates in order to make up for any imperfections in the printer quality and then used the method described above to expose the boards.  For exposure I have an old scanner which is fitted with an array of UV LEDs.  It then has an Arduino controlling the original stepper motor and is able to expose at different speeds and different sized boards (see '
  <a href="/more">
   More
  </a>
  ' for further details).   Next up they were developed in developer for 2 minutes and then quickly rinsed under cold water.  After developing, both boards were etched in Sodium Chloride which took about an hour because of the size of the boards and the age of the acid.  Finally they were rinsed one more time and then I removed the photo resist using acetone.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The moment of truth as to weather the alignment process had worked was when the holes were drilled.  I used a Dremel on a Proxxon drill press with a 0.8mm  carbide bit.  Whilst the holes didn't line up perfectly, they weren't far off and easily within such a tolerance that the vias were not a problem to solder.  I painstakingly soldered copper wire through each via to connect the two sides of the board, and then trimmed of the excess.  Finally I did some visual inspections as well as continuity testing on certain parts of the boards which would later become inaccessible (mainly the section of the board under the LED matrix).
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/qr-code-clock/2014-02-04+19.57.31.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/2014-02-05+22.31.03.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/1.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/2.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/4.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/3.png">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Next up I needed too populate the circuit boards.  I started with the top board by soldering in the headers.  This was a straightforward task and went without a hitch.  Moving on I positioned all the LED matrix's on the board and then tacked them down with two solder joints to check for alignment.  Once they looked good I went ahead and soldered them completely into place.  At this point I tested the connections between the LED matrix's and headers by applying a voltage to the anode and cathode of each LED.  Through this testing I found several continuity issues which had not been discovered earlier; these were easily fixed with jumper wires.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  After this I soldered components such as the current selecting resistors, pull-up resistors, power jack and Arduino headers into place on the bottom board.  Then the most challenging part came, soldering the header in such a way that I would be able to put the SMD driver ICs on top of them.  Once again I tacked the corners down so there position could be adjusted, then I went for it, ensuring plenty of solder went into each joint.  Once I had done this I continuity tested every joint to reduce the chances of me having to lift a chip off later on.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Before soldering the driver ICs on, I had to bend the legs down in order for them to reach the board.  Unfortunately I had not come across drag soldering at this point in time which meant the hand soldering of the SMD chips took significantly longer than it should have done.  After attaching each chip I powered up the Arduino and ran some test code.  Without fail each display worked first time, which was nice!  Finally I used some flying wires to connect the real time clock (I got some measurements wrong so it wouldn't line up with the headers) and then gave it all a clean up with some Flu.
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/qr-code-clock/9.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/11.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/8.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/7.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/10.png">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/6.png">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Before starting this project I never really appreciated the complexity of a QR code.  But now, having learnt enough about them to write a program that can generate them automatically, I no longer look at them in the same way.  Fortunately I came across a detailed tutorial on the generation of QR codes early on in the project, www.thonky.com/qr-code-tutorial/, which explained the entire process very well.  I wont go into the details of QR code generation as it is, however I will explain some of the choices I made about the format of my QR codes and how the Arduino generates and displays them.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Firstly data has to be recovered from the real time clock; this is done over the I2C data bus using some example code for the DS1307 RTC module.  The system waits for the second to change before generating and displaying the next code.  This prevents the display being refreshed to often causing unwanted flashing.  Once the data has been read in, it is converted to a char array which is then used to generate the QR code.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This data then undergoes a series of mathematical functions in the 'generateQRcode' function before being saved to an array as ordered bytes of data.  For this data I opted to use the Alphanumeric mode of the QR code as it supports all numbers and uppercase letters as well as several key symbols such as $, %, *, +, -, ., / and :.  This easily allows the time and date to be presented to the user in a simple way, "09:57:35 - 08/10".  Because of the size of my display (24x24 pixels), I had to use a version 1 QR code (21x21 pixels) which limited the number of characters I could store.  Depending on the level of error correction used I could store 25,20,16 or 10 characters.  At this point in time I was unsure if a QR code scanner would be able to scan an LED display, so I opted for the highest level of error correction possible while still displaying the date and time.  This is type Q which can recover up to 25% of unreadable data.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  At this point the data is ready for the next step, masking.  The data mask is supposed to prevent situations arising that make scanning the QR code difficult, this is done by applying one of 8 data masks and then generating a score based on a series of tests.  The mask used is then included in the QR code so the scanner knows how to read the data.  Whilst applying the mask to the data was easy, I struggled with producing the scores from each mask.  This combined with the ATMEGA328p's lack of memory I gave up on trying to critically select the most appropriate data mask and instead select them sequentially.  Because the clock changes the code every second, if a code does come up that is unreadable due to the mask that's been applied, it is soon changed for one that is likely to be readable.  Once the data mask has been selected, this along with all of the other format data such as error correction type and mode is added into the bytes of data waiting to be positioned in the code itself.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Finally the matrix is cleared, the standard layout is added (location and orientation markers) and the data is filled in from the bottom right hand corner.  Once this has been done the bits are all inverted to make for an easier to scan QR code and this information is sent to the virtual buffer for the LED driver ICs using the Adafruit GFX library.  When all the data has been entered the command is given to shift the data out and the display is updated.  From here the process begins again, repeating itself indefinitely.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Below I have included a link to the Arduino code.  It is not the tidiest piece of code, but it does do the job and it is laid out in such a way that you should be able to understand its rough function from the description above.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Arduino):
  <a href="/s/QR_Clock_RTC.ino">
   QR Clock RTC.ino
  </a>
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The casing design was difficult for this build as originally I never intended to cover up the PCB, but rather have it on display for everyone to see.  This meant I didn't pay particular attention to certain features of the PCB such as the display being central and the power jack being accessible.  When I finally decided to make a case I wanted to ensure it was in keeping with the compact nature of the build, and therefore went with a thin walled 3D print with very tight tolerances.  This is something that worked very well for this project and consequently I went on to use the same idea for the bike speakers.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With a wall thickness of 0.8mm you would think it would be a very weak enclosure.  However because of the shape and the tight fit  with the ciruit board it is actually very tough in the areas it needs to be.  It is designed in 3 parts, the main structure, the lid and finnally a hook which glues to the lid.  The main structure has tabs inside too hold the PCB in such a position that the LED matrix lines up with the hole in the front.  There are then two holes in the bottom for power and a USB connection for reprogramming or control of the matrix via a computer.  Finally two protruding structures from each side allow the lid to be secured with self tapping screws.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The lid is separate not only so the board can be inserted but also to improve the quality of the print by reducing the amount of overhangs.  To ensure the lid fits cleanly it has a notch cut out of it all around the rim so it press fits into the main structure of the case.  There is also a slightly deeper part at the front to close up the gap made between the LED matrix and the lid.
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing5.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing6.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing1.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing2.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing3.jpg">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/QR+code+casing4.jpg">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads:
  <a href="/s/QR-Code-Clock-STL.zip">
   QR Code Clock - STL.zip
  </a>
  <a href="/s/QR-Code-Clock-Solid-Edge.zip">
   QR Code Clock - Solid Edge.zip
  </a>
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  So that's the story behind the QR code clock.  If I were to repeat this project then I might try and use a more accurate real time clock module, as it doesn't take long for it to get significantly out of sync.  Other than this minor detail it was a very successful project, below are some close ups of the finished device as well as a video of it in action.
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_5178.JPG">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_4904.JPG">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_4899.JPG">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_5181.JPG">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_4088.JPG">

<img src="{{ site.url }}/images/portfolio/qr-code-clock/IMG_5176.JPG">

