#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "graphics.h"
#include "menu.h"
#include "stdlib.h"
#include "student-management.h"
#include "cache.h"
#include "input.h"
#include "users.h"

//Hàm tạo giao diện đăng nhập cho người dùng
void LayoutLogin(char username[], char password[])
{
	Yescursortype();//dau nhap nhay
	DrawAppNameTab(0, 2);// chu den, nen green
    //Vẽ khung đăng nhập
	drawRectangle(47, 6, 27, 10, 3);// x=47, y=6, rong=27, dai=10, mau=xanh da troi
	gotoxy(48, 7);//xuong dong
	printf("Username: ");
	gotoxy(48, 10);// xuong dong chua hang de ve khung trang de nhap vao
	printf("Password: ");

	//Vẽ khung input
	drawRectangle(48, 8, 25, 1, 15);
	drawRectangle(48, 11, 25, 1, 15);
	gotoxy(57, 14);
	printf("ENTER to login");

	//Nhập
	gotoxy(48, 8);
	InputUsername(username);
	gotoxy(48, 11);
	InputPassword(password);
	gotoxy(44, 0);
}

//Hàm trả về loại người dùng, -1 nếu username hoặc password không chính xác
int Login(char username[], char password[])
{
	/*
	1:staff
	2: lecturer
	3: student
	*/

	errno_t error;
	FILE* f;
	error = fopen_s(&f, "staff.txt", "r");
	if (error == 0)
	{
		Accounts admin;
		fread(&admin, sizeof(Accounts), 1, f);
		fclose(f);
		//Tài khoản staff luôn ở trạng thái active
		if ((strcmp(username, admin.username) == 0) && (strcmp(password, admin.password) == 0))
		{
			WriteCacheAccount(username, password);
			return 1;
		}
	}
	else
	{
		if (strcmp(username, "ntmphuc") == 0 && strcmp(password, "123456") == 0)
		{
			WriteCacheAccount(username, password);
			Accounts staff;
			strcpy(staff.username, "ntmphuc");
			strcpy(staff.password, "123456");
			staff.active = true;
			strcpy(staff.fullname, "Nguyen Thi Minh Phuc");
			staff.sex = 1;
			staff.type = 1;
			WriteAccount("staff.txt", staff);
			return 1;
		}
		if (strcmp(username, "hatu") == 0 && strcmp(password, "123456") == 0)
		{
			WriteCacheAccount(username, password);
			Accounts staff;
			strcpy(staff.username, "hatu");
			strcpy(staff.password, "123456");
			staff.active = true;
			strcpy(staff.fullname, "Hoang Anh Tu");
			staff.sex = 1;
			staff.type = 1;
			WriteAccount("staff.txt", staff);
			return 1;
		}
		if (strcmp(username, "ltathao") == 0 && strcmp(password, "654321") == 0)
		{
			WriteCacheAccount(username, password);
			Accounts staff;
			strcpy(staff.username, "ltathao");
			strcpy(staff.password, "654321");
			staff.active = true;
			strcpy(staff.fullname, "Le Thi Anh Thao");
			staff.sex = 1;
			staff.type = 1;
			WriteAccount("staff.txt", staff);
			return 1;
		}

	}

	char link[100] = "user/lecturer/";
	strcat(link, username);
	strcat(link, ".txt");
	error = fopen_s(&f, link, "r");
	if (error == 0)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f) != NULL)
		{
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
			{
				if (member.active)
				{
					WriteCacheAccount(username, password);
					return 2;
				}
			}
		}
		fclose(f);
	}

	strcpy(link, "user/student/");
	strcat(link, username);
	strcat(link, ".txt");
	error = fopen_s(&f, link, "r");
	if (error == 0)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f) != NULL)
		{
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
			{
				if (member.active)
				{
					WriteCacheAccount(username, password);
					return 3;
				}
			}
		}
		fclose(f);
	}

	return -1;
}

//Hàm nhận vào loại người dùng để đưa vào menu tương ứng
void CaseLogin(int n)
{
	FILE* f = fopen("cache/menu.txt", "w");	//Viết vào cache trạng thái menu
	FILE* g = fopen("cache/type.txt", "w");	//Viết vào cache loại người dùng
	switch (n)
	{
	case 1:	//staff
		fprintf(g, "%s", "1");
		fclose(g);
		fprintf(f, "%d %s", 9, "111111111");
		fclose(f);
		Menu(9, "111111111");
		break;
	case 2:	//manager
		fprintf(g, "%s", "2");
		fclose(g);
		fprintf(f, "%d %s", 8, "110111111");
		fclose(f);
		Menu(8, "110111111");
		break;
	case 3:	//expert
		fprintf(g, "%s", "3");
		fclose(g);
		fprintf(f, "%d %s", 8, "110111111");
		fclose(f);
		Menu(8, "110111111");
		break;
	default:
		break;
	};
}

//Lặp lại bước nhập <USERNAME> và <PASSWORD> đến khi nào đăng nhập thành công hoặc ấn phím [ESC]
void RepeatInput(char username[], char password[])
{
	int statusLogin;
	//SetBG();
	do
	{
		drawRectangle(36, 9, 48, 3, 15);
		LayoutLogin(username, password);
		statusLogin = Login(username, password);
		if (statusLogin == -1)
		{
			drawRectangle(36, 9, 48, 3, 12);
			gotoxy(51, 10);
			printf("DANG NHAP THAT BAI");
			Sleep(900);
		}
	} while (statusLogin == -1);
	CaseLogin(statusLogin);
}

//Đăng xuất
void LogOut()
{
	WriteCacheAccount("###", "###");
	char username[21], password[21];
	Title(" ");
	drawRectangle(36, 6, 48, 10, 15);
	RepeatInput(username, password);
}