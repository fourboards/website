---
layout: post
uid: nixie-clock
title:  'Nixie Clock'
tags: portfolio arrows
---

<a href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5355.jpg">
<img src = "{{ site.url }}/images/portfolio/nixie-clock/IMG_5355.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Nixie tube clocks are very popular with hobbyists, although for a long time I wasn’t really sure why.  However when I finally saw a nixie tube in person I instantly worked it out and decided I had to make one.  I started searching ebay listings for enough tubes to make a clock, in the end I settled on the IN-14 tubes as they were of a reasonable size and not too expensive.   The only drawback of these tubes is the 5 is in fact just an upside down 2 but at just £30 for 6 this didn’t seem like to much of an issue.  This is how I went about the design and production of my nixie clock.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/nixie-clock/nixie-sch.png">
<img src = "{{ site.url }}/images/portfolio/nixie-clock/nixie-sch.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The schematic for this is fairly simple, I am using an AGTMEGA328 for control and several SN74141 high voltage BCD decoder ICs for driving the tubes.  Because the tubes operate at 170V you also need a boost converter, in my case I bought one from ebay (item 261169220982) to save the hassle of buying all the individual components.  I am also using an LM1117 to produce a 5V line to power the micro-controller and BCD decoder from the 12v input.  The input has to be 12v for the boost converter which is a bit annoying as it isn’t actually used for anything else.  Continuing from the left there is a header for a DS3231 real time clock which also has a battery backup to allow the time to be kept even when the clock is unplugged.  Then we have the driver circuitry; the tubes are multiplexed in a 3 way configuration meaning only 2 tubes are ever lit simultaneously.  This saves a lot of space on the PCB as well as saving some money on the fairly expensive SN74141.  However because the SN74141 driver ICs have open drain outputs we have to switch 170V at the anode of the tubes.  For this I am using a high voltage transistor array using MPSA92s and MPSA42s which allows fast enough switching to successfully multiplex the tubes together.  One thing that I learnt during prototyping this circuit on the breadboard was that’s its extremely important to use current protection resistors on the supply for the nixie tubes.  Unfortunately I learnt the hard way by blowing both ICs and costing me £5!  It is also extremely important to limit the current otherwise you risk significantly shortening the tubes lifespan.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/nixie-clock/image-asset.png">
<img src = "{{ site.url }}/images/portfolio/nixie-clock/image-asset.png">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  From the schematic I produced a PCB which would have the tubes soldered straight too it to reduce the wiring I would have to do later.  Whilst this makes the board more expensive it will save a lot of time later and also offers an excellent way to support the tubes mechanically.  Unfortunately due to eagles hobbyist limitations I was unable to design the board in one piece.  Instead I had to design it as two halves and then solder it together when I received the board.  Whilst this was quite frustrating it worked fairly well in the end, with me only having to add one flying wire to solve a slightly dodgy connection at the join.  As the you can see the top of each board is taken up completely with joining the tubes cathodes together.  This is where the multiplexing worked quite well as it meant all the tubes on one board were connected, preventing the need for too many connections to be made between the boards.  I then put the driver ICs at each end to keep them out of the way and then on one board the micro-controller and associated circuitry and on the other the power control circuitry.  As I mentioned before the 170V boost converter is an extra module which plugs into the main board, this has the added advantage of keeping the high frequency switching away from the sensitive digital electronics.  I did make a few mistakes on this board, mainly with the connection of the tubes to their associated transistor driver .  This meant I couldn't multiplex the tubes effectively and so I had to make some more flying wire connections, but hey it’s a prototype.  Finally the layout of the board positions the nixie tubes in pairs for seconds, minutes and hours with room for a small neon bulb between each set.  This later proved to be a massive nightmare because of how I installed it in the casing…
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Eagle CAD):
  <a href="{{ site.url }}/files/nixie-clock/Nixie_clock.sch">
   Nixie Clock.sch
  </a>
  <a href="{{ site.url }}/files/nixie-clock/Nixie_clock.brd">
   Nixie Clock.brd
  </a>
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/nixie-clock/image-asset.jpeg">
<img src = "{{ site.url }}/images/portfolio/nixie-clock/image-asset.jpeg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I wanted the casing to be simple and stylish to really accent the nixie tubes.  In the end I settled for using a large block oak and using the milling machine at school hollow it out making room for the control circuitry.  I then drilled 20mm holes in the top to allow for the 19mm nixie tubes to slide through.  I took extreme care when doing this bit to make sure the holes were central and evenly spaced as wonky holes are so annoying!  I also drilled holes for the little bulbs between each of the pairs of tubes however rather than drilling one large hole I opted for two smaller ones.  This allows the legs of each bulb to slide in from the top making the finished product look nicer.  However this meant every time I have had to remove the PCB since (all because of one issue I will explain later) I have had to de-solder the bulbs and worse of all when reassembling align both the hole in the wooden case and the 0.8mm hole in the PCB – very time consuming.  At the bottom of the case I milled out an extra ledge for an acrylic Lid to fit into.  I went for see through acrylic as I still wanted to be able to show people the circuitry but also prevent people electrocuting themselves on the 170V power line that runs all over the board.  By far the most annoying thing that happened in this project was when I was 10 minutes from finishing and I went and drilled the hole for the power jack in the front of the case not the back (demonstrated in the picture above), nightmare!
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I have had 3 versions of code for this project, the first was a very rough version which just displayed 123456 across the display to test the circuit was functional.  I then moved onto some more complex code which had an interrupt to keep the multiplexing of the tubes working and it was able to read the time from the RTC and display it accordingly.  However about a month later I went to fill in the hole in the front of the case with a 16mm latching switch and whilst trying to connect up the LED inside shorted out the 5V rail.  I then had to remove the whole PCB assembly from the case to replace the LM1117 from the back of the board and ever since the clock would function for about 30 seconds and then the processor would lock up.  Anyway I wasted a lot of time on it before realising the code was no longer working.  Weird as this was the code I thought I had been running for a month or so with no issues.  In the end I re-wrote the code without the interrupt and it worked fine.  So it works but it is certainly very bodged and by far not the ideal way of doing it.  Here are my 2 versions of the code, working and not working.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads (Arduino):
  <a href="{{ site.url }}/files/nixie-clock/Nixie_Clock.ino">
   Nixie_Clock.ino
  </a>
  <a href="{{ site.url }}/files/nixie-clock/Nixie_Clock_Test.ino">
   Nixie_Clock_Test.ino
  </a>
 </p>
</div>


<hr>

<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMG_5374.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5374.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMG_5377.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5377.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMG_5355.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5355.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMAG1340.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMAG1340.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMG_5372.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5372.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/nixie-clock/IMG_5356.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/nixie-clock/IMG_5356.jpg"></a>
    </div>
  </li>
</ul>
<br>


