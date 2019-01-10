#include <stdio.h>//�̶�ʽ�������� 
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

typedef struct jcb { /*������ҵ���ƿ�JCB ,������Ϣʡ��*/
    char name[10];        //��ҵ��
    int size;			//��ҵ��С
    struct jcb* link;     //��ָ��
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
			printf("û�п��з������޷������ڴ棡\n");
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
	printf("������\t��С\t��ַ\t״̬\n");
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
	printf("�밴�����������\n");
	getchar();
	printf("ÿ������װ��һ����ҵ��\n");
	for(int i=0;i<NUM;i++)
	{
		AllocateMemory((i+1)*3);
	}
	checkTab();
	printf("�밴�����������\n");
	getchar();
	printf("����һ��ʱ�������һ����ҵ���������ո�������ķ���(�������ҵ�ڵ�2����)\n");
	recycleMemory(2);
	checkTab();
	printf("�밴�����������\n");
	getchar();
	printf("����,��������ҵ������ѡ��һ����ҵװ��÷���(�������ҵ��СΪ10)\n");
	AllocateMemory(10);
	checkTab();

	return 0;
}

