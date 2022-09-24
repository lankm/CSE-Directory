package DayOfTheWeek;

import java.util.Scanner;

public class Majors {
    public enum majors {
        ACC("Business"),CHEM("Science"),CIS("Business"),
        ENG("Humanities"),HIS("Humanities"),PHYS("Science");

        String div;

        majors(String div) {
            this.div = div;
        }

        public String toString() {
            return this.name()+" is a part of " + div;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.print("Enter the your major(ACC, CHEM, CIS, ENG, HIS, PHYS): ");
        while(true) {
            String day = in.nextLine();

            try {
                System.out.print(majors.valueOf(day.toUpperCase()));
                break;
            } catch(IllegalArgumentException e) {
                System.out.print("Not a major. Try again: ");
            }
        }
        in.close();
    }
}
