import java.util.HashMap;

public interface Container {
    String ownerName="Anonymous";
    HashMap<String, Integer> items = new HashMap<String, Integer>();  

    void pickItem();
    void pickItem(String itemName);
    void addItem(String itemName, int numItemsAdd);

}