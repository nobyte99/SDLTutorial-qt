#ifndef APP_H
#define APP_H

#include <QObject>

extern "C" {
#include "SDL2/SDL.h"
}

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
    bool initApp();     // SDL环境初始化
    virtual void execute()=0;     // 本次运行
    virtual ~App();     // SDL环境销毁
private:
    virtual bool initPrivate(); // 本次运行需要的surface等的初始化地方
    virtual void releaseResources(); // 本次运行需要的surface等的销毁地方
signals:

public slots:

};

#endif // APP_H
