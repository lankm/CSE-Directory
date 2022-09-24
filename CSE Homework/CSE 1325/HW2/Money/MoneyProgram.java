/* README
 * Program runs similarly to sample run
 * 
 * There is some input varification so thing are smooth. number input is not checked so a NumberFormatException can be thrown.
 * 
 * Currencies accepted are EUR, YEN, and CHF. if wrong input it says what is valid and asks again.
 * similar input varification for your location.
 */

import java.util.Scanner;
import money.*;

public class MoneyProgram {
    public static Scanner in = new Scanner(System.in);  //keeps Scanner syncronized accross program.
    public static void main(String[] args) {
        Airport XYZ = constructAirport();

        while(XYZ.handleCustomer(in)) {}
        System.out.printf("Total dollars given out: %.2f\nExiting...", XYZ.getEchange());

        in.close();
    }

    public static Airport constructAirport() {
        Office ne=null;
        Office sw=null;
        String temp="";

        System.out.printf("Enter the name of the North and East exchange office: ");    //would put these in a loop but thats complicated.
        temp=in.nextLine();
        System.out.printf("Enter the name of the North and East exchange office manager: ");
        ne = new Office(temp, in.nextLine());

        System.out.printf("Enter the name of the South and west exchange office: ");
        temp=in.nextLine();
        System.out.printf("Enter the name of the South and west exchange office manager: ");
        sw = new Office(temp, in.nextLine());

        return new Airport(ne, sw);
    }
}