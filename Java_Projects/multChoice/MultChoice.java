package multChoice;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class MultChoice {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\multChoice\\multchoice.dat"));

        int cap = Integer.parseInt(in.nextLine());

        for(int i = 0;i<cap;i++) {
            System.out.println("Question " + (i+1));

            ArrayList<ArrayList<String>> answers = new ArrayList<>();
            for(int j = 0;j<5;j++) {
                String line = in.nextLine();
                Scanner lineSc = new Scanner(line);

                ArrayList<String> words = new ArrayList<>();
                while (lineSc.hasNext()) {   //gets the roman numerals in to words
                    String word = lineSc.next();
                    if (word.equals("and") || word.contains("."))
                        continue;

                    if (word.contains(","))
                        word = word.substring(0, word.length() - 1);

                    words.add(word);
                }
                answers.add(words);
                lineSc.close();
            }

            System.err.println(answers);
            in = new Scanner(new File("Java_Projects\\multChoice\\multchoice.dat"));
            in.nextLine();

            for(int j = 0; j<5;j++) {
                ArrayList<String> cur = answers.get(j);
                boolean only = false;
                for(int l = 0;l<5;l++) {
                    ArrayList<String> curTest = answers.get(l);
                    if(cur.equals(curTest))
                        continue;

                    if(curTest.containsAll(cur))
                        only=true;
                }
                System.out.println(in.nextLine() + (only?" only":""));
            }
            System.out.println();
        }
    }
}
