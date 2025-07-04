/* App: Shooting Game
   Author: Me (-_-)	*/


#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

//defining symbolic constants for each letter of the alphabet
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//player and bullet position information
struct GAMEINFO {
    COORD PlayerOnePosition;			//coordinates of the first player
    COORD PlayerTwoPosition;			//coordinates of the second player
    COORD PlayerOneBullet;				//coordinates of the first player's bullet
    COORD PlayerTwoBullet;				//coordinates of the second player's bullet
    COORD PlayerOneBullet2;				//second bullet for first player
    COORD PlayerTwoBullet2;				//second bullet for second player
    COORD ZeroZero;						//placeholder coordinates as reference point
};

HANDLE hInput, hOutput;
GAMEINFO GameInfo;

//declaring prototypes of the functions
void Movement(GAMEINFO &GameInfo);
void Draw(GAMEINFO);
void Erase(GAMEINFO);
int LaunchBullet(GAMEINFO &GameInfo, int);
void LaunchBullet2(GAMEINFO &GameInfo, int);
int Wait();


int main()
{
    GAMEINFO GameInfo;
    
    
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
       
    
    SetConsoleMode(hOutput, ENABLE_PROCESSED_INPUT);
    
    //initialising the position coordinates of both players and bullets
	GameInfo.PlayerOnePosition.X = 19;
    GameInfo.PlayerOnePosition.Y = 12;
    GameInfo.PlayerTwoPosition.X = 61;
    GameInfo.PlayerTwoPosition.Y = 12;
    GameInfo.PlayerOneBullet.X = 0;
    GameInfo.PlayerOneBullet.Y = 0;
    GameInfo.PlayerTwoBullet.X = 79;
    GameInfo.PlayerTwoBullet.Y = 0;
    GameInfo.PlayerOneBullet2.X = 1;
    GameInfo.PlayerOneBullet2.Y = 0;
    GameInfo.PlayerTwoBullet2.X = 78;
    GameInfo.PlayerTwoBullet2.Y = 0;
    GameInfo.ZeroZero.X = 0;
    GameInfo.ZeroZero.Y = 0;

    //displaying a frame on the screen
	int i;
    GameInfo.ZeroZero.Y = 24;			//initialising the y coordinate of the placeholder coordinate
    for(i = 0; i < 79; i++)
	{
        SetConsoleCursorPosition(hOutput, GameInfo.ZeroZero);
        cout << ".";
        GameInfo.ZeroZero.X++;			//incrementing the x coordinate of the placeholder coordinate
    }
	
	//displaying controls for each player
	cout << "\n\nControls:\nPlayer 01:\t\t\tPlayer 02:\nQ: Up\t\t\t\tO:Up\nA: Down\t\t\t\tL: Down\nS: Shoot\t\t\tK: Shoot";
	
	//calling function to draw the players on the screen
    Draw(GameInfo);

    while(1)
	{
        //calling function to move players and bullets
		Movement(GameInfo);
    }
    
    return 0;
}

//function for handling player movement and bullet launching
void Movement(GAMEINFO &GameInfo)
{    
    INPUT_RECORD InputRecord;
    DWORD Events = 0;

    //taking input from the console
	ReadConsoleInput(hInput, &InputRecord, 1, &Events);
    
    //checking whether input event is a key event
	if(InputRecord.EventType == KEY_EVENT)
	{
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_Q && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            Erase(GameInfo);
            GameInfo.PlayerOnePosition.Y--;
            if(GameInfo.PlayerOnePosition.Y < 0)
                GameInfo.PlayerOnePosition.Y++;
            Draw(GameInfo);
        }
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_A && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            Erase(GameInfo);
            GameInfo.PlayerOnePosition.Y++;
            if(GameInfo.PlayerOnePosition.Y > 24)
                GameInfo.PlayerOnePosition.Y--;
            Draw(GameInfo);
        }

        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_S && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            LaunchBullet(GameInfo, 1);
        }
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_O && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            Erase(GameInfo);
            GameInfo.PlayerTwoPosition.Y--;
            if(GameInfo.PlayerTwoPosition.Y < 0)
                GameInfo.PlayerTwoPosition.Y++;
            Draw(GameInfo);
        }

        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_L && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            Erase(GameInfo);
            GameInfo.PlayerTwoPosition.Y++;
            if(GameInfo.PlayerTwoPosition.Y > 24)
                GameInfo.PlayerTwoPosition.Y--;
            Draw(GameInfo);
        }

        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_K && InputRecord.Event.KeyEvent.bKeyDown == 1)
		{
            LaunchBullet(GameInfo, 2);
        }

        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
            exit(0);

    }
    FlushConsoleInputBuffer(hInput);
}

//function for drawing player positions and bullets on the screen
void Draw(GAMEINFO GameInfo)
{
    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
    cout << "|";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
    cout << "|";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet);
    cout << ".";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet);
    cout << ".";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet2);
    cout << ".";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet2);
    cout << ".";
    
    GameInfo.ZeroZero.X = 0;
    GameInfo.ZeroZero.Y = 0;

    int i;
    for(i = 0; i < 79; i++){
        SetConsoleCursorPosition(hOutput, GameInfo.ZeroZero);
        cout << ".";
        GameInfo.ZeroZero.X++;
    }

}

