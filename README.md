# Simulated-Campus-Card-System

# 💳 C++ 校园卡管理系统 (Campus Card Lite)

![C++](https://img.shields.io/badge/Language-C++-00599C)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6)
![License](https://img.shields.io/badge/License-MIT-green)

## 👋 简介 (Intro)
这是一个由 C++ 编写的**轻量级校园卡模拟系统**。
仅通过**纯代码 (Native C++)** 和**文本文件**，就实现了一套完整的校园卡生态——从注册、充值、消费到后台管理，一应俱全。

## 🛠️ 技术核心 (Tech Specs)
* **纯粹 C++**: 基于 STL 标准库开发。
* [cite_start]**数据结构**: 使用 **单向链表** 在内存中灵活管理用户数据，告别静态数组的限制 [cite: 81-89, 99-111]。
* [cite_start]**持久化**: 所有数据（账户、流水）均实时保存为本地 `.txt` 文件，程序重启数据不丢失 [cite: 185-197, 234-246]。
* **交互**: 针对 Windows 控制台优化，支持清屏与无回显输入。

## ✨ 功能亮点 (Features)

### 🧑‍🎓 学生端：便捷自助
* [cite_start]**安全登录**: 密码错误 3 次自动冻结，保障账户安全 [cite: 716-756]。
* [cite_start]**隐私保护**: 输入密码时显示为 `******`，防止窥屏 [cite: 690-711]。
* [cite_start]**上机消费**: 按 2元/小时 自动计费，余额不足自动拦截 [cite: 586-618]。
* [cite_start]**账单查询**: 随时查看充值与消费的历史流水，明明白白消费 [cite: 248-284]。

### 👨‍💻 管理员端：掌控全局
* [cite_start]**用户管理**: 查看所有持卡人状态，支持一键挂失与密码重置 [cite: 364-386, 404-422]。
* [cite_start]**财务统计**: 自动核算当日充值总额，营收情况一目了然 [cite: 443-475]。
* **权限控制**: 专属管理员账号登录 (默认: `zjh` / `zjh`)。

## 📂 文件概览 (File Structure)

.
├── main.cpp         # 核心代码：逻辑的大脑
├── cards.txt        # 核心数据库：存储所有用户基本信息
├── [卡号].txt       # 个人账单：自动生成的单用户流水日志（datasets中）
└── README.md        # 说明文档





# 💳 Campus Card System Lite

## 👋 Intro

A lightweight, console-based **Campus Card Simulator** built purely in C++.
No heavy databases, no GUI frameworks—just **Native C++** logic and **File I/O**. It simulates the entire lifecycle of a smart card system, handling everything from user registration and transactions to admin management.

It demonstrates the power of **Linked Lists** for memory management and formatted text files for data persistence.

## 🛠️ Tech Specs

* **Pure C++**: Built with the Standard Template Library (STL).
* 
**Data Structure**: Uses **Singly Linked Lists** for dynamic and efficient user management in memory .


* 
**Persistence**: Auto-saves all accounts and transaction logs to local `.txt` files .


* **Console UI**: Optimized for Windows Command Prompt with secure input masking.

## ✨ Features

### 🧑‍🎓 For Students

* 
**Secure Access**: Account freezes automatically after 3 failed login attempts .


* 
**Privacy First**: Passwords are masked as `******` during input .


* **Smart Billing**: Auto-calculates fees (2.0 units/hour) and blocks transactions if funds are insufficient.
* **Transparency**: View detailed history of all recharges and expenses.

### 👨‍💻 For Admins

* 
**User Control**: List all users, freeze lost cards, or reset forgotten passwords instantly .


* 
**Analytics**: One-click calculation of daily recharge revenue .


* **Admin Access**: Dedicated login portal (Default: `zjh` / `zjh`).

## 🚀 How to Run

> **Note**: Requires **Windows** due to `conio.h` and system calls.

**Option 1: Visual Studio (Recommended)**

1. Create a new Console App.
2. Import the source code.
3. Add `_CRT_SECURE_NO_WARNINGS` to your preprocessor definitions.
4. Build & Run.

**Option 2: Command Line**

```bash
g++ main.cpp -o campus.exe
./campus.exe

```

```

```
