package gui;

import javax.swing.*;
import java.awt.*;

import static gui.HadesOS.dataPanel;

public class DataPanel extends JPanel
{
    private JTextField eulerX;
    private JTextField eulerY;
    private JTextField eulerZ;

    public DataPanel()
    {
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        DataConfigPanel dataConfigPanel = new DataConfigPanel();
        gbc.gridx = 0; gbc.gridy = 0;
        add(dataConfigPanel, gbc);

//        eulerX = new JTextField("0");
//        eulerX.setPreferredSize(new Dimension(125, 50));
//        eulerX.setHorizontalAlignment(SwingConstants.CENTER);
//        add(eulerX);
//
//        eulerY = new JTextField("0");
//        eulerY.setPreferredSize(new Dimension(125, 50));
//        eulerY.setHorizontalAlignment(SwingConstants.CENTER);
//        add(eulerY);
//
//        eulerZ = new JTextField("0");
//        eulerZ.setPreferredSize(new Dimension(125, 50));
//        eulerZ.setHorizontalAlignment(SwingConstants.CENTER);
//        add(eulerZ);
//
//        SerialInit.refreshPorts();
//        SerialInit.openPort("/dev/ttyUSB0");
    }

    public String getAngleX() { return eulerX.getText(); }
    public void setAngleX(String newAngleX) { eulerX.setText(newAngleX); }

    public String getAngleY() { return eulerY.getText(); }
    public void setAngleY(String newAngleY) { eulerY.setText(newAngleY); }

    public String getAngleZ() { return eulerZ.getText(); }
    public void setAngleZ(String newAngleZ) { eulerZ.setText(newAngleZ); }

    public static void parseData(String[] input)
    {
        String dataTag = input[0];

        switch (dataTag)
        {
            case "bno_euler":
                dataPanel.setAngleX(input[1]);
                dataPanel.setAngleY(input[2]);
                dataPanel.setAngleZ(input[3]);
                break;
            case "bno_cal_status":
                System.out.println("Cal Status: " + input[1] + " " + input[2] + " " + input[3]);
                break;
            default: break;
        }
    }
}
