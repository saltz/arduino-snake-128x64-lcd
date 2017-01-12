using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace oit_toets3_snake
{
    public partial class Form1 : Form
    {

        private SerialMessenger serialMessenger;
        private Timer readMessageTimer;
        public Form1()
        {
            InitializeComponent();
            MessageBuilder messageBuilder = new MessageBuilder('#', '%');
            serialMessenger = new SerialMessenger("COM5", 9600, messageBuilder);

            readMessageTimer = new Timer();
            readMessageTimer.Interval = 10;
            readMessageTimer.Tick += new EventHandler(ReadMessageTimer_Tick);
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                serialMessenger.Connect();
                lbControl.Text = "Arduino";
                readMessageTimer.Enabled = true;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            disconnect();
            lbControl.Text = "-";
        }

        private void btnPcControl_Click(object sender, EventArgs e)
        {
            if (serialMessenger.SendMessage("REMOTE_CONTROL"))
            {
                lbControl.Text = "PC";
            }
        }

        private void disconnect()
        {
            try
            {
                readMessageTimer.Enabled = false;
                serialMessenger.Disconnect();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
        private void ReadMessageTimer_Tick(object sender, EventArgs e)
        {
            string[] messages = serialMessenger.ReadMessages();
            if (messages != null)
            {
                foreach (string message in messages)
                {
                    processReceivedMessage(message);
                }
            }
        }
        private void processReceivedMessage(string message)
        {
            if (message == "ARDUINO_CONTROL")
            {
                lbControl.Text = "Arduino";
            }
            else
            {
                textBox2.Text = message;
            }
        }
        private int getParamValue(string message)
        {
            int colonIndex = message.IndexOf(':');
            if (colonIndex != -1)
            {
                string param = message.Substring(colonIndex + 1);
                int value;
                bool done = int.TryParse(param, out value);
                if (done)
                {
                    return value;
                }
            }
            throw new ArgumentException("message contains no value parameter");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialMessenger.SendMessage(textBox1.Text);
        }
    }
}
