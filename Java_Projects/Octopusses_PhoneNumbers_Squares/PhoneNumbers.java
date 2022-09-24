package Octopusses_PhoneNumbers_Squares;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class PhoneNumbers {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Octopusses_PhoneNumbers_Squares\\phonenumbers.dat"));
        for(int i = Integer.parseInt(in.nextLine());i>0;i--) {
            String pn = in.nextLine();
            if(pn.matches("\\d{3}-\\d{3}-\\d{4}"))
                System.out.println(pn);
            else
                System.out.println("INVALID PHONE NUMBER");
        }
    }
}
