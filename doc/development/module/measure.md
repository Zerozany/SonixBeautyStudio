# 测绘测量

## 模块结构图

```mermaid
flowchart TB
    subgraph Measure[测量]
        direction TB
        
        subgraph Basic[基础测量]
            direction TB
            L1[直线测量]
            L2[圆形测量]
            L3[椭圆测量]
            L4[手绘测量]
            L1 ~~~ L2 ~~~ L3 ~~~ L4
        end

        subgraph Adv[进阶测量]
            direction TB
            A1[测量类型]
            A2[算法管理]
            A1 ~~~ A2
        end

        Input[测量输入]
        Output[测量输出]

        Adv ~~~ Input
        Input ~~~ Output
    end
```

## 流程概述

```mermaid
flowchart TD
    Start([开始]) --> Basic[测量]
    
    Basic --> Condition{进阶测量?}
    
    Condition -->|是| Type[进阶测量类型]
    Type --> first[进行基础测量]
    first --> Algo[进阶测量算法]
    Algo --> ExecAdv[执行进阶测量]
    
    Condition -->|否| FinishBasic[进行基础测量]
    
    ExecAdv --> Output([输出结果])
    FinishBasic --> Output
    
    Output --> Stop([结束])

    linkStyle default stroke:#FFFFFF,stroke-width:2px
```

## 目的

- 提供包含基础图形与进阶算法的标准化测量能力，确保进阶测量以基础测量为前提，实现高精度、可扩展的测绘流程与算法管理

## 模块统类

- 进阶测量类

```cpp
#include "MeasureKits.h"

class MeasureKits;
```

- 测量方法

```cpp
@param _measureType 测量类型及选项枚举值
@param args 测量填补参数 基本单位:cm
@return 测量值
template <typename T, typename... Args>
auto measure(T&& _measureType, Args&&... args) noexcept -> double;
```

- 测量类型及选项

1. 头文件

```cpp
#include "MeasureConfig.hpp"
```

<!-- markdownlint-disable MD029 -->
2. 可选类型
<!-- markdownlint-enable MD029 -->

```cpp
namespace Department
{

    enum class Obstetrics
    {
        BiparietalDiameter,
        HeadCircumference,
        AbdominalCircumference,
        CrownRumpLength,
        FemurLength,
    };

    enum class FetalWeight
    {
        Hadlock1,
        Hadlock2,
        Hadlock3,
        Hadlock4
    };

}  // namespace Department
```

- 使用示例

```cpp
#include "MeasureKits.h"
#include <print>

auto main(int argc, char const* argv[]) -> int
{
    MeasureKits measureKits{};
    double      femurLength{measureKits.measure(Department::Obstetrics::FemurLength, 2.84)};
    double      fetalWeight{measureKits.measure(Department::FetalWeight::Hadlock1, 4.95, 0.87)};
    std::println("femurLength:{}", femurLength);
    std::println("fetalWeight:{}", fetalWeight);
    return 0;
}
```

- 算法配置文件

1. 文件格式

```txt
measure.toml
```

<!-- markdownlint-disable MD029 -->
2. 文件内容格式
<!-- markdownlint-enable MD029 -->

```toml
[Obstetrics]
BiparietalDiameter = "9.54 + 1.482 * param_0 + 0.1676 * param_0^2"
HeadCircumference = "8.96 + 0.54 * param_0 + 0.0003 * param_0^3"
AbdominalCircumference = "8.14 + 0.753 * param_0 + 0.0036 * param_0^2"
CrownRumpLength = "5.8434 + 1.4533 * param_0^0.5 + 0.498508 * param_0"
FemurLength = "10.35 + 2.46 * param_0 + 0.17 * param_0^2"

[FetalWeight]
Hadlock1 = "1.304 + 0.05281 * param_0 + 0.1938 * param_1 - 0.004 * param_0 * param_1"
Hadlock2 = "1.335 - 0.0034 * param_0 * param_1 + 0.0316 * param_2 + 0.0457 * param_0 + 0.1623 * param_1"
Hadlock3 = "1.326 - 0.00326 * param_0 * param_1 + 0.0107 * param_2 + 0.0438 * param_0 + 0.158 * param_1"
Hadlock4 = "1.3596 + 0.0064 * param_0 + 0.0424 * param_1 + 0.174 * param_2 + 0.00061 * param_3 * param_1 - 0.00386 * param_1 * param_2"
```
