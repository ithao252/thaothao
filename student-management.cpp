// DO AN KI THUAT LAP TRINH 2020.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "graphics.h"
#include "login.h"
#include "student-management.h"
//#include "cache.h"
//#include "function-standard.h"
// go user name va pass o cmd de hien ra file .exe
int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int Status = Login(argv[1], argv[2]);
		if (Status == -1)
		{
			printf("UNAVAILABLE!");//khong the dang nhap
			system("pause");
		}
		else
		{
			SetBG();
			CaseLogin(Status);
		}
	}
	else
		if (argc == 2)
		{
			if (strcmp(argv[1], "logout") == 0)
			{
				SetBG();
				LogOut();
			}
			else
			{
				printf("FAIL!");//nhap lenh sai
				system("pause");
			}
		}
		else
			if (argc == 1)
			{
				char username[21], password[21];	//Tài khoản và mật khẩu tối đa 20 kí tự
				initSystemFolder();
				if (ReadCacheAccount(username, password) == 1)	//Đọc từ cache <USERNAME> và <PASSWORD>
				{
					SetBG();
					CaseLogin(Login(username, password));
				}
				else
				{
					SetBG();
					RepeatInput(username, password);
				}
			}
			else
			{
				printf("FAIL!");//nhap lenh sai
				system("pause");
			}
	textBgColor(15, 0);
	system("cls");
	return 0;
}
