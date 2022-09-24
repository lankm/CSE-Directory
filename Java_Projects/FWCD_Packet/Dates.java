package FWCD_Packet;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Dates {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\dates.dat"));

        for (int i = Integer.parseInt(in.nextLine()); i > 0; i--) {
            in.useDelimiter("/");

            int month = in.nextInt()-1;
            int day = in.nextInt();
            in.useDelimiter("\\w");
            in.next();
            in.useDelimiter("\\s");
            int year = in.nextInt();

            in.next();

            GregorianCalendar cal = new GregorianCalendar(year,month,day);
            cal.add(Calendar.DAY_OF_YEAR,in.nextInt());
            try {
                in.nextLine();
            } catch(NoSuchElementException e) {
                return;
            }
            System.out.printf("%02d/%02d/%04d\n",cal.get(Calendar.MONTH)+1,
                                                 cal.get(Calendar.DAY_OF_MONTH),
                                                 cal.get(Calendar.YEAR));

        }

    }
}
