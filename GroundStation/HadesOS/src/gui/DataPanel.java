package gui;

import serial.SerialInit;

import javax.swing.*;
import java.awt.*;

public class DataPanel extends JPanel
{
    private JTextField eulerX;
    private JTextField eulerY;
    private JTextField eulerZ;

    public DataPanel()
    {
        eulerX = new JTextField("0");
        eulerX.setPreferredSize(new Dimension(125, 50));
        eulerX.setHorizontalAlignment(SwingConstants.CENTER);
        add(eulerX);

        eulerY = new JTextField("0");
        eulerY.setPreferredSize(new Dimension(125, 50));
        eulerY.setHorizontalAlignment(SwingConstants.CENTER);
        add(eulerY);

        eulerZ = new JTextField("0");
        eulerZ.setPreferredSize(new Dimension(125, 50));
        eulerZ.setHorizontalAlignment(SwingConstants.CENTER);
        add(eulerZ);

        SerialInit.refreshPorts();
        SerialInit.openPort("/dev/ttyUSB0");
    }

    public String getAngleX() { return eulerX.getText(); }
    public void setAngleX(String newAngleX) { eulerX.setText(newAngleX); }

    public String getAngleY() { return eulerY.getText(); }
    public void setAngleY(String newAngleY) { eulerY.setText(newAngleY); }

    public String getAngleZ() { return eulerZ.getText(); }
    public void setAngleZ(String newAngleZ) { eulerZ.setText(newAngleZ); }

}
