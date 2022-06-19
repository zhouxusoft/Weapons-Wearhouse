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
1.名称  string
2.职业{
    1.战士/2.射手/3.法师/4.召唤师  int
}
3.类型{
    1.剑/2.刀/3.斧/4.矛    int
    5.枪/6.弓/7.法杖/8.召唤杖
}
4.等级{
    Lv.1~100   int
}
5.品质{
    1.白-普通   int
    2.绿-精良
    3.蓝-稀有
    4.紫-史诗
    5.橙-传说
    6.红-绝世
}
6.各类属性{
    攻击力   int
    攻击距离  int
    攻击速度   int
    暴击率    int
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
    string name;   //武器名字
    int level;     //武器等级
    int quality;   //武器品质
    int career;     //武器职业
    int type;       //武器类型
    int damage;     //攻击伤害
    float speed;      //攻击速度
    float range;      //攻击距离
    float crit;       //暴击率
};

void Inhouse();   //载入仓库
void Addhouse();        //添加武器库
void House(string housenumber, string housename);  //武器库
void Adddata(string housenumber);     //添加武器
void Delete(string housenumber);      //删除武器
void Modify();      //修改武器
void Search();      //查找武器
void List();        //武器列表
void Destroy();     //销毁武器库
void WeaponInformation(struct weapon weaponinformation);  //打印武器具体信息

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
    cout << "\t\t仓库名称" << "\t" << "仓库编号\n" << endl;
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
        else
        {
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
    housenumber = temp + ".txt";                                              //打开相应的文件夹 若文件夹不存在 则创建
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t--------------   " << housename << "   --------------" << endl;
    cout << "\t\t +\t\t        +" << endl;
    cout << "\t\t |" << "     <1> 新增武器     |" << endl;
    cout << "\t\t |" << "     <2> 删除武器     |" << endl;
    cout << "\t\t |" << "     <3> 修改武器     |" << endl;
    cout << "\t\t |" << "     <4> 查找武器     |" << endl;
    cout << "\t\t |" << "     <5> 查看武器库   |" << endl;
    cout << "\t\t |" << "     <9> 销毁武器库   |" << endl;
    cout << "\t\t |" << "     <0> 退出         |" << endl;
    cout << "\t\t +\t\t        +" << endl;
    cout << "\n\t\t       >>> ";
    cin >> num;   //用户输入操作数
    switch (num)   //判断操作数
    {
    case 0:    //退出武器库
        system("cls");
        Inhouse();
        break;
    case 1:   //增加武器
        system("cls");
        Adddata(housenumber);  //进入添加函数
        House(temp_housenumber, housename);  //操作完成后回到上一级函数
        break;
    case 2:   //删除武器
        system("cls");
        Delete(housenumber);  //进去删除函数
        House(temp_housenumber, housename);  //回到仓库
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
        cout << "\t\t    >>>您的输入有误<<<" << endl;
        House(temp_housenumber, housename);
        break;
    }
}

void Adddata(string housenumber)
{
    struct weapon add;  //创建武器信息结构体
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器名称" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.name;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器等级" << "" << endl;
    cout << "\n\t             " << "Lv.0 ~ Lv.100" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.level;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器品质" << "" << endl;
    cout << "\n\t              " << "<1> 普通 白" << "" << endl;
    cout << "\t              " << "<2> 精良 绿" << "" << endl;
    cout << "\t              " << "<3> 稀有 蓝" << "" << endl;
    cout << "\t              " << "<4> 史诗 紫" << "" << endl;
    cout << "\t              " << "<5> 传说 橙" << "" << endl;
    cout << "\t              " << "<6> 绝世 红" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.quality;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器职业" << "" << endl;
    cout << "\n\t               " << "<1> 战士" << "" << endl;
    cout << "\t               " << "<2> 射手" << "" << endl;
    cout << "\t               " << "<3> 法师" << "" << endl;
    cout << "\t               " << "<4> 召唤师" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.career;
    system("cls");
     //   1.剑/2.刀/3.斧/4.矛 
    //5.枪/6.弓/7.法杖/8.召唤杖
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器类型" << "" << endl;
    cout << "\n\t           " << "<1> 剑     <2> 刀" << "" << endl;
    cout << "\t           " << "<3> 斧     <4> 矛" << "" << endl;
    cout << "\t           " << "<5> 枪     <6> 弓" << "" << endl;
    cout << "\t           " << "<7> 法杖   <8> 召唤杖" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.type;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t           " << "请输入武器攻击伤害" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.damage;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t        " << "请输入武器攻击速度(每秒)" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.speed;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t         " << "请输入武器攻击距离( m )" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.range;
    system("cls");
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t      " << "请输入武器暴击率(0.00 ~ 1.00)" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.crit;
    fstream fs;   //文件操作流
    fs.open(housenumber, ios::app);  //打开对应武器库文件
    fs << add.name << " " << add.level << " " << add.quality << " "    //录入武器信息
        << add.career << " " << add.type << " " << add.damage << " " 
        << add.speed << " " << add.range << " " << add.crit << endl;
    system("cls");
    cout << "\t\t      >>>添加成功<<<" << endl;
    fs.close();
}

