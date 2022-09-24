package money;
/* README
 * Main method in Main.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * repeats asking until valid currency is given.
 * 
 * ERROR POSIBILITY:
 * I did not check to see if the input for the amount to convert is a number or not
 * This can cause a NumberFormatException.
 */

import java.util.Scanner;

public class Office {
    String name="";
    String manager="";

    public Office(String name, String manager) {
        this.name=name;
        this.manager=manager;
    }

    public double customerExchange(Scanner in) {
        System.out.printf("Welcome to %s. Please contact the manager %s if you have any complaints.\n", name, manager);
        
        while(true) {   //repeats asking until valit input.
            System.out.printf("What currency are you converting to dollars: ");
            String input =in.nextLine().toUpperCase();
            switch(input) {
                case "EUR":
                    return convertCur(1.13, in);
                case "YEN":
                    return convertCur(.0087, in);
                case "CHF":
                    return convertCur(1.09, in);
                case "none":
                    return 0;
                default:
                    System.out.printf("Invalid input. valid input is \"EUR\", \"YEN\", \"CHF\", or \"none\".\n"); 
                    break;
            }
        }
    }

    private double convertCur(double rate, Scanner in) {
        System.out.printf("How much are you converting: ");
        double amount = Double.parseDouble(in.nextLine())*rate;
        System.out.printf("Here you go: $%.2f\n", amount);
        return amount;
    }
}