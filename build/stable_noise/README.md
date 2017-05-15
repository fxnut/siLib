# Stable Noise

Houdini scene file and scripts for generating si_noise.h which is used in siLib Turbulize Attribute SOP and siLib Turbulize VOP.


## Turbulize Attribute SOP

Lets you add noise to an attribute using one of 5 types of FBM based noise. The range of the noise is kept consistent regardless of the
values of octaves and roughness. It also avoids the issues that built-in noise nodes have for input positions located around {0, 0, 0}. 

This page also gives details on the corresponding VEX noise functions that you can use in your own VEX code.

### Noise Types

The table below shows the different types of noise available, and the corresponding Vex function that is being called. The <sig> token
designates the suffix that is used to name the overloads of each noise function according to input and output type. See below for more details.

| Displayed Name | siLib Function | Range |
|----------------|----------------|-------|
| Perlin | si_noise _&lt;sig&gt;_ | -1 -> +1 |
| Simplex | si_xnoise _&lt;sig&gt;_ | -1 -> +1 |
| Orig Perlin * | si_onoise _&lt;sig&gt;_ | -1 -> +1 |
| Sparse Convolution * | si_snoise _&lt;sig&gt;_ | -1 -> +1 |
| Alligator * | si_anoise _&lt;sig&gt;_ | 0 -> +1 |

    * These types of noise do not support Vector4 types as input. 
    The 4th component of frequency and offset will be greyed out.
    
    <sig> A two letter suffix designating the return type and input type
    e.g. "fv" means output type is _Float_, input type is _Vector3_. See below for more details.

All of the noise functions but one, are centered around zero and approximately cover the range from -1 to +1. In practice, you'll find
it rare for values to exceed &plusmn; 0.9.

Alligator noise is different in that you could consider it to be an abs(noise) function. In other words it is centered on zero with a 
range of -1 to +1, but any negative values are made positive to give the final range of 0 to +1. Note that this is very different from 
being a distribution that is centered at 0.5 and having a range of 0 to 1, as outlying values are less common

### VEX Noise Functions

The following VEX functions are made available so you can easily use these noise functions in your own VEX scripts. To use it, you 
need to import the "si_noise.h" file like this:

```
#include "si_noise.h"
```

    If you get errors including this file, check that your HOUDINI_VEX_PATH is set 
    (use hconfig on the Houdini command line) and make sure siLib is installed properly.

The code block below shows the prototypes for the VEX functions. Which input and output type you need will define which function
you need to use.

You'll notice that the last three noise types only support Vector3 types as input. The Turbulize Attribute node wraps these functions
for you to emulate support for the <code>ff</code> and <code>vf</code> signatures. 

```
// Perlin Noise

float  si_noiseff (  float pos, freq, offset; float rough; int octaves)
float  si_noisefv ( vector pos, freq, offset; float rough; int octaves)
float  si_noisefp (vector4 pos, freq, offset; float rough; int octaves)
vector si_noisevf (  float pos, freq, offset; float rough; int octaves)
vector si_noisevv ( vector pos, freq, offset; float rough; int octaves)
vector si_noisevp (vector4 pos, freq, offset; float rough; int octaves)


// Simplex Noise

float  si_xnoiseff(  float pos, freq, offset; float rough; int octaves)
float  si_xnoisefv( vector pos, freq, offset; float rough; int octaves)
float  si_xnoisefp(vector4 pos, freq, offset; float rough; int octaves)
vector si_xnoisevf(  float pos, freq, offset; float rough; int octaves)
vector si_xnoisevv( vector pos, freq, offset; float rough; int octaves)
vector si_xnoisevp(vector4 pos, freq, offset; float rough; int octaves)


// Orig Perlin Noise

float  si_onoisefv( vector pos, freq, offset; float rough; int octaves)
vector si_onoisevv( vector pos, freq, offset; float rough; int octaves)


// Sparse Convolution Noise

float  si_snoisefv( vector pos, freq, offset; float rough; int octaves)
vector si_snoisevv( vector pos, freq, offset; float rough; int octaves)


// Alligator Noise

float  si_anoisefv( vector pos, freq, offset; float rough; int octaves)
vector si_anoisevv( vector pos, freq, offset; float rough; int octaves)
```
        
