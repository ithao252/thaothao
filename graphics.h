#pragma once

void resizeConsole(int width, int height);


void gotoxy(int x, int y);


void textColor(int color);


void textBgColor(int colorText, int colorBG);


void drawRectangleBorder(int positionX, int positionY, int width, int height, int color);


void drawRectangle(int positionX, int positionY, int width, int height, int color);


void drawBookshelf(int positionX, int positionY);

int whereX();


int whereY();

void SetBG();


void DrawAppNameTab(int TextColor, int BgColor);

void Title(char title[45]);

void VerticalLine(int PosX, int PosY, int Length, int TextColor, int BgColor);

void HorizontalLine(int PosX, int PosY, int Length, int TextColor, int BgColor);


void Nocursortype();


void Yescursortype();