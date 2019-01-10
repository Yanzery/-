// ConsoleApplication11.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <bits/stdc++.h>
#include <queue>
#include <algorithm>


#define getpch(type) (type*)malloc(sizeof(type))

const int maxdot=100000;

using namespace std;

const string job_alg_list[]= {"","1.�����ȷ�������㷨","2.�����ҵ���ȵ����㷨","3.���ȼ������㷨","4.����Ӧ�����ȵ����㷨"};
const string pro_alg_list[]= {"","1.�����ȷ����㷨","2.�̽�������(����ռ)","3.�̽�������(������ռ)","4.��̬���ȼ������㷨(����ռ)","5.��̬���ȼ������㷨(������ռ)","6.��̬���ȼ������㷨(����ռ)","7.��̬���ȼ������㷨��������ռ��","8.��ת�����㷨�����㷨"};

int mag_num,mode;
int job_num,job_alg,pro_alg;
int que_job[maxdot],que_pro[maxdot];
int input_mode;
bool print_tag;
struct TNode {
	char name[10];         //��ҵ����
	int reach_time,         //����ʱ��
  int run_time,          //Ԥ������ʱ��
  int work_time         //��ǰ�Ѿ����е�ʱ��
  int mem             //ʹ���ڴ�Ĵ�С
  int mag;	             //ʹ�ôŴ����ĸ���
	int finish_time;        //������ɵ�ʱ��
	int insert_time;       //��ҵ������̵ȴ����е�ʱ��
	int pri;              //���ȼ�
	char state;           //��ǰ��ҵ���ĸ�λ�ã�"U"��ʾ��û���'J'��ʾ����ҵ�ȴ����У�'P'��ʾ�ڽ��̵ȴ��������棩
	int start,size;         //�ý��̷��䵽���ڴ����ʼλ�úʹ�С

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
		if (mode ==1)printf("��ҵ%s�Ž����ڴ��ַΪ%d��%d�Ŀռ�\n",job[x].name,job[x].start,job[x].start+job[x].size);
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
		if (t%60<10) printf("��%d��0%d��ʱ��:\n",t/60,t%60);
		else printf("��%d��%d��ʱ��:\n",t/60,t%60);
		print_tag=true;
	}
}

