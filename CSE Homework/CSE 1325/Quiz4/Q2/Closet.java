import java.util.Scanner;
import java.util.Map.Entry;

public class Closet implements Container {

    @Override
    public void pickItem() {
        System.out.printf("All items to pick from:\n");
        int i=1;
        for(Entry<String, Integer> item: items.entrySet()) {
            System.out.printf(" %d. %s: %d\n", i++,item.getKey(),item.getValue());
        }
        

        Scanner in = new Scanner(System.in);
        System.out.printf("Please select an item:\n");
        while(true) {
            String input = in.nextLine();
            Integer num = items.get(input);

            if(num==null) {
                System.out.printf("Not a valid item. Select again:\n");
                continue;
            }

            pickItem(input);
            break;
        }
        in.close();
    }

    @Override
    public void pickItem(String itemName) {
        Integer num = items.get(itemName);
        if(num==null) {
            System.out.printf("You have no %s\n",itemName);
            return;
        }
        System.out.printf("You have %s. Total currently: %d\n",itemName, items.get(itemName));
        
    }

    @Override
    public void addItem(String itemName, int numItemsAdd) {
        Integer num = items.get(itemName);
        if(num==null)
            num=0;
        items.put(itemName, numItemsAdd+num);
        
    }
}