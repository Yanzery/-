#include <cstdlib>
#include <cstdio>
#include <iostream>
 
#define TRUE 1
#define FALSE 0
#define STATUS int
#define KeyType int
#define OK 1
#define ERROR 0

const int m=3;  //B���Ľ� 

typedef struct BTNode
{
	int keynum;        //�ڵ�ؼ��ֵĸ��� 
	KeyType key[m+1];  //�ؼ�������,key[0]δ��
	BTNode *parent;    //˫�׽ڵ�ָ��
	BTNode *ptr [m+1];
	//Record *receptr[m+1];
} BTNode ,*BTree;

typedef struct 
{
	BTree pt;   //ָ���ҵ��Ľڵ�
	int i;      // 1<=i<=n,�ڽڵ��е� �ؼ���λ��
	int tag;    // 1: ���ҳɹ���0������ʧ�� 
} result;

char ch[25][120];   //����ʵ��B���Ŀ��ӻ���ʾ
const int Maxdeep=3; //����ʵ��B���Ŀ��ӻ���ʾ������B����������

void draw_line(int x1,int y1,int x2,int y2) //��B����һ����,��ch����������(x1,y1)��(x2,y2)
{
	int sta,en,i;
	if (y1>y2){sta=y2;en=y1;} else {sta=y1;en=y2;}
	for (i=sta;i<=en;i++) ch[x1][i]='-';
	for (i=x1;i<=x2;i++) ch[i][y2]='|';
}

void draw_node(BTree p,int x,int y)  //��B����һ���ڵ� 
{
	int i;
	for (i=x;i<=x+2;i++) 
	{
		ch[i][y]='*';
		ch[i][y+9]='*';
	}
	for (i=y;i<=y+9;i++) 
	{
		ch[x][i]='*';
		ch[x+2][i]='*';
	}
	if (p->keynum==1)  //ֻ���������� 
	{
		if (((p->key[1])/10)!=0) ch[x+1][y+4]='0'+((p->key[1])/10);
		ch[x+1][y+5]='0'+((p->key[1])%10);
	} 
	else               // ���������� 
	{
		if (((p->key[1])/10)!=0) ch[x+1][y+1]='0'+((p->key[1])/10);
		ch[x+1][y+2]='0'+((p->key[1])%10);
		if (((p->key[2])/10)!=0) ch[x+1][y+7]='0'+((p->key[2])/10);
		ch[x+1][y+8]='0'+((p->key[2])%10);
	}
}

void dfs(BTree p,int x,int y,int fax,int fay)
{
	if (p==NULL)  return ;
	int i;
	int nowx=x;
	int nowy=y;
	int now=x;
	for (;now<Maxdeep;now++)    //������������������ 
	 nowy=(nowy-1)*3+2;
	if (fax!=-1)
	{
		int upx=(nowx-1)*6;
		int upy=(nowy-1)*12+5;
		draw_line(fax,fay,upx,upy);		//����˫�׽ڵ㵽�ýڵ�� 
	}
	draw_node(p,(nowx-1)*6,(nowy-1)*12);
	if (p->keynum==1)          //ֻ���������� 
	{
		dfs(p->ptr[0],x+1,(y-1)*3+1,(nowx-1)*6+1,(nowy-1)*12-1);
		dfs(p->ptr[1],x+1,(y-1)*3+3,(nowx-1)*6+1,(nowy-1)*12+10);
	}
	else                      // ���������� 
	{
		dfs(p->ptr[0],x+1,(y-1)*3+1,(nowx-1)*6+1,(nowy-1)*12-1);
		dfs(p->ptr[1],x+1,(y-1)*3+2,(nowx-1)*6+3,(nowy-1)*12+5);
		dfs(p->ptr[2],x+1,(y-1)*3+3,(nowx-1)*6+1,(nowy-1)*12+10);
	}
}

void show(BTree root)   //���ף��������Ϊ�����B���Ŀ��ӻ�����ʾ 
{
	
	if (root==NULL) 
	{
		printf("the tree is empty\n");
	}
	else
	{ 
	
		for (int i=0;i<=23;i++)        //��ͼ���ȷ���һ��ch�����У����������������� 
		 for (int j=0;j<=108;j++)
		  ch[i][j]=' ';
		dfs(root,1,1,-1,-1);
		int Maxx=0;
		int Miny=10000;
		for (int i=0;i<=23;i++)
		 for (int j=0;j<=108;j++)
		  if (ch[i][j]!=' ') Maxx=i;
	    
		for (int i=0;i<=Maxx;i++)
		{
		 for (int j=0;j<=108;j++)
		  printf("%c",ch[i][j]);
		 printf("\n");
	    }
	}
	for (int i=0;i<=108;i++) printf("+");  
	printf("\n");
}



