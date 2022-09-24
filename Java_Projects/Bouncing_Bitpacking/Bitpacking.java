package Bouncing_Bitpacking;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Bitpacking {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Bouncing_Bitpacking\\bitpacking.dat"));

        for(int i = in.nextInt();i>0;i--) {
            int numb = in.nextInt();
            String bits = Integer.toBinaryString(numb);

            for(int j = 32;j>bits.length();) {
                bits="0"+bits;
            }

            int type = Integer.parseInt(bits.substring(9,14),2);
            int subType = Integer.parseInt(bits.substring(14,20),2);
            int inventory = Integer.parseInt(bits.substring(20,32),2);

            System.out.print("Type: " + (char)(type+64)+" | ");

            if(subType<=26)
                System.out.print("Sub Type: " + (char)(subType+64)+" | ");
            else if(subType<=52)
                System.out.print("Sub Type: " + (char)(subType+70)+" | ");
            else if(subType<=61)
                System.out.print("Sub Type: " + (char)(subType-4)+" | ");

            System.out.println("Inventory: " + inventory);
        }
    }
}
