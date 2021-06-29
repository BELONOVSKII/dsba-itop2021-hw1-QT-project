#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include "editwindow.h"
#include "about.h"
#include "airbnbProperty.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    standartModel = new QStandardItemModel(data.countRows(),data.countColumns(),this);
    data.fillingTheModel(standartModel);
    ui->tableView->setModel(standartModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    style();
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked1(const QModelIndex &)));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_deleteButton_clicked()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectModel->selectedIndexes();
    for (QModelIndex ind : indexes)
    {
        int row = ind.row();
        QModelIndex index = ui->tableView->model()->index(row,1,QModelIndex());
        std::string s = index.data().toString().toStdString();
        data.deleteItem(s);
    }
    standartModel = new QStandardItemModel(data.countRows(),data.countColumns(),this);
    data.fillingTheModel(standartModel);
    ui->tableView->setModel(standartModel);
    ui->searchButton->setText("Search");
    ui->searchEdit->clear();
    check = !check; //this check used to chsnge the text of the search button according to the curretnt situation

}


void MainWindow::on_searchButton_clicked()
{
    if (!check)
    {
        std::string title = ui->searchEdit->text().toStdString();
        mapOfProperty map1 = data.getValues(title);
        airbnbDataBase data2(map1);
        standartModel = new QStandardItemModel(data2.countRows()+18,data2.countColumns(),this);
        data2.fillingTheModel(standartModel);
        ui->tableView->setModel(standartModel);
        ui->searchButton->setText("Return");
        check = !check;
    }
    else
    {
        ui->searchEdit->clear();
        standartModel = new QStandardItemModel(data.countRows(),data.countColumns(),this);
        data.fillingTheModel(standartModel);
        ui->tableView->setModel(standartModel);
        check = !check;
        ui->searchButton->setText("Search");
    }

}



void MainWindow::on_addButton_clicked()
{
    editWindow e;
    connect(&e, SIGNAL(sendData(airbnbProperty&)), this, SLOT(recieveData(airbnbProperty&)));
    e.exec();
}

void MainWindow::addItem(airbnbProperty& air)
{
    data.addProperty(air);
}

void MainWindow::recieveData(airbnbProperty& air)
{
    addItem(air);
    standartModel = new QStandardItemModel(data.countRows(),data.countColumns(),this);
    data.fillingTheModel(standartModel);
    ui->tableView->setModel(standartModel);
}


void MainWindow::on_editButton_clicked()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectModel->selectedIndexes();
    airbnbProperty prop;
    for (QModelIndex ind : indexes)
    {
        int row = ind.row();
        QModelIndex index = ui->tableView->model()->index(row,1,QModelIndex());
        std::string s = index.data().toString().toStdString();
        prop = data.getSingleValue(s);
        data.deleteItem(s);
    }
    editWindow e;
    connect(this, SIGNAL(sendData(airbnbProperty&)), &e, SLOT(recieveData(airbnbProperty&)));
    connect(&e, SIGNAL(sendData(airbnbProperty&)), this, SLOT(recieveData(airbnbProperty&)));
    emit sendData(prop);
    e.exec();
}


void MainWindow::on_saveButton_clicked()
{
    data.save();
}

void MainWindow::on_citySortButton_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(standartModel);
    proxyModel->sort(6);
    ui->tableView->setModel(proxyModel);

}


void MainWindow::on_BedroomsSort_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(standartModel);
    proxyModel->sort(2);
    ui->tableView->setModel(proxyModel);
}



void MainWindow::on_pushButton_3_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(standartModel);
    proxyModel->sort(0);
    ui->tableView->setModel(proxyModel);
}
void MainWindow::on_actionAbout_5_triggered()
{
    about ab;
    ab.exec();
}
void MainWindow::style()
{
    ui->deleteButton->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(247, 10, 81, 200), stop:1 rgba(245, 22, 237, 200));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");
    ui->addButton->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(22, 245, 59, 200), stop:1 rgba(130, 148, 130, 200));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");
    ui->editButton->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(31, 207, 195, 200), stop:1 rgba(130, 148, 130, 200));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");
    ui->saveButton->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(250, 66, 25, 200), stop:1 rgba(235, 237, 111, 200));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");
    ui->tableView->setStyleSheet("QTableView {selection-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(112, 161, 157, 200), stop:1 rgba(252, 210, 104, 200));}");

    ui->citySortButton->setStyleSheet("QPushButton{border: 1px solid transparent; border-radius: 2px; text-align: center;color:rgba(255,255,255,255);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(38, 41, 112, 200), stop:1 rgba(140, 161, 6, 200)); }");

    ui->BedroomsSort->setStyleSheet("QPushButton{border-radius: 2px; text-align: center;color:rgba(255,255,255,255);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(38, 41, 112, 200), stop:1 rgba(140, 161, 6, 200)); }");

    ui->pushButton_3->setStyleSheet("QPushButton{border-radius: 2px; text-align: center;color:rgba(255,255,255,255);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(38, 41, 112, 200), stop:1 rgba(140, 161, 6, 200)); }");

    ui->searchEdit->setStyleSheet("QLineEdit{background-color: green; color:white}");
}
void MainWindow::onTableClicked(const QModelIndex &index)
{
    try
    {
        std::string s = "open " + index.data().toString().toStdString();
        const char * c = s.c_str();
        system(c);
    }
    catch(...)
    {};

}
void MainWindow::onTableClicked1(const QModelIndex &index)
{
    if (!check2)
    {
        QString qs = index.data().toString();
        std::set<QString>::iterator it = data.setOfTowns.find(qs);
        if (it != data.setOfTowns.end())
        {
            standartModel = new QStandardItemModel(data.setOfTowns.size(), 1, this);
            int i = 0;
            for(std::set<QString>::iterator it2 = data.setOfTowns.begin(); it2 != data.setOfTowns.end(); it2++)
            {
                   QModelIndex ind = standartModel->index(i,0,QModelIndex());
                   standartModel->setData(ind,(*it2));
                   i++;
            }
            title = ui->tableView->model()->index(index.row(),1,QModelIndex()).data().toString();
            ui->tableView->setModel(standartModel);
            check2 = !check2;
        }
    }
    if (check2)
    {
        QItemSelectionModel *selectModel = ui->tableView->selectionModel();
        QModelIndexList indexes = selectModel->selectedIndexes();
        for (QModelIndex ind : indexes)
        {
            int row = ind.row();
            QModelIndex index = ui->tableView->model()->index(row,0,QModelIndex());
            std::string s = index.data().toString().toStdString();
            airbnbProperty a;
            a = data.getPropertyData()[title.toStdString()];
            a.city = QString::fromStdString(s);
            data.getPropertyData()[title.toStdString()] = a;
            standartModel = new QStandardItemModel(data.countRows(),data.countColumns(),this);
            data.fillingTheModel(standartModel);
            ui->tableView->setModel(standartModel);
            check2 = !check2;
        }
    }



}

