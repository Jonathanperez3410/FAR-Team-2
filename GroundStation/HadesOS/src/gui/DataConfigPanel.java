package gui;

import serial.SerialInit;

import javax.swing.*;
import java.awt.*;
import java.util.Objects;

public class DataConfigPanel extends JPanel
{
    public DataConfigPanel()
    {
        // Set up the config panel
        setBorder(BorderFactory.createLineBorder(Color.BLACK));
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Refresh the serial ports
        SerialInit.refreshPorts();

        // Create a button to open the currently selected port
        JButton openPort = new JButton("Open Serial Port");
        gbc.gridx = 0; gbc.gridy = 0;
        add(openPort, gbc);

        // Create a combo box of available ports
        JComboBox<String> portList = new JComboBox<>(SerialInit.getComPorts());
        gbc.gridx = 1; gbc.gridy = 0;
        add(portList, gbc);

        // Create a button to refresh the serial ports
        JButton refreshPortList = new JButton("Refresh Serial List");
        gbc.gridx = 0; gbc.gridy = 1;
        add(refreshPortList, gbc);

        // Create a text field for the currently opened port
        JTextField currentPort = new JTextField();
        currentPort.setPreferredSize(new Dimension(120, 25));
        currentPort.setEditable(false);
        currentPort.setHorizontalAlignment(SwingConstants.CENTER);
        gbc.gridx = 1; gbc.gridy = 1;
        add(currentPort, gbc);

        // When the openPort button is pressed, open the currently selected port
        openPort.addActionListener(e ->
        {
            String portName = Objects.requireNonNull(portList.getSelectedItem()).toString();
            SerialInit.openPort(portName);
            currentPort.setText(portName);
        });

        // When the refreshPortList button is pressed, refresh the list of serial ports
        refreshPortList.addActionListener(e -> SerialInit.refreshPorts());
    }
}
