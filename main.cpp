#include "dialog.h"
#include <QApplication>
#include "reciver.h"

using namespace std;
//using namespace project;

void* recive_thread(reciver* t_reciver) {
        (*t_reciver).start();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog w;
    w.test_reciver.set_in_addr(INADDR_LOOPBACK);
    std::thread thread_obj(recive_thread, &(w.test_reciver));
    w.show();
    return a.exec();
}
