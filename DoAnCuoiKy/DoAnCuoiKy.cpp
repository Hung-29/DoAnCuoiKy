#pragma once  //Tranh dung do thu vien khi goi chong file len nhau
#include <stdio.h>
#include <conio.h>
#include<ctime> 
#include "windows.h" 
#define KEY_NONE	-1
// Lay toa do x cua con tro tai thoi diem hien tai
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
// Lay toa do y cua con tro tai thoi diem hien tai
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
// Dich con tro hien tai den diem co toa do (x,y)
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
// Cai dat mau sac cho CHU
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// Lam an tro chuot 
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
// Tra ve phim nguoi dung
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}

#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int speed = 150;
struct TOADO {
	int x;
	int y;
};
typedef struct TOADO toaDo;
// Nhap phim bat ky de tiep tuc
void NhapPhimBatKy() {
	int y = 0;
	gotoXY(0, y);
	cout << "Nhap phim bat ky de tiep tuc!              ";
	while (y < 14) {
		y++;
		gotoXY(0, y);
		cout << "                                      ";
	}
	_getch();
}
// Xoa MeNu
void XoaMenu() {
	int y = 0;
	for (int i = 0; i < 14; i++) {
		gotoXY(0, y);
		cout << "                                   ";
		y++;
	}
}

// Swap
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

// Input
void input(int a[], int& n) {
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		int r = rand() % (100 + 100 + 1) - 100;
		a[i] = r;
		cout << "Phan tu thu " << i + 1 << " la : ";
		cin >> a[i];

	}
}

// Output
void output(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

// Ve hinh vuong
void veHinhVuong(int x, int y) {
	gotoXY(x, y);
	cout << "******";
	for (int i = 0; i < 3; i++) {
		y++;
		gotoXY(x, y);
		cout << "*    *";
	}
	gotoXY(x, y);
	cout << "******";
}
// Ve hinh co so
void VeSo(int x, int y, int k) {
	veHinhVuong(x, y);
	gotoXY(x + 2, y + 1);
	SetColor(9);
	cout << k;
	SetColor(7);
}
// Phan tu trong mang
void VeMang(int a[], toaDo b[], int n) {
	int x = 15, y = 18;
	for (int i = 0; i < n; i++) {
		SetColor(12);
		VeSo(x, y, a[i]);
		Sleep(speed);
		b[i].x = x;
		b[i].y = y;
		x += 8;
	}
}

// Xoa hinh
void XoaHinhVuong(int x, int y) {
	gotoXY(x, y);
	cout << "      ";
	for (int i = 0; i < 3; i++) {
		y++;
		gotoXY(x, y);
		cout << "      ";
	}
	gotoXY(x, y);
	cout << "      ";
}

//Ve so thi co Xoa so
void XoaSo(int x, int y) {
	XoaHinhVuong(x, y);
	gotoXY(x + 3, y + 1);
	cout << "";
}

// Xoa mang
void XoaMang(int a[], toaDo b[], int n) {
	int x = 3, y = 4;
	for (int i = 0; i < n; i++) {
		XoaSo(x, y);
		x += 8;
		Sleep(1100);
	}
}
// Di xuong
void diXuong(int x1, int y1, int x2, int y2, int limitBottom, int value1, int value2) {
	while (y1 < limitBottom) {
		int r = rand() % (14 - 1 + 1) + 1;
		if (y1 == limitBottom - 1)
			r = 12;
		SetColor(r);
		if (y1 < limitBottom) {
			XoaSo(x1, y1);
			y1++;
			VeSo(x1, y1, value1);
		}
		SetColor(r);
		if (y2 < limitBottom) {
			XoaSo(x2, y2);
			y2++;
			VeSo(x2, y2, value2);
		}
		Sleep(speed);
	}
}
// Xoa chu
void XoaChu(int x, int y) {
	gotoXY(x, y);
	cout << "                            ";
}
// Mo phong sap xep
void MPSapXep(toaDo b[], int pos1, int pos2, int value1, int value2) {
	if (value1 == value2)
		return;
	int x1, x2, y1, y2;
	x1 = b[pos1].x;
	y1 = b[pos1].y;
	x2 = b[pos2].x;
	y2 = b[pos2].y;

	// di chuyen len
	int limitBottom = y1;
	int limitUp = y1 - 5;
	int limitLeft = x1;
	int limitRight = x2;
	while (y1 >= limitUp) {
		int r = rand() % (14 - 1 + 1) + 1;
		SetColor(r);
		XoaSo(x1, y1);
		y1--;
		VeSo(x1, y1, value1);
		SetColor(r);
		XoaSo(x2, y2);
		y2--;
		VeSo(x2, y2, value2);
		Sleep(speed);
	}
	int start = x1 + ((x2 - x1) / 2);
	int end = y1 - 2;
	gotoXY(start, end);
	SetColor(1);
	if (value1 < value2) {
		cout << value1 << " < " << value2 << endl;
		Sleep(1000);
		XoaChu(start, end);
		diXuong(x1, y1, x2, y2, limitBottom, value1, value2);
		return;
	}
	else {
		cout << value1 << " >= " << value2 << endl;
		Sleep(1000);
		XoaChu(start, end);
	}
	while (x1 < limitRight) {
		int r = rand() % (14 - 1 + 1) + 1;
		SetColor(r);
		if (x1 < limitRight) {
			XoaSo(x1, y1);
			x1++;
			VeSo(x1, y1, value1);
			XoaSo(x2, y2);
		}
		SetColor(r);
		if (x2 > limitLeft) {
			XoaSo(x2, y2);
			x2--;
			VeSo(x2, y2, value2);
		}
		Sleep(speed);
	}
	diXuong(x1, y1, x2, y2, limitBottom, value1, value2);
}

// SELECTION SORT
void selectionSort(int arr[], toaDo b[], int n)
{
	int max;
	//Di chuyen ranh gioi cua mang da sap xep va chua sap xep
	for (int i = n - 1; i >= 0; i--)
	{
		int vt = i;
		int temp = INT_MIN; //am vo cuc
		// Tim phan tu LON NHAT trong mang chua sap xep
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[i] && arr[j] > temp) {
				temp = arr[j];
				vt = j;
			}
		}
		max = vt;
		arr[max] = temp;
		//Doi cho phan tu LON NHAT voi phan tu CUOI CUNG
		MPSapXep(b, max, i, arr[max], arr[i]);
		swap(arr[i], arr[max]);
	}
	gotoXY(50, 2);
	SetColor(13);
	cout << "SAP XEP HOAN TAT!";
	SetColor(7);
}
void sort_shell(int arr[], toaDo b[], int n) {
	for (int k = n / 2; k > 0; k /= 2) {
		for (int i = k; i < n; i += 1) {
			int temp = arr[i];
			int j = i;
			for (j = i; j >= k && arr[j - k] > temp; j -= k) {
				arr[j] = arr[j - k];
			}
			MPSapXep(b, j, i, arr[j], arr[i]);
			arr[j] = temp;
		}
	}
}

