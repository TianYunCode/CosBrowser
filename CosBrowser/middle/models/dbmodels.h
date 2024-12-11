#ifndef DBMODELS_H
#define DBMODELS_H

// 包含必要的Qt头文件
#include <QString>

/**
 * @brief LoginInfo结构体，表示登录信息
 */
struct LoginInfo
{
    /**
     * @brief 用户名
     */
    QString name;

    /**
     * @brief 密钥ID，用于身份验证
     */
    QString secret_id;

    /**
     * @brief 密钥，用于身份验证
     */
    QString secret_key;

    /**
     * @brief 备注信息，用于描述登录信息
     */
    QString remark;

    /**
     * @brief 时间戳，表示登录信息的时间
     */
    uint timestamp;
};

#endif // DBMODELS_H
