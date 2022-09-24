package Golf_Moose;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Moose {
    public static char[][] map = new char[10][10];
    public static int largest = -1;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Golf_Moose\\moose.dat"));
        for (int i = Integer.parseInt(in.nextLine()); i > 0; i--) {

            for (int y = 0; y < 10; y++) { // sets values form map.txt
                map[y]=in.nextLine().toCharArray();
            }

            for (int y = 0; y < 10; y++) { // searches for groups of trees
                for (int x = 0; x < 10; x++) {
                    if (map[x][y]=='M')
                        largest = Math.max(recur(x, y), largest);
                }
            }
            System.out.println(largest);
            largest=-1;
        }
        in.close();
    }

    public static int recur(int x, int y) { // returns the total number of trees in the group
        map[x][y] = 'n'; // sets to n so it is not counted again

        int total = 0;
        if (map[x][y - 1 <= 0 ? y : y - 1]=='M') // up
            total += recur(x, y - 1);
        if (map[x - 1 <= 0 ? x : x - 1][y]=='M') // left
            total += recur(x - 1, y);
        if (map[x][y + 1 >= map.length ? y : y + 1]=='M') // down
            total += recur(x, y + 1);
        if (map[x + 1 >= map.length ? x : x + 1][y]=='M') // right
            total += recur(x + 1, y);
        return total + 1; // return the single block that its currently on
    }
}

