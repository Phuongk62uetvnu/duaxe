#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<math.h>


#define rong 80
#define cao 28

using namespace std;

// Bien la 1 va 25

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

struct Toado {
	int x, y;//  Y là tung do , x là hoành do
			 // Tung dộ tăng thì đi xuống , giảm thì đi lên
};

struct Hinhdang {
	char a[3][3];
};

struct Xe {
	Toado td;
	Hinhdang hd;
	int diem;
	int level;
};

struct Vatcan {
	Toado td;
	Hinhdang hd;
};


void Khoitao(Xe &xe, Vatcan &vc1, Vatcan &vc2)
{

	//-------------- XE dua----------------
#define tdx xe.hd.a // tdx toa do xe dua
	xe.diem = 0;
	xe.level = 0;
	xe.td.y = cao - 1;
	xe.td.x = cao / 2;
	tdx[0][0] = tdx[0][2] = tdx[2][0] = tdx[2][2] = '@';
	tdx[1][1] = 'X';// than xe
	tdx[1][0] = tdx[1][2] = '*';//2 ben than xe
	tdx[0][1] = tdx[2][1] = ' ';

#define tdxvc1 vc1.hd.a // tdxvc  toa độ xe vật cản 1

	vc1.td.x = 3 + rand() % (cao - 4);
	vc1.td.y = -2;

	tdxvc1[0][0] = tdxvc1[0][2] = tdxvc1[2][0] = tdxvc1[2][2] = '*';
	tdxvc1[1][1] = '*';// than xe
	tdxvc1[1][0] = tdxvc1[1][2] = '*';//2 ben than xe
	tdxvc1[0][1] = tdxvc1[2][1] = ' ';

	//------------------ V? Xe vật cản 2-----------------

#define tdxvc2 vc2.hd.a // tdxvc  toa do xe vat can

	vc2.td.x = 3 + rand() % (cao - 4);
	vc2.td.y = -2;

	tdxvc2[0][0] = tdxvc2[0][2] = tdxvc2[2][0] = tdxvc2[2][2] = '*';
	tdxvc2[1][1] = '*';// than xe
	tdxvc2[1][0] = tdxvc2[1][2] = '*';//2 ben than xe
	tdxvc2[0][1] = tdxvc2[2][1] = ' ';
}

void Hienthi(Xe xe, Vatcan vc1, Vatcan vc2) {
	clrscr();

	// --------------Hien thi đường dua--------------//

	for (int i = 0; i <= cao; i++) {
		gotoXY(1, i);
		textcolor(187);
		cout << "|\n";
		textcolor(7);
	}

	for (int i = 0; i <= cao; i++) {
		gotoXY(cao, i);
		textcolor(187);
		cout << "|";
		textcolor(7);
	}

	// -----------------hiển thị xe dua--------------------//

	for (int kdong = -1; kdong <= 1; kdong++) {
		for (int kcot = -1; kcot <= 1; kcot++) {
			int x = kcot + xe.td.x;
			int y = kdong + xe.td.y;
			gotoXY(x, y);
			textcolor(14);
			cout << xe.hd.a[kdong + 1][kcot + 1];
			textcolor(7);
		}
	}

	//------------------Hiên thị xe vật cản 2 --------------------//

	for (int kdong = -1; kdong <= 1; kdong++) {
		for (int kcot = -1; kcot <= 1; kcot++) {
			int x = kcot + vc1.td.x;
			int y = kdong + vc1.td.y;
			if (y >= 0 && y <= cao) {
				gotoXY(x, y);
				textcolor(12);
				cout << vc1.hd.a[kdong + 1][kcot + 1];
				textcolor(7);
			}
		}
	}

	//------------------Hiên thị xe vật cản 2 --------------------//

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++)
		{
			int z, t;
			z = j + vc2.td.x;
			t = i + vc2.td.y;

			if (t >= 0 && t <= cao)
			{
				gotoXY(z, t);
				textcolor(13);
				cout << vc2.hd.a[i + 1][j + 1];
				textcolor(7);
			}
		}
	}

	//---------------hiển thị trạng thái game---------------/

	gotoXY(cao + 2, 10);
	textcolor(9);
	cout << "Diem cua ban la " << xe.diem;
	textcolor(7);
	gotoXY(cao + 2, 15);
	textcolor(10);
	cout << "lever cua ban la " << xe.level;
	textcolor(7);
}

