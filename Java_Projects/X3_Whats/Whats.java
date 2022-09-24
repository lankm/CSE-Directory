package X3_Whats;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.TreeMap;

public class Whats {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\X3_Whats\\whats.dat"));

        for(int i = in.nextInt();i>0;i--) {
            TreeMap<Integer,Integer> t = new TreeMap<>();
            int numb = in.nextInt();

            for(int j = 0;j<28;j++)
                t.put(-(numb-(numb=in.nextInt())),j);

            for(int j = 0;j<4;j++) {
                System.out.println(t.firstKey() + " " + (t.get(t.firstKey())+1));
                t.remove(t.firstKey());
            }
            System.out.println();
        }

    }
}
