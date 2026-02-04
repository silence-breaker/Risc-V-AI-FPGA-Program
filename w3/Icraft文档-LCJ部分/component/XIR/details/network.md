
                  
  
# 网络

`XIR` 中一个网络是由一系列算子组成的，这些算子通过输入输出相互连接，构成了一个有向无环图。
网络中的算子是存储在 `Array` 容器中的，其在 `Array` 中的顺序代表了执行顺序

网络主要有以下几个属性：

- 
`name`：网络名称

- 
`framework_kind`：前端框架的种类

- 
`framework_version`：前端框架的版本

- 
`icraft_xir_version`： `XIR` 的版本

- 
`icraft_version`： `Icraft` 版本

- 
`params_bytes`：网络中所有参数的字节大小

- 
`params_md5`：参数的 `MD5` ，用于校验

- 
`ops`：网络的算子列表

## 网络的构造

如何构造一个网络在开头的例子中已经展现了，所以此处不在赘述

## 增删查改

网络中涉及到 `CRUD` 的 `API` 主要有以下几个：

- 
`addOp`：添加算子到列表尾部

- 
`insertOpById`：将算子插入到指定 `ID` 的算子前面

- 
`insertOp`：将算子插入到指定的 `index` 的算子前面

- 
`removeOpById`：移除指定 `ID` 的算子

- 
`removeOpsById`：一次性移除指定 `ID` 的若干算子，但保留它们之间的连接关系

- 
`removeOp`：移除符合条件的算子

- 
`getOpById`：获取指定 `ID` 的算子

- 
`replaceOpById`：将指定 `ID` 的算子替换为其他算子

下面的例子展示了网络中增删查改的一些 `API` 和使用方法，更多的方法请参考模式匹配章节：

```cpp
auto network = Network("whatever", Framework::PYTORCH, "v1.9");

auto input_type = TensorType(FloatType::FP32(), { 1, 416, 416, 3 }, Layout::NHWC());
auto input = Input(input_type);
input.setId(100);            // 为算子指定大于0的ID，网络会使用该ID，否则网络会自动生成ID
network.addOp(input);

auto weight_type = TensorType(FloatType::FP32(), { 3, 3, 3, 16 }, Layout::HWIO());
auto weight = Params(weight_type).fill<float>([](size_t i) { return (float)i; });
auto conv2d = Conv2d(input[0], weight, NullOpt, 1, 1, 1);
network.addOp(conv2d);

auto relu = ReLU(conv2d[0]);
network.addOp(relu);

auto max_pool2d = MaxPool2d(relu[0], 3, 2, 1, 1);
network.addOp(max_pool2d);

auto output = Output(max_pool2d[0]);
network.addOp(output);

// 获取输入算子
std::cout << "inputOp: " << std::setw(4) << network->ops[0] << std::endl;
// 获取指定ID的算子
std::cout << "op(1): " << std::setw(4) << network.getOpById(1) << std::endl;

// 删除算子，以下四种写法结果是一样的，都是删除了relu算子
// network.removeOpById(relu->op_id);
// network.removeOp([](auto op) { return op.is<ReLU>(); });
// network.removeOp([](auto op) { return op->hasAttr("threshold"); });
network.removeOp([](auto op) { return op->getAttr("threshold").value_or<float>(-1.f) == 0; });

std::cout << std::setw(4) << network << std::endl;
```

以上代码的输出如下：

