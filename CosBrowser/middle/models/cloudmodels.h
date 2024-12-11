#ifndef CLOUDMODELS_H
#define CLOUDMODELS_H

// 包含必要的Qt头文件
#include <QString>
#include <QMetaType>

/**
 * @brief BaseObject结构体，表示基础对象
 */
struct BaseObject
{
    /**
     * @brief 检查对象是否有效
     * @return 如果对象有效，返回true；否则返回false
     */
    bool isValid() const { return !isInvalid(); }

    /**
     * @brief 检查对象是否无效
     * @return 如果对象无效，返回true；否则返回false
     */
    bool isInvalid() const { return name.isNull() || name.isEmpty(); }

    /**
     * @brief 对象的名称
     */
    QString name;
};

// 注册BaseObject为元类型，以便在信号和槽中使用
Q_DECLARE_METATYPE(BaseObject);

/**
 * @brief MyBucket结构体，继承自BaseObject，表示云存储中的存储桶
 */
struct MyBucket : public BaseObject
{
    /**
     * @brief 构造函数，初始化MyBucket对象
     */
    MyBucket();

    /**
     * @brief 存储桶的位置
     */
    QString location;

    /**
     * @brief 存储桶的创建日期
     */
    QString createDate;
};

// 注册MyBucket为元类型，以便在信号和槽中使用
Q_DECLARE_METATYPE(MyBucket);

/**
 * @brief MyObject结构体，继承自BaseObject，表示云存储中的对象（文件或目录）
 */
struct MyObject : public BaseObject
{
    /**
     * @brief 检查对象是否为目录
     * @return 如果对象是目录，返回true；否则返回false
     */
    bool isDir() const { return isValid() && name.endsWith("/"); }

    /**
     * @brief 检查对象是否为文件
     * @return 如果对象是文件，返回true；否则返回false
     */
    bool isFile() const { return isValid() && !name.endsWith("/"); }

    /**
     * @brief 对象的最后修改时间
     */
    QString lastmodified;

    /**
     * @brief 对象的大小（以字节为单位）
     */
    qulonglong size = 0;

    /**
     * @brief 对象所在的目录
     */
    QString dir;

    /**
     * @brief 对象的键（唯一标识符）
     */
    QString key;
};

// 注册MyObject为元类型，以便在信号和槽中使用
Q_DECLARE_METATYPE(MyObject);

#endif // CLOUDMODELS_H
