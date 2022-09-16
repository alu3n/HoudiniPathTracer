//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../Headers/RenderInterface.hpp"

RenderInterface::RenderInterface(RendererNode *node) {
    rendererNode = node;
}

void RenderInterface::RenderFrame() {
    renderWindow.Open({640,640},{64,64});

    ImageTile tile(ImageCoorinates(0,100,0,100));


//    for(int i = 0; i < 256; ++i){
//        for(int x = 0; x < 64; ++x){
//            for(int y = 0; y < 64; ++y){
//                tile.data[x][y].R.amount = 0.01 * i;
//            }
//        }
        renderWindow.DisplayTile(tile);
//    }
}

void RenderInterface::RenderFramerange() {
    renderWindow.Open({640,640},{64,64});
}