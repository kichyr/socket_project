#include"sender.h"
#include<vector>
using namespace project1;

sender send1;

void handler(int a){
    delete[]&send1;
    exit(0);
}
int main() {
    
    send1.init(true, 4);
    try{
    send1.connect_all("0.0.0.0", 50063);
   /*  send1.send_short_msg("fuck you");
    sleep(2);
    send1.send_short_msg("fuck you2");
    send1.send_short_msg("fuck you3");
    send1.send_short_msg("fusdfksdfjsdfjsdfjsdfhsdhjfhjdshfjdshfh"); */
    } catch (std::string s) {
        std::cout << s;
    }
    char* path = "/home/kichyr/infa_4sem/socket_sender/test_sendin_file.txt";
    send1.send_file(path);
    while(1){}
    //send1.send_short_msg("no fuck you");
    return 0;
}