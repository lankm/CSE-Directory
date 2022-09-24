package firstFour;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Friendly {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\firstFour\\friendly.dat"));
        while(in.hasNextLine()) {
            System.out.println(runLine(in.nextLine()));
        }
    }
    public static String runLine(String line) {
        String output = line.substring(0,9);    //puts the timestamp at the beginning
        int A = (byte)(9*Byte.parseByte(line.substring(0,2))); // init's a according to the format
        int B = (byte)(3*Integer.parseInt(line.substring(3,5))+Integer.parseInt(line.substring(6,8)));

        int i = 0;
        for(char c: line.substring(9).toCharArray()) {   //starts at the beginning of the statement
            int value;
            if(i%2==0)  //is even
                value =(int)(c^A);
            else    //is odd
                value =(int)(c^B);

            output+="0x" + Integer.toHexString(value).toUpperCase() + " ";
            i++;    //determines if its in a odd or even place
        }
        return output;
    }
}
