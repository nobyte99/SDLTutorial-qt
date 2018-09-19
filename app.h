#ifndef APP_H
#define APP_H

#include <QObject>

extern "C" {
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
}

#include <cleanup.h>

#undef main

/**
 * @brief 用来完成SDL的初始化工作，销毁工作等，可以看作是程序与SDL之间的一层接口
 *
 *
 */
class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);    
    bool initAppEnv();     // SDL环境初始化
    virtual void execute();     // 本次运行
    virtual ~App();     // SDL环境销毁

    SDL_Texture* renderText(const QString &message, const QString &fontFile, const SDL_Color color, const int fontSize, SDL_Renderer * renderer);
    SDL_Texture *renderImage(const QString &strFilePath, SDL_Renderer *objRenderer);
    void releaseAppEnv();

private:
    virtual void myRenderBackground() =0 ;
    // 如果使用了事件循环，你可以定制化onEvent
    virtual void onEvent(SDL_Event &e) = 0;
    //分配自己的资源
    virtual bool initPrivate()=0; // 本次运行需要的surface等的初始化地方


    void StartExecute();
    void StopExecute();
signals:

public slots:

private:
    bool isRunning = true;
};

#endif // APP_H