//function for erasing player positions and bullets from the screen
void Erase(GAMEINFO GameInfo)
{
    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
    cout << " ";
    
    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
    cout << " ";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet);
    cout << " ";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet);
    cout << " ";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet2);
    cout << " ";

    SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet2);
    cout << " ";
}

//function for launching bullets and checking for collisions
int LaunchBullet(GAMEINFO &GameInfo, int PlayerNumber)
{    
    int i;
    if(PlayerNumber == 1){
        GameInfo.PlayerOneBullet.Y = GameInfo.PlayerOnePosition.Y;
        GameInfo.PlayerOneBullet.X = GameInfo.PlayerOnePosition.X + 1;
        Draw(GameInfo);
        Erase(GameInfo);
        for(i = 0; i < 77; i++){
            GameInfo.PlayerOneBullet.X += 1;
            Draw(GameInfo);
    
            int move;
            move =    Wait();
            switch(move){
            case 1:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y--;
                if(GameInfo.PlayerOnePosition.Y < 0)
                    GameInfo.PlayerOnePosition.Y++;
                break;
            case 2:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y++;
                if(GameInfo.PlayerOnePosition.Y > 24)
                    GameInfo.PlayerOnePosition.Y--;
                break;
            case 3:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y--;
                if(GameInfo.PlayerTwoPosition.Y < 0)
                    GameInfo.PlayerTwoPosition.Y++;
                break;
            case 4:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y++;
                if(GameInfo.PlayerTwoPosition.Y > 24)
                    GameInfo.PlayerTwoPosition.Y--;
                break;
            case 5:
                LaunchBullet2(GameInfo, 1);
                return 0;
                break;
            case 6:
                LaunchBullet2(GameInfo, 2);
                return 0;
                break;
            }

            Draw(GameInfo);
            Erase(GameInfo);
            if(GameInfo.PlayerOneBullet.X == GameInfo.PlayerTwoPosition.X)
                if(GameInfo.PlayerOneBullet.Y == GameInfo.PlayerTwoPosition.Y){
                    system("cls");
                    cout << "\aPlayer 1 Wins" << endl;
                    system("pause");
                    exit(0);
                }
        }
        GameInfo.PlayerOneBullet.Y = 0;
        GameInfo.PlayerOneBullet.X = 0;
        Draw(GameInfo);
    }
    if(PlayerNumber == 2){
        GameInfo.PlayerTwoBullet.Y = GameInfo.PlayerTwoPosition.Y;
        GameInfo.PlayerTwoBullet.X = GameInfo.PlayerTwoPosition.X - 1;
        Draw(GameInfo);
        Erase(GameInfo);
        for(i = 0; i < 77; i++){
            GameInfo.PlayerTwoBullet.X -= 1;
            Draw(GameInfo);
        
            int move;
            move =    Wait();
            switch(move){
            case 1:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y--;
                if(GameInfo.PlayerOnePosition.Y < 0)
                    GameInfo.PlayerOnePosition.Y++;
                break;
            case 2:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y++;
                if(GameInfo.PlayerOnePosition.Y > 24)
                    GameInfo.PlayerOnePosition.Y--;
                break;
            case 3:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y--;
                if(GameInfo.PlayerTwoPosition.Y < 0)
                    GameInfo.PlayerTwoPosition.Y++;
                break;
            case 4:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y++;
                if(GameInfo.PlayerTwoPosition.Y > 24)
                    GameInfo.PlayerTwoPosition.Y--;
                break;
            case 5:
                LaunchBullet2(GameInfo, 1);
                return 0;
                break;
            case 6:
                LaunchBullet2(GameInfo, 2);
                return 0;
                break;
            }
            
            Draw(GameInfo);
            Erase(GameInfo);
            if(GameInfo.PlayerTwoBullet.X == GameInfo.PlayerOnePosition.X)
                if(GameInfo.PlayerTwoBullet.Y == GameInfo.PlayerOnePosition.Y){
                    system("cls");
                    cout << "\aPlayer 2 Wins" << endl;
                    system("pause");
                    exit(0);
            }
        }
        GameInfo.PlayerTwoBullet.Y = 0;
        GameInfo.PlayerTwoBullet.X = 79;
        Draw(GameInfo);
    }
    return 0;
}

//function for waiting for input and returning corresponding move
int Wait()
{    
    INPUT_RECORD InputRecord;
    DWORD Events = 0;
    
    if(WAIT_TIMEOUT == WaitForSingleObject(hInput,1))
                return 0;
    ReadConsoleInput(hInput, &InputRecord, 1, &Events);

    if(InputRecord.EventType == KEY_EVENT){
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_Q && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 1;
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_A && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 2;
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_O && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 3;
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_L && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 4;
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_S && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 5;
        
        if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_K && InputRecord.Event.KeyEvent.bKeyDown == 1)
            return 6;
    }
    FlushConsoleInputBuffer(hInput);
    return 0;
}

