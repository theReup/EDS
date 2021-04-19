//
// Created by sergey on 19.04.2021.
//

#include "car.h"

void car::getTrinketPublicKey(const string &pubKey){
    trinketKey.publicKey = pubKey;
}

const string car::receiveAndSendDataToVerify(const string &inData){
    cout << "_______________________" << endl;
    cout << "Receiving signal to open car" << endl;

    if(inData == sha.hash_of(CODE_TO_OPEN_CAR)){
        cout << "Signal is true, sending data to trinket to verify, hash of data:" << endl;

        Random randomDataToVerify;
        dataToVerify = std::to_string(randomDataToVerify.next());
        cout << sha.hash_of(dataToVerify) << endl;

        return sha.hash_of(dataToVerify);
    }

    else{
        cout << "Error!" << endl;
        return "Error!";
    }
}

void car::verifySig(const string &signedData){
    cout << "_______________________" << endl;
    cout << "Decrypting with public key:" << endl;
    cout << signedData << endl;

    ubyte *buf = new ubyte[signedData.length() * 2];
    ubyte* p = (ubyte*)signedData.c_str();
    RSA::decrypt(trinketKey.publicKey, p, signedData.length(), buf);
    string ret((char*)buf, sha.hash_of(dataToVerify).length());
    cout << "Hash of decrypted data:" << endl;
    cout << ret << endl;

    if(ret == sha.hash_of(dataToVerify)){
        cout << "Signature is true, opening car" << endl;
        cout << "CAR IS OPEN!" << endl;
    }
    else{
        cout << "Error!" << endl;
    }

    delete[] buf;

}

