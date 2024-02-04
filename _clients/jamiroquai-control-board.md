---
layout: post
hero-bg-color: '#FFFFFF'
uid: jamiroquai-control-board
title:  'Jamiroquai Control Board'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170719_092749.jpg">
<img src = "{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170719_092749.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  <strong>
   Brief:
  </strong>
  To redesign an existing controller board for the Jamiroquai – Automaton project with enhanced reliability, ease of use and in a smaller for factor.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  <strong>
   Approach:
  </strong>
  Previous versions of the controller had used I2C multiplexing ICs to manage joysticks remotely with as few wires as possible.  However losing I2C communication through bad connections would cause the program to lock up and prevent all functionality of the LED helmet.  To overcome this we opted to use a different communication interface, SPI, in conjunction with reliable 74 series logic ICs to provide the same functionality without the possibility of lock ups.  To achieve the size restraints we opted to use tiny 0402 size resistors in conjunction with QFN logic ICs and some micro SMD joystick modules.  As the current controller boards were causing lock ups mid show this project was considered an emergency and the entire development stage through to final implementation was achieved in a matter of days.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  <strong>
   Outcome:
  </strong>
  5 highly reliable, tiny controller boards, as well as embedded c++ software library for easy implementation.  Each board provides 10 input channels over a 5 wire connection requiring just 3 IO pins for control.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170718_154342.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170718_154342.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170719_092716.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170719_092716.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170718_154041.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170718_154041.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170718_154410.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170718_154410.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170718_155541.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170718_155541.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url(/images/portfolio/jamiroquai-control-board/IMG_20170718_153951.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/jamiroquai-control-board/IMG_20170718_153951.jpg"></a>
    </div>
  </li>
</ul>
<br>


<iframe src="//www.youtube.com/embed/rmlmOk4ubcU?time_continue=1&wmode=opaque&enablejsapi=1" height="480" width="854" scrolling="no" frameborder="0" allowfullscreen=""><br/></iframe>

