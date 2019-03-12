#include<stdio.h>
#include<windows.h>
#include"itmojun.h"

#pragma comment(lib,"itmojun.lib")

int main()
{
	char cmd[301];
	while(1)
	{
		GetPCCmd("konakona",cmd);
		printf("%s\n",cmd);
		if(strstr(cmd,"³Ô·¹"))
		Sleep(3000);
	}

	return 0;
}