package de.limago;


import java.awt.*;
import java.awt.event.*;

public class Fenster extends Frame {


    public Fenster()  {

        setSize(300, 300);


        Button button = new Button("Drück mich");
        button.addActionListener(e-> ausgabe());
        add(button);
        addWindowListener(new MyWindowListener());

    }

    private void beenden() {
        dispose();
    }

    private void ausgabe() {
        System.out.println("Hallo");
    }

    public static void main(String[] args) {

        new Fenster().setVisible(true);
    }

    class MyWindowListener extends WindowAdapter {
        @Override
        public void windowClosing(final WindowEvent e) {
            beenden();
        }
    }

}
