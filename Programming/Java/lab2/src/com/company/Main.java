package com.company;

import java.lang.reflect.Array;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        // 25 решение
        Scanner in = new Scanner( System.in );
        while ( in.hasNextLine() ) {
            String s = in.nextLine();
            String rez = s.replaceAll("\\b[a-zA-Z]{1}\\b", " ");
            rez = rez.replaceAll("(^\\s+)|($\\s+)","");
            System.out.println(rez.replaceAll("(\\s{2,})"," "));
        }
        in.close();
    }
}
