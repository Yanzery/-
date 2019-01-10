int ExtGCD(int a,int b,int *x,int *y)//扩展欧几里得算法;
{
    if(b==0)
    {
        *x=1;
        *y=0;
        return a;
    }
//	printf("a:%d  b:%d\n",a,b);
//	printf("***********************\n");
    int ret=exgcd(b,a%b,x,y);
    int t=*x;
    *x=*y;
    *y=t-a/b*(*y);
    return ret;
} 
