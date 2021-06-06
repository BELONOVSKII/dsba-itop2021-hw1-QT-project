#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airbnbdatabase.h"
#include <QStringListModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addItem(airbnbProperty& air);

signals:
    void sendData(airbnbProperty& air);

public slots:
    void recieveData(airbnbProperty& air);

private slots:
    void on_deleteButton_clicked();

    void on_searchButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_saveButton_clicked();

    void on_citySortButton_clicked();

    void on_BedroomsSort_clicked();

    void on_pushButton_3_clicked();

    void on_actionAbout_5_triggered();

    void style();

private:
    Ui::MainWindow *ui;
    airbnbDataBase data;
    QStandardItemModel *standartModel;
    bool check = false;
};
#endif // MAINWINDOW_H
