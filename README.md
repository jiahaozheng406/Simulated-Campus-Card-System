### Simulated-Campus-Card-System

# C++ 校园卡管理系统

**项目介绍**
这是一个纯 C++ 编写的控制台程序，模拟了校园卡系统的完整流程。它不依赖数据库，而是通过**链表**在内存中高效管理数据 ，并利用**文件流**将账户信息和消费记录实时保存到本地 TXT 文件中，确保数据不丢失 。

**功能概览**
在**学生端**，系统注重安全与便捷。登录时若连续 3 次输错密码会自动冻结账户 ，输入密码时屏幕仅显示*以保护隐私 。上机消费按 2元/小时 自动计费，余额不足时会智能拦截 ，并支持随时查询充值与消费流水 。

在**管理员端** (默认账号 `zjh`/`zjh`)，您可以查看所有持卡人状态，支持一键挂失或重置密码 。系统还内置了财务统计功能，能自动遍历日志文件，快速核算当天的充值总收入 。

**运行说明**
项目包含 `main.cpp` 主程序及自动生成的 `cards.txt` 数据库。由于使用了 Windows 控制台特性，请在 Windows 环境下编译运行，并建议添加 `_CRT_SECURE_NO_WARNINGS` 宏以避免时间函数的报错。

---

### English Version

# C++ Campus Card System Lite

**Overview**
This is a pure C++ console application that simulates a complete campus card system. Instead of using a database, it efficiently manages data in memory using **Linked Lists** and persists all account details and transaction logs to local TXT files in real-time .

**Features**
For **Students**, the system prioritizes security. Accounts are automatically frozen after 3 failed login attempts , and password input is masked with * . Expenses are calculated at a rate of 2.0/hour, with automatic blocking if funds are insufficient . Users can also view their full recharge and expense history .

For **Administrators** (default: `zjh`/`zjh`), the system offers full control to view user statuses, report lost cards, or reset passwords . It also includes a financial analytics feature that parses log files to calculate the total daily recharge revenue .

**How to Run**
The project consists of the `main.cpp` source and auto-generated `cards.txt`. It requires a Windows environment due to console-specific features. Please add the `_CRT_SECURE_NO_WARNINGS` macro during compilation to avoid time function warnings.
