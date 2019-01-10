#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
void hello(){
printf("fsdf");
}

int mainFuntion(int in[6]) {
    int In[6];
    for(int i=0;i<6;i++){
        In[i]=in[i];
    }                                                //定义输入异或
    int k;
    int i;
    void Differ(int In[6]);                           //fp是指针，用来指向FILE类型的对象。

    void s_box(int array[6],int brray[4],int crray[4][16]);    //根据des把结果写成8个6比特串的并联，每一个s盒把6比特映射到4比特
                                                             //则array是输入比特串是6位 brray是输出比特串是4位，crray是s盒4X16

    printf("差分分布统计表\n");
    printf("\n输入差分: ");

        for(k=0;k<=5;k++) {                     //打印当前输入异或
            printf("%d",In[k]);
         }
         printf("\n");

         Differ(In);                       //调用差分方法

    return 0;
}



void Differ(int In[6])
{   //定义了s盒，《密码学原理与实践》P76页S1
    int s[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}
                ,{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}
                ,{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}
                ,{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                };
    int b[6]; //可能的输入
    int d[6];
    int e[4],f[4],Out[4],n[4];//n[4]是输出差分0000~1111；
    int flag;
    int l;
    int k;
    int i,j;
    int count;    //定义一个计数器
    void s_box(int array[6],int brray[4],int crray[4][16]);

    printf("————————————————————————————————————————————————————\n");
    printf("S1的输出差分\t可能的输入\n");


    for(i=0;i<=15;i++)
    {
        {
         int t;                  //遍历输出异或
         t=i;                    //四位二进制数0000~1111存在数组n中
         n[3]=t%2;  t=t/2;
         n[2]=t%2;  t=t/2;
         n[1]=t%2;  t=t/2;
         n[0]=t%2;
        }
        //printf("输出差分:");
        for(k=0;k<=3;k++)          //打印当前的输出异或
        {
            printf("%d",n[k]);
        }
        printf("\t\t");


        count=0;                   //将当前输出异或分布初始化为0次
        for(j=0;j<=63;j++)              //遍历输入六元组
        {

            {   int t;
                t=j;
                b[5]=t%2;  t=t/2;
                b[4]=t%2;  t=t/2;
                b[3]=t%2;  t=t/2;
                b[2]=t%2;  t=t/2;
                b[1]=t%2;  t=t/2;
                b[0]=t%2;
            }
            for(l=0;l<=5;l++)
               d[l]=b[l]^In[l];         //将数组进行按位异或操作，求出当前输入异或下x对应的x*，并保存在数组d[]中
            s_box(b,e,s);               //b是输入x ，e是s盒在输入为b时的输出
            s_box(d,f,s);               //d是b在输入异或为in[l]对应下的输入x*，f是s盒在输入为b时的输出
            for(k=0;k<=3;k++)
                Out[k]=e[k]^f[k];       //求出输出差分，存在Out数组中
            flag=1;                     //并将标志位置1；
            for(k=0;k<=3;k++)
            {
                if(Out[k]!=n[k])
                {
                 flag=0;
                 break;
                }
            }
           if(flag==1)  {//符合当前输出差分的时候，当前输出差分的计数器加一
            count=count+1;
            for(int z=0;z<6;z++){
                printf("%d",b[z]);
            }
            printf(",");
           }

        }
      if(count==0)
      printf("没有可能输入");
      else
      printf("\t输入数量为：%d",count);

      printf("\n");
    }
    printf("————————————————————————————————————————————————————\n");
}

    void s_box(int array[6],int brray[4],int crray[4][16])
    {
        int p,q,t;
        p=2*array[0]+array[5];                               //用b1b6比特决定s盒的行取值为p
        q=2*2*2*array[1]+2*2*array[2]+2*array[3]+array[4];   //用b2b3b4b5决定s盒的列取值为q
        t=crray[p][q];                                       //t就是s盒在输入为array[6]时的输出
        brray[3]=t%2;
        t=t/2;
        brray[2]=t%2;
        t=t/2;
        brray[1]=t%2;
        t=t/2;
        brray[0]=t%2;                                        //把t转换成二进制数存储在brray中
    }





#endif // TASK1_H_INCLUDED
