#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include "airbnbdatabase.h"
namespace Ui {
class editWindow;
}

class editWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editWindow(QWidget *parent = nullptr);
    ~editWindow();
signals:
    void sendData(airbnbProperty& air);

public slots:
    void recieveData(airbnbProperty& air);

private slots:
    void on_pushButton_clicked();

private:
    Ui::editWindow *ui;
};

#endif // EDITWINDOW_H
