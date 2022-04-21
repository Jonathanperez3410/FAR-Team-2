package serial;

import gui.DataPanel;
import jssc.SerialPort;
import jssc.SerialPortList;

public class SerialInit
{
    private static String[] comPorts;
    private static SerialPort serialPort;

    public static String[] getComPorts() { return comPorts; }
    public static void setComPorts(String[] newComPorts) { comPorts = newComPorts; }

    public static void refreshPorts()
    {
        // Get a list every available serial port
        setComPorts(SerialPortList.getPortNames());
    }

    public static void openPort(String name)
    {
        try
        {
            // If a serial port is already opened, close it
            if (serialPort != null && serialPort.isOpened())
                serialPort.closePort();

            // Clear any values from the data tab in the GUI
            // DataPanel.clearData();

            // Open a serial port with the given name, under these parameters
            serialPort = new SerialPort(name);
            serialPort.openPort();
            serialPort.setParams(
                    SerialPort.BAUDRATE_115200,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE
            );
            serialPort.setFlowControlMode(
                    SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT
            );

            // Create a new port reader and assign it as the port's event handler
            PortReader portReader = new PortReader(serialPort);
            serialPort.addEventListener(portReader, SerialPort.MASK_RXCHAR);
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }
}
