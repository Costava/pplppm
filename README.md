# Pixel Per Line Portable PixMap (pplppm)

Loads the image at the given path.  
Outputs the image to stdout as a P3 (ASCII) .ppm image with each pixel on its own line.  
The first 3 lines outputted are the .ppm header.  
Each color channel value is [0-255].

Returns 0 on success.  
On error, prints to stderr and returns greater than 0.

Dependencies:
- C99 standard library
- stb_image (included in `vendor` dir)

How many unique colors are in an image?  
Subtract 3 (due to .ppm header) from the number given by `./pplppm path/to/image | sort -u | wc -l`
