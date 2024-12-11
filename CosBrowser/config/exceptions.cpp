#include <QDebug>

#include "exceptions.h"
#include "globals.h"
#include "helper/filehelper.h"

/**
 * @brief BaseException类的构造函数
 *
 * 该构造函数用于初始化BaseException对象，设置错误代码和错误信息。
 *
 * @param code 错误代码
 * @param msg 错误信息
 */
BaseException::BaseException(const QString &code, const QString &msg)
{
    m_code = code;
    m_msg = msg;
}

/**
 * @brief 解析错误代码的函数
 *
 * 该函数用于从CSV文件中解析错误代码和对应的错误信息，并将其存储在ErrorMap中。
 *
 * @param csvPath CSV文件的路径
 * @return 包含错误代码和错误信息的ErrorMap
 */
ErrorMap BaseException::parseErrorCode(const QString &csvPath)
{
    ErrorMap m_map;
    int sectionCount = 6; // CSV文件中每行的段数
    QList<QStringList> records = FileHelper::readAllCsv(csvPath); // 读取CSV文件中的所有记录

    // 遍历CSV文件中的每一行记录
    for (int i = 1; i < records.size(); i++)
    {
        auto record = records[i];
        QString code;
        QString msg;

        // 遍历每一行的每个段
        for (int j = 0; j < sectionCount; ++j)
        {
            if (record[j] == "")
            {
                // 如果段为空，则将代码部分填充为"0"
                code += "0";
            }
            else
            {
                // 将段按"_"分割，并将前半部分作为错误信息，后半部分作为错误代码
                QStringList strs = record[j].split("_");
                msg += strs[0];
                code += strs[1];
            }
        }

        // 如果最后一列为非空，则将其作为错误信息
        if (record[sectionCount] != "")
        {
            msg = record[sectionCount];
        }

        // 将错误代码和错误信息存储在ErrorMap中
        m_map[code] = msg;
    }

    return m_map;
}

/**
 * @brief 生成错误代码头文件的函数
 *
 * 该函数用于从CSV文件中解析错误代码和对应的错误信息，并生成一个包含这些信息的头文件。
 *
 * @param csvPath CSV文件的路径
 * @param targetPath 生成的头文件的目标路径
 */
void BaseException::generateErrorCodeHFile(const QString &csvPath, const QString &targetPath)
{
    QStringList rows;
    rows << "#ifndef ERRORCODE_H" << "#define ERRORCODE_H\\n\\n"; // 头文件保护

    ErrorMap errors = parseErrorCode(csvPath); // 解析错误代码
    ErrorMap::const_iterator iter = errors.constBegin();

    // 遍历ErrorMap，生成头文件内容
    while (iter != errors.constEnd())
    {
        rows << QString::fromLocal8Bit("#define EC_%1 \"%1\"  // %2").arg(iter.key(), iter.value());

        ++iter;
    }

    rows << "\\n\\n#endif // ERRORCODE_H"; // 头文件结束
    FileHelper::writeFlie(rows, targetPath); // 将生成的内容写入头文件
}

/**
 * @brief 获取错误信息的函数
 *
 * 该函数用于获取完整的错误信息，包括错误代码和错误描述。
 *
 * @return 完整的错误信息
 */
QString BaseException::msg() const
{
    // 从全局路径中解析错误代码
    static ErrorMap m_map = BaseException::parseErrorCode(GLOBAL::PATH::ERROR_CODE_PATH);
    QString m = QString::fromLocal8Bit("错误(%1): %2").arg(m_code, m_map[m_code]);

    // 如果存在额外的错误信息，则将其附加到错误信息中
    if (m_msg != "")
    {
        m += QString::fromLocal8Bit("，详情: %1").arg(m_msg);
    }

    return m;
}

/**
 * @brief 获取错误代码的函数
 *
 * 该函数用于获取当前对象的错误代码。
 *
 * @return 错误代码
 */
QString BaseException::code() const
{
    return m_code;
}
