#include "interface.h"

#include <iostream>
#include <regex>

#include "strhandle.h"
#include "useradmin.h"
#include "usergengral.h"

using namespace std;

InterFace::InterFace() {
    adminname_     = "admin";
    adminpassword_ = "123456";
}

InterFace::InterFace(SimpleDataBase* sdb) {
    adminname_     = "admin";
    adminpassword_ = "123456";
    sdb_           = sdb;
}

void InterFace::FirstView() {
    while (true) {
        PrintSymbolEqual(48);
        cout << "1.管理员登录  2.用户注册  3.用户登录  4.退出系统" << endl;
        PrintSymbolEqual(48);
        cout << endl;
        cout << "请输入您的选择：";
        string input;
        getline(cin, input);
        if (input.length() != 1) {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        int choice;
        choice = stoi(input);
        switch (choice) {
        case 1: {
            if (AdminVerification()) {
                UserAdmin admin(sdb_);
                admin.AdminView();
            }
            break;
        }
        case 2: {
            regex  passwordreg("^[a-zA-Z0-9]{6,16}$");
            string username;
            string password;
            cout << "请输入用户名：";
            getline(cin, username);
            // cout << username << endl;
            cout << "请输入密码：";
            getline(cin, password);
            if (!regex_match(password, passwordreg)) {
                cout << "密码格式错误，请重新输入" << endl;
                continue;
            }
            if (!UserRegister(username, password)) {
                cout << "注册失败！" << endl;
            }
            break;
        }
        case 3: {
            string username;
            string password;
            cout << "请输入您的用户名：";
            getline(cin, username);
            cout << "请输入您的密码：";
            getline(cin, password);
            if (UserVerification(username, password)) {
                string userid = sdb_->FindUserid(username);
                if (!sdb_->UserNotBan(userid)) {
                    cout << "您的账户已被封禁，请联系管理员" << endl;
                    break;
                }
                UserGeneral user(sdb_, sdb_->FindUserid(username));
                user.UserGeneralView();
            }
            else {
                cout << "用户名或密码错误！" << endl;
            }
            break;
        }
        case 4:
            return;
        default:
            cout << "似乎输入错误指令?请检查" << endl;
            break;
        }
    }
}

bool InterFace::AdminVerification() {
    cout << "请输入管理员账号：";
    string adminname;
    getline(cin, adminname);
    cout << "请输入管理员密码：";
    string adminpassword;
    getline(cin, adminpassword);
    if (adminname != adminname_ || adminpassword != adminpassword_) {
        cout << "管理员登录失败！将返回主界面" << endl;
        return false;
    }
    else
        return true;
}

bool InterFace::UserVerification(const std::string& username, const std::string& password) {
    return sdb_->UserVerification(username, password);
}

bool InterFace::UserRegister(const std::string& username, const std::string& password) {
    if (sdb_->UsernameExist(username)) {
        cout << "用户已存在！" << endl;
        return false;
    }
    else {
        sdb_->ParseSql("INSERT INTO user VALUES (" + sdb_->GetNewUserid() + "," + username + "," + password + "," + "#" + "," + "#" + "," + "0" + "," + "正常" + ")");
        return true;
    }
}