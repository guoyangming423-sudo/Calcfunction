#include "calculator.h"
#include "calcfunction.h"

#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

Calculator::Calculator(QWidget *parent) : QWidget(parent),
    m_nCurrentIndex(-1)
{
    // 固定窗口大小为800x480，和野火开发板一致
    setFixedSize(800, 480);

    m_bInputSymbol = false;
    m_bResult = false;

    express_lineEdit = new QLineEdit(this);
    express_lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    // 替换掉Skin::m_strAppFontBold，使用系统默认字体
    express_lineEdit->setStyleSheet("QLineEdit{border: none; font: bold 40px Arial; color: #333333;}");
    express_lineEdit->setAlignment(Qt::AlignRight);
    express_lineEdit->setFocus();
    // 设置输入框位置和大小
    express_lineEdit->setGeometry(14, 119, 772, 57);

    // 初始化按钮
    InitData();
    ccalculator = new CCalculator();
}

Calculator::~Calculator()
{
    delete ccalculator;
    ccalculator = NULL;
}

void Calculator::InitData()
{
    m_realTemp = 0.0;
    m_strResult = "0";

    QStringList strLabes = QStringList() << "bin" << "oct" << "dec" << "hex" << "AC" << "←" << "/"
                                         << "x^2" << "x^y" << "ln" << "7" << "8" << "9" << "*"
                                         << "x!" << "log" << "√" << "4" << "5" << "6" << "-"
                                         << "sin" << "cos" << "tan" << "1" << "2" << "3" << "+"
                                         << "mod" << "(" << ")" << "±" << "0" << "." << "=";

    int space = 1;
    int nWidth = (800 - 8 - (space * 6)) / 7;
    int nHeight = (480 - 180 - 4 - space * 4) / 5;
    for (int i = 0; i < strLabes.size(); i++) {
        QRect rect(4 + (i % 7) * (nWidth + space) , 180 + (i / 7) * (nHeight + space), nWidth, nHeight);
        m_calcBtns.insert(i, new CalcButton(i, rect, strLabes.at(i)));
    }
}

