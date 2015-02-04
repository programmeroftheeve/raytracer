/*************************************************************************************
**************************************************************************************
*** The MIT License (MIT)                                                          ***
***                                                                                ***
*** Copyright (c) 2014 Tim Bradt                                                   ***
***`                                                                               ***
*** Permission is hereby granted, free of charge, to any person obtaining a copy   ***
*** of this software and associated documentation files (the "Software"), to deal  ***
*** in the Software without restriction, including without limitation the rights   ***
*** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      ***
*** copies of the Software, and to permit persons to whom the Software is          ***
*** furnished to do so, subject to the following conditions:                       ***
***                                                                                ***
*** The above copyright notice and this permission notice shall be included in all ***
*** copies or substantial portions of the Software.                                ***
***                                                                                ***
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     ***
*** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       ***
*** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    ***
*** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         ***
*** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ***
*** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  ***
*** SOFTWARE.                                                                      ***
**************************************************************************************
*************************************************************************************/
#include <stdio.h>
#include <util/vector.h>
#include <util/usefulfunctions.h>
#include <rayTracerCore/ray.h>
#include <rayTracerCore/shapes/geometry.h>
#include <util/colors.h>
#include <util/imageio.h>
#include <rayTracerCore/light.h>
#include <rayTracerCore/material.h>
#include <getopt.h>

#define XRES 512
#define YRES 512
#define XBREAK 0
#define YBREAK 256
#define SAMPLES_X 1
#define SAMPLES_Y 1
#define SCENE 0
#define SHADING 0

#ifndef ANAGLYPH
#define ANAGLYPH 0
#endif
const light refLight = {.type = POINT, .ambinentFactor = .1f, .l.point = {.color = {1, 1, 1}, .location = {3, 5, -15}}};
const light sceneLight = {.type = POINT, .ambinentFactor = .1f, .l.point = {.color = {1, 1, 1}, .location = {0, 0, 0}}};
// const light sceneLight2 = {.type = POINT, .ambinentFactor = .1f, .l.point = {.color = {1, 1, 1}, .location = {-5.0f, 5.0f, 0}}};
const light sceneLight2 = {.type = POINT, .ambinentFactor = .2f, .l.point = {.color = {1, 1, 1}, .location = {0.0f, 10.0f, -4.0f}}};
light l;
vector3f shift = { .06f, 0, 0};
float xShift = .06f;
vector3f lookat = {0, 0, -2};
vector3f lookup = {0, 1, 0};
vector3f camPos = {0, 0, 1};
int buildRef = 0;
int toe = 0;
int xres = XRES, yres = YRES;
float width = 4, height = 4, viewPlaneDistance = 2;
char* file = "scene.png";



void writeImage(char *filename, int width, int height, char *data)
{
    imageio_info info_out;
    info_out.width = width;
    info_out.height = height;
    info_out.depth = 8;
    info_out.quality = 85;
    info_out.colorspace = sRGBColorspace;
    info_out.filename = strdup(filename);
    info_out.comment = NULL;
    info_out.type = CharPixel;
    info_out.map = "RGB";
    imageout(&info_out, data);
    free(info_out.filename);
}

void displayImage(char *filename, int width, int height, char *data)
{
    imageio_info info_out;
    info_out.width = width;
    info_out.height = height;
    info_out.depth = 8;
    info_out.quality = 85;
    info_out.colorspace = sRGBColorspace;
    info_out.filename = strdup(filename);
    info_out.comment = NULL;
    info_out.type = CharPixel;
    info_out.map = "RGB";
    imagedisplay(&info_out, data);
    free(info_out.filename);
}

void addToObjectList(object **list, object *newObject)
{
    if (*list == NULL)
    {
        *list = newObject;
    }
    else
    {
        object *tmp = *list;
        while (tmp->next != 0)
        {
            tmp = tmp->next;
        }
        tmp->next = newObject;
    }
}

