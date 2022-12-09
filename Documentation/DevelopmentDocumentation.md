# Development Documentation
##### TODOS - What to describe



## Basics
### Technologies
- C++
- HDK

### Algorithms
- Path Tracing

### Resources
- Ray Tracing Gems
- The PBR Book
- Fundamentals of Computer Graphics




## Basics
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
#### Houdini -> Renderer
**TODO**

#### Renderer -> Houdini
**TODO**


## Algorithms



## Extending Functionality
### Changing the rendering algorithm
**TODO**

### Changing the BxDFs
**TODO**

### Adding materials
To create a new material you have to make it a public child of `Material` class.  You have to implement `Evaluate` method which is purely virtual in the base class. You’re free to output any `TextureData` as long its values are inside the boundaries for texture data.

I. e., each individual parameter in the `TextureData` has to be in the interval [0,1]. With the exception of `RGBEnergy` whose values are in [0,1]^3.  For example of implementation check out `ProceduralTiles` in the file `MaterialLibrary.cpp`.

After implementing the material you have to register it into the texture hashmap. This is done in the file `PhysicallyBasedRenderer.cpp` in the renderers constructor. You have to pick keyword which isn’t in the hashmap yet as a key.

### Adding scene elements
If you want to add entirely new scene element you can use one of the existing scene elements as reference e.g. `Camera`.

You might also want to implement different light than the default one (`ConstantRectangularLight`). In that case you should use `Light` as a base clase and implement its `GenerateSample` method.  This light may then be added to the scene during the light loading in the `RenderInterface.cpp`.

### Changing the node interface
If you want to change node interface you can do so in the `RendererNode.cpp`.  More information on node interfaces is available in the [HDK: Working with Parameters](https://www.sidefx.com/docs/hdk/_h_d_k__node_intro__working_with_parameters.html). After adding new parameters correct place to access them is the `RenderInterface.cpp`. 


