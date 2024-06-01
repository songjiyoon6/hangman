#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h> 

#define UP 0
#define DOWN 1
#define SUBMIT 4
#define QUIT 5


void init();//콘솔창 등장 및 크기 조절
void game();
int check(char sol[], char ans[], char ch);
int menu();
void gotoxy(int x, int y);
int keyControl();
void how();
void titleDraw();

int main() {
    srand(time(NULL));// 랜덤 시드 초기화
    init();
    for (int i = 0; i < 2; i++) {
        titleDraw();
        int menuCode = menu();
        if (menuCode == 10) {
            game();
        }
        else if (menuCode == 11) {
            how();
        }
        else if (menuCode == 12) {
            break;
        }
        system("cls");
    }
    
    getchar(); //계속하려면~~~ 안 보이게 하려고 임시로

    return 0;
}

void init() {
    system("mode con cols=50 lines=20 | title Hangman Game");//콘솔창 크기 조절(폭 94문자, 높이 25줄), 콘솔창 이름 설정
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0; //커서 숨기기
    ConsoleCursor.dwSize = 1; //커서 크기 1로 설정
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void game() {
    system("cls");
    int HP = 10; //생명 10개
    char solution[10][20] = { "apple","banana","orange","pineapple","source","queen","company","korea","chair","computer" }; // 정답
    char answer[10][20] = { "_____", "______", "______", "_________", "______", "_____", "_______", "_____", "_____", "________" }; // 플레이어가 입력할 곳(현재까지 맞춘 것)
    char ch; //문자 입력 (맞히기)

    int random = rand() % 10; // 0 ~ 9


    while (1) {
        for (int i = 1; i <= HP; i++) {
            printf("♥");
        }
        printf("\n진행상황: %s\n", answer[random]);
        printf("문자 입력: ");
        ch = getchar(); //getchar(): 입력한 문자 버퍼o, echo 즉 엔터 쳐야 전달됨
        if (check(solution[random], answer[random], ch) == 1) { //1: 모든 문자 일치 정답! => 게임 종료 0: 이어서 입력받기
            printf("정답! %s\n", answer[random]);
            break;
        }
        else if (check(solution[random], answer[random], ch) == 0) {
            HP -= 1;
        }
        if (HP == 0) {
            printf("HP 소진! 게임 종료\n");
            break;
        }
        getchar(); //줄바꿈 문자
        }
    }
    
int check(char sol[], char ans[], char ch) {//solution[random][], answer[random][random][], ch
    int tmp = 0;
    for (int i = 0; sol[i] != 0; i++) {
        if (sol[i] == ch) { //solution[random]에 입력한 문자와 일치하는 것이 있다면
            ans[i] = ch; //answer[random]의 해당 위치에 문자 넣어주기(ex.____ -> __a_)
            tmp = 1;

        }
    }

    if (strcmp(sol, ans) == 0)return 1; //solution[random],answer[random] 모든 문자 일치 정답!
    else if (tmp == 0) return 0;
    else return 2; //solution[random]에 있는 문자를 answer[random]에 넣기

}

int menu() {
    int x = 18;
    int y = 10;
    gotoxy(x, y);
    printf("> 게임시작");
    gotoxy(x, y + 1);
    printf("> 게임방법");
    gotoxy(x, y + 2);
    printf("> 끝내기  ");

    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 10) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 12) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y;
        }
        }
    }
}


int keyControl() { //방향키, submit 
    char temp = _getch();
    if (temp == 'w' || temp == 'W') {
        return UP;
    }
    else if (temp == 's' || temp == 'S') {
        return DOWN;
    }
    else if (temp == ' ') {
        return SUBMIT;
    }
    else if (temp == 'q' || temp == 'Q') {
        return QUIT;
    }


}

void gotoxy(int x, int y) {

    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

int keycontrol() { //방향키, submit 
    char temp = _getch();
    if (temp == 'w' || temp == 'W') {
        return UP;
    }
    else if (temp == 's' || temp == 'S') {
        return DOWN;
    }
    else if (temp == ' ') {
        return SUBMIT;
    }
    else if (temp == 'q' || temp == 'Q') {
        return QUIT;
    }
}

void how() {
    system("cls");
    printf("\n\n");
    printf("<게임 방법>\n\n");
    printf("설명1");
    printf("설명2");
    while (1) {
        if (keyControl() == QUIT) {
            break;
        }
    }
}


void titleDraw() {

    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 | FOREGROUND_INTENSITY); //색상 넣기 (노란색)
    printf("              ×××××××××××              \n          ");

    printf("        HANGMAN GAME                    \n          ");
    printf("    ×××××××××××              \n          ");
    printf("    ×××××××××××              \n          ");
}


