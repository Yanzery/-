#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"task1.h"
#include"task2.h"
#include"task3.h"

int main(){

    int chooseNum ;
    char Ptext[8];
    char Skey[8];
    int changeSum;

    printf(" \n\n\n\n\n\n\n                                                   \n");
	printf("                        ################################################################\n");
	printf("                        ##                                                            ##\n");
	printf("                        ##                          三个任务                          ##\n");
	printf("                        ##                                                            ##\n");
	printf("                        ##                                                            ##\n");
	printf("                        ##                                   ##\n");
	printf("                        ################################################################\n\n");
	printf(" 请按任何键以继续 ,, ");
	getchar();
	system("cls");

    printf("\n\n\n\n\n\n\n                                            请选择任务序号:\n");
	printf("                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("                               @                                       @\n");
	printf("                               @       **    1=任务1 差分分析   **     @\n");
	printf("                               @       **    2=任务2 改变明文   **     @\n");
	printf("                               @       **    3=任务3 改变秘钥   **     @\n");
	printf("                               @             4=退出                    @\n");
	printf("                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("                                           请输入您的选择：");
	scanf("%d", &chooseNum);
	getchar();

	   while (chooseNum != 4)
	{
		switch (chooseNum)
		{
			case 1:
             printf("请输入6位差分：");
             char intput[6];
             scanf("%s",intput);
             int intputchafen[6];
             for(int i=0;i<6;i++){
             if(intput[i]=='0')
             intputchafen[i] = 0;
             else intputchafen[i] = 1;
               }
             printf("\n");
             mainFuntion(intputchafen);
             system("PAUSE");
			break;

			case 2:
             printf("请输入8位字符作为明文：");
             scanf("%s",Ptext);
             printf("\n请输入8位字符作为秘钥：");
             scanf("%s",Skey);
             printf("\n请输入明文改变的位数：");
             scanf("%d",&changeSum);
             mainFuntion2(Ptext,Skey,changeSum);
             system("PAUSE");
			break;

			case 3:
             printf("请输入8位字符作为明文：");
             scanf("%s",Ptext);
             printf("\n请输入8位字符作为秘钥：");
             scanf("%s",Skey);
             printf("\n请输入秘钥改变的位数：");
             scanf("%d",&changeSum);
             mainFuntion3(Ptext,Skey,changeSum);
             system("PAUSE");
            break;
		}
    system("cls");
    printf("\n\n\n\n\n\n\n                                            请选择任务序号:\n");
	printf("                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("                               @                                       @\n");
	printf("                               @       **    1=任务1 差分分析   **     @\n");
	printf("                               @       **    2=任务2 改变明文   **     @\n");
	printf("                               @       **    3=任务3 改变秘钥   **     @\n");
	printf("                               @             4=退出                    @\n");
	printf("                               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("                                           请输入您的选择：");
	scanf("%d", &chooseNum);
	getchar();
	}

 return 0;
}
