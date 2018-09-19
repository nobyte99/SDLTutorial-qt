#ifndef LOADIMAGEBYEXTENSION_H
#define LOADIMAGEBYEXTENSION_H

#include <QObject>
#include <loadimageonce.h>

class LoadImageByExtension : public LoadImageOnce
{
public:
    LoadImageByExtension();
    bool initLoadImageByExtension(QString strFilePath, QString strFilePath2);  ///< 本地init
};

#endif // LOADIMAGEBYEXTENSION_H
