#ifndef APIS_H
#define APIS_H

// 定义一个名为 API 的命名空间
namespace API
{
// 定义一个名为 LOGIN 的命名空间，用于处理登录相关的接口编号
namespace LOGIN
{
// 定义一个静态常量 NORMAL，表示常规登录的接口编号为 1
static const int NORMAL = 1;
}

// 定义一个名为 BUCKETS 的命名空间，用于处理桶操作相关的接口编号
namespace BUCKETS
{
// 定义一个静态常量 BASE，表示桶操作接口的基础编号为 100
static const int BASE = 100;

// 定义一个静态常量 LIST，表示获取桶列表的接口编号为 BASE + 1
static const int LIST = BASE + 1;

// 定义一个静态常量 PUT，表示创建桶的接口编号为 BASE + 2
static const int PUT = BASE + 2;

// 定义一个静态常量 DEL，表示删除桶的接口编号为 BASE + 3
static const int DEL = BASE + 3;
} // namespace BUCKETS

// 定义一个名为 OBJECTS 的命名空间，用于处理对象操作相关的接口编号
namespace OBJECTS
{
// 定义一个静态常量 BASE，表示对象操作接口的基础编号为 200
static const int BASE = 200;

// 定义一个静态常量 LIST，表示获取对象列表的接口编号为 BASE + 1
static const int LIST = BASE + 1;

// 定义一个静态常量 GET，表示下载对象的接口编号为 BASE + 10
static const int GET = BASE + 10;

// 定义一个静态常量 PUT，表示上传对象的接口编号为 BASE + 20
static const int PUT = BASE + 20;
} // namespace OBJECTS
} // namespace API

#endif // APIS_H
