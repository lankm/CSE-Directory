package InvitationalA2014;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Family {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvitationalA2014\\family.dat"));

        PriorityQueue<Person> people = new PriorityQueue<>();
        for(int i = Integer.parseInt(in.nextLine()); i > 0; i--) {
            String first = in.next();
            String relation = in.next();
            String second = in.next();

            boolean firstExist = false; //some problem here
            boolean secondExist = false;
            for(Person p: people) {
                if(p.name.equals(first))
                    firstExist = true;
                else if(p.name.equals(second))
                    secondExist = true;
            }
            if(!firstExist)
                people.add(new Person(first));
            if(!secondExist)
                people.add(new Person(second));

            for(Person p: people) {
                if (p.name.equals(first))
                    p.setRelation(relation, second);
                if (relation.equals("sibling") && p.name.equals(second))
                    p.setRelation(relation, first);
            }
        }
        for(int i = people.size();i>0;i--) {    //prints out data.
            System.out.println(people.poll());
        }
    }
}
class Person implements Comparable<Person>{
    String name;
    String father = "Unknown";
    String mother = "Unknown";
    PriorityQueue<String> siblings = new PriorityQueue<>();

    public Person(String name) {
        this.name = name;
    }

    public void setRelation(String relation, String name) {
        if(relation.equals("father"))
            father = name;
        else if(relation.equals("mother"))
            mother = name;
        else
            siblings.add(name);
    }

    public int compareTo(Person person) {
        return name.compareTo(person.name);
    }
    public String toString() {
        String output = "";
        output += name + "\n";
        output += "Father: " + father + "\n";
        output += "Mother: " + mother + "\n";
        for(int i = siblings.size();i>0;i--) {
            output += "Sibling: " + siblings.poll() + "\n";
        }
        return output;
    }
}
