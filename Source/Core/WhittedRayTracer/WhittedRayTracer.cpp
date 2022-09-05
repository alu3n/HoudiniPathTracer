//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "WhittedRayTracer.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_Detail.h>
#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>



UT_Vector3F WhittedRayTracer::RenderPixel(UT_Vector2i pixelCoords, int frame) {
    OP_Context context(1.0/frame);
    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));

    GU_RayIntersect intersect(temp->gdp());
    GU_RayInfo info;
    auto ray = Settings.Cam.GenerateRay(pixelCoords);


    intersect.sendRay(ray.org,ray.dir,info);

    if(info.myTValid){
        return{1,0,0};
    }
    else{
        return{0,0,0};
    }
//    return {info.myTmax,info.myTmin,0};

//    if(info.myTmax > 0){
//        return {1,0,0};
//    }
//    return {0,0,0};
//    GU_RayIntersect()

}

WhittedRayTracer::WhittedRayTracer(RenderSettings settings, SOP_Node *geo) : Renderer(settings, geo) {

}