/* README
 * runs same as sample run in assignment. when asking for a break it defaults to continuing with orders.
 */

import java.util.Scanner;

import chilistuff.Customer;
import chilistuff.Employee;
import chilistuff.StarbucksCup;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedHashMap;
import java.util.Map;

public class Main1 {
    public static LinkedHashMap<Customer, StarbucksCup> orders = new LinkedHashMap<Customer, StarbucksCup>();
    public static int hc;   //Half cups since a Tall is 1.5 cups.
    public static void main(String args[]) throws FileNotFoundException {   //I'm being lazy and just handling the exception here.
        Employee chef = new Employee(input("Hello! What is your name chef? "));
        printf("\n--Welcome %s--\n", chef.getName());
        printf("Checking today's customers...");

        File f = new File("CSE Homework\\CSE 1325\\HW3\\Chili\\orders.dat");
        Scanner fIn = new Scanner(f);  //change location as needed. This would only work on my machine.
        while(fIn.hasNextLine()) {
            String line = fIn.nextLine();
            if(line.equals(""))
                break;

            String[] values = line.split(",");
            orders.put(new Customer(values[0]), new StarbucksCup(values[1]));
        }
        fIn.close();
        printf("done!\n");

        hc=8*Integer.parseInt(input("\nHow many batches of your famous chili are you making today %s? ", chef.getName()));
        printf("\nStarting orders...\n");

        int i=0;
        for(Map.Entry<Customer, StarbucksCup> entry: orders.entrySet()) {
            Customer c=entry.getKey();
            StarbucksCup s=entry.getValue();

            printf("\nCustomer %d: %s's order is %s.\n", i++ +1, c.getName(), s.name);
            if(hc>=s.size) {
                printf("Order served. ");
                hc-=s.size;
                if(hc<=2)   //don't know the exact value wanted.
                    printf("Not much chili left!\n");
                else
                    printf("Still got lots of chili!\n");
            } else {
                String ans=input("Sorry, not enough chili. Would you like to make an other batch or quit(y/quit)? ");
                if(ans.toLowerCase().equals("y")) {
                    hc+=8*Integer.parseInt(input("How many batches will you make? "));
                }
                else if(ans.toLowerCase().equals("quit")) {
                    System.exit(0);
                } else {
                    printf("Invalid input. Quitting.");
                    System.exit(0);
                }
            }

            String ans=input("\ncontinue with orders or take a break? ").toLowerCase();
            if(ans.equals("break")) {
                input("Ok. Press enter to continue when you are finished with your break.\n");
            }
        }
        printf("Out of customers. Closing down.");
    }

    public static Scanner in = new Scanner(System.in);
    public static String input(String format, Object... args) {
        System.out.printf(format, args);

        return in.nextLine();
    }
    public static void printf(String format, Object... args) {
        System.out.printf(format, args);
    }
}
