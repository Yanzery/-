// ConsoleApplication5.cpp : ??????????????
//

#include<cstdio>
#include <cstdlib> 

#define STATUS int
#define OK 1
#define ERROR 0

const int MAX_cus=1000;  //�ͻ����ڴ�صĴ�С 
const int MAX_event=1000; //�¼����ڴ�صĴ�С
const int MAX_que=1000;   //���е��ڴ�صĴ�С
int top_cus;             //�ͻ��ڴ�����п��е���ջ��ջ���±� 
int top_event;           //�¼��ڴ�����п��е���ջ��ջ���±�
int top_que;             //�����ڴ�����п��е���ջ��ջ���±� 
int total;              //���е�ǰ��Ǯ�� 
int closetime;          //���е�Ӫҵʱ�� 
int lastevent;          //��¼�¼����е�ͷ���¼��ڴ���е��±� 
int firstevent;         //��¼�¼����е�β���¼��ڴ���е��±�
int use_cus; //-1�ǹ�̨���У�����Ϊ���ڴ���Ŀͻ����±� 
int firstque_head;      //��һ�����е�ͷ�ڶ����ڴ���е��±� 
int firstque_tail;      //��һ�����е�β�ڶ����ڴ���е��±� 
int firstque_num;       //��һ�����еĿͻ������� 
int secondque_head;     //�ڶ������е�ͷ�ڶ����ڴ���е��±� 
int secondque_tail;     //�ڶ������е�β�ڶ����ڴ���е��±� 
int secondque_num;      //�ڶ������еĿͻ������� 
int sum;               //��¼�ͻ������д�����ʱ�� 
int number;            //��¼�ܿͻ��� 
struct CustNode
{
	 int num,arrtime,durtime,amount,next;//�ֱ��ǿͻ���ţ�����ʱ�䣬���׿�����һ�����пͻ����±� 
} pool_cus[MAX_cus];   //�ͻ��ڴ��
enum Event_mode{come,go};
struct Event
{
	int time;      //���¼�������ʱ�� 
	int cus;       //���¼��Ŀͻ����±� 
	int next_event;//��һ��������ʱ����±� 
	int event;  // 0��ʾ����1��ʾ��
	int next;   // ��һ�������¼����±� 
} pool_event[MAX_event]; //�¼����ڴ�� 

struct Queue
{
	int cus;           //�����пͻ��ı�� 
	int next;          //�����ڴ������һ�����е�Ԫ�� 
	int next_que;     //��������һ��Ԫ�ص��±� 
} pool_que[MAX_que];  //�����ڴ��

int myMalloc_event()  //��̬�洢�����¼�Ԫ�ص��ڴ� 
{
	if (top_event==0) return 0;
	int re=top_event;
	top_event=pool_event[top_event].next;  //��ջ 
	return re;                            //����ԭջ��Ԫ�ص��±� 
}

void myFree_event(int x) //�ͷ��¼�Ԫ�ص��ڴ�
{
	pool_event[x].next=top_event; 
	top_event=x;                  //��ջ 
}

void build_event()               //��ʼ���¼��ڴ��
{
	for (int i=1;i<MAX_event;i++)
		pool_event[i].next=i-1;
	top_event=MAX_event-1;
}


int myMalloc_cus() //��̬�洢����ͻ�Ԫ�ص��ڴ�
{
	if (top_cus==0) return 0;
	int re=top_cus;
	top_cus=pool_cus[top_cus].next;   //��ջ 
	return re;                        //����ԭջ��Ԫ�ص��±�
}

void myFree_cus(int x)            //�ͷſͻ�Ԫ�صĿռ� 
{
	pool_cus[x].next=top_cus;
	top_cus=x;                        //��ջ 
}

void build_cus()                   //��ʼ���ͻ��ڴ�� 
{
	for (int i=1;i<MAX_cus;i++)
		pool_cus[i].next=i-1;
	top_cus=MAX_cus-1;
}


int myMalloc_que()  //��̬�洢�������Ԫ�ص��ڴ�
{
	if (top_que==0) return 0;
	int re=top_que;
	top_que=pool_que[top_que].next;  //��ջ 
	return re;                       //����ԭջ��Ԫ�ص��±�
}

