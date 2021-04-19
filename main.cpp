#include "car.h"
#include "trinket.h"

using namespace std;

int main() {

    car myCar;
    trinket myTrinket;

    myCar.getTrinketPublicKey(myTrinket.getPublicKey());

    myCar.verifySig(myTrinket.generateSig(
            myCar.receiveAndSendDataToVerify(myTrinket.sendSignal())));

    return 0;
}