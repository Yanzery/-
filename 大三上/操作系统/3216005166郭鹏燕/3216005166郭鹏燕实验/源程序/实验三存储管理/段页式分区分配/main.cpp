#include<iostream>
#include<string>
using namespace std;

typedef struct Quick
{
int qs;//���κ�
int qp;//���ҳ��
int qb;//���κ�
}Quick;

typedef struct Data
{
int num;//�ڴ�Ŀ���
string str;//��Ӧ���ݿ����ҵ���ݣ������˵������Ϊһ���ַ���
}Data;
//ҳ��
typedef struct Page
{
int num;//ҳ��
int flag;//ҳ״̬�����Ƿ����ڴ档
int block;//��ҳ��Ӧ�Ŀ��
}Page;

typedef struct Stack
{
int num;//�κ�
int flag;//��״̬
int plen;//ҳ����
int psta;//ҳ��ʼַ
}Stack;
//�α�Ĵ���
typedef struct Stare
{
int ssta;//�α�ʼַ
int slen;//�α���
}Stare;
Stack ss[10];////ȫ�ֱ���
    Stare st;///////ȫ�ֱ���
    Data work[20];//ȫ�ֱ���
Quick qu;//////ȫ�ֱ���
Page page[5][5];
bool menuflag=0;
int bbs;//�ڴ���С
int bs;//�ڴ��С
void menu();
void start();
void change();
int main()
{ 
menu();
return 0;
}
void menu()
{
    cout<<"��ѡ��:"<<endl;
cout<<endl;
cout<<"    1����ʼ����         "<<endl;
cout<<"    2�������ַת��       "<<endl;
cout<<"    3���˳�               "<<endl;
int menu1;
cin>>menu1;
if(menu1!=1&&menu1!=2&&menu1!=3)
{
cout<<"��������ȷ��ѡ��"<<endl;
menu();
} 
switch(menu1)
{
case 1:
{
 menuflag=1;
 start();
 break;}
case 2:
{
if(menuflag==0) 
{
cout<<"���ʼ����"<<endl;
menu();

}
change();
break;
}
case 3:return;
}//switch

}  
void start()
{
            cout<<"�������ڴ��С(K)"<<endl;
            cin>>bs;
         cout<<"�������ڴ��Ĵ�С(k)"<<endl;
            cin>>bbs;
       int blocknum;
      blocknum=bs/bbs;
      cout<<"�ڴ�һ������Ϊ"<<blocknum<<"�飬ÿ��"<<bbs<<"k"<<"һ��"<<bs<<"k"<<endl;
      cout<<"��������̸���"<<endl;
      int pn;cin>>pn;
      //���������н��̵��ܶ����Ͷα�,��Ϊÿ�δ���ҳ��
      int sums=0;
      for (int pn1=0;pn1<pn;pn1++)
      {
      cout<<"�������"<<pn1<<"�����̵Ķ���"<<endl;
      int ppn;cin>>ppn;
      sums+=ppn;
      }
      for(int ss1=0;ss1<sums;ss1++)
      {
      cout<<"�������"<<ss1<<"���α����ݣ��κţ�״̬��ҳ���ȣ�ҳ��ʼַ"<<endl;
      cin>>ss[ss1].num>>ss[ss1].flag>>ss[ss1].plen>>ss[ss1].psta;
      cout<<"���ʼ����"<<ss1<<"�ε�ҳ��������������ҳ��״̬�Ͷ�Ӧ���"<<endl;
      for(int sss1=0;sss1<ss[ss1].plen;sss1++)
      {
      page[ss1][sss1].num=sss1;
      cout<<"������öε�"<<sss1<<"��ҳ���ҳ��״̬�Ͷ�Ӧ���"<<endl;
      cin>>page[ss1][sss1].flag>>page[ss1][sss1].block;
      }

      }
      //��ʼ���α�Ĵ���
      cout<<"��ʼ���α�Ĵ����Ķα�ʼַ"<<endl;
      cin>>st.ssta;
      st.slen=sums;
        //��ʼ���ڴ��������ַÿһ���������
     cout<<"����������Ƕ������ַ��ÿһ�����ַ������м򵥵ĳ�ʼ����û�о��嵽ÿһ�����ַ"<<endl;
      for (int bn=0;bn<blocknum;bn++)
      {
      work[bn].num=bn;
      cout<<"�������"<<bn<<"���ڴ�������ҵ����"<<endl;
      cin>>work[bn].str; 
      }
//��ʼ�����
cout<<"����������ǳ�ʼ�����ֻ��һ��"<<endl;
cout<<"������Ҫ��Ϊ���Ķκź�ҳ��"<<endl;
cin>>qu.qb>>qu.qp;
while(ss[qu.qb].flag!=1||page[qu.qb][qu.qp].flag!=1)
{
cout<<"��ҳ�����ڴ�������һҳ���ڴ��е���Ϊ���,������Ҫ��Ϊ���Ķκź�ҳ��"<<endl;
    cin>>qu.qb>>qu.qp;

}
qu.qs=page[qu.qb][qu.qp].block;
menu();
}
void change()
{
             cout<<"������Ҫת�����߼���ַ���κ�s������ҳ��p��ҳ��ƫ�Ƶ�ַd(B)"<<endl;
 int snum,pnum,dnum;
 cin>>snum>>pnum>>dnum;
 //���Ȳ���
 if(snum==qu.qb&&pnum==qu.qp)
 {
 cout<<"�������"<<"��Ӧ�����"<<qu.qs<<endl;
 cout<<"�ÿ�����ҵ������"<<work[page[qu.qb][qu.qp].block].str<<endl;
 cout<<"�����ַ��"<<qu.qs*bbs*1024+dnum<<endl;;
 menu();
 }
 //���ʶα�Ĵ���
 else
 {
 cout<<"���û������,���ʶα�Ĵ������κŵ��ڶα�ʼַ����ƫ�Ƶ�ַ"<<endl;
 int ssnum;
                 ssnum=st.ssta+snum;
 if(ssnum>st.slen-1)
 {
 cout<<"Խ���ж�"<<endl;
 menu();
 }
 //���ʶα�
 else
 {
 if(ssnum>=0&&ssnum<=st.slen-1)
 {
 //�Ƿ�ȱ��
 cout<<"�α���Ч"<<endl;
 if(ss[ssnum].flag==0)
 {
 cout<<"ȱ���ж�"<<endl;
 menu();
 }
 else
 {
 //��ѯҳ�����ݶκŲ��ҳ��ʼַ�����϶���ƫ��ҳ�������õ�ҳ���
 //ȱҳ�жϲ���
 if(pnum>ss[ssnum].plen-1)
 {
 cout<<"ȱҳ�ж�"<<endl;
 menu();
 }
 else
 {
 if(pnum>=0&&pnum<=ss[ssnum].plen-1)
 {
 if(page[ssnum][pnum].flag==0)
 {
 cout<<"ȱҳ�ж�"<<endl;
 menu();
 }
 else
 {
 cout<<"�ҵ���ҳ"<<"��ѯҳ����Ӧ���"<<page[ssnum][pnum].block<<endl;
 cout<<"�ÿ��ڴ��������"<<work[page[ssnum][pnum].block].str<<endl;
 cout<<"ת���õ��������ַ�ǣ�"<<page[ssnum][pnum].block*bbs*1024+dnum<<endl;
     menu();
	  } } } }}} }}

