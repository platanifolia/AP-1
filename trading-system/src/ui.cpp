#include "ui.h"

#include <iostream>

#include "simpledatabase.h"

using namespace std;

InterFace::InterFace()
{
    adminname_ = "admin";
    adminpassword_ = "123456";
    usernow_ = "";
}

void InterFace::FirstView()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "1" << endl;
        cout << string(50, '=') << endl;
        cout << endl;
        cout << "2";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            AdminLogin();
            break;
        case 2:
            UserRegister();
            break;
        case 3:
            UserLogin();
            break;
        case 4:
            exit(0);
        default:
            cout << "3" << endl;
            break;
        }
    }
}

bool InterFace::AdminLogin()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "4";
        string adminname;
        cin >> adminname;
        cout << "5";
        string adminpassword;
        cin >> adminpassword;
        if (adminname == adminname_ && adminpassword == adminpassword_)
        {
            cout << "6" << endl;
            usernow_ = adminname;
            AdminView();
            return true;
        }
        else
        {
            cout << "7" << endl;
            return false;
        }
    }
}

bool InterFace::UserRegister()
{
    // TODO: ����û�ע��
    return false;
}

bool InterFace::UserLogin()
{
    // TODO: ����û���¼
    return false;
}

bool InterFace::AdminView()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "8" << endl;
        cout << string(50, '=') << endl;
        cout << endl;
        cout << "9";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            return true;
        default:
            cout << "10" << endl;
        }
    }
}

bool InterFace::CommomUserView()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "11" << endl;
        cout << string(50, '=') << endl;
        cout << endl;
        cout << "12";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            exit(0);
        default:
            cout << "13" << endl;
        }
    }
}

bool InterFace::BuyerView()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "14" << endl;
        cout << string(50, '=') << endl;
        cout << endl;
        cout << "15";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return true;
        default:
            cout << "16" << endl;
        }
    }
}

bool InterFace::SellerView()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "17" << endl;
        cout << string(50, '=') << endl;
        cout << endl;
        cout << "18";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return true;
        default:
            cout << "19" << endl;
        }
    }
}