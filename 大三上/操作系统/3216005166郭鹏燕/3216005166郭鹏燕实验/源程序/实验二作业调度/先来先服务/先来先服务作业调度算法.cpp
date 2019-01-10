#include <bits/stdc++.h>
#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 
using namespace std;

struct JCB
{
	char name[10];
	char state; 
	int ctime;
	int rtime;
	int ntime;
	int ftime;
	struct JCB* link;
}*ready=NULL,*p,*come=NULL,ans[10];



int h,num;

void sort_in_ready() /* �����Խ��̽������ȼ����к���*/ 
{ 
	if (ready==NULL) ready=p;
	else
	{
		JCB *now=ready;
		while (now->link!=NULL) now=now->link;	
		now->link=p;
	}
	
} 


void sort_in_come() /* �����Խ��̽������ȼ����к���*/ 
{ 
	JCB *first, *second; 
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
		p=getpch(JCB); 
		scanf("%s %d %d",p->name,&p->ctime,&p->ntime); 
		p->rtime=0;p->state='w'; 
		p->link=NULL; 
		sort_in_come(); /* ����sort����*/ 
	} 
} 

void disp(JCB * pr) /*����������ʾ����,������ʾ��ǰ����*/ 
{ 
	printf("\n qname \t state \t ntime \t runtime \n"); 
	printf("| %s \t",pr->name); 
	printf("| %c \t",pr->state); 
	printf("| %d \t",pr->ntime); 
	printf("   | %d \t",pr->rtime); 
	printf(" \n"); 
} 
void check() /* �������̲鿴���� */ 
{ 
	JCB* pr; 
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
	p->ftime=h+1;
	ans[++num]=*p;
	free(p); 
	
} 
void running() /* �������̾�������(��������ʱ�䵽,�þ���״̬*/ 
{ 
	(p->rtime)++; 
	if(p->rtime==p->ntime) 
	{
	
		destroy(); /* ����destroy����*/ 
	}
	else 
	{ 
		p->state='W'; 
		if (ready==NULL) p->link=NULL;
		else
		p->link=ready;
		ready=p;
		 /*����sort����*/ 
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


void output()
{
	printf("\n\n\n");

	puts("FCFS");
	puts("");
	printf("\n qname\t ctime \t ntime \t ftime \t ttime \t wttime\n"); 
	double sum_ttime=0,sum_wttime=0;
	for (int i=1;i<=num;i++)
	{
		printf("|%s      |%d      |%d      |%d      |%d      |%.2f\n",ans[i].name,ans[i].ctime,ans[i].ntime,ans[i].ftime,ans[i].ftime-ans[i].ctime,(1.0*ans[i].ftime-ans[i].ctime)/ans[i].ntime);
		sum_ttime+=ans[i].ftime-ans[i].ctime;
		sum_wttime+=(1.0*ans[i].ftime-ans[i].ctime)/ans[i].ntime;
	}
	puts("");
	printf("avg_time=%.2f\n",1.*sum_ttime/num);
	printf("avg_wtime=%.2f\n",1.*sum_wttime/num);
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
	
	
	output();
	
	ch=getchar(); 
} 
