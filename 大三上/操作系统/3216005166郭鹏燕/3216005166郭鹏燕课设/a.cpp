// ConsoleApplication11.cpp : 定义控制台应用程序的入口点。
//

#include <bits/stdc++.h>
#include <queue>
#include <algorithm>


#define getpch(type) (type*)malloc(sizeof(type))

const int maxdot=100000;

using namespace std;

const string job_alg_list[]= {"","1.先来先服务调度算法","2.最短作业优先调度算法","3.优先级调度算法","4.高响应比优先调度算法"};
const string pro_alg_list[]= {"","1.先来先服务算法","2.短进程优先(可抢占)","3.短进程优先(不可抢占)","4.静态优先级调度算法(可抢占)","5.静态优先级调度算法(不可抢占)","6.动态优先级调度算法(可抢占)","7.动态优先级调度算法（不可抢占）","8.轮转调度算法调度算法"};

int mag_num,mode;
int job_num,job_alg,pro_alg;
int que_job[maxdot],que_pro[maxdot];
int input_mode;
bool print_tag;
struct TNode {
	char name[10];         //作业名称
	int reach_time,         //到达时间
  int run_time,          //预计运行时间
  int work_time         //当前已经运行的时间
  int mem             //使用内存的大小
  int mag;	             //使用磁带机的个数
	int finish_time;        //进程完成的时间
	int insert_time;       //作业进入进程等待队列的时间
	int pri;              //优先级
	char state;           //当前作业在哪个位置（"U"表示还没到达，'J'表示在作业等待队列，'P'表示在进程等待队列里面）
	int start,size;         //该进程分配到的内存的起始位置和大小

} job[maxdot];

struct TMem {
	int start,size;
	TMem *link;
} *mem_head,mem[maxdot];


void write_line() {
	printf("-------------------------------------------------------------------------------\n");
}


bool Insert(int x) {
	TMem *tmp=mem_head;
	TMem *Next=NULL;
	int Min=100005;
	while (tmp!=NULL) {
		if (tmp->size>=job[x].size && tmp->size<Min) {
			Min=tmp->size;
			Next=tmp;
		}
		tmp=tmp->link;
	}
	tmp=Next;
	if (tmp!=NULL && tmp->size>=job[x].size) {

		job[x].start=tmp->start;
		tmp->start=tmp->start+job[x].size;
		tmp->size=tmp->size-job[x].size;
		if (mode ==1)printf("作业%s放进了内存地址为%d到%d的空间\n",job[x].name,job[x].start,job[x].start+job[x].size);
		return true;
	}


	return false;
}


void Release(int x) {

	if (mem_head->start>=job[x].start) {
		if (job[x].start+job[x].size==mem_head->start) {
			mem_head->start=job[x].start;
			mem_head->size+=job[x].size;
		} else {
			TMem *p=getpch(TMem);
			p->start=job[x].start;
			p->size=job[x].size;
			p->link=mem_head;
			mem_head=p;
		}
	} else {
		TMem *tmp=mem_head;
		while (tmp->link!=NULL && tmp->link->start<job[x].start) {
			tmp=tmp->link;
		}
		if  ((tmp->start+tmp->size==job[x].start) &&(tmp->link!=NULL && job[x].start+job[x].size==tmp->link->start)) {
			tmp->size+=job[x].size+tmp->link->size;
			tmp->link=tmp->link->link;
		} else if (tmp->start+tmp->size==job[x].start) tmp->size+=job[x].size;
		else if (tmp->link!=NULL && job[x].start+job[x].size==tmp->link->start) {
			tmp->link->start=job[x].start;
			tmp->link->size+=job[x].size;
		} else {
			TMem *p=getpch(TMem);
			p->start=job[x].start;
			p->size=job[x].size;
			p->link=tmp->link;
			tmp->link=p;
		}

	}
}


void pt(int t) {
	if (!print_tag) {
		write_line();
		if (t%60<10) printf("在%d：0%d的时候:\n",t/60,t%60);
		else printf("在%d：%d的时候:\n",t/60,t%60);
		print_tag=true;
	}
}

