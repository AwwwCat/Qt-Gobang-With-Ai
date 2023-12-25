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

## 文件说明  
## Q&A  
