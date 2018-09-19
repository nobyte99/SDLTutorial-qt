#ifndef MYSHOWIMAGETTF_H
#define MYSHOWIMAGETTF_H

#include <QObject>
#include <app.h>

class myShowImageTTF : public App
{
public:
    myShowImageTTF();
    bool initMyShowImageTTF(const QString &strBackgroundFile, const QString &strFontFile, const SDL_Color objColor);
    void releaseResources();
    virtual ~myShowImageTTF();
    // App interface
private:
    virtual void myRenderBackground();
    virtual void onEvent(SDL_Event &e);
    virtual bool initPrivate();


private:
    SDL_Window   * objSDlWin;
    SDL_Renderer * objSDLRen;
    SDL_Texture  * objSDLTexBackground;
    SDL_Texture  * objSDLTexForeground;
    int iScreenWidth;
    int iScreenHeight;
    int x;
    int y;

};

#endif // MYSHOWIMAGETTF_H
