using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace shooting
{
    public partial class Form : System.Windows.Forms.Form
    {

        private int R, a, b, numberOfShoots, hit, miss, Xs, Ys;
        private Point C;
        private bool flag = false;

        public Form()
        {
            InitializeComponent();
        }

        private void btSG_Click(object sender, EventArgs e)
        {
            if (tbSoots.Text != "" && tba.Text != "" && tbb.Text != "" && tbR.Text != "" && checkABR())
            {
                hit = 0;
                miss = 0;
                lbHit.Text = string.Format("Hit : {0:D}", hit);
                lbMiss.Text = string.Format("Miss : {0:D}", miss);
                btSG.Enabled = false;
                btShot.Enabled = true;
                tba.ReadOnly = true;
                tbb.ReadOnly = true;
                tbR.ReadOnly = true;
                flag = true;
                tbSoots.ReadOnly = true;
                numberOfShoots = int.Parse(tbSoots.Text);
                Invalidate();
                //DrawTarget(ClientRectangle,CreateGraphics());
            }
            else
                err1.SetError((sender as Button), "Data is not correct");
        }

        private bool checkABR()
        {
            if (a > b && R > b && a > R)
                return true;
            return false;
        }

        private void btShot_Click(object sender, EventArgs e)
        {
            if (tbX.Text != "" && tbY.Text != "")
            {
                if (numberOfShoots-- > 0)
                {
                    Shot(C.X + Xs, C.Y - Ys);
                }
                if (numberOfShoots == 0)
                {
                    MessageBox.Show(String.Format("The end of game\nTotal hit : {0:D}\nTotal miss : {1:D}", hit, miss));
                    btShot.Enabled = false;
                    btSG.Enabled = true;
                    tbSoots.ReadOnly = false;
                    tba.ReadOnly = false;
                    tbb.ReadOnly = false;
                    tbR.ReadOnly = false;
                }
                tbX.Clear();
                tbY.Clear();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            if (flag)
                DrawTarget(ClientRectangle, e.Graphics);
        }

        private void Shot(int X, int Y)
        {
            if (Y < C.Y && Y > C.Y - b && X < C.X + a && X > Math.Sqrt(R * R - Math.Pow((Y - C.Y), 2)) + C.X)
            {
                DrawHit(X, Y);
            }
            else if (Y > C.Y && Y < C.Y + b && X < C.X && X > -Math.Sqrt(R * R - Math.Pow((Y - C.Y), 2)) + C.X)
            {
                DrawHit(X, Y);
            }
            else if (X < 3 * ClientRectangle.Width / 4)
            {
                DrawMiss(X, Y);
            }
            else
            {
                DrawMiss(-10, -10);
            }
        }

        private void DrawTarget(Rectangle rect, Graphics g)
        {
            double Xa = Math.Sqrt(Math.Abs(R * R - b * b));
            int angel = RadianToDegree(Math.Asin(Xa / R));
            C = new Point(3 * rect.Width / 8, rect.Height / 2);
            Point[] r = new Point[4];
            r[0] = C;
            r[1] = new Point(C.X - R, C.Y);
            r[2] = new Point(C.X - (int)Xa, C.Y + b);
            r[3] = new Point(C.X, C.Y + b);
           
            SolidBrush brush = new SolidBrush(Color.Black);
            Pen pen = new Pen(brush);
            brush.Color = Color.Gray;
            g.FillRectangle(brush, C.X, C.Y - b, a, b);
            brush.Color = Color.White;
            g.FillEllipse(brush, C.X - R, C.Y - R, 2 * R, 2 * R);
            brush.Color = Color.Gray;
            g.FillPolygon(brush, r);
            g.FillPie(brush, C.X - R, C.Y - R, 2 * R, 2 * R, 90 + angel, 90 - angel);
            g.DrawRectangle(pen, C.X - a, C.Y - b, 2 * a, 2 * b);
            g.DrawEllipse(pen, C.X - R, C.Y - R, 2 * R, 2 * R);
            g.DrawLine(pen, C.X, C.Y - R, C.X, C.Y + R);
            g.DrawLine(pen, C.X - a, C.Y, C.X + a, C.Y);
            brush.Dispose();
            pen.Dispose();
        }

        private void DrawMiss(int X, int Y)
        {
            miss++;
            lbMiss.Text = string.Format("Miss : {0:D}", miss);
            Graphics graphics = CreateGraphics();
            Pen pen = new Pen(Color.Red);
            pen.Width = 2;
            graphics.DrawLine(pen, X - 5, Y - 5, X + 5, Y + 5);
            graphics.DrawLine(pen, X + 5, Y - 5, X - 5, Y + 5);
            pen.Dispose();
            graphics.Dispose();
        }

        private void DrawHit(int X, int Y)
        {
            hit++;
            lbHit.Text = string.Format("Hit : {0:D}", hit);
            Graphics graphics = CreateGraphics();
            SolidBrush brush = new SolidBrush(Color.WhiteSmoke);
            graphics.FillEllipse(brush, X - 2, Y - 2, 4, 4);
            brush.Dispose();
            graphics.Dispose();
        }

        private int RadianToDegree(double angle)
        {
            return (int)(angle * (180.0 / Math.PI));
        }

        private void NumberValidation(object sender, CancelEventArgs e, ref int N, bool check, int max)
        {
            if (this.ActiveControl.Equals(sender))
                return;
            try
            {
                N = int.Parse((sender as TextBox).Text);
                if (check && N <= 0)
                    throw new ArgumentException("Value is less than or equal to zero");
                if (check && N > max)
                    throw new ArgumentException("Value should be less than " + max);
            }
            catch (Exception ex)
            {
                err1.SetError((sender as TextBox), ex.Message);
                (sender as TextBox).SelectAll();
                e.Cancel = true;
            }
        }

        private void tba_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref a, true, 3 * ClientRectangle.Width / 8);
        }

        private void tbb_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref b, true, ClientRectangle.Height / 2);
        }

        private void tbR_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref R, true, ClientRectangle.Height / 2);
        }

        private void tbX_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref Xs, false, -1);
        }

        private void tbY_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref Ys, false, -1);
        }

        private void tbSoots_Validating(object sender, CancelEventArgs e)
        {
            NumberValidation(sender, e, ref numberOfShoots, true, int.MaxValue);
        }

        private void tba_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void tbb_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void tbR_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void tbSoots_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void tbY_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void tbX_Validated(object sender, EventArgs e)
        {
            Clearing();
        }

        private void Clearing()
        {
            err1.Clear();
        }
    }
}