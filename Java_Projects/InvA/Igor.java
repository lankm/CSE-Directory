package InvA;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;

public class Igor {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvA\\igor.dat"));

        for(int i = in.nextInt();i>0;i--) {
            String line = in.next();

            int length = 0;
            HashSet<Character> letters = new HashSet<>();
            for(char c: line.toCharArray()) {
                if(letters.contains(c)) {
                    letters.remove(c);
                    length+=2;
                } else {
                    letters.add(c);
                }
            }

            boolean empty = letters.isEmpty();
            int value = (int)Math.pow(length+(empty?0:1),2);
            int extras = empty?0:letters.size()-1;

            System.out.println(value+extras);
        }
    }
}
