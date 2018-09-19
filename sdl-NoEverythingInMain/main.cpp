/**
 * @file
 *
 *  不要把所有东西都放在main中
 *
 */

#include <QCoreApplication>
#include <loadimageonce.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // first test: load bmp image
    LoadImageOnce objLoadImageOnce;
    QString strFilePath("sample.bmp");
    QString strFilePath2("icon.bmp");
    objLoadImageOnce.initLoadImageOnce(strFilePath,strFilePath2);
    objLoadImageOnce.execute();


    // second test: load any image by sdl extension image library


    return a.exec();
}
