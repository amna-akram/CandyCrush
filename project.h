#ifndef PROJECT_H_INCLUDE
#define PROJRECT_H_INCLUDE
int const rows = 10;
int const col = 10;
void tosetboard(int arr[][col], int & no);
void work(int arr[][col], int & no);
void implement(int arr[][col], int & score);
void PrintXY(int x, float y, const char str[], int color);
void move_down(int arr[][col], int & no);
void check(int arr[][col], int & no);
void playgame(int arr[][col], int & no);
void swapback(int arr[][col], int & playr, int & playc, int & swapr, int & swapc);
void displayboard(int arr[][col]);
void high_scores(int score);
void mousefunc(int & X1, int & Y1, int & X2, int & Y2);
DWORD SetUpMouse();
int GetInput(int & kInput, int &mInput, int & X, int & Y);
int MouseEventProc(MOUSE_EVENT_RECORD mer);
void DrawButtons(int x, int y, int color);
void savegame(int arr[][col], int score, float remaining_time);
void loadgame(int arr[][col], int & score, float & remaining_time);
#endif