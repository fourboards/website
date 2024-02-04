---
layout: post
hero-bg-color: '#FFFFFF'
uid: touchpad-pro
title:  'TouchPad Pro'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1714.JPG">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/IMG_1714.JPG">
</a>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/Sponsored+by+PCBWay.png">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/Sponsored+by+PCBWay.png">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:right;white-space:pre-wrap;">
  <strong>
   <em>
    V2.0
   </em>
  </strong>
 </p>
 <p class="" style="white-space:pre-wrap;">
  This projects starts where
  <a href="/touchpad">
   TouchPad
  </a>
  left off.  Having created TouchPad to be a low-cost macro keyboard I wanted to take what I had learnt and build the ultimate macro keyboard.  To do this I wanted to incorporate the following features:
 </p>
 <ul data-rte-list="default">
  <li>
   <p class="" style="white-space:pre-wrap;">
    Display driven key labels
   </p>
  </li>
  <li>
   <p class="" style="white-space:pre-wrap;">
    Improved haptics (inspired by Apple’s Magic Trackpad)
   </p>
  </li>
  <li>
   <p class="" style="white-space:pre-wrap;">
    Improved interface for configuring macros
   </p>
  </li>
 </ul>
 <p class="" style="white-space:pre-wrap;">
  To achieve this I initially planned on using a full colour TFT touch screen, USB-C for power and data and solenoid like actuators for turning the whole display into a tactile surface.  This resulted in the prototype below which proved out the haptics but went no further.  The haptics are achieved by mounting the entire display on a thin piece of soft silicone to give it some compliance.  A pair of custom designed actuators are then used to pull the entire display towards a 3mm square mild-steel rod.  This provides the tactile click of pressing a real button.  I had provisioned for a controller board that could solder down to drive the screen and haptics but the design went in a different direction so this was never completed.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1681.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1681.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1680.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1680.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1683.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1683.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_20201110_204850.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_20201110_204850.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:right;white-space:pre-wrap;">
  <strong>
   <em>
    V3.0
   </em>
  </strong>
 </p>
 <p class="" style="white-space:pre-wrap;">
  The new direction was to make TouchPad Pro wireless, a feature that should definitely have been included from the start.  Consequently a large TFT screen was no longer feasible but also in hindsight this was likely unnecessary any way.  Instead I planned to use an e-paper display which has very low power consumption when static, ideal for this application as it will only be changed infrequently.  E-paper displays are becoming much more available but the only one I could find that included a capacitive touch screen was TP370PGH01 from Pervasive Displays.  This has a size of 3.7” (81x47mm) which comfortably fits 3x5 keys.
 </p>
 <p class="" style="white-space:pre-wrap;">
  As the screen is the main component in the device the change meant that the mechanics needed re-designing.  I decided to start once again by proving out the haptics first, before integrating all of the control electronics.  Another key change here was the integration of strain gauges to measure the force applied to the screen.  Previously I had intended to use a resistive touchscreen from which you can calculate an approximation of applied pressure however I never tested this and suspect the firmness of a capacitive touchscreen would provide better results in terms of haptics.  I was inspired by
  <a href="https://github.com/scottbez1/smartknob">
   scottbez1’s Haptic Smart Knob
  </a>
  which uses tiny BF350-3AA strain gauges glued to flextures in the PCB for this purpose.  I used 8 strain gauges to form two Wheatstone Bridges, one for each end of the PCB, which are read using a HX711 24-bit ADC designed for use in scales.
 </p>
 <p class="" style="white-space:pre-wrap;">
  The first test PCB also incorporates mounts for the haptic actuators in the form of SMT spaces from Wurth (9774015151).  Previously I used these to transfer power to the actuators but this was not ideal as the spacers had to be carefully isolated from the body of the actuators to prevent shorts.  In the new design I moved the actuator PCB to the bottom of the actuators so direct contact is made between pads on this board and the main board to transfer power.  Finally I added the display FFC connectors to test the cable routing.  I should have routed the key signals out to pin headers so I could test the display but I was in a rush to get the board out so this got missed.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/Schematics.png">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/Schematics.png">
