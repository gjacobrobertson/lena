Lena
====

## Purpose
So for no apparent reason I thought it would be fun to play around with the famous [Lena test image](http://en.wikipedia.org/wiki/Lenna). The idea came to me one morning that it might be fun to apply image processing and computer vision algorithms to the Lena test image to create Andy Warhol-esque pop art. From that spawned a number of other ideas for other renderings based on the same test image. Hough transformations, linear filters, edge detection, contour analysis, etc

![Original Lena Image](/images/lena.jpg)

##Requirements
* g++
* pkg-config
* opencv

##Warhol
In a quick attempt to Warholify the image, I start by doing k-means clustering to segment the image, and then color the segments randomly.

    warhol images/lena.jpg images/warhol.jpg 3 4

![Warhol Panel](/images/warhol.jpg)

##Contour
This one is the result of finding some contours and filling them in with the average values of those contours.

    contour images/lena.jpg images/contour.jpg

![Contour](/images/contour.jpg)

