# Simulated-Campus-Card-System

这是一个精简去重、术语更专业的版本。去掉了一些修饰性的“废话”（如“逻辑的大脑”、“告别限制”等），直接采用技术词汇，更加干练。

---

# 💳 C++ 校园卡管理系统 (Campus Card Lite)

## 👋 简介

基于 C++ 开发的**轻量级校园卡模拟器**。
零依赖、无数据库，仅通过**原生代码**与**文件流技术**，实现注册、充值、消费及后台管理的全流程闭环。

## 🛠️ 技术栈

* **原生开发**: 基于 C++ STL 标准库。
* 
**链表结构**: 采用单向链表动态管理内存数据 。


* 
**持久存储**: 账户与流水实时写入 TXT，掉电不丢失 。


* **交互优化**: 适配 Windows 控制台，支持清屏与无回显输入。

## ✨ 核心功能

### 🧑‍🎓 学生模块

* 
**安全风控**: 连续 3 次错密自动冻结账户 。


* 
**隐私掩码**: 密码输入回显为 `******` 。


* 
**自动结算**: 2元/时计费，余额不足自动拦截 。


* 
**流水追溯**: 支持充值与消费记录的双向查询 。



### 👨‍💻 管理模块

* 
**账户运维**: 全局状态监控，支持一键挂失与密码重置 。


* 
**财务审计**: 自动遍历日志，核算当日充值总收 。


* **权限隔离**: 独立管理员入口 (默认: `zjh` / `zjh`)。

## 📂 目录结构

```text
.
├── main.cpp         # 主程序入口
├── cards.txt        # 账户数据库
├── [卡号].txt       # 交易流水日志
└── README.md        # 项目文档

```

## 🚀 快速启动

1. **环境**: Windows (依赖 `conio.h`).
2. **编译**: 需添加宏 `_CRT_SECURE_NO_WARNINGS`.
3. **运行**: 编译后直接运行 `exe` 即可。





Here is the refined English version, matching the concise and technical tone of the Chinese version.

---

# 💳 C++ Campus Card Management System (Campus Card Lite)

## 👋 Introduction

A **lightweight campus card simulator** built with C++.
Zero dependencies and database-free. It utilizes **native code** and **file streams** to implement the complete lifecycle: registration, recharge, expense, and backend management.

## 🛠️ Tech Stack

* **Native Dev**: Built purely with C++ STL.
* 
**Linked List**: Dynamic memory management using singly linked lists .


* 
**Persistence**: Real-time syncing of accounts and logs to TXT files .


* **Interaction**: Optimized for Windows Console with clear-screen and input handling.

## ✨ Core Features

### 🧑‍🎓 Student Module

* 
**Risk Control**: Account auto-freezes after 3 consecutive failed login attempts .


* 
**Input Masking**: Passwords are masked as `******` during input .


* 
**Auto-Billing**: Hourly rate (2.0/hr) with automatic insufficient funds blocking .


* 
**Traceability**: Bidirectional query support for recharge and expense history .



### 👨‍💻 Admin Module

* 
**Operations**: Global status monitoring, one-click "Report Loss", and password resets .


* 
**Auditing**: Automated traversal of logs to calculate daily recharge revenue .


* **Auth Isolation**: Dedicated administrator login portal (Default: `zjh` / `zjh`).

## 📂 File Structure

```text
.
├── main.cpp         # Entry Point
├── cards.txt        # Account Database
├── [ID].txt         # Transaction Logs
└── README.md        # Documentation

```

## 🚀 Quick Start

1. **Env**: Windows (Requires `conio.h`).
2. **Compile**: Add `_CRT_SECURE_NO_WARNINGS` macro.
3. **Run**: Execute the compiled `exe` directly.
