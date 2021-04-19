#include "rsa.h"
#include "tea/xtea.h"
//#include "aes.h"
#include <iostream>
#include <cstring>
//
using namespace crypto::rsa;

int main()
{
    RSAKeyPair keyPair = RSA::generateKeyPair(256);
    cout << keyPair.privateKey << endl;
    cout << keyPair.publicKey << endl;

    string data = "Copyright: Copyright Digital Mars 2007 - 2011.License:   $(HTTP www.boost.org/LICENSE_1_0.txt, Boost License 1.0).";

    ubyte* buf = new ubyte[data.length() * 2 + 256]; // 256 is key size.
    ubyte* p = (ubyte*)data.c_str();
    size_t len = RSA::encrypt(keyPair.privateKey, p, strlen((char*)p), buf);

    ubyte* buf2 = new ubyte[data.length() * 2];
    len = RSA::decrypt(keyPair.publicKey, buf, len, buf2);

    string ret((char*)buf2, len);
    cout << ret << endl;

    delete[] buf;
    delete[] buf2;

    return 0;
}