# Qt-Gobang-With-Ai  
这是一个基于 Qt 框架的五子棋游戏，提供了与 AI 对战的 PvC 模式，并包含了自主开发的 AI 算法。
## 目录  
* [环境](https://github.com/AwwwCat/Qt-Gobang-With-Ai#%E7%8E%AF%E5%A2%83)  
* [Ai逻辑](https://github.com/AwwwCat/Qt-Gobang-With-Ai#ai%E9%80%BB%E8%BE%91)  
* [文件说明](https://github.com/AwwwCat/Qt-Gobang-With-Ai#ai%E9%80%BB%E8%BE%91)  
* [Q&A](https://github.com/AwwwCat/Qt-Gobang-With-Ai#qa)  
## 环境  
运行本项目需要 `Qt 5.14.2` 环境以及 `Visual Studio 2022 (Community)` ，你可以从[这里](https://download.qt.io/archive/qt/5.14/5.14.2/ "Qt 5.14.2 下载")下载所需的环境。  
具体相关环境如下：  
* Qt 5.14.2 (mingw73_64)  
* Qt 5.14.2 (msvc2017_64)
  
下载后导入项目即可。  
## Ai逻辑  
### 周边类型运算
该算法遍历所有的空棋位，并根据八个方向分别计算棋子的类型。相关定义在 `chess.h` 文件中的枚举中。具体内容及含意如下——  
```
enum SingleTypes {
    WP, OXP, WXP, OXXP, WXXP, OXXXP, WXXXP, OXXXXP, WXXXXP, WOOP, WOP, OP, WXOP, OXOP, WXXOP, OXXOP, WXXXOP, OXOXP
};
```
其中  
* P 代表要下的棋子，即判断的空位；  
* O 代表空位；  
* X 代表棋；  
* W 代表和 X 相反的棋。  
### 具体连子类型判断
根据周边类型的计算结果，组合各个方向的棋子类型，得出棋子周边真正的连子类型。比如，OXP 和 WXXP 在一条线上能组成 OXPXXW，代表着 "眠三"；或者 OXXP 和 OP 能组成 OPXXO，代表着 "活二"；或者两个 "活二" 组成 三三 类型等等。
具体枚举如下——
```
enum Categorys {
    MakeKill, AliveFour, LongFive, RushFour, AliveThree, SleepThree, AliveTwo, JumpTwo, MiddleTwo, SideTwo, SleepTwo, AliveOne, SleepOne, ThreeThree, FourThree, FourFour, AllCategorys
};
```
具体含义见下表——
枚举名 | 含义 | 判断类型 
:---: | :---: | :---:
MakeKill | 做杀 | 
AliveFour | 活四 | OXXXXPA
LongFive | 长五 | WXXPXXXO WXXPXXXW OXXPXXXW WXXXXPXO WXXXXPXW
RushFour | 冲四 | WXXXXPA WXXXPXO WXXPXXO WXXXPXW OXXPXXO OXXXPXO
AliveThree | 活三 | OXXXPM OXXPXO
SleepThree | 眠三 | WXXPXO WXPXXO WXXXPM WXXXOPW
AliveTwo | 活二 | OXXPM OXPXO
JumpTwo | 跳二 | OXOXPM
MiddleTwo | 中二 | OXOPXO
SideTwo | 边二 | OXXOPM
SleepTwo | 眠二 | WXPXO WPXXO WXXPO WXXPOOW WXXOPOW
AliveOne | 活一 | OXPM
SleepOne | 眠一 | WXPM
ThreeThree | 三三 | 两个及以上 AliveTwo 或 JumpTwo 或 MiddleTwo 或 SideTwo
FourThree | 四三 | 两个及以上 SleepThree 和 AliveTwo 或 JumpTwo 或 MiddleTwo 或 SideTwo
FourFour | 四四 | 两个及以上 SleepThree
AllCategorys | 枚举数 | 创建数组用

其中    
* P, O, X, W 含义见上文；
* M 代表 OP，WOP，WOOP。 
### 计算权重
根据 AI 对棋局的需求设置权重，并利用上述数据计算出每个空位的权重。当遍历完所有空位后，数组将记录所有空位的权重。
### 选择下棋点
计算 `scoreMap` 中的最大值，然后选出所有最大值的位置，并随机选择一个位置作为下棋点。。  
## 文件说明  
* **Chess.h/.cpp:**  
继承 ChessBoard 类，实现棋局对战和AI算法。  
* **ChessBoard.h/.cpp:**  
继承 Qwidget 类，实现棋盘绘制及缩放。
* **DebugOption.h/.cpp:**  
继承 QDialog 类，实现 Debug 设置窗口。
* **Gobang.h/.cpp:**  
继承 QMainWindows 类，实现游戏全局。
* **ImportDialog.h/.cpp:**  
继承 QDialog 类，实现导入窗口。
* **MainOption.h/.cpp:**  
继承 QDialog 类，实现主设置窗口。
* **MainWidget.h/.cpp:**  
继承 QWidget 类，实现游戏主窗口。
* **NewGame.h/.cpp:**  
继承 QDialog 类，实现新游戏窗口。
* **PlayerOption.h/.cpp:**  
继承 QDialog 类，实现玩家设置窗口。
* **main.cpp:**  
实现 main 函数。
* **其他:**  
Visual Studio 相关文件。
## Q&A  
* **有些功能无法使用怎么办？**  
有些功能正在开发中，请稍候... 咕咕咕
* **AI 是独立开发的吗？会有进一步优化吗？**
是的，这是独立开发的 AI 算法，如有雷同，纯属巧合。  
优化方案已经在考虑中，不过目前的架构可能不易再次改进。  
