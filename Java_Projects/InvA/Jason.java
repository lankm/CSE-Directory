package InvA;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Jason {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("Java_Projects\\InvA\\jason.dat"));

        for(int i = in.nextInt();i>0;i--) {
            double a = in.nextDouble();
            double b = in.nextDouble();
            double c = in.nextDouble();

            boolean dir = a>0;
            double x = -b/2/a;
            double y = a*Math.pow(x,2)+b*x+c;

            System.out.printf("(%.3f,%.3f)-->"+(dir?"UPWARD":"DOWNWARD")+"\n",x,y);

        }
    }
}
