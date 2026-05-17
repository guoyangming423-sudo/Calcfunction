#include "calculator.h"

#include <QApplication>

// 主函数：所有 C++ 程序的入口
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;

    w.resize(800, 480);
    w.show();

    return a.exec();
}
