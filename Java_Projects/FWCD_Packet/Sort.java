package FWCD_Packet;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Sort {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\sort.dat"));

        ArrayList<String> lines = new ArrayList<>();
        while(in.hasNextLine())
            lines.add(in.nextLine());

        while(!lines.isEmpty()) {
            ArrayList<String> half = new ArrayList<>();
            for(int i = lines.size()/2; i>0;i--) {
                String line;
                line = lines.remove(0);

                Scanner lineS = new Scanner(line);
                String first = lineS.next();
                String last = lineS.next();
                String val = lineS.next();
                half.add(last + " " + first + " " + val);
                lineS.close();
            }
            Collections.sort(half);
            for(int i = half.size()-1;i>=0;i--) {
                System.out.println(half.get(i));
            }
            if(lines.size()==1) {
                String line = lines.get(0);
                Scanner l = new Scanner(line);
                String first = l.next();
                String last = l.next();
                String val = l.next();
                System.out.println(last + " " + first + " " + val);
                l.close();
                break;
            }

        }

    }
}
