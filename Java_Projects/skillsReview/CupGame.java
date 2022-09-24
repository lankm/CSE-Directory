package skillsReview;

import java.util.Scanner;

public class CupGame {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.print("Enter the number 1, 2, or 3: ");
        int input = in.nextInt();


        int cup = (int)(Math.random()*3)+1;
        if(cup==input)
            System.out.println("Winner.");
        else
            System.out.println("Sorry you lost.");
        in.close();
    }
}
