#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("垂直布局示例");
    window.resize(200, 300);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);

    layout->addWidget(new QPushButton("顶部按钮"));
    // 添加一个可拉伸的空白项，占据中间所有空间
    layout->addStretch();
    layout->addWidget(new QPushButton("底部按钮1"));
    layout->addWidget(new QPushButton("底部按钮2"));

    window.show();
    return app.exec();
}