int Search(BTree p,KeyType k)  // ��p->key[1..p->keynum]��xʹ��p->key[x]>=k ,���û�з���p->keynum+1
{
	int i=1;
	while (i<=p->keynum && k>p->key[i]) i++;
	return i;
}

void SearchBTree(BTree t, KeyType k,result &r) 
//��m��b���ϲ��ҹؼ���k����r����(pt,i,tag) 
//�����ҳɹ�������tag=1,ָ��pt��ָ����е�i���ؼ��ֵ���k
//����tag=0�� ��Ҫ����ؼ���Ϊk�ļ�¼��Ӧλ��pt����е�i-1�͵�i���ؼ���֮�� 
{
	int i=0,found=0;
	BTree p=t,q=NULL;  //��ʼ��pָ������; p�����ڴ�����,q ָ��˫��
	while (p!=NULL && found==0)
	{
		i = Search (p,k);  // ��p->key[1..p->keynum]�в��� ��p->key[i-1]<k<=p->key[i]
		if (i<=p->keynum && p->key[i]==k) found =1; // �ҵ�����ؼ��� 
		else {q=p;p=p->ptr[i-1];}
	}	
	if (found==1) // ���ҳɹ� ,����k��λ��p��i 
	{
		r.pt=p; r.i=i; r.tag=1;
	}
	else   //���Ҳ��ɹ�������k�Ĳ���λ��q��i 
	{
  		r.pt=q; r.i=i; r.tag=0;
	}
}

STATUS FindIsExist(BTree &root,KeyType k)   //����B�����Ƿ���ֹؼ���Ϊk�Ľڵ�
{
	result r; 
	SearchBTree(root,k,r);
	if (r.tag==1) return TRUE;
	return FALSE;
}

void Insert(BTree &q,int i,KeyType x,BTree ap)
//�ؼ���x���½ڵ�ָ��ap�ֱ�嵽q-> key[i]�� q->ptr[i]
{
	int j,n=q->keynum;
	for (j=n;j>=i;j--)
	{
		q->key[j+1]=q->key[j];
		q->ptr[j+1]=q->ptr[j]; 
	} 	
	q->key[i]=x; q->ptr[i]=ap;
	if (ap!=NULL) ap->parent =q;
	q->keynum++;
}

void newRoot(BTree &t,BTree p,KeyType x,BTree ap)  
//�����µĸ��ڵ㣬x�ǹؼ��֣�p�ǵ�һ�����ӣ�ap�ǵڶ������� 
{
	t = (BTNode *) malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0]=p; t->ptr[1]=ap; t->key[1]=x;
	if (p!=NULL) p->parent =t;
	if (ap!=NULL) ap->parent =t;
	t->parent=NULL;               //�¸���˫�׽ڵ��ǿսڵ� 
}


void split(BTree &q,int s,BTree &ap)
//��q�����ѳ�������㣬���±�sΪ�ֽ磬ǰһ�뱣����Դ�ڵ㣬��һ��������ָ�½ڵ� 
{
	int i,j,n=q->keynum;
	ap = (BTNode* ) malloc (sizeof(BTNode));  // �����½ڵ� 
	 
	ap->ptr[0]=q->ptr[s];
	for (i=s+1,j=1;i<=n;i++,j++)
	{
		ap->key[j]=q->key[i];
		ap->ptr[j]=q->ptr[i]; 
	}
	
	ap->keynum=n-s;
	ap->parent =q->parent;
	for (i=0;i<=n-s;i++)
		if (ap->ptr[i]!=NULL) ap->ptr[i]->parent =ap;
	q->keynum=s-1;
}

void InsertBTree(BTree &t,KeyType k,BTree q,int i)
// ��B��t��q����key[i-1]��key[i]֮�����ؼ���k
//���������ؼ��ָ�������B���Ľף�����˫��ָ�������н����ѣ�ʹt����m��B�� 
{
	int x,s,finished=0,needNewRoot=0;
	BTree ap;
	if (q==NULL) newRoot(t,NULL,k,NULL);  // �����µĸ��ڵ�
	else 
	{
		x=k;ap=NULL;
		while (needNewRoot==0 && finished==0)
		{
			Insert(q,i,x,ap);    //x��ap�ֱ�嵽q->key[i]��q->ptr[i]
			if (q->keynum <m)  finished=1; // �������
			else
			{
				s=(m+1)/2; split(q,s,ap); x=q->key[s];
				if (q->parent!=NULL)
				{
					q=q->parent; i=Search(q,x);
				}
				else needNewRoot=1;
			}
		}
		if (needNewRoot) newRoot(t,q,x,ap);
	}
}