void trace(const ray r, rayHit *rh, const object *objects)
{
    rh->hit = false;
    rh->mat = EMPTYNESS;
    rayHit testrh;
    testrh.hit = false;
    testrh.depth = rh->depth;
    float time = INFINITY;
    for (const object *obj = objects; obj != NULL; obj = obj->next)
    {
        float hitTime = 0;

        bool hit = obj->hit(r, obj, &hitTime, &testrh);
        if (hit)
            DEBUGOUT(printDepth(rh->depth);
                         printf("Hit: ");
                         printRayHit(testrh));
        if (hit && hitTime < time)
        {
            DEBUGOUT(printDepth(rh->depth);
                         printf("Replacing ");
                         printRayHit(*rh);
                         printf(" with ");
                         printRayHit(testrh));
            time = hitTime;
            *rh = testrh;
        }
    }
    if (rh->hit) DEBUGOUT(printf("\n"));


    if (rh->hit && rh->mat.reflect)
    {
        if (rh->depth > 10)
        {
            return;
        }
        ray reflect;
        vector3f offset = {};
        vector3f_scaleMul_new(offset, rh->normal, rh->offsetError);
        vector3f_add(rh->location, offset);
        reflectRay(&reflect, rh->location, rh->normal, r);
        rh->depth++;
        trace(reflect, rh, objects);
    }
}

void buildScene1(object **list)
{
    DPRINT("Building Scene\n");
    material refl = {.reflect = true, .color = {0, 0, 0}};
    material red = {.reflect = false, .color = {1, 0, 0}};
    material blue = {.reflect = false, .color = {0, 0, 1}};
    material white = {.reflect = false, .color = {1, 1, 1}};
    material color = {.reflect = false, .color = {1, 0, 1}};

    
    
    // Pri
    material priMat = {.reflect = false, .color = {.3, .6, .3}};
    vector3f priTop[3] = {
        { -1.158, .5f, -2.8116 },
        {  .174, 0, -1.015 },
        {  .811, .5f, -3.158}};
    vector3f priBottom[3] =  {
        { -1.158, -.5f, -2.8116 },
        {  .174, 0, -1.015 },
        {  .811, -.5f, -3.158}};
    vector3f priLeft[3] =  {
        { -1.158, -.5f, -2.8116 },
        {  .174, 0, -1.015 },
        { -1.158, .5f, -2.8116 }};
    vector3f priRight[3] =  {
        {  .811, .5f, -3.158 },
        {  .174, 0, -1.015 },
        {  .811, -.5f, -3.158}};
    addToObjectList(list, createTriangle(priMat, priTop[0], priTop[1], priTop[2]));
    addToObjectList(list, createTriangle(priMat, priBottom[2], priBottom[1], priBottom[0]));
    addToObjectList(list, createTriangle(priMat, priLeft[2], priLeft[1], priLeft[0]));
    addToObjectList(list, createTriangle(priMat, priRight[2], priRight[1], priRight[0]));
    
    // Spheres
    vector3f sph1Center = {0, 0, -1};
    float sph1Radius = .25;
    material sph1Mat = {.reflect = false, .color = {.5, .8, .5}};
    //addToObjectList(list, createSphere(sph1Mat, sph1Radius, sph1Center));
    
    vector3f sph2Center = {2, -1, -3.5};
    float sph2Radius = 1;
    material sph2Mat = {.reflect = false, .color = {.2, .4, .8}};
    addToObjectList(list, createSphere(sph2Mat, sph2Radius, sph2Center));

    vector3f sph3Center = {-2, -1, -1.5};
    float sph3Radius = 1;
    material sph3Mat = {.reflect = false, .color = {.8, .4, .2}};
    addToObjectList(list, createSphere(sph3Mat, sph3Radius, sph3Center));

    //back wall
    vector3f back1points[3] = {
        {-8, -2, -10},
        {8,  -2, -10},
        {8,  10, -10}};
    vector3f back2points[3] = {
        {-8, -2, -10},
        {8,  10, -10},
        {-8, 10, -10}};
    material backMat = {.reflect = false, .color = {.79, .79, .4}};
    addToObjectList(list, createTriangle(backMat, back1points[0], back1points[1], back1points[2]));
    addToObjectList(list, createTriangle(backMat, back2points[0], back2points[1], back2points[2]));

    //floor
    vector3f floor1points[3] = {
        {-8, -2, -10},
        {8,  -2, -0},
        {8,  -2, -10}};
    vector3f floor2points[3] = {
        {-8, -2, -10},
        {-8, -2, -0},
        {8,  -2, -0}};
    material floorMat = {.reflect = false, .color = {.5, .1, .5}};
    addToObjectList(list, createTriangle(floorMat, floor1points[0], floor1points[1], floor1points[2]));
    addToObjectList(list, createTriangle(floorMat, floor2points[0], floor2points[1], floor2points[2]));

    // right red triangle
    vector3f rightpoints[3] = {
        {8, -2, -10},
        {8, -2, -0},
        {8, 10, -10}};
    material rightMat =  {.reflect = false, .color = {.79, .79, .4}};
    addToObjectList(list, createTriangle(rightMat, rightpoints[0], rightpoints[1], rightpoints[2]));
    // left red triangle
    vector3f leftpoints[3] = {
        {-8, -2, -10},
        {-8, -2, -0},
        {-8, 10, -10}};
    material leftMat =  {.reflect = false, .color = {.79, .79, .4}};
    addToObjectList(list, createTriangle(leftMat, leftpoints[1], leftpoints[0], leftpoints[2]));

}

