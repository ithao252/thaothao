//Cac chuc nang
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "graphics.h"
#include "menu.h"
#include "stdlib.h"
#include "login.h"
#include "string.h"
#include "student-management.h"
#include "cache.h"
#include "input.h"

//Cho biết username có khả dụng cho việc tạo mới hay không?
bool AcceptUser(char username[])
{
	if (strcmp(username, "ntmphuc") == 0|| strcmp(username, "hatu") == 0|| strcmp(username, "ltathao") == 0) 
		return false;	//Nếu tài khoản đăng kí mới trùng tên staff thì trả về false

	bool ACCEPT = true;//co hieu

	//Kiểm tra các tài khoản thuộc nhóm Quản lý
	char link[100] = "user/lecturer/";
	strcat(link, username);
	strcat(link, ".txt");
	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "r");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;	//ACCEPT bằng false chỉ khi tài khoản đã được tạo trước đó và vẫn còn đang trạng thái ACTIVE
	}

	//Kiểm tra các tài khoản thuộc nhóm Chuyên viên
	strcpy(link, "user/student/");
	strcat(link, username);
	strcat(link, ".txt");
	error = fopen_s(&f, link, "r");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;
	}
	return ACCEPT;
}
//============================================================================================//



//Thêm Account Student vao file .txt
void AddAccount(student S)
{
	char LINK[100], link[100], listlink[100];
	if (S.acc.type== 1)
		strcpy(LINK, "user/student/");
	strcpy(link, LINK);
	strcat(link, S.acc.username);
	strcat(link, ".txt");

	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "r");
	if (error != 0)	//Không mở được file để đọc
	{// tao ra file .txt chua danh sach cac username
		strcpy(listlink, LINK);
		strcat(listlink, "ListOfUserName.txt");
		fopen_s(&f, listlink, "w");
		fprintf(f, "%s\n%s\n%d/%d/%d\n%s\n", S.acc.username, S.acc.password,S.DoB, S.ID);
		fclose(f);
	}
	else
		fclose(f);

	S.acc.active = true;

	fopen_s(&f, link, "w");
	fwrite(&S, sizeof(Accounts), 1, f);
	fclose(f);
}
//Thêm Account Lecturer vao file .txt
void AddAccount(lecturer L)
{
	char LINK[100], link[100], listlink[100];
	if (L.acc.type == 2)
		strcpy(LINK, "user/lecturer/");
	strcpy(link, LINK);
	strcat(link, L.acc.username);
	strcat(link, ".txt");

	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "r");
	if (error != 0)	//Không mở được file để đọc
	{// tao ra file .txt chua danh sach cac username
		strcpy(listlink, LINK);
		strcat(listlink, "ListOfUserName.txt");
		fopen_s(&f, listlink, "w");
		fprintf(f, "%s\n", L.acc.username);
		fclose(f);
	}
	else
		fclose(f);

	L.acc.active = true;

	fopen_s(&f, link, "w");
	fwrite(&L, sizeof(Accounts), 1, f);
	fclose(f);
}

