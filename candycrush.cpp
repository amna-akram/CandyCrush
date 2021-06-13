//to exit pause mode you have to click on start 

#include<iostream>
#include<fstream>
#include<ctime>
#include<windows.h>
#include<cstdlib>
#include<stdlib.h>
#include "project.h"
//void DisableWindowMenuBar();
using namespace std;
int main()
{
	srand((int)time(0));
	int no;
	int arr[rows][col] = { 0 };
	//DisableWindowMenuBar();
	tosetboard(arr, no);
	displayboard(arr);
	playgame(arr, no);
	//system("pause");
	return 0;
}
//**************************
void tosetboard(int arr[][col], int & no)
{
	work(arr, no);
}
//****************************
void displayboard(int arr[][col])
{
	int x;
	float y;
	DrawButtons(70, 5, 70);
	int color = 0;
	char str[] = "    ";
	int i, j;
	int f = 0;
	y = 0;
	//cout << endl << endl;
	for (i = 0; i < rows; i++)
	{
		x = 0;
		for (j = 0; j < col; j++)
		{
			if (arr[i][j] >= 1 && arr[i][j] < 9)
			{
				if (arr[i][j] == 1)
				{
					color = 20;
				}
				if (arr[i][j] == 2)
				{
					color = 70;
				}
				if (arr[i][j] == 3)
				{
					color = 80;
				}
				if (arr[i][j] == 4)
				{
					color = 100;
				}
				if (arr[i][j] == 5)
				{
					color = 120;
				}
				if (arr[i][j] == 6)
				{
					color = 160;
				}
				if (arr[i][j] == 7)
				{
					color = 180;
				}
				if (arr[i][j] == 8)
				{
					color = 230;
				}
				PrintXY(x, y, str, color);
				//PrintXY(x, y + 1, str, color);
				//PrintXY(x, y+1, str, color);
			}
			x += 5;
		}
		y += 2;
	}
	cout << endl;
}
//************************************
//this function saves a digit of particular color to  a cell
void work(int arr[][col], int & no)
{
	no = rand() % 4 + 5; //no of colored boxes
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < col; j++)
		{
			int randno = rand() % no + 1;
			if ((arr[i][j - 1] == randno && arr[i][j - 2] == randno) || (arr[i - 1][j] == randno && arr[i - 2][j] == randno))
			{
				j--;
			}
			else
			{
				arr[i][j] = randno;
			}
		}
	}
}
//****************************************************************************