// QUICK SORT
void quickSort(int a[], toaDo b[], int l, int r) {
	int p = a[(l + r) / 2];
	int i = l, j = r;
	while (i < j) {
		while (a[i] < p) {
			i++;
		}
		while (a[j] > p) {
			j--;
		}
		if (i <= j) {
			MPSapXep(b, i, j, a[i], a[j]);
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	if (i < r) {
		quickSort(a, b, i, r);
	}
	if (l < j) {
		quickSort(a, b, l, j);
	}
	gotoXY(50, 2);
	SetColor(13);
	cout << "SAP XEP HOAN TAT!";


}

//COMPARISON SORT
void Comparison(int arr[], toaDo b[], int n)
{
	int* count = (int*)malloc(sizeof(int));
	int i, j;
	for (i = 0; i < n; i++)
	{
		count[i] = 0;
	}
	for (i = n - 1; i >= 1; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[i] <= arr[j])
			{
				count[j] += 1;
				MPSapXep(b, j, i, arr[j], arr[i]);
				swap(arr[j], arr[i]);
			}
			else

				count[i] += 1;
		}
	}
	gotoXY(50, 2);
	SetColor(13);
	cout << "SAP XEP HOAN TAT!";
	SetColor(7);
}

//SHELL SORT
void shellSort(int a[], toaDo b[], int n) {
	int interval, i, j, temp;
	for (interval = n / 2; interval > 0; interval /= 2) {
		for (i = interval; i < n; i++) {
			temp = a[i];
			for (j = i; j >= interval && a[j - interval] > temp; j -= interval) {
				a[j] = a[j - interval];
			}
			MPSapXep(b, j, i, a[j], temp);
			a[j] = temp;
		}
	}
	gotoXY(50, 2);
	SetColor(13);
	cout << "SAP XEP HOAN TAT!";
	SetColor(7);
}
// ve duong bao 
void VeDuongBao(int x1, int y1, int x2, int y2) {
	int up = y1 - 1;
	int down = y1 + 1;
	int left = x1 - 1;
	int right = x2 + 1;
	int r = rand() % (15 - 0 + 1);
	SetColor(r);
	for (int i = left; i <= right; i++) {
		gotoXY(i, up);
		cout << "*";
	}
	for (int i = up; i <= down; i++) {
		gotoXY(left, i);
		cout << "*";
	}
	for (int i = left; i <= right; i++) {
		gotoXY(i, down);
		cout << "*";
	}
	for (int i = down; i >= up; i--) {
		gotoXY(right, i);
		cout << "*";
	}
	SetColor(7);
}

// Menu
void MeNu(int a[], toaDo b[], int n) {
	int choose;
	while (1) {
		gotoXY(0, 0);
		cout << "______________MENU_____________\n";
		cout << " 1. Nhap mang\n";
		cout << " 2. Selection Sort\n";
		cout << " 3. Quick Sort\n";
		cout << " 4. Comparision Couting Sort\n";
		cout << " 5. Shell Sort\n";
		cout << " 0. Thoat\n";
		cout << "_______________________________\n";
		cout << "Ban chon: ";

		cin >> choose;
		switch (choose) {
		case 1:
			system("cls");
			input(a, n);
			VeMang(a, b, n);
			NhapPhimBatKy();
			break;
		case 2:
			selectionSort(a, b, n);
			NhapPhimBatKy();
			break;
		case 3:
			quickSort(a, b, 0, n - 1);
			NhapPhimBatKy();
			break;
		case 4:
			Comparison(a, b, n);
			NhapPhimBatKy();
		case 5:
			shellSort(a, b, n);
			NhapPhimBatKy();
			break;
		case 0:
			system("cls");
			gotoXY(30, 30);
			cout << "KET THUC CHUONG TRINH!";
			_getch();
			return;
		}
		XoaMenu();
	}
}

int main() {
	srand(time(NULL));
	int a[100], n = 0; // thuat toan seclectionsort
	toaDo b[100]; // danh sach luu tru toado selection va quicksort
	MeNu(a, b, n);

}

