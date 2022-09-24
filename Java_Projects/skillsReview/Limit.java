package skillsReview;

public class Limit {
    public static void main(String[] args) {
        int val=1;
        final int LIMIT = 10;
        while(val<LIMIT) {
            System.out.println(val);
            val+=1;
        }

        for(val=1;val<LIMIT;val++)
            System.out.println(val);
    }
}