</a>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/Layout.PNG">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/Layout.PNG">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  This project was sponsored by
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  who manufactured the PCBs and corresponding SMT stencil as well as providing these beautiful clear resin 3D prints.  The PCBs are 1mm thick standard FR4 with HASL finish and of the usual high quality produced by
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  .  The 3D prints are UTR-8100 translucent resin which was very useful for test fitting the mechanical parts and identifying any interference or tolerance issues with the design.  Due to the nature of the clear resin they are not the most dimensionally stable parts but they are exceptionally clear and great for showing off the internals of your project!
 </p>
 <p class="" style="white-space:pre-wrap;">
  The parts fitted together with some minor modifications to allow for design oversights.  This highlighted a few issues that will need to be fixed for the next iteration:
 </p>
 <ul data-rte-list="default">
  <li>
   <p class="" style="white-space:pre-wrap;">
    Not enough Z-height was left for bends in the FFC for the screen, this caused the PCB to be raised up at one end making for a non-level surface
   </p>
  </li>
  <li>
   <p class="" style="white-space:pre-wrap;">
    The use of silicone for the compliant mounts is not ideal as silicone does not adhere well to other materials.  This took a lot of work to find an alternative, but EMC gasket seems to work well for this as it can be glued in place and is filled with a compliant polyurethane foam
   </p>
  </li>
  <li>
   <p class="" style="white-space:pre-wrap;">
    It is not possible to adjust the positioning of the actuators once the case is closed - which is when this would need to be done.  Some holes will need to be provided in the base for this purpose.
   </p>
  </li>
 </ul>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1720.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1720.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1642.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1642.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1673.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1673.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1719.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1719.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1671.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1671.JPG"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  The finished assembly is shown below.  This enabled me to test the haptics which work very effectively and has highlighted some changes that are required to the mechanical design.  I plan to incorporate an ESP-32 into the next revision which will enable the bluetooth functionality and can hopefully provide a web interface for configuring macros.  The HX711 will also need replacing as although it provides two channels, they cannot be configured to have the same gain and it takes up a lot of space on the PCB.  Stay tuned for the next iteration.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1718.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1718.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1710.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1710.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1703.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1703.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1715.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1715.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_1714.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_1714.JPG"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:right;white-space:pre-wrap;">
  <strong>
   <em>
    V3.1
   </em>
  </strong>
 </p>
 <p class="" style="white-space:pre-wrap;">
  With the haptics proved out I moved onto adding the control electronics to the design. I used an ESP32-S3-MINI-1 module for control, the plan being for it to host a webserver for configuration and act as the BLE keyboard peripheral. As mentioned above the HX711 needed replacing as it doesn’t provide two channels with the same gain, the package is also quite large, and space is at a premium with this design. I opted to use the ADS131M02 from TI, it is a two-channel, 24-bit, 64-kSPS, simultaneous-sampling, delta-sigma ADC with programmable gain up to 128 like the HX711. I suspect this is overkill for the application, but I wanted to ensure I wouldn’t get caught out with a lack of resolution, it should provide very responsive and precise haptics.
 </p>
 <p class="" style="white-space:pre-wrap;">
  As the device is battery powered a battery charger IC is required, I found the BQ24232 also from TI which covers this but also has a nice feature called Dynamic Power-Path Management (DPPM). This automatically switches between USB power and battery power depending on the current draw while also charging the battery when the system is running from USB power. To complete the battery management circuit the MAX17048G+ fuel gauge IC from Maxim is used to track the batterie’s state of charge which can then be reported via BLE to the user’s device. To ensure the haptics have a constant feel as the battery voltage drops, a buck-boost is used to generate a constant voltage. This is another TI part, the TPS63802 as it has the option for a forced PWM mode, something I have found to be critical to avoid audible frequencies being generated when switching on and off the coils. Finally, an N-channel MOSFET is used to switch the haptic coils on and off, with flywheel diodes to prevent damage during switching.
 </p>
 <p class="" style="white-space:pre-wrap;">
  A simple flip-flop circuit provides a hardware power switch to minimise standby current. The push button used for this is also connected to the ESP32 for control. The ESP32 has an output that can be used to disable power to itself and the other circuitry.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/Layout+V4.0.PNG">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/Layout+V4.0.PNG">
