---
layout: post
hero-bg-color: '#FFFFFF'
uid: bascetta-star-light
title:  'Bascetta Star Light'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7798.jpg">
<img src = "{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7798.jpg">
</a>


<a href="{{ site.url }}/images/portfolio/bascetta-star-light/Sponsored+by+PCBWay.png">
<img src = "{{ site.url }}/images/portfolio/bascetta-star-light/Sponsored+by+PCBWay.png">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  A Bascetta star is a 20 point origami star named after Italian maths professor Paolo Bascetta its creator.  By making the star out of a translucent paper it can be lit from the inside to make a nice decoration.  There are many kits available for this which include a short string of fairy lights for illumination, this can be improved!  Both the external and internal geometry is intriguing and lends itself well to a 3D PCB project.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  As you can see from the pictures on this page, the internal geometry of the Bascetta star, and therefore the shape for the light is a 20-sided polyhedron, or icosahedron.  This shape can be formed from 20 identical equlateral triangles, by placing an LED in the centre of each you get a light source for each point of the star.  It therefore makes sense to create a triangular PCB that can be assembled into the icosahedron shape, with the use of castellated holes the necessary electrical and mechanical connections can be made between 20 common PCBs.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  The circuit for this project is very simple, each PCB has a single RGB LED with an optional 4 pin header on the rear for power.  For the first prototype I decided to use an off the shelf RGB controller, these are very common and come in bluetooth and IR variants, they have a common pinout (Vdd, G, R, B) which matches the 4 pin header.  For individual colour control of each point, the standard RGB LEDs could be replaced with NeoPixel style ones and an appropriate controller.  A single controller is sufficient to drive the whole star, so the connections from the 4 pin header on 1 PCB must be routed out to the other 19 boards.  This is achieved with a carefully selected pinout for the castellated holes which is symetrical about the centre of each edge and identical on all edges.  This means the pinout matches between two triangles in any orientation, although not all joints are required for connection as this pinout creates a lot of duplication.
 </p>
</div>


<a href="{{ site.url }}/images/portfolio/bascetta-star-light/PCB+2D.jpg">
<img src = "{{ site.url }}/images/portfolio/bascetta-star-light/PCB+2D.jpg">
</a>


<a href="{{ site.url }}/images/portfolio/bascetta-star-light/PCB+3D.jpg">
<img src = "{{ site.url }}/images/portfolio/bascetta-star-light/PCB+3D.jpg">
</a>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  PCB and stencil manufacture was done by
  <a href="https://www.pcbway.com">
   <strong>
    PCBWay
   </strong>
  </a>
  , the PCBs are relatively standard 1.6mm FR4 but with white soldermask and castellated holes.  I ordered 50 boards, enough for two and a bit stars, and had them on my bench 10 days later.  I started with a test board to check connectivity with the RGB controller before assembling a full 20 boards.  As always the PCBs were of excellent quality, the whilte soldermask with HASL finish produced a very nice look.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0832.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0832.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0840.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0840.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0838.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0838.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0830.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0830.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0834.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0834.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0835.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0835.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  With the PCBs assembled I set about creating the full icosahedron assembly.  I started with a rough test piece out of paper before trying with the actual boards.  I ended up taping the net together with kapton tape so I could assemble the entire shape before creating any rigid joints, this worked well as some fine adjustment were needed to get everything lined up.  At this point I started filling the castellated holes between faces with solder to form the mechanical and electrical connections required.  I left two faced detached so the RGB controller and wiring could be installed.  With this done and a USB plug connected to the power lead it was ready for a test, and it worked first time!  I finished up by soldering the last two panels in place and cleaning off all the flux residue.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0859.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0859.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0847.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0847.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0879.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0879.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0846.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0846.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/274989300_635846514383046_4896757359245013514_n.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/274989300_635846514383046_4896757359245013514_n.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_0843.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_0843.jpg"></a>
    </div>
  </li>
</ul>
<br>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I am very pleased with the finished piece, in fact it feels a shame to conceal it within the Bascetta star it was originally intended for!
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_7798.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7798.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_7801.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7801.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_7807.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7807.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_7809.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7809.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/IMG_7804.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/IMG_7804.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bascetta-star-light/275026423_670457897473879_3186137048368127375_n.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bascetta-star-light/275026423_670457897473879_3186137048368127375_n.jpg"></a>
    </div>
  </li>
</ul>
<br>


