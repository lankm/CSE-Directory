package Jewels_WaitList;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Thirteen {
    public static Scanner in;

    static {
        try {
            in = new Scanner(new File("Java_Projects\\Jewels_WaitList\\thirteen.dat"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        for(int i = Integer.parseInt(in.nextLine());i>0;i--) {
            char[][] map = map(10);
            System.out.println(recur(map,0,0,0,0));
        }
    }

    public static char[][] map(int size) {
        char[][] map = new char[size][size];

        for(int i = 0;i<10;i++) {
            map[i]=in.nextLine().toCharArray();
        }

        return map;
    }

    public static int recur(char[][] map, int length, int x, int y,int jewels) {
        char value = ' ';   //try catch
        try {
            value = map[x][y];
        } catch(IndexOutOfBoundsException e) {
            return Integer.MAX_VALUE;
        }

        if(value=='#')  //obstacle
            return Integer.MAX_VALUE;
        if(value=='E'&&jewels==13)  //end
            return length;
        if(value=='*')
            jewels++;


        map[x][y]='#';  //replace with obstacle.

        int first = Math.min(recur(map,length+1,x,y+1,jewels),recur(map,length+1,x,y-1,jewels));
        int second = Math.min(recur(map,length+1,x+1,y,jewels),recur(map,length+1,x-1,y,jewels));
        length = Math.min(first,second);

        map[x][y]=value;    //replace with original.

        return length;
    }
}
