package InvB;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Emily {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvB\\emily.dat"));

        while(in.hasNextLine()) {
            String line = in.nextLine();
            Scanner lineS = new Scanner(line);

            double avg = (lineS.nextInt()+lineS.nextInt())/2.0;
            double total = avg*Double.parseDouble(lineS.nextLine());

            if(total%1==0)
                System.out.println((int)total);
            else
                System.out.printf("%.1f", total);
            lineS.close();
        }
    }
}