STATUS InsertNewNumber(BTree &root,KeyType k)   //��B���в���һ���ؼ���k 
{
	result r; 
	SearchBTree(root,k,r);
	printf("����%d:\n",k);
	if (r.tag==1) 
	{
		printf("���󣬸ùؼ����Ѵ���\n");
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");		
		return ERROR; //����ùؼ����Ѿ����ڸ�B����
	}
	InsertBTree(root,k,r.pt,r.i);
	show(root);   //��ʾ����
	return OK;
}



void Successor(BTree &p,int i) //�ҵ� p->ptr[i]�����������Ĺؼ��ֲ����p->key[i]��ֵ
{
	result r; 
	SearchBTree(p->ptr[i],p->key[i],r);   //��Ϊ p->ptr[i]�е�Ԫ��һ����p->key[i],���� SearchBTree(p->ptr[i],p->key[i],r)���ҵ���С�� ���²���ն˽ڵ� 
	int temp;
	p->key[i]=r.pt->key[1];    
	p=r.pt;
}

void Remove(BTree &q,int i) //��B���ڵ���ɾ���±�Ϊi�Ĺؼ���
{
	int j,n=q->keynum;
	for (j=i;j<n;j++)               //���±�Ϊj�Ժ��key��point ��ǰ�� 
	{
		q->key[j]=q->key[j+1];
		q->ptr[j]=q->ptr[j+1]; 
	} 
	q->keynum--;
}

void Merge(BTree go,int i) //��B���ڵ�go�е�ptr[i-1]��key[i]��ptr[i]����ͬһ���ڵ�
{
	BTree p=go->ptr[i-1];
	BTree q=go->ptr[i];
	int n=p->keynum;
	
	n++;                          //key[i]����p�ڵ�ĺ���
	p->key[n]=go->key[i];
	p->ptr[n]=q->ptr[0];
	if (p->ptr[n]!=NULL) (p->ptr[n])->parent=p;
	
	int j;                        
	for (j=1;j<=q->keynum;j++) //q�ڵ�����ݷ���p�ڵ�ĺ���
	{
		n++;
		p->key[n]=q->key[j];
		p->ptr[n]=q->ptr[j];
		if (p->ptr[n]!=NULL) (p->ptr[n])->parent=p;
	}
	
	p->keynum=n;
	
	free(q);
	
	for (j=i;j<go->keynum;j++)  //��go�ڵ���ɾ���±�Ϊi�Ĺؼ���
	{
		go->key[j]=go->key[j+1];
		go->ptr[j]=go->ptr[j+1];
	}
	go->keynum--;
	
}

