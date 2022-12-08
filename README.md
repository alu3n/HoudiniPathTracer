# HoudiniPathTracer
Individual software project for NPRG045.

## Compatibility
As of September 3. 2022 this library was only tested on Apple Silicon based macOS machine (version 19.5.353 arm64). The code should be compatible with other builds of the Houdini 19.5 but it wasn't tested yet.

## Requirements
For more information check out [HDK documentation](https://www.sidefx.com/docs/hdk/_h_d_k__intro.html)
### MacOS
- XCode
- Houdini 19.5
### Linux
- TODO
### Windows
- TODO

## Build instructions
1) Download and install required libraries
2) Set environment variables in the `config.env` file
3) Run `run.sh`

# Technical documentation
There are technically two main parts of the source code - first one is core part,
which encapsulates functionality of the renderer itself such as illumination computation, 
etc.. Second part is houdini hook which is responsible for the communication with the
houdini software through their api.

**STRUCTURE**
## Core
### Materials
This folder is dedicated to classes and functions related to the materials
in the renderer portion of the project.

### Mathematics
This folder is dedicated to mathematical classes and functions used all over
the project.

### Physics
This folder is dedicated to physical classes and functions used in the renderer
portion of the project.

### Renderers
This folder contains the main rendering logic for the project renderers.

### Scene
This folder contains classes which make up the scene.

### Textures
This folder is dedicated to textures.


## Sample Scenes
### Morning Room
### Statue
### Teapot