package InvB;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class Constanza {
    public static void main(String[] args) throws FileNotFoundException {
        LinkedHashMap<String, String> colors = new LinkedHashMap<>();
        colors.put("red","");colors.put("orange","");
        colors.put("yellow","");colors.put("green","");
        colors.put("blue","");colors.put("indigo","");
        colors.put("violet","");

        Scanner in = new Scanner(new File("Java_Projects\\InvB\\constanza.dat"));

        while(in.hasNextLine()) {
            String color = in.nextLine();
            colors.put(color,colors.get(color)+"*");
        }

        for(Map.Entry<String, String> e: colors.entrySet()) {
            System.out.printf("%-7s%s\n",e.getKey(),e.getValue());
        }
    }
}
