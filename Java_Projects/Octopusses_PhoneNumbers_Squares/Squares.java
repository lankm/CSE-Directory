package Octopusses_PhoneNumbers_Squares;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Squares {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Octopusses_PhoneNumbers_Squares\\squares.dat"));
        while(in.hasNextInt()) {
            int i = in.nextInt();
            print(i);
            System.out.println();
        }
    }
    public static void print(int numb) {
        for(int i = 0;i<numb;i++) {
            String output = "";
            int number = minDist(numb,i);

            for(int j = 0;j<number;j++) {   //prints each part by the diagonals from left to right
                if(j%2==0)
                    output+="*";
                else
                    output+=" ";
            }
            for(int j = 0;j<numb-number*2;j++) {
                if(number%2==0)
                    output+="*";
                else
                    output+=" ";
            }
            for(int j = number;j>0;j--) {
                if(j%2==1)
                    output+="*";
                else
                    output+=" ";
            }

            System.out.println(output);
        }
    }
    public static int minDist(int length, int numb) {
        if(numb>=length/2)
            return Math.abs(length-numb)-1;
        return numb;
    }
}
