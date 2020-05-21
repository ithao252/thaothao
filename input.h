#pragma once
//Kiểm tra <USERNAME> có đúng quy ước hay không?
bool ValidUser(char x);

//Kiểm tra <PASSWORD> có đúng quy ước hay không?
bool ValidPass(char x);

//Kiểm tra <FULLNAME> có đúng quy ước hay không?
bool ValidFullname(char x);

//Kiểm tra <CHAR> có phải kí tự số hay không?
bool ValidNum(char x);

//Hàm nhập <USERNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputUsername(char username[]);

//Hàm nhập <PASSWORD>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputPassword(char password[]);

//Hàm nhập <FULLNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputFullname(char fullname[]);

//Hàm nhập 1 số 1 hoặc 2, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input1Num();

//Hàm nhập 2 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input2Num();

//Hàm nhập 4 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input4Num();

//Hàm nhập 9 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
long Input9Num();

//Hàm nhập <ID>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputIndentity(char ID[]);

//Hàm nhập <CLASS>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputClass(char lop[]);

//Hàm nhập <STRING[44]>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputCourse(char course[]);

//Hàm nhập <SCORE>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputScore(char score[]);

//Hàm nhập <COURSE>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputCourse(char course[]);

//Hàm nhập <DEGREE>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputDegree(char degree[]);

//Hàm nhập <STRING[100]>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputString100(char string100[]);