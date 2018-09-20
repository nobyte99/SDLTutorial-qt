#ifndef MYSHOWIMAGETTF_H
#define MYSHOWIMAGETTF_H

#include <QMutex>
#include <QObject>
#include <app.h>

class myShowImageTTF : public App
{
public:
    explicit myShowImageTTF();
    bool initMyShowImageTTF(const QString &strBackgroundFile, const QString &strFontFile, const SDL_Color objColor);
    void releaseResources();
    virtual ~myShowImageTTF();
    // App interface
    SDL_Texture *getObjSDLTexForeground() const;
    void setObjSDLTexForeground(SDL_Texture *value);
    void setObjSDLTexForegroundText(QString strText);

    QString getStrMsg() const;
    void setStrMsg(const QString &value);

private:
    virtual void myRenderBackground();
    virtual void onEvent(SDL_Event &e);
    virtual bool initPrivate();


private:
    SDL_Window   * objSDlWin;
    SDL_Renderer * objSDLRen;
    SDL_Texture  * objSDLTexBackground;
    SDL_Texture  * objSDLTexForeground;
    QString      strMsg;
    QString      strFondFilePath;
    SDL_Color    objSDL_Color;
    SDL_TimerID  objSDL_TimerID;

    Mix_Music    *objMix_Music;
    SDL_mutex    *objSDL_mutex;

    int iScreenWidth;
    int iScreenHeight;
    int x;
    int y;
    int iAlpha;
    bool isFullScreen;



};

#endif // MYSHOWIMAGETTF_H
