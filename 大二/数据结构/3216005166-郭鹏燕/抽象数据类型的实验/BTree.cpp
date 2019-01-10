#include <cstdlib>
#include <cstdio>
#include <iostream>
 
#define TRUE 1
#define FALSE 0
#define STATUS int
#define KeyType int
#define OK 1
#define ERROR 0

const int m=3;  //B树的阶 

typedef struct BTNode
{
	int keynum;        //节点关键字的个数 
	KeyType key[m+1];  //关键字数组,key[0]未用
	BTNode *parent;    //双亲节点指针
	BTNode *ptr [m+1];
	//Record *receptr[m+1];
} BTNode ,*BTree;

typedef struct 
{
	BTree pt;   //指向找到的节点
	int i;      // 1<=i<=n,在节点中的 关键字位序
	int tag;    // 1: 查找成功，0：查找失败 
} result;

char ch[25][120];   //用于实现B树的可视化显示
const int Maxdeep=3; //用于实现B树的可视化显示，限制B树的最大深度

void draw_line(int x1,int y1,int x2,int y2) //画B树的一条线,在ch数组里连接(x1,y1)和(x2,y2)
{
	int sta,en,i;
	if (y1>y2){sta=y2;en=y1;} else {sta=y1;en=y2;}
	for (i=sta;i<=en;i++) ch[x1][i]='-';
	for (i=x1;i<=x2;i++) ch[i][y2]='|';
}

void draw_node(BTree p,int x,int y)  //画B树的一个节点 
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
	if (p->keynum==1)  //只有两个儿子 
	{
		if (((p->key[1])/10)!=0) ch[x+1][y+4]='0'+((p->key[1])/10);
		ch[x+1][y+5]='0'+((p->key[1])%10);
	} 
	else               // 有三个儿子 
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
	for (;now<Maxdeep;now++)    //算出从左往右数的序号 
	 nowy=(nowy-1)*3+2;
	if (fax!=-1)
	{
		int upx=(nowx-1)*6;
		int upy=(nowy-1)*12+5;
		draw_line(fax,fay,upx,upy);		//画出双亲节点到该节点的 
	}
	draw_node(p,(nowx-1)*6,(nowy-1)*12);
	if (p->keynum==1)          //只有两个儿子 
	{
		dfs(p->ptr[0],x+1,(y-1)*3+1,(nowx-1)*6+1,(nowy-1)*12-1);
		dfs(p->ptr[1],x+1,(y-1)*3+3,(nowx-1)*6+1,(nowy-1)*12+10);
	}
	else                      // 有三个儿子 
	{
		dfs(p->ptr[0],x+1,(y-1)*3+1,(nowx-1)*6+1,(nowy-1)*12-1);
		dfs(p->ptr[1],x+1,(y-1)*3+2,(nowx-1)*6+3,(nowy-1)*12+5);
		dfs(p->ptr[2],x+1,(y-1)*3+3,(nowx-1)*6+1,(nowy-1)*12+10);
	}
}

