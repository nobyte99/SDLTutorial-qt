#ifndef LOADIMAGEBYEXTENSIONWITHEVENT_H
#define LOADIMAGEBYEXTENSIONWITHEVENT_H

#include <QObject>
#include <loadimagebyextension.h>

class LoadImageByExtensionWithEvent : public LoadImageByExtension
{
public:
    LoadImageByExtensionWithEvent();
    ~LoadImageByExtensionWithEvent();

    // App interface
private:
    virtual void onEvent(SDL_Event &e);


};

#endif // LOADIMAGEBYEXTENSIONWITHEVENT_H
