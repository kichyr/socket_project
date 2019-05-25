#include "dialog.h"
#include "ui_dialog.h"
#include "sender.h"
#include "reciver.h"
#include <vector>
#include <string>
#include <QTextStream>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
using namespace std;
/*
std::ostream&  operator <<(std::ostream &stream,const QString &str)
{
   stream << str.toUtf8().constData(); //or: stream << str.toStdString(); //??
   return stream;
}*/


dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);
    test_reciver.init(50069);
    send1.init(true, 0);
    reciver* test_reciver_ptr = &test_reciver;
    recive_listener = std::async(std::launch::async, [this, test_reciver_ptr](){
           print(this, test_reciver_ptr);
    });

}

dialog::~dialog()
{
    delete ui;
}

void print(dialog* d, reciver* test_reciver) {
    int num_recived_mess = 0;
    int iterator = 0;
    QString name;
    while(true) {
        sleep(1);
        if((test_reciver->rcv_short_mess.size() != num_recived_mess) && iterator == 0) {
            QString s = QString::fromStdString(test_reciver->rcv_short_mess[num_recived_mess]);
            name = s;
            num_recived_mess++;
            iterator++;
        }
        else if((test_reciver->rcv_short_mess.size() != num_recived_mess) && iterator != 0) {
            QString s = QString::fromStdString(test_reciver->rcv_short_mess[num_recived_mess]);
            d->ui->log->insertItem(0,name + " : " + s);
            d->ui->log->item(0)->setTextColor(Qt::blue);
            num_recived_mess++;
        }
    }
}

void dialog::on_but_connect_clicked()
{
    if(u_name.isEmpty()){
        QMessageBox::warning(this, "warning","Enter Name");
        return;
    }
    QString ip1 = ui->ip->text();
    if(ip1.isEmpty()){
        QMessageBox::warning(this, "warning","Enter IP");
        return;
    }
    string ip = ip1.toUtf8().constData();
    QString port1 = ui->port->text();
    if(port1.isEmpty()){
        QMessageBox::warning(this, "warning","Enter Port");
        return;
    }
    int port = port1.toInt();
    send1.connect_all(ip, port);
    string str = u_name.toUtf8().constData();
    send1.send_short_msg(str);


}



void dialog::on_but_send_clicked()
{

    QString text = ui->message->text();
    if(text.isEmpty()){
        return;
    }
    string text1 = text.toUtf8().constData();
    text = u_name + " : " + text;
    //std::T << text.toUtf8().constData();
    if(u_name.isEmpty()){
        return;
    }
    send1.send_short_msg(text1);
    //string s = test_reciver.rcv_short_mess();
    ui->log->insertItem(0, text);
    ui->log->item(0)->setTextColor(Qt::green);
    //ui->log->append(text);
    ui->message->clear();
}


void dialog::on_entName_clicked()
{
    u_name = ui->name->text();
    //u_name = str.toUtf8().constData();
}

void dialog::on_AddFile_clicked()
{
    path = QFileDialog::getOpenFileName(0,QObject::tr("Chose file"),QDir::homePath(), QObject::tr("Все файлы (*.*)"));
    ui->log->insertItem(0, path);
}
