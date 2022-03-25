#include "interface.h"

#include <iostream>

#include "useradmin.h"

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
        cout << string(67, '=') << endl;
        cout << "1.管理员登录   2.用户注册  3.用户登录  4.退出系统" << endl;
        cout << string(67, '=') << endl;
        cout << endl;
        cout << "请输入您的选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            if(AdminVerification())
            {
                cout << "管理员登录成功！" << endl;
                UserAdmin admin(sdb_);
                admin.AdminView();
            }
            break;
        }
        case 2:
            // UserRegister();
            break;
        case 3:
            // UserLogin();
            break;
        case 4:
            // exit(0);
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