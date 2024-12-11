#ifndef COMMON_H
#define COMMON_H

// 包含中间层的全局头文件
#include "middle/manglobal.h"

// 包含配置层的异常处理头文件
#include "config/exceptions.h"

// 包含配置层的错误码定义头文件
#include "config/errorcode.h"

// 包含配置层的API接口定义头文件
#include "config/apis.h"

// 包含配置层的全局变量定义头文件
#include "config/globals.h"

// 包含后端层的云管理头文件
#include "bend/man/mancloud.h"

// 包含中间层的模型管理头文件
#include "middle/manmodels.h"

// 包含中间层的信号管理头文件
#include "middle/signals/mansignals.h"

// 包含后端层的网关管理头文件
#include "bend/gateway.h"

// 包含辅助工具层的文件操作辅助头文件
#include "helper/filehelper.h"

// 包含辅助工具层的字节操作辅助头文件
#include "helper/bytehelper.h"

// 定义一个宏 STR，用于将本地8位字符串转换为QString
#define STR QString::fromLocal8Bit

#endif // COMMON_H
