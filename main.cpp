/**
 * @file
 *
 *  不要把所有东西都放在main中
 *
 */

#include <QtTest/QtTest>

#include <loadimageonce.h>
#include <loadimagebyextension.h>
#include <loadimagebyextensionwithevent.h>
#include <myshowimagettf.h>

class TestQString: public QObject
{
  Q_OBJECT
private slots:
  // 每个private slot函数都是会被自动调用的测试函数
//  void testToLower();
//  // 以“_data”结尾的函数向对应的测试函数提供测试数据
//  void testToLower_data();

  // first test for sdl to load bmp image
//  void testShowBmpImage();

  // second test for sdl to load images by SDL extension
//  void testShowImages();

  // third test for sdl to load images by SDL extension
  void testShowImageEvents();
  void testShowImageTTFEvents();

};
//void TestQString::testToLower()
//{
//  // 获取测试数据
//  QFETCH(QString, string);
//  QFETCH(QString, result);
//  // 如果输入的两个参数不同，则会被认为测试失败
//  QCOMPARE(string.toLower(), result);
//}
//void TestQString::testToLower_data()
//{
//  // 添加数据列
//  QTest::addColumn<QString>("string");
//  QTest::addColumn<QString>("result");
//  // 添加测试数据
//  QTest::newRow("lower") << "hello" << "hello";
//  QTest::newRow("mixed") << "HeLlO" << "hello";
//  QTest::newRow("upper") << "HELLO" << "hello";
//}

//// loading bmp images
//void TestQString::testShowBmpImage()
//{
//    LoadImageOnce objLoadImageOnce;
//    QString strF1("sample.bmp");
//    QString strF2("icon.bmp");
//    objLoadImageOnce.initLoadImageOnce(strF1, strF2);
//    objLoadImageOnce.execute();

//}

//// load images by SDL extension
//void TestQString::testShowImages()
//{
//    LoadImageByExtension objLoadImageByExtension;
//    QString strF1("sample.bmp");
//    QString strF2("icon.bmp");
//    objLoadImageByExtension.initLoadImageByExtension(strF1, strF2);
//    objLoadImageByExtension.execute();
//}

// load images and handle events
void TestQString::testShowImageEvents()
{
    LoadImageByExtensionWithEvent objLoadImageByExtensionWithEvent;
    QString strF1(QString(strSourcePWD)+QString("/sample.bmp"));
    QString strF2(QString(strSourcePWD)+QString("/icon.bmp"));
    objLoadImageByExtensionWithEvent.initLoadImageByExtension(strF1, strF2);
    objLoadImageByExtensionWithEvent.execute();

}

void TestQString::testShowImageTTFEvents()
{
    myShowImageTTF  objMyShowImageTTF;
    QString strF1(QString(strSourcePWD)+QString("/sample.bmp"));
    QString strFontPath("C:/Windows/Fonts/STHUPO.TTF");
    SDL_Color mySDLColor={255,255,255,255};

    objMyShowImageTTF.initMyShowImageTTF(strF1, strFontPath, mySDLColor);
    objMyShowImageTTF.execute();

}
// 用于构建可执行的测试程序

QTEST_MAIN(TestQString)

#include "main.moc"
