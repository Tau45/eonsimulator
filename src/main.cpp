#include "../include/network/Network.h"
#include "../include/network/Benes4x4.h"

using namespace std;

int main() {
    Network *network = new Benes4x4();

    network->establishConnection(2, 0, 2);
    network->establishConnection(3, 0, 1);
    network->establishConnection(3, 1, 1);

    return 0;
}