//**************************
void playgame(int arr[][col], int & no)
{
	int playr, playc, swapr, swapc;
	int f = 0;
	int score = 0;   //score is in such a way that if user crushes 3 candies together score is 30 and if 4 then
					 //40 which means per candy crushing gives 10 scores
	double finaltime = 0.0;
	float remaining_time = 1;
	int total_time = 30; //time allocated is 1 min
	float time_min = 0.0;
	int time2 = 0;
	int X1, Y1, X2, Y2;
	bool end = true;
	bool gameend = true;
	cout << "total time=" << total_time << " seconds" << endl;
	while (remaining_time > 0 && end == true && gameend == true)
	{
		time2 = 0;
		time_t begin = time(NULL);
		mousefunc(X1, Y1, X2, Y2);
		if (X1 >= 70 && X1 <= 75 && Y1 == 13)
		{
			gameend = false;
		}
		if (X1 >= 70 && X1 <= 79 && Y1 == 15)
		{
			tosetboard(arr, no);
			score = 0;
			remaining_time = 120;
			system("CLS");
			displayboard(arr);
			cout << "remaining time in min=" << time_min << "and remaining time in sec=" << remaining_time << endl;
			cout << "your score   =" << score << endl;
			mousefunc(X1, Y1, X2, Y2);
		}
		if (X1 >= 70 && X1 <= 88 && Y1 == 9)
		{
			loadgame(arr, score, remaining_time);
			system("CLS");
			displayboard(arr);
			cout << "remaining time in min=" << time_min << "and remaining time in sec=" << remaining_time << endl;
			cout << "your score   =" << score << endl;
			mousefunc(X1, Y1, X2, Y2);
		}
		if ((X1 >= 70 && X1 <= 75) && Y1 == 7)
		{
			end = false;
		}
		if (X1 >= 70 && X1 <= 75 && Y1 == 11)
		{
			time_t begin2 = time(NULL);
			mousefunc(X1, Y1, X2, Y2);
			if (X1 >= 70 && Y1 <= 75 && Y1 == 5)
			{
				time_t end2 = time(NULL);
				double time2 = double(end2 - begin2);
				cout << "game started again" << endl;
				mousefunc(X1, Y1, X2, Y2);
			}
		}
		else if (gameend == true && end == true)
		{
			playr = Y1 / 2;
			playc = X1 / 5;
			swapr = Y2 / 2;
			swapc = X2 / 5;
			while (playr < 0 || playr>9 || playc < 0 || playc>9 || swapr < 0 || swapr>9 || swapc < 0 || swapc>9)
			{
				mousefunc(X1, Y1, X2, Y2);
				playr = Y1 / 2;
				playc = X1 / 5;
				swapr = Y2 / 2;
				swapc = X2 / 5;
			}
			if ((playr == swapr && (playc - swapc == 1 || swapc - playc == 1)) || (playc == swapc && (playr - swapr == 1 || swapr - playr == 1)))
			{
				int temp = arr[playr][playc];
				arr[playr][playc] = arr[swapr][swapc];
				arr[swapr][swapc] = temp;
				//next steps are to swapback if colors dont match
				swapback(arr, playr, playc, swapr, swapc);
				implement(arr, score);
				move_down(arr, no);
				check(arr, no);
				system("CLS");
				displayboard(arr);
				time_t end = time(NULL);
				double time = double(end - begin);
				finaltime = finaltime + time;
				remaining_time = total_time - finaltime - time2;
				time_min = remaining_time / 60;
				cout << "remaining time in min=" << time_min << "and remaining time in sec=" << remaining_time << endl;
				cout << "your score   =" << score << endl;
			}
		}

	}
	if (end == true && gameend==true)
	{
		cout << "TIMES UP!!" << endl;
		high_scores(score);
		system("pause");
	}
	if (end == false)
	{
		cout << "YOU SAVED GAME" << endl;
		savegame(arr, score, remaining_time);
		system("pause");
	}
}
//********************************************************changeddddddddddd
//this function moves down the cells and generate new cells
void move_down(int arr[][col], int & no)
{
	int count = 0;
	int i, j;
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < rows; j++)
		{
			if (arr[j][i] == 0)
			{
				int worow = j;
				int wocol = i;
				while (worow > 0)
				{
					arr[worow][wocol] = arr[worow - 1][wocol];
					arr[worow - 1][wocol] = 0;
					worow--;
				}
			}
		}
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (arr[i][j] == 0)
			{
				int randno = rand() % no + 1;
				if ((arr[i][j - 1] == randno && arr[i][j - 2] == randno) || (arr[i - 1][j] == randno && arr[i - 2][j] == randno) || (arr[i][j + 1] == randno && arr[i][j + 2] == randno) || (arr[i + 1][j] == randno && arr[i + 2][j] == randno))
				{
					j--;
				}
				else if ((arr[i][j - 1] == randno && arr[i][j + 1] == randno) || arr[i - 1][j] == randno && arr[i + 1][j] == randno)
				{
					j--;
				}
				else
				{
					arr[i][j] = randno;
				}
			}
		}

	}
}
//*************************************************************
//ths function is to find sequence
void implement(int arr[][col], int & score)
{
	bool found = true;
	int i, j;
	int oprow, opcol;
	for (i = 0; i < rows; i++) //runs row vise
	{
		found = true;
		for (j = 0; j < col; j++) //////////////////changes made there
		{
			found = true;
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && j < 8 && arr[i][j] != 0)
			{
				found = false;
				oprow = i;
				opcol = j;
			}
			if (found == false)
			{
				int temp2 = arr[oprow][opcol];   //temp2 stores the value which is repeated rowwise
				int a = oprow, b = opcol;
				while (arr[a][b] == temp2 && b < 10)
				{
					arr[a][b] = 0;
					b++;
					score += 10;
				}
			}
		}
	}
	bool found2 = true;
	int oprow2, opcol2;
	for (i = 0; i < col; i++) //runs col vise
	{
		found2 = true;
		for (j = 0; j < rows && found2 == true; j++)
		{
			found2 = true;
			if (arr[j][i] == arr[j + 1][i] && arr[j + 1][i] == arr[j + 2][i] && j < 8 && arr[i][j] != 0)
			{
				found2 = false;
				oprow2 = j;
				opcol2 = i;
			}
			if (found2 == false)
			{
				int temp3 = arr[oprow2][opcol2];
				int c = oprow2, d = opcol2;
				while (arr[c][d] == temp3 && c < 10)
				{
					arr[c][d] = 0;
					score += 10;
					c++;
				}
			}
		}
	}

}

