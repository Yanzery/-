import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * @Auther: Hz1kai
 * @Date: 2018/11/29 20:23
 * @Description:
 */
public class RSAUtils {
    private int p=0;
    private int q=0;
    private long n=0;
    private long m=0;

    private long public_key=0;//公匙
    private long private_key=0;//密匙

    private long text=0;//明文
    private long secretword=0;//密文
    private long word=0;//解密后明文

    //判定是否为素数
    public boolean primenumber(long t)
    {
        long k=0;
        k=(long)Math.sqrt((double)t);
        boolean flag=true;
        outer:for(int i=2;i<=k;i++)
        {
            if((t%i)==0)
            {
                flag = false;
                break outer;

            }
        }
        return flag;
    }
    //输入PQ
    public void inputPQ()throws Exception
    {
        do{
            System.out.println("请输入素数p: ");
            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
            String br=stdin.readLine();
            this.p=Integer.parseInt(br);
        }
        while(!primenumber(this.p));
        do{
            System.out.println("请输入素数q: ");
            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
            String br=stdin.readLine();
            this.q=Integer.parseInt(br);
        }
        while(!primenumber(this.q));
        this.n=this.p*this.q;
        this.m=(p-1)*(q-1);
        System.out.println("这两个素数的乘积为p*q:"+this.n);
        System.out.println("所得的小于N并且与N互素的整数的个数为m=(p-1)(q-1):"+this.m);
    }
    //求最大公约数
    public long gcd(long a,long b)
    {
        long gcd;
        if(b==0)
            gcd=a;
        else
            gcd=gcd(b,a%b);
        System.out.println("gcd:"+gcd);
        return gcd;

    }

    //输入公匙
    public void getPublic_key()throws Exception
    {
        do{
            System.out.println("请输入一个公钥的值,这个值要求小于m并且和m互质: ");
            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
            String br=stdin.readLine();
            this.public_key=Long.parseLong(br);
        }while((this.public_key >= this.m) &&(this.gcd(this.m,this.public_key)!=1));
        System.out.println("公钥为:"+this.public_key);
    }
    //计算得到密匙
    public void getPrivate_key()
    {
        long value=1;
        outer:for(long i=1;;i++)
        {
            value=i*this.m+1;
            //System.out.println("value:  "+value);
            if((value%this.public_key==0)&&(value/this.public_key < this.m))
            {
                this.private_key=value/this.public_key;
                break outer;
            }
        }
        System.out.println("产生的一个私钥为:"+this.private_key);
    }
    //输入明文
    public void getText()throws Exception
    {
        System.out.println("请输入明文:");
        BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
        String br=stdin.readLine();
        this.text=Long.parseLong(br);
    }
    //加密、解密计算
    public long colum(long y,long n,long key)
    {

        long mul;
        if(key==1)
            mul=y%n;
        else
            mul=y*this.colum(y,n,key-1)%n;
        return mul;
    }

    //加密后解密
    public void pascolum()throws Exception
    {
        this.getText();
        //System.out.println("输入明文为: "+this.text);
        //加密
        this.secretword=this.colum(this.text,this.n,this.public_key);
        System.out.println("所得的密文为:"+this.secretword);
        System.out.println("请输入密钥解密:");
        BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
        String pk=stdin.readLine();
        //解密
        this.word=this.colum(this.secretword,this.n,Long.valueOf(pk));
        System.out.println("解密后所得的明文为:"+this.word);

    }
    public static void main(String []args)throws Exception
    {
        RSAUtils t = new RSAUtils();
        t.inputPQ();
        t.getPublic_key();
        t.getPrivate_key();
        t.pascolum();
    }

}
