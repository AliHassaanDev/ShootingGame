#include <iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;

char maze[32][82];
int bulletX[200];
int bulletY[200];
bool isBulletActive[200];
int bulletCount=0;
bool isEnemy1Active = true;
bool isEnemy2Active = true;
bool isEnemy3Active = true;
bool isEnemy4Active = true;
bool isEnemy5Active = true;
int pX=1,pY=13;
int e1X=73,e1Y=2;
int e2X=73,e2Y=8;
int e3X=73,e3Y=14;
int e4X=73,e4Y=20;
int e5X=73,e5Y=26;
int score=0;
int health=03;
int timer=000;
int sleep=000;
char levelOption= '1';
char menuOption , isHome ,islevel;
void homePage()
{
    do{
        system("cls");
        cout<<" ___________________________________________________________ "<<endl;
        cout<<"|          $$$$$$$$$$    $$     $$$   $$  $$   $$           |"<<endl;
        cout<<"|          $$  $$  $$  $$  $$   $$$$  $$  $$ $$             |"<<endl;
        cout<<"|              $$     $$$$$$$$  $$ $$ $$  $$$$              |"<<endl;
        cout<<"|              $$     $$    $$  $$  $$$$  $$ $$             |"<<endl;
        cout<<"|             $$$$    $$    $$  $$   $$$  $$   $$           |"<<endl;
        cout<<"|                                                           |"<<endl;
        cout<<"|  $$$$  $$   $$  $$$$   $$$$  $$$$$$$$ $$ $$$   $$  $$$$$  |"<<endl;
        cout<<"| $$   $ $$   $$ $$  $$ $$  $$    $$    $$ $$$$  $$ $$   $$ |"<<endl;
        cout<<"|   $$   $$$$$$$ $$  $$ $$  $$    $$    $$ $$ $$ $$ $$      |"<<endl;
        cout<<"| $   $$ $$   $$ $$  $$ $$  $$    $$    $$ $$  $$$$ $$ $$$$ |"<<endl;
        cout<<"|  $$$$  $$   $$  $$$$   $$$$     $$    $$ $$   $$$  $$$$$  |"<<endl;
        cout<<"|___________________________________________________________|"<<endl;
        cout<<"                   Option 1: Play"<<endl;
        cout<<"                   Option 2: Level"<<endl;
        cout<<"                   Option 3: Instructions"<<endl;
        cout<<"                   Option 4: Exit"<<endl;
        cout<<"                   Enter your Option: ";
        cin>>menuOption;
    }while(menuOption!= '1' && menuOption!= '2' && menuOption!= '3'&& menuOption!= '4' );
}
void levels()
{
    do{
    system("cls");
    cout<<" ------------------------------ "<<endl;
    cout<<"|            LEVELS            |"<<endl;
    cout<<" ------------------------------ "<<endl;
    cout<<"Option 1: Easy"<<endl;
    cout<<"Option 2: Medium"<<endl;
    cout<<"Option 3: Hard"<<endl;
    cout<<"Enter your Option: ";
    cin>>levelOption;
    cout<<"Enter 1 to go back: ";
    cin>>islevel;
    }while((levelOption!= '1' && levelOption!= '2' && levelOption!= '3' ) || islevel !='1' );
}
void levelSleep()
{
    if(levelOption== '1')
    {
        sleep=50;
    }
    if(levelOption== '2')
    {
        sleep=20;
    }
    if(levelOption== '3')
    {
        sleep=5;
    }
}
void instructions()
{
    do{
        system("cls");
        cout<<" ----------------------------------- "<<endl;
        cout<<"|            INSTRUCTIONS           |"<<endl;
        cout<<" ----------------------------------- "<<endl<<endl;
        cout<<"KEYS"<<endl;
        cout<<"1. Right Key = To move player right."<<endl;
        cout<<"2. Left Key = To move player left."<<endl;
        cout<<"3. Up Key = To move player up."<<endl;
        cout<<"4. Down Key = To move player down."<<endl;
        cout<<"5. Space Key = To shoot the bullets."<<endl<<endl;
        cout<<"SCORE"<<endl;
        cout<<"Score = Number of enemies killed."<<endl<<endl;
        cout<<"HEALTH"<<endl;
        cout<<"Health = Number of lifes of player."<<endl;
        cout<<"Health Decreases by 1 when enemy touch touches the player."<<endl;
        cout<<"Health Increase by 1 when player touches the $ ."<<endl<<endl;
        cout<<"GAME OVER"<<endl;
        cout<<"1. When enemy reaches left wall of maze."<<endl;
        cout<<"2. When health becomes zero."<<endl<<endl;
        cout<<"WIN CONDITIONS"<<endl;
        cout<<"1. At Easy level when score becomes 50."<<endl;
        cout<<"2. At Medium level when score becomes 100."<<endl;
        cout<<"3. At Hard level when score becomes 150."<<endl<<endl;
        cout<<"Enter 1 to go back: ";
        cin>>isHome;
    }while(isHome != '1');
}
void printMaze()
{
    int length=82;
    int height=32;
    int x=0, y=0;
    for(int i=0;i<length;i++)
    {
        maze[y][x]={'#'};
        x++;
    }
    for(int j=0; j<height-2;j++)
    {
        x=0, y++;
        maze[y][x]={'$'};
        x=1;
        for(int i=0;i<length-2;i++)
        {
            maze[y][x]={' '};
            x++;
        }
        x=81; 
        maze[y][x]={'#'}; 
    }
    x=0;y=31;
    for(int i=0;i<82;i++)
    {
        maze[y][x]={'#'};
        x++;
    }
    
    for(int i=0;i<32;i++)
    {
        for(int j=0; j<82;j++)
        {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
    maze[5][5]='$';
}
void gotoxy(int x,int y)
{
    COORD coordinates;
    coordinates.X= x;
    coordinates.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x,short int y)
{
   CHAR_INFO ci;
   COORD xy= {0,0};
   SMALL_RECT rect={x,y,x,y};
   COORD coordBufSize;
   coordBufSize.X=1;
   coordBufSize.Y=1;
   return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),&ci,coordBufSize,xy,&rect) ? ci.Char.AsciiChar: ' ';
}
void printPlayer()
{
    gotoxy(pX,pY);
    cout<<"      __            "<<endl;
    gotoxy(pX,pY+1);
    cout<<"     [||]-          "<<endl;
    gotoxy(pX,pY+2);
    cout<<"  -||||||||\\======o"<<endl;
    gotoxy(pX,pY+3);
    cout<<"[|||||||||||||]     "<<endl;
    gotoxy(pX,pY+4);
    cout<<" \\00000000000/     "<<endl;
    gotoxy(0,35);
}
void erasePlayer()
{
    gotoxy(pX,pY);
    cout<<"                    "<<endl;
    gotoxy(pX,pY+1);
    cout<<"                    "<<endl;
    gotoxy(pX,pY+2);
    cout<<"                    "<<endl;
    gotoxy(pX,pY+3);
    cout<<"                    "<<endl;
    gotoxy(pX,pY+4);
    cout<<"                    "<<endl;
    gotoxy(0,35);
}
void movePlayerUp()
{
    if(getCharAtxy(pX,pY-1)==' ')
    {
        erasePlayer();
        pY=pY-1;
        printPlayer();
    }
}
void movePlayerDown()
{
    if(getCharAtxy(pX,pY-26)==' ')
    {
    erasePlayer();
    pY=pY+1;
    printPlayer();
    }
}
void movePlayerLeft()
{
    if(getCharAtxy(pX-1,pY)==' ')
    {
    erasePlayer();
    pX=pX-1;
    printPlayer();
    }
    
}
void movePlayerRight()
{
    if(getCharAtxy(pX+20,pY)==' ')
    {
    erasePlayer();
    pX=pX+1;
    printPlayer();
    }
    
}
void printEnemy(int& eX,int& eY)
{
    gotoxy(eX,eY);
    cout<<" (0,0) "<<endl;
    gotoxy(eX,eY+1);
    cout<<" __v   "<<endl;
    gotoxy(eX,eY+2);
    cout<<"/ /|   "<<endl;
    gotoxy(eX,eY+3);
    cout<<"  /\\  "<<endl;
    gotoxy(eX,eY+4);
    cout<<" / |   "<<endl;
    gotoxy(0,35);
}
void eraseEnemy(int& eX,int& eY)
{
    gotoxy(eX,eY);
    cout<<"       "<<endl;
    gotoxy(eX,eY+1);
    cout<<"       "<<endl;
    gotoxy(eX,eY+2);
    cout<<"       "<<endl;
    gotoxy(eX,eY+3);
    cout<<"       "<<endl;
    gotoxy(eX,eY+4);
    cout<<"       "<<endl;
    gotoxy(0,35);
}
void moveEnemy(int& eX,int& eY)
{
    eraseEnemy(eX,eY);
    eX=eX-1;
    printEnemy(eX,eY);
}
void moveEnemyDiDown(int& eX,int& eY)
{
    eraseEnemy(eX,eY);
    eX=eX-1;
    if(getCharAtxy(eX,eY+5)!='#')
    {
        eY=eY+1;
    }
    printEnemy(eX,eY);
}
void moveEnemyDiUp(int& eX,int& eY)
{
    eraseEnemy(eX,eY);
    eX=eX-1;
    if(getCharAtxy(eX,eY-2)!='#')
    {
        eY=eY-1;
    }
    printEnemy(eX,eY);
                  
}
void makeEnemyInactive(int eX, int eY)
{
    if((getCharAtxy(eX-1,eY) != ' ' && getCharAtxy(eX-1,eY) != '*') ||(getCharAtxy(eX-1,eY+1) != ' ' &&  getCharAtxy(eX-1,eY+1) != '*' ) || (getCharAtxy(eX-1,eY+2) != ' ' && getCharAtxy(eX-1,eY+2) != '*' ) 
    || (getCharAtxy(eX-1,eY+3) != ' ' && getCharAtxy(eX-1,eY+3) != '*') || (getCharAtxy(eX-1,eY+4) != ' ' && getCharAtxy(eX-1,eY+4) != '*' ))
    {
        if(eY==26 )
        {
           isEnemy1Active= false; 
           score+=2;
        }
        if(eY== 8)
        {
            isEnemy2Active= false;
            score+=2;
        }
         if(eY== 14)
        {
            isEnemy3Active= false;
            score+=2;
        }
        if(eY== 20)
        {
           isEnemy4Active= false;
           score+=2; 
        }
        if(eY== 2)
        {
            isEnemy5Active= false;
            score+=2;
        }
        eraseEnemy(eX,eY);
        gotoxy(eX+4,eY+2);
        cout<<"*";
    } 
}
void healthIncrease()
{
    if(getCharAtxy(pX-1,pY)=='*' || getCharAtxy(pX-1,pY+1)=='*' || getCharAtxy(pX-1,pY+2)=='*' ||getCharAtxy(pX-1,pY+3)=='*' ||getCharAtxy(pX-1,pY+4)=='*' )
    {
        health++;
    }
    if(getCharAtxy(pX+21,pY)=='*' || getCharAtxy(pX+21,pY+1)=='*' || getCharAtxy(pX+21,pY+2)=='*' ||getCharAtxy(pX+21,pY+3)=='*' ||getCharAtxy(pX+21,pY+4)=='*' )
    {
        health++;
    }
    if(getCharAtxy(pX,pY-1)=='*' ||getCharAtxy(pX+1,pY-1)=='*' ||getCharAtxy(pX+2,pY-1)=='*' ||getCharAtxy(pX+3,pY-1)=='*' ||getCharAtxy(pX+4,pY-1)=='*' ||getCharAtxy(pX+5,pY-1)=='*' ||getCharAtxy(pX+6,pY-1)=='*' ||getCharAtxy(pX+7,pY-1)=='*' ||getCharAtxy(pX+8,pY-1)=='*' ||getCharAtxy(pX+9,pY-1)=='*' ||
    getCharAtxy(pX+10,pY-1)=='*' ||getCharAtxy(pX+11,pY-1)=='*' ||getCharAtxy(pX+12,pY-1)=='*' ||getCharAtxy(pX+13,pY-1)=='*' ||getCharAtxy(pX+14,pY-1)=='*' ||getCharAtxy(pX+15,pY-1)=='*' ||getCharAtxy(pX+16,pY-1)=='*' ||getCharAtxy(pX+17,pY-1)=='*' ||getCharAtxy(pX+18,pY-1)=='*' ||getCharAtxy(pX+19,pY-1)=='*')
    {
        health++;
    }
    if(getCharAtxy(pX,pY+5)=='*' ||getCharAtxy(pX+1,pY+5)=='*' ||getCharAtxy(pX+2,pY+5)=='*' ||getCharAtxy(pX+3,pY+5)=='*' ||getCharAtxy(pX+4,pY+5)=='*' ||getCharAtxy(pX+5,pY+5)=='*' ||getCharAtxy(pX+6,pY+5)=='*' ||getCharAtxy(pX+7,pY+5)=='*' ||getCharAtxy(pX+8,pY+5)=='*' ||getCharAtxy(pX+9,pY+5)=='*' ||
    getCharAtxy(pX+10,pY+5)=='*' ||getCharAtxy(pX+11,pY+5)=='*' ||getCharAtxy(pX+12,pY+5)=='*' ||getCharAtxy(pX+13,pY+5)=='*' ||getCharAtxy(pX+14,pY+5)=='*' ||getCharAtxy(pX+15,pY+5)=='*' ||getCharAtxy(pX+16,pY+5)=='*' ||getCharAtxy(pX+17,pY+5)=='*' ||getCharAtxy(pX+18,pY+5)=='*' ||getCharAtxy(pX+19,pY+5)=='*')
    {
        health++;
    }
}
void healthDecrease()
{
    if(getCharAtxy(pX+24 ,pY)== ',' || getCharAtxy(pX+24,pY)== 'v' || getCharAtxy(pX+24,pY)== '|'|| getCharAtxy(pX+24,pY)== '\\')
    {
        health--;
    }
    else if(getCharAtxy(pX+24,pY+1)== ',' || getCharAtxy(pX+24,pY+1)== 'v' || getCharAtxy(pX+24,pY+1)== '|' || getCharAtxy(pX+24,pY+1)== '\\')
    {
        health--;
    }
    else if(getCharAtxy(pX+24,pY)+2== ',' || getCharAtxy(pX+24,pY+2)== 'v' || getCharAtxy(pX+24,pY+2)== '|' || getCharAtxy(pX+24,pY+2)== '\\')
    {
        health--;
    }
    else if(getCharAtxy(pX+24,pY+3)== ',' || getCharAtxy(pX+24,pY+3)== 'v' || getCharAtxy(pX+24,pY+3)== '|' || getCharAtxy(pX+24,pY+3)== '\\')
    {
        health--;
    }
    else if(getCharAtxy(pX+24,pY+4)== ',' || getCharAtxy(pX+24,pY+4)== 'v' || getCharAtxy(pX+24,pY+4)== '|' || getCharAtxy(pX+24,pY+4)== '\\')
    {
        health--;
    }
}
void printHealth()
{
    gotoxy(0,34);
    cout<<"Health: "<<health;
}
void printBullet(int x, int y)
{
    gotoxy(x,y);
    cout<<"o";
}
void eraseBullet(int x, int y)
{
    gotoxy(x,y);
    cout<<" ";
}
void makeBulletInactive(int idx)
{
    isBulletActive[idx]= false;            
}
void generateBullet()
{
    bulletX[bulletCount]=pX+19;
    bulletY[bulletCount]=pY+2;
    isBulletActive[bulletCount]= true;
    gotoxy(pX+19,pY+2);
    cout<<"o";
    bulletCount++;
}
void playerShooting()
{
    for(int x=0;x<bulletCount;x++)
    {
        if(isBulletActive[x]== true)
        {
            char next=getCharAtxy(bulletX[x]+1,bulletY[x]);
            if(next !=' ')
            {
                eraseBullet(bulletX[x],bulletY[x]);
                makeBulletInactive(x);
            }
            else
            {
                eraseBullet(bulletX[x],bulletY[x]);
                bulletX[x]=bulletX[x]+1;
                printBullet(bulletX[x],bulletY[x]);
            }
        }
    }    
}
void printScore()
{
    if(levelOption =='1')
    {
      gotoxy(0,32);
      cout<<"Target Score: 50"<<endl;  
    }
    if(levelOption =='2')
    {
      gotoxy(0,32);
      cout<<"Target Score: 100"<<endl;  
    }
    if(levelOption =='3')
    {
      gotoxy(0,32);
      cout<<"Target Score: 150"<<endl;  
    }
    gotoxy(0,33);
    cout<<"Score: "<<score;
}
void lost()
{
    if(health==0 || e1X==1 || e2X==1 || e3X==1|| e4X==1 || e5X==1)
    {
        gotoxy(10,14);
        cout<<" ####   ###  ##   ## #####   ###  ##   ## ##### ####  "<<endl;
        gotoxy(10,15);
        cout<<"##     ## ## ### ### ##__   ## ## ##   ## ##__  ## ## "<<endl;
        gotoxy(10,16);
        cout<<"## ### ##### ## # ## ##     ## ##  ## ##  ##    ####  "<<endl;
        gotoxy(10,17);
        cout<<" ####  ## ## ##   ## #####   ###    ###   ##### ## ## "<<endl;
        gotoxy(10,34);
    }
}
void win()
{
    if((score==50 && levelOption=='1') || (score==100 && levelOption=='2') || (score==150 && levelOption=='3'))
    {
        gotoxy(15,14);
        cout<<"##   ##  ###  ##  ##   ##   ##  ###  ###  ##"<<endl;
        gotoxy(15,15);
        cout<<" ## ##  ## ## ##  ##   ## # ## ## ## #### ##"<<endl;
        gotoxy(15,16);
        cout<<"  ##    ## ## ##  ##   ### ### ## ## ## ####"<<endl;
        gotoxy(15,17);
        cout<<"  ##     ###   ####    ##   ##  ###  ##  ###"<<endl;
        gotoxy(0,34);
        getch();
    }
}