```cpp
inputOp: {
   "_type_key": "icraft::xir::Input",
   "compile_target": "@hostt",
   "inputs": [],
   "name": "",
   "op_id": 100,
   "outputs": [
      {
            "_type_key": "icraft::xir::Value",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(NHWC)",
               "merged_distrs": [],
               "shape": [
                  1,
                  416,
                  416,
                  3
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 0
      }
   ],
   "tags": {}
}
op(101): {
   "_type_key": "icraft::xir::Conv2d",
   "compile_target": "@hostt",
   "cut_scale": "@scales([axis=-1])",
   "dilation_height": 1,
   "dilation_width": 1,
   "groups": 1,
   "inputs": [
      {
            "_type_key": "icraft::xir::Value",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(NHWC)",
               "merged_distrs": [],
               "shape": [
                  1,
                  416,
                  416,
                  3
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 0
      },
      {
            "_allow_no_data": false,
            "_type_key": "icraft::xir::Params",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(HWIO)",
               "merged_distrs": [],
               "shape": [
                  3,
                  3,
                  416,
                  16
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 1
      }
   ],
   "name": "",
   "op_id": 101,
   "outputs": [
      {
            "_type_key": "icraft::xir::Value",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(NHWC)",
               "merged_distrs": [],
               "shape": [
                  1,
                  416,
                  416,
                  16
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 2
      }
   ],
   "pad_bottom": 1,
   "pad_left": 1,
   "pad_right": 1,
   "pad_top": 1,
   "padding_mode": "ZEROS",
   "stride_height": 1,
   "stride_width": 1,
   "tags": {}
}
{
   "_type_key": "icraft::xir::Network",
   "framework_kind": "PYTORCH",
   "framework_version": "v1.9",
   "icraft_version": "v0.0.0",
   "icraft_xir_version": "3.6.2.82",
   "name": "whatever",
   "ops": [
      {
            "_type_key": "icraft::xir::Input",
            "compile_target": "@hostt",
            "inputs": [],
            "name": "",
            "op_id": 100,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           3
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 0
               }
            ],
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::Conv2d",
            "compile_target": "@hostt",
            "cut_scale": "@scales([axis=-1])",
            "dilation_height": 1,
            "dilation_width": 1,
            "groups": 1,
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           3
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 0
               },
               {
                  "_allow_no_data": false,
                  "_type_key": "icraft::xir::Params",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(HWIO)",
                        "merged_distrs": [],
                        "shape": [
                           3,
                           3,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 1
               }
            ],
            "name": "",
            "op_id": 101,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 2
               }
            ],
            "pad_bottom": 1,
            "pad_left": 1,
            "pad_right": 1,
            "pad_top": 1,
            "padding_mode": "ZEROS",
            "stride_height": 1,
            "stride_width": 1,
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::MaxPool2d",
            "compile_target": "@hostt",
            "dilation_height": 1,
            "dilation_width": 1,
            "inputs": [],
            "name": "",
            "op_id": 103,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           208,
                           208,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 4
               }
            ],
            "pad_bottom": 1,
            "pad_left": 1,
            "pad_right": 1,
            "pad_top": 1,
            "pool_height": 3,
            "pool_width": 3,
            "stride_height": 2,
            "stride_width": 2,
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::Output",
            "compile_target": "@hostt",
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           208,
                           208,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 4
               }
            ],
            "name": "",
            "op_id": 104,
            "outputs": [],
            "tags": {}
      }
   ],
   "params_bytes": 0,
   "params_md5": "d41d8cd98f00b204e9800998ecf8427e",
   "tags": {}
}
```

## 执行序和连接序

老的 `IR` 中同时使用了 `pre/next` 以及 `producer/consumer` 的概念来表达算子的连接关系，比较冗余。
`XIR` 中使用 `pre/next` 的概念来表达算子执行序的前后关系，使用 `producer/consumer` 的概念来表达算子连接的关系

```cpp
auto network = Network("whatever", Framework::PYTORCH, "v1.9");

auto input_type = TensorType(FloatType::FP32(), { 1, 416, 416, 3 }, Layout::NHWC());
auto input = Input(input_type);
network.addOp(input);

auto weight_type = TensorType(FloatType::FP32(), { 3, 3, 3, 16 }, Layout::HWIO());
auto weight = Params(weight_type).fill<float>([](size_t i) {return (float)i; });
auto conv2d = Conv2d(input[0], weight, NullOpt, 1, 1, 1);
network.addOp(conv2d);

auto relu = ReLU(conv2d[0]);
network.addOp(relu);

auto max_pool2d = MaxPool2d(relu[0], 3, 2, 1, 1);
network.addOp(max_pool2d);

auto output = Output(max_pool2d[0]);
network.addOp(output);

// 获取执行序maxpool的前一个算子
std::cout << "maxpool.preOp: " << std::setw(4) << maxpool.preOp() << std::endl;

// 获取连接序max_pool2d的生产者，即输出作为max_pool2d的输入
std::cout << "max_pool2d.producers: " << std::setw(4) << max_pool2d.producers() << std::endl;

// 获取max_pool2d所在的网络
std::cout << "max_pool2d.network: " << std::setw(4) << max_pool2d.network() << std::endl;
```

以上代码的执行结果如下：

