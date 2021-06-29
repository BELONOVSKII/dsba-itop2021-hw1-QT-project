#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airbnbdatabase.h"
#include <QStringListModel>
#include <set>
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
    std::set<QString> getSet();

signals:
    void sendData(airbnbProperty& air);


public slots:
    void recieveData(airbnbProperty& air);

    void onTableClicked(const QModelIndex &);

    void onTableClicked1(const QModelIndex &);

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
    bool check2 = false;
    QModelIndex index1;
    QString title;
    QString city;
};
#endif // MAINWINDOW_H
