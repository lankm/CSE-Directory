package skillsReview;

import java.util.Arrays;
import java.util.Scanner;

public class Lottery {
    static int[] numbers = new int[3];
    static int[] guesses = new int[3];

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        for(int i = 0; i<3;i++) {    //sets random numbers
            numbers[i] = (int)(Math.random()*9+1);
        }

        for(int i = 0; i<3;i++) {    //retrieves the users guesses
            System.out.print("Enter your " + (i+1) + " number: ");
            guesses[i] = in.nextInt();
        }

        int match = match();
        if(match==3&&Arrays.equals(numbers,guesses))
            output(1000000);
        else if(match==3)
            output(1000);
        else if(match==2)
            output(100);
        else if(match==1)
            output(10);
        else
            output(0);
        in.close();
    }
    public static int match() {
        int[] numbersCopy = Arrays.copyOf(numbers, numbers.length);

        int total = 0;
        for(int i = 0; i<guesses.length;i++) {
            int number = guesses[i];
            for(int j = i;j<numbersCopy.length;j++) {
                if(numbersCopy[j]==number) {
                    total++;
                    numbersCopy[j] = Integer.MAX_VALUE;
                }
            }
        }
        return total;
    }
    public static void output(int won) {
        System.out.println("your numbers were " + Arrays.toString(guesses) +
                           " and the numbers rolled were " + Arrays.toString(numbers) +
                           " . you won "+ won);

    }
}
