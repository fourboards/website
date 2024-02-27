---
layout: post
hero-bg-color: '#FFFFFF'
uid: bike-speakers
title:  'Bike Speakers'
tags: portfolio
---

<a href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4820.jpg">
<img src = "{{ site.url }}/images/portfolio/bike-speakers/IMG_4820.jpg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  A while ago I attempted to repair a Bose docking station which had given up on life by replacing the internal circuitry with a new amp from Sparkfun electronics.  Originally I had intended this to be a Christmas present for my sister, however I was too ambitious with the project trying to add all sorts of extra functionality.  This meant it never got finished on time and the whole thing was lost in a cupboard for quite some time.  Recently my sister was complaining about having to listen to music through her tinny phone speaker, so I decided to have another go at it.
 </p>
</div>


<hr>

<a href="{{ site.url }}/images/portfolio/bike-speakers/image-asset.jpeg">
<img src = "{{ site.url }}/images/portfolio/bike-speakers/image-asset.jpeg">
</a>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Here is the amplifier kit I bought from Sparkfun, it features an STA540 power amplifier which increases the volume of the music and allows larger speakers to be driven than the amp in a phone can.  For just under £20 it has been very good, however it does not produce the highest quality sound and static can be heard over the music when the volume is turned down low (I tried adding filtering caps but it made little difference).  There were also several changes that had to be madefor it to suit my needs: firstly the heat sink was far to big to fit in a compact case so I replaced it with one of half the height from an old Dell PC, I also replaced the two volume pots with a single dual pot to ensure the channels are always evenly balanced and finally I removed the two on board LEDs and replaced them with a permanently on RGB LED which produces a turquoise colour.
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Whilst the electronics are fundamental in this project, most of my time was focused on the CAD design of the casing.  I started off designing the bike shape that the speakers would be a part of.  This was fairly easy as I used a picture of a bike to get the rough outline and then I made a few changes to ensure the 3D print would work well.  This included joining up the handlebars with the main frame and making a few of the thinner areas slightly thicker.  I also added an 8mm hole on the underside of the cranks for connection to the base and finally some 'ears' on each corner of the bike to stop the print from warping.  These 'ears' are 20mm discs which are 0.2mm thick (one printed layer) adding lots of extra surface area whilst still being very easy to remove afterwards.  The print came out very well and the only touch up work that was required was the removal of the ears and slight sanding of the speaker mounts to ensure a tight fit.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Next I started work on the base, this was the hardest part of the project as I wanted it to be very compact.  In the end I opted for a two part design, a functional base with all of the mounting holes underneath and the structural support for the bike with a thin walled cuboid cover to ensure the final product looked good too.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I started on the structural component first making it so the amplifier could slide in underneath the main support for the speaker assembly.  This meant the walls of the main support had to be relatively thick and printed with a high fill density.  The first print of this was printed too cold with a feed rate that was too high causing it to be brittle and not fit for purpose.  I used this opportunity to do a test fit and found several areas were measurements needed to be altered slightly.  On the next attempt I slowed the printer right down and set the hot end to a higher temperature (230 degrees Celsius).  This worked much better and the slight changes to the design paid off as print number two came off the print bed needing no modifications.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Work then started on the cover, I designed it to be a perfect fit in CAD meaning when it was 3D printed and it shrunk slightly it would not require and further securing to the structural part of the case.  I added holes to line up with the IO on the base part of the case and a wave cut out on the front of it to allow the volume knob to be preinstalled.  It was printed upside down with a wall thickness of 0.8mm which is surprisingly strong and in this particular case worked very well.
 </p>
 <p class="" style="text-align:center;white-space:pre-wrap;">
  I was able to simulate the assembly of all the parts in CAD before I started printing 3D printing which was very useful, below are some renders I produced as well as an interactive 3D model of the product.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers1.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers1.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers4.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers4.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers5.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers5.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers3.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers3.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers2.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers2.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/Complete+Speakers.jpg"></a>
    </div>
  </li>
</ul>
<br>


<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Downloads:
  <a href="{{ site.url }}/files/bike-speakers/Bike_Speakers_STL.zip">
   Bike Speakers - STL.zip
  </a>
 </p>
</div>


<hr>

<div class="sqs-html-content">
 <p class="" style="text-align:center;white-space:pre-wrap;">
  Here is the finished product, I am very pleased with how the casing turned out as it remained small and compact but does not compromise functionality in any way.  Using the transparent black between the two blue plastic parts really enhances its look, and the turquoise light shining through provides the finishing touch.   The electronics inside could produce a nicer sound but my sister is very pleased with it as they still sound significantly better than her phone speakers.
 </p>
</div>


<ul class="projects clearfix">
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4823.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4823.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4821.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4821.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4829.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4829.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4824.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4824.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4818.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4818.jpg"></a>
    </div>
  </li>
  <li>
    <div class="project" style='background-image: url({{ site.url }}/images/portfolio/bike-speakers/IMG_4813.jpg)'>
      <a class="cover" href="{{ site.url }}/images/portfolio/bike-speakers/IMG_4813.jpg"></a>
    </div>
  </li>
</ul>
<br>


