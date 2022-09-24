package instruments;

import java.util.Scanner;

public class Piano extends Instrument{
    int size=-1;

    public Piano(String brand, int size) {
        super(brand);
        this.size=size;
    }
    public void play(String sheetMusic) {
        Scanner smin = new Scanner(sheetMusic);
        while(smin.hasNext()) {
            String notes = smin.next();
            if(notes.charAt(0)!='P') {
                continue;
            } else {
                System.out.printf("~~~Playing piano: ");
            }

            System.out.printf("%s\n", notes.substring(2,notes.length()));
        }
        smin.close();
    }

    public void play(String sheetMusic, boolean expert) {
        if(!expert) {
            System.out.printf("Sorry, only experts are allowed to ply. Please leave.\n");
            return;
        } else if (size<3) {
            System.out.printf("Sorry, I require a larger piano, I refuse to play on this one.\n");
            return;
        }

        Scanner smin = new Scanner(sheetMusic);
        while(smin.hasNext()) {
            String notes = smin.next();
            if(notes.charAt(0)!='P') {
                continue;
            } else {
                System.out.printf("EXPERT! Playing piano: ");
            }

            System.out.printf("%s\n", notes.substring(2,notes.length()));
        }
        smin.close();
    }
}
