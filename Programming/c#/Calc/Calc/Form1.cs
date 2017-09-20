using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calc
{
    public partial class Form1 : Form
    {
        private double N1, N2, rez;
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
   
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
                
        }

        private void button4_Click(object sender, EventArgs e)
        {
            
        }

        private void numberValidation(object sender, CancelEventArgs e, ref double N)
        {
            try
            {
                N = Double.Parse((sender as TextBox).Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Введено не число");
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
        }

    }
}
