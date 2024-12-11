#ifndef BYTEHELPER_H
#define BYTEHELPER_H

// 包含QString类头文件
#include <QString>

/**
 * @brief ByteHelper类，提供字节转换为易读字符串的静态方法
 */
class ByteHelper
{
public:
    /**
     * @brief 将字节数转换为易读的字符串格式
     * @param bytes 要转换的字节数
     * @return 返回转换后的易读字符串
     */
    static QString toBeautifulStr(qulonglong bytes);
};

#endif // BYTEHELPER_H
