#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>
#include <QByteArray>

#include "filehelper.h"

// 构造函数
FileHelper::FileHelper()
{
    // 构造函数中不需要特别的初始化操作
}

// 读取整个文本文件的内容
QString FileHelper::readAllTxt(const QString &filePath)
{
    QFile file(filePath); // 创建一个 QFile 对象，指向指定的文件路径
    if (file.exists() && file.open(QIODevice::ReadOnly)) // 检查文件是否存在并尝试以只读模式打开
    {
        QByteArray data = file.readAll(); // 读取文件的所有内容
        file.close(); // 关闭文件

        return data; // 返回读取到的数据
    }

    throw "读取文件失败"; // 如果文件不存在或无法打开，抛出异常
}

// 读取整个 JSON 文件的内容并转换为 QVariant
QVariant FileHelper::readAllJson(const QString &filePath)
{
    QString data = FileHelper::readAllTxt(filePath); // 调用 readAllTxt 方法读取文件内容
    QJsonDocument doc = QJsonDocument::fromJson(data.toLocal8Bit()); // 将字符串内容转换为 JSON 文档

    return doc.toVariant(); // 将 JSON 文档转换为 QVariant 并返回
}

// 读取整个 CSV 文件的内容并转换为 QList<QStringList>
QList<QStringList> FileHelper::readAllCsv(const QString &filePath)
{
    QList<QStringList> records; // 创建一个 QList<QStringList> 对象用于存储 CSV 记录
    QFile file(filePath); // 创建一个 QFile 对象，指向指定的文件路径
    if (file.exists() && file.open(QIODevice::ReadOnly)) // 检查文件是否存在并尝试以只读模式打开
    {
        QTextStream stream(&file); // 创建一个 QTextStream 对象用于读取文件内容
        while (!stream.atEnd()) // 循环读取文件的每一行
        {
            QString line = stream.readLine(); // 读取一行内容
            QStringList row = line.split(','); // 将一行内容按逗号分割成多个字段
            records.append(row); // 将分割后的字段列表添加到记录列表中
        }

        file.close(); // 关闭文件
    }

    return records; // 返回读取到的记录列表
}

// 生成异常文件（目前未实现）
void FileHelper::generateExceptionFile(const QString &filePath)
{
    // TODO: 实现生成异常文件的逻辑
}

// 将多行字符串写入文件
void FileHelper::writeFlie(const QStringList lines, const QString &filePath)
{
    QFile file(filePath); // 创建一个 QFile 对象，指向指定的文件路径
    if (file.open(QIODevice::WriteOnly)) // 尝试以只写模式打开文件
    {
        QTextStream stream(&file); // 创建一个 QTextStream 对象用于写入文件内容
        stream.setCodec("UTF-8"); // 设置编码为 UTF-8
        for (const auto &line : lines) // 循环遍历每一行字符串
        {
            stream << line << "\\n"; // 将每一行字符串写入文件，并换行
        }

        file.close(); // 关闭文件

        return; // 成功写入后返回
    }

    throw "写入文件失败"; // 如果文件无法打开，抛出异常
}

// 合并两个路径并返回规范化的路径
QString FileHelper::joinPath(const QString &path1, const QString &path2)
{
    QString path = path1 + "/" + path2; // 将两个路径简单拼接
    QStringList pathList = path.split(QRegExp("[/\\\\\\\\]"), Qt::SkipEmptyParts); // 使用正则表达式分割路径，跳过空部分
    path = pathList.join("/"); // 将分割后的路径部分重新用斜杠拼接

    return QDir::cleanPath(path); // 返回规范化后的路径
}

// 创建指定路径的目录
bool FileHelper::mkPath(const QString &path)
{
    QDir dir; // 创建一个 QDir 对象

    return dir.mkpath(path); // 创建指定路径的目录，如果成功返回 true，否则返回 false
}
