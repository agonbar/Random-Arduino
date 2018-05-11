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

namespace WoWbot
{
    public partial class fMain : Form
    {
        private Keylogger keylog = null;
        public fMain()
        {
            InitializeComponent();
        }

        private void bInit_Click(object sender, EventArgs e)
        {
            if (keylog == null)
            {
                keylog = new Keylogger();
                keylog.Listen(Application.StartupPath + @"\" + this.tbRecordName.Text + ".txt");
                this.bInit.Text = "Parar";
            }
            else
            {
                this.bInit.Text = "Iniciar";
                // TODO: Implementar la parada del hook
                keylog = null;
            }
        }

        private void fMain_Load(object sender, EventArgs e)
        {
            // Log default name
            this.tbRecordName.Text = "test1";

            // COM ports
            foreach (string s in SerialPort.GetPortNames())
            {
                this.cbSerialPort.Items.Add(s);
            }
            if (this.cbSerialPort.Items.Count > 0) this.cbSerialPort.SelectedIndex = 0;
        }
    }
}
