#include <stdio.h>//固定式分区分配 
#include<math.h>
#include<stdlib.h>

#define NUM 4
#define alloMemory(type) (type*)malloc(sizeof(type))

struct partiTab
{
	int no;
	int size;
	int firstAddr;
	char state;
}parTab[NUM];
typedef struct partiTab PARTITAB;

typedef struct jcb { /*定义作业控制块JCB ,部分信息省略*/
    char name[10];        //作业名
    int size;			//作业大小
    struct jcb* link;     //链指针
}JCB;
typedef struct
{
	JCB *front,*rear;
}jcbQue;
jcbQue *jcbReadyQue;

void AllocateMemory(int size);
void createTab();
void checkTab();
void recycleMemory(int i);


void AllocateMemory(int size)
{
	for(int i=0;i<NUM;i++)
	{
		PARTITAB p=parTab[i];
		if(p.state='N' && p.size>size)
			parTab[i].state='Y';
		else
			printf("没有空闲分区，无法分配内存！\n");
	}
}

void createTab()
{
	for(int i=1;i<=NUM;i++)
	{
		//getPartiTab(PARTITAB);
		parTab[i-1].no=i;
		parTab[i-1].size=20;
		parTab[i-1].firstAddr=21;
		parTab[i-1].state='N';
	}
}

void checkTab()
{
	printf("分区号\t大小\t起址\t状态\n");
	for(int i=0;i<NUM;i++)
	{
		printf("%d\t",parTab[i].no);
		printf("%d\t",parTab[i].size);
		printf("%d\t",parTab[i].firstAddr);
		printf("%c\t",parTab[i].state);
		printf("\n");
	}
}

void recycleMemory(int i)
{
	parTab[i-1].state='N';
}
int main(int argc, char* argv[])
{
	createTab();
	checkTab();
	printf("请按任意键继续：\n");
	getchar();
	printf("每个分区装入一道作业：\n");
	for(int i=0;i<NUM;i++)
	{
		AllocateMemory((i+1)*3);
	}
	checkTab();
	printf("请按任意键继续：\n");
	getchar();
	printf("假如一段时间后，其中一个作业结束，回收给它分配的分区(假如该作业在第2分区)\n");
	recycleMemory(2);
	checkTab();
	printf("请按任意键继续：\n");
	getchar();
	printf("接着,从外存后备作业队列中选择一个作业装入该分区(假如该作业大小为10)\n");
	AllocateMemory(10);
	checkTab();

	return 0;
}