void Ve1() {
	for (int i = 0; i <= cao; i++) {
		if (i % 2 != 0) {
			gotoXY(cao / 2, i);
			cout << "|";
		}
	}
}

void Ve2() {
	for (int i = 0; i <= cao; i++) {
		if (i % 2 == 0) {
			gotoXY(cao / 2, i);
			cout << "|";
		}
	}
}

void Dieukhien(Xe &xe) {
	if (_kbhit()) {
		int key = _getch();
		if ((key == 'a' || GetAsyncKeyState(VK_LEFT)) && xe.td.x > 3) {
			xe.td.x--;
		}
		else if ((key == 'd' || GetAsyncKeyState(VK_RIGHT)) && xe.td.x < cao - 2) {
			xe.td.x++;
		}
		else if ((key == 'z' || GetAsyncKeyState(VK_DOWN)) && xe.td.y < cao - 1) {
			xe.td.y++;
		}
		else if ((key == 'w' || GetAsyncKeyState(VK_UP)) && xe.td.y > 1) {
			xe.td.y--;
		}
	}
}

int Xuly(Xe &xe, Vatcan &vc1, Vatcan &vc2, int &Thoigian){
	//----------------------------tao cam giac vat can di chuyen------------------//	
	vc1.td.y++;
	vc2.td.y = vc2.td.y + 2;

	//-----------------------------------------tang diem va tang toc do cua xe---------------------------------
	if (vc1.td.y > cao || vc2.td.y > cao)
	{
		xe.diem++;

		if (xe.diem % 10 == 0)
		{
			xe.level++;
			if (Thoigian >= 30)
				Thoigian = Thoigian - 20;   //tang toc vat can
		}

		if (vc1.td.y > cao)
		{
			vc1.td.x = 3 + rand() % (cao - 4);	 // khoi tao vat can 1 sau khi xe bien mat
			vc1.td.y = -2;
		}

		if (vc2.td.y > cao)
		{
		vc2.td.x = 3 + rand() % (cao - 4);// khoi tao vat can 2 sau khi xe bien mat
		vc2.td.y = -2;
		}
	}

	//------------------------------XU LY TINH HUONG VA CHAM---------------------//
	int dx = abs(xe.td.x - vc1.td.x);           // khoang cach giua tam xe va tam vat can 1
	int dy = abs(xe.td.y - vc1.td.y);           // khoang cach xe va vat can 1

	int dxx = abs(xe.td.x - vc2.td.x);          // khoang cach giua tam xe va tam vat can 2
	int dyy = abs(xe.td.y - vc2.td.y);          // khoang cach xe va vat can 2

	if (dx <3 && dy <3){
		return 1;
	}
	else if (dxx < 3 && dyy <3){
		return 1;
	}
	else
		return 0;
}

int main() {
	srand(time(0));

	Xe xe;

	Vatcan vc1, vc2;

	int ma = 0;

	int a = 0;

	int Thoigian = 200;

	Khoitao(xe, vc1, vc2);

	while (true) {

		//srand(time(0));
		Hienthi(xe, vc1, vc2);

		a++;
		if (a % 2 == 0) {
			Ve1();
		}
		else {
			Ve2();
		}
		if (a >= 100) {
			a = 0;
		}

		Dieukhien(xe);

		ma = Xuly(xe, vc1, vc2, Thoigian);

		if (ma == 1) {
			gotoXY(30, 5);
			textcolor(13);
			cout << "Ban thua game roi";
			textcolor(7);
			break;
		}
		Sleep(Thoigian);
	}
	system("pause");
	return 0;
}