void show(BTree root)   //三阶，层数最多为三层的B树的可视化的演示 
{
	
	if (root==NULL) 
	{
		printf("the tree is empty\n");
	}
	else
	{ 
	
		for (int i=0;i<=23;i++)        //该图形先放在一个ch数组中，最后再整个数组输出 
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



int Search(BTree p,KeyType k)  // 在p->key[1..p->keynum]找x使得p->key[x]>=k ,如果没有返回p->keynum+1
{
	int i=1;
	while (i<=p->keynum && k>p->key[i]) i++;
	return i;
}

void SearchBTree(BTree t, KeyType k,result &r) 
//在m阶b树上查找关键字k，用r返回(pt,i,tag) 
//若查找成功，则标记tag=1,指针pt所指结点中第i个关键字等于k
//否则tag=0， 若要插入关键字为k的记录，应位于pt结点中第i-1和第i个关键字之间 
{
	int i=0,found=0;
	BTree p=t,q=NULL;  //初始，p指向根结点; p将用于待查结点,q 指向双亲
	while (p!=NULL && found==0)
	{
		i = Search (p,k);  // 在p->key[1..p->keynum]中查找 在p->key[i-1]<k<=p->key[i]
		if (i<=p->keynum && p->key[i]==k) found =1; // 找到待查关键字 
		else {q=p;p=p->ptr[i-1];}
	}	
	if (found==1) // 查找成功 ,返回k的位置p及i 
	{
		r.pt=p; r.i=i; r.tag=1;
	}
	else   //查找不成功，返回k的插入位置q及i 
	{
  		r.pt=q; r.i=i; r.tag=0;
	}
}

STATUS FindIsExist(BTree &root,KeyType k)   //查找B树中是否出现关键字为k的节点
{
	result r; 
	SearchBTree(root,k,r);
	if (r.tag==1) return TRUE;
	return FALSE;
}

void Insert(BTree &q,int i,KeyType x,BTree ap)
//关键字x和新节点指针ap分别插到q-> key[i]和 q->ptr[i]
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
//生成新的根节点，x是关键字，p是第一个儿子，ap是第二个儿子 
{
	t = (BTNode *) malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0]=p; t->ptr[1]=ap; t->key[1]=x;
	if (p!=NULL) p->parent =t;
	if (ap!=NULL) ap->parent =t;
	t->parent=NULL;               //新根的双亲节点是空节点 
}


void split(BTree &q,int s,BTree &ap)
//将q结点分裂成两个结点，以下标s为分界，前一半保留在源节点，后一半移入所指新节点 
{
	int i,j,n=q->keynum;
	ap = (BTNode* ) malloc (sizeof(BTNode));  // 生成新节点 
	 
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
// 在B树t中q结点的key[i-1]和key[i]之间插入关键字k
//若插入后结点关键字个数等于B树的阶，则沿双亲指针链进行结点分裂，使t仍是m阶B树 
{
	int x,s,finished=0,needNewRoot=0;
	BTree ap;
	if (q==NULL) newRoot(t,NULL,k,NULL);  // 生成新的根节点
	else 
	{
		x=k;ap=NULL;
		while (needNewRoot==0 && finished==0)
		{
			Insert(q,i,x,ap);    //x和ap分别插到q->key[i]和q->ptr[i]
			if (q->keynum <m)  finished=1; // 插入完成
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

STATUS InsertNewNumber(BTree &root,KeyType k)   //在B树中插入一个关键字k 
{
	result r; 
	SearchBTree(root,k,r);
	printf("插入%d:\n",k);
	if (r.tag==1) 
	{
		printf("错误，该关键字已存在\n");
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");		
		return ERROR; //如果该关键字已经存在该B树中
	}
	InsertBTree(root,k,r.pt,r.i);
	show(root);   //显示该树
	return OK;
}



void Successor(BTree &p,int i) //找到 p->ptr[i]的子树中最大的关键字并替代p->key[i]的值
{
	result r; 
	SearchBTree(p->ptr[i],p->key[i],r);   //因为 p->ptr[i]中的元素一定比p->key[i],调用 SearchBTree(p->ptr[i],p->key[i],r)可找到最小的 最下层非终端节点 
	int temp;
	p->key[i]=r.pt->key[1];    
	p=r.pt;
}

void Remove(BTree &q,int i) //在B树节点中删除下标为i的关键字
{
	int j,n=q->keynum;
	for (j=i;j<n;j++)               //把下标为j以后的key和point 向前移 
	{
		q->key[j]=q->key[j+1];
		q->ptr[j]=q->ptr[j+1]; 
	} 
	q->keynum--;
}

void Merge(BTree go,int i) //把B树节点go中的ptr[i-1]和key[i]和ptr[i]合在同一个节点
{
	BTree p=go->ptr[i-1];
	BTree q=go->ptr[i];
	int n=p->keynum;
	
	n++;                          //key[i]放在p节点的后面
	p->key[n]=go->key[i];
	p->ptr[n]=q->ptr[0];
	if (p->ptr[n]!=NULL) (p->ptr[n])->parent=p;
	
	int j;                        
	for (j=1;j<=q->keynum;j++) //q节点的内容放在p节点的后面
	{
		n++;
		p->key[n]=q->key[j];
		p->ptr[n]=q->ptr[j];
		if (p->ptr[n]!=NULL) (p->ptr[n])->parent=p;
	}
	
	p->keynum=n;
	
	free(q);
	
	for (j=i;j<go->keynum;j++)  //在go节点中删除下标为i的关键字
	{
		go->key[j]=go->key[j+1];
		go->ptr[j]=go->ptr[j+1];
	}
	go->keynum--;
	
}

void Restore(BTree &root,BTree p)  //在根节点为root的B树中调整p节点使得满足B树的性质
{
	BTree par;
	par=p->parent; 
	int i;
	if (par==NULL)  //root节点是根节点
	{
		if (p->keynum==0)   //根节点为空
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
	i--;                  //找到par中p的位置
	if (i==0)             //如果p在par的ptr[0]
	{
		BTree q=par->ptr[i+1];
		if (q->keynum>(m-1)/2)
		{
			
			p->keynum++;                        //把 par->key[i+1]和右兄弟子树的 ptr[0]放在p结点的后面 
			p->key[p->keynum]=par->key[i+1];
			p->ptr[p->keynum]=q->ptr[0];
			if (p->ptr[p->keynum]!=NULL) (p->ptr[p->keynum])->parent=p;
  
			par->key[i+1]=q->key[1];  //更新双亲节点关键字 
			
			int j;                     // 删除q的第一个关键字和ptr[0] 
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
			Merge(par,1); //合并par的ptr[0]和key[0]和ptr[1]
		}
	}
	else
	{
		 BTree q=par->ptr[i-1];
		if (q->keynum>(m-1)/2)
		{	
		
		  int j;                        //把左兄弟子树的最后一个ptr和par->keynum[i]插入p节点的前面	 
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
		  
		  par->key[i]=q->key[q->keynum]; //更新双亲节点关键字 
		  q->keynum--;	                  // 删除q的第最后一个关键字和ptr
	    }
	    else
	    {
	    	Merge(par,i);    //合并par的ptr[i-1]和key[i]和ptr[i]
	    }
	}
	if (par->keynum<(m-1)/2)  Restore(root,par); //如果par节点需要调整，则递推的进行调整
}


void DeleteBTree(BTree &root,BTree p,int i)  //在根为root的B树中删除p节点的第i个关键字
{
	if (p->ptr[i]!=NULL)
	{
		Successor(p,i);                //找到 p->ptr[i]的子树中最大的关键字并替代p->key[i]的值 
		DeleteBTree(root,p,1);     //转化为 p->ptr[i]的子树中最大的关键字
	}
	else
	{
		Remove(p,i);              //删除第i个关键字 
		if (p->keynum<(m-1)/2)
		  Restore(root,p);       //在根节点为root的B树中调整p节点及附近的节点使得满足B树的性质
	}
} 

STATUS DeleteNumber(BTree &root,KeyType k)   //在B树中删除关键字为k的节点
{
	result r; 
	SearchBTree(root,k,r);
	printf("删除%d:\n",k);
	if (r.tag==0) 
	{
		printf("错误，该关键字不存在\n");
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
		return ERROR; //如果该树B不存在的关键字为k的节点，错误
	}
	DeleteBTree(root,r.pt,r.i); 
	
	show(root);   //显示该树
	return OK; 
}

void Distory(BTree &root) //销毁根节点为root的B树 
{
	if (root==NULL) return ;
	int i;
	for (int i=0;i<=root->keynum;i++) //枚举root的子树
	{
		Distory(root->ptr[i]);    //销毁root的子树
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
    printf("查找关键字%d:\n",x); 
    if (FindIsExist(root,x)==TRUE) 
	{
		printf("关键字%d存在\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	else
	{
		printf("关键字%d不存在\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	
	x=6;
	printf("查找关键字%d:\n",x); 
	if (FindIsExist(root,x)==TRUE) 
	{
		printf("关键字%d存在\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	else
	{
		printf("关键字%d不存在\n",x);
		for (int i=0;i<=108;i++) printf("+");  
	    printf("\n");
	}
	printf("销毁B树：\n"); 
	Distory(root);
	show(root);
	while (true);
	return 0;
}

