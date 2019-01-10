#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#define getpch(type) (type*)malloc(sizeof(type))

/* ������̿��ƿ�PCB */
struct pcb {
	char name[10];
	char state;//״̬
	int super;//���ȼ�
	int ntime;//��ִ��ʱ��
	int otime;//ʣ����ִ��ʱ��
	int rtime;//ִ������
	struct pcb* link;
}*ready=NULL,*p;

typedef struct pcb PCB;
int timeSlice=0;//ʱ��Ƭ��С

/* �����Խ��̽������ȼ����к���*/
void sort() {
	PCB *first, *second;
	int insert=0;
	if((ready==NULL)||((p->super)>(ready->super))) {/*���ȼ������,�������*/
		p->link=ready;
		ready=p;
	} else {/*���̱Ƚ����ȼ�,�����ʵ���λ����*/
		first=ready;
		second=first->link;
		while(second!=NULL) {
			if((p->super)>(second->super)) {/*��������̱ȵ�ǰ������������,���뵽��ǰ����ǰ��*/
				p->link=second;
				first->link=p;
				second=NULL;
				insert=1;
			} else { /* ����������������,����뵽��β*/
				first=first->link;
				second=second->link;
			}
		}
		if(insert==0) first->link=p;
	}
}

/* �������̿��ƿ麯��*/
void input() {
	int i,num;
	system("CLS");/*����*/
	// clrscr(); /*����*/
	printf("\n ��������̸���\n");
	scanf("%d",&num);
	printf("\n ������ʱ��Ƭ��С\n");
	scanf("%d",&timeSlice);
	for(i=0;i<num;i++) {
		printf("\n ���̺�No.%d:\n",i);
		p=getpch(PCB);
		printf("\n ���������:");
		scanf("%s",p->name);
		// printf("\n �������������:");
		// scanf("%d",&p->super);
		p->super=num;
		printf("\n �����������ʱ��:");
		scanf("%d",&p->ntime);
		p->otime=p->ntime;
		printf("\n");
		p->rtime=0;p->state='w';
		p->link=NULL;
		sort(); /* ����sort����*/
	}
}


int space() {
	int l=0; PCB* pr=ready;
	while(pr!=NULL) {
		l++;
		pr=pr->link;
	}
	return(l);
}

/*����������ʾ����,������ʾ��ǰ����*/
void disp(PCB * pr) {
	printf("\n qname\t state\t super\t ntime\t otime\t rtime \n");
	printf("|%s\t",pr->name);
	printf("|%c\t",pr->state);
	printf("|%d\t",pr->super);
	printf("|%d\t",pr->ntime);
	printf("|%d\t",pr->otime);
	printf("|%d\t",pr->rtime);
	printf("\n");
}

 /* �������̲鿴���� */
void check() {
	PCB* pr;
	p->otime=p->otime-timeSlice;//check() �� running() ����һ��ʣ��ʱ���ж� 
	if(p->otime<0) {
		p->otime=0;
	}
	printf("\n **** ��ǰ�������еĽ�����:%s",p->name); /*��ʾ��ǰ���н���*/
	disp(p);
	pr=ready;
	printf("\n ****��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/
	while(pr!=NULL) {
		disp(pr);
		pr=pr->link;
	}
}

/*�������̳�������(�������н���,��������)*/
void destroy() {
	printf("\n ���� [%s] �����.\n",p->name);
	free(p);
}

/* �������̾�������(��������ʱ�䵽,�þ���״̬)*/
void running() {
	(p->rtime)++;
	if(p->otime==0) {
		destroy(); /* ����destroy����*/
	} else {
		(p->super)--;
		p->state='w';
		sort(); /*����sort����*/
	}
}

int main() { /*������*/
	int len,h=0;
	char ch;
	input();
	len=space();
	while((len!=0)&&(ready!=NULL)) {
		ch=getchar();
		h++;
		printf("\n The execute number:%d \n",h);
		p=ready;
		ready=p->link;
		p->link=NULL;
		p->state='R';
		check();
		running();
		printf("\n ����һ������......");
		ch=getchar();
	}
	printf("\n\n �����Ѿ����.\n");
	ch=getchar();
	return 0;
}
