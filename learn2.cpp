#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("网格布局-登录表单");
    window.resize(300, 150);

    QGridLayout *layout = new QGridLayout(&window);
    layout->setContentsMargins(30, 20, 30, 20);
    layout->setSpacing(15);

    // 第0行：用户名
    layout->addWidget(new QLabel("用户名:"), 0, 0);
    layout->addWidget(new QLineEdit(), 0, 1);

    // 第1行：密码
    layout->addWidget(new QLabel("密  码:"), 1, 0);
    layout->addWidget(new QLineEdit(), 1, 1);

    // 第2行：登录按钮，跨2列（占据第0列和第1列）
    QPushButton *loginBtn = new QPushButton("登录");
    layout->addWidget(loginBtn, 2, 0, 1, 2);

    // 设置列拉伸因子：第1列（输入框列）占所有额外空间
    layout->setColumnStretch(1, 1);

    window.show();
    return app.exec();
}
