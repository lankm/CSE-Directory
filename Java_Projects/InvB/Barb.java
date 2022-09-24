package InvB;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Barb {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvB\\barb.dat"));

        while(in.hasNextLine()) {
            String color = in.nextLine();
            char[] colorC = color.toCharArray();

            System.out.print(color+" ");

            for(int i = colorC.length-1;i>=0;i--) {
                System.out.print(Character.toUpperCase(colorC[i]));
            }
            System.out.print(" ");

            for(int i = (colorC.length-1)/2;i>=0;i--) {
                System.out.print(colorC[i]);
            }
            System.out.print(" ");

            for(int i = colorC.length/2;i<colorC.length;i++) {
                System.out.print(Character.toUpperCase(colorC[i]));
            }
            System.out.println();
        }
    }
}
