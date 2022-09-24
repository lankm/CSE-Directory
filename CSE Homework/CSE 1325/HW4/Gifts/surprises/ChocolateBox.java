package surprises;

public class ChocolateBox implements Gift {
    public void surpriseRecipient(String name){
        System.out.printf("***Chocolates for you!!***: %s\n", name);
    }
}
