package InvitationalA2014;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CandyFest {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvitationalA2014\\candyfest.dat"));

        for(int i = in.nextInt(); i > 0; i--) {
            int length = in.nextInt();
            int[] numbs = new int[length];

            for(int j = 0; j < length; j++) {   //input into memory
                numbs[j] = in.nextInt();
            }

            boolean change = true;
            while(change) {
                change = false;

                for(int j = 0; j < numbs.length-1;j++) {
                    int total = numbs[j] + numbs[j + 1];
                    int avg = total / 2;

                    if(avg<numbs[j]) {
                        numbs[j] = avg;
                        numbs[j+1] = avg + total % 2;
                        change = true;
                    }
                }
            }
            System.out.println(numbs[0]);
        }
    }
}