int main()
{
    home:
    system("cls");
    homePage();
    getchar();
    if(menuOption == '2')
    {
        system("cls");
        levels();
        if(islevel == '1')
        {
            goto home;
        }
    }
    if(menuOption == '3')
    {
        system("cls");
        instructions();
        if(isHome == '1')
        {
            goto home;
        }
    }
    if(menuOption == '4' )
    {
        system("cls");
        return 0;
    }
    if(menuOption == '1')
    {
        system("cls");
        printMaze();
        printPlayer(); 
        levelSleep();      
        while(true)
        {
            if (GetAsyncKeyState(VK_UP))
            {
                movePlayerUp();
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                movePlayerDown();
            }
            if (GetAsyncKeyState(VK_LEFT))
            {
                movePlayerLeft();
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                movePlayerRight();
            }
            if (GetAsyncKeyState(VK_SPACE))
            {
                generateBullet();
            }
            playerShooting();
            printScore(); 
            healthIncrease();
            healthDecrease();
            printHealth();
            if(isEnemy1Active== true && timer >=292 )
            {
                printEnemy(e1X,e1Y);
                moveEnemyDiDown(e1X,e1Y);
                makeEnemyInactive(e1X, e1Y);
            }
            if(isEnemy2Active== true && timer>=5)
            {
                printEnemy(e2X,e2Y);
                moveEnemy(e2X,e2Y);
                makeEnemyInactive(e2X, e2Y);
            }
            if(isEnemy3Active== true && timer>=219)
            {
                printEnemy(e3X,e3Y);
                moveEnemy(e3X,e3Y);
                makeEnemyInactive(e3X, e3Y);
            }
            if(isEnemy4Active== true && timer >=73)
            {
                printEnemy(e4X,e4Y);
                moveEnemy(e4X,e4Y);
                makeEnemyInactive(e4X, e4Y);
            }
            if(isEnemy5Active== true && timer >=146)
            {
                printEnemy(e5X,e5Y);
                moveEnemyDiUp(e5X,e5Y);
                makeEnemyInactive(e5X, e5Y);
            }
            Sleep(sleep);
            if(health==0 || e1X==1 || e2X==1 || e3X==1 || e4X==1 || e5X==1 )
            {
                break;
            }
            if((score==50 && levelOption=='1') || (score==100 && levelOption=='2') || (score==150 && levelOption=='3') )
            {
                break;
            }
            timer++;
            if( timer == 365) 
            {
                timer=0;
                isEnemy1Active= true;
                e1X=73,e1Y=2;
                isEnemy2Active= true;
                e2X=73,e2Y=8;
                isEnemy3Active= true;
                e3X=73,e3Y=14;
                isEnemy4Active= true;
                e4X=73,e4Y=20;
                isEnemy5Active= true;
                e5X=73,e5Y=26;
            }
        }
        lost();
        win();
    }  
}