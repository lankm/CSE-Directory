package skillsReview.Library;

import java.util.ArrayList;
import java.util.Scanner;

public class Library {
    static ArrayList<Patron> currentPatrons = new ArrayList<>();
    static ArrayList<Book> currentBooks = new ArrayList<>();
    static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        help();
        while (true) {
            System.out.print("What do you want to do: ");

            String input;
            b:
            {
                while (true) {
                    input = in.nextLine();
                    switch (input.toLowerCase()) {
                        case "newbook":
                            newBook();
                            break b;
                        case "bookinfo":
                            bookInfo();
                            break b;
                        case "hasbook":
                            hasBook();
                            break b;
                        case "borrowbook":
                            borrowBook();
                            break b;
                        case "returnbook":
                            returnBook();
                            break b;
                        case "list":
                            list();
                            break b;
                        case "printbooks":
                            listB();
                            break b;
                        case "printpatrons":
                            listP();
                            break b;
                        case "help":
                            help();
                            break b;
                        case "newpatron":
                            newPatron();
                            break b;
                    }
                    System.out.print("Wrong input. try again: ");
                }
            }
            System.out.println("Finished.\n");
        }
    }

    public static void newBook() {  //done
        System.out.print("Enter a name: ");
        String name = in.nextLine();
        System.out.print("Enter a author name: ");
        String aName = in.nextLine();
        currentBooks.add(new Book(name, aName));
    }

    public static void bookInfo() { //done
        if (currentBooks.size() == 0) {
            System.out.println("No books exist.");
            return;
        }
        Book b = currentBooks.get(indexB());
        System.out.println("title: "+b.getTitle()+" author: "+b.getAuthor());
    }

    public static void hasBook() {
        if (currentPatrons.size() == 0) {
            System.out.println("No patrons exist.");
            return;
        }
        int index =indexP();
        Patron p = currentPatrons.get(index);
        System.out.println(p.getName() + " " + p.hasBook() + " have a book.");
    }

    public static void borrowBook() {
        if (currentPatrons.size() == 0) {
            System.out.println("No patrons exist.");
            return;
        }
        if (currentBooks.size() == 0) {
            System.out.println("No books exist.");
            return;
        }

        int patron =indexP();
        int book = indexB();
        currentPatrons.get(patron).borrowBook(currentBooks.get(book));
    }

    public static void returnBook() {
        if (currentPatrons.size() == 0) {
            System.out.println("No patrons exist.");
            return;
        }
        int patron =indexP();
        int index = -1;
        currentPatrons.get(patron).listB();
        System.out.print("choose a book from "+patron+": ");
        while (true) {   //gets the selected book as index
            String name = in.nextLine();
            for (int i = 0; i < currentPatrons.get(patron).currentBooks.size(); i++) {  //gets the index of the name of the book
                if (name.equals(currentPatrons.get(patron).currentBooks.get(i).getTitle())) {
                    index = i;
                }
            }
            if (index != -1)   //loops if no name was found
                break;
            else
                System.out.print("wrong input. try again: ");
        }
        currentPatrons.get(patron).returnBook(currentPatrons.get(patron).currentBooks.get(index));
    }

    public static void listP() {
        if (currentPatrons.size() == 0) {
            System.out.println("No patrons exist.");
            return;
        }
        String output = "Current patrons: ";
        for (int i = 0; i < currentPatrons.size(); i++) {
            output += currentPatrons.get(i) + ", ";
        }
        System.out.println(output.substring(0, output.length() - 2) + ".");
    }
    public static void listB() {
        if (currentBooks.size() == 0) {
            System.out.println("No books exist.");
            return;
        }
        String output = "Current books: ";
        for (int i = 0; i < currentBooks.size(); i++) {
            output += currentBooks.get(i) + ", ";
        }
        System.out.println(output.substring(0, output.length() - 2) + ".");
    }
    public static void list() {
        int indexp = indexP();
        currentPatrons.get(indexp).listB();
    }

    public static void help() {
        System.out.println("commands are: NewBook, BookInfo, HasBook, BorrowBook, ReturnBook, NewPatron, Help, PrintBooks, PrintPatrons, and List.");
    }

    public static void newPatron() {
        System.out.print("Enter a name: ");
        String name = in.nextLine();
        currentPatrons.add(new Patron(name));
    }

    private static int indexB() {
        int index = -1;
        listB();
        System.out.print("choose a book: ");
        while (true) {   //gets the selected book as index
            String name = in.nextLine();
            for (int i = 0; i < currentBooks.size(); i++) {  //gets the index of the name of the book
                if (name.equals(currentBooks.get(i).getTitle())) {
                    index = i;
                }
            }
            if (index != -1)   //loops if no name was found
                break;
            else
                System.out.print("wrong input. try again: ");
        }
        return index;
    }
    private static int indexP() {
        int index = -1;
        listP();
        System.out.print("choose a patron: ");
        while (true) {   //gets the selected book as index
            String name = in.nextLine();
            for (int i = 0; i < currentPatrons.size(); i++) {  //gets the index of the name of the book
                if (name.equals(currentPatrons.get(i).getName())) {
                    index = i;
                }
            }
            if (index != -1)   //loops if no name was found
                break;
            else
                System.out.print("wrong input. try again: ");
        }
        return index;
    }
}
