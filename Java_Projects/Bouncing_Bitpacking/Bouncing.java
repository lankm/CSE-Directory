package Bouncing_Bitpacking;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Bouncing {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Bouncing_Bitpacking\\bouncing.dat"));
        for (int i = in.nextInt(); i > 0; i--) {
            Random r = new Random(in.nextLong());
            int r1 = r.nextInt(10) + 1;
            Dice d = new Dice();

            for (; r1 > 0; r1--) {
                int r2 = r.nextInt(4) + 1;
                int r3 = r.nextInt(5) + 1;

                if(r2<3)    //forward or back
                    d.rollForwardBackwards(r3);
                else
                    d.rollLeftRight(r3);
            }
            System.out.println(d.getTop());
        }
    }
}

class Dice {
    String topBottom = "WHITE";
    String leftRight = "BLUE";
    String frontBack = "RED";

    public void rollForwardBackwards(int times) {
        if(times%2==0)
            return;

        String temp = topBottom;
        topBottom = frontBack;
        frontBack = temp;
    }

    public void rollLeftRight(int times) {
        if(times%2==0)
            return;

        String temp = topBottom;
        topBottom = leftRight;
        leftRight = temp;
    }

    public String getTop() {
        return topBottom;
    }
}
