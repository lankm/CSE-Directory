package firstFour;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Bears {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\firstFour\\bears.dat"));
        for(int i = Integer.parseInt(in.nextLine());i>0;i--) {
            int total = 0;
            for(int j = 0;j<10;j++) {
                total+=line(in.nextLine());
            }
            System.out.println(total);
        }
    }
    public static int line(String line) {   //gets the number of B's in a line
        char[] l = line.toCharArray();
        int total = 0;

        for(int i = 0;i<10;i++) {
            if(l[i]=='B')
                total+=1;
        }
        return total;
    }
}