void myFree_que(int x)  //�ͷŶ���Ԫ�ص��ڴ�
{
	pool_que[x].next=top_que;
	top_que=x;                       //��ջ 
}

void build_que()                   //��ʼ�������ڴ��
{
	for (int i=1;i<MAX_que;i++)
		pool_que[i].next=i-1;
	top_que=MAX_que-1;
}

STATUS push_firstque(int cus)      //�ͻ����һ������ 
{
	int temp_que=myMalloc_que();
	if (temp_que==0) return ERROR;
	pool_que[temp_que].cus=cus;
	if (firstque_head==-1) {firstque_head=firstque_tail=temp_que;}  //�������һΪ�� 
	else//�������һ��Ϊ��
	{
		pool_que[firstque_tail].next_que=temp_que;
		firstque_tail=temp_que;
		pool_que[temp_que].next_que=-1;
	}
	firstque_num++;  //����һ��������һ 
	return OK;
}

STATUS push_secondque(int cus) //�ͻ���ڶ�������
{
	int temp_que=myMalloc_que();
	if (temp_que==0) return ERROR;
	pool_que[temp_que].cus=cus;
	if (secondque_head==-1) {secondque_head=secondque_tail=temp_que;} //�������һΪ�� 
	else//�������һ��Ϊ��
	{
		pool_que[secondque_tail].next_que=temp_que;
		secondque_tail=temp_que;
		pool_que[temp_que].next_que=-1;
	}
	secondque_num++;
	return OK;
}

int pop_firstque() //��һ�����г��� 
{
	int now_que=firstque_head;
	if (now_que==-1) return -1;
	int now_cus=pool_que[now_que].cus;
	int temp=firstque_head;
	if (firstque_head==firstque_tail)firstque_head=firstque_tail=-1; //���Ӻ����Ϊ�� 
	else
	firstque_head=pool_que[firstque_head].next_que;//���Ӻ���в�Ϊ��
	myFree_que(now_que);         //�ͷſռ� 
	firstque_num--;        
	return now_cus;
}

int pop_secondque() //�ڶ������г��� 
{
	int now_que=secondque_head;
	if (now_que==-1) return -1;
	int now_cus=pool_que[now_que].cus;
	int temp=secondque_head;
	if (secondque_head==secondque_tail)secondque_head=secondque_tail=-1;//���Ӻ����Ϊ�� 
	else
	secondque_head=pool_que[secondque_head].next_que;//���Ӻ���в�Ϊ��
	myFree_que(now_que);//�ͷſռ� 
	secondque_num--;
	return now_cus;
}

STATUS set_event(int now_event,int cus,int time)  //���¼����в���һ��ʱ��Ϊtime���¼�����Ϊ now_event���ͻ��±�Ϊcus���¼� 
{
	if (time>closetime) return OK;        //����¼���ʱ�䳬��Ӫҵʱ���򲻼�������� 
	
	int temp_event;
	if ((temp_event=myMalloc_event())==ERROR)return ERROR;
	pool_event[temp_event].cus=cus;
	pool_event[temp_event].time=time;
	pool_event[temp_event].event=1;
	while ((pool_event[now_event].next_event!=-1) &&( pool_event[pool_event[now_event].next_event].time<=time))//�ҵ������λ�� 
	{
		now_event=pool_event[now_event].next_event;
	}
	pool_event[temp_event].next_event=pool_event[now_event].next_event;
	pool_event[now_event].next_event=temp_event;
	return OK;
}

void print_line()  //����ָ��� 
{
	for(int i=1;i<=50;i++) printf("*") ;
	printf("\n");
}