void read_init() {

	write_line();
	mem_head=getpch(TMem);

	puts("基本信息录入");
	mem_head->start=0;
	mem_head->link=NULL;
	printf("请输入内存大小(K):");
	scanf("%d",&mem_head->size);
	printf("请输入磁带机个数:");
	scanf("%d",&mag_num);
	printf("请输入作业的个数:");
	scanf("%d",&job_num);
	if (mode ==2 || job_alg==3 || (pro_alg>=4 && pro_alg<=7)) {
		printf("请按照\"作业名 到达时间(hh:mm) 估计运行时间（min） 内存需要（K） 磁带机需要(台) 优先级(数字越大优先级越高)\"的顺序输入\n");
		for (int i=1; i<=job_num; i++) {
			int reach_hour,reach_minute;
			scanf("%s %d:%d %d %d %d %d",job[i].name,&reach_hour,&reach_minute,&job[i].run_time,&job[i].size,&job[i].mag,&job[i].pri);
			job[i].reach_time=reach_hour*60+reach_minute;

		}
	} else {
		printf("请按照\"作业名 到达时间(hh:mm) 估计运行时间（min） 内存需要（K） 磁带机需要(台)\"的顺序输入\n");
		for (int i=1; i<=job_num; i++) {
			int reach_hour,reach_minute;
			scanf("%s %d:%d %d %d %d",job[i].name,&reach_hour,&reach_minute,&job[i].run_time,&job[i].size,&job[i].mag);
			job[i].reach_time=reach_hour*60+reach_minute;
			job[i].state='U';
		}
	}
}

void init() {
	for (int i=1; i<=job_num; i++) {
		job[i].state='U';
		job[i].insert_time=0;
		job[i].finish_time=0;
		job[i].start=0;
		job[i].work_time=0;
	}
}

void read_mode() {
	write_line();
	printf("1.普通模式\n2.对比模式\n请输入你要执行的模式：");
	scanf("%d",&mode);
	write_line();
	if (mode==2) return ;
	printf("作业调度的算法有：\n1.先来先服务调度算法\n2.最小作业优先调度算法\n3.优先级调度算法\n4.高响应比优先调度算法\n请输入你要选择的作业调度算法的序号:");
	scanf("%d",&job_alg);
	write_line();
	printf("进程调度的算法有：\n1.先来先服务算法\n2.短进程优先(可抢占)\n3.短进程优先(不可抢占)\n4.静态优先级调度算法(可抢占)\n5.静态优先级调度算法(不可抢占)\n6.动态优先级调度算法(可抢占)\n7.动态优先级调度算法（不可抢占）\n8.轮转调度算法调度算法\n请输入你要选择的进程调度算法的序号:");
	scanf("%d",&pro_alg);
	write_line();
}



void jobCome(int t) {
	for (int i=1; i<=job_num; i++) {
		if ((job[i].state=='U') && (job[i].reach_time==t)) {
			que_job[++que_job[0]]=i;
			if (mode ==1) {
				pt(t);
				printf("作业%s到达,进入作业等待队列\n\n",job[i].name);
			}
			job[i].state='J';
			job[i].work_time=0;

		}
	}
}

int pro_calc2(int i) {
	return job[i].run_time-job[i].work_time;
}

int pro_calc3(int i) {
	return pro_calc2(i);
}

int pro_calc4(int i) {
	return job[i].pri;
}

int pro_calc5(int i) {
	return pro_calc4(i);
}

int pro_calc6(int t,int i) {
	return job[i].pri+(t-job[i].insert_time-job[i].work_time);
}

int pro_calc7(int t,int i) {
	return pro_calc6(t,i);
}

