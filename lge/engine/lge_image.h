#pragma once

NAMESPACE_BEGIN

class Image
{
public:
    Image(const char* fileName);
    Image(unsigned char* data, int length);
private:
    int m_width;
    int m_height;
    int m_bpp;
    bool m_hasAlpha;
    bool m_isPremultipliedAlpha;
    std::string m_fileName;
    unsigned char* m_data;
};

NAMESPACE_END