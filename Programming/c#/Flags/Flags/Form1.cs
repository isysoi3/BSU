using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Flags
{
    delegate void paint(Rectangle r, Graphics g);

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }

        private paint p;

        private Point wnPoint(Rectangle r, int PROPX, int PROPY, out int H, out int W)
        {
            Point WN = new Point(0, menu.Height);
            H = r.Height;
            W = r.Width;
            if (PROPX * r.Width > PROPY * r.Height) // широкое поле
            {
                W = H * PROPY / PROPX;
                WN.X = (r.Width - W) / 2;
            }
            else if (PROPX * r.Width < PROPY * r.Height) // высокое поле
            {
                H = W * PROPX / PROPY;
                WN.Y += (r.Height - H) / 2;
            }
            return WN;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.Clear(Color.Gray);
            Rectangle newRect = new Rectangle(new Point(ClientRectangle.X, ClientRectangle.Y + menu.Height), new Size(ClientRectangle.Width, ClientRectangle.Height - menu.Height));
            if (p != null)
                p(newRect, e.Graphics);
            //p?.Invoke(newRect, e.Graphics);
        }

        private void DrawKNDR(Rectangle r, Graphics g)
        {
            const int PROPX = 1, PROPY = 2;
            int H, W;
            Point WN = wnPoint(r, PROPX, PROPY, out H, out W);
            Point C = new Point(WN.X + W / 3, WN.Y + H / 2);
            Point P1 = new Point(WN.X, WN.Y + 6 * H / 30);
            Point P2 = new Point(WN.X, WN.Y + H / 6);

            SolidBrush brush = new SolidBrush(Color.Blue);
            g.FillRectangle(brush, WN.X, WN.Y, W, H);
            brush.Color = Color.White;
            g.FillRectangle(brush, P2.X, P2.Y, W, 4 * H / 6);
            brush.Color = Color.Red;
            g.FillRectangle(brush, P1.X, P1.Y, W, 18 * H / 30);
            brush.Color = Color.White;
            g.FillEllipse(brush, C.X - H / 4, C.Y - H / 4, 2 * H / 4, 2 * H / 4);
            brush.Color = Color.Red;
            Draw_Star(5, H / 4, H / 9, C, brush, g);

            Write(brush, g, "КНДР");
            brush.Dispose();
        }

        private void Write(SolidBrush brush, Graphics g, string str)
        {
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            brush.Color = Color.Black;
            g.DrawString(str, font, brush, 0, 25, drawFormat);
            font.Dispose();
        }

        private void DrawUAR(Rectangle r, Graphics g)
        {
            int H, W;
            const int PROPX = 2, PROPY = 3;
            Point WN = wnPoint(r, PROPX, PROPY, out H, out W);

            Point[] tringleOrange = new Point[3];
            Point[] tringleBlack = new Point[3];
            Point[] trapezeRed = new Point[4];
            Point[] trapezeBlue = new Point[4];
            Point[] trapezeWhite1 = new Point[4];
            Point[] trapezeWhite2 = new Point[4];

            tringleOrange[0] = new Point(WN.X, WN.Y + 7 * H / 60);
            tringleOrange[1] = new Point(WN.X + 17 * W / 45, WN.Y + H / 2);
            tringleOrange[2] = new Point(WN.X, WN.Y + 53 * H / 60);

            tringleBlack[0] = new Point(WN.X, WN.Y + H / 5);
            tringleBlack[1] = new Point(WN.X + 3 * W / 10, WN.Y + H / 2);
            tringleBlack[2] = new Point(WN.X, WN.Y + 4 * H / 5);

            trapezeRed[0] = new Point(WN.X + W, WN.Y + H / 3);
            trapezeRed[1] = new Point(WN.X + 8 * W / 15, WN.Y + H / 3);
            trapezeRed[2] = new Point(WN.X + W / 5, WN.Y);
            trapezeRed[3] = new Point(WN.X + W, WN.Y);

            trapezeBlue[0] = new Point(WN.X + W, WN.Y + 2 * H / 3);
            trapezeBlue[1] = new Point(WN.X + 8 * W / 15, WN.Y + 2 * H / 3);
            trapezeBlue[2] = new Point(WN.X + W / 5, WN.Y + H);
            trapezeBlue[3] = new Point(WN.X + W, WN.Y + H);

            trapezeWhite1[0] = new Point(WN.X + W, WN.Y);
            trapezeWhite1[1] = new Point(WN.X + 11 * W / 90, WN.Y);
            trapezeWhite1[2] = new Point(WN.X + 47 * W / 90, WN.Y + 2 * H / 5);
            trapezeWhite1[3] = new Point(WN.X + W, WN.Y + 2 * H / 5);

            trapezeWhite2[0] = new Point(WN.X + W, WN.Y + 3 * H / 5);
            trapezeWhite2[1] = new Point(WN.X + 47 * W / 90, WN.Y + 3 * H / 5);
            trapezeWhite2[2] = new Point(WN.X + 11 * W / 90, WN.Y + H);
            trapezeWhite2[3] = new Point(WN.X + W, WN.Y + H);

            SolidBrush brush = new SolidBrush(Color.DarkGreen);
            g.FillRectangle(brush, WN.X, WN.Y, W, H);
            brush.Color = Color.White;
            g.FillPolygon(brush, trapezeWhite1);
            g.FillPolygon(brush, trapezeWhite2);
            brush.Color = Color.DarkOrange;
            g.FillPolygon(brush, tringleOrange);
            brush.Color = Color.Black;
            g.FillPolygon(brush, tringleBlack);
            brush.Color = Color.Red;
            g.FillPolygon(brush, trapezeRed);
            brush.Color = Color.Blue;
            g.FillPolygon(brush, trapezeBlue);

            Write(brush, g, "ЮАР");
            brush.Dispose();
        }

        private void Draw_Star(int n, double R1, double R2, Point Star, SolidBrush brush, Graphics a)
        {
            double alpha = 0, tmp = Math.PI / n;

            Point[] points = new Point[n * 2];
            for (int i = 0; i < n; i++)
            {
                points[i * 2] = new Point((int)(Star.X + R1 * Math.Sin(alpha)), (int)(Star.Y - R1 * Math.Cos(alpha)));
                alpha += tmp;
                points[i * 2 + 1] = new Point((int)(Star.X + R2 * Math.Sin(alpha)), (int)(Star.Y - R2 * Math.Cos(alpha)));
                alpha += tmp;
            }
            a.FillPolygon(brush, points);
        }

        private void KNDRToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Invalidate();
            p = new paint(DrawKNDR);
        }

        private void UARToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Invalidate();
            p = new paint(DrawUAR);
        }
    }
}





