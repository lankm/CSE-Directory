import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class DentalOffice extends Building {

    DentalOffice(String name) {
        super(name);
    }
    void addCustomer(Person p1) {
        allCustomers.add(p1);
    }
    void addCustomer(String filename) {
        allCustomers = new ArrayList<Person>();
        try (Scanner in = new Scanner(new File(filename))) {    //the filename might have to be changed depending on how your directory is set up.
                                                                //on my machine it requires going into subfolders from the main directory because people.txt is in a 1325/Quiz4/Q4 folder.
            while(in.hasNextLine()) {
                String line = in.nextLine();
                Scanner ins = new Scanner(line);
                ins.useDelimiter(",");

                Person p = new Person(ins.next(),
                                      ins.next().equals("yes"),
                                      ins.next().equals("yes"),
                                      ins.nextInt());
                allCustomers.add(p);
                ins.close();
            }
            in.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
    void showCustomers() {
        System.out.printf("--All accepted patients\n");
        for(Person p: allCustomers) {
            if(p.brushesMorning||p.brushesNight)
                System.out.printf("%s\n", p.name);
        }
        System.out.printf("\n");
    }
}

abstract class Building {
    String name;
    ArrayList<Person> allCustomers;

    Building(String name){
        this.name=name;
    }
    abstract void addCustomer(Person p1);
    abstract void addCustomer(String filename);
    abstract void showCustomers();
}
