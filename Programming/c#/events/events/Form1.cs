using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace events
{
    public partial class Form : System.Windows.Forms.Form
    {
        public Form()
        {
            InitializeComponent();
        }

        public static Thread thread;
        private int? DelayTime;

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (Check() && !Calculator.isActive)
            {
                Calculator calc = new Calculator(Convert.ToInt32(textBoxTime.Text));
                thread = new Thread(calc.Calculate);
                calc.EventEndCalculate += Demonstrator.Message;
                textBoxTime.ReadOnly = true;
                thread.Start();
            }
        }

        private bool Check()
        {
            if (DelayTime != null)
                return true;
            error.SetError(textBoxTime, "Enter the Time!");
            return false;
        }

        private void buttonFinish_Click(object sender, EventArgs e)
        {
            if (Calculator.isActive)
            {
                Demonstrator demo = new Demonstrator();
                demo.StopCalculate += Calculator.StopHandler;
                demo.Stop();
            }
        }

        private void textBoxTime_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                DelayTime = int.Parse((sender as TextBox).Text);
                if (DelayTime <= 0)
                    throw new ArgumentException("PauseTime DelayTime can't be lower then zero.");
            }
            catch (Exception ex)
            {
                error.SetError((sender as TextBox), ex.Message);
                (sender as TextBox).SelectAll();
                e.Cancel = true;
            }
        }

        private void textBoxTime_Validated(object sender, EventArgs e)
        {
            error.Clear();
        }

        private void Form_Deactivate(object sender, EventArgs e)
        {
            thread?.Abort();
        }
    }

}
