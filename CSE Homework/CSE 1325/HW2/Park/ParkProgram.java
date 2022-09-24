/* README
 * Sample run has .getRide(1) get index 0 instead of index 1. not convention.
 * Can't change main but its just weird.
 * 
 * program runs exactly like the sample run program.
 * There is no loops or input verification for entering data for the amusement parks. Assumes "number name"
 * for each line of input. otherwise behaviour is undefined.
 */

import parkstuff.AmusementPark;
//import parkstuff.Ride;    //not directly used.
import parkstuff.Rider;

public class ParkProgram {
    public static void main(String[] args) {
        Rider r1 = new Rider("Yaris", 45); // name, height in inches
        Rider r2 = new Rider(49); // height in inches

        AmusementPark a1 = new AmusementPark(3); // 3 is the number of rides in the amusement park
        a1.getRide(1).addLine(r1); // add a rider to the line of a ride

        AmusementPark a2 = new AmusementPark(2); // 2 is the number of rides in the amusement park
        a2.getRide(1).addLine(r2); // add a rider to the line of a ride

    }
}