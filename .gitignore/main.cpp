#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;
HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursor;

int score;

bool set_number(int a[][4])
{
    bool flag = false;
    int c=0;
    for(int j=0; j<4; j++)
    {
        for(int i=0; i<4; i++)
        {
            if(a[j][i]==0) c++;
        }
    }
    if(c!=0)
    {
        int x, y;
        do{
            x = rand()%4;
            y = rand()%4;
        }while(a[y][x]!=0);

        if(rand()%100>90)
        {
            a[y][x]=4;
        }
        else
        {
            a[y][x] = 2;
        }
    }
    else
    {
        flag = true;
    }
    return flag;
}
void print(int a[][4])
{
    for(int j=0; j<4; j++)
    {
        for(int i=0; i<4; i++)
        {
            cursor.X = i * 4;
            cursor.Y = j*2;
            SetConsoleCursorPosition(output,cursor);
            cout << (a[j][i] & 0x7fff) << "   ";
        }
    }
    cursor.X = 40;
    cursor.Y = 5;
    SetConsoleCursorPosition(output,cursor);
    cout << "SCORE = " << score << "   ";
}
void reset(int a[][4])
{
        for(int j=0; j<4; j++)
        {
            for(int i=0; i<4; i++)
            {
                a[j][i] = a[j][i] & 0x7fff;
            }
        }

}
void up(int a[][4])
{
    bool flag;
    do{
        flag = false;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(a[j][i] == a[j + 1][i] && a[j][i]>0 && a[j][i]<0x8000)
                {
                    a[j][i] = a[j][i] + a[j + 1][i];
                    score +=  a[j][i];
                    a[j][i] = a[j][i] | 0x8000;
                    a[j + 1][i] = 0;
                    flag = true;
                }
                if(a[j][i] == 0 && a[j + 1][i] !=0)
                {
                    a[j][i] = a[j + 1][i];
                    a[j + 1][i] = 0;
                    flag = true;
                }
            }
        }
        print(a);
        Sleep(100);
    }while(flag == true);
    reset(a);
}

void down(int a[][4])
{
    bool flag;
    do{
        flag = false;
        for(int i=0; i<4; i++)
        {
            for(int j=3; j>=1; j--)
            {
                if(a[j][i] == a[j - 1][i] && a[j][i]>0 && a[j][i]<0x8000)
                {
                    a[j][i] = a[j][i] + a[j - 1][i];
                    score +=  a[j][i];
                    a[j][i] = a[j][i] | 0x8000;
                    a[j - 1][i] = 0;
                    flag = true;
                }
                if(a[j][i] == 0 && a[j - 1][i] !=0)
                {
                    a[j][i] = a[j - 1][i];
                    a[j - 1][i] = 0;
                    flag = true;
                }
            }
        }
        print(a);
        Sleep(100);
    }while(flag == true);
    reset(a);
}

void left(int a[][4])
{
    bool flag;
    do{
        flag = false;
        for(int j=0; j<4; j++)
        {
            for(int i=0; i<3; i++)
            {
                if(a[j][i] == a[j][i+1] && a[j][i]>0 && a[j][i]<0x8000)
                {
                    a[j][i] = a[j][i] + a[j][i + 1];
                    score +=  a[j][i];
                    a[j][i] = a[j][i] | 0x8000;
                    a[j][i + 1] = 0;
                    flag = true;
                }
                if(a[j][i] == 0 && a[j][i + 1] !=0)
                {
                    a[j][i] = a[j][i + 1];
                    a[j][i + 1] = 0;
                    flag = true;
                }
            }
        }
        print(a);
        Sleep(100);
    }while(flag == true);
    reset(a);
}

void right(int a[][4])
{
    bool flag;
    do{
        flag = false;
        for(int j=0; j<4; j++)
        {
            for(int i=3; i>=1; i--)
            {
                if(a[j][i] == a[j][i-1] && a[j][i]>0 && a[j][i]<0x8000)
                {
                    a[j][i] = a[j][i] + a[j][i - 1];
                    score +=  a[j][i];
                    a[j][i] = a[j][i] | 0x8000;
                    a[j][i - 1] = 0;
                    flag = true;

                }
                if(a[j][i] == 0 && a[j][i - 1] !=0)
                {
                    a[j][i] = a[j][i - 1];
                    a[j][i - 1] = 0;
                    flag = true;
                }
            }
        }
        Sleep(100);
        print(a);

    }while(flag == true);
    reset(a);
}

int main()
{
    int i_input;
    int a[4][4] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    bool game_over = false;
    score = 0;
    //set_number(a);
   game_over =  set_number(a);

    print(a);
    while((i_input = getch())!=27 || game_over != true)
    {
        switch (i_input)
        {
            case 75:
                {
                    left(a);
                    break;
                }
            case 80:
                {
                    down(a);
                    break;
                }
            case 77:
                {
                    right(a);

                    break;

                }
            case 72:
                {
                    up(a);
                    break;
                }

        }
        if(i_input == 72 || i_input == 77 || i_input == 80 || i_input == 75)
        {
            game_over == set_number(a);
        }

         print(a);

    }
    return 0;
}

