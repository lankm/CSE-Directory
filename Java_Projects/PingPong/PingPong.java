package PingPong;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class PingPong {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\PingPong\\pingpong.dat"));

        int max = Integer.parseInt(in.nextLine());  //since the index is used later; must go from 0 up
        for(int i = 0;i<max;i++) {
            Player[] players = new Player[Integer.parseInt(in.nextLine())];

            for(int j = 0;j<players.length;j++) {   //gets the information in
                players[j] = new Player(in.next(),in.next().charAt(0),in.next().charAt(0),in.nextLine().charAt(1));
            }

            for(int p = 0;p<players.length;p+=2) { //stores in memory who each player has played
                players[p].play(players[p+1]);
                players[p+1].play(players[p]);
            }

            for(int r = 0; r<3;r++) {
                for(Player p: players)  //increases the round number for each object.
                    p.round++;

                ArrayList<Player> data = new ArrayList<>();
                for(Player p: players)  //orders by part 2
                    data.add(p);
                Collections.sort(data); //orders by wins

                for(int p = 0;p<data.size();p+=2) { //part c. changes the order if the people have already played.
                    Player A = data.get(p);
                    Player B = data.get(p+1);

                    if(A.hasPlayed(B)) {   //if the people have played
                        for (int k = p+2;k<data.size();k++) {

                            Player X = data.get(k);
                            if (!A.hasPlayed(X)) {  //if they haven't played
                                data.remove(X);
                                data.add(p+1,X);
                                break;
                            }
                        }
                    }
                }

                Player A = data.get(data.size()-2);
                Player B = data.get(data.size()-1);
                if(A.hasPlayed(B)) {    //if the last two players have played
                    for(int l = data.size()-3;l>=0;l--) {   //goes from bottom to top checking
                        if(!B.hasPlayed(data.get(l))) { //checks for if the switching player hasn't been played
                            int offset = -(l % 2 * 2 - 1);  //gets the up/down val for the opponent

                            if (!A.hasPlayed(data.get(l + offset))) {
                                data.set(data.indexOf(A),data.get(l));    //switches the two players
                                data.set(data.indexOf(data.get(l)),A);
                                break;
                            }
                        }
                    }
                }

                for(int p = 0;p<data.size();p+=2) { //stores in memory who each player has played
                    data.get(p).play(data.get(p+1));
                    data.get(p+1).play(data.get(p));
                }

                print(i+1,r+2,data);    //prints the current round.
            }
        }
    }
    public static void print(int testCase, int round, ArrayList<Player> players) {
        System.out.println("TEST CASE #" + testCase + " ROUND " + round + ":");
        for(Player p: players)
            System.out.println(p.getName());
        System.out.println();
    }
}
class Player implements Comparable<Player>{
    private String name;
    private boolean[] scores = new boolean[3];
    int round = 0;
    private Set<Player> played = new HashSet<>();

    public Player(String name, char roundOne, char roundTwo, char roundThree) {
        this.name = name;

        scores[0] = roundOne=='W'?true:false;
        scores[1] = roundTwo=='W'?true:false;
        scores[2] = roundThree=='W'?true:false;
    }

    public String getName() {
        return name;
    }

    public char getScore(int i) {
        return scores[i]?'W':'L';
    }

    public int totalWins() {   //returns the total amount of wins up to the round.
        int output = 0;
        for(int i = 0; i<round;i++) {
            if(scores[i])
                output++;
        }
        return output;
    }

    public void play(Player p) {
        played.add(p);
    }

    public boolean hasPlayed(Player p) {
        return played.contains(p);
    }

    public String toString() {
        return name + " " + getScore(0) + " " + getScore(1) + " " + getScore(2);
    }

    public int compareTo(Player player) {
        int totWins = totalWins();
        int totWins2 = player.totalWins();

        return -(totWins-totWins2);
    }
}
