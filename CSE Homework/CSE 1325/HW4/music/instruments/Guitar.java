package instruments;

import java.util.Scanner;

public class Guitar extends Instrument {
    public int strings=-1;

    public Guitar(String brand, int strings) {
        super(brand);
        this.strings=strings;
    }

    public void play(String sheetMusic) {
        Scanner smin = new Scanner(sheetMusic);
        while(smin.hasNext()) {
            String notes = smin.next();
            if(notes.charAt(0)!='G') {
                continue;
            } else {
                System.out.printf("--Playing guitar:\n");
            }

            for(int i=0; i<strings;i++)
                System.out.printf("%s\n", notes.substring(2,notes.length()));
        }
        smin.close();
    }
}
