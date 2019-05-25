#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "reciver.h"
#include "sender.h"
#include <string>

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT


public:
    explicit dialog(QWidget *parent = 0);
    ~dialog();
    project1::sender send1;
    QString u_name;
    reciver test_reciver;
    QString path;
    friend void print(dialog* d, reciver* test_reciver);

private slots:
    void on_but_connect_clicked();

    void on_but_send_clicked();

    void on_recieve_clicked();

    void on_entName_clicked();

    void on_AddFile_clicked();

private:
    std::future<void> recive_listener;
    Ui::dialog *ui;
};

#endif // DIALOG_H