</a>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  For the design to fit into the board outline designed above a 4-layer PCB is required. Layer 2 is used as a ground flood while Layer 3 is split between 3.0V and the coil power tracks. Layer 1 is the component layer with some low-speed vertical routing. Layer 4 has most of the routing including the impedance-controlled USB lines. The battery cut-out makes the board a challenge to route as most signals on the board must route through this region to reach the ESP32. The slot is required to avoid adding excess height to the device due to the size of the battery so it must be worked around.
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  PCBs have once again been provided by
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  as they continue to sponsor the project. The PCBs are 1mm thick standard FR4 with HASL finish as before but this time with 4-layers.
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  also manufactured some additional feet PCBs which will be glued to the main board using the EMC gasket as mentioned above. This will provide the conformal mechanical fastening, while the same SMT spacers as used for mounting the haptic actuators will allow the whole assembly to be mounted in the casing. The boards were complete after 3 days and they arrived 4 days later. I also had a solder paste stencil made which I used to assemble all the SMD parts to the board.
 </p>
 <p class="" style="white-space:pre-wrap;">
  Unfortunately, during the bring up of the boards I discovered that I had got the FFC connectors for the display the wrong way around, this made it very difficult to plug in and impossible to assemble in the case. Other than this and a few other small mods everything on the board worked as expected.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2028.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2028.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2017.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2017.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2024.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2024.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2027.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2027.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2020.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2020.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2023.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2023.JPG"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  As I started writing the firmware, I discovered a more fundamental issue with the design. The ESP32 was consuming around 80mA with the radio enabled, no good for a battery powered device. There are various sleep modes available, but it does not seem possible to reduce this power consumption while still maintaining a BLE connection. As a result, I have decided to switch to using an nRF52840 from Nordic Semiconductor. As a BLE focused device the power consumption is much lower, rarely exceeding 10mA. Another revision is required to fix the display connector issue so I will swap the controller out then, in the meantime I am working on a dev-board proof of concept with the nRF52840 to ensure there are no other problems ahead - something you should do for every project!
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2117.JPG">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/IMG_2117.JPG">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:right;white-space:pre-wrap;">
  <strong>
   <em>
    V4.0
   </em>
  </strong>
 </p>
 <p class="" style="white-space:pre-wrap;">
  Having completed the new proof of concept design I set about updating the main PCB to support the nRF52840.  I selected the MDBT50Q-1MV2 module from Raytac as it is low cost, compact and breaks out all of the GPIO pins.  Fortunately it is smaller than the ESP32 module used previously so only minimal changes were required, however it does not natively support programming over USB so I added a 1.27mm programming header which allows connection to the debugger output on Nordic development boards.  I took this opportunity to fix a few other minor issues with the previous design, mainly relating to the flip-flop circuit for enabling/disabling power and of course I also fixed the reversed display connector!  An RGB LED was also added, a missing feature that made debugging the previous revision very difficult.  Once the design was complete I exported gerbers from KiCAD and submitted to
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  <strong>
  </strong>
  for review.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2171.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2171.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2145.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2145.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2153.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2153.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2143.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2143.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2150.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2150.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2144.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2144.JPG"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  Just 8 days later the boards arrived complete with solder past stencil.  With the design further along this time I ordered the ENIG surface finish, once again in 1.0mm thickness and traditional green soldermask.  The boards and stencil are of high quality as I have come to expect from
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  .  I got the boards assembled and then fitted the battery, coils, strain gauges and display ready for testing.  Unfortunately Digikey shipped some incorrect parts first time around so the the fuel gauge had to be solder later on.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2176.JPG">
<img src = "{{ site.url }}/images/portfolio/touchpad-pro/IMG_2176.JPG">
</a>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  Bring up went without a hitch thanks to previous iterations and the work done with the Nordic development kit.  I 3D printed a new enclosure which incorporates some lessons learnt from the first iteration.  Unfortunately this is where I ran into a new issue, the display works perfectly while plugged into a computer USB port however as soon as it is unplugged it stops detecting presses.  This is down to a grounding issue common to capacitive touch sensors, the most reliable solution seems to be grounding the person using the device.  I have experimented with conductive 3D filament from ProtoPasta, making the case conductive achieves this as the buttons are far enough recessed that it is nearly impossible to press the screen without also making contact with the case.  This lends itself perfectly to making the case from Aluminium, hopefully the last step before finishing off the firmware and wrapping up the project.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:right;white-space:pre-wrap;">
  <strong>
   <em>
    V4.1
   </em>
  </strong>
 </p>
 <p class="" style="white-space:pre-wrap;">
  There were a few changes required for the design to work in metal. The base plate largely remained unchanged however now that the design was not being 3D printed I took the opportunity to add a recess to the bottom side for a silicone pad to fit into. I bevelled the external edges and the design was ready.
 </p>
 <p class="" style="white-space:pre-wrap;">
  For the top part of the case I tweaked some of the critical dimensions that had previously been causing assembly issues. I also had to redesign the retaining mechanism for the PCB. In the plastic version, the PCB was taped down to a third part which slotted into one wall and engaged with a clip feature on the opposite wall. This relied on a small amount of compliance in the plastic which would not work in metal! To minimise the number of external fasteners required I opted to replace the clip mechanisms with two M2.5 bolts that could be inserted after the PCB was installed on its mounting plate to hold it in place. I left these as 2.05mm holes so I could tap them myself. Like the base plate I added a bevel to the external edges to soften them up.
 </p>
 <p class="" style="white-space:pre-wrap;">
  Fortunately
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  don’t just offer PCB services so they offered to machine these parts through their CNC service. I decided to make the parts out of 6061 Aluminium, it is described as “the most popular aluminum alloy. It has good strength-to-weight ratio, excellent machinability and natural corrosion resistance”. This would mean I could relatively easily modify it with hand tools if required, it also meant I could make use of the electrically conductive anodised surface finish. This is important as using a non-conductive surface treatment would prevent the touch screen from working as discovered earlier.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2250.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2250.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2248.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2248.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2246.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2246.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2247.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2247.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_2249.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_2249.JPG"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  The full manufacturing process took 2 weeks as originally specified, and before long I had the parts as shown above. I was very impressed with the quality and pleased with how the surface finish turned out. I confirmed the parts were conductive and then moved on to tapping the two M5 holes - at the time of ordering I was not fully sure this was the route I was going to take otherwise I could have requested them to be tapped as part of the other machining operations.
 </p>
 <p class="" style="white-space:pre-wrap;">
  With the metal parts ready I was able to transfer the main PCB and feet PCB from the plastic enclosure.  Everything fit and the touchscreen worked flawlessly.  I spent some time optimising the firmware developed for the eval board and put together an HTML based button configurator page.  With this complete the project was ready for use.  I am very pleased with how this has worked out, the haptics feel like real buttons and the e-paper display provides high-contrast, wide viewing angles and no glare.  Having the project in a machined metal enclosure finishes it perfectly.  There is one outstanding issue, the standby battery life is very poor.  This requires further investigation before I can really make the most of this new tool.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3071.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3071.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3067.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3067.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3069.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3069.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3070.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3070.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3073.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3073.JPG"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/touchpad-pro/IMG_3068.JPG)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/touchpad-pro/IMG_3068.JPG"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="white-space:pre-wrap;">
  <br/>
 </p>
</div>


