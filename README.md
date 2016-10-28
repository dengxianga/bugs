CUDA Rasterizer
===============

**University of Pennsylvania, CIS 565: GPU Programming and Architecture, Project 4** 

* Xiang Deng
* Tested on:  Windows 10-Home, i7-6700U @ 2.6GHz 16GB, GTX 1060 6GB (Personal Computer)

**Features:**

* Basic pipeline
  * Vertex assembly and vertex shader
  * Primitive assembly
  * Rasterization
  * Depth test
  * Fragment shader
  * Fragment-to-depth-buffer writing (with atomics for race avoidance).
  * A depth buffer for storing and depth testing fragments. 
* UV texture mapping with bilinear texture filtering and perspective correct texture coordinates
* Support for rasterizing additional primitives: lines and points

Milk truck | Duck
:-------------------------:|:-------------------------: 
![](imgs/milk1.gif) | ![](imgs/duck1.gif) 



VC
![](imgs/VC1.gif)

Cow with Lines | VC with Lines
:-------------------------:|:-------------------------: 
![](imgs/cow2.gif) | ![](imgs/VC2.gif)

Truck with Lines | Flower with Lines
:-------------------------:|:-------------------------: 
![](imgs/truck2.gif) | ![](imgs/flower.gif)

Duck with Points (dense) | Duck with Points (sparse)
:-------------------------:|:-------------------------: 
![](imgs/duck3.gif) | ![](imgs/duck4.gif)

Checkerboard with perspective correction | Checkerboard without perspective correction
:-------------------------:|:-------------------------: 
![](imgs/checkerboard.gif) | ![](imgs/checkerboard2.gif)

Checkerboard with bilinear filtering | Checkerboard without bilinear filtering
:-------------------------:|:-------------------------: 
![](imgs/checkwithbin.JPG) | ![](imgs/checkwithnobin.JPG)



Cow | Di|Engine | Buggy
:-------------------------:|:-------------------------: |:-------------------------:|:-------------------------: 
![](imgs/cow1.gif) | ![](imgs/di1.gif) |![](imgs/engine1.gif) | ![](imgs/buggy1.gif)

# Analysis


#PS: looking for models: just we & just tank



### Credits

* [tinygltfloader](https://github.com/syoyo/tinygltfloader) by [@soyoyo](https://github.com/syoyo)
* [glTF Sample Models](https://github.com/KhronosGroup/glTF/blob/master/sampleModels/README.md)
