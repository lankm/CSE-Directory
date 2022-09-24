package deliverystuff;

public class Order {
    public String type="";
    public String meal="";
    public String lime="";
    public String sause="";

    public Order(String type, String meal, String lime, String sause) {
        this.type=type;
        this.meal=meal;
        this.lime=lime;
        this.sause=sause;
    }

    public void printOrder() {
        System.out.printf("%s: %s, %s, %s\n", type, meal, lime, sause);
    }
}