```cpp
max_pool2d.preOp: {
   "_type_key": "icraft::xir::ReLU",
   "alpha": 0.0,
   "compile_target": "@hostt",
   "inputs": [
      {
            "_type_key": "icraft::xir::Value",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(NHWC)",
               "merged_distrs": [],
               "shape": [
                  1,
                  416,
                  416,
                  16
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 2
      }
   ],
   "max_value": "inf",
   "name": "",
   "op_id": 2,
   "outputs": [
      {
            "_type_key": "icraft::xir::Value",
            "dtype": {
               "_type_key": "icraft::xir::TensorType",
               "element_dtype": "@fp(32)",
               "layout": "@layout(NHWC)",
               "merged_distrs": [],
               "shape": [
                  1,
                  416,
                  416,
                  16
               ]
            },
            "mtype": "@hostm",
            "name": "",
            "tags": {},
            "v_id": 3
      }
   ],
   "tags": {},
   "threshold": 0.0
}
max_pool2d.producers: [
   {
      "_type_key": "icraft::xir::ReLU",
      "alpha": 0.0,
      "compile_target": "@hostt",
      "inputs": [
            {
               "_type_key": "icraft::xir::Value",
               "dtype": {
                  "_type_key": "icraft::xir::TensorType",
                  "element_dtype": "@fp(32)",
                  "layout": "@layout(NHWC)",
                  "merged_distrs": [],
                  "shape": [
                        1,
                        416,
                        416,
                        16
                  ]
               },
               "mtype": "@hostm",
               "name": "",
               "tags": {},
               "v_id": 2
            }
      ],
      "max_value": "inf",
      "name": "",
      "op_id": 2,
      "outputs": [
            {
               "_type_key": "icraft::xir::Value",
               "dtype": {
                  "_type_key": "icraft::xir::TensorType",
                  "element_dtype": "@fp(32)",
                  "layout": "@layout(NHWC)",
                  "merged_distrs": [],
                  "shape": [
                        1,
                        416,
                        416,
                        16
                  ]
               },
               "mtype": "@hostm",
               "name": "",
               "tags": {},
               "v_id": 3
            }
      ],
      "tags": {},
      "threshold": 0.0
   }
]
max_pool2d.network: {
   "_type_key": "icraft::xir::Network",
   "framework_kind": "PYTORCH",
   "framework_version": "v1.9",
   "icraft_version": "v0.0.0",
   "icraft_xir_version": "3.6.2.82",
   "name": "whatever",
   "ops": [
      {
            "_type_key": "icraft::xir::Input",
            "compile_target": "@hostt",
            "inputs": [],
            "name": "",
            "op_id": 0,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           3
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 0
               }
            ],
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::Conv2d",
            "compile_target": "@hostt",
            "cut_scale": "@scales([axis=-1])",
            "dilation_height": 1,
            "dilation_width": 1,
            "groups": 1,
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           3
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 0
               },
               {
                  "_allow_no_data": false,
                  "_type_key": "icraft::xir::Params",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(HWIO)",
                        "merged_distrs": [],
                        "shape": [
                           3,
                           3,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 1
               }
            ],
            "name": "",
            "op_id": 1,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 2
               }
            ],
            "pad_bottom": 1,
            "pad_left": 1,
            "pad_right": 1,
            "pad_top": 1,
            "padding_mode": "ZEROS",
            "stride_height": 1,
            "stride_width": 1,
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::ReLU",
            "alpha": 0.0,
            "compile_target": "@hostt",
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 2
               }
            ],
            "max_value": "inf",
            "name": "",
            "op_id": 2,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 3
               }
            ],
            "tags": {},
            "threshold": 0.0
      },
      {
            "_type_key": "icraft::xir::MaxPool2d",
            "compile_target": "@hostt",
            "dilation_height": 1,
            "dilation_width": 1,
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           416,
                           416,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 3
               }
            ],
            "name": "",
            "op_id": 3,
            "outputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           208,
                           208,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 4
               }
            ],
            "pad_bottom": 1,
            "pad_left": 1,
            "pad_right": 1,
            "pad_top": 1,
            "pool_height": 3,
            "pool_width": 3,
            "stride_height": 2,
            "stride_width": 2,
            "tags": {}
      },
      {
            "_type_key": "icraft::xir::Output",
            "compile_target": "@hostt",
            "inputs": [
               {
                  "_type_key": "icraft::xir::Value",
                  "dtype": {
                        "_type_key": "icraft::xir::TensorType",
                        "element_dtype": "@fp(32)",
                        "layout": "@layout(NHWC)",
                        "merged_distrs": [],
                        "shape": [
                           1,
                           208,
                           208,
                           16
                        ]
                  },
                  "mtype": "@hostm",
                  "name": "",
                  "tags": {},
                  "v_id": 4
               }
            ],
            "name": "",
            "op_id": 4,
            "outputs": [],
            "tags": {}
      }
   ],
   "params_bytes": 0,
   "params_md5": "d41d8cd98f00b204e9800998ecf8427e",
   "tags": {}
}
```

## 模式匹配

为了方便的对网络进行查询和更改， `XIR` 提供了模式匹配机制。模式匹配主要包含两个方面：模式和匹配

## 模式

模式描述了所想要匹配的对象的特点， `XIR` 目前提供了以下几种模式：

- 
`AttrPattern`：匹配算子属性的模式

- 
`ValuePattern`：匹配算子输入的模式

- 
`OpPattern`：匹配算子的模式，其包含了以上两种模式来描述属性和输入

