package Jewels_WaitList;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Waitlist {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Jewels_WaitList\\waitlist.dat"));

        for(int i = in.nextInt();i>0;i--) {
            System.out.print(in.next());
            int numb = -(in.nextInt()-in.nextInt());
            System.out.println(" " + (numb>0?numb:0));
        }
    }
}
