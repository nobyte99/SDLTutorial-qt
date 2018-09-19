#ifndef LOADIMAGEONCE_H
#define LOADIMAGEONCE_H

#include <QObject>
#include <app.h>

class LoadImageOnce : public App
{
    Q_OBJECT
public:
    LoadImageOnce();   
    bool initLoadImageOnce(QString strFilePath, QString strFilePath2);  ///< 本地init

signals:

public slots:



    // App interface
public:
    virtual void execute();


private:
    virtual bool initPrivate();  // 本地资源Init,但是总的Init在父类
    virtual void releaseResources();

// 本次运行需要的资源
private:
    SDL_Window * objSDlWin;
    SDL_Renderer * objSDLRen;
    SDL_Texture  * objSDLTexBackground;
    SDL_Texture  * objSDLTexForeground;
    int iDelay;
    int iScreenWidth;
    int iScreenHeight;
};

#endif // LOADIMAGEONCE_H
