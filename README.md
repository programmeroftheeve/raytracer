Raytracer
=========
How to build:

mkdir build && cd build

cmake ..

make

Running
=======
./raytrace [--ref] [-x xres] [-y yres] [-h height] [-w width] [-d view dist]

Raytrace without arguments builds the reference.
The defaults for resolution is 512x512, and the dimensions of the image plane defualts to 4x4.

Anaglyph
========
Change #define ANAGLYPH 0 in main.c to 1
And then build

./raytrace [-x final xres] [-y final yres] [-w view width] [-h view height] [-s camera shift distance] [-d view dist] [-t|--toe]

Creates Left Eye and Right Eye images, as well as Greyscale and Color anaglyphs
Units are in meters

Defaults:
- Xres: 512 px
- Yres: 512 px
- View Width: 4 m
- View Height: 4 m
- View Plane Distnce: 2 m
- Camera Shift: .06 m
- Toeing: Disabled


