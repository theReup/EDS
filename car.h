//
// Created by sergey on 19.04.2021.
//

#ifndef TRINKET_CAR_H
#define TRINKET_CAR_H

#include "src/rsa.h"
#include "src/tea/xtea.h"
#include <iostream>
#include "SHA256.h"
#include <cstring>

using namespace crypto::rsa;
using namespace std;

class car{
private:

    string CODE_TO_OPEN_CAR = "777";
    SHA256 sha;
    string dataToVerify;
    RSAKeyPair trinketKey;

public:

    void getTrinketPublicKey(const string &pubKey);
    const string receiveAndSendDataToVerify(const string &inData);
    void verifySig(const string &signedData);

};

#endif //TRINKET_CAR_H
