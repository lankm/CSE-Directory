//This class is an example. 

import watches.Watch;

public class WatchInfoMain {
    public static void main(String[] args) {
        Watch w = new Watch("gold", "12h 05m pm", 800, 55);
        //                  mat     time        price   age(years)
        w.break_obj();
        w.repair();
        w.setTime("04h 13m pm");
        System.out.printf(w.getTime());
    }
}
