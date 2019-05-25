#include"reciver.h"
#include<vector>
#include <sys/stat.h>
#include<signal.h>
// C++ template to print vector container elements 
using namespace std;
template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
} 
//
reciver test_reciver;
void* recive_thread(reciver* t_reciver) {
        (*t_reciver).start();
}

void handler(int a){
    delete[]&test_reciver;
    exit(0);
}

int main() {
    test_reciver.init(50063);
    test_reciver.set_in_addr(INADDR_LOOPBACK);
    signal(SIGINT, handler);
    std::thread thread_obj(recive_thread, &test_reciver);
    while(true) {
        sleep(5);
        for(auto s : test_reciver.rcv_short_mess)
            cout << s << endl;
        cout << endl;
        fflush(stdout);
    }
}