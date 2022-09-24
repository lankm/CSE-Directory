package InvB;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Judith {
    public static void main(String[] args) throws FileNotFoundException {
        PriorityQueue<BigDecimal> numbs = new PriorityQueue<>();
        Scanner in = new Scanner(new File("Java_Projects\\InvB\\judith.dat"));

        while(in.hasNext())
            numbs.add(in.nextBigDecimal());

        while(!numbs.isEmpty())
            System.out.println(numbs.remove());

    }
}
