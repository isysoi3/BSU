using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace vietnam
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            DrawFlag(ClientRectangle, e.Graphics);
        }

        private void DrawFlag(Rectangle r, Graphics g)
        {
            const int PROPX = 2, PROPY = 3;
            g.Clear(Color.Gray);

            int H = r.Height, W = r.Width;
            Point WN = new Point(0, 0);
            if (PROPX * r.Width > PROPY * r.Height) // широкое поле
            {
                W = H * PROPY / PROPX;
                WN.X = (r.Width - W) / 2;
            }
            else if (PROPX * r.Width < PROPY * r.Height) // высокое поле
            {
                H = W * PROPX / PROPY;
                WN.Y = (r.Height - H) / 2;
            }
            Point C = new Point(WN.X + W / 2, WN.Y + H / 2);

            int n = 5;              
            double R1 = H / 3, R2 = H / 8;
            double alpha = 0, tmp = Math.PI / n;

            Point[] points = new Point[n * 2];
            for (int i = 0; i < n; i++)
            {
                points[i*2] = new Point((int)(C.X + R1 * Math.Sin(alpha)), (int)(C.Y - R1 * Math.Cos(alpha)));
                alpha += tmp;
                points[i*2 +1] = new Point((int)(C.X + R2 * Math.Sin(alpha)), (int)(C.Y - R2 * Math.Cos(alpha)));
                alpha += tmp;
            }



            SolidBrush brush = new SolidBrush(Color.Red);
            g.FillRectangle(brush, WN.X, WN.Y, W, H);

            brush.Color = Color.Yellow;
            g.FillPolygon(brush, points);

            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();

            brush.Color = Color.White;
            g.DrawString("Вьетнам", font, brush, 0, 0, drawFormat);
            brush.Dispose();
            font.Dispose();



        }

        private void Form1Resize(object sender, EventArgs e)
        {
            Invalidate();
        }
    }
}
