using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace calculator
{
    public partial class Form1 : Form
    {
        private double N1, N2;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            N1 = 0;
            N2 = 0;
            div.Enabled = false;
            tbN1.Text = N1.ToString();
            tbN2.Text = N2.ToString();
        }
       

        private void sum_Click(object sender, EventArgs e)
        {
            tbRez.Text = (N1 + N2).ToString();
        }

        private void sub_Click(object sender, EventArgs e)
        {
            tbRez.Text = (N1 - N2).ToString();
        }

        private void div_Click(object sender, EventArgs e)
        {
            tbRez.Text = (N1 / N2).ToString();
        }

        private void mult_Click(object sender, EventArgs e)
        {
            tbRez.Text = (N1 * N2).ToString();
        }

        private void numberValidation(object sender, CancelEventArgs e, ref double N)
        {
            try
            {
                N = Double.Parse((sender as TextBox).Text);
            }
            catch (Exception ex)
            {
                err1.SetError((sender as TextBox), "Введено не число");
                (sender as TextBox).SelectAll();
                e.Cancel = true;
            }
        }

        private void tbN1_Validating(object sender, CancelEventArgs e)
        {
            numberValidation(sender, e, ref N1);
        }

        private void tbN2_Validating(object sender, CancelEventArgs e)
        {
            numberValidation(sender, e, ref N2);
            if (N2 == 0)
                div.Enabled = false;
            else
                div.Enabled = true;

        }

        private void tbN1_Validated(object sender, EventArgs e)
        {
            err1.Clear();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.Cancel = true)
                e.Cancel = false;
        }

        private void tbN2_Validated(object sender, EventArgs e)
        {
            err1.Clear();
        }


    }
}
