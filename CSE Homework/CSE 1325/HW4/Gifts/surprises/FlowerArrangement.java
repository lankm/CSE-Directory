package surprises;

public class FlowerArrangement implements Gift {
    public void surpriseRecipient(String name){
        System.out.printf("~~~Flowers for you!~~~: %s\n", name);
    }
}