//int H = r.Height, W = r.Width;
//Point WN = new Point(0, 0);
//    if (PROPX* r.Width > PROPY* r.Height) // широкое поле
//{
//    W = H * PROPY / PROPX;
//    WN.X = (r.Width - W) / 2;
//}
//    else if (PROPX* r.Width<PROPY * r.Height) // высокое поле
//{
//    H = W * PROPX / PROPY;
//    WN.Y = (r.Height - H) / 2;
//}
//Point C = new Point(WN.X + W / 3, WN.Y + H / 2);
//Point P1 = new Point(WN.X, WN.Y + 6 * H / 30);
//Point P2 = new Point(WN.X, WN.Y + H / 6);

//SolidBrush brush = new SolidBrush(Color.Blue);
//g.FillRectangle(brush, WN.X, WN.Y, W, H);
//    brush.Color = Color.White;
//    g.FillRectangle(brush, P2.X, P2.Y, W, 4 * H / 6);
//    brush.Color = Color.Red;
//    g.FillRectangle(brush, P1.X, P1.Y, W, 18 * H / 30);
//    brush.Color = Color.White;
//    g.FillEllipse(brush, C.X - H / 4, C.Y - H / 4, 2 * H / 4, 2 * H / 4);
//    brush.Color = Color.Red;
//    Draw_Star(5, H / 4, H / 9, C, brush, g);


//Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
//StringFormat drawFormat = new System.Drawing.StringFormat();

//brush.Color = Color.Red;
//    g.DrawString("КНДР", font, brush, 0, 25, drawFormat);
//    brush.Dispose();
//    font.Dispose();
