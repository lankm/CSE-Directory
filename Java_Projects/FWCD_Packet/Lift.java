package FWCD_Packet;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collections;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Lift {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\FWCD_Packet\\lift.dat"));

        TreeMap<Double,Double> ratios = new TreeMap<>(Collections.reverseOrder());

        for(int i = in.nextInt();i>0;i--) {
            int length = in.nextInt();

            double[] values = new double[length];

            for(int j = 0 ; j < length;j++) {
                values[j] = in.nextInt();
            }
            for(double d: values) {
                double worth = in.nextDouble();
                if(ratios.containsKey(worth/d))
                    ratios.put(worth/d,ratios.get(worth/d)+d);
                else
                    ratios.put(worth/d,d);
            }

            int total = in.nextInt();

            double curAmount = 0;
            double value = 0;
            for(Map.Entry<Double,Double> e: ratios.entrySet()) {
                double worth = e.getKey();
                double amount = e.getValue();

                System.out.println(e);
                if(!(amount+curAmount>total)) {
                    curAmount += amount;
                    value+=worth*amount;
                } else {
                    value+=(total-curAmount)*worth;
                    break;
                }
            }

            System.out.printf("$%.2f\n",value);
        }



    }
}
