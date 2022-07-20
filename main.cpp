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
void Modify(string housenumber);      //修改武器
void Search(string housenumber);      //查找武器
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

    system("cls");  //结束前清屏
    cout << "===感谢使用===" << endl;
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
    else if (housenumber == "off" || housenumber == "OFF") //如果用户输入退出 则终止函数
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
        Delete(housenumber);  //进入删除函数
        House(temp_housenumber, housename);  //回到仓库
        break;
    case 3:    //修改武器
        system("cls");
        Modify(housenumber);  //进去修改函数
        House(temp_housenumber, housename);  //回到仓库
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
    int num = 1;   //用于判断用户输入的正确性
    struct weapon add;  //创建武器信息结构体
    struct weapon temp;  //创建武器信息结构体
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器名称" << "" << endl;
    cout << "\t             - " << "输入off返回" << " -" << endl;
    cout << "\n\t\t    >>> ";
    cin >> add.name;
    if (add.name == "off" || add.name == "OFF")   //判断用户是否想返回
    {
        system("cls");
        return;
    }
    fstream fs;
    fs.open(housenumber, ios::in);   //打开仓库 可读
    while (fs >> temp.name)
    {
        fs >> temp.level;
        fs >> temp.quality;
        fs >> temp.career;
        fs >> temp.type;
        fs >> temp.damage;
        fs >> temp.speed;
        fs >> temp.range;
        fs >> temp.crit;
        if (add.name == temp.name)
        {
            system("cls");
            fs.close();  //关闭文件
            cout << "\t\t >>>已存在此名称的武器<<<" << endl;
            Adddata(housenumber);   //武器名冲突 重新输入
            num = 0;
        }
    }
    if (num)
    {
        num = 1;  //将num重置为1 进行下一步判断
        system("cls");
        while (num)
        {    
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t             " << "请输入武器等级" << "" << endl;
            cout << "\n\t             " << "Lv.0 ~ Lv.100" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.level;
            if (add.level >= 0 && add.level <= 100)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
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
            if (add.quality == 1 || add.quality == 2 || add.quality == 3 )
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else if (add.quality == 4 || add.quality == 5 || add.quality == 6)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t             " << "请输入武器职业" << "" << endl;
            cout << "\n\t               " << "<1> 战士" << "" << endl;
            cout << "\t               " << "<2> 射手" << "" << endl;
            cout << "\t               " << "<3> 法师" << "" << endl;
            cout << "\t               " << "<4> 召唤师" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.career;
            if (add.career == 1 || add.career == 2 || add.career == 3 || add.career == 4)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t             " << "请输入武器类型" << "" << endl;
            cout << "\n\t           " << "<1> 剑     <2> 刀" << "" << endl;
            cout << "\t           " << "<3> 斧     <4> 矛" << "" << endl;
            cout << "\t           " << "<5> 枪     <6> 弓" << "" << endl;
            cout << "\t           " << "<7> 法杖   <8> 召唤杖" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.type;
            if (add.type == 1 || add.type == 2 || add.type == 3 || add.type == 4)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else if (add.type == 5 || add.type == 6 || add.type == 7 || add.type == 8)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t       " << "请输入武器攻击伤害(0 ~ 999)" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.damage;
            if (add.damage >= 0 && add.damage <= 999)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t        " << "请输入武器攻击速度(每秒)" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.speed;
            if (add.speed > 0)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t         " << "请输入武器攻击距离( m )" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.range;
            if (add.range > 0)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }
        num = 1;  //将num重置为1 进行下一步判断
        while (num)
        {
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "添加武器" << "   -------------" << endl;
            cout << "\n\t       " << "请输入武器暴击率(0.0 ~ 1.0)" << "" << endl;
            cout << "\n\t\t    >>> ";
            cin >> add.crit;
            if (add.crit >= 0 && add.crit <= 1)
            {
                num = 0;
                system("cls");  //进入下一步前清屏
            }
            else
            {
                system("cls");    //输入有误 重新输入
                cout << "\t\t    >>>您的输入有误<<<" << endl;
            }
        }   
        fstream fs;   //文件操作流
        fs.open(housenumber, ios::app);  //打开对应武器库文件
        fs << add.name << " " << add.level << " " << add.quality << " "    //录入武器信息
            << add.career << " " << add.type << " " << add.damage << " " 
            << add.speed << " " << add.range << " " << add.crit << endl;
        system("cls");
        cout << "\t\t      >>>添加成功<<<" << endl;
        fs.close();
    }           
}

