#include <QVector>
#include "qmath.h"

#include "bytehelper.h"

// 将字节数转换为人类可读的字符串格式
QString ByteHelper::toBeautifulStr(qulonglong bytes)
{
    // 如果字节数小于 1024 字节，直接返回字节数加上单位 "B"
    if (bytes < 1024)
    {
        return QString("%1 B").arg(bytes);
    }
    // 如果字节数小于 1024 * 1024 字节（即小于 1MB），转换为 KB 并返回
    else if (bytes < 1024 * 1024)
    {
        return QString("%1 KB").arg(bytes / 1024);
    }
    // 如果字节数小于 1024 * 1024 * 1024 字节（即小于 1GB），转换为 MB 并返回
    else if (bytes < 1024 * 1024 * 1024)
    {
        return QString("%1 MB").arg(bytes / (1024 * 1024));
    }
    // 如果字节数大于等于 1024 * 1024 * 1024 字节（即大于等于 1GB），转换为 GB 并返回
    else
    {
        return QString("%1 GB").arg(bytes / (1024 * 1024 * 1024));
    }
}
