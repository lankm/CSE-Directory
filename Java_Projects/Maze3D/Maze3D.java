package Maze3D;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Maze3D {
    static char[][][] asteroidField;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Maze3D\\maze3D.dat"));
        

        for (int count = in.nextInt(); count > 0; count--) {
            int r = in.nextInt();   //sets the asteroid field to the required size.
            int c = in.nextInt();
            int f = in.nextInt();
            asteroidField = new char[f][r][c];
            in.nextLine();

            int startFloor = -1;
            int startX = -1;
            int startY = -1;

            for(int i = 0;i<f;i++) {    //puts the data into asteroidField
                for(int j = 0;j<r;j++) {
                    char[] line = in.nextLine().toCharArray();
                    for(int l = 0;l<c;l++) {
                        if(line[l]=='S') {
                            startFloor = i;
                            startX = l;
                            startY = j;
                            asteroidField[i][l][j] = '.';
                        }
                        else
                            asteroidField[i][l][j] = line[l];
                    }
                }
            }

            int minDist = recur(startFloor,startX,startY,0,3);
            if(minDist==Integer.MAX_VALUE)
                System.out.println("STUCK");
            else
                System.out.println(minDist + " MOVES");
        }
    }
    public static int recur(int curFloor,int curX, int curY, int length, int shotsLeft) {   //returns true if it finds the E
        char curChar;

        try {   //if the place is off the map
            curChar = asteroidField[curFloor][curX][curY];
        } catch(IndexOutOfBoundsException e) {  //for if the place is outside the map
            return Integer.MAX_VALUE;
        }

        if(curChar=='#')    //if run into a large asteroid
            return Integer.MAX_VALUE;

        if(curChar=='*') {  //if you run into a small asteroid
            if (shotsLeft == 0)
                return Integer.MAX_VALUE;
            shotsLeft--;
        }

        if(curChar=='E')    //returns the length if it finds the end.
            return length;

        asteroidField[curFloor][curX][curY] = '#';
        int output = Integer.MAX_VALUE;
        output = Math.min(output,recur(curFloor-1,curX,curY,length+1,shotsLeft));   //up
        output = Math.min(output,recur(curFloor+1,curX,curY,length+1,shotsLeft));   //down
        output = Math.min(output,recur(curFloor,curX-1,curY,length+1,shotsLeft));   //left
        output = Math.min(output,recur(curFloor,curX+1,curY,length+1,shotsLeft));   //right
        output = Math.min(output,recur(curFloor,curX,curY-1,length+1,shotsLeft));   //forward
        output = Math.min(output,recur(curFloor,curX,curY+1,length+1,shotsLeft));   //back
        asteroidField[curFloor][curX][curY]=curChar;

        return output;
    }
}
