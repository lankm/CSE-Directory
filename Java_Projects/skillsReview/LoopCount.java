package skillsReview;

public class LoopCount {
    public static void main(String[] args) {
        int loopCount=1;
        while(loopCount<=10) {
            System.out.println("Welcome");
            loopCount+=1;
        }

        for(loopCount=1;loopCount<=10;loopCount++)
            System.out.println("Welcome");
    }
}
