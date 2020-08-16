#include <bits/stdc++.h>//万能库 
#include <windows.h>//Windows库 
using namespace std;

#define START (GetKeyState(VK_MENU)<0) 
#define STOP (GetKeyState(VK_SPACE)<0)
#define END (GetKeyState(VK_ESCAPE)<0)
#define SET (GetKeyState('S')<0&&GetKeyState('E')<0&&GetKeyState('T')<0)

void go(int,int);//光标定位函数 
void color(int);//文本颜色设置函数 

void setpinl();//设置点击频率 

void weikaishi();//状态显示为 未开始点击 
void dianjizhong();//状态显示为 点击中 
void shezhizhong();//状态显示为 设置频率中 
void jieshu();//程序结束  

int pinl=10;//点击频率 
int times=0;//点击次数 

int main()
{
	system("mode con cols=40 lines=10");//设置窗口的列数与行数 
	
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏光标 
	
	SetWindowPos(GetForegroundWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//置顶窗口 
	
	SetConsoleTitle("连点器");//设置窗口标题文本 

	color(15);
	go(1,1);
		cout<<"按下[Alt]开始点击";
	go(1,2);
		cout<<"按下[Space]暂停点击";
	go(1,3);
		cout<<"同时按下[S][E][T]更改频率： "<<pinl<<"次/s   ";
	go(1,4);
		cout<<"按下[Esc]退出程序";
	
	go(1,7);
		cout<<"当前状态：";
	
	while(!START)//未开始点击时 
	{
		Sleep(100);
		weikaishi();
		if(SET)
		{
			setpinl();
			weikaishi();
		}
		if(END)
		{
			jieshu();
			return 0;
		}
			
	}
	dianjizhong();
	while(!END)//程序未结束 
	{
		if(STOP)//暂停 
		{
			weikaishi();	
			while(!START)
			{
				if(SET)
				{
					setpinl();
					weikaishi();
				} 	
				if(END)
				{
					jieshu();
					return 0;
				}
				Sleep(100);
			}
			dianjizhong();
		}
		if(SET)//设置频率 
		{
			setpinl();
			dianjizhong();
		}	
		
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//鼠标左键按下
		Sleep(500/pinl); 
		mouse_event(MOUSEEVENTF_LEFTUP  ,0,0,0,0);//鼠标左键抬起 
		Sleep(500/pinl);
		
		times++;//点击次数+1 
	}
	jieshu();
	

	return 0;
}

void setpinl()
{
	shezhizhong();
	
	CONSOLE_CURSOR_INFO cursor_info={1,1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//显示光标 
	
	go(15,3);
		color(8);
		cout<<"（请输入）";
	
	go(15,3);
		color(15);
	
	
	pinl=0;
	char a;
	a=getchar();//以字符形式输入 
	while(a!='\n')//只要还没输入换行符 
	{
		if(a<='9'&&a>='0')//如果当前字符是数字 
			pinl=pinl*10+(a-'0');//放入pinl的后面一位 
		a=getchar();//继续输入 
	}
	
	CONSOLE_CURSOR_INFO cursor_info2={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info2);//隐藏光标 
	
	if(pinl>500)
	{
		setpinl();
		return;
	}
	go(1,3);
		cout<<"同时按下[S][E][T]更改频率： "<<pinl<<"次/s   ";
}

void weikaishi()
{
	go(6,7);
		color(175);cout<<"未开始点击";
}
void dianjizhong()
{
	go(6,7);
		color(79);cout<<"点击中";
		color(15);cout<<"    ";
}
void shezhizhong()
{
	go(6,7);
		color(159);cout<<"设置频率中";
}

void jieshu()
{
	go(6,7);
		color(240);
		cout<<"程序结束";
		color(15);
		cout<<"  ";

	go(1,8);
		color(15);
		cout<<"共点击"<<times<<"次"<<endl<<"                    ";
	
	color(8);
	system("pause");
}

void go(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
    COORD coord;         //使用头文件自带的坐标结构
    coord.X=x*2;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
    SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}//黑 深蓝 深绿 浅蓝  红  深紫  土黄 浅灰 深灰 亮蓝 亮绿  最淡的蓝 桃红 浅紫  米黄  白