- 
`OrPattern`：表示模式的逻辑或运算

- 
`Wildcard`：表示通配符，匹配任意一个输入

- 
`Anycards`：表示通配符，匹配任意数量输入

同时提供了以下语法糖来构造模式：

```cpp
// 构造了一个模式匹配Conv2d算子，不关心其输入，该算子的stride_width属性为1，groups属性为2
auto conv2d_p = IsOp<Conv2d>().hasAttr("stride_width", 1ll).hasAttr("groups", 2ll);

// 构造一个模式匹配算子，不关心其类型，其输入是上面Conv2d算子的输出
auto relu_p = IsOp(conv2d_p[0]);

// 构造一个模式匹配MaxPool2d算子，其输入是上面ReLU算子的第0个输出
auto max_pool2d_p = IsOp<MaxPool2d>(relu_p[0]);

// 构造一个模式匹配Avgpool算子，其输入是上面ReLU算子的第0个输出
auto avg_pool2d_p = IsOp<AvgPool2d>(relu_p[0]);

// 构造一个模式，匹配上面的MaxPool2d或者Avgpool
auto or_p = max_pool2d_p || avg_pool2d_p;
```

在构造模式时需要注意两点：

- 
每个模式都是以 `OpPattern` 为单位的，即不支持匹配单独构造的 `AttrPattern` 或者 `ValuePattern` 。
自然，也没有提供语法糖支持以上二者的单独构造

- 
每一个模式其实都描述了一张图，所以不能单独看待。
比如不能认为示例中的 `max_pool2d_p` 只是匹配了 `MaxPool2d` ，它匹配的特定图中的 `MaxPool2d`

以上示例中 `conv2d_p` 没有描述其输入，可以匹配任意输入。我们知道 `Conv2d` 的输入有两种情况：带 `Bias` 的三输入和不带 `Bias` 的两输入。
如果你只关心输入的个数，可以使用 `Wildcard` 和 `Anycards` 来实现，
`Wildcard` 表示任意一个输入，而 `Anycards` 表示任意数量的输入，只能作为算子模式的最后一个输入：

```cpp
// 构造了一个模式匹配Conv2d算子，其有两个输入，因此只能匹配到不带Bias的卷积
auto conv2d_p = IsOp<Conv2d>(Wildcard(), Wildcard());

// 构造了一个模式匹配Conv2d算子，其有三个输入，因此只能匹配到带Bias的卷积
auto conv2d_p = IsOp<Conv2d>(Wildcard(), Wildcard(), Wildcard());

// 构造了一个模式匹配Conv2d算子，其有两个以上输入，因此能匹配到以上两种卷积
auto conv2d_p = IsOp<Conv2d>(Wildcard(), Wildcard(), Anycards());

// 以下模式非法
auto conv2d_p = IsOp<Conv2d>(Wildcard(), Anycards(), Wildcard());
```

除了对算子的属性进行设置模式外，还可以为 `Value` 设置一些模式：

```cpp
// 设置Wildcard只被一个算子使用
auto conv2d_p = IsOp<Conv2d>(Wildcard().hasUses(1), Wildcard(), Anycards());
auto relu_p = IsOp(conv2d_p[0]);
// relu的输出且只有一个使用且其数据类型为relu_dtype
auto relu_dtype = TensorType(FloatType::FP32(), { 1, 416, 416, 16 }, Layout::NHWC());
auto relu_use1 = relu_p[0].hasUses(2).hasDtype(relu_dtype);
auto max_pool2d_p = IsOp<MaxPool2d>(relu_use1);
```

## 匹配

`XIR` 中模式的匹配是以网络为单位的，而匹配到了相应的子图免不了要进行一番操作，因此 `Network` 提供了一些方法来对网络进行增删查改：

- 
`addOp`：添加算子到列表尾部

- 
`insertOp`：将算子插入到算子列表迭代器或索引的前面

- 
`insertOpById`：将算子插入到指定 `ID` 的算子前面

- 
`removeOp`：移除符合条件的算子

- 
`removeOpById`：移除指定 `ID` 的算子

- 
`removeOpsById`：一次性移除网络中的若干算子，但保留它们之间的连接关系

- 
`replaceOpById`：将网络中指定 `ID` 的算子替换成新的算子

- 
`replaceOpByIdKeepUses`：同上，但保持老的连接关系，需要新老算子输出数量相同

- 
`replaceOp`：将网络中的算子替换成新的算子

- 
`replaceOpKeepUses`：同上，但保持老的连接关系

- 
`operator[]`：获取算子列表中第 `index` 个算子

- 
`inputOp：` 获取网络的 `Input` 算子(一定是第一个算子)

- 
`getOpById`：获取指定 `ID` 的算子

                