package FWCD_Packet;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Blast {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\blast.dat"));

        char[][] map = new char[10][10];
        int startX=-1;
        int startY=-1;
        for(int i = 0;i <10;i++) {
            char[] line = in.nextLine().toCharArray();

            if (startX == -1) {
                for (int j = 9; j >= 0; j--) {
                    if (line[j] == 'S') {
                        startX = i;
                        startY = j;
                    }
                }
            }

            map[i] = line;
        }

        if(blast(map,startX,startY,in.nextInt()))
            System.out.println("Escaped!");
        else
            System.out.println("Impossible");
    }

    public static boolean blast(char[][] map, int x, int y, int energy) {
        System.out.print(x + " " + y + " ");

        char cur;

        try {
            cur = map[x][y];
        } catch (Exception e) {
            return false;
        }

        System.out.println(cur + " " + energy);


        if(energy==1)
            return false;
        if(cur=='X')
            return false;
        if(cur=='E')
            return true;

        if(cur=='*')
            energy-=5;
        else
            energy-=1;

        map[x][y] = 'X';
        boolean answer =  blast(map,x+1,y,energy) ||
                blast(map,x,y+1,energy) ||
                blast(map,x-1,y,energy) ||
                blast(map,x,y-1,energy);
        map[x][y] = cur;

        return  answer;

    }
}
