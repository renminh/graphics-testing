on OpenGL

everything in GL is in 3D space but the screen/window is a matrix of pixels
a 2D array. Large part of OpenGL's work is to transform all 3D coordinates
to 2D pixels that fit on your screen

this is managed by the graphics pipeline

it can be split into two large parts
1. transform 3D coordinates into 2D coordinates
2. transform 2D coordinates into actual colored pixels

shaders are the programs that run directly on the GPU
