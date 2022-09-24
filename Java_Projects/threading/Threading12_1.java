package threading;

import java.util.Scanner;

public class Threading12_1 {
    public static void main(String[] args) throws InterruptedException {
        Scanner in = new Scanner(System.in);
        Counter c = new Counter();

        System.out.print("Enter the number of threads: ");
        int numbT = in.nextInt();

        System.out.print("Enter the number of increments for each thread: ");
        int numbI = in.nextInt();

        Active[] threads = new Active[numbT];
        for(int i = 0;i<numbT;i++) {
            threads[i] = new Active(c,numbI);
        }
        for(Active a: threads) {
            a.start();
        }
        for(Active a: threads) {
            a.join();
        }

        System.out.print(c.getCount() + "/" + (numbI*numbT));
        in.close();
    }
}
class Counter {
    int count;
    void inc() {
        count = count+1;
    }
    int getCount() {
        return count;
    }
}
class Active extends Thread{
    Counter c;
    int totalLeft;

    public Active(Counter c, int i) {
        this.c = c;
        totalLeft = i;
    }

    public void run() {
        for(;totalLeft>0;totalLeft--)
            c.inc();
    }
}