void buildScene2(object **list)
{
    DPRINT("Building Scene\n");
    material refl = {.reflect = true, .color = {0, 0, 0}};
    material red = {.reflect = false, .color = {1, 0, 0}};
    material blue = {.reflect = false, .color = {0, 0, 1}};
    material white = {.reflect = false, .color = {1, 1, 1}};

    // Spheres
    vector3f sph1Center = {0, 0, 0};
    float sph1Radius = 0;
    material sph1Mat = blue;

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    for(int i = 0; i < 10; i++)
    {
        float locationR = mapToRangef(((float)rand()/(float)(RAND_MAX)), 0, 1, 4, 18);
        float phi = (float) (mapToRangef(((float)rand()/(float)(RAND_MAX)), 0, 1, -180, 180) * M_PI / 180);
        float rnd = mapToRangef(((float)rand()/(float)(RAND_MAX)), 0, 1, .4, .96);
        float theta = acosf(2*rnd - 1);
        sph1Center[0] = locationR * sinf(theta) * cosf(phi);
        sph1Center[1] = locationR * cosf(theta);
        sph1Center[2] = -locationR * sinf(theta) * sinf(phi);
        sph1Radius = mapToRangef(((float)rand()/(float)(RAND_MAX)), 0, 1, .1, .5);
        sph1Mat.reflect = (bool) (rand() & 2);
        for(int x = 0; x < 3; x++) sph1Mat.color[x] = ((float)rand()/(float)(RAND_MAX));
        addToObjectList(list, createSphere(sph1Mat, sph1Radius, sph1Center));
    }

    //floor
    vector3f floor1points[3] = {
        {-8, -10+8, 10*2},
        {8,  -10+8, 10*2},
        {8,  -10+8, -10*2}};
    vector3f floor2points[3] = {
        {-8, -10+8,  10*2},
        { 8, -10+8, -10*2},
        {-8, -10+8, -10*2}};
    material floorMat = white;
    addToObjectList(list, createTriangle(floorMat, floor1points[0], floor1points[1], floor1points[2]));
    addToObjectList(list, createTriangle(floorMat, floor2points[0], floor2points[1], floor2points[2]));
}