void read_init() {

	write_line();
	mem_head=getpch(TMem);

	puts("������Ϣ¼��");
	mem_head->start=0;
	mem_head->link=NULL;
	printf("�������ڴ��С(K):");
	scanf("%d",&mem_head->size);
	printf("������Ŵ�������:");
	scanf("%d",&mag_num);
	printf("��������ҵ�ĸ���:");
	scanf("%d",&job_num);
	if (mode ==2 || job_alg==3 || (pro_alg>=4 && pro_alg<=7)) {
		printf("�밴��\"��ҵ�� ����ʱ��(hh:mm) ��������ʱ�䣨min�� �ڴ���Ҫ��K�� �Ŵ�����Ҫ(̨) ���ȼ�(����Խ�����ȼ�Խ��)\"��˳������\n");
		for (int i=1; i<=job_num; i++) {
			int reach_hour,reach_minute;
			scanf("%s %d:%d %d %d %d %d",job[i].name,&reach_hour,&reach_minute,&job[i].run_time,&job[i].size,&job[i].mag,&job[i].pri);
			job[i].reach_time=reach_hour*60+reach_minute;

		}
	} else {
		printf("�밴��\"��ҵ�� ����ʱ��(hh:mm) ��������ʱ�䣨min�� �ڴ���Ҫ��K�� �Ŵ�����Ҫ(̨)\"��˳������\n");
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
	printf("1.��ͨģʽ\n2.�Ա�ģʽ\n��������Ҫִ�е�ģʽ��");
	scanf("%d",&mode);
	write_line();
	if (mode==2) return ;
	printf("��ҵ���ȵ��㷨�У�\n1.�����ȷ�������㷨\n2.��С��ҵ���ȵ����㷨\n3.���ȼ������㷨\n4.����Ӧ�����ȵ����㷨\n��������Ҫѡ�����ҵ�����㷨�����:");
	scanf("%d",&job_alg);
	write_line();
	printf("���̵��ȵ��㷨�У�\n1.�����ȷ����㷨\n2.�̽�������(����ռ)\n3.�̽�������(������ռ)\n4.��̬���ȼ������㷨(����ռ)\n5.��̬���ȼ������㷨(������ռ)\n6.��̬���ȼ������㷨(����ռ)\n7.��̬���ȼ������㷨��������ռ��\n8.��ת�����㷨�����㷨\n��������Ҫѡ��Ľ��̵����㷨�����:");
	scanf("%d",&pro_alg);
	write_line();
}



void jobCome(int t) {
	for (int i=1; i<=job_num; i++) {
		if ((job[i].state=='U') && (job[i].reach_time==t)) {
			que_job[++que_job[0]]=i;
			if (mode ==1) {
				pt(t);
				printf("��ҵ%s����,������ҵ�ȴ�����\n\n",job[i].name);
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

//1.�����ȷ����㷨\n2.�̽�������(����ռ)3.�̽�������(������ռ)\n4.��̬���ȼ������㷨(����ռ)\n5.��̬���ȼ������㷨(������ռ)6.��̬���ȼ������㷨������ռ��\n7.��̬���ȼ������㷨��������ռ��8.��ת�����㷨�����㷨\n9.�༶�������е����㷨\n"
void refresh_pro_que(int t) {
	bool boo=false;;
	switch(pro_alg) {
		case 1:  //1.�����ȷ����㷨
			break;
		case 2:  //2.�̽�������(����ռ)
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc2(que_pro[i])>pro_calc2(que_pro[j])) {

						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;

		case 3://�̽�������(������ռ)
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc3(que_pro[i])>pro_calc3(que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 4://4.��̬���ȼ������㷨(����ռ)
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc4(que_pro[i])<pro_calc4(que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 5://5.��̬���ȼ������㷨(������ռ)
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (job[que_pro[i]].pri<job[que_pro[j]].pri) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}
			break;
		case 6://6.��̬���ȼ������㷨������ռ��
			for (int i=1; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc6(t,que_pro[i])<pro_calc6(t,que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}

			break;
		case 7://7.��̬���ȼ������㷨��������ռ��
			for (int i=2; i<=que_pro[0]; i++)
				for (int j=i+1; j<=que_pro[0]; j++)
					if (pro_calc7(t,que_pro[i])<pro_calc7(t,que_pro[j])) {
						boo=true;
						swap(que_pro[i],que_pro[j]);
					}

			break;
		case 8: //8.��ת�����㷨�����㷨
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
		printf("���̵ȴ����з����˽���\n");
	}
}

double job_calc4(int t,int i) {
	return (t-job[i].reach_time+job[i].run_time*1.0)/job[i].run_time;
}


void refresh_job_que(int t) {
	bool boo=false;

	switch (job_alg) {
		case 1://1.�����ȷ�������㷨
			break;
		case 2://2.��С��ҵ���ȵ����㷨
			for (int i=1; i<=que_job[0]; i++)
				for (int j=i+1; j<=que_job[0]; j++)
					if (job[que_job[i]].run_time>job[que_job[j]].run_time) {
						boo=true;
						swap(que_job[i],que_job[j]);
					}
			break;
		case 3://3.���ȼ������㷨
			for (int i=1; i<=que_job[0]; i++)
				for (int j=i+1; j<=que_job[0]; j++)
					if (job[que_job[i]].pri<job[que_job[j]].pri) {
						boo=true;
						swap(que_job[i],que_job[j]);
					}
			break;
		case 4://4.����Ӧ�����ȵ����㷨
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
		printf("��ҵ�ȴ����з����˽���\n");
	}

}


void run_pro(int t) {
	if (que_pro[0]==0) return ;
	job[que_pro[1]].work_time++;
	if (job[que_pro[1]].work_time>=job[que_pro[1]].run_time) {
		if (mode==1) {
			pt(t);
			printf("����%s���н���\n",job[que_pro[1]].name);
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
	printf("ʣ��Ŵ���%d��\n\n",mag_num);
	if (que_pro[0]==0) {
		printf("��ǰû���������еĽ���\n");
	} else {
		printf("��ǰ���г���\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("|��������   |��������ʱ��  |  �ڴ����   |  ������ʱ�� |  ���ȼ�   |\n");
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
		printf("��ǰ���̵ȴ�����Ϊ��\n");
	} else {
		printf("���̵ȴ�����״̬:\n");

		printf("--------------------------------------------------------------------------------\n");
		printf("| ��������  |��������ʱ��  | �ڴ����    |  ������ʱ�� |  ���ȼ�   |\n");
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
		printf("��ǰ��ҵ�ȴ�����Ϊ��\n");
	} else {
		printf("��ҵ�ȴ�����״̬:\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("|  ��ҵ���� |  ��������ʱ�� |  ��Ҫ�Ŵ��������� |  ���ȼ�   |   ��Ӧ��      |\n");
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
			printf("��ҵ%s�����˽��̵ȴ�������\n",job[que_job[1]].name);
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
		printf("���н���");
		double ans=0;
		for (int i=1; i<=job_num; i++)
			ans=ans+(job[i].finish_time-job[i].reach_time);
		printf("ƽ����תʱ��Ϊ%f����\n",ans/job_num);
	} else {
		write_line();
		printf("��ҵ���ȣ�");
		cout << job_alg_list[job_alg]<<endl;
		printf("���̵��ȣ�");
		cout << pro_alg_list[pro_alg]<<endl;
		double ans=0;
		for (int i=1; i<=job_num; i++)
			ans=ans+(job[i].finish_time-job[i].reach_time);
		printf("ƽ����תʱ��Ϊ%f����\n",ans/job_num);
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

