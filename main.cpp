/*
װ���ֿ����ϵͳ
1.װ�������
2.װ����ɾ��
3.װ���������޸�
4.װ���Ĳ�ѯ{
    4.1װ�������̲�ѯ
    4.2װ����ְҵ��ѯ
    4.3װ�������Ͳ�ѯ
    ģ����ѯ�Ὣ�鵽���������յȼ��Ӹߵ�������
}
װ����Ϣ
1.����
2.ְҵ{
    սʿ/����/�ٻ�ʦ
}
3.����{
    ��/��/��/ì/��/��
    ǹ/��/�ٻ���
}
4.�ȼ�{
    Lv.1~100
}
5.Ʒ��{
    ��-��ͨ
    ��-����
    ��-ϡ��
    ��-ʷʫ
    ��-��˵
    ��-����
}
6.��������{
    ������
    ��������
    �����ٶ�
    ������
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
    char dirs[2][20] = {"house", "information"}; //�ж�ͬ��Ŀ¼���Ƿ�����������ļ��У���û�У��򴴽�
    int index;
    for (index = 0; index < 2; index++)
    {
        if (access(dirs[index], 0))
        {
            mkdir(dirs[index]);
        }
    }
    system("cls"); //����ǰ����
    Inhouse();     //�����¼����/�ֿ�ѡ��

    cout << endl;
    system("pause");
}

void Inhouse()
{
    int i = 1;                            //�����ж��Ƿ����û������Ӧ�Ĳֿ�
    string housenumber, temp_housenumber; //�ֿ��� ��½ʱ���ڶԱȵĲֿ���
    string password, temp_password;       //�ֿ����� ��½ʱ���ڶԱȵ�����
    string housename;
    fstream fs;                                                                   //������д�ļ�������
    cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
    cout << "\n\t---------- �����������Ĳֿ��� -----------" << endl;
    cout << "\t\t   - ����add�����ֿ� -"<< endl;
    cout << "\t\t     - ����off�˳� -\n"
         << endl;
    fs.open("information/register.txt", ios::in | ios::app);
    cout << "\t\t�ֿ�����"
         << "\t"
         << "�ֿ���\n"
         << endl;
    while (fs >> housename) //��ӡ���ֿ��б�
    {
        fs >> temp_housenumber;
        fs >> password;
        cout << "\t\t" << housename << "\t " << temp_housenumber << endl;
    }
    cout << "\n\t\t     >>>  ";
    cin >> housenumber;       //�û�����ֿ���
    if (housenumber == "add") //����û������½��ֿ� ����ת�½��ֿ⺯��
    {
        fs.close(); //�ر��Ѵ򿪵��ļ�
        Addhouse();
    }
    else if (housenumber == "off") //����û������˳� ����ֹ����
    {
        fs.close(); //�ر��Ѵ򿪵��ļ�
        //return;
    }
    else
    {
        fs.clear();  //����ļ���ָ��ָ��ĩβ�ı�־
        fs.seekg(0); //ʹ�ļ���ָ��ָ���ļ���ͷ
        while (fs >> housename)
        {
            fs >> temp_housenumber;
            fs >> temp_password;
            if (housenumber == temp_housenumber) //���û�����ı�������б�Ž�����һ�ȶ�
            {
                i = 0; //����i=0����ʾ�û���������ȷ�Ĳֿ���
                break;
            }
        }
        fs.close(); //�ر��ļ�
        if (i)
        {
            system("cls");
            cout << "\t\t>>>������Ĳֿ�������<<<" << endl;
            Inhouse(); //��������ֿ���
        }
        system("cls");                                                                //������һ��ҳ��ǰ����
        cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
        cout << "\n\t-----------������װ���ֿ������-----------" << endl;
        cout << "\n\t\t     >>>  ";
        cin >> password;
        if (password == temp_password) //�ж��û�����������Ƿ���ȷ
        {
            system("cls");  //������һҳ��֮ǰ����
            House(housenumber, housename);
        }
        else
        {
            system("cls");
            cout << "\t\t>>>������Ĳֿ���������<<<" << endl;
            Inhouse(); //��������ֿ�����
        }
    }
}

void Addhouse()
{
    system("cls");
    time_t now; //��ȡ��ǰʱ��
    time(&now);
    int housenumber = now % 100000;                                               //��ȡһ����һ�޶��Ĳֿ���
    cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
    cout << "\n\t-----------�������½��ֿ������-----------" << endl;
    cout << "\n\t\t>>> ";
    string housename, password; //����ֿ����ƺ�����
    cin >> housename;           //��������
    system("cls");
    cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
    cout << "\n\t-----------�������½��ֿ������-----------" << endl;
    cout << "\n\t\t>>> ";
    cin >> password; //��������
    ofstream fs;
    fs.open("information/register.txt", ios::app);
    fs << housename << " " << housenumber << " " << password << endl;
    fs.close(); //�ر��ļ�
    system("cls");
    cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
    cout << "\n\t-------------�µĲֿⴴ���ɹ�-------------" << endl;
    cout << "\n\t\t�ֿ�����:  " << housename << endl;
    cout << "\t\t�ֿ���:  " << housenumber << endl;
    cout << "\t\t�ֿ�����:  " << password << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls"); //������һ��ǰ����
    Inhouse();
}

void House(string housenumber, string housename)
{
    int num;   //���������
    string temp_housenumber = housenumber;
    string temp = "house/"; //Ϊ��һ�����û�����Ķ�Ӧ�ֿ������ַ���
    temp += housenumber;
    housenumber = temp + ".txt";
    fstream fs;
    fs.open(housenumber, ios::out);                                               //����Ӧ���ļ��� ���ļ��в����� �򴴽�
    cout << "=================��ӭʹ��װ���ֿ����ϵͳ=================" << endl; //����
    cout << "\n\t-------------   " << housename << "   -------------" << endl;
    cout << "\t\t+\t\t       +" << endl;
    cout << "\t\t|" << "     <1> ��������     |" << endl;
    cout << "\t\t|" << "     <2> ɾ������     |" << endl;
    cout << "\t\t|" << "     <3> �޸�����     |" << endl;
    cout << "\t\t|" << "     <4> ��������     |" << endl;
    cout << "\t\t|" << "     <5> �鿴������   |" << endl;
    cout << "\t\t|" << "     <9> ����������   |" << endl;
    cout << "\t\t|" << "     <0> �˳�         |" << endl;
    cout << "\t\t+\t\t       +" << endl;
    cout << "\n\t\t       >>> ";
    cin >> num;   //�û����������
    switch (num)   //�жϲ�����
    {
    case 0:    //�˳�������
        system("cls");
        Inhouse();
        break;
    case 1:   //��������
        
        break;
    case 2:   //ɾ������
        
        break;
    case 3:    //�޸�����
        
        break;
    case 4:   //��������
        
        break;
    case 5:   //�����б�
        
        break;
    case 9:   //����������
        
        break;
    default:  //�������
        system("cls");
        fs.close();  //�ر��Ѵ򿪵��ļ�
        cout << "\t\t    >>>������������<<<" << endl;
        House(temp_housenumber, housename);
        break;
    }
}