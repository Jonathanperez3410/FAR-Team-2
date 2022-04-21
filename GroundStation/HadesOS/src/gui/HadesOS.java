package gui;

import gui.j3d.Rocket3D;

import javax.swing.*;

public class HadesOS
{
    public static DataPanel dataPanel;

    public static void main(String[] args)
    {
        System.setProperty("sun.awt.noerasebackground", "true");

        JFrame frame = new JFrame();
        JPanel mainPanel = new JPanel();
        mainPanel.setSize(800, 600);

        dataPanel = new DataPanel();
        Rocket3D cubePanel = new Rocket3D();
        mainPanel.add(dataPanel);
        mainPanel.add(cubePanel);

        frame.add(mainPanel);
        frame.setTitle("HadesOS");
        frame.setSize(800, 600);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
