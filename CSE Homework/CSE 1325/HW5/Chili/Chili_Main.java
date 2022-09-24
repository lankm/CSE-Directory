//This program feels rough. Its more of a practice for guis for me.

import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import chilistuff.*;

public class Chili_Main {
    public static LinkedHashMap<Customer, StarbucksCup> orders = new LinkedHashMap<Customer, StarbucksCup>();
    public static int hc;   //Half cups since a Tall is .5 cups.
    public static int next;

    public static JFrame f;
    public static JPanel left;
    public static JPanel right;
    public static JTextField t;
    public static JTextArea l;

    public static void main(String args[]) throws FileNotFoundException {   //I'm being lazy and just handling the exception here.
        load("CSE Homework\\CSE 1325\\HW3\\Chili\\orders.dat");

        f = new JFrame();
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setSize(300,300);


        t = new JTextField("");
        t.addActionListener(new TextListener());
        f.add(t, BorderLayout.PAGE_END);

        l = new JTextArea("Enter the number of batches made");
        f.add(l, BorderLayout.CENTER);




        f.setVisible(true);
    }

    public static void load(String fileName) throws FileNotFoundException {
        File f = new File(fileName);
        Scanner fIn = new Scanner(f);  //change location as needed. This would only work on my machine.
        while(fIn.hasNextLine()) {
            String line = fIn.nextLine();
            if(line.equals(""))
                break;

            String[] values = line.split(",");
            orders.put(new Customer(values[0]), new StarbucksCup(values[1]));
        }
        fIn.close();
    }
    public static void nextCust() {
        Map.Entry<Customer, StarbucksCup> firstEntry;
        try {
            firstEntry = orders.entrySet().stream().findFirst().get();
        } catch(NoSuchElementException e) {
            l.setText("All customers served.");
            return;
        }
        Customer c = firstEntry.getKey();
        StarbucksCup sbc = firstEntry.getValue();
        next=sbc.size;
        orders.remove(c);


        l.setText(c.getName()+" wants a "+sbc.name+" ("+sbc.size/2.0+")\n\n"+"you have "+hc/2.0+" cups left\n");
        l.setText(l.getText()+"Take the order or take a break.");
    }


    static class TextListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            hc = Integer.parseInt(t.getText())*2;
            t.setText("");
            nextCust();

            t.removeActionListener(this);
            t.addActionListener(new BreakListener());
            System.out.println(hc);
        }
    }
    static class BreakListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String s = t.getText();
            t.setText("");
            

            if(s.toLowerCase().contains("break")) {
                l.setText(l.getText()+"\n\n"+"press enter to continue.");
            } else {
                hc-=next;
                if(hc<=0) {
                    l.setText("You've ran out of Chili.");
                    t.removeActionListener(this);
                    t.addActionListener(new nullListener());
                } else
                    nextCust();
            }
        }
    }
    static class nullListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            t.setText("");
        }
    }
}
