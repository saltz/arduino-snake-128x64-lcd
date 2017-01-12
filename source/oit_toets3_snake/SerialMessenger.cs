using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace oit_toets3_snake
{
    public class SerialMessenger
    {
        /// <summary>
        /// Serial port used for the connection.
        /// </summary>
        private SerialPort serialPort;

        private MessageBuilder messageBuilder;

        /// <summary>
        /// The Baudrate of the communication (bytes per second)
        /// </summary>
        public int BaudRate { get { return serialPort.BaudRate; } }

        /// <summary>
        /// The serial port name
        /// </summary>
        public string PortName { get { return serialPort.PortName; } }

        /// <summary>
        /// Creates a Serial Messenger
        /// </summary>
        /// <param name="portName">The name of the serial port</param>
        /// <param name="baudRate">The speed</param>
        /// <param name="messageBuilder">The messagebuilder used</param>
        public SerialMessenger(string portName, int baudRate, MessageBuilder messageBuilder)
        {
            if (portName == null)
            {
                throw new ArgumentNullException("portName");

            }

            if (baudRate < 9600)
            {
                throw new ArgumentOutOfRangeException("baudRate");
            }

            if (messageBuilder == null)
            {
                throw new ArgumentNullException("messageBuilder");

            }
            serialPort = new SerialPort();
            serialPort.BaudRate = baudRate;
            serialPort.PortName = portName;

            this.messageBuilder = messageBuilder;
        }

        /// <summary>
        /// Connect to the serial port
        /// </summary>
        public void Connect()
        {
            if (!serialPort.IsOpen)
            {
                serialPort.Open();
                if (serialPort.IsOpen)
                {
                    serialPort.DiscardInBuffer();
                    serialPort.DiscardOutBuffer();
                }
            }
        }

        /// <summary>
        /// Disconnect from the serial port
        /// </summary>
        public void Disconnect()
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

        /// <summary>
        /// Gets the available serial port names.
        /// </summary>
        /// <returns>The names of the available serial ports</returns>
        public string[] GetAvailablePortNames()
        {
            return SerialPort.GetPortNames();
        }

        /// <summary>
        /// Checks connection status
        /// </summary>
        /// <returns>True is connected, else false</returns>
        public bool IsConnected()
        {
            return serialPort.IsOpen;
        }

        /// <summary>
        /// Sends the given message to the serial port.
        /// </summary>
        /// <param name="message">The message to send.</param>
        /// <returns>true if the message was send, false otherwise.</returns>
        public bool SendMessage(string message)
        {
            if (serialPort.IsOpen)
            {
                //try
                //{
                serialPort.Write(messageBuilder.MessageBeginMarker + message + messageBuilder.MessageEndMarker);
                return true;
                //}
                //catch (Exception exception) // Not very nice to catch Exception...but for now it's good enough.
                //{
                //   Debug.WriteLine("Could not write to serial port: " + exception.Message);
                //}
            }
            return false;
        }

        /// <summary>
        /// Reads data from the serialport and extracts the mesages
        /// </summary>
        /// <returns>An array with messages, of null if no (complete) messages were received (yet)</returns>
        public string[] ReadMessages()
        {
            if (serialPort.IsOpen
                && serialPort.BytesToRead > 0)
            {
                //try
                //{
                string data = serialPort.ReadExisting();
                messageBuilder.Add(data);

                int messageCount = messageBuilder.MessageCount;
                if (messageCount > 0)
                {
                    string[] messages = new string[messageCount];
                    for (int i = 0; i < messageCount; i++) // not very fail safe programming... 
                    {
                        messages[i] = messageBuilder.GetNextMessage();
                    }
                    return messages;
                }

                //ProcessMessages();
                //}
                //catch (Exception exception) // Not very nice to catch Exception...but for now it's good enough.
                //{
                //    Debug.WriteLine("Could not read from serial port: " + exception.Message);
                //}
            }
            return null;
        }
    }
}
