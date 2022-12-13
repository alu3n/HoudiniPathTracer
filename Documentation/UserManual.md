# User Manual
## Renderer
Once you install the render engine it is available as a ROP node under the name “NPRG045 Renderer”.

### Rendering
In order to render an image you have to specify the following parameters in the renderer node - they’re described in the next section. Once you’ve done that you can start render using the “Render” button in the renderer node parameters. Renderer will freeze output node of the geometry node, which you’ve specified as an input. During the rendering time **you shouldn’t manipulate the frozen node**. The node will be unfrozen once the rendering is complete. You also **shouldn’t close the rendering window** while is the render still running.

### Renderer Parameters
#### Tile Size
- Values range: [1,128]
Image is broken down into individual tiles whose size is determined by this parameter. Renderer updates individual tiles. Keeping this value small will result in more frequent update of the rendered image, but it might slow down the rendering a bit.

#### Cycle Count
- Values range: [1,10000]
Each tile is improved n number of times, where n is the cycle count.

#### Samples Per Cycle
- Values range: [1,100]
During each improvement cycle each pixel will be sampled n times, where n is the number of samples per cycle.

#### Geometry
This parameter is used to link geometry node to the renderer. It has to follow specifications declared in the geometry section.

#### Camera
This parameter is used to link camera node to the renderer. It has to follow specifications declared in the camera section.

#### Number of Lights
This parameter controlls number of lights that can be added to the scene. More lights will result in slower convergence of the image.

#### Light
This parameter is used to link light node to the renderer. It has to follow specifications declared in the light section.

## Geometry
To create geometry for the renderer you have to create **Geometry** node inside the objects context. The has to contain only polygonal geometry. For the renderer to work properly **it is necessary to specify vertex normals**. Inside the geometry node create null node and set it as output of the geometry node.

You can specify certain parameters that can alter appearance of the rendered geometry. To do so you have to add attribute to corresponding part of geometry and set its value.

### Normals
- **Geometry part:** Vertices
- **Attribute name:** N
- **Attribute type:** Vector Float 3
- **Limitation:** Values have to be normalized

### Color
- **Geometry part:** Points
- **Attribute name:** Cd
- **Attribute type:** Vector Float 3
- **Limitation:** Each value has to be in [0,1]

By default renderer uses shader color, if you want to use the point color you have to set useCd to 1.

### Use Cd
- **Geometry part:** Points
- **Attribute name:** useCd
- **Attribute type:** Int
- **Limitation:** Value has to be in {0,1}

### Shader
- **Geometry part:** Points
- **Attribute name:** shader
- **Attribute type:** Int

If you set the value to non-existent shader index, the default shader will be used instead.

## Camera
During scene layout you might view your scene through the camera, renderer mimics that view. You might also use viewport representation of the camera.

### Supported parameters
- Translate
- Rotate
- Resolution
  - Values range: [1,4096]
- Focal Length
  - Values range: [1,10000]
- Aperature
  - Values range: [1,10000]
- Focus Distance
  - Values range: [0.0001,1000000]
- F-Stop
  - Values range: [0.0001,1000000]

Those parameters are described in the [Houdini Documentation](https://www.sidefx.com/docs/houdini/render/cameras.html)

## Light
During layout you should use viewport as a guide for the light placement.

### Supported parameters
- Translate
- Rotate
- Color
- Area Size
- Intensity

Those parameters are described in the [Houdini Documentation](https://www.sidefx.com/docs/houdini/nodes/obj/hlight.html

## Default shaders
### Marble
- Shader code: Marble
- Type: Constant

### Rubber
- Shader code: Rubber
- Type: Constant

### Porcelain
- Shader code: Porcelain
- Type: Constant

### Glass
- Shader code: Glass
- Type: Constant

### Piano Black
- Shader code: Piano Black
- Type: Constant

### Rock
- Shader code: Rock
- Type: Constant

### Plastic
- Shader code: Plastic
- Type: Constant

### Marble
- Shader code: Marble
- Type: Constant

### Checker Board
- Shader code: Checker Board
- Type: Procedural

## Custom Shaders
You can also create your own shader, which might even create values procedurally. This is described in the development documentation. Once you’ve added the shader to renderer you can use it the same way as default shaders.
