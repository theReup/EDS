//
// Created by sergey on 19.04.2021.
//

#ifndef TRINKET_TRINKET_H
#define TRINKET_TRINKET_H

#include "src/rsa.h"
#include "src/tea/xtea.h"
#include <iostream>
#include "SHA256.h"
#include <cstring>

using namespace crypto::rsa;
using namespace std;

class trinket{
private:

    string CODE_TO_OPEN_CAR = "777";
    RSAKeyPair trinketKeyPair = RSA::generateKeyPair(256);
    SHA256 sha;

public:

    const string getPublicKey();
    const string sendSignal();
    const string generateSig(const string &inData);
    trinket();

};

#endif //TRINKET_TRINKET_H