//function for launching a second bullet
void LaunchBullet2(GAMEINFO &GameInfo, int PlayerNumber)
{
    if(PlayerNumber == 1){
        GameInfo.PlayerOneBullet2.X = GameInfo.PlayerOnePosition.X + 1;
        GameInfo.PlayerOneBullet2.Y = GameInfo.PlayerOnePosition.Y;

        Draw(GameInfo);
        Erase(GameInfo);
        int i;
        for(i = 0; i < 77; i++){
            GameInfo.PlayerOneBullet.X += 1;
            GameInfo.PlayerOneBullet2.X += 1;
            GameInfo.PlayerTwoBullet.X -= 1;
            GameInfo.PlayerTwoBullet2.X -= 1;
            Draw(GameInfo);
    
            int move;
            move =    Wait();
            switch(move){
            case 1:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y--;
                if(GameInfo.PlayerOnePosition.Y < 0)
                    GameInfo.PlayerOnePosition.Y++;
                break;
            case 2:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y++;
                if(GameInfo.PlayerOnePosition.Y > 24)
                    GameInfo.PlayerOnePosition.Y--;
                break;
            case 3:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y--;
                if(GameInfo.PlayerTwoPosition.Y < 0)
                    GameInfo.PlayerTwoPosition.Y++;
                break;
            case 4:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y++;
                if(GameInfo.PlayerTwoPosition.Y > 24)
                    GameInfo.PlayerTwoPosition.Y--;
                break;
            }

            Draw(GameInfo);
            Erase(GameInfo);
            if(GameInfo.PlayerOneBullet.X == GameInfo.PlayerTwoPosition.X)
                if(GameInfo.PlayerOneBullet.Y == GameInfo.PlayerTwoPosition.Y){
                    system("cls");
                    cout << "\aPlayer 1 Wins" << endl;
                    system("pause");
                    exit(0);
                }
            if(GameInfo.PlayerOneBullet2.X == GameInfo.PlayerTwoPosition.X)
                if(GameInfo.PlayerOneBullet2.Y == GameInfo.PlayerTwoPosition.Y){
                    system("cls");
                    cout << "\aPlayer 1 Wins" << endl;
                    system("pause");
                    exit(0);
                }
        }
        GameInfo.PlayerOneBullet.Y = 0;
        GameInfo.PlayerOneBullet.X = 0;
        GameInfo.PlayerOneBullet2.Y = 0;
        GameInfo.PlayerOneBullet2.X = 1;
        Draw(GameInfo);
    }

    if(PlayerNumber == 2){
        GameInfo.PlayerTwoBullet2.Y = GameInfo.PlayerTwoPosition.Y;
        GameInfo.PlayerTwoBullet2.X = GameInfo.PlayerTwoPosition.X - 1;
        Draw(GameInfo);
        Erase(GameInfo);
        int i;
        for(i = 0; i < 77; i++){
            GameInfo.PlayerTwoBullet.X -= 1;
            GameInfo.PlayerTwoBullet2.X -= 1;
            GameInfo.PlayerOneBullet.X += 1;
            GameInfo.PlayerOneBullet2.X += 1;
            Draw(GameInfo);
        
            int move;
            move =    Wait();
            switch(move){
            case 1:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y--;
                if(GameInfo.PlayerOnePosition.Y < 0)
                    GameInfo.PlayerOnePosition.Y++;
                break;
            case 2:
                Erase(GameInfo);
                GameInfo.PlayerOnePosition.Y++;
                if(GameInfo.PlayerOnePosition.Y > 24)
                    GameInfo.PlayerOnePosition.Y--;
                break;
            case 3:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y--;
                if(GameInfo.PlayerTwoPosition.Y < 0)
                    GameInfo.PlayerTwoPosition.Y++;
                break;
            case 4:
                Erase(GameInfo);
                GameInfo.PlayerTwoPosition.Y++;
                if(GameInfo.PlayerTwoPosition.Y > 24)
                    GameInfo.PlayerTwoPosition.Y--;
                break;
            }

            Draw(GameInfo);
            Erase(GameInfo);
            if(GameInfo.PlayerTwoBullet.X == GameInfo.PlayerOnePosition.X)
                if(GameInfo.PlayerTwoBullet.Y == GameInfo.PlayerOnePosition.Y){
                    system("cls");
                    cout << "\aPlayer 2 Wins" << endl;
                    system("pause");
                    exit(0);
            }
            if(GameInfo.PlayerTwoBullet2.X == GameInfo.PlayerOnePosition.X)
                if(GameInfo.PlayerTwoBullet2.Y == GameInfo.PlayerOnePosition.Y){
                    system("cls");
                    cout << "\aPlayer 2 Wins" << endl;
                    system("pause");
                    exit(0);
            }
        }
        GameInfo.PlayerOneBullet.Y = 0;
        GameInfo.PlayerOneBullet.X = 0;
        GameInfo.PlayerOneBullet2.Y = 0;
        GameInfo.PlayerOneBullet2.X = 1;
        Draw(GameInfo);
    }
}
