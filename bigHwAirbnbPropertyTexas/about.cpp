#include "about.h"
#include "ui_about.h"
#include <QPainter>
about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
}

about::~about()
{
    delete ui;
}

void about::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.translate(width()/2,height()/2);
    painter.drawLine(-75,-100,75,-100);
    painter.drawLine(-75,-100,0,-220);
    painter.drawLine(75,-100,0,-220);
    painter.drawEllipse(-50,-155,100,40);
    painter.drawEllipse(-20,-155,40,40);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black));
    painter.drawEllipse(-10,-145,20,20);
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(0,-145,5,5);
}
