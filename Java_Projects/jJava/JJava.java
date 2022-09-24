package jJava;

import java.util.Scanner;
import java.util.Set;

public class JJava {
    public static final String INTEGER_REGEX = "[+-]?\\d+";
    public static final String DOUBLE_REGEX = "[+-]?\\d*\\.?\\d+";

    public static String verifyString(String prompt, String regex, String errMessage) {
        Scanner in = new Scanner(System.in);
        System.out.print(prompt); // prompts the user

        while (true) { // loops until input given matches the regular expression
            String s = in.nextLine();
            if (s.matches(regex)) {// returns if the the input if it is in the correct format.
                in.close();
                return s;
            }
            System.out.print(errMessage);
        }
    }

    public static String verifySet(String prompt, Set<String> valid, String errMessage, boolean ignoreCase) {
        Scanner in = new Scanner(System.in);
        System.out.print(prompt); // prompts the user

        while(true) {
            String s = in.nextLine();
            for(String str: valid) {
                if (ignoreCase && str.toLowerCase().equals(s.toLowerCase())) {
                    in.close();
                    return s;
                }
                else if(str.equals(s)) {
                    in.close();
                    return s;
                }
            }
            System.out.print(errMessage);
        }
    }

    public static <E extends Comparable<Number>> double verifyRange(String prompt, E lowerBound, E upperBound , String errMessage) {
        Scanner in = new Scanner(System.in);
        System.out.print(prompt); // prompts the user

        double low = Double.parseDouble(lowerBound.toString());
        double high = Double.parseDouble(upperBound.toString());

        while(true) {
            String s = in.nextLine();
            Double d = Double.parseDouble(s);
            if(d.compareTo(high)<=0&&d.compareTo(low)>=0) {
                in.close();
                return d;
            }
            System.out.print(errMessage);
        }
    }
    
    @SafeVarargs
    public static <E extends Comparable<Number>> double average(E... numbers) {
        double total = 0;
        for (E number : numbers) {
            total += Double.parseDouble(number.toString());
        }
        return total / (numbers.length);
    }

    public static double round(double numb, int prec) {
        numb *= Math.pow(10, prec);
        numb = Math.round(numb) / Math.pow(10, prec);
        return numb;
    }
}
