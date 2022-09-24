package Lawn_Local_Qualified;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Qualified {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Lawn_Local_Qualified\\qualified.dat"));
        for(int i = in.nextInt();i>0;i--) {
            String name = in.next();
            int score = in.nextInt();
            String comp = in.next();

            if(comp.equals("STC")&&score>=560)
                System.out.println(name);
            else if(comp.equals("WTC")&&score>=340)
                System.out.println(name);
            else if(comp.equals("NTC")&&score>=420)
                System.out.println(name);
            else if(comp.equals("CTC")&&score>=370)
                System.out.println(name);
            else if(comp.equals("LVC")&&score>=470)
                System.out.println(name);
        }
    }
}