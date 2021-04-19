#include "rsa.h"
#include "tea/xtea.h"
#include "utils/random.h"
#include "utils/utility.h"
#include "base64.h"
#include <iostream>
using namespace std;
using namespace crypto::rsa;
using namespace crypto::base64;

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#define DLL_EXPORT __declspec(dllexport) __stdcall
#ifdef __cplusplus
extern "C"
{
#endif

size_t DLL_EXPORT rsaKeyGenerate(int bitLength, char* buf);
long   DLL_EXPORT rsaEncrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result);
long   DLL_EXPORT rsaDecrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result);

#ifdef __cplusplus
}
#endif

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}

#else

extern "C" size_t rsaKeyGenerate(int bitLength, char* result);
extern "C" long   rsaEncrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result);
extern "C" long   rsaDecrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result);

#endif

size_t rsaKeyGenerate(int bitLength, char* result)
{
    RSAKeyPair keyPair = RSA::generateKeyPair(bitLength);
    string key = "privateKey:\r\n" + keyPair.privateKey + "\r\npublicKey:\r\n" + keyPair.publicKey;

    ubyte* p = (ubyte*)key.c_str();
    size_t i;
    for (i = 0; i < key.length(); i++)
    {
        result[i] = p[i];
    }
    result[i] = 0;

    return key.length();
}

long rsaEncrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result)
{
    string sKey(key, keyLength);
    ubyte* buf = new ubyte[len * 2 + keyLength];
    size_t t_len = 0;

    try
    {
        t_len = RSA::encrypt(sKey, data, len, buf, true);
    }
    catch (...)
    {
        delete[] buf;
        return -1;
    }

    string baseStr = crypto::base64::Base64::encode(buf, t_len);
    delete[] buf;

    size_t i = 0;
    ubyte* p = (ubyte*)baseStr.c_str();

    while (i < baseStr.size())
    {
        result[i] = p[i];
        i++;
    }
    result[i] = 0;

    return (long)baseStr.size();
}

long rsaDecrypt(char* key, int keyLength, ubyte* data, size_t len, ubyte* result)
{
    string sData((char*)data, len);
    unsigned char* buf = new unsigned char[len * 2];
    size_t t_len = 0;

    try
    {
        t_len = crypto::base64::Base64::decode(sData, buf);
    }
    catch (...)
    {
        delete[] buf;
        return -1;
    }

    string sKey(key, keyLength);

    try
    {
        t_len = RSA::decrypt(sKey, buf, t_len, result, true);
    }
    catch (...)
    {
        delete[] buf;
        return -2;
    }

    delete[] buf;

    return (long)t_len;
}
