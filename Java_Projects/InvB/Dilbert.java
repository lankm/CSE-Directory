package InvB;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.NumberFormat;
import java.util.*;

public class Dilbert {
    @Deprecated
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvB\\dilbert.dat"));

        //      total           date, value
        TreeMap<String, Person> list = new TreeMap<>();

        while(in.hasNextLine()) {
            String name = in.next() + " " + in.next();

            String time = in.next();
            Scanner timeS = new Scanner(time);
            timeS.useDelimiter("/");
            int month = timeS.nextInt();
            int day = timeS.nextInt();
            int year = timeS.nextInt();
            Date date = new Date(year, month, day);

            double value = Double.parseDouble(in.nextLine());

            if (list.containsKey(name))
                list.get(name).put(date, value);
            else {
                list.put(name, new Person(name));
                list.get(name).put(date,value);
            }
            timeS.close();
        }

        TreeSet<Person> names = new TreeSet<>(list.values());
        for(Person p: names) {
            System.out.println(p);
        }
    }
}

class Person implements Comparable<Person>{
    private String name;
    private TreeMap<Date, Double> values = new TreeMap<>();
    private double total;

    public Person(String name) {
        this.name = name;
    }
    public void put(Date d, double val) {
        values.put(d,val);
        total+=val;
    }
    @Deprecated
    public String toString() {
        String output = "";
        output+=name+"\n";
        for(Map.Entry<Date,Double> e: values.entrySet()) {
            output+=e.getKey().getMonth()+"/";
            output+=e.getKey().getDate()+"/";
            output+=e.getKey().getYear()+" ";
            output+=NumberFormat.getCurrencyInstance().format(e.getValue())+"\n";
        }
        output+= "Total Sales " + NumberFormat.getCurrencyInstance().format(total)+"\n";
        return output;
    }

    public int compareTo(Person o) {
        return Double.compare(o.total,total);
    }
}
