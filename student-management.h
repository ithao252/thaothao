#pragma once
struct Day
{
	int date;
	int month;
	int year;
};
struct Accounts
{
	char username[21];
	char password[21];
	bool active;
	char fullname[45];
	int sex;
	int type;// giao vu, giao vien, sinh vien
};
struct lop {
	char tenlop[50];
};
struct course {
	char IDcourse[10];
	char nameCourse[50];
	char startDate[20];
	char endDate[20];
	char dayOfWeek[5];
	char startHour[5];
	char startMinute[5];
	char endHour[5];
	char endMinute[5];
};
struct semester {
	char namhoc[20];
	char hocki[10];
	course course[20];
};
struct student
{
	Accounts acc;
	Day DoB;
	course courses;
	char ID;

};
struct scoreBoard {
	student tensv;
	char midterm[10];
	char final[10];
	char bonus[10];
	char total[10];

};
struct lecturer {
	Accounts acc;
	course course;
	char degree;
	
};
struct schedule {
	course course;
	lecturer lecturer;
	char room[5];
};

struct Node_Class {
	lop data;
	Node_Class* next;
	Node_Class* prev;
};
struct List_Class {
	Node_Class* head;
	Node_Class* tail;
};
struct Node_Student {
	student data;
	Node_Student* next;
	Node_Student* prev;
};
struct List_Student {
	Node_Student* head;
	Node_Student* tail;
};
struct Node_Course {
	course data;
	Node_Course* next;
	Node_Course* prev;
};
struct List_Course {
	Node_Course* head;
	Node_Course* tail;
};
struct Node_Lecturer {
	lecturer data;
	Node_Lecturer* next;
	Node_Lecturer* prev;
};
struct List_Lecturer {
	Node_Lecturer* head;
	Node_Lecturer* tail;
};
struct Node_Scoreboard {
	scoreBoard data;
	Node_Scoreboard* next;
	Node_Scoreboard* prev;
};
struct List_Scoreboard {
	Node_Scoreboard* head;
	Node_Scoreboard* tail;
};
#define MAXWIDTH 120
#define MAXHEIGHT 30