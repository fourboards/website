---
layout: post
uid: diy-jbc
title:  'DIY JBC'
tags: portfolio arrows
---

<a href="{{ site.url }}/images/portfolio/diy-jbc/IMG_5667.jpg">
<img src = "{{ site.url }}/images/portfolio/diy-jbc/IMG_5667.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Having used a cheap soldering station for years and starting to embark on some more ambitious SMD projects I felt it was time for an upgrade to my soldering equipment.  However I did not want to pay the premium price tag for some premium equipment.  I started reading up about DIY soldering stations using the hand piece and tips from professional grade product lines, in my case JBC but also applicable to Hakko, Weller etc.  From my initial reasearch it seemed fairly achievable so I went ahead and ordered the necessary parts.  Here is how I went about making my DIY JBC soldering station.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/diy-jbc/Capture.jpg">
<img src = "{{ site.url }}/images/portfolio/diy-jbc/Capture.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This whole project was done in quite a rush so there was never time to properly draw up a schematic and produce a PCB.  My main inspiration for the circuit came from a combination of
  <a href="https://www.youtube.com/watch?v=UvH49nzpJts" target="_blank">
   GreatScott's
  </a>
  and
  <a href="https://www.youtube.com/watch?v=GYIiOkr6x9o" target="_blank">
   Marco Reps's
  </a>
  YouTube tutorials with a few tweaks to suit my personal requirements.  The above schematic is a modified version of GreatScott's schematic which adds the feature of a grounded tip and changes the pin numbers to match the Arduino code below.  A grounded tip is important when working with static sensitive components as it prevents the build up of electrical charge on the tip of the iron which can damage certain electronic components.  Having a grounded tip also gives an easy way to replicate the real JBC's sleep functionality.  For this a digital pin with an internal pull up is simply connected to the soldering iron stand, when the iron is placed in the stand the pin is pulled low and the Arduino can reduce the tip temperature.  This schematic does not include the control side of the project however the comments in the code explain how to connect the LCD, rotary encoder and sleep pins.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The concept of the above circuit is to sense when the AC voltage is at the zero crossing using the optocouple powered from the bridge rectifier.  At this point the Triac can be either switched on or off depending on how much power the soldering iron requires.  This ensures either half or full waves of AC power pass through the iron as apposed to methods such as phase angle control which can produce deformed power.  There is a thermocouple in the tip of the iron which is used to measure the tip temperature. This is one of the advantages of a premium soldering iron as an integrated thermocouple in the tip allows a much faster response to temperature change.  The thermocouple temperature is measured using a MAX6675 IC.  Whilst this IC is designed for K type thermocouples and JBC appear to be using a different variant of thermocouple, it still measures the temperature effectively and a linear correction can later be applied in software.  This is a relatively simple circuit for controlling an iron like this and whilst it works it is not the most efficient solution as I will discuss later.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  If you would like to build one of these I recommend watching the videos linked above and then considering using some of the parts I have used linked below in the project BOM.  I opted to use a powerful toroidal transformer to ensure a fast temperature response which was certainly achieved.  I also added a 3W embedded switch mode power supply from RS so there was no need for more than one socket to be used for power.  Finnally a large graphic LCD allows current and set temperature to be displayed as well as graphs mapping temperature and output power which I thought was a nice addition.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Excel):
  <a href="{{ site.url }}/files/diy-jbc/BOM.xlsx">
   BOM.xlsx
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  When it came to enclosing this project I wanted to keep it as compact as possible.  Using a toroidal transformer is possibly the least space efficient way to do this, so to make up for it I decided to enclose the entire project in a large acrylic tube matching the dimensions of the transformer.  This worked well and I managed to get the transformer wedged in the tube with no need for proper mounting.  I ordered some acrylic circles to match the outer diameter of the tube on ebay and then made cutouts for the LCD, switches and sockets myself.  I glued the rear panel in place permanently as I wanted to keep the mains part of the project well out of anyones way.  I then cutout and tapped three tabs to allow the front panel to screw into place with M5 machine bolts, allowing for easy maintenance and a solid enclosure.  With this finished I ordered some more acrylic tube on ebay along with some aluminium bar stock matching the inner diameter of the tube for use as an iron holder and tip cleaner .  The aluminium was tough to work but it had to be done as the tip holder needed to be metal for the sleep functionality to work.  With this all done I got everything connected together and started work on the code.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_131248.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_131248.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_163425.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_163425.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_191903.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_191903.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_130712.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_130712.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_160425.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170617_160425.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_153150.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170621_153150.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The below code was also inspired by GreatScott's initial code with a few bug fixes and some tweaks to the functionality.  Features I have added include the new display functionality as discussed earlier, a sleep function and some general improvements to the heating control providing a more constant temperature and faster temperature changes.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The code relies on a hardware interrupt to detect zero crossings of the AC waveform.  This takes priority over everything else as it is the main functionality of the iron, the GUI and everything else are stacked on top of this.  Because the thermocouple shares a connection with the heater, readings can't be taken at the same time as power is being applied and because of technicalities with the MAX6675 the heater has to be off for an amount of time before a stable reading can be taken.  To take all this into account a number of counters operate within the interrupt to ensure all of these conditions are met.  Every 40 mains cycles a temperature reading is taken and depending on the difference between set temperature and desired temperature a duty cycle specific to the difference is set.  This will allow a certain number of mains cycles to occur over the next 40 mains cycles.  This can limit how quickly the iron will heat up as power has to be removed every 40 mains cycles.  To account for this a prediction is made on how many cycles will be required to heat up the iron for large temperature changes, based on previous heating events, allowing less temperature readings to be taken and speeding up the temperature change.  This software combined with the hardware I am using allows for a T-245 cartridge to be heated from 20 degrees C to 350 degrees C in less than 10 seconds, not bad!
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Whilst temperature regulation is occurring a hardware interrupt also monitors the optical encoder, any movements on this immediately adjust the set temperature.  Other digital inputs that are monitored include the rotary encoder push button which when pressed allows the user to adjust the sleep mode temperature and also the sleep pin which changes the set temperature to the user defined sleep temperature when the tool is in its stand.  All of these user defined variables are saved to internal EEPROM when adjusted, meaning they remain unaltered even when power is removed.  A state machine style of coding is used to handle the various operating modes.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Download (Arduino):
  <a href="{{ site.url }}/files/diy-jbc/JBC_code.ino">
   JBC_code.ino
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This project has been very interesting and I have learnt a lot from it.  The iron works great as it is extremely powerful and has good temperature regulation.  I would definitely recommend it to any hobbyist looking for a premium soldering experience without paying the premium price tag.   However having used the iron for over a month I ended up buying a JBC station anyway, whilst my iron does the job it is missing valuable features such as the quick tip changing bracket and the reliability that comes with the JBC name.  I had initially thought I would be able use the station with the T210 tip and cartidge line too however it turned out to be too powerful and after having melted two tips I decided to bight the bullet and buy the real station.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121335.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121335.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121108.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121108.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170612_182834.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170612_182834.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121051.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121051.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121325.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121325.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121032.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/diy-jbc/IMG_20170622_121032.jpg"></a>
    </div>
  </li>
</ul>
<br>


