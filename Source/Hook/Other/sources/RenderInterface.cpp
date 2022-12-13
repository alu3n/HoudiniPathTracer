//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include <limits>
#include <UT/UT_NetPacket.h>
#include <OP/OP_Director.h>
#include <OBJ/OBJ_Light.h>
#include <UT/UT_Exit.h>
#include <exception>
#include <chrono>
#include <thread>

#include "../include/RenderInterface.hpp"
#include "../../../Core/Renderers/include/PhysicallyBasedRenderer.hpp"



//constexpr float currentTime = 0;

/*
 * Purpose of those boundaries is to prevent unwanted numerical errors etc.
 */

constexpr float largeF = 1000000.0;
constexpr float smallF = 0.0001;

//Light boundaries
constexpr float minLightIntensity = 0;
constexpr float maxLightIntensity = largeF;
constexpr float minLightArea = 0;
constexpr float maxLightArea = largeF;
constexpr float minLightColor = 0;
constexpr float maxLightColor = 1;

//Renderer boundaries
constexpr int minTileSize = 1;
constexpr int maxTileSize = 128;
constexpr int minCycleCount = 1;
constexpr int maxCycleCount = 10000;
constexpr int minSamplesPerCycle = 1;
constexpr int maxSamplesPerCycle = 100;

//Camera boundaries
constexpr float minFStop = smallF;
constexpr float maxFStop = largeF;
constexpr int minResolution = 1;
constexpr int maxResolution = 4096;
constexpr float minAperature = 1;
constexpr float maxAperature = 10000;
constexpr float minFocalLenght = 1;
constexpr float maxFocalLength = 10000;
constexpr float minFocusDistance = smallF;
constexpr float maxFocusDistance = largeF;


RenderInterface::RenderInterface(RendererNode *node) {
    rendererNode = node;
}

//bound function
float B(float val, float min, float max){
    auto rtrval = min > val ? min : val;
    return rtrval > max ? max : rtrval;
}

//Todo: Avoid crashing when wrong node provided

void RenderInterface::Render() {

    renderWindow.Open({ImageResX,ImageResY},{TileResX,TileResY});
    PhysicallyBasedRenderer Renderer = PhysicallyBasedRenderer(*scene.get());
    Image img(ImageResX,ImageResY,TileResX,TileResY);


    for(int i = 0; i < CycleCount; ++i){
        std::cout << "Rendering Cycle " << i << "/" << CycleCount << std::endl;
        for(auto && tile : img.data){
            Renderer.ImproveTile(tile,SamplesPerCycle);
            renderWindow.DisplayTile(tile);
        }
    }

    if(geoExist) geoNode->setHardLock(false);

    renderWindow.Device->close();
}

void RenderInterface::RenderFrame(fpreal time) {
    OP_Context context(time);
    LoadData(context);

    if(!LoadFailed){
        auto start = std::chrono::steady_clock::now();
        Render();
        std::cout << "Render done in " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << "ms" << std::endl;
    }
    else{
        std::cout << "Error while loading data!" << std::endl;
    }
}

Light* RenderInterface::LoadLight(UT_String lightPath,OP_Context context) {
    if(OPgetDirector()->findNode(lightPath) == NULL) throw "non existent node";
    auto lightNode = OPgetDirector()->getOBJNode(lightPath);
    if(!lightNode) throw "wrong node";

    float PX = lightNode->evalFloat("t",0,0);
    float PY = lightNode->evalFloat("t",1,0);
    float PZ = lightNode->evalFloat("t",2,0);

    float RX = lightNode->evalFloat("r",0,0);
    float RY = lightNode->evalFloat("r",1,0);
    float RZ = lightNode->evalFloat("r",2,0);

    float SX = lightNode->evalFloat("areasize",0,0);
    float SY = lightNode->evalFloat("areasize",1,0);

    float I = lightNode->evalFloat("light_intensity",0,0);

    float CR = lightNode->evalFloat("light_color",0,0);
    float CG = lightNode->evalFloat("light_color",1,0);
    float CB = lightNode->evalFloat("light_color",2,0);

    std::cout << SX << " " << SY << std::endl;

    ConstantRectangularLight * light = new ConstantRectangularLight(
        {PX,PY,PZ},
        {RX,RY,RZ},
        {B(SX,minLightArea,maxLightArea),B(SY,minLightArea,maxLightArea)},
        B(I,minLightIntensity,maxLightIntensity),
        {B(CR,minLightColor,maxLightColor),B(CG,minLightColor,maxLightColor),B(CB,minLightColor,maxLightColor)}
    );

    return light;
}

