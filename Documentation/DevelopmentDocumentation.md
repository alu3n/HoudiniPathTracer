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


## Source Code Structure
The project code is divided into two main parts - `Source/Core` which contains code that is used by the rendering algorithm  itself and `Source/Hook` that contains code for direct comunication with Houdini.

Both of the folders are in turn devided on subfolders depending on usecase of the code inside. All of the subfolders contain `Sources/x/y/include` and `Sources/x/y/sources` folder, first is to store header files and later is to store source files implementing those header files.

### `Sources/Core`
#### `/Materials`

#### `Mathematics`
#### `Physics`
#### `Renderers`
#### `Scene`

### `Hook`
#### `Nodes`
#### `Other`

## Functionality in detail
### How does the plugin function
**TODO**
### How does the renderer function
**TODO**

## Algorithms

## Extending Functionality
### Changing the rendering algorithm
**TODO**
### Changing the BxDFs
**TODO**
### Adding materials
**TODO**
### Adding scene elements
**TODO**
### Changing the node interface
**TODO**
### 
**TODO**