//****************************************************************
//this overloaded function prints a string str in specified color at pos(x,y) 
void PrintXY(int x, float y, const char str[], int color)
{
	COORD c;
	c.X = x;
	c.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	short ret = info.wAttributes;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, color);
	cout << str;
	cout.flush();
	SetConsoleTextAttribute(h, ret);
}
//******************************************************
/*void DisableWindowMenuBar() {
DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
DrawMenuBar(GetConsoleWindow());
DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MAXIMIZE, MF_BYCOMMAND);
DrawMenuBar(GetConsoleWindow())


}*/
//this function checks that if after swapping and moving the cells downward cells of same color appears
//if cells of same colors appear it crushes them and again repeat the moving down of cells
void check(int arr[][col], int & no)
{
	int score;
	implement(arr, score);
	move_down(arr, no);
}
void swapback(int arr[][col], int & playr, int & playc, int & swapr, int & swapc)
{
	bool ch = true;
	if (arr[playr][playc] == arr[playr + 1][playc] && arr[playr + 1][playc] == arr[playr + 2][playc] && playr < 8)
	{
		ch = false;
	}
	else if (arr[playr][playc] == arr[playr - 1][playc] && arr[playr - 1][playc] == arr[playr - 2][playc] && playr > 1)
	{
		ch = false;
	}
	else if (arr[playr][playc] == arr[playr][playc + 1] && arr[playr][playc + 1] == arr[playr][playc + 2] && playc < 8)
	{
		ch = false;
	}
	else if (arr[playr][playc] == arr[playr][playc - 1] && arr[playr][playc - 1] == arr[playr][playc - 2] && playc > 1)
	{
		ch = false;
	}
	else if (arr[swapr][swapc] == arr[swapr + 1][swapc] && arr[swapr + 1][swapc] == arr[swapr + 2][swapc] && swapr < 8)
	{
		ch = false;
	}
	else if (arr[swapr][swapc] == arr[swapr - 1][swapc] && arr[swapr - 1][swapc] == arr[swapr - 2][swapc] && swapr > 1)
	{
		ch = false;
	}
	else if ((arr[swapr][swapc] == arr[swapr][swapc + 1] && arr[swapr][swapc + 1] == arr[swapr][swapc + 2] && swapc < 8))
	{
		ch = false;
	}
	else if (arr[swapr][swapc] == arr[swapr][swapc - 1] && arr[swapr][swapc - 1] == arr[swapr][swapc - 2] && swapc > 1)
	{
		ch = false;
	}
	else if (arr[swapr][swapc] == arr[swapr][swapc + 1] && arr[swapr][swapc] == arr[swapr][swapc - 1] && swapc > 0 && swapc < 9)
	{
		ch = false;
	}
	else if (arr[playr][playc] == arr[playr][playc + 1] && arr[playr][playc] == arr[playr][playc - 1] && playc > 0 && playc < 9)
	{
		ch = false;
	}
	else if (arr[swapr][swapc] == arr[swapr + 1][swapc] && arr[swapr][swapc] == arr[swapr - 1][swapc] && swapr > 0 && swapr < 9)
	{
		ch = false;
	}
	else if (arr[playr][playc] == arr[playr + 1][playc] && arr[playr][playc] == arr[playr - 1][playc] && playr > 0 && playr < 9)
	{
		ch = false;
	}
		if (ch == true)
	{
		int temp = arr[playr][playc];
		arr[playr][playc] = arr[swapr][swapc];
		arr[swapr][swapc] = temp;
	}
}
void high_scores(int score)
{
	ifstream fin;
	char name[11][10];
	int score2[11];
	fin.open("score.txt");
	if (!fin)
	{
		cout << "error no file exist 1st create a file" << endl;
	}
	else
	{
		
		int i = 0;
		while (!fin.eof())
		{
			fin >> name[i];
			fin >> score2[i];
			i++;
		}
		cout << "enter your first name" << endl;
		cin >> name[i];
		score2[i] = score;
		int j;
		for (j = 0; j < i + 1 && j<11; j++)
		{
			int max = j;
			for (int k = j + 1; k < i + 1 && k<11; k++)
			{
				if (score2[max] < score2[k])
				{
					max = k;
				}
			}
			int temp = score2[max];
			char tempname[10];
			for (int k = 0; k < 10 && name[max][k - 1] != '/0'; k++)
			{
				tempname[k] = name[max][k];
			}
			score2[max] = score2[j];

			for (int k = 0; k < 10 && name[j][k - 1] != '/0'; k++)
			{
				name[max][k] = name[j][k];
			}
			score2[j] = temp;
			for (int k = 0; k < 10 && tempname[k - 1] != '/0'; k++)
			{
				name[j][k] = tempname[k];
			}

		}
		fin.close();
		ofstream fout;
		fout.open("score.txt");
		cout << "high scores are" << endl;
		for (int m = 0; m < i && m<10; m++)
		{
			fout << name[m] << "   " << score2[m] << endl;
			cout << name[m] << "   " << score2[m] << endl;
		}
		fout.close();
	}
	for (int i = 0; i < 11; i++)
	{
		score2[i] = 0;
		name[i][0] =  '\0' ;
	}
	
}
void mousefunc(int & X1, int & Y1, int & X2, int & Y2)
{
	X2 = 0, Y2 = 0;
	DWORD temp = SetUpMouse();
	int mInput1 = 0, kInput;
	int mInput2 = 0;
	int c = 0;
	while (mInput1 != 3)
	{
		c = GetInput(kInput, mInput1, X1, Y1);
	}
	int c2 = 0;
	if (((X1 <= 70) && Y1 != 7) && ((X1 <= 70) && Y1 != 9) && (X1 <= 70 && (Y1 != 11 && Y1 != 5 && Y1 != 13 && Y1 != 15)))
	{
		while (mInput2 != 3)
		{
			c2 = GetInput(kInput, mInput2, X2, Y2);
		}
	}
}
DWORD SetUpMouse() {
	// Get the standard input handle. 

	DWORD fdwSaveOldMode;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		printf("Error in GetStdHandle \n");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		printf("Error inGetConsoleMode \n");

	// Enable the window and mouse input events. 

	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		printf("Error in SetConsoleMode\n");
	return fdwSaveOldMode;
}
//Check for input events(mouse and keyboard) and returns the type of the event occured 
//If input event doesnot occured then the fuction returns 0, 
//to indicate error it returns -1
//For keyboard events the function returns 1 and save the ascii of the key pressed in kInput
//For mouse events it returns 2 and save the further information in variable mInput.. 
// --------- If mouse is moved then mInput =1,  For double click mInput =2 
// --------- If left button is pressed mInput =3, For right button mInput=4, 
// ---------  and  for mouse button released mInput =5
int GetInput(int & kInput, int &mInput, int & X, int & Y) {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD cNumRead, i;
	LPDWORD x = &i;
	INPUT_RECORD irInBuf[1];
	mInput = -1, kInput = -1, X = -1, Y = -1;
	GetNumberOfConsoleInputEvents(hStdin, x);
	int etype = 0; //type of event occured .. For no_event value is 0, for keyboard =1, for mouse value is 2

	if (i > 0) {

		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			1,         // size of read buffer 
			&cNumRead)) // number of records read 
			return -1;// error: cannot read the input

		switch (irInBuf[0].EventType)
		{
		case KEY_EVENT: // keyboard input 
			if (irInBuf[0].Event.KeyEvent.bKeyDown) {
				kInput = irInBuf[0].Event.KeyEvent.wVirtualKeyCode;
				etype = 1;
			}
			break;

		case MOUSE_EVENT: // mouse input 
			mInput = MouseEventProc(irInBuf[0].Event.MouseEvent);
			X = irInBuf[0].Event.MouseEvent.dwMousePosition.X;
			Y = irInBuf[0].Event.MouseEvent.dwMousePosition.Y;
			etype = 2;
			break;
		default:
			break;
		}

	}
	return etype;

}
int MouseEventProc(MOUSE_EVENT_RECORD mer) {
	//printf("Mouse event: ");
	int b = mer.dwEventFlags;
	switch (mer.dwEventFlags) {
	case 0:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			b = 3;  //printf("left button press \n");
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			b = 4; // printf("right button press \n");
		else
			b = 5;	//printf(" button released \n");			
		break;
	case DOUBLE_CLICK:
		b = DOUBLE_CLICK;	//printf("double clicked at x=%d, y=%d\n\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		break;
	case MOUSE_MOVED:
		b = MOUSE_MOVED;// printf("mouse moved\n");
		break;

	default:
		//printf("unknown\n");
		break;
	}

	return b;
}
//Draw buttons on the screen starting from given co-ordinates 
void DrawButtons(int x, int y, int color) {
	PrintXY(x, y, " START ", color);
	PrintXY(x, y + 2, " SAVE ", color);
	PrintXY(x, y + 4, "LOAD PREVIOUS GAME", color);
	PrintXY(x, y + 6, " PAUSE ", color);
	PrintXY(x, y + 8, " EXIT ", color);
	PrintXY(x, y + 10, " NEW GAME ", color);

}
void savegame(int arr[][col], int score, float remaining_time)
{
	ofstream fout;
	fout.open("save.txt");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fout << arr[i][j] << "   ";
		}
		fout << endl;
	}
	fout << endl;
	fout << score << endl;
	fout << remaining_time;
	fout.close();
}
void loadgame(int arr[][col], int & score, float & remaining_time)
{
	ifstream fin;
	fin.open("save.txt");
	if (!fin)
	{
		cout << "error there is no saved game available!!" << endl;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				fin >> arr[i][j];
			}
		}

		fin >> score;
		fin >> remaining_time;
	}
	fin.close();
}



