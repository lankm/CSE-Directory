package DQL_Florist;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Florist {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\DQL_Florist\\florist.dat"));

        PriorityQueue<Integer> pots = new PriorityQueue<>(10, Collections.reverseOrder());

        Scanner fir = new Scanner(in.nextLine());   //gets the weights of the pots
        while (fir.hasNextInt())
            pots.add(fir.nextInt());
        fir.close();

        for (int i = Integer.parseInt(in.nextLine()); i > 0; i--) {
            PriorityQueue<Integer> flow = new PriorityQueue<>(10, Collections.reverseOrder());

            Scanner line = new Scanner(in.nextLine());  //gets the weights of the flowers
            while (line.hasNextInt())
                flow.add(line.nextInt());
            line.close();

            PriorityQueue<Integer> potsCopy = new PriorityQueue<>(pots);
            int total = 0;
            for (int j = flow.size(); j > 0; j--) {
                if (potsCopy.isEmpty() || flow.isEmpty())
                    break;

                int potTop = potsCopy.peek();
                int flowerTop = flow.remove();

                if (flowerTop <= potTop) {
                    total++;
                    potsCopy.remove();
                }
            }
            System.out.println(total);
        }
    }
}
