#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->registerBt, SIGNAL(clicked()), this, SLOT(registerBt_clicked_slots()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    qDebug("yang sudo");
}

void Widget::registerBt_clicked_slots()
{
    qDebug("you can here to register");
}