void Restore(BTree &root,BTree p)  //�ڸ��ڵ�Ϊroot��B���е���p�ڵ�ʹ������B��������
{
	BTree par;
	par=p->parent; 
	int i;
	if (par==NULL)  //root�ڵ��Ǹ��ڵ�
	{
		if (p->keynum==0)   //���ڵ�Ϊ��
		{
			root=p->ptr[0];
			if (root!=NULL)
			root->parent=NULL;
			free(p);
		}
		return ;
	}
	for (i=1;i<=par->keynum;i++)
	 if (par->key[i]>p->key[1]) break;
	i--;                  //�ҵ�par��p��λ��
	if (i==0)             //���p��par��ptr[0]
	{
		BTree q=par->ptr[i+1];
		if (q->keynum>(m-1)/2)
		{
			
			p->keynum++;                        //�� par->key[i+1]�����ֵ������� ptr[0]����p���ĺ��� 
			p->key[p->keynum]=par->key[i+1];
			p->ptr[p->keynum]=q->ptr[0];
			if (p->ptr[p->keynum]!=NULL) (p->ptr[p->keynum])->parent=p;
  
			par->key[i+1]=q->key[1];  //����˫�׽ڵ�ؼ��� 
			
			int j;                     // ɾ��q�ĵ�һ���ؼ��ֺ�ptr[0] 
			q->ptr[0]=q->ptr[1];                    
			for (j=1;j<q->keynum;j++)
			{
			   q->key[j]=q->key[j+1];	
			   q->ptr[j]=q->ptr[j+1];
			}
			q->keynum--;
	    }
		else
		{
			Merge(par,1); //�ϲ�par��ptr[0]��key[0]��ptr[1]
		}
	}
	else
	{
		 BTree q=par->ptr[i-1];
		if (q->keynum>(m-1)/2)
		{	
		
		  int j;                        //�����ֵ����������һ��ptr��par->keynum[i]����p�ڵ��ǰ��	 
		  for (j=p->keynum+1;j>=2;j--)
		  {
		  	p->key[j]=p->key[j-1];
		  	p->ptr[j]=p->ptr[j-1];
		  }
		  p->ptr[1]=p->ptr[0];
		  p->key[1]=par->key[i];
		  p->ptr[0]=q->ptr[q->keynum]; 
		  if (p->ptr[0]!=NULL) (p->ptr[0])->parent=p;
		  p->keynum++;             	
		  
		  par->key[i]=q->key[q->keynum]; //����˫�׽ڵ�ؼ��� 
		  q->keynum--;	                  // ɾ��q�ĵ����һ���ؼ��ֺ�ptr
	    }
	    else
	    {
	    	Merge(par,i);    //�ϲ�par��ptr[i-1]��key[i]��ptr[i]
	    }
	}
	if (par->keynum<(m-1)/2)  Restore(root,par); //���par�ڵ���Ҫ����������ƵĽ��е���
}


void DeleteBTree(BTree &root,BTree p,int i)  //�ڸ�Ϊroot��B����ɾ��p�ڵ�ĵ�i���ؼ���
{
	if (p->ptr[i]!=NULL)
	{
		Successor(p,i);                //�ҵ� p->ptr[i]�����������Ĺؼ��ֲ����p->key[i]��ֵ 
		DeleteBTree(root,p,1);     //ת��Ϊ p->ptr[i]�����������Ĺؼ���
	}
	else
	{
		Remove(p,i);              //ɾ����i���ؼ��� 
		if (p->keynum<(m-1)/2)
		  Restore(root,p);       //�ڸ��ڵ�Ϊroot��B���е���p�ڵ㼰�����Ľڵ�ʹ������B��������
	}
} 

STATUS DeleteNumber(BTree &root,KeyType k)   //��B����ɾ���ؼ���Ϊk�Ľڵ�
{
	result r; 
	SearchBTree(root,k,r);
	printf("ɾ��%d:\n",k);
	if (r.tag==0) 
	{
		printf("���󣬸ùؼ��ֲ�����\n");
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
		return ERROR; //�������B�����ڵĹؼ���Ϊk�Ľڵ㣬����
	}
	DeleteBTree(root,r.pt,r.i); 
	
	show(root);   //��ʾ����
	return OK; 
}

void Distory(BTree &root) //���ٸ��ڵ�Ϊroot��B�� 
{
	if (root==NULL) return ;
	int i;
	for (int i=0;i<=root->keynum;i++) //ö��root������
	{
		Distory(root->ptr[i]);    //����root������
	}
	free(root);
	root=NULL;
}


int main()
{

    BTree root=NULL;
    int n;
    for (int i=0;i<=108;i++) printf("+");
	printf("\n");

	InsertNewNumber(root,1);
	InsertNewNumber(root,2);
	InsertNewNumber(root,3);
	InsertNewNumber(root,4);
	InsertNewNumber(root,5);
	InsertNewNumber(root,6);
	InsertNewNumber(root,7);
	InsertNewNumber(root,8);
	InsertNewNumber(root,9);

    DeleteNumber(root,1);
    DeleteNumber(root,2);
    DeleteNumber(root,4);
    DeleteNumber(root,6);
    
    InsertNewNumber(root,5);
    DeleteNumber(root,6);
    
    int x=5;
    printf("���ҹؼ���%d:\n",x); 
    if (FindIsExist(root,x)==TRUE) 
	{
		printf("�ؼ���%d����\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	else
	{
		printf("�ؼ���%d������\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	
	x=6;
	printf("���ҹؼ���%d:\n",x); 
	if (FindIsExist(root,x)==TRUE) 
	{
		printf("�ؼ���%d����\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	else
	{
		printf("�ؼ���%d������\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	printf("����B����\n"); 
	Distory(root);
	show(root);
	while (true);
	return 0;
}

