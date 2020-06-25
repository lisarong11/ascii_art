# Ascii Art

 The software allow user to select 1 image from 3 and convert it to ASCII ART image. (present the image with ASCII characters)User can input their desired colour for background and font(by rgb value). The final image can be saved into bmp file with a user input name. 
 
---
#  Alogrithm Design

**Brightness Calculation** 

 This is the centre function for the whole source code. The main goal for the software is fill sub images with same brightness character.So without this function,all the code would not work.   For this part of code,I used the source code from gigi lab and put it in a counting loop and make this function return a interger value. I used to use the brightness=r+b+g/3 function,but I find the out put is more accurate with the brightness=0.212671f*r+0.715160f*g+0.072169f*b.   I used to struggle how to add all per pixel brightness together by counting loop ,but  I find out that using a increment in the loop can solve the problem with just one line.
 
**Character Brightness Table Optimization**

 Before writing the brightness optimization,I struggling with the font size of each single character because I think many blank would influence the final result.But after looking at the pasted link, I find out that the character brightness is not the final brightness use to map with sub images.It also need a table optimization to strecth it to a proper range from 0-255.When I compile without optimization,I couldnt print out a proper image

---
# Usage

1.please select the image you want to scaled to full screen( you can press backspcae going back to cover)

2.If you want to convert this full screen image,press g

3.please notice the note on terminal and wait patiently

4.please enter the rgb value for the colour you want for background and font in the format below and press enter: Background r, background g, background b,font r,font g,font b, please don't forget to input the comma

5.please notice the note on terminal,if it says present finished ,save your work,please press s.

6.please enter the name for the saved image,press enter after input name. (if it print image is saved before you enter the name,just press s again and it would be correct)

7.Finishied!you have saved a ASCII ART work.You can press Esc and click on the x button to quit.

---
# Reference

ref1: Dwight.H.Dwight Hooker.(1972).Lenna.[image] Available at:https://en.wikipedia.org/wiki/Lenna 

ref2:Reinbacher.R.Reinbacher.(2014).Canon EOS 40d.[image]Available at:https://pixabay.com/en/rose-flower-blossom-bloom-616013/

ref3:WhatdogRobot.W.WhatdogRobot.(unkown).Beagle.[image]Available at:https://www.what-dog.net/#results
