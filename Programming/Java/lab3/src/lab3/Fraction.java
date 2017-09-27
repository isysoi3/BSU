package lab3;

public class Fraction {

    private int numerator; // числитель
    private int denominator; // знаменатель

    Fraction(int num,int den) {
        assert( den != 0 ) : "denominator is zero";
        if (den < 0) {
            num = -num;
            den = -den;
        }
        numerator = num;
        denominator = den;
        Reduce();
    }

    private void Reduce(){
        int NOD = gcd(this.numerator,this.denominator);
        numerator /=  NOD;
        denominator /= NOD;
    }

    private static int gcd(int a,int b) {
        while (b !=0) {
            int tmp = a%b;
            a = b;
            b = tmp;
        }
        return a;
    }

    public static Fraction Sum(Fraction a,Fraction b){
        return new Fraction(a.numerator *b.denominator + b.numerator * a.denominator, b.denominator * a.denominator);
    }


    public static Fraction Sub(Fraction a,Fraction b){
        return Sum(a,unaryMinus(b));
    }

    public static Fraction unaryMinus(Fraction a){
            return new Fraction(-a.numerator,a.denominator);
    }

    public static Fraction Mul(Fraction a,Fraction b){
        return new Fraction(a.numerator * b.numerator,a.denominator * b.denominator);
    }
    public static Fraction Div(Fraction a,Fraction b){
        return new Fraction(a.numerator * b.denominator,a.denominator * b.numerator);
    }


    @Override
    public String toString(){
        return String.format("%s/%s", numerator, denominator);
    }

}
