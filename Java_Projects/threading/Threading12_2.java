package threading;

import java.util.HashSet;
import java.util.Set;

public class Threading12_2 {
    public static void main(String[] args) {
        long beginTime = System.currentTimeMillis();

        long numb = 2;

        Set<Integer> primes = new HashSet<>();
        primes.add(2);

        for(int i = 3;;i++) A:{
            for(Integer prime: primes) {
                if(i%prime==0)
                    break A;
            }
            primes.add(i);
            if(numb*i>100000)
                break;
            numb*=i;
        }

        long endTime = System.currentTimeMillis();
        System.out.println((endTime-beginTime) + " " + numb + " " + primes.size());
    }
}