void Calculator::onButtonClicked(CalcButton *btn)
{
    if (NULL == btn) return;
    switch (btn->type()) {
    case AC: {
        m_strHistory.clear();
        express_lineEdit->clear();
        m_bInputSymbol = true;
        m_bResult = false;
        m_realTemp = 0.0;
    }
        break;
    case BackSpace:
    {
        express_lineEdit->backspace();
    }
        break;
    case Square:
    {
        express_lineEdit->insert(tr("^2"));
    }
        break;
    case Power:
    {
        express_lineEdit->insert(tr("pow( , )"));
        express_lineEdit->cursorBackward(false, 3);
    }
        break;
    case Factorial:
    {
        express_lineEdit->insert(tr("!"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Ln:
    {
        express_lineEdit->insert(tr("ln()"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Log:
    {
        express_lineEdit->insert(tr("log( , )"));
        express_lineEdit->cursorBackward(false, 3);
    }
        break;
    case SquareRoot:
    {
        express_lineEdit->insert(tr("sqrt()"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Sin:
    {
        express_lineEdit->insert(tr("sin()"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Cos:
    {
        express_lineEdit->insert(tr("cos()"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Tan:
    {
        express_lineEdit->insert(tr("tan()"));
        express_lineEdit->cursorBackward(false, 1);
    }
        break;
    case Mod:
    {
        express_lineEdit->insert(tr(" mod "));
    }
        break;
    case Point:
    {
        QString str = express_lineEdit->text();
        int curPos = express_lineEdit->cursorPosition();
        if (curPos == 0)
            express_lineEdit->insert(tr("0."));
        else if(!str[curPos - 1].isDigit())
            express_lineEdit->insert(tr("0."));
        else
            express_lineEdit->insert(tr("."));
    }
        break;
    case Number_0:
    case Number_1:
    case Number_2:
    case Number_3:
    case Number_4:
    case Number_5:
    case Number_6:
    case Number_7:
    case Number_8:
    case Number_9:
    case Plus:
    case Minus:
    case Division:
    case Multiplication:
    case LeftBrackets:
    case RightBrackets:
    {
        express_lineEdit->insert(btn->text());
    }
        break;
    case Negative: {
        QString str = express_lineEdit->text();
        if (str.startsWith("-")) {
            str.remove(0, 1);
        } else {
            str.insert(0, "-");
        }
        express_lineEdit->setText(str);
    }
        break;
    case Result:
    {
        QString result;
        QString express = express_lineEdit->text();
        int ret=ccalculator->Calc(result, express);
        if(ret == RET_CORRECT) {
            express_lineEdit->setText(result);
            m_strHistory = express;
        } else {
            express_lineEdit->setText("error");
        }
    }
        break;
    default:
        break;
    }

    this->update();
}

// 删掉了原来的resizeEvent函数，因为我们固定了窗口大小

void Calculator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.fillRect(this->rect(), QColor("#000000"));

    // 绘制标题栏
    QRect rectTitle(0, 0, 800, 60);
    QFont font("Arial");
    font.setBold(true);
    font.setPixelSize(22);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    painter.drawText(rectTitle, Qt::AlignCenter, tr("计算器"));

    // 绘制结果和历史记录
    drawHistory(&painter);
    // 绘制按钮
    drawButtons(&painter);
}

void Calculator::drawHistory(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    painter->setPen(Qt::NoPen);

    QRect rect(4, 63, 792, 114);
    painter->setBrush(QColor("#ffffff"));
    painter->drawRoundedRect(rect, 6, 6);
    // 历史及公式
    QRect rectValue(rect.left() + 10, rect.top(), rect.width() - 20, rect.height() / 2);
    painter->setPen("#666666");
    font.setPixelSize(20);
    painter->setFont(font);
    painter->drawText(rectValue, Qt::AlignRight | Qt::AlignVCenter, m_strHistory);

#if !INPUT_BY_LINEEDIT
    // 输入
    rectValue = QRect(rectValue.left(), rectValue.bottom(), rectValue.width(), rectValue.height());
    painter->setPen("#333333");
    font.setPixelSize(40);
    painter->setFont(font);
    painter->drawText(rectValue, Qt::AlignRight | Qt::AlignVCenter, m_strResult);
#endif

    painter->restore();
}

void Calculator::drawButtons(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#c2c4c3"));
    QRect rectBtns(4, 180, 792, 295);
    painter->drawRoundedRect(rectBtns, 6, 6);
    painter->setPen(QColor("#000000"));
    // 绘制网格
    int nOffset = (rectBtns.width() - 6) / 7;
    for (int i = 0; i < 6; i++) {
        painter->drawLine(QPoint(rectBtns.left() + (i + 1) * nOffset + i, rectBtns.top()),
                          QPoint(rectBtns.left() + (i + 1) * nOffset + i, rectBtns.bottom()));
    }
    // row
    nOffset = (rectBtns.height() - 4) / 5;
    for (int i = 0; i < 6; i++) {
        painter->drawLine(QPoint(rectBtns.left(), rectBtns.top() + (i + 1) * nOffset + i),
                          QPoint(rectBtns.right(), rectBtns.top() + (i + 1) * nOffset + i));
    }

    QFont font("Arial");
    font.setPixelSize(25);
    painter->setFont(font);
    foreach (CalcButton *btn, m_calcBtns) {
        painter->setPen("#333333");
        if (4 == btn->id()) {
            painter->setPen("#ed8e32");
        }

        if ((btn->text().toInt() > 0 && (btn->text().toInt() <= 9)) ||
                (32 == btn->id() || 33 == btn->id()))
        {
            QRect rect(btn->rect().left(), btn->rect().top(), btn->rect().width() - 1, btn->rect().height());
            painter->fillRect(rect, QColor("#cbccce"));
        }

        if (34 == btn->id()) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(QColor("#ed8e32"));
            QPainterPath path;
            path.addRoundedRect(btn->rect().left(), btn->rect().top(), btn->rect().width(), btn->rect().height(), 6, 6);
            path.addRect(btn->rect().left(), btn->rect().top(), btn->rect().width(), 20);
            path.addRect(btn->rect().left(), btn->rect().top(), 20, btn->rect().height());
            path.setFillRule(Qt::WindingFill);
            painter->drawPath(path);
            painter->setPen("#ffffff");
        }

        if (m_nCurrentIndex == btn->id() && btn->id() < 34) {
            QRect rect(btn->rect().left(), btn->rect().top(), btn->rect().width() - 1, btn->rect().height());
            painter->fillRect(rect, QColor("#666666"));
        }

        painter->drawText(btn->rect(), Qt::AlignCenter, btn->text());
    }
    painter->restore();
}

void Calculator::mousePressEvent(QMouseEvent *e)
{
    foreach (CalcButton *btn, m_calcBtns) {
        if (btn->rect().contains(e->pos())) {
            m_nCurrentIndex = btn->id();
            this->update();
            break;
        }
    }
}

void Calculator::mouseReleaseEvent(QMouseEvent *e)
{
    if (-1 != m_nCurrentIndex) {
        onButtonClicked(m_calcBtns.value(m_nCurrentIndex));
        m_nCurrentIndex = -1;
    }

    QWidget::mouseReleaseEvent(e);
}

void Calculator::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}
