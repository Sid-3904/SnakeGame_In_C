# include <stdio.h>
# include <windows.h>
# include <conio.h>
# include <stdlib.h>
# include <time.h>

# define Body 'O'
# define Wall '#'
# define Fruit '@'
# define Width 60
# define Height 25
# define Speed 3

void gotoxy(int X, int Y);
void move(int *n, int pos[*n][2], int *dir, int *p, int* fx, int *fy, int *sc);
int collisioncheck(int *n, int pos[*n][2], int *p, int* fx, int *fy);
void fruitput(int *fx, int *fy);

void main() {
    //initializing
    int len=5, i=0, dir=2, score=0;
    int *sc=&score;
    int *p=&i;
    int *pdr=&dir;
    int pos[len+50][2];
    for(int x=0; x<len; x++) {
        pos[x][0]=10+2*(Width/4);
        pos[x][1]=5+Height/2;
    }
    int *n=&len;
    //poster
    system("cls");
    gotoxy(10, 5);printf("  oo<                   ___      ___                  ___           \n");
    gotoxy(10, 6);printf(" o   |\\   |   /\\   | / |        /        /\\   |\\  /| |          \n");
    gotoxy(10, 7);printf("  o  | \\  |  /__\\  |/  |__      | __    /__\\  | \\/ | |__       \n");
    gotoxy(10, 8);printf("   o |  \\ | /    \\ |\\  |        |   |  /    \\ |    | |         \n");
    gotoxy(10, 9);printf("o  o |   \\|/      \\| \\ |___     \\___| /      \\|    | |___      \n");
    gotoxy(10, 10);printf(" oo                                                                   \n");
    Sleep(4000);
    //make bgd
    system("cls");
    gotoxy(10,5);
    for(int m=0; m<=Width/2; m++) {
        printf("%c ", Wall);
    }
    for(int m=0; m<Height; m++) {
        printf("\n          %c", Wall);
        for(int s=0; s<=2*(Width/2)-2; s++) printf(" ");
        printf("%c", Wall);
    }
    gotoxy(10,Height+5);
    for(int m=0; m<=Width/2; m++) {
        printf("%c ", Wall);
    }
    gotoxy(5+Width/2, Height+7);
    printf("SCORE: %d", *sc);
    Sleep(2000);
    //1st fruit
    int *fx, *fy;
    int fpos[2];
    fx=&fpos[0];
    fy=&fpos[1];
    fruitput(fx, fy);
    //game loop
    int k=1;
    while(1) { 
        //game over termination
        if(*pdr==0) {
            Sleep(1000);
            system("cls");
            gotoxy(20, 20);
            printf("GAME OVER! & SCORE: %d", *sc);
            Sleep(10000);
            return;
        }
        move(n, pos, pdr, p, fx, fy, sc);
        //controls
        if(kbhit()) {
            char a;
            a=getch();
            char buff;
            while(kbhit() == 1) buff=getch();
            switch(a) {
                case 'w' :
                    if(*pdr !=-1)
                    *pdr=1;
                    break;
                case 'd' :
                    if(*pdr !=-2)
                    *pdr=2;
                    break;
                case 'a' :
                    if(*pdr !=2)
                    *pdr=-2;
                    break;
                case 's' :
                    if(*pdr !=1)
                    *pdr=-1;
                    break;
                case 'x' : 
                    system("cls");
                    return;
            }
        }   
    }
}
void gotoxy(int X, int Y) {
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position={X, Y};
    SetConsoleCursorPosition(Screen, Position);
}
void move(int *n, int pos[*n][2], int *dir, int *p, int *fx, int *fy, int *sc) {
    int r, x=0;
    for(int f=0; f<*n; f++) {
        if(f == *p) {
            continue;
        }
        if((pos[*p][0]==pos[f][0]) && (pos[*p][1]==pos[f][1])) {
            x=1;
            break;       
        }   
    }
    if(x==0) {
        gotoxy(pos[*p][0]+1,pos[*p][1]);
        printf("\b ");
    }
    x=0;
    if(*p==0) r=*n-1;
    else r=*p-1;
    //turning
    if (*dir==2) {
        pos[*p][0]=pos[r][0]+2;
        pos[*p][1]=pos[r][1];      
    }
    if (*dir==1) {
        pos[*p][1]=pos[r][1]-1;
        pos[*p][0]=pos[r][0];
    }
    if (*dir==-2) {
        pos[*p][0]=pos[r][0]-2;
        pos[*p][1]=pos[r][1];      
    }
    if (*dir==-1) {
        pos[*p][1]=pos[r][1]+1;
        pos[*p][0]=pos[r][0];   
    }
    x=collisioncheck(n, pos, p, fx, fy);
    if(x==2) {
        (*sc)++;
        gotoxy(12+Width/2, Height+7);
        printf("%d", *sc);
        (*n)++;
        pos[*n][0]=pos[*p][0];
        pos[*n][1]=pos[*p][1];
        fruitput(fx, fy);
        for(int f=0; f<*n; f++) {
            if((*fx==pos[f][0]) && (*fy==pos[f][1])) {
                printf("\b%c", Body);
                fruitput(fx, fy);
                f=-1;
                continue;
            }
            break;   
        }
    }
    if(x==0 || x==2) {
        gotoxy(pos[*p][0],pos[*p][1]);
        printf("%c", Body);
    }
    if(*p == *n-1) *p=0;
    else *p=*p+1;
    if(x==1) *dir=0;
    Sleep(50*Speed);
}
int collisioncheck(int *n, int pos[*n][2], int *p, int *fx, int *fy) {
    if(pos[*p][0]>=Width+10 || pos[*p][0]<=10 || pos[*p][1]>=Height+5 || pos[*p][1]<=5) return 1;
    for(int f=0; f<*n; f++) {
        if(f == *p) {
            continue;
        }
        if((pos[*p][0]==pos[f][0]) && (pos[*p][1]==pos[f][1])) {
            return 1;       
        }   
    }
    if(pos[*p][0]==*fx && pos[*p][1]==*fy) {
        return 2;
    }
    return 0;
}
void fruitput(int *fx, int *fy) {
    time_t t;
    srand((unsigned) time(&t));
    do *fx=2*(rand() % ((Width+10)/2));
    while (*fx<=10);
    do *fy=rand() % (Height+5);
    while (*fy<=5);
    gotoxy(*fx, *fy);
    printf("%c", Fruit);
}