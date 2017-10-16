package com.company;

class Main {



    public static double solve (double x,double touch){
        /*double  i = 3,factorial = 6, pow = x*x*x,step = x,rez = step;
        while(Math.abs(step) > touch) {
            step = pow/factorial;
            rez += step;
            i += 2;
            factorial *= i * (i -1);
            pow *= x * x;
            }*/
        double step = 1,rez = 1,t = 2,n = 2;
        while(Math.abs(step) > touch) {
            step = (step/t )* x;
            if (n % 2 == 1)
                step = - step;
            rez += step;
            t += 2;
            n ++;
        }

        return rez;
    }


    public static void main(String[] args) {
        if ( args.length != 2 ) {
            System.err.println("Invalid number of arguments");
            System.exit(1);
        }
        double x = Double.parseDouble( args[0] );

        int k = Integer.parseInt( args[1] );
        if ( k <= 1 ) {
            System.err.println("Invalid argument: " + k );
            System.exit(1);
        }

        String fmt = "%." + args[1] + "f\n";
        System.out.format(fmt,solve(x,Math.pow(10,-k)) );
        System.out.format( fmt, Math.sqrt(1+x));
        System.exit(0);
    }
}
