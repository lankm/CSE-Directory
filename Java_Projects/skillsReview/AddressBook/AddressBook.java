package skillsReview.AddressBook;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class AddressBook {
    static Map<String,Address> addresses = new HashMap<>();
    static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        help();
        while (true) {
            System.out.print("What do you want to do: ");

            b:{ while (true) {
                    String input = in.nextLine();
                    switch (input.toLowerCase()) {
                        case "newaddress": newAddress(); break b;
                        case "deleteaddress": deleteAddress(); break b;
                        case "getinfo": getInfo(); break b;
                        case "setinfo": setInfo(); break b;
                        case "help": help(); break b;
                        case "quit": quit(); break b;
                    }
                    System.out.print("Wrong input. try again: ");
            }}

            System.out.println("Finished.\n");
        }
    }

    public static void newAddress() {   //done
        System.out.print("Enter a name: ");
        String name = in.nextLine();
        System.out.print("Enter a address: ");
        String address = in.nextLine();
        System.out.print("Enter a phone number: ");
        String phoneNumber = in.nextLine();
        System.out.print("Enter a email: ");
        String email = in.nextLine();

        addresses.put(name, new Address(address,phoneNumber,email));
    }
    public static void deleteAddress() {
        if(addresses.size()==0) {
            System.out.println("No addresses.");
            return;
        }
        printAddresses();
        String name = getName();
        addresses.remove(name);
    }
    public static void getInfo() {
        if(addresses.size()==0) {
            System.out.println("No addresses.");
            return;
        }
        printAddresses();
        String name = getName();
        String input;
        String info;

        System.out.print("What info do you want(address, phone number, or email): ");
        while(true) {
            input = in.nextLine().toLowerCase();
            info = matchInput(name,input);
            if(!info.equals("null"))
                break;
        }
        System.out.println(name + ": " + input + ": " + info);
    }
    public static void setInfo() {
        if(addresses.size()==0) {
            System.out.println("No addresses.");
            return;
        }
        printAddresses();
        String name = getName();
        System.out.print("What do you want to change(address, phone number, or email): ");
        while(true) {
            String input = in.nextLine();
            if(input.equals("address")) {
                addresses.get(name).setAddress(getString());
                break;
            }
            else if(input.equals("phone number")){
                addresses.get(name).setPhoneNumber(getString());
                break;
            }
            else if(input.equals("email")){
                addresses.get(name).setEmail(getString());
                break;
            }
            else
                System.out.print("Invalid option. Try again: ");
        }
    }
    public static void help() { //done
        System.out.println("commands are: Help, Quit, NewAddress, deleteAddress, getInfo, and setInfo.");
    }
    public static void quit() {
        System.exit(1);
    }

    private static void printAddresses() {  //done
        String output = "Current addresses: ";

        for(Map.Entry<String, Address> entry: addresses.entrySet())
            output += entry.getKey() + ", ";
        output=output.substring(0,output.length()-2)+".";

        System.out.println(output);
    }
    private static String getName() {
        System.out.print("Enter an address: ");

        while(true) {
            String name = in.nextLine();
            if(addresses.containsKey(name))
                return name;
            System.out.print("Invalid name. Please try again: ");
        }
    }
    private static String matchInput(String name,String input) {
        if(input.equals("address"))
            return addresses.get(name).getAddress();
        else if(input.equals("phone number"))
            return addresses.get(name).getPhoneNumber();
        else if(input.equals("email"))
            return addresses.get(name).getEmail();
        else
            System.out.print("Invalid option. Try again: ");
        return "null";
    }
    private static String getString() {
        System.out.print("Enter a new value: ");
        return in.nextLine();
    }
}