//1.先来先服务算法\n2.短进程优先(可抢占)3.短进程优先(不可抢占)\n4.静态优先级调度算法(可抢占)\n5.静态优先级调度算法(不可抢占)6.动态优先级调度算法（可抢占）\n7.动态优先级调度算法（不可抢占）8.轮转调度算法调度算法\n9.多级反馈队列调度算法\n"
void refresh_pro_que(int t) {
	bool boo=false;;
	switch(pro_alg) {
		case 1:  //1.先来先服务算法
			break;
		case 2:  //2.短进程优先(可抢占)
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc2(que_pro[i])>pro_calc2(que_pro[j])) {

						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;

		case 3://短进程优先(不可抢占)
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc3(que_pro[i])>pro_calc3(que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 4://4.静态优先级调度算法(可抢占)
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc4(que_pro[i])<pro_calc4(que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 5://5.静态优先级调度算法(不可抢占)
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (job[que_pro[i]].pri<job[que_pro[j]].pri) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 6://6.动态优先级调度算法（可抢占）
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc6(t,que_pro[i])<pro_calc6(t,que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}

			break;
		case 7://7.动态优先级调度算法（不可抢占）
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc7(t,que_pro[i])<pro_calc7(t,que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}

			break;
		case 8: //8.轮转调度算法调度算法
			if (que_pro[0]==0) break;
			int tmp=que_pro[1];
			for (int i=1; i<que_pro[0]; i++) {
				que_pro[i]=que_pro[i+1];
				boo=true;
			}
			que_pro[que_pro[0]]=tmp;

			break;

	}
	if (mode==1 && boo) {
		pt(t);
		printf("进程等待队列发生了交换\n");
	}
}

double job_calc4(int t,int i) {
	return (t-job[i].reach_time+job[i].run_time*1.0)/job[i].run_time;
}


void refresh_job_que(int t) {
	bool boo=false;

	switch (job_alg) {
		case 1://1.先来先服务调度算法
			break;
		case 2://2.最小作业优先调度算法
			for (int i=1; i<=que_job[0]; i++)
				for (int j=i+1; j<=que_job[0]; j++)
					if (job[que_job[i]].run_time>job[que_job[j]].run_time) {
						boo=true;
						swap(que_job[i],que_job[j]);
					}
			break;
		case 3://3.优先级调度算法
			for (int i=1; i<=que_job[0]; i++)
				for (int j=i+1; j<=que_job[0]; j++)
					if (job[que_job[i]].pri<job[que_job[j]].pri) {
						boo=true;
						swap(que_job[i],que_job[j]);
					}
			break;
		case 4://4.高响应比优先调度算法
			for (int i=1; i<=que_job[0]; i++)
				for (int j=i+1; j<=que_job[0]; j++)
					if (job_calc4(t,que_job[i])<job_calc4(t,que_job[j])) {
						boo=true;
						swap(que_job[i],que_job[j]);
					}
			break;

	}
	if (mode == 1 && boo) {
		pt(t);
		printf("作业等待队列发生了交换\n");
	}

}


void run_pro(int t) {
	if (que_pro[0]==0) return ;
	job[que_pro[1]].work_time++;
	if (job[que_pro[1]].work_time>=job[que_pro[1]].run_time) {
		if (mode==1) {
			pt(t);
			printf("进程%s运行结束\n",job[que_pro[1]].name);
		}
		job[que_pro[1]].finish_time=t;
		Release(que_pro[1]);
		mag_num+=job[que_pro[1]].mag;
		for (int i=1; i<que_pro[0]; i++) {
			que_pro[i]=que_pro[i+1];
		}
		que_pro[0]--;

	}

}

void print_info(int t) {
	printf("剩余磁带机%d部\n\n",mag_num);
	if (que_pro[0]==0) {
		printf("当前没有正在运行的进程\n");
	} else {
		printf("当前运行程序\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("|进程名称   |估计运行时间  |  内存分配   |  已运行时间 |  优先级   |\n");
		printf("--------------------------------------------------------------------------------\n");
		for (int i=1; i<=1; i++) {
			int pri=-1;
			if ((pro_alg>=4)&& (pro_alg<=7)) {
				if (pro_alg>=6)
					pri=pro_calc6(t,que_pro[i]);
				else
					pri=job[que_pro[i]].pri;
			}
			printf("|    %s   |      %d      |    %d - %d    |     %d      |    %d    |\n",job[que_pro[i]].name,job[que_pro[i]].run_time,job[que_pro[i]].start,job[que_pro[i]].start+job[que_pro[i]].size,job[que_pro[i]].work_time,pri);
		}
	}
	puts("");
	if (que_pro[0]<=1) {
		printf("当前进程等待队列为空\n");
	} else {
		printf("进程等待队列状态:\n");

		printf("--------------------------------------------------------------------------------\n");
		printf("| 进程名称  |估计运行时间  | 内存分配    |  已运行时间 |  优先级   |\n");
		printf("--------------------------------------------------------------------------------\n");
		for (int i=2; i<=que_pro[0]; i++) {
			int pri=-1;
			if ((pro_alg>=4)&& (pro_alg<=7)) {
				if (pro_alg>=6)
					pri=pro_calc6(t,que_pro[i]);
				else
					pri=job[que_pro[i]].pri;
			}
			printf("|   %s    |     %d       |    %d - %d    |     %d       |     %d     |\n",job[que_pro[i]].name,job[que_pro[i]].run_time,job[que_pro[i]].start,job[que_pro[i]].start+job[que_pro[i]].size,job[que_pro[i]].work_time,pri);
		}
	}
	puts("");
	if (que_job[0]==0) {
		printf("当前作业等待队列为空\n");
	} else {
		printf("作业等待队列状态:\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("|  作业名称 |  估计运行时间 |  需要磁带机的数量 |  优先级   |   响应比      |\n");
		for (int i=1; i<=que_job[0]; i++) {
			int pri=-1;
			double tmp=-1.0;
			if (job_alg==3) pri=job[que_job[i]].pri;
			else if (job_alg==4) tmp=job_calc4(t,que_job[i]);
			printf("|   %s    |      %d       |        %d          |    %d     |   %f   |\n",job[que_job[i]].name,job[que_job[i]].run_time,job[que_job[i]].mag,pri,tmp);
		}

	}
	system("pause");
	write_line();
}



void gointoque(int t) {
	while ((que_job[0]>0) && (job[que_job[1]].mag<=mag_num) && Insert(que_job[1])) {
		mag_num-=job[que_job[1]].mag;
		if (mode==1) {
			pt(t);
			printf("作业%s进入了进程等待队列中\n",job[que_job[1]].name);
		}
		job[que_job[1]].state='P';
		job[que_job[1]].insert_time=t;
		que_pro[++que_pro[0]]=que_job[1];
		for (int i=1; i<que_job[0]; i++) {
			que_job[i]=que_job[i+1];
		}
		que_job[0]--;
	}

}


void work() {


	print_tag=false;
	for (int i=0; i<100000; i++) {

		jobCome(i);
		refresh_job_que(i);
		run_pro(i);
		gointoque(i);
		refresh_pro_que(i);

		if (mode == 1 && print_tag) {
			print_info(i);
			print_tag=false;
		}
	}
	if (mode==1) {
		write_line();
		printf("运行结束");
		double ans=0;
		for (int i=1; i<=job_num; i++)
			ans=ans+(job[i].finish_time-job[i].reach_time);
		printf("平均周转时间为%f分钟\n",ans/job_num);
	} else {
		write_line();
		printf("作业调度：");
		cout << job_alg_list[job_alg]<<endl;
		printf("进程调度：");
		cout << pro_alg_list[pro_alg]<<endl;
		double ans=0;
		for (int i=1; i<=job_num; i++)
			ans=ans+(job[i].finish_time-job[i].reach_time);
		printf("平均周转时间为%f分钟\n",ans/job_num);
	}
}

int main() {
	//freopen("a.in","r",stdin);
	while (true) {
		read_mode();
		read_init();
		init();
		if (mode==2) {

			for (int i=1; i<=4; i++)
				for (int j=1; j<=8; j++) {
					job_alg=i;
					pro_alg=j;
					init();
					work();
				}
		} else {
			init();
			work();
		}
		system("pause");

	}
	return 0;
}

