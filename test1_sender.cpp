#include"sender.h"
#include<vector>

int main() {
    std::vector<int> ports = {8081, 8081, 8081};
    sender send1("0.0.0.0", ports);
    send1.connect_all();
    send1.send_short_msg("fuck you");
}