using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Esp32_24_sensors
{
    public partial class Form1 : Form
    {
        string serialDataIn;
        sbyte indexOfA, indexOfB, indexOfC, indexOfD, indexOfE, indexOfF, indexOfG, indexOfH;
        sbyte indexOfI, indexOfJ, indexOfK, indexOfL, indexOfM, indexOfN, indexOfO, indexOfP;
        sbyte indexOfQ, indexOfR, indexOfS, indexOfT, indexOfU, indexOfV, indexOfW, indexOfZ;
        string dataSensor1, dataSensor2, dataSensor3, dataSensor4, dataSensor5, dataSensor6, dataSensor7, dataSensor8;
        string dataSensor11, dataSensor12, dataSensor13, dataSensor14, dataSensor15, dataSensor16, dataSensor17, dataSensor18;
        string dataSensor21, dataSensor22, dataSensor23, dataSensor24, dataSensor25, dataSensor26, dataSensor27, dataSensor28;
        Int32 baudRate1 = 115200;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button_open.Enabled = true;
            button_close.Enabled = false;

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel1_Paint_1(object sender, PaintEventArgs e)
        {
             
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox_comPort_DropDown(object sender, EventArgs e)
        {
            string[] portlist = SerialPort.GetPortNames();
            comboBox_comPort.Items.Clear();
            comboBox_comPort.Items.AddRange(portlist);

        }

        private void button_open_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBox_comPort.Text;
                serialPort1.BaudRate = baudRate1;
                serialPort1.Open();

                button_open.Enabled = false;
                button_close.Enabled = true;
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox_sensor1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button_close_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();

                button_open.Enabled = true;
                button_close.Enabled = false;

            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                serialPort1.Close();
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            serialDataIn = serialPort1.ReadLine();
            this.BeginInvoke(new EventHandler(processData));
        }

        private void processData(object sender, EventArgs e)
        {
            try
            {
                indexOfA = Convert.ToSByte(serialDataIn.IndexOf('A'));
                indexOfB = Convert.ToSByte(serialDataIn.IndexOf('B'));
                indexOfC = Convert.ToSByte(serialDataIn.IndexOf('C'));
                indexOfD = Convert.ToSByte(serialDataIn.IndexOf('D'));
                indexOfE = Convert.ToSByte(serialDataIn.IndexOf('E'));
                indexOfF = Convert.ToSByte(serialDataIn.IndexOf('F'));
                indexOfG = Convert.ToSByte(serialDataIn.IndexOf('G'));
                indexOfH = Convert.ToSByte(serialDataIn.IndexOf('H'));

                indexOfI = Convert.ToSByte(serialDataIn.IndexOf('I'));
                indexOfJ = Convert.ToSByte(serialDataIn.IndexOf('J'));
                indexOfK = Convert.ToSByte(serialDataIn.IndexOf('K'));
                indexOfL = Convert.ToSByte(serialDataIn.IndexOf('L'));
                indexOfM = Convert.ToSByte(serialDataIn.IndexOf('M'));
                indexOfN = Convert.ToSByte(serialDataIn.IndexOf('N'));
                indexOfO = Convert.ToSByte(serialDataIn.IndexOf('O'));
                indexOfP = Convert.ToSByte(serialDataIn.IndexOf('P'));

                indexOfQ = Convert.ToSByte(serialDataIn.IndexOf('Q'));
                indexOfR = Convert.ToSByte(serialDataIn.IndexOf('R'));
                indexOfS = Convert.ToSByte(serialDataIn.IndexOf('S'));
                indexOfT = Convert.ToSByte(serialDataIn.IndexOf('T'));
                indexOfU = Convert.ToSByte(serialDataIn.IndexOf('U'));
                indexOfV = Convert.ToSByte(serialDataIn.IndexOf('V'));
                indexOfW = Convert.ToSByte(serialDataIn.IndexOf('W'));
                indexOfZ = Convert.ToSByte(serialDataIn.IndexOf('Z'));


                dataSensor1 = serialDataIn.Substring(0, indexOfA);
                dataSensor2 = serialDataIn.Substring(indexOfA + 1, (indexOfB - indexOfA) - 1);
                dataSensor3 = serialDataIn.Substring(indexOfB + 1, (indexOfC - indexOfB) - 1);
                dataSensor4 = serialDataIn.Substring(indexOfC + 1, (indexOfD - indexOfC) - 1);
                dataSensor5 = serialDataIn.Substring(indexOfD + 1, (indexOfE - indexOfD) - 1);
                dataSensor6 = serialDataIn.Substring(indexOfE + 1, (indexOfF - indexOfE) - 1);
                dataSensor7 = serialDataIn.Substring(indexOfF + 1, (indexOfG - indexOfF) - 1);
                dataSensor8 = serialDataIn.Substring(indexOfG + 1, (indexOfH - indexOfG) - 1);

                dataSensor11 = serialDataIn.Substring(indexOfH + 1, (indexOfI - indexOfH) - 1);
                dataSensor12 = serialDataIn.Substring(indexOfI + 1, (indexOfJ - indexOfI) - 1);
                dataSensor13 = serialDataIn.Substring(indexOfJ + 1, (indexOfK - indexOfJ) - 1);
                dataSensor14 = serialDataIn.Substring(indexOfK + 1, (indexOfL - indexOfK) - 1);
                dataSensor15 = serialDataIn.Substring(indexOfL + 1, (indexOfM - indexOfL) - 1);
                dataSensor16 = serialDataIn.Substring(indexOfM + 1, (indexOfN - indexOfM) - 1);
                dataSensor17 = serialDataIn.Substring(indexOfN + 1, (indexOfO - indexOfN) - 1);
                dataSensor18 = serialDataIn.Substring(indexOfO + 1, (indexOfP - indexOfO) - 1);

                dataSensor21 = serialDataIn.Substring(indexOfP + 1, (indexOfQ - indexOfP) - 1);
                dataSensor22 = serialDataIn.Substring(indexOfQ + 1, (indexOfR - indexOfQ) - 1);
                dataSensor23 = serialDataIn.Substring(indexOfR + 1, (indexOfS - indexOfR) - 1);
                dataSensor24 = serialDataIn.Substring(indexOfS + 1, (indexOfT - indexOfS) - 1);
                dataSensor25 = serialDataIn.Substring(indexOfT + 1, (indexOfU - indexOfT) - 1);
                dataSensor26 = serialDataIn.Substring(indexOfU + 1, (indexOfV - indexOfU) - 1);
                dataSensor27 = serialDataIn.Substring(indexOfV + 1, (indexOfW - indexOfV) - 1);
                dataSensor28 = serialDataIn.Substring(indexOfW + 1, (indexOfZ - indexOfW) - 1);


                verticalProgressBar_sensor1.Value = Convert.ToInt16(dataSensor1);
                verticalProgressBar_sensor2.Value = Convert.ToInt16(dataSensor2);
                verticalProgressBar_sensor3.Value = Convert.ToInt16(dataSensor3);
                verticalProgressBar_sensor4.Value = Convert.ToInt16(dataSensor4);
                verticalProgressBar_sensor5.Value = Convert.ToInt16(dataSensor5);
                verticalProgressBar_sensor6.Value = Convert.ToInt16(dataSensor6);
                verticalProgressBar_sensor7.Value = Convert.ToInt16(dataSensor7);
                verticalProgressBar_sensor8.Value = Convert.ToInt16(dataSensor8);

                verticalProgressBar_sensor11.Value = Convert.ToInt16(dataSensor11);
                verticalProgressBar_sensor12.Value = Convert.ToInt16(dataSensor12);
                verticalProgressBar_sensor13.Value = Convert.ToInt16(dataSensor13);
                verticalProgressBar_sensor14.Value = Convert.ToInt16(dataSensor14);
                verticalProgressBar_sensor15.Value = Convert.ToInt16(dataSensor15);
                verticalProgressBar_sensor16.Value = Convert.ToInt16(dataSensor16);
                verticalProgressBar_sensor17.Value = Convert.ToInt16(dataSensor17);
                verticalProgressBar_sensor18.Value = Convert.ToInt16(dataSensor18);

                verticalProgressBar_sensor21.Value = Convert.ToInt16(dataSensor21);
                verticalProgressBar_sensor22.Value = Convert.ToInt16(dataSensor22);
                verticalProgressBar_sensor23.Value = Convert.ToInt16(dataSensor23);
                verticalProgressBar_sensor24.Value = Convert.ToInt16(dataSensor24);
                verticalProgressBar_sensor25.Value = Convert.ToInt16(dataSensor25);
                verticalProgressBar_sensor26.Value = Convert.ToInt16(dataSensor26);
                verticalProgressBar_sensor27.Value = Convert.ToInt16(dataSensor27);
                verticalProgressBar_sensor28.Value = Convert.ToInt16(dataSensor28);
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }


    }
}
