#include "../include/network/Network.h"
#include "../include/network/Benes4x4.h"

using namespace std;

int main() {
    Network *network = new Benes4x4();

    uint64_t connectionId = 0;

    Connection *conn1 = new Connection(connectionId++, 2, 0, 2);
    Connection *conn2 = new Connection(connectionId++, 3, 0, 1);
    Connection *conn3 = new Connection(connectionId++, 3, 1, 1);

    network->tryToEstablishConnection(conn1);
    network->tryToEstablishConnection(conn2);
    network->tryToEstablishConnection(conn3);

    network->closeConnection(conn1->id);

    Connection *conn4 = new Connection(connectionId++, 2, 0, 1);
    Connection *conn5 = new Connection(connectionId++, 2, 0, 2);
    Connection *conn6 = new Connection(connectionId++, 2, 0, 1);
    Connection *conn7 = new Connection(connectionId++, 2, 0, 1);

    network->tryToEstablishConnection(conn4);
    network->tryToEstablishConnection(conn5);
    network->tryToEstablishConnection(conn6);
    network->tryToEstablishConnection(conn7);

    return 0;
}