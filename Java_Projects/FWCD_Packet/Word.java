package FWCD_Packet;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Word {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\words.dat"));

        while(in.hasNext()) {
            char[] word = in.next().toCharArray();

            String punct = "";
            for(int i = word.length-1;i>=0;i--) {
                char letter = word[i];

                if(Character.isDigit(letter))
                    continue;
                if(!Character.isDigit(letter)&&!Character.isLetter(letter)) {
                    punct = letter + punct;
                    continue;
                }
                System.out.print(letter);
            }
            System.out.print(punct + " ");
        }
    }
}
