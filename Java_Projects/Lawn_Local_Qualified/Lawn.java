package Lawn_Local_Qualified;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Lawn {
    private static char[][] map; // [row][column]

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Lawn_Local_Qualified\\lawn.dat"));
        for (int i = in.nextInt(); i > 0; i--) {
            int r = in.nextInt();
            int c = Integer.parseInt(in.nextLine().trim()); //uses next line to make setup easier

            map = new char[r][c];   //sets the map for the current lawn
            for (int j = 0; j < r; j++) {
                String line = in.nextLine();
                map[j] = line.toCharArray();
            }
            mow();
            print();
        }
    }

    private static void mow() {
        int startR = -1;
        int startC = -1;

        for (int i = 0; i < map.length; i++) { //sets the beginning, and sets all periods to s.
            char[] line = map[i];
            for (int j = 0; j < line.length; j++) {
                if (line[j] == '=') {//should only happen once, sets beginning.
                    startR = i;
                    startC = j;
                } else if (line[j] == '.')    //replacing all land with s except *
                    map[i][j] = 's';
            }
        }
        recur(startR, startC, 0); //mows the lawn
        cover();
    }

    private static void recur(int r, int c, int dir) {
        try {
            if (map[r][c] == 'X')   //if the spot has already been mowed
                return;
        } catch (IndexOutOfBoundsException e) {   //if starting point is outside the map
            return;
        }

        if (cut(r, c)) {
            if (dir != 3) recur(r - 1, c, 1); //up
            if (dir != 4) recur(r, c - 1, 2); //left
            if (dir != 1) recur(r + 1, c, 3); //down
            if (dir != 2) recur(r, c + 1, 4); //right
        }
    }

    private static boolean cut(int r, int c) {   //cuts the area with the big mower. returns false if it cant cut
        for (int i = r; i < r + 3; i++) {   //looks for an obstruction
            for (int j = c; j < c + 3; j++) {
                try {
                    if (map[i][j] == '*')
                        return false;
                } catch (IndexOutOfBoundsException e) {
                    return false;
                }
            }
        }
        for (int i = r; i < r + 3; i++) {   //cuts grass
            for (int j = c; j < c + 3; j++) {
                try {
                    if (map[i][j] != 'X')
                        map[i][j] = 'B';
                } catch (IndexOutOfBoundsException ignored) {

                }
            }
        }
        map[r][c] = 'X';  //X's mean where the mower has been
        return true;
    }

    private static void cover() {    //replaces the X's used with the proper value B
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                if (map[i][j] == 'X')
                    map[i][j] = 'B';
            }
        }
    }

    private static void print() {    //prints map
        for (char[] line : map) {
            for (char c : line) {
                System.out.print(c);
            }
            System.out.println();
        }
        System.out.println();
    }
}
