package Lawn_Local_Qualified;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Local {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Lawn_Local_Qualified\\local.dat"));

        for (int i = in.nextInt(); i > 0; i--) {
            String y = in.next();
            int b = 0;
            int w = 0;

            for (int j = 0;j<31;j++) {
                int numb = in.nextInt();
                if(numb<32)
                    b++;
                else if(numb>50)
                    w++;
            }

            System.out.println(y+" " +b + " "+w);
        }
    }
}
