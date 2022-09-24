package InvitationalA2014;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Farkle {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvitationalA2014\\farkle.dat"));

        while(in.hasNext()) {
            Random r = new Random(in.nextInt());
            int max = in.nextInt();

            int last = -1;     //some error with repeating 100 times
            int total = 0;
            double amount = 0;
            int inARow = 0;
            while(inARow !=max-1) {
                int next = r.nextInt(6)+1;

                amount++;
                total+=next;
                System.out.print(next);
                if(next==last)
                    inARow++;
                last=next;
            }
            System.out.println();
            System.out.println(total/amount);
        }
    }
}
