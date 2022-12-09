# Development Documentation
## Basics
### Technologies
The software is compiled as a plugin for a commercial 3D graphics software [SideFX Houdini](https://www.sidefx.com). Main programming language of the project is C++ 17. The only external library used for this project is the [Houdini Development Kit](https://www.sidefx.com/docs/hdk/) which is used by the developers at SideFX to develop Houdini.

Build system used for the project is [CMake](https://cmake.org). For more information about compiling Houdini plugins you can visit [HDK: Compiling HDK Code](https://www.sidefx.com/docs/hdk/_h_d_k__intro__compiling.html).

### Algorithms
#### Path Tracing
The core algorithm of the renderer is pathtracing, which is described in multiple articles and books (e.g. books mentioned in the resources sections).

Notable modification to the algorithm is that, light sources aren’t treated as geometry, but are treated as separate entities. During the computation of intersection point algorithm choses one of the lights (uniform probability) and generates sample on the light surface (also uniform probability). The sample is then used to compute direct illumination at the point.  This can be seen in the file `PhysicallyBasedRenderer.cpp` int the method `ComputeDirectIllumination`.


### Resources
Resources used during implementation are the following lectures and books.
#### Books
- [Fundamentals of Computer Graphics](https://www.goodreads.com/book/show/1933732.Fundamentals_of_Computer_Graphics)
- [Physically Based Rendering: From Theory to Implementation](https://www.pbr-book.org)
- [Ray Tracing Gems Series](https://www.realtimerendering.com/raytracinggems/)

#### Lectures
- [Fotorealistická grafika (NPGR004)](https://cgg.mff.cuni.cz/lectures/npgr004.cz.php)
- [Advanced 3D Graphics for Movies and Games](https://cgg.mff.cuni.cz/courses/advanced-3d-graphics-for-movies-and-games/)

## Compilation
### Compilation scripts

### Environment variables

### Setting up IDE
You should set variables in `HFS` and `CMAKE_PREFIX_PATH` in the `CMakeLists.txt` if you want your IDE to be able to load the project.



## Basics
### Technologies


### Resources

- Program is compiled as a houdini plugin
- Program uses HDK for some of its computations
-

### Project Structure
Projects root folder contains the following folders and files
**`/Compilation`**
This folder contains things related to debuging and compilation.

**`/Documentation`**
This folder contains detailed documentation.

**`/Samples`**
This folder contains sample houdini files to test out the plugin.

**`/Sources`**
This folder contains source code for the plugin itself.

### Build and debug

### Terms
#### Material
Materials are classes derived from the `Material` class that are keepable of evaluating texture data at a certain point in space. The texture data is then used to drive appearance of the object via BxDFs.

#### BxDF

#### 



## Source Code Structure
The project code is divided into two main parts - `Source/Core` which contains code that is used by the rendering algorithm  itself and `Source/Hook` that contains code for direct comunication with Houdini.

Both of the folders are in turn devided on subfolders depending on usecase of the code inside. All of the subfolders contain `Sources/x/y/include` and `Sources/x/y/sources` folder, first is to store header files and later is to store source files implementing those header files.

### `Sources/Core`
#### `/Materials`
**TODO**
#### `/Mathematics`
**TODO**
#### `/Physics`
**TODO**
#### `/Renderers`
**TODO**
#### `/Scene`
**TODO**

### `Sources/Hook`
#### `/Nodes`
**TODO**
#### `/Other`
**TODO**

## Functionality in detail
### Plugin
**TODO**

### Renderer
**TODO**

### Scene
**TODO**

### Data transfer
#### Houdini -> Plugin
**TODO**

#### Plugin -> Houdini
**TODO**


## Algorithms


## Extending Functionality
### Changing the rendering algorithm
Entire rendering algorithm is in the file `PhysicallyBasedRenderer.cpp`.  If you want change it you should do that here.

### Changing the BxDFs
You can change BxDFs in the `BxDF.cpp`. There are both methods for evaluating BRDF/BTDF as well as generating sample direction.

### Adding materials
To create a new material you have to make it a public child of `Material` class.  You have to implement `Evaluate` method which is purely virtual in the base class. You’re free to output any `TextureData` as long its values are inside the boundaries for texture data.

I. e., each individual parameter in the `TextureData` has to be in the interval [0,1]. With the exception of `RGBEnergy` whose values are in [0,1]^3.  For example of implementation check out `ProceduralTiles` in the file `MaterialLibrary.cpp`.

After implementing the material you have to register it into the texture hashmap. This is done in the file `PhysicallyBasedRenderer.cpp` in the renderers constructor. You have to pick keyword which isn’t in the hashmap yet as a key.

### Adding scene elements
#### New Elements
If you want to add entirely new scene element you can use one of the existing scene elements as reference e.g. `Camera`.

#### Lights
You might also want to implement different light than the default one (`ConstantRectangularLight`). In that case you should use `Light` as a base clase and implement its `GenerateSample` method.  This light may then be added to the scene during the light loading in the `RenderInterface.cpp`.

### Changing the node interface
If you want to change node interface you can do so in the `RendererNode.cpp`.  More information on node interfaces is available in the [HDK: Working with Parameters](https://www.sidefx.com/docs/hdk/_h_d_k__node_intro__working_with_parameters.html). After adding new parameters correct place to access them is the `RenderInterface.cpp`. 


