#include"sender.h"
#include<vector>

int main() {
    sender send1(true, 4);
    try{
    send1.connect_all("0.0.0.0", 50055);
    send1.send_short_msg("fuck you");
    sleep(2);
    send1.send_short_msg("fuck you2");
    send1.send_short_msg("fuck you3");
    send1.send_short_msg("fusdfksdfjsdfjsdfjsdfhsdhjfhjdshfjdshfh");
    } catch (std::string s) {
        std::cout << s;
    }

    //send1.send_short_msg("no fuck you");
    return 0;
}