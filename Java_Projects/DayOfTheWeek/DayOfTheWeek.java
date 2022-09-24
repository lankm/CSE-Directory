package DayOfTheWeek;

import java.util.Scanner;

public class DayOfTheWeek {
    public enum days {
        SUNDAY(13, 18), MONDAY(9, 21), TUESDAY(9, 21),
        WEDNESDAY(9, 21), THURSDAY(9, 21), FRIDAY(9, 22),
        SATURDAY(9, 18);

        int start;
        int end;

        days(int s, int e) {
            start = s;
            end = e;
        }

        public String toString() {
            String start = this.start<12?this.start+" AM":this.start-12+" PM";
            String end = this.end<12?this.end+" AM":this.end-12+" PM";

            return "On " + this.name().toLowerCase() + " the business is open from " + start + " to " + end;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.print("Enter the day of the week: ");
        while(true) {
            String day = in.nextLine();

            try {
                System.out.print(days.valueOf(day.toUpperCase()));
                break;
            } catch(IllegalArgumentException e) {
                System.out.print("Not a day. Try again: ");
            }
        }
        in.close();
    }
}
