/*
装备仓库管理系统
1.装备的添加
2.装备的删除
3.装备的属性修改
4.装备的查询{
    4.1装备的名程查询
    4.2装备的职业查询
    4.3装备的类型查询
    模糊查询会将查到的武器按照等级从高到低排列
}
装备信息
1.名称
2.职业{
    战士/射手/召唤师
}
3.类型{
    剑/刀/斧/矛/锤/尺
    枪/弓/召唤杖
}
4.等级{
    Lv.1~100
}
5.品质{
    白-普通
    绿-精良
    蓝-稀有
    紫-史诗
    橙-传说
    红-绝世
}
6.各类属性{
    攻击力
    攻击距离
    攻击速度
    暴击率
}
*/

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <ctime>
#include <direct.h>
using namespace std;

struct weapon
{
    string name;
    int level;
    int quality;
    int career;
    int type;
    int damage;
    int speed;
    int range;
    int crit;
};

void Inhouse();
void Addhouse();
void House(string housenumber, string housename);
void Adddata();
void Delete();
void Modify();
void Search();
void List();
void Destroy();

int main()
{
    char dirs[2][20] = {"house", "information"}; //判断同级目录下是否存在这两个文件夹，若没有，则创建
    int index;
    for (index = 0; index < 2; index++)
    {
        if (access(dirs[index], 0))
        {
            mkdir(dirs[index]);
        }
    }
    system("cls"); //运行前清屏
    Inhouse();     //载入登录函数/仓库选择

    cout << endl;
    system("pause");
}

void Inhouse()
{
    int i = 1;                            //用于判断是否有用户输入对应的仓库
    string housenumber, temp_housenumber; //仓库编号 登陆时用于对比的仓库编号
    string password, temp_password;       //仓库密码 登陆时用于对比的密码
    string housename;
    fstream fs;                                                                   //创建读写文件流对象
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t---------- 请先输入您的仓库编号 -----------" << endl;
    cout << "\t\t   - 输入add创建仓库 -"<< endl;
    cout << "\t\t     - 输入off退出 -\n"
         << endl;
    fs.open("information/register.txt", ios::in | ios::app);
    cout << "\t\t仓库名称"
         << "\t"
         << "仓库编号\n"
         << endl;
    while (fs >> housename) //打印出仓库列表
    {
        fs >> temp_housenumber;
        fs >> password;
        cout << "\t\t" << housename << "\t " << temp_housenumber << endl;
    }
    cout << "\n\t\t     >>>  ";
    cin >> housenumber;       //用户输入仓库编号
    if (housenumber == "add") //如果用户输入新建仓库 则跳转新建仓库函数
    {
        fs.close(); //关闭已打开的文件
        Addhouse();
    }
    else if (housenumber == "off") //如果用户输入退出 则终止函数
    {
        fs.close(); //关闭已打开的文件
        //return;
    }
    else
    {
        fs.clear();  //清楚文件流指针指向末尾的标志
        fs.seekg(0); //使文件流指针指向文件开头
        while (fs >> housename)
        {
            fs >> temp_housenumber;
            fs >> temp_password;
            if (housenumber == temp_housenumber) //将用户输入的编号与现有编号进行逐一比对
            {
                i = 0; //设置i=0，表示用户输入了正确的仓库编号
                break;
            }
        }
        fs.close(); //关闭文件
        if (i)
        {
            system("cls");
            cout << "\t\t>>>您输入的仓库编号有误<<<" << endl;
            Inhouse(); //重新输入仓库编号
        }
        system("cls");                                                                //进入下一个页面前清屏
        cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
        cout << "\n\t-----------请输入装备仓库的密码-----------" << endl;
        cout << "\n\t\t     >>>  ";
        cin >> password;
        if (password == temp_password) //判断用户输入的密码是否正确
        {
            system("cls");  //进入下一页面之前清屏
            House(housenumber, housename);
        }
        else
        {
            system("cls");
            cout << "\t\t>>>您输入的仓库密码有误<<<" << endl;
            Inhouse(); //重新输入仓库密码
        }
    }
}

void Addhouse()
{
    system("cls");
    time_t now; //获取当前时间
    time(&now);
    int housenumber = now % 100000;                                               //获取一个独一无二的仓库编号
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-----------请输入新建仓库的名称-----------" << endl;
    cout << "\n\t\t>>> ";
    string housename, password; //定义仓库名称和密码
    cin >> housename;           //输入名称
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-----------请输入新建仓库的密码-----------" << endl;
    cout << "\n\t\t>>> ";
    cin >> password; //输入密码
    ofstream fs;
    fs.open("information/register.txt", ios::app);
    fs << housename << " " << housenumber << " " << password << endl;
    fs.close(); //关闭文件
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------新的仓库创建成功-------------" << endl;
    cout << "\n\t\t仓库名称:  " << housename << endl;
    cout << "\t\t仓库编号:  " << housenumber << endl;
    cout << "\t\t仓库密码:  " << password << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls"); //进入下一步前清屏
    Inhouse();
}

void House(string housenumber, string housename)
{
    int num;   //记入操作数
    string temp_housenumber = housenumber;
    string temp = "house/"; //为下一步打开用户输入的对应仓库制作字符串
    temp += housenumber;
    housenumber = temp + ".txt";
    fstream fs;
    fs.open(housenumber, ios::out);                                               //打开相应的文件夹 若文件夹不存在 则创建
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << housename << "   -------------" << endl;
    cout << "\t\t+\t\t       +" << endl;
    cout << "\t\t|" << "     <1> 新增武器     |" << endl;
    cout << "\t\t|" << "     <2> 删除武器     |" << endl;
    cout << "\t\t|" << "     <3> 修改武器     |" << endl;
    cout << "\t\t|" << "     <4> 查找武器     |" << endl;
    cout << "\t\t|" << "     <5> 查看武器库   |" << endl;
    cout << "\t\t|" << "     <9> 销毁武器库   |" << endl;
    cout << "\t\t|" << "     <0> 退出         |" << endl;
    cout << "\t\t+\t\t       +" << endl;
    cout << "\n\t\t       >>> ";
    cin >> num;   //用户输入操作数
    switch (num)   //判断操作数
    {
    case 0:    //退出武器库
        system("cls");
        Inhouse();
        break;
    case 1:   //增加武器
        
        break;
    case 2:   //删除武器
        
        break;
    case 3:    //修改武器
        
        break;
    case 4:   //查找武器
        
        break;
    case 5:   //武器列表
        
        break;
    case 9:   //销毁武器库
        
        break;
    default:  //输入错误
        system("cls");
        fs.close();  //关闭已打开的文件
        cout << "\t\t    >>>您的输入有误<<<" << endl;
        House(temp_housenumber, housename);
        break;
    }
}