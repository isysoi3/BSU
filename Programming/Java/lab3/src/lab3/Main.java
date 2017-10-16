package lab3;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter k: ");
        int k = in.nextInt();
        if ( k < 1 ) {
            System.err.println("Invalid k value (require: n >= 1");
            System.exit( 1 );
        }

        int a,b;

        Fraction mas[] = new Fraction[k];
        for (int i = 0;i < k; i++){
            System.out.print("Enter numerator: ");
            a = in.nextInt();
            System.out.print("Enter denominator: ");
            b = in.nextInt();
            System.out.print("");
            mas[i] = new Fraction(a,b);

        }

        System.out.println();

        if(k > 1) {
            System.out.println("Sum of the first and the second is " + Fraction.Sum(mas[0], mas[1]).toString());
            System.out.println("Sub of the first and the second is " + Fraction.Sub(mas[0], mas[1]).toString());
            System.out.println("Mul of the first and the second is " + Fraction.Mul(mas[0], mas[1]).toString());
            System.out.println("Div of the first and the second is " + Fraction.Div(mas[0], mas[1]).toString());
        }
        System.out.println();
        System.out.println("Fractions:");
        for (int i = 0;i < k; i++){
            System.out.println(mas[i].toString());
        }

    }
}
