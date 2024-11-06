# What is Opengl 

-> Opengl is typically called as an API but it is rather a specification that kronos specify on how such and such function's output should be displayed as. 
-> Since Opengl is a specification, the actual code or the implementation is done by the graphics card manufacturers like Nvidia, Intel and AMD.
-> So based on GPU architecture there are various implementation of these codes. But these differences in code will not hamper how the output for such and such function shows.

# Core-profile mode vs Immediate mode

They refer to the programming style in which opengl codes are written in. 
## 1. Immediate mode (Fixed function pipeline):

The mode is called immediate because you send individual vertex data to the GPU immediately as you call the corresponding function. Most of the functions were hidden inside the library and devs didn't have much control over them. Now the immediate mode is deprecated. In this mode functions you should start the program with `glBegin()`, give the vertices with `glVertex()` and end the program with `glEnd()`.

## 2. Core-profile mode:


