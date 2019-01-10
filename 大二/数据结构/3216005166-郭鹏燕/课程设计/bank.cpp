// ConsoleApplication5.cpp : ??????????????
//

#include<cstdio>
#include <cstdlib> 

#define STATUS int
#define OK 1
#define ERROR 0

const int MAX_cus=1000;  //客户的内存池的大小 
const int MAX_event=1000; //事件的内存池的大小
const int MAX_que=1000;   //队列的内存池的大小
int top_cus;             //客户内存池内中空闲的链栈的栈顶下标 
int top_event;           //事件内存池内中空闲的链栈的栈顶下标
int top_que;             //队列内存池内中空闲的链栈的栈顶下标 
int total;              //银行当前的钱数 
int closetime;          //银行的营业时间 
int lastevent;          //记录事件队列的头在事件内存池中的下标 
int firstevent;         //记录事件队列的尾在事件内存池中的下标
int use_cus; //-1是柜台空闲，其他为正在处理的客户的下标 
int firstque_head;      //第一个队列的头在队列内存池中的下标 
int firstque_tail;      //第一个队列的尾在队列内存池中的下标 
int firstque_num;       //第一个队列的客户的人数 
int secondque_head;     //第二个队列的头在队列内存池中的下标 
int secondque_tail;     //第二个队列的尾在队列内存池中的下标 
int secondque_num;      //第二个队列的客户的人数 
int sum;               //记录客户在银行待的总时间 
int number;            //记录总客户数 
struct CustNode
{
	 int num,arrtime,durtime,amount,next;//分别是客户编号，到达时间，交易款额和下一个空闲客户的下标 
} pool_cus[MAX_cus];   //客户内存池
enum Event_mode{come,go};
struct Event
{
	int time;      //该事件发生的时间 
	int cus;       //该事件的客户的下标 
	int next_event;//下一个发生的时间的下标 
	int event;  // 0表示来，1表示走
	int next;   // 下一个空闲事件的下标 
} pool_event[MAX_event]; //事件的内存池 

struct Queue
{
	int cus;           //队列中客户的编号 
	int next;          //队列内存池中下一个空闲的元素 
	int next_que;     //队列中下一个元素的下标 
} pool_que[MAX_que];  //队列内存池

int myMalloc_event()  //动态存储分配事件元素的内存 
{
	if (top_event==0) return 0;
	int re=top_event;
	top_event=pool_event[top_event].next;  //出栈 
	return re;                            //返回原栈顶元素的下标 
}

void myFree_event(int x) //释放事件元素的内存
{
	pool_event[x].next=top_event; 
	top_event=x;                  //入栈 
}

void build_event()               //初始化事件内存池
{
	for (int i=1;i<MAX_event;i++)
		pool_event[i].next=i-1;
	top_event=MAX_event-1;
}


int myMalloc_cus() //动态存储分配客户元素的内存
{
	if (top_cus==0) return 0;
	int re=top_cus;
	top_cus=pool_cus[top_cus].next;   //出栈 
	return re;                        //返回原栈顶元素的下标
}

void myFree_cus(int x)            //释放客户元素的空间 
{
	pool_cus[x].next=top_cus;
	top_cus=x;                        //入栈 
}

void build_cus()                   //初始化客户内存池 
{
	for (int i=1;i<MAX_cus;i++)
		pool_cus[i].next=i-1;
	top_cus=MAX_cus-1;
}


int myMalloc_que()  //动态存储分配队列元素的内存
{
	if (top_que==0) return 0;
	int re=top_que;
	top_que=pool_que[top_que].next;  //出栈 
	return re;                       //返回原栈顶元素的下标
}

void myFree_que(int x)  //释放队列元素的内存
{
	pool_que[x].next=top_que;
	top_que=x;                       //入栈 
}

void build_que()                   //初始化队列内存池
{
	for (int i=1;i<MAX_que;i++)
		pool_que[i].next=i-1;
	top_que=MAX_que-1;
}

STATUS push_firstque(int cus)      //客户入第一个队列 
{
	int temp_que=myMalloc_que();
	if (temp_que==0) return ERROR;
	pool_que[temp_que].cus=cus;
	if (firstque_head==-1) {firstque_head=firstque_tail=temp_que;}  //如果队列一为空 
	else//如果队列一不为空
	{
		pool_que[firstque_tail].next_que=temp_que;
		firstque_tail=temp_que;
		pool_que[temp_que].next_que=-1;
	}
	firstque_num++;  //队列一的人数加一 
	return OK;
}

STATUS push_secondque(int cus) //客户入第二个队列
{
	int temp_que=myMalloc_que();
	if (temp_que==0) return ERROR;
	pool_que[temp_que].cus=cus;
	if (secondque_head==-1) {secondque_head=secondque_tail=temp_que;} //如果队列一为空 
	else//如果队列一不为空
	{
		pool_que[secondque_tail].next_que=temp_que;
		secondque_tail=temp_que;
		pool_que[temp_que].next_que=-1;
	}
	secondque_num++;
	return OK;
}

int pop_firstque() //第一个队列出队 
{
	int now_que=firstque_head;
	if (now_que==-1) return -1;
	int now_cus=pool_que[now_que].cus;
	int temp=firstque_head;
	if (firstque_head==firstque_tail)firstque_head=firstque_tail=-1; //出队后队列为空 
	else
	firstque_head=pool_que[firstque_head].next_que;//出队后队列不为空
	myFree_que(now_que);         //释放空间 
	firstque_num--;        
	return now_cus;
}

int pop_secondque() //第二个队列出队 
{
	int now_que=secondque_head;
	if (now_que==-1) return -1;
	int now_cus=pool_que[now_que].cus;
	int temp=secondque_head;
	if (secondque_head==secondque_tail)secondque_head=secondque_tail=-1;//出队后队列为空 
	else
	secondque_head=pool_que[secondque_head].next_que;//出队后队列不为空
	myFree_que(now_que);//释放空间 
	secondque_num--;
	return now_cus;
}

STATUS set_event(int now_event,int cus,int time)  //在事件队列插入一个时间为time，事件类型为 now_event，客户下标为cus的事件 
{
	if (time>closetime) return OK;        //如果事件的时间超过营业时间则不加入队列中 
	
	int temp_event;
	if ((temp_event=myMalloc_event())==ERROR)return ERROR;
	pool_event[temp_event].cus=cus;
	pool_event[temp_event].time=time;
	pool_event[temp_event].event=1;
	while ((pool_event[now_event].next_event!=-1) &&( pool_event[pool_event[now_event].next_event].time<=time))//找到插入的位置 
	{
		now_event=pool_event[now_event].next_event;
	}
	pool_event[temp_event].next_event=pool_event[now_event].next_event;
	pool_event[now_event].next_event=temp_event;
	return OK;
}

void print_line()  //输出分割线 
{
	for(int i=1;i<=50;i++) printf("*") ;
	printf("\n");
}

STATUS set_data()  //输入并设定数据 
{
	printf("请输入银行的信息\n");
	total=-1; 
	while (total==-1)   //输入初始金额，如果不在范围里面则重新输入 
	{
		printf("初始金额：");
		scanf("%d",&total);
		if ((total<0) || (total>1000000000)) 
		{
			printf("输入的初始金额应大于等于0，小于等于1000000000,请重新输入\n"); 
			total=-1;
		}
	}
	
	closetime=-1;
	while (closetime==-1) //输入营业时间，如果不在范围里面则重新输入  
	{
		printf("营业时间：");
		scanf("%d",&closetime);
		if ((closetime<=0) || (closetime>1440))
		{
			printf("输入的营业时间应大于0，小于等于1440,请重新输入\n"); 
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
		printf("请输入第%d个顾客的信息\n",i);
		
		durtime=-1;
		while (durtime==-1)   //输入交易时间，如果不在范围里面则重新输入 
		{
			printf("交易时间："); 
			scanf("%d",&durtime);
			if ((durtime<=0) || (durtime>1440)) 
			{
				printf("输入的交易时间应大于0，小于等于1440,请重新输入\n"); 
				durtime=-1;
			}
		}
		
		amount=-2147483647;
		while (amount==-2147483647) //输入款额，如果不在范围里面则重新输入 
		{
			printf("款额："); 
			scanf("%d",&amount);
			if ((amount<-1000000000) || (amount>1000000000)) 
			{
				printf("输入的款额应大于等于-1000000000，小于等于1000000000,请重新输入\n"); 
				amount=-2147483647;
			}
		}
		
		printf("*第%d个顾客的到达时间为%d,业务为",i,t);
		if (amount<0)
			printf("取款或借款%d元\n",-amount);
		else
			printf("存款或还款%d元\n",amount);


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
		printf("输入第%d个顾客的信息\n",i+1,i);
		
		interval=0;
		while (interval==0) //输入时间差，如果不在范围里面则重新输入 
		{
			printf("与前一个顾客的到达的时间差(结束输入-1)：");  
			scanf("%d",&interval);
			if (interval==-1) break;
			if (interval<=0 || interval>10000)
			{
				printf("时间差只能为小于等于10000的正整数或-1请重新输入\n");
				interval=0;
			}
		}
		if (interval==-1) break;
		
		t+=interval;
		i++;
	}
	
	if (lastevent!=-1) pool_event[lastevent].next_event=-1;

	if (interval!=-1) //如果根据时间差算出的客户到达时间已经超过了营业时间 
	{
		print_line();
		printf("提示：第%d个顾客到达时银行已经关门,输入结束\n",i);
		number=i-1;
	}
	else number=i;
	print_line();
	return OK;
}

void build()       //初始化 
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

STATUS run() //处理事件并输出 
{
	int now_event=firstevent;
	use_cus=-1;
	int lasttotal=total;
	int count=-1;
	int counttime=0;
	for (;now_event!=-1;)                 //如果时间队列不为空则继续执行 
	{
		if (pool_event[now_event].event==0)  //如果当前事件是客户到达 
		{
			if (push_firstque(pool_event[now_event].cus)==ERROR) return ERROR;  //客户入第一个队列 
			printf("时间：%d 第%d个顾客到达\n",pool_event[now_event].time,pool_cus[pool_event[now_event].cus].num);
		}
		if ((pool_event[now_event].event==1)) //如果当前事件是客户离开 
		{
			if (pool_cus[use_cus].amount>0) {lasttotal=total;count=1;counttime=secondque_num;}
			total+=pool_cus[use_cus].amount;
			printf("时间：%d 第%d个顾客离开,该客户在银行逗留了%d分钟\n",pool_event[now_event].time,pool_cus[use_cus].num,pool_event[now_event].time-pool_cus[use_cus].arrtime);
			sum+=pool_event[now_event].time-pool_cus[use_cus].arrtime;
			myFree_cus(use_cus);
			use_cus=-1;      //没有处理业务的顾客 
			
			if (count!=-1)  //正在执行查找第二个队列的过程 
			{
			if (total<=lasttotal) 
			{
				count=-1;
			}
			else
			{
				int temp_cus=-1;
				while (count<=counttime)  //当找完整个队列或找到符合要求的客户退出 
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
				 
				  if (set_event(now_event,temp_cus,pool_event[now_event].time+pool_cus[temp_cus].durtime)==ERROR)  return ERROR;//把符合条件的客户的离开事件加入事件队列中 
				  use_cus=temp_cus;
			   }
			}
		}
			
		}
		
	
		
		while (use_cus==-1) //从第一个队伍中找到可以进入柜台办理业务或者第一条队伍为空时退出 
		{
			int now_cus=pop_firstque();
			if (now_cus==-1)  //如果第一个队伍为空，那么不处理第一个队伍的事件，查看下一个事件 
			{
				break; 
			}
			if (pool_cus[now_cus].amount>0)  //如果该客户是存款或还款 
			{
				if (set_event(now_event,now_cus,pool_event[now_event].time+pool_cus[now_cus].durtime)==ERROR) return ERROR;
				use_cus=now_cus;
				count=0;
			}
			else
			if ((pool_cus[now_cus].amount<0)) //如果该客户是取款或借款
			{
				if (total+pool_cus[now_cus].amount>=0) //银行的钱可以满足需要 
				{
					if (set_event(now_event,now_cus,pool_event[now_event].time+pool_cus[now_cus].durtime)==ERROR) return ERROR;
					use_cus=now_cus;
				}
				else
				{
					if (push_secondque(now_cus)==ERROR) return ERROR; //银行的钱不可以满足需要，则客户进入第二个队列等待 
				}
			}
		
		}

		int temp=now_event;
		now_event=pool_event[now_event].next_event;
		myFree_event(temp);

	}
	if (use_cus!=-1)   //营业时间结束，正在处理业务的顾客离开 
	{
		int now_cus=use_cus;
		total+=pool_cus[now_cus].amount;
		printf("时间：%d 第%d个顾客离开,该客户在银行逗留了%d分钟\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
	}
	for (;firstque_num>0;)//营业时间结束，第一个队列的顾客离开
	{
		int now_cus=pop_firstque();
		total+=pool_cus[now_cus].amount;
		printf("时间：%d 第%d个顾客离开,该客户在银行逗留了%d分钟\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
		myFree_cus(now_cus);
	}
	for (;secondque_num>0;) //营业时间结束，第二个队列的顾客离开)
	{
		int now_cus=pop_secondque();
		total+=pool_cus[now_cus].amount;
		printf("时间：%d 第%d个顾客离开,该客户在银行逗留了%d分钟\n",closetime,pool_cus[now_cus].num,closetime-pool_cus[now_cus].arrtime);
		sum+=closetime-pool_cus[now_cus].arrtime;
		myFree_cus(now_cus);
	}
	return OK;
}

int main()  //主程序 
{
	//freopen("bank.in","r",stdin);
	build();
	set_data();
	run();
	printf("客户在银行逗留的平均的时间为%.2f分钟",1.0*sum/number);
	
	return 0;
}



