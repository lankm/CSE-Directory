package InvA;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Brian {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvA\\brian.dat"));

        for(int i = in.nextInt();i>0;i--) {
            int year = in.nextInt();
            int numb = (year-1995)/2;

            System.out.println("In the year "+year+", Brian will be coding in Java "+numb+"!");
        }

    }
}
