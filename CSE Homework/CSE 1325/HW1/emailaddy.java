//Name Landon Moon      ID:1001906270

package HW1;

import java.util.Scanner;

public class emailaddy {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        
        System.out.printf("Enter your email address: \n");
        String email = in.nextLine();

        boolean match = email.matches(".*@.+((.com)|(.edu))");

        if(match) {
            boolean general = email.matches(".*@.+(.com)");
            String place = email.substring(email.indexOf("@")+1, 
                                           Math.max(email.indexOf(".edu"),email.indexOf(".com")));

            System.out.printf("This is a %s email from the %s: %s", general?"general":"school", general?"company":"school", place);
        } else {
            System.out.printf("This is not a valid email address.\n");
        }
        

        in.close();
    } 
}
