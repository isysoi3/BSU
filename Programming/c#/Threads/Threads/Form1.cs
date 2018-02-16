using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace events
{
    delegate void SetTextCallback(TextBox tb, string text);

    public partial class Form : System.Windows.Forms.Form
    {
        public Form()
        {
            InitializeComponent();
            C = new PointF(Target.ClientSize.Width / 2f, Target.ClientSize.Height / 2f);
        }

        private List<Point> shootsPoint = new List<Point>();
        Calculator calculator;
        Demonstrator demonstrator;
        private PointF C;
        private int hit, miss;

        /// <summary>
        /// Рисование мишени
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="g"></param>
        private void TargetDraw(object sender, Graphics g)
        {
            if (demonstrator == null)
                return;
            for (int i = 0; i < shootsPoint.Count; i++)
                g.FillEllipse(Brushes.Black, shootsPoint[i].X - 3, shootsPoint[i].Y - 3, 6, 6);
            g.Clear(Color.White);
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.TranslateTransform(C.X, C.Y);
            g.FillPath(Brushes.Gray, demonstrator.aim.RightRegion);
            g.FillPath(Brushes.Gray, demonstrator.aim.LeftRegion);
            g.DrawPolygon(Pens.Gray, demonstrator.aim.Rect);
            g.DrawEllipse(Pens.Gray, RectangleF.FromLTRB(demonstrator.aim.Circle[0].X, demonstrator.aim.Circle[0].Y, demonstrator.aim.Circle[1].X, demonstrator.aim.Circle[2].Y));
            g.DrawLine(Pens.Black, -C.X, 0, C.Y, 0);
            g.DrawLine(Pens.Black, 0, -C.Y, 0, C.Y);
            for (int i = 0; i < shootsPoint.Count; i++)
                g.FillEllipse(Brushes.Black, shootsPoint[i].X - 3, shootsPoint[i].Y - 3, 6, 6);
        }

        /// <summary>
        /// Рисование попадания
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ShootPoint(object sender, ShootEventArgs e)
        {
            shootsPoint.Add(e.shoot);
            Graphics g = Target.CreateGraphics();
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.TranslateTransform(C.X, C.Y);
            g.FillEllipse(Brushes.Black, e.shoot.X - 3, e.shoot.Y - 3, 6, 6);
            ShowResult(e.shoot.X + (int)C.X, e.shoot.Y + (int)C.Y);
        }

        /// <summary>
        /// Дабавление текста
        /// </summary>
        /// <param name="tb"></param>
        /// <param name="text"></param>
        private void AppendText(TextBox tb, string text)
        {
            if (tb.InvokeRequired)
            {
                SetTextCallback s = new SetTextCallback(AppendText);
                this.Invoke(s, tb, text);
            }
            else
            {
                tb.AppendText(text + Environment.NewLine);
            }
        }

        /// <summary>
        /// Строка расчета
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Print(object sender, CalculatorEventArgs e)
        {
            AppendText(output, string.Format("{0:D}-ое число Шредера равно {1:D}\n", e.amount, e.value));
        }


        /// <summary>
        /// Нажатие кнопки стоп калькулятор
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btStopClac_Click(object sender, EventArgs e)
        {
            demonstrator?.StopCalculation();
            btS.Enabled = true;
        }

        /// <summary>
        /// Закрытие формы
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (demonstrator != null)
            {
                demonstrator.StopCalculation();
                demonstrator.StopShooting();
            }
        }

        /// <summary>
        /// Выстрелы кол-во
        /// </summary>
        /// <param name="tb"></param>
        /// <param name="text"></param>
        private void AppendTextShoot(TextBox tb, string text)
        {
            if (tb.InvokeRequired)
            {
                SetTextCallback s = new SetTextCallback(AppendTextShoot);
                this.Invoke(s, tb, text);
            }
            else
            {
                tb.Clear();
                tb.AppendText(text);
            }
        }

        /// <summary>
        /// Кнопка стоп стрельба
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btStopShoot_Click(object sender, EventArgs e)
        {
            try
            {
                demonstrator.StopShooting();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        /// <summary>
        /// Проверка выстрела
        /// </summary>
        /// <param name="X"></param>
        /// <param name="Y"></param>
        /// <returns></returns>
        private bool Shot(int X, int Y)
        {

            if (Y < C.Y && Y > C.Y - demonstrator.aim.B && X < C.X + demonstrator.aim.A && X > Math.Sqrt(demonstrator.aim.R * demonstrator.aim.R - Math.Pow((Y - C.Y), 2)) + C.X)
            {
                return true;
            }
            if (Y > C.Y && Y < C.Y + demonstrator.aim.B && X < C.X && X > -Math.Sqrt(demonstrator.aim.R * demonstrator.aim.R - Math.Pow((Y - C.Y), 2)) + C.X)
            {
                return true;
            }
            return false;
        }

        private void ShowResult(int X, int Y)
        {
            if (Shot(X, Y))
                hit++;
            else
                miss++;
            AppendTextShoot(textBoxGoodShoots, hit.ToString());
            AppendTextShoot(textBoxMisses, miss.ToString());
        }

        private void btS_Click(object sender, EventArgs e)
        {
            int sleepTime = 0;

            int tm, mxX, mxY, R, a, b;
            try
            {
                tm = Convert.ToInt32(textBoxTimeBetweenShoots.Text);
                R = Convert.ToInt32(tbR.Text);
                a = Convert.ToInt32(tbA.Text);
                b = Convert.ToInt32(tbB.Text);
                mxX = Convert.ToInt32(textBoxX.Text);
                mxY = Convert.ToInt32(textBoxY.Text);
                sleepTime = Convert.ToInt32(textBoxTime.Text);
            }
            catch (Exception)
            {
                MessageBox.Show("Incorrect Data");
                return;
            }

            if (tm < 0 || tm > 100000 || R < 0 || R > Target.Height / 2
                || mxX > Target.Width || mxX < 0 || mxY > Target.Height || mxY < 0 || sleepTime < 0 || sleepTime > 10000)
            {
                MessageBox.Show("Incorrect Data");
                return;
            }
            try
            {
                if (demonstrator != null)
                {
                    demonstrator.StopCalculation();
                    demonstrator.StopShooting();
                }
                demonstrator = new Demonstrator(a, b, R, tm, mxX, mxY);
                calculator = new Calculator(Convert.ToInt32(textBoxTime.Text));
                demonstrator.SetCalculator(calculator);
                demonstrator.Start();
                demonstrator.ShootEvent += new ShootEventHandler(ShootPoint);
                demonstrator.CalcEvent += new CalcEventHandler(Print);
                TargetDraw(Target.ClientRectangle, Target.CreateGraphics());
                demonstrator.StartShooting();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
            btS.Enabled = false;
            tbA.ReadOnly = true;
            tbR.ReadOnly = true;
            tbB.ReadOnly = true;
            textBoxX.ReadOnly = true;
            textBoxY.ReadOnly = true;
            textBoxTimeBetweenShoots.ReadOnly = true;
            textBoxTime.ReadOnly = true;

        }
    }

}

//private void textBoxTime_Validating(object sender, CancelEventArgs e)
//{
//    try
//    {
//        DelayTime = int.Parse((sender as TextBox).Text);
//        if (DelayTime <= 0)
//            throw new ArgumentException("sleepTime DelayTime can't be lower then zero.");
//    }
//    catch (Exception ex)
//    {
//        error.SetError((sender as TextBox), ex.Message);
//        (sender as TextBox).SelectAll();
//        e.Cancel = true;
//    }
//}

//private void textBoxTime_Validated(object sender, EventArgs e)
//{
//    error.Clear();
//}
