package InvitationalA2014;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ConnectFour {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvitationalA2014\\connectfour.dat"));

        for (int i = Integer.parseInt(in.nextLine()); i > 0; i--) A:{
            char[][] map = new char[6][7];

            for(int j = 0; j < map.length; j++) {
                map[j] = in.nextLine().toCharArray();
            }

            for(int j = 0; j < map.length; j++) {
                for(int k = 0; k < map[j].length; k++) {    //goes to each point once. left to right, top down.

                    char center = map[j][k];

                    if(center == '-')   //gets the point to test around
                        continue;

                    for (double l = 0; l < 2 * Math.PI; l += Math.PI / 4) { //goes in a circle
                        int xDir = (int)Math.round(Math.cos(l));
                        int yDir = (int)Math.round(Math.sin(l));

                        for (int m = 1;; m++) {   //goes in one direction
                            char point = ' ';
                            try {   //gets the point
                                int x = j+yDir*m;   //goes clockwise instead of counter clockwise. it works tho
                                int y = k+xDir*m;
                                point = map[x][y];
                            } catch(IndexOutOfBoundsException e) {
                                break;
                            }

                            if(point == '-')    //stops at a blank
                                break;
                            if(point != center) //stops at the other teams chip
                                break;

                            if(m==3) {  //if a case of four in a row is found
                                if(center=='r')
                                    System.out.println("Red Wins");
                                else if(center=='b')
                                    System.out.println("Blue Wins");
                                break A;
                            }
                        }
                    }
                }
            }
            System.out.println("No wins");
        }
    }
}
