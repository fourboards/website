---
layout: post
hero-bg-color: '#FFFFFF'
uid: swim-ring
title:  'Swim Ring'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/swim-ring/IMG_0346.jpg">
<img src = "{{ site.url }}/images/portfolio/swim-ring/IMG_0346.jpg">
</a>


<a href="{{ site.url }}/images/portfolio/swim-ring/Sponsored+by+PCBWay.png">
<img src = "{{ site.url }}/images/portfolio/swim-ring/Sponsored+by+PCBWay.png">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Swim Ring is a swimming tracker that is worn on the finger like a ring.  It includes two push buttons and a small LED screen to provide a simple user interface which can be used to track lengths and length times.  It was designed as a simple, compact alternative to the modern wrist worn fitness tracker and while it does not provide many of the insights these trackers do, it was a very interesting project that threw up many challenges.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  For such an integrated device a flex circuit is the obvious choice. I am a big fan of
  <a href="https://www.pcbway.com/flexible.aspx">
   <strong>
    PCBWay’s flexible PCB service
   </strong>
  </a>
  as the option to use stiffeners in combination with a thin flexible substrate provides a lot of’flexibility’ when it comes to design. With this in mind the main challenge becomes fitting everything in, display, buttons, battery and supporting circuitry.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Starting with the battery I originally looked at miniature Li-Ion packs, however finding these at a low price off the shelf and sufficiently small is not easy. Instead I found the LIR1220 which is still Li-Ion based with a nominal voltage of 3.7V but in a 12x2mm coin cell form factor and readily available. These are limited to a maximum discharge of 1C which with a capacity of ~12mAh equates to 12mA, however this is still workable as you will see shortly. The battery is now defining the ring PCB height to be at least 12mm, the final challenge comes in the form of how to connect it to the circuit. Since we have a flexible PCB we can easily fold the PCB around the battery to make contact on both sides - originally I intended to use an SMT coin cell holder with its feet folded over to then clamp the battery in place. Due to space constraints though this did not work and in the end I used conductive epoxy to secure the positive and negative terminals (I also tried with Z-tape however this proved unreliable).
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the battery decided and some dimensions already falling into place the next challenge was displaying the results. I did consider using a small BLE radio and a phone for interaction however this prevents viewing the data while still in the pool and is therefore no good. 0201 LEDs appeared to be the only way! In combination with my favourite LED driver, the IS31FL3731, I was able to form a 3x3 display of 5x3 characters using 141/144 of the LED outputs available. At this point the 12mA current limit is looking problematic, but these charlieplexed display drivers are very efficient and with some bright LEDs the display is very readable in sunlight while drawing &lt;10mA. This high density LED display is only made possible thanks to
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay’s
   </strong>
  </a>
  0.06mm track and gap rule and minimum drill and pad requirements of 0.15/0.35mm on flex circuits. Due to the circuit being only 0.1mm thick I was also able to place the vias in the LED’s pads, saving yet more space. Usually this would be a bad idea as on thicker boards the solder would wick into the via and leave no solder to mount the component, but with the hole only being 0.1mm deep and 0.15mm wide this is not an issue.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Buttons are next. They need to be very tactile so the user can feel the press and it must be possible to press them through whatever is used for encapsulating the device. This leaves one obvious choice in the form of metal dome switches. By this point I had enough information to design the board shape, I found an octagon design worked quite well with two different sized rigid section which you can see in the renders below. With the battery and display dictating the size of the larger sections, I found that an 8.4mm diameter metal dome switch fitted well and with two of these all of the larger sections were occupied.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  At the time of writing silicone was in short supply so the selection of an STM32 microcontroller was dictated by distributor stock levels, this ended up being a STM32G071 in a QFN28 package. The final critical part of the design is the battery charger. As the device must be fully sealed wireless charging is ideal however usually requires a lot of circuitry. I found the LTC4126EV-ADJ from Analog Devices which is a 7.5mA Wireless Li-Ion Charger with 1.2V Step-Down DC/DC Converter primarily designed for use in hearing aids. This part is ideal as it handles all of the wireless charging with the addition of only a few passives, it also incorporates a debounced on-off circuit for the 1.2V DC/DC converter which I used to enable/disable the 3V LDO and subsequently the entire circuit. I attempted to design a coil into the PCB however it ended up being too high in resistance and with the metal dome switch above was inefficient and produced a lot of heat. I also provisioned some pads for connecting an external coil which turned out to be a good decision.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the boards designed, I uploaded the files to
  <a href="https://www.pcbway.com/orderonline.aspx">
   <strong>
    PCBWay’s website
   </strong>
  </a>
  and selected the various options I required: 0.1mm polyimide, black coverlay, white silkscreen, metal and plastic stiffeners, ENIG surface finish, 1 oz CU and with high temperature Tesa tape applied.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/swim-ring/PCB.jpg">
