#pragma once
//Tạo giao diện đăng nhập cho người dùng
void LayoutLogin(char username[], char password[]);

//Trả về loại người dùng, -1 nếu username hoặc password không chính xác
int Login(char username[], char password[]);

//Hàm nhận vào loại người dùng để đưa vào menu với tính năng tương ứng
void CaseLogin(int n);

//Lặp lại bước nhập username và password đến khi nào đăng nhập thành công hoặc ấn phím esc
void RepeatInput(char username[], char password[]);

//Đăng xuất
void LogOut();