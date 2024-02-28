---
layout: post
hero-bg-color: '#FFFFFF'
uid: led-card
title:  'LED Card'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/led-card/IMG_5059.jpg">
<img src = "{{ site.url }}/images/portfolio/led-card/IMG_5059.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  When the electronics teacher at my school left after having taught me through various clubs, lessons and extra curricular activities I felt it appropriate to thank him for all his hard work with one of my signature LED cards.  However things quickly got out of hand and I found myself designing a 20x10 LED matrix to be the centrepiece of the card.  Because of the time frame I had, prototyping was not an option and I was forced straight into the PCB design followed by a very long circuit board manufacture process.  Unfortunately due to the time pressure once again I failed to photography most of the process so this write up will focus mainly on the design work and programming that went into the project.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/led-card/image-asset.png">
<img src = "{{ site.url }}/images/portfolio/led-card/image-asset.png">
</a>


<a href="{{ site.url }}/images/portfolio/led-card/image-asset.png">
<img src = "{{ site.url }}/images/portfolio/led-card/image-asset.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Here is the schematic and circuit board design, for this explanation I will focus on the PCB itself but everything can also be related to the schematic above.  The circuit board be split into 3 main parts, power, display and control circuitry.  For power I opted to use a 3.7v 1100mAh LiPo battery as it is light enough and thin enough to fit in the envelope and it can easily supply the current required for the display.  This battery connects to the main header (SV1) in the bottom middle of the board where it is then redirected to via the switch on the left (SV4) to the step up transformer (SV2).  The step up transformer takes the 3.7V supply from the battery and produces a 5V power rail for the main circuit to run off.  The other circuitry in this corner of the board is the charging circuit for the battery which is powered via a mini USB socket, ensuring the card does not go to waste when the battery inevitably dies.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  To the right of the charging circuit is the main control circuit.  It is powered by an ATMEGA328 running an arduino bootloader and programmed via the main header (SV1) using a USB to TTL Serial converter and the arduino IDE.  It runs at 16MHZ which is more than sufficient to maintain a good refresh rate on the display.  For inputs the header SV3 breaks out 4 capacitive touch channels, which whilst only 1 was used in this project offers expandability for the future.  These channels use the
  <a href="http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense" target="_blank">
   Capacative Sensor
  </a>
  library for code and two digital IOs, one connected in series with a 1M resistor and the other with a 22uF capacitor to produce a reading.  The one channel that is used triggers the display meaning it starts the scrolling message as someone picks it up.  To produce the scrolling message there are then 3 shift registers (HC74LS595D) controlling the columns and 10 FETs (2N7000) controlling the rows.  Current limiting resistors protect the LEDs and the FETs by being position on the shift register side of the LEDs and the gates of the FETs accordingly.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Finally there is the display, comprised of 200 SMD0603 green LEDs.  The use of surface mount parts in this project allows the display to be very low profile and the control circuitry to be very compact.  As I mentioned earlier the board had to be home made due to the time restrictions, which isn't a major problem as I have now made many double sided PCBs at home.  However the 272 vias that each had to be connected using wire did take quite some time and it is definitely something that I will not be doing again in a hurry!
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Eagle CAD):
  <a href="{{ site.url }}/files/led-card/Board.sch">
   LEDCard.sch
  </a>
  <a href="{{ site.url }}/files/led-card/Board.brd">
   LEDCard.brd
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The code required to run the display is relatively simple, it comprises of 3 main layers, the animation code, interface code and control code.  There are a number of subroutines which simplify the animation code to form the interface code, these allow individual LEDs to be switched on and off (setPixel) and have there state returned (readPixel) as well as the whole display being cleared (displayClear).  All of these sub routines simply set or read the state of the LEDs in question to or from a boolean array.  Below is the code which produces scrolling messages.  Characters are predefined in a variable called alphabets and this routine simply organises the letters on screen and uses the interface commands to display the message.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/led-card/image-asset.png">
<img src = "{{ site.url }}/images/portfolio/led-card/image-asset.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  A timer interrupt on timer 1 has a frequency of 600hz.  During each interrupt the row FETs are all switched off, the shift registers are set according to the boolean array for the LEDs and then the next row's FET is switched back on.  This means the display refreshes at a rate of 60Hz which is standard for many computer monitors.  Data is sent to the shift registers via SPI which involves the latch pin being pulled high, 3 bytes of information being shifted out (1 byte for each register) and then the latch pin being pulled low again to signal the end of the transfer.  A variable called rowcount is then incremented to ensure the next row is switched on next time the interrupt fires.  This technique of controlling LEDs in rows and colums is called multiplexing and is how other projects such as the
  <a href="{{ site.url }}/new-page-1">
   QR Code Clock
  </a>
  and
  <a href="{{ site.url }}/rgb-led-cube">
   RGB LED Cube
  </a>
  work.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/led-card/Code1.png">
<img src = "{{ site.url }}/images/portfolio/led-card/Code1.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  These whole operation is then coordinated from the main loop.  This continually checks the value of the capacitive sensor and when someone triggers it by picking the card up a series of animations are triggered.  This includes the scrolling messages and a final animation that involves random LEDs being switched on and off rapidly that continues until the card is physically switched off.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Arduino):
  <a href="{{ site.url }}/files/led-card/Card_SPI.ino">
   Card_SPI.ino
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  To see this last piece of code in action here is a short video of the card working.  As you can see I ended up mounting the PCB straight to the card as I felt it was worthy of being seen and I found an electronic themed backdrop which ends up giving quite a nice effect.
 </p>
</div>


<iframe src="//www.youtube.com/embed/uXhqPxu4wf8?wmode=opaque&enablejsapi=1" height="480" width="854" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