STATUS set_data()  //���벢�趨���� 
{
	printf("���������е���Ϣ\n");
	total=-1; 
	while (total==-1)   //�����ʼ��������ڷ�Χ�������������� 
	{
		printf("��ʼ��");
		scanf("%d",&total);
		if ((total<0) || (total>1000000000)) 
		{
			printf("����ĳ�ʼ���Ӧ���ڵ���0��С�ڵ���1000000000,����������\n"); 
			total=-1;
		}
	}
	
	closetime=-1;
	while (closetime==-1) //����Ӫҵʱ�䣬������ڷ�Χ��������������  
	{
		printf("Ӫҵʱ�䣺");
		scanf("%d",&closetime);
		if ((closetime<=0) || (closetime>1440))
		{
			printf("�����Ӫҵʱ��Ӧ����0��С�ڵ���1440,����������\n"); 
			closetime=-1;
		}
	}
	
	print_line();
	int durtime,interval,amount;


	int t=0;
	int i=1;
	lastevent=-1;
	firstevent=-1;
	while (t<=closetime)
	{
		printf("�������%d���˿͵���Ϣ\n",i);
		
		durtime=-1;
		while (durtime==-1)   //���뽻��ʱ�䣬������ڷ�Χ�������������� 
		{
			printf("����ʱ�䣺"); 
			scanf("%d",&durtime);
			if ((durtime<=0) || (durtime>1440)) 
			{
				printf("����Ľ���ʱ��Ӧ����0��С�ڵ���1440,����������\n"); 
				durtime=-1;
			}
		}
		
		amount=-2147483647;
		while (amount==-2147483647) //�����������ڷ�Χ�������������� 
		{
			printf("��"); 
			scanf("%d",&amount);
			if ((amount<-1000000000) || (amount>1000000000)) 
			{
				printf("����Ŀ��Ӧ���ڵ���-1000000000��С�ڵ���1000000000,����������\n"); 
				amount=-2147483647;
			}
		}
		
		printf("*��%d���˿͵ĵ���ʱ��Ϊ%d,ҵ��Ϊ",i,t);
		if (amount<0)
			printf("ȡ�����%dԪ\n",-amount);
		else
			printf("���򻹿�%dԪ\n",amount);


		int temp_cus=myMalloc_cus();
		if (temp_cus==0) return ERROR;
		int temp_event=myMalloc_event();
		if (temp_event==0) return ERROR;
		pool_cus[temp_cus].amount=amount;
		pool_cus[temp_cus].arrtime=t;
		pool_cus[temp_cus].durtime=durtime;
		pool_cus[temp_cus].num=i;
		pool_event[temp_event].cus=temp_cus;
		pool_event[temp_event].time=pool_cus[temp_cus].arrtime;
		if (lastevent==-1) {firstevent=temp_event;}
		else
		pool_event[lastevent].next_event=temp_event;
		lastevent=temp_event;
		print_line();
		printf("�����%d���˿͵���Ϣ\n",i+1,i);
		
		interval=0;
		while (interval==0) //����ʱ��������ڷ�Χ�������������� 
		{
			printf("��ǰһ���˿͵ĵ����ʱ���(��������-1)��");  
			scanf("%d",&interval);
			if (interval==-1) break;
			if (interval<=0 || interval>10000)
			{
				printf("ʱ���ֻ��ΪС�ڵ���10000����������-1����������\n");
				interval=0;
			}
		}
		if (interval==-1) break;
		
		t+=interval;
		i++;
	}
	
	if (lastevent!=-1) pool_event[lastevent].next_event=-1;

	if (interval!=-1) //�������ʱ�������Ŀͻ�����ʱ���Ѿ�������Ӫҵʱ�� 
	{
		print_line();
		printf("��ʾ����%d���˿͵���ʱ�����Ѿ�����,�������\n",i);
		number=i-1;
	}
	else number=i;
	print_line();
	return OK;
}

void build()       //��ʼ�� 
{
	build_event();
	build_cus();
	build_que();
	

	firstque_head=-1;
	firstque_tail=-1;
	firstque_num=0;
	secondque_head=-1;
	secondque_tail=-1;
	secondque_num=0;
}

