+++
draft = false
title = "siLib Turbulize Attribute SOP"
description = ""

[menu.main]
parent = "silib_help_cards"
identifier = "silib_turbulize_attribute_sop"
weight = 10

+++

Lets you add noise to an attribute using one of 5 types of FBM based noise. The range of the noise is kept consistent regardless of the
values of octaves and roughness. It also avoids the issues that built-in noise nodes have for input positions located around {0, 0, 0}. 

This page also gives details on the corresponding VEX noise functions that you can use in your own VEX code.

## Noise Types

The table below shows the different types of noise available, and the corresponding Vex function that is being called. The <sig> token
designates the suffix that is used to name the overloads of each noise function according to input and output type. See below for more details.

| Displayed Name | siLib Function | Range |
|----------------|----------------|-------|
| Perlin | si_noise _&lt;sig&gt;_ | -1 -> +1 |
| Simplex | si_xnoise _&lt;sig&gt;_ | -1 -> +1 |
| Orig Perlin **\*** | si_onoise _&lt;sig&gt;_ | -1 -> +1 |
| Sparse Convolution **\*** | si_snoise _&lt;sig&gt;_ | -1 -> +1 |
| Alligator **\*** | si_anoise _&lt;sig&gt;_ | 0 -> +1 |

\ 

{{% panel header="Notes" %}}
**\*** These types of noise do not support Vector4 types as input. 
The 4th component of frequency and offset will be greyed out.

_**&lt;sig&gt;**_ A two letter suffix designating the return type and input type
e.g. "fv" means output type is _Float_, input type is _Vector3_. See below for more details.
{{% /panel %}}

All of the noise functions but one, are centered around zero and approximately cover the range from -1 to +1. In practice, you'll find
it rare for values to exceed &plusmn; 0.9.

Alligator noise is different in that you could consider it to be an abs(noise) function. In other words it is centered on zero with a 
range of -1 to +1, but any negative values are made positive to give the final range of 0 to +1. Note that this is very different from 
being a distribution that is centered at 0.5 and having a range of 0 to 1, as outlying values are less common

## VEX Noise Functions

The following VEX functions are made available so you can easily use these noise functions in your own VEX scripts. To use it, you 
need to import the "si_noise.h" file like this:

```
#include "si_noise.h"
```
{{% notice tip %}}
If you get errors including this file, check that your HOUDINI_VEX_PATH is set 
(use hconfig on the Houdini command line) and make sure siLib is installed properly.
{{% /notice %}}

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

## Parameters

|   Name    | Description |
|-----------|-------------|
| Group | Subset of geometry to affect.|
| Group Type | Type of group. |
| Attribute Name | Name of the attribute to modify. There is no need to use the "@" symbol as a prefix. Accepts names such as "P" or "Cd", "P.y", "Cd.x", etc. |
| Attribute Class | What type of geometry the attribute is stored on. |
|Type | The data type of the attribute. |
| Update Normals | This checkbox only appears if you are modifying the point position P or a component of it (e.g. P.y). It lets you enable/disable the automatic recalculation of point normals after the attribute has been changed. |

#### Noise

|   Name    | Description |
|-----------|-------------|
| Noise Type | The class of noise to apply |
| Frequency	| The frequency of the noise. By default, the y and z components are linked to the x component. For Perlin and Simplex noise, you can use the 4th component to set the speed of noise evolution when modifying the 4th component of the Offset parameter. For other noise types, the 4th component will be disabled as they don’t support 4 component inputs. |
| Offset | A vector to offset the center of the noise. Unlike some of the built-in noise nodes, you shouldn’t see any issues when position and offset values are set around {0, 0, 0}. Internally, this is achieved by reflecting each successive layer of noise in each axis. |
| Octaves | The number of layers of noise to apply. Each layer uses double the frequency of the previous layer. |
| Roughness	| Each layer of noise applied has its amplitude multiplied by this amount to progressively reduce the affect. A roughness of 1 means that each layer is applied with exactly the same amplitude as the first. A roughness of 0 will mean that only the first layer of noise has any affect. |
| Amplitude	| The amplitude of each component of noise. |