package firstFour;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class FamilyTree {

    static int upTicks = 0; // steps up from first line of input
    static int downTicks = 0; //steps down from first line of input
    static Map<String, Integer> family = new HashMap<>();   //contains the names and index of their generation

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\firstFour\\family2.dat"));
        while(in.hasNextLine()) {
            setData(in.next(),in.next(),in.nextLine().trim());
        }
        print();
    }
    public static void setData(String nameOne, String identifier, String nameTwo) { //sets the names given with the correct relation
        boolean firstExists = family.containsKey(nameOne);
        boolean secondExists = family.containsKey(nameTwo);

        if(!firstExists&!secondExists) { //if neither name exists. should be first input line
            family.put(nameOne,0);
            family.put(nameTwo, 0+indexData(identifier));
            downTicks+=1;
        } else if(firstExists&!secondExists) { //if only the first exists.
            int index = family.get(nameOne)+indexData(identifier);
            setLengths(index);
            family.put(nameTwo,index);
        } else if(!firstExists&secondExists) { //if only the second exists. if both already exist then no change is needed.
            int index = family.get(nameTwo)-indexData(identifier);
            setLengths(index);
            family.put(nameOne,index);
        }
    }
    public static void setLengths(int i) {  //determines the required change in size for upTicks and downTicks.
        if(i<-upTicks) //there's no way i is more than one more than upticks
            upTicks+=1;
        if(i>=downTicks)    //>= needed because of arrays starting at 0
            downTicks+=1;
    }
    public static int indexData(String identifier) {    //finds the difference needed between the two names
        if(identifier.equals("SIBLING"))
            return 0;
        else return 1;
    }
    public static void print() {    //prints all the current data
        String[] names = new String[upTicks+downTicks]; //upTicks plus downTicks are the total size of the array.
        for(int i = 0;i<upTicks+downTicks;i++) {    //sets up the beginning of each line
            names[i] = ordinal(i+1)+" Generation: ";
        }
        for(Map.Entry<String,Integer> entry: family.entrySet()) {   //puts the names of the people on the right lines
            names[entry.getValue()+upTicks]+=entry.getKey()+" ";
        }
        for(String s: names) {  //prints each line in the names array
            System.out.println(s.trim());
        }
    }
    public static String ordinal(int i) { // returns the correct ordinal indicator for 1 through 20.
        if(i==1)
            return "1st";
        else if(i==2)
            return "2nd";
        else if(i==3)
            return "3rd";
        else
            return i+"th";
    }
}
