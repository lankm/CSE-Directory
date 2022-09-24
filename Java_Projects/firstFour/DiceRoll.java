package firstFour;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class DiceRoll {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\firstFour\\diceroll.dat"));
        for(int i = in.nextInt();i>0;i--) {
            long seed = in.nextLong();
            Random generator = new Random(seed);

            int first = generator.nextInt(4)+1;
            int second = generator.nextInt(25)+1;
            System.out.println(getSide(first,second));
        }
    }
    public static String getSide(int direction, int number) {
        if((direction+1)/2==1) { //red,white
            if(number%2==1) //odd
                return "RED";
            else    //even
                return "WHITE";
        } else {    //blue white
            if(number%2==1) //odd
                return "BLUE";
            else    //even
                return "WHITE";
        }
    }
}
