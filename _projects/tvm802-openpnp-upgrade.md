---
layout: post
hero-bg-color: '#FFFFFF'
uid: tvm802-openpnp-upgrade
title:  'TVM802 OpenPNP Upgrade'
tags: portfolio
---

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20191223_125624.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/Sponsored+by+PCBWay.png">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The TVM802 pick and place machine from QiHe is a great machine for the price.  I have put it through its paces with many assembly jobs totalling thousands of component placements.  However it does have its limitations, most annoyingly the lack of camera driver support for windows 10 but in general just an inability to customise the software to make minor improvements.  It should be noted that QiHe offer great support and constant software updates but this is something I want the machine to be less dependant upon.  The following project documents the upgrades I have made to the machine in the process of converting it to run
  <a href="https://openpnp.org/" target="_blank">
   <strong>
    OpenPNP
   </strong>
  </a>
  .
 </p>
</div>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The journey starts with the aforementioned camera grievances. The original TVM802 vision system uses a single USB RCA capture card with an analogue multiplexer to switch between up and down vision. For improved image quality and compatibility with openPNP both cameras were replaced with VC36USB100W devices. One of the major benefits of using OpenPNP for control of the machine is the integration of the OpenCV image processing library for component alignment. Therefore it felt like a good opportunity to improve the down camera lighting to complement this upgrade and hopefully significantly improve the machine’s placement accuracy in doing so.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  In an attempt to reduce the effect of reflections from the PCB, the machines original flat ring light was replaced with an angled ring light. In theory angling the ring light prevents light reflecting directly at the lens however in practice it did not completely solve the issue and it seemed diffusing the light source had a greater effect. Either way the design of the angled ring light threw up an interesting design challenge and a perfect use for flexible PCBs. I used
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  ’s flexible PCB service to prototype the design below in a double sided 0.1mm polyimide flex with black coverlay and pre-applied high temperature double-sided tape. The PCBs arrived on time and were of high quality, unfortunately the double-sided tape had not been applied however
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  quickly resolved the issue with me and I was able to manually apply the tape instead. As shown in the pictures I proceeded to assemble the PCBs with KA-5630SEL2Z4S high brightness red LEDs from Kingbright and then used the double-sided tape to form the board into its cone shape. Once this had been soldered to the base PCB and then mounted to the camera with standoffs it was ready to go!
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  As mentioned previously the design did not completely remove all the reflections from the image however the addition of a paper cone over the LEDs did lead to an even and well diffused lighting setup in the end.
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_093626.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_092438.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_093653.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_091355.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_183758.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_20200619_093532.jpg">

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  After using the first version of the new ring light for some time I realised there were some design changes that might improve its functionality.  Firstly, the original light had a dial to adjust the brightness, in retrospect this was very useful as it allowed the brightness to be tweaked without having to remove it from the machine and adjust resistor values!  I also realised that using a small number of very bright LEDs was not conducive to producing a well diffused light source, instead it would be better to use a large number of dimmer LEDs.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  To control the LED brightness I used a BCR 320U E6327 LED driver from Infineon with a thumwheel potentiometer to adjust the current limit.  This proves a very simple solution although it is important to take into consideration the power dissipation when driving large currents.  For the new LEDs I went with 72 0603 LEDs (TLMS1100-GS08 from Vishay), positioned on the same flex PCB as with the previous design.  Once again
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  <strong>
  </strong>
  provided the PCBs and as always they arrived incredibly quickly and looked great!  This time due to the increased number of LEDs the pick and place machine was called upon for assembly.  Unfortunately I neglected to add fiducials for this purpose so instead had to align the coordinate system using components, this is mad very easy using
  <a href="https://openpnp.org/" target="_blank">
   <strong>
    OpenPNP
   </strong>
  </a>
  though.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Once fired up the results are certainly better than the previous version, however additional diffusion is still needed and even with this on glossy white PCBs the individual LED reflections are still visible.  Most of the time
  <a href="https://openpnp.org/" target="_blank">
   <strong>
    OpenPNP
   </strong>
  </a>
  is able to identify the real board fiducial however it does also consider the LED reflections as fiducial like objects.  As with the previous version I have PCBs spare so if you want to try one yourself then please
  <a href="/contact-us">
   <strong>
    get in touch
   </strong>
  </a>
  <strong>
   .
  </strong>
 </p>
</div>


<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0020.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0012.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0008.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0018.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0017.jpg">

<img src="{{ site.url }}/images/portfolio/tvm802-openpnp-upgrade/IMG_0007.jpg">