//Bảng nhập thông tin Tạo Student moi
void InputUserData()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>CREATE A NEW STUDENT");
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(36, 6, 48, 17, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Username[20]: ");
		gotoxy(38, 9);
		printf("Password[20]: ");
		gotoxy(38, 11);
		printf("Full name[44]: ");
		gotoxy(38, 13);
		printf("DOB: dd/mm/yyyy");
		gotoxy(38, 15);
		printf("ID:   ");
		gotoxy(38, 17);
		printf("Sex: 1->Male ; 2-> Female");
		gotoxy(38, 19);
		printf("Class:   ");
		

		
		//Vẽ các trường nhập
		drawRectangle(38, 8, 44, 1, 15);

		drawRectangle(38, 10, 44, 1, 15);

		drawRectangle(38, 12, 44, 1, 15);

		drawRectangle(38, 14, 44, 1, 15);

		drawRectangle(38, 16, 44, 1, 15);
		gotoxy(40, 14);
		printf("/  /");
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);

		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 22);
		printf("ENTER to Creat account");
		gotoxy(60, 23);
		printf("F12 to Back");
		textBgColor(0, 15);
		//Nhập <USERNAME>
		student S;
		do
		{
			gotoxy(38, 8);
			int status = InputUsername(S.acc.username);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		} while (strlen(S.acc.username) == 0 && !BACK);
		//Nhập Mật khẩu
		if (!BACK)
		{
			do
			{
				gotoxy(38, 10);
				int status = InputPassword(S.acc.password);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(S.acc.password) == 0 && !BACK);
		}
		//Nhập Họ tên
		if (!BACK)
		{
			do
			{
				gotoxy(38, 12);
				int status = InputFullname(S.acc.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(S.acc.fullname) == 0 && !BACK);
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			do {
				gotoxy(38, 14);
				S.DoB.date = Input2Num();
				if (S.DoB.date == -1)
				{
					BACK = true;
				}
			} while (S.DoB.date == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(41, 14);
				S.DoB.month = Input2Num();
				if (S.DoB.month == -1)
				{
					BACK = true;
				}
			} while (S.DoB.month == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(44, 14);
				S.DoB.year = Input4Num();
				if (S.DoB.year == -1)
				{
					BACK = true;
				}
			} while (S.DoB.year == 0 && !BACK);
		}
		//Nhập MSSV
		if (!BACK)
		{
			do
			{
				gotoxy(38, 16);
				int status = InputIndentity(S.ID);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(S.ID) == 0 && !BACK);
		}
	
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 18);
			S.acc.sex = Input1Num();
			if (S.acc.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Class
		if (!BACK)
		{
			gotoxy(38, 20);
			status= InputClass(S.courses.lop);
			if (S.courses.lop == -1)
			{
				BACK = true;
			}
		}
		int n;
		char list[11];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Nếu username khả dụng thì tạo mới tài khoản kèm thông báo tạo thành công
			if (AcceptUser(S.acc.username))
			{
				AddAccount(S);
				drawRectangle(36, 12, 48, 3, 10);
				char Alert[100] = "SUCCESSFUL!";
				strcat(Alert, S.acc.username);
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Nếu username không khả dụng thì thông báo tài khoản đã được sử dụng
			else
			{
				drawRectangle(36, 12, 48, 3, 12);
				gotoxy(37, 13);
				char Alert[100] = "This account ";
				strcat(Alert, S.acc.username);
				strcat(Alert, " has been used");
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(36, 6, 48, 21, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}
//Bảng nhập thông tin Tạo Lecturer moi
void InputUserData1()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>CREATE A NEW LECTURER");
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(36, 6, 48, 17, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Username[20]: ");
		gotoxy(38, 9);
		printf("Password[20]: ");
		gotoxy(38, 11);
		printf("Full name[44]: ");
		gotoxy(38, 13);
		printf("Sex: 1->Male ; 2-> Female");
		gotoxy(38, 15);
		printf("Degree:   ");
		gotoxy(38, 17);
		printf("Course:   ");
		gotoxy(38, 19);
		

		//Vẽ các trường nhập
		drawRectangle(38, 8, 44, 1, 15);

		drawRectangle(38, 10, 44, 1, 15);

		drawRectangle(38, 12, 44, 1, 15);

		drawRectangle(38, 14, 44, 1, 15);

		drawRectangle(38, 16, 44, 1, 15);
		gotoxy(40, 14);
		printf("/  /");
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 22);
		printf("ENTER to Creat account");
		gotoxy(60, 23);
		printf("F12 to Back");
		textBgColor(0, 15);
		//Nhập <USERNAME>
		lecturer L;
		do
		{
			gotoxy(38, 8);
			int status = InputUsername(L.acc.username);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		} while (strlen(L.acc.username) == 0 && !BACK);
		//Nhập Mật khẩu
		if (!BACK)
		{
			do
			{
				gotoxy(38, 10);
				int status = InputPassword(L.acc.password);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(L.acc.password) == 0 && !BACK);
		}
		//Nhập Họ tên
		if (!BACK)
		{
			do
			{
				gotoxy(38, 12);
				int status = InputFullname(L.acc.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(L.acc.fullname) == 0 && !BACK);
		}
		
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 14);
			L.acc.sex = Input1Num();
			if (L.acc.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Degree
		if (!BACK)
		{
			gotoxy(38, 16);
			status = inputDegree(L.degree);
			if (L.degree== -1)
			{
				BACK = true;
			}
		}
		
		//Nhập Course
		if (!BACK)
		{
			gotoxy(38, 16);
			status = InputCourse(L.course);
			if (L.courses.lop == -1)
			{
				BACK = true;
			}
		}
		int n;
		char list[11];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Nếu username khả dụng thì tạo mới tài khoản kèm thông báo tạo thành công
			if (AcceptUser(L.acc.username))
			{
				AddAccount(L);
				drawRectangle(36, 12, 48, 3, 10);
				char Alert[100] = "SUCCESSFUL!";
				strcat(Alert, L.acc.username);
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Nếu username không khả dụng thì thông báo tài khoản đã được sử dụng
			else
			{
				drawRectangle(36, 12, 48, 3, 12);
				gotoxy(37, 13);
				char Alert[100] = "This account ";
				strcat(Alert, L.acc.username);
				strcat(Alert, " has been used");
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(36, 6, 48, 21, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}


//Hàm trả về dữ liệu tài khoản theo đường dẫn <LINK>
Accounts ReadAccount(char link[])
{
	Accounts B;
	FILE *f = fopen(link, "r");
	if (f)
	{
		fread(&B, sizeof(Accounts), 1, f);
		fclose(f);
	}
	return B;
}

//Viết dữ liệu <USER> vào file với đường dẫn <LINK>
int WriteAccount(char link[], Accounts user)
{
	fcloseall();
	FILE *f;
	errno_t err = fopen_s(&f, link, "w");
	if (err == 0)
	{
		fwrite(&user, sizeof(Accounts), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}



//Chỉnh sửa thông tin
void ModifyInfo()
{
	bool BACK = false;
	Title(">>CHANGE INFORMATION OF STUDENT");
	do
	{
		int n;
		char list[11];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);
		int k = ReadClassification();

		//Tạo đường dẫn đến file người dùng
		char link[256];
		if (k == 1)
		{
			strcpy(link, "user/staff/");
		}
		if (k == 2)
		{
			strcpy(link, "user/lecturer/");
		}
		if (k == 3)
		{
			strcpy(link, "user/student/");
		}
		strcat(link, user);
		strcat(link, ".txt\0");

		Accounts A = ReadAccount(link);

		///chua xong