#ifndef TASK3_H_INCLUDED
#define TASK3_H_INCLUDED

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>

int mainFuntion3(char Plaintext[8],char Secret_key[8],int changeSum)
{
    srand(time(NULL));
    int SecretariesChangeCount = 0;//密文改变的位数
    int output[64] = { 0 }; //密文

//将明文,秘钥变为二进制
int PlaintextBits[64] = {0};
int Secret_keyBits[64] = {0};
CharToBit(Plaintext, PlaintextBits, 8);
CharToBit(Secret_key, Secret_keyBits, 8);

DES_Efun(PlaintextBits, Secret_keyBits, output); //获取密文


int tempSecret_keyBits[64] = {0};
int tempOutput[64] = {0};

    for(int i=0;i<10;i++){//随机获取秘钥改变的位置，改变秘钥10次，计算密文位数改变平均值
     int randNum =  rand()%64;
     for(int i=0;i<64;i++){tempSecret_keyBits[i] = Secret_keyBits[i];}//对秘钥bits重新赋值
     for(int j=0;j<changeSum;j++){//对秘钥的changeSum位进行改变
        if(tempSecret_keyBits[(randNum+j)%64]==0)
            tempSecret_keyBits[(randNum+j)%64] = 1;
        else tempSecret_keyBits[(randNum+j)%64] = 0;
     }

     DES_Efun(PlaintextBits, tempSecret_keyBits, tempOutput);//获取秘钥改变后的密文

     for(int k=0;k<64;k++ ){//比较密文改变的位数
        if(tempOutput[k]!=output[k]) SecretariesChangeCount++;
     }
    }
    printf("*********************************\n");
    printf("经过10次随机改变秘钥 %d 位\n密文平均改变位数为：%.2f",changeSum,1.0*SecretariesChangeCount/10);
    printf("\n*********************************\n");
    return 0;
}



#endif // TASK3_H_INCLUDED
