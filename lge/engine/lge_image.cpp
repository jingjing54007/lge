#include "lge_platform.h"
#include "lge_image.h"

NAMESPACE_BEGIN

Image::Image(const char* fileName)
{
    FILE* fp = fopen(fileName, "rb");
    int fileSize = 0;
    fseek(fp,0,SEEK_END);
    fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);
    
    unsigned char* pBuffer = new unsigned char[fileSize + 1];
    pBuffer[fileSize] = 0;
    fclose(fp);
    
    Image(pBuffer, fileSize);

    delete pBuffer;
}

NAMESPACE_END
