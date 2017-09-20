using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace durak
{
    public partial class Fool : Form
    {
        private bool flag = true;
        private const string code = "дурак";
        private int count = 0;
        private const int bias = 10;
        public Fool()
        {
            InitializeComponent();
        }

        private void btYes_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Я так и знал");
        }

        private void btNo_Click(object sender, EventArgs e)
        {
            MessageBox.Show("А ты хитер!");
        }


        private void Form_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == code[count] && flag)
            {
                count++;
                if (count == code.Length)
                    flag = false;
            }
            else
                count = 0;
        }


        private void Check(int Ex, int Ey)
        {
            int X, Y;
            X = btNo.Location.X;
            Y = btNo.Location.Y;
            
            if (flag == true)
            {
                if (Ex < X && Ex > X - bias && Ey > Y && Ey < Y + btNo.Height)
                {
                    btNo.Location = new Point(btNo.Location.X + bias, btNo.Location.Y);
                }
                if (Ex < X + btNo.Width + bias && Ex > X && Ey > Y && Ey < Y + btNo.Height)
                {
                    btNo.Location = new Point(btNo.Location.X - bias, btNo.Location.Y);
                }
                if (Ex < X + btNo.Width && Ex > X && Ey > Y - bias && Ey < Y)
                {
                    btNo.Location = new Point(btNo.Location.X, btNo.Location.Y + bias);
                }
                if (Ex < X + btNo.Width && Ex > X && Ey > Y && Ey < Y + btNo.Height + bias)
                {
                    btNo.Location = new Point(btNo.Location.X, btNo.Location.Y - bias);
                }
                if (Ex < X && Ex > X - bias && Ey > Y - bias && Ey < Y)
                {
                    btNo.Location = new Point(btNo.Location.X + bias, btNo.Location.Y + bias);
                }
                if (Ex < X && Ex > X - bias && Ey > Y + btNo.Height && Ey < Y + btNo.Height + bias)
                {
                    btNo.Location = new Point(btNo.Location.X + bias, btNo.Location.Y - bias);
                }
                if (Ex > X + btNo.Width && Ex < X + btNo.Width + bias && Ey > Y - bias && Ey < Y)
                {
                    btNo.Location = new Point(btNo.Location.X - bias, btNo.Location.Y + bias);
                }
                if (Ex > X + btNo.Width && Ex < X + btNo.Width + bias && Ey > Y + btNo.Height && Ey < Y + btNo.Height + bias)
                {
                    btNo.Location = new Point(btNo.Location.X - bias, btNo.Location.Y - bias);
                }

                if (X < bias)
                    btNo.Left = 2 * btNo.Width;
                if (X + btNo.Width > Width - 2 * bias)
                    btNo.Left = Width - 3 * btNo.Width;
                if (Y < bias)
                    btNo.Top = 2 * btNo.Height;
                if (Y + btNo.Height > Height - 4 * bias)
                    btNo.Top = Height - 4 * btNo.Height;
                //75.23

            }
        }

        private void Form_MouseMove(object sender, MouseEventArgs e)
        {
            Check(e.X, e.Y);
        }

        private void btYes_MouseMove(object sender, MouseEventArgs e)
        {
            Check(e.X + btYes.Location.X, e.Y + btYes.Location.Y);
        }

        private void lbQuestion_MouseMove(object sender, MouseEventArgs e)
        {
            Check(e.X + lbQuestion.Location.X, e.Y + lbQuestion.Location.Y);
        }

        Random rand = new Random();

        private void btNo_MouseEnter(object sender, EventArgs e)
        {
           
            if (flag == true)
            {
                btNo.Location = new Point(rand.Next(btNo.Location.X - bias, btNo.Location.X + btNo.Width + bias),rand.Next(btNo.Location.Y - bias, btNo.Location.Y + btNo.Height + bias));
                //btNo.Location = new Point(rand.Next(btNo.Location.X + 2*bias),rand.Next(btNo.Location.Y + 2 * bias));
            }
        }

        private void btYes_KeyDown(object sender, KeyEventArgs e)
        {

        }

        private void btYes_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Down || e.KeyCode == Keys.Up
                || e.KeyCode == Keys.Left || e.KeyCode == Keys.Right)
                e.IsInputKey = true;
        }
    }
}
