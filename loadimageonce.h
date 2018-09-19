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
    void releaseResources();

    // App interface
private:
    virtual void myRenderBackground();
    virtual bool initPrivate();  // 本地资源Init,但是总的Init在父类


// 本次运行需要的资源
public:
    SDL_Window   * objSDlWin;
    SDL_Renderer * objSDLRen;
    SDL_Texture  * objSDLTexBackground;
    SDL_Texture  * objSDLTexForeground;
    int iDelay;
    int iScreenWidth;
    int iScreenHeight;
    int x;
    int y;
    void myRenderImage(int x, int y);




    // App interface
private:
    void onEvent(SDL_Event &e);

};

#endif // LOADIMAGEONCE_H
