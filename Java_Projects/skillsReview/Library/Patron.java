package skillsReview.Library;

import java.util.ArrayList;

public class Patron {
    public ArrayList<Book> currentBooks = new ArrayList<>();
    private String name;

    public Patron(String name) {
        this.name = name;
    }
    public String hasBook() {
        if(currentBooks.size()>0)
            return "does";
        return "does not";
    }
    public void borrowBook(Book b) {
        currentBooks.add(b);
    }
    public void returnBook(Book b) {
        currentBooks.remove(b);
    }
    public void printBooks() {
        System.out.println("====="+name+"=====");
        for(int i = 0;i<currentBooks.size();i++) {
            System.out.println(currentBooks.get(i));
        }
    }
    public String getName() {
        return name;
    }
    public String toString() {
        return name;
    }
    public void listB() {
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
}
