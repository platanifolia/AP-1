#include "interface.h"

#include <iostream>

#include "useradmin.h"
#include "usergengral.h"

using namespace std;

InterFace::InterFace()
{
    adminname_ = "admin";
    adminpassword_ = "123456";
}

InterFace::InterFace(SimpleDataBase *sdb)
{
    adminname_ = "admin";
    adminpassword_ = "123456";
    sdb_ = sdb;
}

void InterFace::FirstView()
{
    while (true)
    {
        cout << string(48, '=') << endl;
        cout << "1.管理员登录  2.用户注册  3.用户登录  4.退出系统" << endl;
        cout << string(48, '=') << endl;
        cout << endl;
        cout << "请输入您的选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            if (AdminVerification())
            {
                UserAdmin admin(sdb_);
                admin.AdminView();
            }
            break;
        }
        case 2:
        {
            string username;
            string password;
            cout << "请输入用户名：";
            cin >> username;
            cout << "请输入密码：";
            cin >> password;
            if (UserRegister(username, password))
            {
                cout << "注册成功！可在用户信息管理出修改个人信息" << endl;
            }
            else
            {
                cout << "注册失败！" << endl;
            }
            break;
        }
        case 3:
        {
            string username;
            string password;
            cout << "请输入您的用户名：";
            cin >> username;
            cout << "请输入您的密码：";
            cin >> password;
            if (UserVerification(username, password))
            {
                string userid = sdb_->FindUserid(username);
                UserGeneral user(sdb_, sdb_->FindUserid(username));
                user.UserGeneralView();
            }
            else
            {
                cerr << "用户名或密码错误！" << endl;
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

bool InterFace::AdminVerification()
{
    cout << "请输入管理员账号：";
    string adminname;
    cin >> adminname;
    cout << "请输入管理员密码：";
    string adminpassword;
    cin >> adminpassword;
    if (adminname == adminname_ && adminpassword == adminpassword_)
    {
        cout << "管理员登录成功！将进入管理员界面" << endl;
        return true;
    }
    else
    {
        cout << "管理员登录失败！将返回主界面" << endl;
        return false;
    }
}

bool InterFace::UserVerification(const std::string &username, const std::string &password)
{
    return sdb_->UserVerification(username, password);
}

bool InterFace::UserRegister(const std::string &username, const std::string &password)
{
    if (sdb_->UsernameExist(username))
    {
        cerr << "用户已存在！" << endl;
        return false;
    }
    else
    {
        sdb_->ParseSql("INSERT INTO user VALUES (" + sdb_->GetNewUserid() + "," + username + "," + password + "," + "#" + "," + "#" + "," + "0" + "," + "active" + ")");
        return true;
    }
}