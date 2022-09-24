package Golf_Moose;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class GolfQ {
    public static void main(String[] args) throws FileNotFoundException {
        Map<String, Integer> people = new LinkedHashMap<>();
        Queue<Integer> scores = new PriorityQueue<>();
        Scanner in = new Scanner(new File("Java_Projects\\Golf_Moose\\golfq.dat"));

        for(int i = in.nextInt();i>0;i--) { //adds all the values to the two collections
            String name = in.next()+" "+in.next();
            Integer score = in.nextInt();
            scores.add(score);
            people.put(name,score);
        }

        Queue<Integer> newScores = new PriorityQueue<>(10,Collections.reverseOrder());
        for(int i = 12;i>0;i--) {
            newScores.add(scores.remove());
        }

        System.out.println(newScores);
        for(Map.Entry<String, Integer> person: people.entrySet()) {
            if(newScores.contains(person.getValue()))
                System.out.println(person.getKey() + " " + person.getValue());
        }
    }
}