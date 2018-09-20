#include "myshowimagettf.h"
#include <QFile>
#include <QtDebug>
#include <QMutexLocker>

myShowImageTTF::myShowImageTTF()
{
    this->objSDLRen = nullptr;
    this->objSDLTexBackground = nullptr;
    this->objSDlWin = nullptr;
    this->objMix_Music = nullptr;
    objSDL_mutex = nullptr;
    x = 0;
    y = 0;
    iAlpha = 0;
    isFullScreen = false;
}

// 静态的定时器回调（inteval , myShowImageTTF * ）
Uint32 TimerCallback(Uint32 interval, void *param)  // 定时器线程和主线程不是同一个线程
{
    static int iNum(0);
    iNum++;
//    qDebug() <<iNum;
    myShowImageTTF * objMyShowImageTTF = static_cast<myShowImageTTF *>(param);
    //should just change objMyShowImageTTF 中的 ForeGroundTexture
    objMyShowImageTTF->setStrMsg(QString::number(iNum));
    return interval;
}


// 初始化背景图，并且初始化运行环境
bool myShowImageTTF::initMyShowImageTTF(const QString &strBackgroundFile, const QString &strFontFile, const SDL_Color objColor)
{
    if(!this->initAppEnv()){  // 初始化父类
        return false;
    }

    if(!QFile::exists(strBackgroundFile) || !QFile::exists(strFontFile)){
        qDebug() << "file no exists";
        return false;
    }


    // 加载字体图
    this->strFondFilePath = strFontFile;
    this->objSDL_Color = objColor;
    this->objSDLTexBackground = this->renderImage(strBackgroundFile, this->objSDLRen);
    Q_ASSERT(this->objSDLTexBackground != nullptr);
    strMsg = "This is a Test!";

    //加载音乐
    objMix_Music = Mix_LoadMUS( "E:/afghanistan.MP3" );

    //如果加载音乐出了问题
    if( objMix_Music == NULL )
    {
        return false;
    }
    // 启用定时器对帧数进行计算
//    objSDL_mutex = SDL_CreateMutex();
    this->objSDL_TimerID = SDL_AddTimer(100, TimerCallback, this);

}



// 画一次背景图
void myShowImageTTF::myRenderBackground()
{
    CleanUp(this->objSDLTexForeground);
    this->objSDLTexForeground =  this->renderText(this->getStrMsg(),this->strFondFilePath, this->objSDL_Color, 88,this->objSDLRen);

    SDL_RenderClear(this->objSDLRen);  // clear render
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexBackground, NULL, NULL);
    int bW, bH;
//    SDL_mutexP( objSDL_mutex );
    SDL_QueryTexture(this->objSDLTexForeground, NULL, NULL, &bW, &bH);
    SDL_Rect objRect;
    objRect.x = x;
    objRect.y = y;
    objRect.w = bW;
    objRect.h = bH;

    SDL_SetTextureBlendMode(this->objSDLTexForeground, SDL_BLENDMODE_BLEND);  // 设置alpha模式
    SDL_SetTextureAlphaMod( objSDLTexForeground, this->iAlpha );
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexForeground, NULL, &objRect);
//    SDL_mutexV( objSDL_mutex );
    //Update the screen
    SDL_RenderPresent(objSDLRen);

}

// 响应事件，进行字体位置绘制
void myShowImageTTF::onEvent(SDL_Event &e)
{

    switch(e.type){
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym){
        case SDLK_LEFT:
            iAlpha  = std::min(255,iAlpha+1);
            x = std::max(0,std::min(x, x-10));
            break;
        case SDLK_RIGHT:
            iAlpha  = std::min(255,iAlpha-1);
            x = std::min(this->iScreenWidth,std::max(x, x+10));
            break;
        case SDLK_UP:
            y = std::max(0,std::min(y, y-10));
            if( Mix_PlayingMusic() == 0 )  //Mix_PausedMusic()
            {
                //播放音乐
                Mix_PlayMusic( objMix_Music, 1 );   //Mix_ResumeMusic();  Mix_PauseMusic();  Mix_HaltMusic();
            }
            break;
        case SDLK_DOWN:
            y = std::min(this->iScreenHeight,std::max(y, y+10));
            break;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
            if(!isFullScreen){
                //SDL_WINDOW_FULLSCREEN  : 等比例放大了，包括各项数字
                //SDL_WINDOW_FULLSCREEN_desktop  : 仅仅背景图放大了，数字没变，所以数字没法运动到最下方。
                SDL_SetWindowFullscreen(this->objSDlWin, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
            }else{
                SDL_SetWindowFullscreen(this->objSDlWin, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            }
            isFullScreen = !isFullScreen;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    this->myRenderBackground();
}



bool myShowImageTTF::initPrivate()
{
    iScreenWidth = 640;
    iScreenHeight = 480;
    this->objSDlWin = SDL_CreateWindow("Hello World!", 100, 100, this->iScreenWidth, iScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );

    if (objSDlWin == nullptr){
        qDebug() << "SDL_CreateWindow Error: " << SDL_GetError();
        return false;
    }
    this->objSDLRen = SDL_CreateRenderer(objSDlWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (objSDLRen == nullptr){
        qDebug() << "SDL_CreateRenderer Error: " << SDL_GetError();
        return false;
    }

    //初始化SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    SDL_RendererInfo rendererInfo;
    SDL_GetRendererInfo(objSDLRen, &rendererInfo);
    qDebug() << "Renderer: " << rendererInfo.name  << SDL_GetCurrentVideoDriver();

    return true;
}

QString myShowImageTTF::getStrMsg() const
{
    return strMsg;
}

void myShowImageTTF::setStrMsg(const QString &value)
{
    strMsg = value;
}

SDL_Texture *myShowImageTTF::getObjSDLTexForeground() const
{
    return objSDLTexForeground;
}

void myShowImageTTF::setObjSDLTexForeground(SDL_Texture *value)
{
//    SDL_mutexP( objSDL_mutex );
    if(objSDLTexForeground != nullptr){
        CleanUp(this->objSDLTexForeground);
    }
    objSDLTexForeground = value;
//    SDL_mutexV( objSDL_mutex );
}

void myShowImageTTF::setObjSDLTexForegroundText(QString strText)
{
    this->objSDLTexForeground = this->renderText(strText, this->strFondFilePath, this->objSDL_Color,88,this->objSDLRen);
}

/**
 * @brief LoadImageOnce::releaseResources
 * 释放所有的资源
 */
void myShowImageTTF::releaseResources()
{    
    SDL_RemoveTimer(this->objSDL_TimerID);
    Mix_FreeMusic( objMix_Music );
    //退出SDL_mixer
    Mix_CloseAudio();
    CleanUp(this->objSDlWin, this->objSDLRen, this->objSDLTexBackground, objSDLTexForeground, objSDL_mutex);
    qDebug() << "myShowImageTTF releaseResources()";
    this->releaseAppEnv();
}

myShowImageTTF::~myShowImageTTF()
{
    this->releaseResources();
}
