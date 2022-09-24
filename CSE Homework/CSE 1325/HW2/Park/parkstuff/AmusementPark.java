package parkstuff;
/* README
 * Main method in Main.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * constructor contains input for park info. Scanner is static to syncronize multiple amusement parks.
 * Because I can not alter the main method, the scanner is never closed propperly.
 */

import java.util.LinkedHashSet;
import java.util.Scanner;

public class AmusementPark {
    private LinkedHashSet<Ride> rides = new LinkedHashSet<>();
    private static Scanner in = new Scanner(System.in); //made to keep each constructor using the same scanner

    public AmusementPark(int numRides) {
        System.out.printf("~~~Amusement Park Info~~~");
        for(int i=0; i<numRides; i++) {
            System.out.printf("\nRide %d- Enter minimum ride height and ride name:\n", i+1);
            
            int minHeight=in.nextInt();
            String name=in.nextLine();
            Ride r=new Ride(name, minHeight);

            rides.add(r);
        }
    }

    public Ride getRide(int index) {
        return rides.toArray(new Ride[0])[index-1];
    }
}