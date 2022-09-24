//Name Landon Moon      ID:1001906270

package HW1;

import java.util.Scanner;

public class grapes {
    public static void main(String args[]) {
        String [] grapeInfo=enterInput(3); //why is the program set up to contain what im assuming is name info when the types are defined. You might want just the raw input from the user?
        System.out.println("\nTotal grapes: "+getTotal("grape", grapeInfo)+"\n"); 
        System.out.println("Total grape leaves: "+getTotal("grape leaves", grapeInfo)+"\n");
    }

    public static String[] enterInput(int max) {
        System.out.printf("%d grape farms!\n", max);

        Scanner in = new Scanner(System.in);
        String info[] = new String[max];

        for(int i=0;i<max;i++) {
            System.out.printf("\n%d. Enter the number of grapes and the number of grape leaves, separated by a space:\n", i+1);
            info[i]=in.nextLine();
        }

        in.close();
        return info;

    }
    public static int getTotal(String type, String[] info) {
        int total=0;

        if(type.matches("grape")) {
            for(int i = 0; i<info.length; i++) {
                total+=Integer.parseInt(info[i].substring(0,info[i].indexOf(" ")));
            }
        }
        else if(type.matches("grape leaves")) {
            for(int i = 0; i<info.length; i++) {
                total+=Integer.parseInt(info[i].substring(info[i].indexOf(" ")+1));
            }
        }
        else
            return -1;

        return total;

    }
}
