package parkstuff;
/* README
 * Main method in Main.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * Simple object that holds the name and height of a rider.
 */

public class Rider {
    private String name="";
    private int height=-1;

    //CONSTRUCTORS
    public Rider(String name, int height) {
        this.name=name;
        this.height=height;
    }
    public Rider(int height) {
        this("", height);
    }

    //GETTERS/SETTERS
    public String getName() {
        return name;
    }
    public int getHeight() {
        return height;
    }
    public void setName(String name) {
        this.name=name;
    }
    public void set(int height) {
        this.height=height;
    }
}