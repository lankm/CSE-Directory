package parkstuff;
/* README
 * Main method in Main.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * constains a constructor and method defined in assignment description.
 * 
 * The line datatype is a Queue. this is really just practice for me. Would be
 * best data structure for the circumstance.
 */

import java.util.LinkedList;
import java.util.Queue;

public class Ride {
    private String name="";
    private int minHeight=-1;
    private Queue<Rider> line = new LinkedList<>();

    //CONSTRUCTORS
    public Ride(String name, int minHeight) {
        this.name=name;
        this.minHeight=minHeight;
    }

    //METHODS
    public void addLine(Rider r1) {
        if(r1.getHeight()<=minHeight)
            System.out.printf("\n-Sorry can't add rider-too short.\n\n");
        else {
            System.out.printf("\n-Adding rider to line.\n\n");
            line.add(r1);
        }
    }

    //GETTERS/SETTERS
    public String getName() {
        return name;
    }
    public int getMinHeight() {
        return minHeight;
    }
    public void setName(String name) {
        this.name=name;
    }
    public void setMinHeight(int minHeight) {
        this.minHeight=minHeight;
    }
}
