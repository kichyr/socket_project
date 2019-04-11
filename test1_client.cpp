#include"clientSock.h"

int main() {
    clientSock client1;
    client1.connect("0.0.0.0", 8081);
    client1.write("fuck you");
    cout << client1.read();
}