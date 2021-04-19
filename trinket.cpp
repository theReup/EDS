//
// Created by sergey on 19.04.2021.
//

#include "trinket.h"

const string trinket::getPublicKey(){
    return trinketKeyPair.publicKey;
}

const string trinket::sendSignal(){
    cout << "_______________________" << endl;
    cout << "Sending signal to car to open car, hash of data:" << endl;
    cout << sha.hash_of(CODE_TO_OPEN_CAR) << endl;
    return sha.hash_of(CODE_TO_OPEN_CAR);
}

const string trinket::generateSig(const string &inData){
    cout << "_______________________" << endl;
    cout << "Encrypting with secret key and sending to car:" << endl;

    ubyte* buf = new ubyte[inData.length() * 2 + 256]; // 256 is key size.
    ubyte* p = (ubyte*)inData.c_str();
    size_t len = RSA::encrypt(trinketKeyPair.privateKey, p, strlen((char*)p), buf);// reading data from p, encrypting and putting into buf
    string ret((char*)buf, len);
    cout << ret << endl;
    delete[] buf;

    return ret;
}

trinket::trinket(){
    cout << "_______________________" << endl;
    cout << "Trinket keypair is generated, public key is:" << endl;
    cout << trinketKeyPair.publicKey << endl;
}
