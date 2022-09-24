package money;
/* README
 * Main method in Main.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * Extra constructors are given.
 * 
 * Repeats asking where you are. loop is in main.
 */

import java.util.Scanner;

public class Airport {
    private Office north=null;
    private Office east=null;

    private Office south=null;
    private Office west=null;

    private double exchange=0;

    public Airport(Office n, Office e, Office s, Office w) {
        north=n;
        east=e;
        south=s;
        west=w;
    }
    public Airport(Office ne, Office sw) {
        this(ne, ne, sw, sw);
    }

    public boolean handleCustomer(Scanner in) {   //returns false if user input exit.
        System.out.printf("\n");
        printDots(8);

        System.out.printf("Hello traveler! Where are you in the airport: ");
        String input =in.nextLine().toLowerCase();
        switch(input) {
            case "north":
                exchange+=north.customerExchange(in);
                break;
            case "east":
                exchange+=east.customerExchange(in);
                break;
            case "south":
                exchange+=south.customerExchange(in);
                break;
            case "west":
                exchange+=west.customerExchange(in);
                break;
            case "exit":
                return false;
            default:
                System.out.printf("Invalid input. valid input is \"north\", \"east\", \"south\", \"west\", or \"exit\".\n"); 
                break;
        }
        return true;
        
    }
    private void printDots(int i) {
        for(;i>0;i--) {
            System.out.printf("*");
        }
        System.out.printf("\n");
    }

    public double getEchange() {
        return exchange;
    }
}