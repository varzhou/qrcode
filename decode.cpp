#include <string>  
#include <fstream>
  
#include <zxing/LuminanceSource.h>  
#include <zxing/common/Counted.h>  
#include <zxing/Reader.h>  
#include <zxing/aztec/AztecReader.h>  
#include <zxing/common/GlobalHistogramBinarizer.h>  
#include <zxing/DecodeHints.h>  
#include <zxing/datamatrix/DataMatrixReader.h>  
#include <zxing/MultiFormatReader.h>  
#include <zxing/pdf417/PDF417Reader.h>  
#include <zxing/qrcode/QRCodeReader.h>  
  
#include <opencv2/opencv.hpp>
#include <zxing/MatSource.h>

int main(int argc, char** argv)
{
    std::string image_name(argv[1]);

    /* 读取文件内容 */
    cv::Mat matSrc = cv::imread(image_name, 1);  
    if (!matSrc.data) 
    {  
        printf("read image error: %s", image_name.c_str());  
        return -1;  
    }    
    
    /* 灰度化图像 */
    cv::Mat matGray;  
    cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);  
    
    /* LuminanceSource将不同平台的图像抽象成一个统一类，实现统一的接口 */ 
    zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);  
    int width = source->getWidth();  
    int height = source->getHeight();  
    printf("image width: %d, height: %d\n", width, height);
    
    /* 初始化一个reader，初始化qrcode，也就是一个二维码的reader */
    zxing::Ref<zxing::Reader> reader;  
    reader.reset(new zxing::qrcode::QRCodeReader);  
  
    /* Binarizer实现了图像的二值化处理 */
    zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));  
    
    /* BinaryBitmap 存储了二值化的图像 */
    zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));  
    
    /* reader实现真正的解析，得到了解码内容 */
    zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::QR_CODE_HINT)));  
    
    std::string str2 = result->getText()->getText();
    printf("recognization result: %s\n", str2.c_str());

    return 0;
}
