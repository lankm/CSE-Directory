package FWCD_Packet;

import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Escape {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\escape.dat"));

        for(int i = in.nextInt();i>0;i--) {
            int r = in.nextInt();
            int c = in.nextInt();
            in.nextLine();

            char[][] map = new char[r][c];
            for(int j = 0; j<r;j++) {
                map[j] = in.nextLine().toCharArray();
            }

            int xEnd = in.nextInt();
            int yEnd = in.nextInt();
            int xStart = in.nextInt();
            int yStart = in.nextInt();

            if(expansion(map,xStart,yStart,xEnd,yEnd))
                System.out.println("Escaped");
            else
                System.out.println("Trapped");
        }
    }
    public static boolean expansion(char[][] map, int xStart, int yStart, int xEnd, int yEnd) {
        Set<Point> unchecked = new HashSet<>();
        unchecked.add(new Point(xStart,yStart));

        while(true) {
            if(unchecked.isEmpty()) //if the set is empty then there has been no successful completion
                return false;

            Set<Point> temp = new HashSet<>();

            for(Point p: unchecked) {   //goes through the next set of unchecked points
                if(p.equals(new Point(xEnd, yEnd)))
                    return true;

                for(double rad = 0.0; rad<2*Math.PI; rad+=Math.PI/2) {  //goes in a circle
                    int xPlus = (int)Math.cos(rad);
                    int yPlus = (int)Math.sin(rad);

                    char val;
                    try {
                        val = map[p.y + yPlus][p.x + xPlus];
                    } catch (IndexOutOfBoundsException e) {
                        continue;
                    }

                    if(val=='#')
                        continue;
                    else
                        temp.add(new Point(p.x+xPlus,p.y+yPlus));
                }
                map[p.y][p.x] = '#';
            }
            unchecked = temp;

        }
    }
}
