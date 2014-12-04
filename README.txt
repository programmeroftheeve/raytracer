Raytracer
=========
How to build: cmake . && make

Running
=======
./raytrace [--ref] [-x xres] [-y yres] [-h height] [-w width]

raytrace without arguments builds both the reference and a custom scene.
The defaults for resolution is 512x512, and the dimensions of the image plane defualts to 2x2.

The custom scene is consisted of 1000 randomly generated spheres of various materials and sizes, as well as a floor.
Materials are randomly generated to be reflective and have random colors.
This is used to show how the reflections work with a large amount of geometry.