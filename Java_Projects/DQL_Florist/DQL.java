package DQL_Florist;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class DQL {
    public static void main(String[] args) throws FileNotFoundException {
        ArrayList<Entry> column = new ArrayList<>();

        Scanner in = new Scanner(new File("Java_Projects\\DQL_Florist\\dql.dat"));

        in.next();
        int i = in.nextInt() + 1;
        in.nextLine();

        for (; i > 0; i--)   //data entry
            column.add(new Entry(in.nextLine()));

        int l = in.nextInt();
        in.nextLine();
        for (int j = 0; j < l; j++) {
            Scanner line = new Scanner(in.nextLine());
            line.next();
            System.out.println("Query #" + (j + 1));
            String s = line.next(); //s is the current word being examined.

            ArrayList<Integer> indexes = new ArrayList<>();

            if (s.equals("*")) {    //gets the indexes of the values
                indexes = allIndexes(column.get(0).data.size());
            } else while (true) {
                if(s.substring(s.length()-1).equals(","))
                    indexes.add(column.get(0).data.indexOf(s.substring(0,s.length()-1)));
                else {
                    indexes.add(column.get(0).data.indexOf(s));
                    break;
                }
                s = line.next();
            }
            //indexes are in.

            String condition = "";  //gets the condition statement at the end
            if(line.hasNext()) {
                line.next();
                condition = line.next();
            }

            boolean none = true;
            for(int k = 1; k<column.size();k++) {   //prints the answers
                Entry curEntry = column.get(k);
                if(curEntry.condition(column.get(0), condition)) {
                    none = false;
                    for(int index: indexes) {
                        System.out.print(column.get(k).data.get(index) + " ");
                    }
                    System.out.println();
                }
            }
            if(none==true)
                System.out.println("NONE");
            System.out.println();
        }
    }

    public static ArrayList<Integer> allIndexes(int size) {
        ArrayList<Integer> output = new ArrayList<>();
        for (int i = 0; i < size; i++)
            output.add(i);
        return output;
    }
}

class Entry {
    public ArrayList<String> data = new ArrayList<>();

    public Entry(String line) {
        Scanner in = new Scanner(line);
        while (in.hasNext())
            data.add(in.next());
            in.close();
    }

    public String toString() {
        return data.toString();
    }

    public boolean condition(Entry first, String con) {
        if(con.isEmpty())
            return true;

        String[] comparators = {">=","<=","=",">","<"};
        for(int i = 0;i<5;i++) {
            int index = con.indexOf(comparators[i]);
            if(index==-1)
                continue;

            String name = con.substring(0,index);
            String name2 = con.substring(index+comparators[i].length());
            String dataVar = data.get(first.data.indexOf(name));
            int val = dataVar.compareTo(name2);

            if(comparators[i].equals("="))
                return val==0;
            if(comparators[i].equals(">"))
                return val>0;
            if(comparators[i].equals("<"))
                return val<0;
            if(comparators[i].equals(">="))
                return val>0||val==0;
            if(comparators[i].equals("<="))
                return val<0||val==0;
        }
        return false;
    }
}
