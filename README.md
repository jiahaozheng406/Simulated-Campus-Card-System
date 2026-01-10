##Campus Card Management System
# C++ 校园卡管理系统

**简介**
这是一个用 C++ 写的校园卡模拟程序。
不需要安装数据库，所有数据（账户信息、消费记录）都直接保存在本地的 TXT 文本文件中。程序包含了学生日常使用（充值、消费）和管理员后台管理（挂失、统计）的完整功能。

**核心特点**

* **纯代码实现**：只用了 C++ 标准库，没用复杂的第三方工具。
* 
**链表管理**：在内存中用单向链表存数据，比数组更灵活，方便增删用户 。


* 
**自动保存**：所有操作实时写入文件，程序关闭后数据不会丢 。


* 
**安全输入**：输入密码时屏幕显示星号 `******`，防窥屏 。



**功能列表**

* **学生功能**
* 
**登录保护**：输错 3 次密码自动冻结账号 。


* 
**上机消费**：按 2元/小时 扣费，余额不足会自动拦截 。


* 
**账单查询**：可以查充值记录和消费流水 。




* **管理员功能** (默认账号: `zjh` / 密码: `zjh`)
* 
**用户维护**：查看所有卡状态，支持一键挂失、重置密码 。


* 
**收入统计**：自动计算当天的充值总金额 。





**文件说明**

* `main.cpp`: 主程序代码。
* `cards.txt`: 存所有用户的基本信息。
* `[卡号].txt`: 自动生成的，存每个人的具体流水。

**如何运行**

1. 环境：需要 Windows 系统（因为用了 `conio.h` 做键盘交互）。
2. 编译：代码中使用了时间函数，编译时如果报错，请添加宏定义 `_CRT_SECURE_NO_WARNINGS`。
3. 运行：编译出 exe 后直接打开即可。

---

# C++ Campus Card System 

**Introduction**
A simple C++ console program that simulates a university ID card system.
It requires no database installation; all data (accounts and transaction logs) are saved directly into local TXT files. It covers full functionality for both students (recharge, expense) and administrators (management, statistics).

**Key Features**

* **Native C++**: Built using only the Standard Template Library (STL).
* 
**Linked Lists**: Uses linked lists in memory instead of arrays for flexible user management .


* 
**Auto-Save**: Data is written to files in real-time, ensuring nothing is lost after closing the program .


* 
**Privacy**: Passwords are masked as `******` during input .



**Functionality**

* **For Students**
* 
**Security**: Account freezes automatically after 3 consecutive wrong passwords .


* **Expense**: Charges 2.0/hour. Transactions are blocked if the balance is insufficient .


* 
**History**: View detailed logs for recharges and expenses .




* **For Admins** (Default: `zjh` / `zjh`)
* 
**Management**: View user statuses, report lost cards, or reset passwords .


* 
**Statistics**: One-click calculation of the daily total recharge income .





**Files**

* `main.cpp`: Main source code.
* `cards.txt`: Database for all user accounts.
* `[ID].txt`: Auto-generated logs for individual transaction history.

**How to Run**

1. **System**: Windows is required (due to `conio.h` for console interaction).
2. **Compile**: Add the `_CRT_SECURE_NO_WARNINGS` macro to avoid warnings about time functions.
3. **Run**: Execute the compiled exe file directly.