STATUS run() //�����¼������ 
{
	int now_event=firstevent;
	use_cus=-1;
	int lasttotal=total;
	int count=-1;
	int counttime=0;
	for (;now_event!=-1;)                 //���ʱ����в�Ϊ�������ִ�� 
	{
		if (pool_event[now_event].event==0)  //�����ǰ�¼��ǿͻ����� 
		{
			if (push_firstque(pool_event[now_event].cus)==ERROR) return ERROR;  //�ͻ����һ������ 
			printf("ʱ�䣺%d ��%d���˿͵���\n",pool_event[now_event].time,pool_cus[pool_event[now_event].cus].num);
		}
		if ((pool_event[now_event].event==1)) //�����ǰ�¼��ǿͻ��뿪 
		{
			if (pool_cus[use_cus].amount>0) {lasttotal=total;count=1;counttime=secondque_num;}
			total+=pool_cus[use_cus].amount;
			printf("ʱ�䣺%d ��%d���˿��뿪,�ÿͻ������ж�����%d����\n",pool_event[now_event].time,pool_cus[use_cus].num,pool_event[now_event].time-pool_cus[use_cus].arrtime);
			sum+=pool_event[now_event].time-pool_cus[use_cus].arrtime;
			myFree_cus(use_cus);
			use_cus=-1;      //û�д���ҵ��Ĺ˿� 
			
			if (count!=-1)  //����ִ�в��ҵڶ������еĹ��� 
			{
			if (total<=lasttotal) 
			{
				count=-1;
			}
			else
			{
				int temp_cus=-1;
				while (count<=counttime)  //�������������л��ҵ�����Ҫ��Ŀͻ��˳� 
				{
					temp_cus=pop_secondque();
					count++;
					if (total+pool_cus[temp_cus].amount>=0) {break;}
					if (push_secondque(temp_cus)==ERROR) return ERROR;
					temp_cus=-1; 
				}
				//if (count>counttime)
				if (temp_cus==-1)
				{
					count=-1;
				}
				else
				{
				 
				  if (set_event(now_event,temp_cus,pool_event[now_event].time+pool_cus[temp_cus].durtime)==ERROR)  return ERROR;//�ѷ��������Ŀͻ����뿪�¼������¼������� 
				  use_cus=temp_cus;
			   }
			}
		}
			
		}
		
	
		
		while (use_cus==-1) //�ӵ�һ���������ҵ����Խ����̨����ҵ����ߵ�һ������Ϊ��ʱ�˳� 
		{
			int now_cus=pop_firstque();
			if (now_cus==-1)  //�����һ������Ϊ�գ���ô�������һ��������¼����鿴��һ���¼� 
			{
				break; 
			}
			if (pool_cus[now_cus].amount>0)  //����ÿͻ��Ǵ��򻹿� 
			{
				if (set_event(now_event,now_cus,pool_event[now_event].time+pool_cus[now_cus].durtime)==ERROR) return ERROR;
				use_cus=now_cus;
				count=0;
			}
			else
			if ((pool_cus[now_cus].amount<0)) //����ÿͻ���ȡ�����
			{
				if (total+pool_cus[now_cus].amount>=0) //���е�Ǯ����������Ҫ 
				{
					if (set_event(now_event,now_cus,pool_event[now_event].time+pool_cus[now_cus].durtime)==ERROR) return ERROR;
					use_cus=now_cus;
				}
				else
				{
					if (push_secondque(now_cus)==ERROR) return ERROR; //���е�Ǯ������������Ҫ����ͻ�����ڶ������еȴ� 
				}
			}
		
		}

		int temp=now_event;
		now_event=pool_event[now_event].next_event;
		myFree_event(temp);

	}
	if (use_cus!=-1)   //Ӫҵʱ����������ڴ���ҵ��Ĺ˿��뿪 
	{
		int now_cus=use_cus;
		total+=pool_cus[now_cus].amount;
		printf("ʱ�䣺%d ��%d���˿��뿪,�ÿͻ������ж�����%d����\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
	}
	for (;firstque_num>0;)//Ӫҵʱ���������һ�����еĹ˿��뿪
	{
		int now_cus=pop_firstque();
		total+=pool_cus[now_cus].amount;
		printf("ʱ�䣺%d ��%d���˿��뿪,�ÿͻ������ж�����%d����\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
		myFree_cus(now_cus);
	}
	for (;secondque_num>0;) //Ӫҵʱ��������ڶ������еĹ˿��뿪)
	{
		int now_cus=pop_secondque();
		total+=pool_cus[now_cus].amount;
		printf("ʱ�䣺%d ��%d���˿��뿪,�ÿͻ������ж�����%d����\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
		myFree_cus(now_cus);
	}
	return OK;
}

int main()  //������ 
{
	//freopen("bank.in","r",stdin);
	build();
	set_data();
	run();
	printf("�ͻ������ж�����ƽ����ʱ��Ϊ%.2f����",1.0*sum/number);
	
	return 0;
}