<img src = "{{ site.url }}/images/portfolio/swim-ring/PCB.jpg">
</a>


<a href="{{ site.url }}/images/portfolio/swim-ring/PCB+Folded.jpg">
<img src = "{{ site.url }}/images/portfolio/swim-ring/PCB+Folded.jpg">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Amazingly these complex PCBs arrived in just 5 days and they looked great! I ordered quite a few boards which was very useful as it allowed for some experimenting. The first issue I ran into was soldering the 0201 LEDs, I was applying too much solder paste and they were floating on the solder and falling over during reflow. To fix this I ordered a new stencil with a thickness of 80um and with various aperture size reductions applied to the LED pad cut-outs. This did help although it did not fix the problem entirely as it becomes very difficult to apply a small enough quantity of solder paste due to it not releasing from the stencil. Further steps to try would be rounding the corners of the LED pad apertures and having the stencil electropolished but for now it is working well enough.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the LED assembly improved I populated all 141 LEDs and the rest of the components before reflowing the board. For once their were no shorts out of the oven and I proceeded with testing. After solving a charging issue caused by two resistors populated incorrectly the boards were fully working and I started writing the application for the STM32.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0368.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0368.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0300.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0300.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0229.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0229.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0236.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0236.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0242.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0242.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0232.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0232.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the electronics working I turned my attention to encapsulating the device. Initially I investigated using polyurethane resin for this purpose as it is commonly used for potting LEDs so is available in a clear formulation. This turned out to be a bad idea for several reasons: it is highly moisture sensitive meaning once a resin pack is opened it must be used immediately, it is fairly brittle once cured and it is dangerous to work with. I did try several castings with polyurethane resin however these all failed due to the aforementioned moisture sensitivity. The second material I found was a 40A shore hardness clear silicone from Smooth-On called SORTA-Clear 40. This material solved all of the issues I had previously, and I would highly recommend it for any similar applications.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Despite finding a great material to work with there were still a lot of challenges to overcome. I initially intended to cast the device in a silicone mould, however removing the finished casting without damaging it proved difficult especially as silicone sticks very well to silicone. My next attempt was a single-use 3D printed mould that could be cut away once the part had cured, this proved better, but it was difficult to get the fairly thick Silicone into the mould and the clarity of the cured silicone was affected by the 3D printing details. To solve the issue with the viscous silicone I first tried injecting it from below through a 3D printed spout but later reverted to injecting it through a relatively thick blunt needle. The issue with the optical clarity was solved using some 3M 1080 car wrap vinyl covering the sides of the 3D printed material - another great material! In all of these cases I was able to achieve full encapsulation by curing the silicone in two stages, first pouring a 1.5mm base then filling the rest and inserting the electronics. This works thanks to how well silicone sticks to itself.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the encapsulation step now worked out I was able to produce my first complete prototype. It had a strange issue where it would turn on with small movements or vibration. Initially I put this down to an issue with the switch used to trigger the on/off circuit however later identified it was caused by static charge generated by the silicone rubbing against the PCB. While silicone sticks very well to itself, it sticks very poorly to most other materials, this means that while the electronics are encapsulated, they are not stuck to the encapsulating material. This is another great advantage is it means the silicone can be removed without damaging the electronics. A quick firmware fix immediately switches the device back off in the event of a static charge triggering the on circuit.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0470.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0470.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0465.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0465.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0310.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0310.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0263.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0263.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0386.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0386.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0307.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0307.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Finally, the charger, this is a simple LC tank circuit driven by an N-Channel FET as detailed in the LTC4126 datasheet. It is powered by 5V USB Type C and includes a TI eFuse for protection. Another STM32G071 generates the 280kHz square wave used to drive the FET and also control some LEDs to indicate charging. In the original design I used a dual P/N-channel FET with the P-channel driving the coil and the N-channel driving the P-Channel, however this was not fast enough to switch at the required frequency. In the pictures below you can see the board modifications as well as the breadboard prototype, bare boards and finished charger.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0471.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0471.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0397.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0397.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0394.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0394.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0380.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0380.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0379.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0379.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0312.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0312.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  This ended up being a very successful project, the device serves its purpose and so far has remained functional after multiple swimming sessions. I am intrigued to see how long the waterproofing and flex circuit withstand the abuse of regular use. One change I would definitely make to the PCB is rounding the corners of the rigid sections, at just 0.3mm thick and metal they are very sharp and no match for the &lt;1mm thick silicone internal walls. Thanks to
  <a href="https://www.pcbway.com" target="_blank">
   PCBWay
  </a>
  for sponsoring this project, check them out at the link at the top of the page and enjoy the pictures of the finished product below.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0346.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0346.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0347.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0347.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0352.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0352.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0349.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0349.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0351.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0351.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/swim-ring/IMG_0348.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/swim-ring/IMG_0348.jpg"></a>
    </div>
  </li>
</ul>
<br>


