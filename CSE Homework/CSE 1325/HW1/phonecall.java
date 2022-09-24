//Name Landon Moon      ID:1001906270

package HW1;

import java.util.Arrays;

public class phonecall {
    public static void main(String args[]) {
        System.out.print(phoneNum("682.694.6767", "fort worth"));
    }
    public static boolean phoneNum(String num, String code) {
        String dal[] = {"214","972","469"}; //Dallas area codes
        String fw[] = {"817","682"};    //Fort Worth area codes

        boolean valid = num.matches("\\d{3}[\\s.-]\\d{3}[\\s.-]\\d{4}");    //simple regex for verifying number is in correct format.
        if(!valid)
            return valid;
        String area = num.substring(0,3);

        if(code.toLowerCase().matches("dallas"))
            return Arrays.asList(dal).contains(area);
        else if(code.toLowerCase().matches("fort worth"))
            return Arrays.asList(fw).contains(area);
        else return false;  //default is false
    }
}