void parseArguments(int argc, char **argv)
{
    while (1)
    {
        static struct option long_options[] =
            {
                /* These options set a flag. */
#if !ANAGLYPH
                {"ref",     no_argument,  &buildRef, 1},
                {"file",    required_argument,  0, 'f'},
#else
                {"toe",     no_argument,       &toe, 0},
#endif
                /* These options don’t set a flag.
                   We distinguish them by their indices. */
                {"xres",    required_argument,  0, 'x'},
                {"yres",    required_argument,  0, 'y'},
                {"width",   required_argument,  0, 'w'},
                {"height",  required_argument,  0, 'h'},
                {"shift",   required_argument,  0, 's'},
                {"dist",    required_argument,  0, 'd'},
                
                {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;
#if ANAGLYPH
        int c = getopt_long (argc, argv, "tx:y:h:w:s:",
                         long_options, &option_index);
#else
        int c = getopt_long (argc, argv, "x:y:f:h:w:",
                         long_options, &option_index);
#endif
        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'x':
                printf ("Final X Res: %s\n", optarg);
                xres = atoi(optarg);
                break;

            case 'y':
                printf ("Final Y Res: %s\n", optarg);
                yres = atoi(optarg);
                break;

            case 'w':
                printf ("View Width: %s\n", optarg);
                width = (float) atof(optarg);
                break;

            case 'h':
                printf ("View Height: %s\n", optarg);
                height = (float) atof(optarg);
                break;
            case 'd':
                printf ("View Dist: %s\n", optarg);
                viewPlaneDistance = (float) atof(optarg);
                break;
#if !ANAGLYPH
            case 'f':
                printf ("Output File: %s\n", optarg);
                file = optarg;
                break;
#else
            case 's':
                printf ("Camera Shift: %s\n", optarg);
                xShift = (float) atof(optarg);
                break;
            case 't':
                printf("Camera toed\n");
                toe = 1;
                break;
#endif
            case '?':
                /* getopt_long already printed an error message. */
                exit(1);
                break;

            default:
                abort ();
        }
    }
}

int main(int argc, char **argv)
{
    parseArguments(argc, argv);
    
#if ANAGLYPH
    if(!toe)
        xres = (float)(xres - 1)/(float)(1.0f - xShift / width);
    
    shift[0] = -xShift/2;
    vector3f_add(camPos, shift);
    shift[0] = xShift;
#endif
    
    char *image = calloc((size_t) (xres * yres * 3), sizeof(char));
#if ANAGLYPH
    char* left =  calloc((size_t) (xres * yres * 3), sizeof(char));
    char* right =  calloc((size_t) (xres * yres * 3), sizeof(char));
    char* i = right;
#else
    char* i = image;
#endif



    camera cam;
    setCamera(&cam, camPos, lookat, lookup);
    perspective p = {.cam = cam, .height = height, .width = width, .res_x = (unsigned int) xres, .res_y = (unsigned int) yres, .viewPlaneDistance = viewPlaneDistance};
    object *objects = NULL;
    
    do
    {
#if ANAGLYPH == 1
        if (buildRef)
        {
            i = left;
            vector3f_add(camPos, shift);
            if(!toe)
            {
                vector3f_add(lookat, shift);
            }
            setCamera(&cam, camPos, lookat, lookup);
            p.cam = cam;
            l = sceneLight2;
            file = "reference-left.png";
            buildScene1(&objects);
        }
        else
        {
            i = right;
            l = sceneLight2;
            file = "reference-right.png";
            buildScene1(&objects);
        }
        buildRef++;
#else
        //Build List
        if (buildRef)
        {
            buildRef++;
            printf("Rendering reference\n");
            l = sceneLight2;
            file = "reference.png";
            buildScene1(&objects);
        }
        else
        {
            buildRef++;
            continue;
            l = sceneLight;
            buildScene2(&objects);
        }
        
#endif
        

        for (unsigned int y = 0; y < p.res_y; y++)
        {
            for (unsigned int x = 0; x < p.res_x; x++)
            {
                if (x == XBREAK && y == YBREAK)
                {
                    volatile int b = 1;
                    b++;
                }
                sampler samples;
                getSampler(&samples, SAMPLES_X, SAMPLES_Y, p, x, y, GLOBAL);
                rayHit samplesRayHits[samples.numOfSamplesX * samples.numOfSamplesY];
                for (unsigned int sample = 0; sample < samples.numOfSamplesX * samples.numOfSamplesY; sample++)
                {
                    samplesRayHits[sample].depth = 0;
                    trace(samples.rays[sample], &samplesRayHits[sample], objects);
                    samplesRayHits[sample].objects = objects;
                    if (samplesRayHits[sample].hit)
                    {
                        float ambinentFactor = l.ambinentFactor;
                        float diffuse = getDiffuseFactor(samplesRayHits[sample], l);
                        float specular = getSpecularFactor(samplesRayHits[sample], l);
                        if (inShadow(samplesRayHits[sample], l))
                        {
                            DEBUGOUT(printf("In Shadow"));
                            diffuse = 0.0f;
                            specular = 0.0f;
                        }
                        DEBUGOUT(printf("Ambinent: %4.4f Diffuse: %4.4f Specular: %4.4f\n", ambinentFactor, diffuse, specular));
                        vector3f ambientColor = {}, diffuseColor = {}, specularColor = {};
                        vector3f_scaleMul_new(ambientColor, samplesRayHits[sample].mat.color, ambinentFactor);
                        vector3f_scaleMul_new(diffuseColor, samplesRayHits[sample].mat.color, diffuse);
                        vector3f_scaleMul_new(specularColor, samplesRayHits[sample].mat.color, specular);
                        vector3f_copy(samplesRayHits[sample].mat.color, ambientColor);
                        vector3f_add(samplesRayHits[sample].mat.color, diffuseColor);
                        vector3f_add(samplesRayHits[sample].mat.color, specularColor);
                    }
                }
                vector3f color = {};
                getFinalColor(color, samplesRayHits, samples.numOfSamplesX * samples.numOfSamplesY);
#define MIN(x, y) ((x < y) ? x : y)
                i[XY2INDEX(x, y, 0, xres, 3)] = (char) mapToRangef(MIN(color[0], 1), 0, 1, 0, 255);
                i[XY2INDEX(x, y, 1, xres, 3)] = (char) mapToRangef(MIN(color[1], 1), 0, 1, 0, 255);
                i[XY2INDEX(x, y, 2, xres, 3)] = (char) mapToRangef(MIN(color[2], 1), 0, 1, 0, 255);
#undef MIN
                cleanSampler(&samples);
            }
        }
        cleanObjectList(&objects);
        writeImage(file, xres, yres, i);
    } while(buildRef < 2);
    
#if ANAGLYPH == 1
    ///TODO Combine images
    float pixelWidth = getPixelWidth(p.width, p.res_x);
#define ABS(x) ( x < 0 ? -x : x )
    int shiftPixels = (!toe ? ABS(((shift[0] / pixelWidth) - 1)) : 0); 
    
    int newXres = xres - shiftPixels;
    int newSize = newXres * yres * 3;
    if(!toe)
    {
        char* newLoc = realloc(image, newSize);
        if(newLoc != NULL)
        {
            image = newLoc;
        }
        else
        {
            printf("\nExiting!!");
            free(image);
            free(left);
            free(right);
            exit(0);
        }
    }
    
    displayImage("testL.png", xres, yres, left);
    //displayImage("testR.png", xres, yres, right);
    for (unsigned int y = 0; y < yres; y++)
    {
        for (unsigned int x = 0; x < newXres; x++)
        {
            unsigned int leftX = x;
            if(!toe)
                leftX += shiftPixels;
            
            if( x == 444 && y == 783 )
            {
                volatile int s = 0;
                s++;
            }
            unsigned int rightX = x;
            unsigned int imageR = XY2INDEX(x, y, 0, newXres, 3);
            unsigned int imageG = XY2INDEX(x, y, 1, newXres, 3);
            unsigned int imageB = XY2INDEX(x, y, 2, newXres, 3);
            unsigned int leftRi = XY2INDEX(leftX, y, 0, xres, 3);
            unsigned int leftGi = XY2INDEX(leftX, y, 1, xres, 3);
            unsigned int leftBi = XY2INDEX(leftX, y, 2, xres, 3);
            unsigned int rightRi = XY2INDEX(rightX, y, 0, xres, 3);
            unsigned int rightGi = XY2INDEX(rightX, y, 1, xres, 3);
            unsigned int rightBi = XY2INDEX(rightX, y, 2, xres, 3);
            unsigned int leftR = (unsigned char)left[leftRi];
            unsigned int leftG = (unsigned char)left[leftGi];
            unsigned int leftB = (unsigned char)left[leftBi];
            unsigned int rightR = (unsigned char)right[rightRi];
            unsigned int rightG = (unsigned char)right[rightGi];
            unsigned int rightB = (unsigned char)right[rightBi];
            
            unsigned int leftGreyA = ((float)leftR + (float)leftG + (float)leftB)/3.0f;
            unsigned int rightGreyA = ((float)rightR + (float)rightG + (float)rightB)/3.0f;
            #define MIN(x, y) ((x < y) ? x : y)
            #define MAX(x, y) ((x > y) ? x : y)
            unsigned int leftGreyLight = ((float)( MAX(MAX(leftR, leftB), leftG) + MIN(MIN(leftR, leftB), leftG) )) / 2.0f;
            unsigned int rightGreyLight = ((float)( MAX(MAX(rightR, rightG), rightB) + MIN(MIN(rightR, rightG), rightB) )) / 2.0f;
            
            unsigned int leftGreyLu = .3f * (float)leftR + .59f * (float)leftG + .11f * (float)leftB;
            unsigned int rightGreyLu = .3f * (float)rightR + .59f * (float)rightG + .11f * (float)rightB;
            
            //printf("\t\tLu\t\tLi\t\tAve\nLeft:\t%f\t\t%f\t\t%f\nRight:\t%f\t\t%f\t\t%f\n\n",leftGreyLu, leftGreyLight, leftGreyA, rightGreyLu, rightGreyLight, rightGreyA); 
            
            image[imageR] = leftGreyLu;
            image[imageG] = rightGreyLu;
            image[imageB] = rightGreyLu;
        }
    }
    file = "referenceG.png";
    writeImage(file, newXres, yres, image);
    displayImage("testR.png", newXres, yres, image);
    
    for (unsigned int y = 0; y < yres; y++)
    {
        for (unsigned int x = 0; x < newXres; x++)
        {
            
            unsigned int leftX = x + shiftPixels;
            unsigned int rightX = x;
            unsigned int imageR = XY2INDEX(x, y, 0, newXres, 3);
            unsigned int imageG = XY2INDEX(x, y, 1, newXres, 3);
            unsigned int imageB = XY2INDEX(x, y, 2, newXres, 3);
            unsigned int leftR = left[XY2INDEX(leftX, y, 0, xres, 3)];
            unsigned int leftG = left[XY2INDEX(leftX, y, 1, xres, 3)];
            unsigned int leftB = left[XY2INDEX(leftX, y, 2, xres, 3)];
            unsigned int rightR = right[XY2INDEX(rightX, y, 0, xres, 3)];
            unsigned int rightG = right[XY2INDEX(rightX, y, 1, xres, 3)];
            unsigned int rightB = right[XY2INDEX(rightX, y, 2, xres, 3)];
            
            image[imageR] = leftR;
            image[imageG] = rightG;
            image[imageB] = rightB;
        }
    }
    file = "referenceC.png";
    writeImage(file, newXres, yres, image);
    displayImage("testR.png", newXres, yres, image);
    
    free(left);
    free(right);
#endif
    free(image);
    return 0;
}