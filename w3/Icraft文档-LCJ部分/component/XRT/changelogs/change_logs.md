
                  
  
# 更新日志

## v3.8.0

- 

**修复BUG**

- 修复waitForReady不支持单位为s的问题

- 

**新增功能**

- 合并了诸葛分支代码，支持布衣和诸葛架构。

- 新增forward接口，可指定输出tensor数据存储地址。详见 [XRT使用手册1.3.2章节](../index.md)

- 新增setDumpOutputs接口，用于设置每层前向结束保存输出结果至指定路径下。详见 [XRT使用手册1.4.3章节](../index.md)

- 新增内存管理器类MemManager，和getAllMemChunk接口，用于获取当前已分配的内存情况。详见 [XRT使用手册1.5章节](../index.md)

- MemRegion.malloc接口新增字节对齐参数，默认为1。

- MemChunk添加修改deleter和autofree的接口。

## v3.7.0

- 对100TAI OpenDevice 时间进行优化

## v3.6.0

- 无

## v3.5.0

- 

**新增功能**

- 新增CreateWithSnapshot接口，用于从快照文件中构造网络。详见 [XRT使用手册1.1.3章节](../index.md)

- 新增dumpSnapshot， 用于序列化网络得到快照文件。详见 [XRT使用手册1.2章节](../index.md)

## v3.4.0

- 无

## v3.3.0

- 

**新增功能**

- mmu模式部署网络，可以减少部署时的内存消耗以及部署时间，具体可参见 [BuyiBackend使用手册1.1章节](../../buyibackend/index.md)

## v3.2.0

- 无

                