#include <stdio.h>
#include <fstream>
#include "qr.h"

using namespace std;

int main(int argc, char** argv)
{
    int errcode = QR_ERR_NONE;
    //qrInit的5个参数分别是version,mode,纠错等级和掩码。
    QRCode* p = qrInit(10, QR_EM_8BIT, QR_ECL_Q, -1, &errcode);
    if (p == NULL)
    {
        printf("error\n");
        return -1;
    }

    string strData(argv[1]);
    qrAddData(p, (const qr_byte_t*)strData.data(), strData.length());
    //注意需要调用qrFinalize函数
    if (!qrFinalize(p))
    {
        printf("finalize error\n");
        return -1;
    }
    int size = 0;
    //两个5分别表示：像素之间的距离和二维码图片的放大倍数，范围都是1-16
    qr_byte_t * buffer = qrSymbolToBMP(p, 5, 5, &size);
    if (buffer == NULL)
    {
        printf("error %s", qrGetErrorInfo(p));
        return -1;
    }
    ofstream f(argv[2]);
    f.write((const char *)buffer, size);
    f.close();
    return 0;
}
