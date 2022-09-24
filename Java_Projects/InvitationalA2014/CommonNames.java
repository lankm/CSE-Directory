package InvitationalA2014;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class CommonNames {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvitationalA2014\\Commonnames.dat"));

        for (int i = Integer.parseInt(in.nextLine()); i > 0; i--) {
            TreeMap<String, Integer> names = new TreeMap<>();
            for(String name: in.nextLine().split(" ")) {
                if(names.containsKey(name))
                    names.put(name,names.get(name)+1);
                else
                    names.put(name, 1);
            }
            int max = -1;
            for(Map.Entry<String, Integer> entry: names.entrySet()) {
                Integer number = entry.getValue();
                max=Math.max(max,number);
            }
            for(Map.Entry<String, Integer> entry: names.entrySet()) {
                if(entry.getValue()==max)
                    System.out.print(entry.getKey() + " ");
            }
            System.out.println();
        }
    }
}
