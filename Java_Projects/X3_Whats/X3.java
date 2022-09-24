package X3_Whats;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class X3 {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\X3_Whats\\x3.dat"));
        for (int i = in.nextInt(); i > 0; i--) {
            int[] coef = new int[4];

            for (int j = 0; j < 4; j++) {
                coef[j] = in.nextInt();
            }
            Integer[] out = factor(coef);

            if (out.length != 0)
                for (int val : out)
                    System.out.print(val + " ");
            else
                System.out.print("NO INTEGER SOLUTION");
            System.out.println();
        }
    }

    public static Integer[] factor(int[] coef) {
        ArrayList<Integer> a = new ArrayList<Integer>();
        for(int i = -Math.abs(coef[3]);i<Math.abs(coef[3]);i++) {
            if(eval(coef,i)==0)
                a.add(i);
        }
        return a.toArray(new Integer[a.size()]);
    }
    public static int eval(int[] coef, int numb) {
        int output=0;
        for(int i = coef.length-1;i>=0;i--) {
            output+=Math.pow(numb,i)*coef[coef.length-i-1];
        }
        return output;
    }
}
