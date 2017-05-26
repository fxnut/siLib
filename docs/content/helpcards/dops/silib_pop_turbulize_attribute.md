+++
draft = false
title = "siLib POP Turbulize Attribute"
description = ""

[menu.main]
parent = "silib_help_cards"
identifier = "silib_pop_turbulize_attribute"
weight = 200

+++

Lets you add noise to an attribute using one of 5 types of FBM based noise. The range of the noise is kept consistent regardless of the
values of octaves and roughness. It also avoids the issues that built-in noise nodes have for input positions located around {0, 0, 0}. 

For details on the corresponding VEX noise functions that you can use in your own VEX code, view the [siLib Turbulize VOP]({{< relref "silib_turbulize_vop.md" >}}) node.

## Noise Types

The table below shows the different types of noise available, and the corresponding Vex function that is being called. The <sig> token
designates the suffix that is used to name the overloads of each noise function according to input and output type. See below for more details.

| Displayed Name | Range |
|----------------|-------|
| Perlin |-1 -> +1 |
| Simplex |-1 -> +1 |
| Orig Perlin **\*** |-1 -> +1 |
| Sparse Convolution **\*** | -1 -> +1 |
| Alligator **\*** | 0 -> +1 |

\ 

{{% panel header="Notes" %}}
**\*** These types of noise do not support Vector4 types as input. 
The 4th component of frequency and offset will be greyed out.

{{% /panel %}}

All of the noise functions but one, are centered around zero and approximately cover the range from -1 to +1. In practice, you'll find
it rare for values to exceed &plusmn; 0.9.

Alligator noise is different in that you could consider it to be an abs(noise) function. In other words it is centered on zero with a 
range of -1 to +1, but any negative values are made positive to give the final range of 0 to +1. Note that this is very different from 
being a distribution that is centered at 0.5 and having a range of 0 to 1, as outlying values are less common


## Parameters

|   Name    | Description |
|-----------|-------------|
| Group | Subset of geometry to affect.|
| Group Type | Type of group. |
| Attribute Name | Name of the attribute to modify. There is no need to use the "@" symbol as a prefix, although it won't break if you do. Accepts names such as "P" or "Cd", "P.y", "Cd.x", etc. If the attribute doesn't exist, it will create it for you.|
| Attribute Class | What type of geometry the attribute is stored on. |
| Attribute Type | The data type of the attribute. |
| Update Normals | This checkbox only appears if you are modifying the point position P or a component of it (e.g. P.y). It lets you enable/disable the automatic recalculation of point normals after the attribute has been changed. |

#### Noise

|   Name    | Description |
|-----------|-------------|
| Noise Type | The class of noise to apply |
| Operation | Select whether to add or multiply the noise with the existing value of the attribute. |
| Frequency	| The frequency of the noise. By default, the y and z components are linked to the x component. For Perlin and Simplex noise, you can use the 4th component to set the speed of noise evolution when modifying the 4th component of the Offset parameter. For other noise types, the 4th component will be disabled as they don’t support 4 component inputs. |
| Offset | A vector to offset the center of the noise. Unlike some of the built-in noise nodes, you shouldn’t see any issues when position and offset values are set around {0, 0, 0}. Internally, this is achieved by reflecting each successive layer of noise in each axis. |
| Octaves | The number of layers of noise to apply. Each layer uses double the frequency of the previous layer. |
| Roughness	| Each layer of noise applied has its amplitude multiplied by this amount to progressively reduce the affect. A roughness of 1 means that each layer is applied with exactly the same amplitude as the first. A roughness of 0 will mean that only the first layer of noise has any affect. |
| Bias | Optionally allows you to control the distribution of the noise using a Bias shaping function. |
| Gain | Optionally allows you to control the distribution of the noise using a Gain shaping function. |

#### Amplitude

You can specify the size of the noise using two methods.

* **By Amplitude**: A multiplier on the noise value
* **By Range**: Fits the noise to the specified range. Note that Alligator noise will also be fitted to the full range, even though the original distribution
 is only from 0 to 1.

{{% notice tip %}}
If you are modifying a component of a vector attribute, then you need to use the matching component of amplitude. 
So for example, for **P.y** you need to use the **y** component of amplitude.
{{% /notice %}}

|   Name    | Description |
|-----------|-------------|
| Amplitude | The amplitude of each component of noise. |
| Min Range | The minimum value of each component of noise. |
| Max Range | The maximum value of each component of noise. |

#### Bindings

|   Name    | Description |
|-----------|-------------|
| Geometry | The name of the data on the DOP object that is storing the Geometry you want to modify. |
