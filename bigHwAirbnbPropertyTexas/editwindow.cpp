#include "editwindow.h"
#include "ui_editwindow.h"
#include "airbnbdatabase.h"
#include "mainwindow.h"
#include <string>
editWindow::editWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWindow)
{
    ui->setupUi(this);
}

editWindow::~editWindow()
{
    delete ui;
}

void editWindow::on_pushButton_clicked()
{
    try {
        airbnbProperty prop;
        prop.averageRatePerNight = std::stod(ui->priceEdit_2->text().toStdString());
        prop.bedroomsCount = std::stoi(ui->lineEdit_4->text().toStdString());
        prop.city = ui->lineEdit->text();
        prop.coordinates = ui->coordinateslineEdit->text();
        prop.dateOfListing = ui->coordinateslineEdit->text();
        prop.title = ui->titleEdit->text();
        prop.url = ui->urllineEdit_3->text().toStdString();
        prop.description = ui->descriptiontextEdit->toPlainText();
        emit sendData(prop);
        close();
    }  catch (...) {
        close();
    }
}
void editWindow::recieveData(airbnbProperty& air)
{
    ui->pushButton->setText("Edit");
    ui->coordinateslineEdit->setText(air.coordinates);
    ui->datelineEdit_2->setText(air.dateOfListing);
    ui->descriptiontextEdit->setText(air.description);
    ui->priceEdit_2->setText(QString::fromStdString(std::to_string(air.averageRatePerNight)));
    ui->titleEdit->setText(air.title);
    ui->urllineEdit_3->setText(QString::fromStdString(air.url));
    ui->lineEdit->setText(air.city);
    ui->lineEdit_4->setText(QString::fromStdString(std::to_string(air.bedroomsCount)));
}