void Delete(string housenumber)
{
    int num = 1; //用于判断用户是否输入了正确的武器名
    int count = 0, temp_count =0;  //用于记录所删除武器所在的行数 进而通过行数去删除武器
    struct weapon weaponinformation; //定义武器信息结构体
    string weaponname;  //武器名称
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "删除武器" << "   -------------" << endl;
    cout << "\n\t             " << "请输入武器名称" << "" << endl;
    cout << "\t             - " << "输入off返回" << " -" << endl;
    cout << "\n\t\t    >>> ";
    cin >> weaponname;
    if (weaponname == "off" || weaponname == "OFF")   //判断用户是否想返回
    {
        system("cls");
        return;
    }
    fstream fs;
    fs.open(housenumber, ios::in | ios::out);   //打开仓库 可读可写
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
        count++;  //记入当前武器所在行数
        if (weaponname == weaponinformation.name)
        {
            num = 0;  //代表用户输入了正确的武器名
            system("cls");
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "武器详情" << "   -------------" << endl;
            WeaponInformation(weaponinformation);
            cout << "\n\t\t 是否确认删除(Y/N):";
            char YorN;
            cin >> YorN;
            if (YorN == 'Y' || YorN == 'y')
            {
                /*
                    1.先获取到用户想要删除的武器所在文件的行数
                    2.建立一个用于过度的文件
                    3.将原存放武器信息的文件内的信息输入进用于过度的文件并跳过用户想要删除的行数
                    4.将原文件清空，并将过度文件里的内容放回原文件
                */
                system("cls");
                fs.clear();  //清除文件在末尾的标志
                fs.seekg(0);   //文件输出流指向开头
                fstream temp_fs;
                temp_fs.open("house/temp.txt", ios::trunc | ios::out | ios::in);  //可读可写 每次打开文件都是清空状态
                while (fs >> weaponinformation.name)
                {
                    temp_count++;
                    fs >> weaponinformation.level;
                    fs >> weaponinformation.quality;
                    fs >> weaponinformation.career;
                    fs >> weaponinformation.type;
                    fs >> weaponinformation.damage;
                    fs >> weaponinformation.speed;
                    fs >> weaponinformation.range;
                    fs >> weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                //以新的方式打开文件（清除原文件信息并重新写入）
                fs.open(housenumber, ios::trunc | ios::out); 
                temp_fs.clear();
                temp_fs.seekg(0);
                while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                {
                    temp_fs >> weaponinformation.level;
                    temp_fs >> weaponinformation.quality;
                    temp_fs >> weaponinformation.career;
                    temp_fs >> weaponinformation.type;
                    temp_fs >> weaponinformation.damage;
                    temp_fs >> weaponinformation.speed;
                    temp_fs >> weaponinformation.range;
                    temp_fs >> weaponinformation.crit;
                    fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                    fs << weaponinformation.level << " ";
                    fs << weaponinformation.quality << " ";
                    fs << weaponinformation.career << " ";
                    fs << weaponinformation.type << " ";
                    fs << weaponinformation.damage << " ";
                    fs << weaponinformation.speed << " ";
                    fs << weaponinformation.range << " ";
                    fs << weaponinformation.crit << endl;
                }
                temp_fs.close();
                cout << "\t\t      >>>删除成功<<<" << endl;
                remove("house/temp.txt");  //temp文件用完后删除
            }
            else{
                system("cls");
                cout << "\t\t      >>>取消删除<<<" << endl;
            }
        }
    }
    if (num)
    {
        system("cls");
        fs.close();  //关闭已打开的文件
        cout << "\t\t   >>>未查询到该武器<<<" << endl;
        Delete(housenumber); //重新进入武器删除函数
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

void Modify(string housenumber)
{
    int num = 1;      //用于判断用户是否输入了正确的武器名
    int count = 0, temp_count = 0;    //用于记录用户修改武器的所在行
    struct weapon weaponinformation; //定义武器信息结构体
    struct weapon temp_weaponinformation;  //武器信息暂存中间变量
    string weaponname;  //武器名称
    cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
    cout << "\n\t-------------   " << "修改武器" << "   -------------" << endl;
    cout << "\n\t           - " << "请输入武器名称" << " -" << endl;
    cout << "\t             - " << "输入off返回" << " -" << endl;
    cout << "\n\t\t    >>> ";
    cin >> weaponname;
    if (weaponname == "off" || weaponname == "OFF")   //判断用户是否想返回
    {
        system("cls");
        return;
    }
    fstream fs;
    fs.open(housenumber, ios::in | ios::out);   //打开仓库 可读可写
    while (fs >> weaponinformation.name) //打印出修改武器的武器信息
    {
        count++;
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
            num = 0;   //武器名正确
            int flag;  //用于记入用户输入的信息
            system("cls");
            cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
            cout << "\n\t-------------   " << "武器详情" << "   -------------" << endl;
            WeaponInformation(weaponinformation);
            cout << "\n       <1>武器名称     <2>武器等级     <3>武器品质" << endl;
            cout << "       <4>武器职业     <5>武器类型     <6>攻击伤害" << endl;
            cout << "       <7>攻击速度     <8>攻击距离     <9>暴击几率" << endl;
            cout << "       <o>退出修改" << endl;
            cout << "\n\t\t    >>> ";
            cin >> flag;
            fs.clear();
            fs.seekg(0);
            fstream temp_fs;
            temp_fs.open("house/temp.txt", ios::trunc | ios::out | ios::in);  //可读可写 每次打开文件都是清空状态
            switch (flag)
            {
            case 1:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "武器名称" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.name; 
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 2:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "武器等级" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.level;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 3:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "武器品质" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.quality;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 4:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "武器职业" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.career;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 5:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "武器类型" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.type;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 6:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "攻击伤害" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.damage;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 7:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "攻击速度" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.speed;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 8:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "攻击距离" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.range;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 9:
                system("cls");
                cout << "=================欢迎使用装备仓库管理系统=================" << endl; //界面
                cout << "\n\t-------------   " << "暴击几率" << "   -------------" << endl;
                cout << "\n\t\t    >>> ";
                cin >> weaponinformation.crit;
                while (fs >> temp_weaponinformation.name)
                {
                    temp_count++;
                    fs >> temp_weaponinformation.level;
                    fs >> temp_weaponinformation.quality;
                    fs >> temp_weaponinformation.career;
                    fs >> temp_weaponinformation.type;
                    fs >> temp_weaponinformation.damage;
                    fs >> temp_weaponinformation.speed;
                    fs >> temp_weaponinformation.range;
                    fs >> temp_weaponinformation.crit;
                    if (temp_count != count)    //将所需删除的信息跳过
                    {
                        temp_fs << temp_weaponinformation.name << " ";     //将文件信息存放进中间文件
                        temp_fs << temp_weaponinformation.level << " ";
                        temp_fs << temp_weaponinformation.quality << " ";
                        temp_fs << temp_weaponinformation.career << " ";
                        temp_fs << temp_weaponinformation.type << " ";
                        temp_fs << temp_weaponinformation.damage << " ";
                        temp_fs << temp_weaponinformation.speed << " ";
                        temp_fs << temp_weaponinformation.range << " ";
                        temp_fs << temp_weaponinformation.crit << endl;
                    }
                    else
                    {
                        temp_fs << weaponinformation.name << " ";     //写入修改后的所在行武器信息
                        temp_fs << weaponinformation.level << " ";
                        temp_fs << weaponinformation.quality << " ";
                        temp_fs << weaponinformation.career << " ";
                        temp_fs << weaponinformation.type << " ";
                        temp_fs << weaponinformation.damage << " ";
                        temp_fs << weaponinformation.speed << " ";
                        temp_fs << weaponinformation.range << " ";
                        temp_fs << weaponinformation.crit << endl;
                    }
                }
                fs.close();  //关闭已打开的文件
                    //以新的方式打开文件（清除原文件信息并重新写入）
                    fs.open(housenumber, ios::trunc | ios::out); 
                    temp_fs.clear();
                    temp_fs.seekg(0);
                    while (temp_fs >> weaponinformation.name) //打印出删除武器的武器信息
                    {
                        temp_fs >> weaponinformation.level;
                        temp_fs >> weaponinformation.quality;
                        temp_fs >> weaponinformation.career;
                        temp_fs >> weaponinformation.type;
                        temp_fs >> weaponinformation.damage;
                        temp_fs >> weaponinformation.speed;
                        temp_fs >> weaponinformation.range;
                        temp_fs >> weaponinformation.crit;
                        fs << weaponinformation.name << " ";     //将文件信息存放进中间文件
                        fs << weaponinformation.level << " ";
                        fs << weaponinformation.quality << " ";
                        fs << weaponinformation.career << " ";
                        fs << weaponinformation.type << " ";
                        fs << weaponinformation.damage << " ";
                        fs << weaponinformation.speed << " ";
                        fs << weaponinformation.range << " ";
                        fs << weaponinformation.crit << endl;
                    }
                    temp_fs.close();
                    system("cls");
                    cout << "\t\t      >>>修改成功<<<" << endl;
                    remove("house/temp.txt");  //temp文件用完后删除
                break;
            case 0:
                system("cls");  //清屏返回
                break;
            default:
                system("cls");
                fs.close();
                cout << "\t\t    >>>您的输入有误<<<" << endl;  //提示输入错误
                Modify(housenumber);                      //重新输入
                break;
            }
        }
    }
    if (num)
    {
        system("cls");
        fs.close();  //关闭已打开的文件
        cout << "\t\t   >>>未查询到该武器<<<" << endl;
        Modify(housenumber); //重新进入武器修改函数
    }   
}

void Search(string housenumber)
{
    
}
