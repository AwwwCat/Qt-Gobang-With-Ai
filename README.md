# Qt-Gobang-With-Ai  
基于Qt框架的五子棋，带有 PvC 模式。包含了自己开发的 ai 算法。  
## 目录  
* [环境](https://github.com/AwwwCat/Qt-Gobang-With-Ai#%E7%8E%AF%E5%A2%83)  
* [Ai逻辑](https://github.com/AwwwCat/Qt-Gobang-With-Ai#ai%E9%80%BB%E8%BE%91)  
* [文件说明](https://github.com/AwwwCat/Qt-Gobang-With-Ai#ai%E9%80%BB%E8%BE%91)  
* [Q&A](https://github.com/AwwwCat/Qt-Gobang-With-Ai#qa)  
## 环境  
需要 Qt 环境运行，本项目使用 `Qt 5.14.2` 环境，并使用 `Qt Creator 4.11.1 (Community)` 开发，相关资源可以前往[下载地址](https://download.qt.io/archive/qt/5.14/5.14.2/ "Qt 5.14.2 下载")自行下载环境。  
具体相关环境如下：  
* Qt 5.14.2 (mingw73_64)  
* Qt 5.14.2 (msvc2017_64)
  
下载后导入项目即可。  
## Ai逻辑  
### 周边类型运算
代码将遍历所有的空棋位，按照八个方向分别算出该空棋位各个方向最多5个棋子的类型，分别为无棋，活一，死一，活二，死二，活三，死三，活四，死四。相关定义在 `chess.h` 文件中枚举，具体内容及含意如下——  
```
enum SingleTypes {
    OP, OXP, WXP, OXXP, WXXP, OXXXP, WXXXP, OXXXXP, WXXXXP
};
```
其中  
* P 代表要下的棋子，即判断的空位；  
* O 代表空位；  
* X 代表棋；  
* W 代表和 X 相反的棋。  
### 具体连子类型判断
根据上面的算法得到棋子周边的类型，通过组合得出棋子周边真正的类型。如在一条线上 `OXP` 和 `WXXP` 能组成 `OXPXXW`，为 `死三`；或在一条线上 `OXXP` 和 `OP` 能组成 `OPXXO`，为 `活二`；或两个 `活二` 组成 `双活二` 类型等等......具体枚举如下——
```
enum Categorys {
        Kill, DeadFive, LiveFour, DeadFour, LiveThree, DeadThree, LiveTwo, DeadTwo, LiveOne, DeadOne, TwoLiveTwo, AllCategorys
    };
```
具体含义见下表——
枚举名 | 含义 | 判断类型
:---: | :---: | :---:
Kill | 必杀棋 | OXXXXPO
DeadFive | 死五 | WXXPXXXO WXXPXXXW OXXPXXXW WXXXXPXO WXXXXPXW
LiveFour | 活四 | OXXXPXO OXXPXXO
DeadFour | 死四 | WXXXXP WXXXPXO WXXPXXO WXXXPXW
LiveThree | 活三 | OXXXPO OXXPXO
DeadThree | 死三 | WXXXPO WXXPXO WXPXXO
LiveTwo | 活二 | OXXPO OXPXO
DeadTwo | 死二 | WXXPO WXPXO WXPXW
LiveOne | 活一 | OXPO
DeadOne | 死一 | WXPO
TwoLiveTwo | 双活二 | 两个及以上 LiveTwo 或 DeadThree
AllCategorys | 枚举数 | 创建数组用
### 计算权重
根据对Ai的需求设置权重并使用上面的数据计算，算出该空位的权重并记录在二维数组 `int scoreMap[CELL_NUM+1][CELL_NUM+1]`;。当遍历完所有空位后，数组将记录了所有空位的权重。  
### 选择下棋点
计算 `scoreMap` 中的最大值，然后选出所有最大值的位置并随机挑选一个位置下棋。  
至此Ai运算结束。  
## 文件说明  
## Q&A  
