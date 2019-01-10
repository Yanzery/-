import java.math.BigInteger;
import java.util.Scanner;

/**
 * @Auther: Hz1kai
 * @Date: 2018/10/7 22:26
 * @Description:
 */
public class homework {

    /**
     * <p>辗转相除法求最大公约数
     * @param a
     * @param b
     * @return
     */
    public static BigInteger gcd(BigInteger a, BigInteger b){
        if(b.equals(BigInteger.ZERO)){
            return a ;
        }else{
            return gcd(b, a.mod(b)) ;
        }
    }

    /**
     * <p>扩展欧几里得算法：
     * <p>求ax + by = 1中的x与y的整数解（a，b互质）
     * @param a
     * @param b
     * @return
     */
    public static BigInteger[] extGcd(BigInteger a, BigInteger b){
        if(b.equals(BigInteger.ZERO)){
            BigInteger x1 = BigInteger.ONE ;
            BigInteger y1 = BigInteger.ZERO ;
            BigInteger x = x1 ;
            BigInteger y = y1 ;
            BigInteger r = a ;
            BigInteger[] result = {r, x, y} ;
            return result ;
        }else{
            BigInteger[] temp = extGcd(b, a.mod(b)) ;
            BigInteger r  = temp[0] ;
            BigInteger x1 = temp[1] ;
            BigInteger y1 = temp[2] ;

            BigInteger x = y1 ;
            BigInteger y = x1.subtract(a.divide(b).multiply(y1)) ;
            BigInteger[] result = {r, x, y} ;
            return result ;
        }
    }


    //判断素数
    public static boolean isPrime(Long a) {
        if (a < 2) return false;
        else {
            for (long i = 2; i < a; i++) {
                if (a % i == 0) return false;
            }
        }
        return true;
    }


    //模指运算
    public static int ModExp(int n, int b, int m) {
        return (int) Math.pow(n, b) % m;
    }

    public static void printCmd() {
        System.out.println("1.素数的选择判断");
        System.out.println("2.模逆算法");
        System.out.println("3.快速模指运算");
        System.out.println("4.RSA算法加密");
    }

    public static void main(String[] args) throws Exception {
        RSAUtils t = new RSAUtils();
        Scanner scanner = new Scanner(System.in);
        printCmd();
        while (scanner.hasNext()) {
            String cmd = scanner.nextLine();
            switch (cmd) {
                case "1":
                    System.out.print("请输入要判断的素数:");
                    String prime = scanner.next();
                    boolean isPrime = isPrime(Long.valueOf(prime));
                    if (isPrime) {
                        System.out.println(prime + "为素数");
                    } else {
                        System.out.println(prime + "不为素数");
                    }
                    printCmd();
                    break;
                case "2":
                    System.out.print("请输入a,b求a模b的逆元:");
                    String str = scanner.nextLine();
                    String[] numbs = str.split(",");
                    BigInteger[] result = extGcd(new BigInteger(numbs[0]), new BigInteger(numbs[1]));
                    System.out.println(result[1] + "为逆元");
                    printCmd();
                    break;
                case "3":
                    System.out.print("请输入n,b,m求n的b次方模m:");
                    String str1 = scanner.nextLine();
                    String[] numStr = str1.split(",");
                    int mod = ModExp(new Integer(numStr[0]), new Integer(numStr[1]), new Integer(numStr[2]));
                    System.out.println("结果为：" + mod);
                    printCmd();
                    break;
                case "4":
                    t.inputPQ();
                    t.getPublic_key();
                    t.getPrivate_key();
                    t.pascolum();
                    printCmd();
                    break;
            }

        }

    }
}
