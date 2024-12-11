#ifndef FILEHELPER_H
#define FILEHELPER_H

// 包含必要的Qt头文件
#include <QVariant>
#include <QString>
#include <QList>

/**
 * @brief FileHelper类，用于文件操作的辅助类
 */
class FileHelper
{
public:
    /**
     * @brief 构造函数，初始化FileHelper对象
     */
    FileHelper();

    /**
     * @brief 读取文本文件的所有内容
     * @param filePath 文件路径
     * @return 返回文件内容的QString
     */
    static QString readAllTxt(const QString &filePath);

    /**
     * @brief 读取JSON文件的所有内容
     * @param filePath 文件路径
     * @return 返回文件内容的QVariant
     */
    static QVariant readAllJson(const QString &filePath);

    /**
     * @brief 读取CSV文件的所有内容
     * @param filePath 文件路径
     * @return 返回文件内容的QList<QStringList>，其中每个QStringList代表一行数据
     */
    static QList<QStringList> readAllCsv(const QString &filePath);

    /**
     * @brief 生成异常文件
     * @param filePath 文件路径
     */
    static void generateExceptionFile(const QString &filePath);

    /**
     * @brief 将多行内容写入文件
     * @param lines 要写入的QStringList，每个元素代表一行
     * @param filePath 文件路径
     */
    static void writeFlie(const QStringList lines, const QString &filePath);

    /**
     * @brief 拼接两个路径
     * @param path1 第一个路径
     * @param path2 第二个路径
     * @return 返回拼接后的路径
     */
    static QString joinPath(const QString &path1, const QString &path2);

    /**
     * @brief 创建目录
     * @param path 要创建的目录路径
     * @return 如果目录创建成功，返回true；否则返回false
     */
    static bool mkPath(const QString &path);
};

#endif // FILEHELPER_H