void Delete(string housenumber)
{
    struct weapon weaponinformation; //定义武器信息结构体
    string weaponname;  //武器名称
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "删除武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器名称" << "" << endl;
    cout << "\n\t\t    >>> ";
    cin >> weaponname;
    fstream fs;
    fs.open(housenumber, ios::in);
    while (fs >> weaponinformation.name) //打印出删除武器的武器信息
    {
        fs >> weaponinformation.level;
        fs >> weaponinformation.quality;
        fs >> weaponinformation.career;
        fs >> weaponinformation.type;
        fs >> weaponinformation.damage;
        fs >> weaponinformation.speed;
        fs >> weaponinformation.range;
        fs >> weaponinformation.crit;
        if (weaponname == weaponinformation.name)
        {
            system("cls");
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "武器详情" << "   -------------" << endl;
            WeaponInformation(weaponinformation);
            cout << "\n\t\t 是否确认删除(Y/N):";
            char YN;
            cin >> YN;
            if (YN == 'Y' || YN == 'y')
            {
                system("cls");
                fs.close();  //关闭已打开的文件
                cout << "\t\t      >>>删除成功<<<" << endl;
            }
            else
            {
                system("cls");
                fs.close();  //关闭已打开的文件
                cout << "\t\t      >>>删除取消<<<" << endl;  //提示删除取消

            }
        }
    }
}

void WeaponInformation(struct weapon weaponinformation)
{
    string quality, career, type;
    switch (weaponinformation.quality)
    {
    case 1:
        quality = "普通";
        break;
    case 2:
        quality = "精良";
        break;
    case 3:
        quality = "稀有";
        break;
    case 4:
        quality = "史诗";
        break;
    case 5:
        quality = "传说";
        break;
    case 6:
        quality = "绝世";
        break;
    default:
        quality = "不详";
        break;
    }
    switch (weaponinformation.career)
    {
    case 1:
        career = "战士";
        break;
    case 2:
        career = "射手";
        break;
    case 3:
        career = "法师";
        break;
    case 4:
        career = "召唤师";
        break;
    default:
        career = "不详";
        break;
    }
    switch (weaponinformation.type)
    {
    case 1:
        type = "剑";
        break;
    case 2:
        type = "刀";
        break;
    case 3:
        type = "斧";
        break;
    case 4:
        type = "矛";
        break;
    case 5:
        type = "枪";
        break;
    case 6:
        type = "弓";
        break;
    case 7:
        type = "法杖";
        break;
    case 8:
        type = "召唤杖";
        break;
    default:
        type = "特殊";
        break;
    }
    cout << "\n\t\t|     " << quality << " " << weaponinformation.name << "  \t|" << endl; 
    cout << "\t\t|     Lv." << weaponinformation.level << "\t\t|" << endl;
    cout << "\t\t|     " << career << "\t\t|" << endl;
    cout << "\t\t|     " << type << " \t\t|" << endl;
    cout << "\t\t|     伤害: " << weaponinformation.damage << "\t\t|" << endl;
    cout << "\t\t|     速度: " << weaponinformation.speed << "\t\t|" << endl;
    cout << "\t\t|     距离: " << weaponinformation.range << "\t\t|" << endl;
    cout << "\t\t|     暴击: " << weaponinformation.crit << "\t\t|" << endl;
}
