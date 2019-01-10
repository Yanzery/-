#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 
struct pcb 
{ /* ������̿��ƿ�PCB */ 
	char name[10]; 
	char state; 
	int ctime; 
	int ntime; 
	int rtime; 
	struct pcb* link; 
}*ready=NULL,*p,*come=NULL; 
typedef struct pcb PCB;   

int h;

void sort_in_ready() /* �����Խ��̽������ȼ����к���*/ 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((ready==NULL)||((p->ntime-p->rtime)<(ready->ntime-ready->rtime))) /*���ȼ������,�������*/ 
	{ 
		p->link=ready; 
		ready=p; 
	} 
	else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/ 
	{ 
		first=ready; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->ntime-p->rtime)<(second->ntime-second->rtime)) /*��������̱ȵ�ǰ������������,*/ 
			{ /*���뵽��ǰ����ǰ��*/ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else /* ����������������,����뵽��β*/ 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		} 
		if(insert==0) first->link=p; 
	} 
} 

void sort_in_come() /* �����Խ��̽������ȼ����к���*/ 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((come==NULL)||((p->ctime)<(come->ctime))) /*���ȼ������,�������*/ 
	{ 
		p->link=come; 
		come=p; 
	} 
	else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/ 
	{ 
		first=come; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->ctime)<(second->ctime)) /*��������̱ȵ�ǰ������������,*/ 
			{ /*���뵽��ǰ����ǰ��*/ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else /* ����������������,����뵽��β*/ 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		} 
		if(insert==0) first->link=p; 
	} 
} 




void input() /* �������̿��ƿ麯��*/ 
{ 
	int i,num; 
	scanf("%d",&num); 
	for(i=0;i<num;i++) 
	{ 
		p=getpch(PCB); 
		scanf("%s %d %d",p->name,&p->ctime,&p->ntime); 
		p->rtime=0;p->state='w'; 
		p->link=NULL; 
		sort_in_come(); /* ����sort����*/ 
	} 
} 

void disp(PCB * pr) /*����������ʾ����,������ʾ��ǰ����*/ 
{ 
	printf("\n qname \t state \t ndtime \t runtime \n"); 
	printf("| %s \t",pr->name); 
	printf("| %c \t",pr->state); 
	printf("| %d \t",pr->ntime); 
	printf("    | %d \t",pr->rtime); 
	printf(" \n"); 
} 
void check() /* �������̲鿴���� */ 
{ 
	PCB* pr; 
	printf("\n **** ��ǰ�������еĽ�����:%s",p->name); /*��ʾ��ǰ���н���*/ 
	disp(p); 
	pr=ready; 
	printf("\n ****��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/ 
	while(pr!=NULL) 
	{ 
		disp(pr); 
		pr=pr->link; 
	} 
} 
void destroy() /*�������̳�������(�������н���,��������)*/ 
{ 
	printf("\n ���� [%s] �����.\n",p->name); 
	free(p); 
} 
void running() /* �������̾�������(��������ʱ�䵽,�þ���״̬*/ 
{ 
	(p->rtime)++; 
	if(p->rtime==p->ntime) 
	destroy(); /* ����destroy����*/ 
	else 
	{ 
		p->state='w'; 
		sort_in_ready(); /*����sort����*/ 
	} 
} 

void come2ready()
{
	while (true)
	{
		if (come==NULL) return ;
		if (come->ctime==h)
		{
			p=come;
			come=come->link;
			p->link=NULL;			
			sort_in_ready();
		}
		else return ;
	}
}

int main() /*������*/ 
{ 
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int len; 
	h=-1;
	char ch; 
	input(); 
	while(((ready!=NULL) || (come!=NULL)) )
	{ 
		h++;
		printf("--------------------------------"); 
		printf("\n The execute number:%d \n",h); 
		come2ready(); 
		if (ready!=NULL)
		{
			p=ready; 
			ready=p->link; 
			p->link=NULL; 
			p->state='R'; 
		}
		else
		{
			printf("\n���޳�������\n",h);  
		}	
		check(); 
		running(); 
	} 
	printf("\n\n �����Ѿ����.\n"); 
	ch=getchar(); 
} 

