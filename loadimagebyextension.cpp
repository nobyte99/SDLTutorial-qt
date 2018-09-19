#include "loadimagebyextension.h"

LoadImageByExtension::LoadImageByExtension()
{

}

// 初始化，采用SDL extension中的SDL Image扩展来加载图片
bool LoadImageByExtension::initLoadImageByExtension(QString strFilePath, QString strFilePath2)
{
    if(!this->initAppEnv()){ // 初始化父类
        return false;
    }

    // 进行本地特殊初始化
    this->iDelay = 2000;

    // background
    this->objSDLTexBackground=IMG_LoadTexture(this->objSDLRen,strFilePath.toLocal8Bit().data());
    Q_ASSERT(objSDLTexBackground!=nullptr);

    // foreground
    this->objSDLTexForeground=IMG_LoadTexture(this->objSDLRen,strFilePath2.toLocal8Bit().data());
    Q_ASSERT(objSDLTexForeground!=nullptr);

    return true;
}
