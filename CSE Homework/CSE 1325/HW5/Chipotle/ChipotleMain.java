/* I made the program a bit simpler but made the gui look nicer. Given how this is practice for gui's I feel like this is ok.
 * It doesn't get the drivers but still deals with the total bought and output file.
 */

import java.io.*;
import java.util.*;
import java.awt.event.*;

import javax.swing.*;
import java.awt.*;

public class ChipotleMain {
    public static final String FileLocalo = "CSE Homework\\CSE 1325\\HW3\\Chipotle\\output.dat";   //change as needed
    public static double total=0;
    public static LinkedList<DeliveryPerson> deliv = new LinkedList<DeliveryPerson>();

    static JLabel message = new JLabel("Welcome To Chipotle", SwingConstants.CENTER);

    static JPanel top = new JPanel();
    static JButton customer = new JButton("Submit Order");
    static JButton exit = new JButton("Exit");

    static JPanel bottom = new JPanel();
    static JTextField meal = new JTextField("");
    static JTextField topping = new JTextField("");
    static JTextField sause = new JTextField("");
    
    public static void main(String args[]) throws FileNotFoundException {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300,300);

        JPanel grid = new JPanel();
        grid.setLayout(new GridLayout(3,1));

        grid.add(message);
        grid.add(top);
        grid.add(bottom);

        top.add(customer);
        customer.addActionListener(new CustomerListener());
        top.add(exit);
        exit.addActionListener(new ExitListener());

        bottom.setLayout(new GridLayout(3,2));
        bottom.add(new JLabel("Meal type:", SwingConstants.RIGHT));
        bottom.add(meal);
        bottom.add(new JLabel("Topping:", SwingConstants.RIGHT));
        bottom.add(topping);
        bottom.add(new JLabel("Sause:", SwingConstants.RIGHT));
        bottom.add(sause);

        frame.add(grid);
        frame.setVisible(true);
    }

    static class CustomerListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            if(meal.getText().equals("")||meal.getText().equals("")||meal.getText().equals("")) {
                message.setText("A text field is empty");
                return;
            } else {
                if(meal.getText().toLowerCase().equals("bowl")) {
                    message.setText("Your total is $5.50");
                    total+=5.5;
                } else {
                    message.setText("Your total is $6.75");
                    total+=6.75;
                }
            }




            meal.setText("");
            topping.setText("");
            sause.setText("");

        }
    }
    static class ExitListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            PrintStream out = null;
            try { out = new PrintStream(new File(FileLocalo)); }
            catch(FileNotFoundException ex){System.exit(0);}

            out.printf("%s", total);
            System.exit(0);
        }
    }
}
