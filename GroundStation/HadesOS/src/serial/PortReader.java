package serial;

import gui.DataPanel;
import gui.HadesOS;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class PortReader implements SerialPortEventListener
{
    SerialPort serialPort;

    public PortReader(SerialPort serialPort)
    {
        this.serialPort = serialPort;
    }

    @Override
    public void serialEvent(SerialPortEvent event)
    {
        // This code just does event handling for the serial port
        if (event.isRXCHAR() && event.getEventValue() > 0)
        {
            try
            {
                String ch;
                StringBuilder input = new StringBuilder();

                // Only starts reading when the next byte is a '*'
                // Stops reading when the next byte is a '#'
                while (!(serialPort.readString(1)).equals("*"));
                while (!(ch = serialPort.readString(1)).equals("#"))
                    input.append(ch);

                // Split the data string by commas and send it to the parse serial method
                String[] inputArr = input.toString().split(",");
                DataPanel.parseData(inputArr);
            }
            catch (SerialPortException ex)
            {
                ex.printStackTrace();
            }
        }
    }
}