//Throw exception when unable to load the geometry
Geometry RenderInterface::LoadGeometry(UT_String geometryPath, OP_Context context) {
    try{
        if(OPgetDirector()->findNode(geometryPath) == NULL) throw "non existent node";
        auto geometryNode = OPgetDirector()->getSOPNode(geometryPath);
        if(!geometryNode) throw "wrong node";

        geoExist = true;
        geoNode = geometryNode;
        geoNode->setHardLock(true);

        return Geometry(geometryNode,context);
    }
    catch(...){
        std::cout << "Geometry EXP" << std::endl;
        LoadFailed = true;
    }
}

//Throw exception when unable to load the camera
Camera RenderInterface::LoadCamera(UT_String cameraPath, OP_Context context) {
    try{
        if(OPgetDirector()->findNode(cameraPath) == NULL) throw "non existent node";
        auto cameraNode = OPgetDirector()->getOBJNode(cameraPath)->castToOBJCamera();
        if(!cameraNode) throw "wrong node";

        ImageResX = cameraNode->evalInt("res",0,0);
        ImageResY = cameraNode->evalInt("res",1,0);


        auto focalLength = B(cameraNode->evalFloat("focal", 0, 0),minFocalLenght,maxFocalLength);
        auto aperture = B(cameraNode->evalFloat("aperture", 0, 0),minAperature,maxAperature);
        auto fStop = B(cameraNode->evalFloat("fstop",0,0),minFStop,maxFStop);
        auto focusDistance = B(cameraNode->evalFloat("focus",0,0),minFocusDistance,maxFocusDistance);


        return Camera(cameraNode,context,ImageResX,ImageResY,focalLength,aperture,fStop,focusDistance);
    }
    catch(...){
        std::cout << "Camera EXP" << std::endl;
        LoadFailed = true;
    }
}

Lights RenderInterface::LoadLights(OP_Context context) {
    int numLights = rendererNode->evalInt("lights",0, context.getTime());
    Lights lights;

    for(int i = 1; i <= numLights; i++){
        UT_String lightName;
        rendererNode->evalStringInst("light",&i,lightName, 0, context.getTime());
        try{
            lights.push_back(LoadLight(lightName,context));
        }
        catch(...){
            std::cout << "Light EXP" << std::endl;
        }
    }

    if(lights.empty()) LoadFailed = true;
    return lights;
}

void RenderInterface::LoadData(OP_Context context) {
    float t = context.getTime();

    TileResX = B(rendererNode->evalInt("tileSize", 0, t),minTileSize,maxTileSize);
    TileResY = B(rendererNode->evalInt("tileSize", 1, t),minTileSize,maxTileSize);
    CycleCount = B(rendererNode->evalInt("cycleCount", 0, t),minCycleCount,maxCycleCount);
    SamplesPerCycle = B(rendererNode->evalInt("samplesPerCycle", 0, t),minSamplesPerCycle,maxSamplesPerCycle);

    UT_String cameraPath;
    UT_String geometryPath;
    rendererNode->evalString(cameraPath, "camera", 0, t);
    rendererNode->evalString(geometryPath, "geometry", 0, t);

    auto camera = LoadCamera(cameraPath,context);
    auto geometry = LoadGeometry(geometryPath,context);
    auto lights = LoadLights(context);

    if(!LoadFailed) scene = std::make_unique<Scene>(lights,camera,geometry);
}