#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream> // 用于处理字符串流
#include <conio.h>  // 包含_getch函数的头文件
#include <algorithm>
using namespace std;

struct Card {
    string ID;               // 校园卡号码，8位数字
    string name;             // 姓名
    string password;         // 密码，6-12位数字或字母
    double recharge;         // 充值数额
    double remain;           // 余额
    int state;               // 状态，0表示正常，1表示挂失，2表示冻结
    Card* next;              // 下一个节点
};

struct Record {
    string ID;               // 校园卡号码
    string date;             //日期
    string time;             // 时间
    string address;          // 地点
    double money;            // 金额
    int duration;            // 上机用时
    char state;              // 状态，'1'表示上机中，'0'表示未上机
};

// 添加校园卡节点，返回链表首节点指针
Card* addNode(Card* head, Card* node) {
    if (head) {
        Card* p = head;
        while (p->next) { // 找到尾节点
            p = p->next;
        }
        p->next = node; // 将新节点插入到链表尾部
        return head;
    }
    else {
        return node; // 链表为空返回该节点
    }
}

// 查找校园卡节点
Card* findNode(Card* head, const string& id) {
    Card* p = head;
    while (p) {
        if (p->ID == id) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

//检查卡号格式（8位数字）
bool isValidID(const string& id) {
    if (id.length() != 8 || !all_of(id.begin(), id.end(), ::isdigit)) {
        return false;
    }
    return true;
}

//检查密码格式，6-12位数字或字母
bool isValidPassword(const string& password) {
    if (password.length() < 6 || password.length() > 12) {
        return false;
    }
    for (char ch : password) {
        if (!(isalpha(ch) || isdigit(ch))) {
            return false;
        }
    }
    return true;
}


// 清空输入缓冲区
void flushit() {
    int c;
    while ((c = cin.get()) != '\n' && c != EOF);
}

// 输入密码
void inputPassword(string& password) {
    cout << "密码（6-12位字母和数字）: ";
    cin >> password;
}

// 加密密码
void encode(string& password) {
    for (char& ch : password) {
        if (isalpha(ch)) {
            ch = ch + 3;
            if (ch > 'z' && islower(ch)) ch = ch - 'z' + 'a' - 1;
            else if (ch > 'Z' && isupper(ch)) ch = ch - 'Z' + 'A' - 1;
        }
    }
}

// 解密密码
void decode(const string& password, string& decoded) {
    decoded.clear();
    for (char ch : password) {
        if (isalpha(ch)) {
            ch = ch - 3;
            if (ch < 'a' && islower(ch)) ch = ch + 'z' - 'a' + 1;
            else if (ch < 'A' && isupper(ch)) ch = ch + 'Z' - 'A' + 1;
        }
        decoded.push_back(ch);
    }
}

// 等待按下任意键
void keyboard() {
    flushit();
    cin.get();
}

// 清屏
void clearScreen() {
    system("cls");
}

// 保存校园卡信息到文件
void saveFile(const Card* head) {
    ofstream output("cards.txt", ios::out);
    if (output) {
        while (head) {
            output << head->ID << " " << head->name << " " << head->password << " " << head->recharge << " " << head->remain << endl;
            head = head->next;
        }
        output.close();
    }
    else {
        cout << "写文件失败！" << endl;
    }
}

// 从文件中加载校园卡信息
Card* loadFile() {
    ifstream input("cards.txt", ios::in);
    if (input) {
        Card* head = nullptr;
        Card* tail = nullptr;
        while (input) {
            Card* card = new Card();
            input >> card->ID >> card->name >> card->password >> card->recharge >> card->remain;
            card->next = nullptr;
            if (!head) {
                head = card;
                tail = card;
            }
            else {
                tail->next = card;
                tail = card;
            }
        }
        input.close();
        return head;
    }
    else {
        cout << "读文件失败！" << endl;
        return nullptr;
    }
}

// 日期时间转换成字符串
void convertDateTime(time_t tt, string& buf) {
    struct tm* t;
    t = localtime(&tt);
    char temp[256];
    sprintf(temp, "[%04d-%02d-%02d %02d:%02d:%02d]", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    buf = temp;
}

// 添加记录
void addHistory(const string& id, const string& type, double remain, const string& address) {
    string filename = id + ".txt";
    ofstream file(filename, ios::app);
    if (file) {
        string timestamp;
        convertDateTime(time(nullptr), timestamp);
        file << timestamp << " " << type << " " << remain << " " << address << endl;
        file.close();
    }
    else {
        cout << "读文件失败！" << endl;
    }
}

// 加载历史记录
void readHistory(const string& id, const string& type) {
    int count = 0;
    string filename = id + ".txt";
    ifstream file(filename, ios::in);
    cout << "┌-------------------------------------------------┐" << endl;
    cout << "***记录***" << endl;
    if (file) {
        string line; // 用于存储每行的内容
        while (getline(file, line)) { // 使用getline读取整行
            string timenow, types;
            double money;
            string address;
            // 去除时间字段的方括号
            size_t endPos = line.find("]", 1);
            if (endPos != string::npos) {
                timenow = line.substr(1, endPos - 1); // 提取时间
                line.erase(0, endPos + 1); // 删除方括号及时间部分
            }
            // 使用istringstream来分割剩余的字段
            istringstream iss(line);
            if (iss >> types >> money >> address) {
                if (types == type) {
                    cout << timenow << " " << types << " " << money << " " << address << endl;
                    ++count;
                }
            }
        }
        file.close();
    }
    else {
        cout << "无法打开文件！" << endl;
    }
    if (count == 0) {
        cout << "没有记录！" << endl;
    }
    cout << "└-------------------------------------------------┘" << endl;
}

// 显示校园卡信息
void showCard(const Card* card) {
    cout << "┌-------------------------------------------------┐" << endl;
    cout << "***校园卡信息如下***" << endl;
    cout << "卡号：" << card->ID << endl;
    cout << "姓名；" << card->name << endl;
    cout << "密码：" << card->password << endl;
    cout << "充值金额：" << card->recharge << endl;
    cout << "余额：" << card->remain << endl;
    cout << "└-------------------------------------------------┘" << endl;
}
void showCardTitle() {
    cout << "卡号" << " 姓名" << " 密码" << " 充值金额" << " 余额" << endl;
}

// 显示校园卡信息具体内容
void showCardLine(const Card* card) {
    cout << "卡号" << card->ID << "\n" << "姓名" << card->name << "\n" << "密码" << card->password << "\n" << "充值金额" << card->recharge << "\n" << "余额" << card->remain << endl;
}

// 检测卡号和密码格式
void editCard(Card* card) {
    cout << "***录入校园卡信息***" << endl;
    cout << "卡号(8位数字)：";
    string id;
    cin >> id;
    if (!isValidID(id)) {
        cout << "无效的卡号格式！" << endl;
        return;
    }
    card->ID = id;

    cout << "姓名：";
    string name;
    cin >> name;
    card->name = name;

    inputPassword(card->password);
    if (!isValidPassword(card->password)) {
        cout << "无效的密码格式！" << endl;
        return;
    }
    encode(card->password);
}

// 显示校园卡清单选项
void showCardList(Card* head) {
    if (!head) {
        cout << "暂无校园卡信息。" << endl; // 如果链表为空，提示用户
        return;
    }

    cout << "卡号\t\t姓名\t余额\t状态" << endl;
    Card* current = head;
    while (current) {
        cout << current->ID << "\t" << current->name << "\t" << current->remain << "\t";
        if (current->state == 0)
            cout << "正常";
        else if (current->state == 1)
            cout << "挂失";
        else if (current->state == 2)
            cout << "冻结";
        cout << endl;
        current = current->next;

    }
    cout << "校园卡清单显示完成。" << endl;
}
// 注册校园卡选项
void registerCard(Card** head) {
    Card* card = new Card();
    clearScreen();
    cout << "***注册***" << endl;
    editCard(card);
    if (findNode(*head, card->ID)) {
        delete card;
        cout << "注册失败" << endl;
    }
    else {
        *head = addNode(*head, card);
        saveFile(*head); // 同步文件信息
        cout << "注册成功！" << endl;
    }
    keyboard();
}

// 挂失选项
void cancelCard(Card** head) {
    string id;
    clearScreen();
    cout << "***挂失***" << endl;
    cout << "校园卡:";
    cin >> id;
    cout << "└------------------------┘" << endl;
    Card* aim = findNode(*head, id);
    if (aim) {
        if (aim->state != 1 && aim->remain >= 0) { // 检查是否已经挂失
            aim->state = 1; // 设置状态为挂失
            saveFile(*head); // 同步文件信息
            cout << "校园卡挂失成功！" << endl;
        }
        else {
            cout << "余额不足，无法挂失！" << endl;
        }
    }
    else {
        cout << "未找到该校园卡！" << endl;
    }
    keyboard();
}

// 管理员查询选项
void findCard(Card** head) {
    string id;
    clearScreen();
    cout << "***查询***" << endl;
    cout << "校园卡号:";
    cin >> id;
    Card* aim = findNode(*head, id);
    if (aim) {

        showCardLine(aim);
    }
    else {
        cout << "未找到该校园卡！" << endl;
    }
    keyboard();
}

// 重置密码选项
void resetPassword(Card** head, Card* card) {
    clearScreen();
    string id;
    cout << "***重置密码***" << endl;
    cout << "校园卡:";
    cin >> id;
    Card* aim = findNode(*head, id);
    if (aim != nullptr) {
        const string initialPassword = "123456";

        aim->password = initialPassword;
        aim->state = 0; // 将状态重置为正常
        saveFile(*head); // 同步文件信息
        cout << "密码已重置为初始密码！" << endl;
    }
    else {
        cout << "未找到该校园卡！" << endl;
    }
    keyboard();
}

string inputPassword0();
// 管理员登录菜单
int loginAdmin() {
    string id, password;
    cout << "╔----------------------------╗" << endl;
    cout << " ***欢迎进入管理员登录***" << endl;
    cout << "账号 :";
    cin >> id;
    // 输入密码时显示为 *
    password = inputPassword0();
    cout << "╚----------------------------╝" << endl;
    if (id == "zjh" && password == "zjh") {
        return 1;
    }
    else {
        cout << "登录失败，户名或密码错误！" << endl;
    }
    return 0;
}
//统计当天收入
void calculateincome(Card* head) {
    time_t now = time(nullptr);
    struct tm* now_tm = localtime(&now);
    string today = to_string(now_tm->tm_year + 1900) + "-" + to_string(now_tm->tm_mon + 1) + "-" + to_string(now_tm->tm_mday);

    double income = 0.0;
    for (Card* card = head; card != nullptr; card = card->next) {
        string filename = card->ID + ".txt";
        ifstream file(filename, ios::in);
        if (file) {
            string line;
            while (getline(file, line)) {
                size_t endPos = line.find("]", 1);
                if (endPos != string::npos) {
                    string date = line.substr(1, endPos - 1);
                    if (date.find(today) == 0) {
                        istringstream iss(line.substr(endPos + 1));
                        string type;
                        double money;
                        string address;
                        if (iss >> type >> money >> address) {
                            if (type == "充值") {
                                income += money;
                            }
                        }
                    }
                }
            }
            file.close();
        }
    }
    cout << "当天总收入：" << income << endl;
    keyboard();
}
// 校园卡管理菜单
void depositCard(Card** head, Card* card);
void manageMenu(Card** head, Card* card) {
    if (loginAdmin()) { // 管理员登录验证
        int option;
        while (true) {
            clearScreen();
            cout << "***校园卡管理***" << endl;
            cout << "[1]校园卡清单" << endl;
            cout << "[2]挂失" << endl;
            cout << "[3]查询" << endl;
            cout << "[4]充值" << endl;
            cout << "[5]重置密码" << endl;
            cout << "[6]统计当天收入" << endl;
            cout << "[0]退出" << endl;
            cout << "请选择：";
            cin >> option;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区

            switch (option) {
            case 1:
                showCardList(*head); // 调用显示清单函数
                keyboard(); // 等待按键继续
                break;
            case 2:
                cancelCard(head);
                break;
            case 3:
                findCard(head);
                break;
            case 4:
                depositCard(head, card);
                break;
            case 5:
                resetPassword(head, card);
                break;
            case 6:
                calculateincome(*head);
                break;
            case 0:
                return;
            default:
                cout << "无效输入，请重新选择。" << endl;
                keyboard();
            }
        }
    }
}

// 登录验证
Card* checkLogin(Card* head, const string& id, const string& password) {
    Card* aim = findNode(head, id);
    if (aim) {
        if (aim->password == password) {
            return aim;
        }
    }
    return nullptr;
}

// 管理员充值菜单
void depositCard(Card** head, Card* card) {
    double remain = 0.0;
    clearScreen();
    cout << "***充值***" << endl;
    cout << "请选择需要充值的\n";
    Card* currentCard = *head;
    while (currentCard != nullptr) {
        cout << currentCard->ID << endl;
        currentCard = currentCard->next;
    }
    string selectedID;
    cout << "请输入卡号:";
    cin >> selectedID;
    currentCard = *head;
    while (currentCard != nullptr) {
        if (selectedID == currentCard->ID) {
            cout << "您选择的卡号为: " << currentCard->ID << endl;
            break;
        }
        currentCard = currentCard->next;
    }
    if (currentCard == nullptr) {
        cout << "未找到该卡号，请重试！" << endl;
        keyboard();
        return;
    }
    cout << "请输入充值金额：";
    while (true) {
        cin >> remain;
        if (remain > 0) break;
        cout << "输入不合法！请重新输入。" << endl;
        cout << "输入充值金额：";
    }
    remain = static_cast<int>(remain * 100) / 100.0; // 将充值金额精确到小数点后两位
    currentCard->recharge += remain;
    currentCard->remain += remain; // 将增加的remain累积到自己的校园卡中
    saveFile(*head); // 同步文件信息
    addHistory(currentCard->ID, "充值", remain, "cards.txt"); // 将新的记录添加到文件中
    cout << "充值成功，请到查询操作中查看余额变化！" << endl;
    cout << "是否查看账户变化？（1 是 0 否）:";
    int opt;
    cin >> opt;
    if (opt == 1) {
        cout << "业务类型 : 充值" << endl;
        cout << "充值金额 : " << remain << endl;
        cout << "本人校园卡 : " << currentCard->ID << endl;
        cout << "校园卡余额 : " << currentCard->remain << endl;
    }
    keyboard();
}
// 用户上机菜单
void expenseCard(Card* head, Card* card) {
    int hour = 0;
    double money = 0;
    string address;
    clearScreen(); // 清理屏幕
    cout << "#上机#" << endl;
    cout << "上机费：2元/小时" << endl;
    cout << "输入上机耗时：";
    cin >> hour; // 输入上机金额
    cout << "输入上机地点：";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略之前留在输入流中的换行符
    std::getline(std::cin, address);
    money = hour * 2;
    if (money <= card->remain) { // 设计的校园卡是不能透支使用的，判断充值是否够
        card->remain -= money; // 扣除自己校园卡减少的金钱
        saveFile(head); // 同步文件信息
        addHistory(card->ID, "上机", money, address); // 将新的记录添加到文件中
        cout << "操作成功！" << endl;
        cout << "是否查看账户变化？（1 是 0 否）:";
        int opt;
        cin >> opt;
        if (opt == 1) {
            cout << "业务类型 : 上机" << endl;
            cout << "上机金额 : " << money << endl;
            cout << "本人校园卡 : " << card->ID << endl;
            cout << "校园卡余额 : " << card->remain << endl;
            cout << "回单打印成功，请查收！" << endl;
        }
    }
    else { // 金钱不够的话，显示提示信息
        cout << "校园卡余额不足，上机失败！" << endl;
    }
    keyboard();
}
// 学生查询菜单
void searchCard(Card* card) {
    while (true) {
        int option;
        clearScreen();
        cout << "***校园卡详情***" << endl;
        cout << "卡号：" << card->ID << endl;
        cout << "姓名：" << card->name << endl;
        cout << "充值金额：" << card->recharge << endl;
        cout << "余额：" << card->remain << endl;
        cout << "查询" << endl;
        cout << "[1]充值记录" << endl;
        cout << "[2]上机记录" << endl;
        cout << "[0]返回" << endl;
        cin >> option; // 输入选择
        switch (option) {
        case 1:
            readHistory(card->ID, "充值");
            break;
        case 2:
            readHistory(card->ID, "上机");
            break;
        case 0:
            return;
        }
        keyboard();
    }
}

//用户修改密码菜单
void changePassword(Card* head, Card* card) {
    std::string newPassword;
    clearScreen(); // 假设这个函数已经定义好，用于清屏
    std::cout << "***修改密码***\n";
    std::cout << "重置密码\n";

    std::cout << "输入的密码为: " << std::endl; // 调试语句
    cin >> newPassword;

    card->password = newPassword; // 假设Card结构体中password是string类型
    saveFile(head); // 同步文件信息，假设这个函数已经定义好
    std::cout << "密码已更新为: " << newPassword << std::endl; // 调试语句
    std::cout << "密码修改成功！" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略之前留在输入流中的所有字符
    std::cin.get(); // 等待用户按下任意键继续
}
// 用户菜单
void userMenu(Card* head, Card* card) {
    while (true) {
        int option;
        clearScreen();
        cout << "***学生功能***" << endl;
        cout << "[1]上机" << endl;
        cout << "[2]查询" << endl;
        cout << "[3]修改密码" << endl;
        cout << "[0]退出" << endl;
        cin >> option; // 输入选项
        switch (option) {
        case 1:
            expenseCard(head, card);
            break;
        case 2:
            searchCard(card);
            break;
        case 3:
            changePassword(head, card);
            break;
        case 0:
            return;
        }
    }
}
// 用于安全输入密码，显示为 *
string inputPassword0() {
    string password;
    char ch;
    cout << "密码 : ";
    while ((ch = _getch())) { // 使用 _getch() 获取单个字符输入（需要 <conio.h>）
        if (ch == '\r') {     // 检测 Enter 键
            cout << endl;
            break;
        }
        else if (ch == '\b') { // 检测 Backspace 键
            if (!password.empty()) {
                cout << "\b \b"; // 删除一个字符
                password.pop_back();
            }
        }
        else {
            cout << '*'; // 显示星号
            password += ch;
        }
    }
    return password;
}

// 学生登录
void loginCard(Card** head) {
    string id, password;
    Card* card = nullptr;
    int count = 3;
    while (true) { // 校园卡登录验证，输错三次以上显示锁卡
        clearScreen();
        cout << "***学生登录***" << endl;
        cout << "卡号 : ";
        cin >> id;

        // 输入密码时显示为 *
        password = inputPassword0();

        card = checkLogin(*head, id, password); // 验证校园卡和密码是否正确
        if (card) { // 如果校园卡名和密码正确则转到用户菜单界面
            if (card->state == 1) {
                cout << "该校园卡已挂失！" << endl;
                keyboard();
                return;
            }
            if (card->state == 2) {
                cout << "该校园卡已被冻结！" << endl;
                keyboard();
                return;
            }
            userMenu(*head, card);
            break;
        }
        else { // 用户名和密码不正确
            --count;
            if (count > 0) {
                cout << "登录失败，姓名或密码错误或不存在！  按0请重试" << endl;
                keyboard();
            }
            else {
                cout << "连错三次，该卡已被锁定！" << endl;
                Card* temp = findNode(*head, id);
                if (temp) {
                    temp->state = 2; // 设置状态为冻结
                    saveFile(*head); // 同步文件信息
                }
                keyboard();
                break;
            }
        }
    }
}

// 系统主菜单
void process(Card** head, Card** card) {
    while (true) {
        int option;
        clearScreen();
        cout << "欢迎使用校园卡管理系统" << endl;
        cout << "Welcome to Campus Card Management System\n" << endl;
        cout << "[1]学生登录" << endl;
        cout << "[2]学生注册" << endl;
        cout << "[3]管理员登录" << endl;
        cout << "[0]退出系统" << endl;
        cout << "请选择：";
        cin >> option; // 输入选择
        switch (option) {
        case 1:
            loginCard(head);
            break;
        case 2:
            registerCard(head);
            break;
        case 3:
            manageMenu(head, *head); // 注意这里的参数应该是头节点
            break;
        case 0:
            clearScreen();
            cout << "谢谢您的使用" << endl;
            cout << "请保管好您的校园卡！" << endl;
            return;
        }
    }
}
int main() {
    system("***校园卡消费记录查询系统***");
    Card* head = loadFile(); // 从文件中加载数据,返回头节点指针
    process(&head, &head); // 进入菜单操作
    while (head) { // 释放内存
        Card* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
