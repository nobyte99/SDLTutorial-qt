#include "loadimagebyextensionwithevent.h"
#include <QtDebug>
LoadImageByExtensionWithEvent::LoadImageByExtensionWithEvent()
{

}

LoadImageByExtensionWithEvent::~LoadImageByExtensionWithEvent()
{
    qDebug() << "LoadImageByExtensionWithEvent::~LoadImageByExtensionWithEvent()";
    this->releaseResources();
    this->releaseAppEnv();
}

/**
 * @brief LoadImageByExtensionWithEvent::execute
 * 判断是否在运行，在运行，先进性事件处理，然后在渲染
 */

// 执行事件循环
void LoadImageByExtensionWithEvent::onEvent(SDL_Event &e)
{
    static int x=0;
    static int y=0;
    switch(e.type){
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym){
        case SDLK_LEFT:
            x = std::max(0,std::min(x, x-10));
            break;
        case SDLK_RIGHT:
            x = std::min(this->iScreenWidth,std::max(x, x+10));
            break;
        case SDLK_UP:
            y = std::max(0,std::min(y, y-10));
            break;
        case SDLK_DOWN:
            y = std::min(this->iScreenHeight,std::max(y, y+10));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    this->myRenderImage(x,y);
}


