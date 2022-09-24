package watches;

public abstract class Product implements Repairable, Timeable {
    protected boolean designer=false;
    protected boolean antique=false;
    protected boolean working=true;
    protected double price = 0;
    protected String material="";   //really should be an enum
    protected String time="00h-00m";    //time does not pass lol

    public Product(String mat, String time, double price, int age) {
        this.material=mat;
        this.time=time;
        this.price=price;

        if(price>800)
            designer=true;
        if(age>50)
            antique=true;
    }
}
