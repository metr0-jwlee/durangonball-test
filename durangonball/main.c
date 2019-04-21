#include <stdio.h>
#include <stdlib.h>
#define c 0
#define a 1
#define b 2

int arr[50][2] = {{}};
int old_arr[50][2] = {{}};
int hp, mp = 0, you_hp, you_mp = 0;
int status = 0;
int you_status = 0;
int turn = 0;
int old_score = 0;
int score = 0;
int game_round = 1;

void firstRun(void);
void scoreCheck(void);
void arrCompare(void);
void reinforcement(void);
int dataSave(void);

int main()
{
    firstRun();
    scoreCheck();
    printf("점수 : %d \n", old_score);
    for(int i = 0; i < 50; i++)
        printf("[%d, %d]", old_arr[i][0], old_arr[i][1]);
    reinforcement();
    printf("점수 : %d \n", old_score);
    for(int i = 0; i < 50; i++)
        printf("[%d, %d]", old_arr[i][0], old_arr[i][1]);
    arrCompare();
    printf("점수 : %d \n", old_score);
    for(int i = 0; i < 50; i++)
        printf("[%d, %d]", old_arr[i][0], old_arr[i][1]);
}
void firstRun(void)
{
    hp = 25, you_hp = 25;
    mp = 0, you_mp = 0;
    while (0 < hp && 0 < you_hp && turn <= 50) {
        printf("당신의 status, 적의 status 입력: ");
        scanf("%d %d", &you_status, &status);
        
        if (status == 0) {
            if (you_status == 0) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                mp++;
                you_mp++;
            } else if (you_status == 1) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                hp = hp - (1 + you_mp);
                mp = 0;
                if(you_mp > 0)
                    you_mp--;
            } else if(you_status == 2) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                mp++;
            }
            turn++;
        }
        
        else if (status == 1) {
            if (you_status == 0) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                you_mp = 0;
                you_hp = you_hp - (1 + mp);
                if(mp > 0)
                    mp--;
            } else if (you_status == 1) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                hp = hp - (1 + you_mp);
                you_hp = you_hp - (1 + mp);
                mp = 0;
                you_mp = 0;
            } else if(you_status == 2) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                you_mp++;
                you_hp = you_hp - mp;
                if(mp > 0)
                    mp--;
            }
            turn++;
        }
        
        else if (status == 2) {
            if (you_status == 0) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                you_mp++;
            } else if (you_status == 1) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                mp++;
                hp = hp - you_mp;
                if(you_mp > 0)
                    mp--;
            } else if(you_status == 2) {
                arr[turn][0] = you_status;
                arr[turn][1] = status;
                //공란
            }
            turn++;
        }
    }
}

void scoreCheck()
{
    if(hp <= 0 && you_hp > 0)
        score = score + 3;
    
    else if(hp > 0 && you_hp <= 0)
        score = score;
    
    else if(hp <= 0 && you_hp <= 0)
        score = score + 1;
    game_round++;
}

void arrCompare()
{
    if(score > old_score)
    {
        old_score = score;
        for(int i = 0; i < 50; i++)
        {
            old_arr[i][0] = arr[i][0];
            old_arr[i][1] = arr[i][1];
        }
    }
}

void reinforcement()
{
    hp = 25, you_hp = 25;
    mp = 0, you_mp = 0;
    
    if(game_round == 100)
    {
        arrCompare();
        printf("점수 : %d \n", old_score);
        for(int i = 0; i < 50; i++)
            printf("[%d, %d]", old_arr[i][0], old_arr[i][1]);
    }
    
    while (0 < hp && 0 < you_hp) {
        for (int i = 0; i < 50; i++) {
            status = old_arr[i][1];
            you_status = rand() % 3;
            
            if (turn == 50)
                scoreCheck();
            
            else if (status == 0) {
                if (you_status == 0) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    mp++;
                    you_mp++;
                } else if (you_status == 1) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    hp = hp - (1 + you_mp);
                    mp = 0;
                    if (you_mp > 0)
                        you_mp--;
                } else if (you_status == 2) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    mp++;
                }
                turn++;
            } else if (status == 1) {
                if (you_status == 0) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    you_mp = 0;
                    you_hp = you_hp - (1 + mp);
                    if (mp > 0)
                        mp--;
                } else if (you_status == 1) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    hp = hp - (1 + you_mp);
                    you_hp = you_hp - (1 + mp);
                    mp = 0;
                    you_mp = 0;
                } else if (you_status == 2) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    you_mp++;
                    you_hp = you_hp - mp;
                    if (mp > 0)
                        mp--;
                }
                turn++;
            } else if (status == 2) {
                if (you_status == 0) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    you_mp++;
                } else if (you_status == 1) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    mp++;
                    hp = hp - you_mp;
                    if (you_mp > 0)
                        mp--;
                } else if (you_status == 2) {
                    arr[turn][0] = you_status;
                    arr[turn][1] = status;
                    //공란
                }
                turn++;
            }
        }
    }
}
