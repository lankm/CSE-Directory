package Octopusses_PhoneNumbers_Squares;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Octopusses {
    private static ArrayList<ArrayList<Integer>> map;
    private static int[] players;
    private static Random rand;
    private static int round = 0;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\Octopusses_PhoneNumbers_Squares\\octopusses.dat"));
        for (int i = in.nextInt(); i > 0; i--) {
            players = new int[in.nextInt()];
            rand = new Random(in.nextLong());

            map = new ArrayList<ArrayList<Integer>>();
            for(int j = 0;j<64;j++) {
                map.add(new ArrayList<>());
            }

            for(int j = in.nextInt()+in.nextInt();j>0;j--) {
                map.get(in.nextInt()-1).add(in.nextInt()-1);
            }

            //JJava.debug(map);
            int player = play();
            System.out.println("Player "+(char)(65+player)+" wins after "+(round+1)+" rolls!");
        }
    }
    public static int play() {  //returns the index of the player that won
        for(;true;round++) {
            for(int i = 0;i<players.length;i++) {   //plays everyone one turn
                //System.out.print("Player "+ i + ": ");

                players[i] = turn(players[i]);  //sets the index of the player for the next roll
                //System.out.println();

                if(players[i]>63)
                    return i;
            }
        }
    }
    public static int turn(int index) {
        //System.out.print(index + " ");

        int roll = rand.nextInt(6)+1;
        index+=roll;
        //System.out.print(roll+" ");

        //System.out.print(index+" ");
        if(index>=64)
            return index;
        return tele(index, roll);
    }
    public static int tele(int index, int roll) {
        if(map.get(index).size()==0) {
            return index;
        }
        int newroll = roll;
        if(roll>=map.get(index).size())
            newroll = (roll-1)%map.get(index).size();

        //System.out.print(map.get(index).get(roll)+" ");

        return tele(map.get(index).get(newroll), roll);
    }
}
