# ULog

该模块可生成一种自描述的二进制日志文件，其格式符合PX4的日志格式要求。

## 使用方法

### 1、定义类型

使用ULog前，需要在`Topic/Topic.xlse`文件中定义日志中要保存的数据的类型，具体规则如下：

- excel文件的一个sheet代表一个数据类型，对应一个C语言的结构体类型，sheet的名称对应着结构体的名称；
- sheet中的一行，代表结构体中的一个元素；
- 第一列定义元素的类型，第二列定义元素的组数，第三列定义元素的名称；

### 2、生成类型和函数

可以通过以下两种方式生成日志保存所需要的类型和函数：

- 在matlab中运行`Generate.m`脚本，将会生成`Topic.h`和`Topic.c`文件；
- 手动编写`ULogInit`函数所需要`ULOG_VARIABLE_ENTER_T`结构体相关的内容；

### 3、保存数据

通过`ULogUpdateID`或`ULogUpdateName`向日志中保存数据，每次调用保存一个数据类型。

## 目录概览
```
.
├── core
│     ├── inc
│     │    ├── ulog.h             # 对外接口头文件
│     │    └── ulog_internal.h    # 内部头文件
│     └── src
│          └── ulog.c             # 核心代码
├── Tool
│     ├── flightplot.jar          # 日志文件解析工具
│     ├── Generate.m              # matlab脚本，根据用户在Topic/Topic.xlse中定义的要保存到日志中数据的类型，生成日志保存所需要的类型和函数
│     ├── Parse.m                 # matlab脚本，根据用户在Topic/Topic.xlse中定义的要保存到日志中数据的类型，解析日志文件，并生成matlab数据
│     └── Function                # 以上两个matlab脚本所需要用到的函数
├── Topic
│     ├── Topic.xlse              # 该文件定义需要保存到日志中数据的类型
│     ├── Topic.h                 # Generate.m产生的类型定义
│     └── Topic.c                 # Generate.m产生的函数定义 
├── _Doc
│     └── ULog.pdf                # 内部头文件
└── _example                      # 例程
```
