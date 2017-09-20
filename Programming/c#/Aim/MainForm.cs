using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace Aim
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            //Принудительное обновление параметров
            Nud_ValueChanged(null, new EventArgs());
            //Пересчёт при перерисовке
            panel1.Resize += (_, __) => Nud_ValueChanged(null, new EventArgs());
        }

        private Aim _aim;
        private float _scale = 1;
        private readonly float _sq2 = (float)Math.Sqrt(2);

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            var w = panel1.ClientSize.Width / 2f;
            var h = panel1.ClientSize.Height / 2f;
            e.Graphics.SmoothingMode = SmoothingMode.HighQuality;
            e.Graphics.TranslateTransform(w, h);

            //Масштабирование графика
            using (var m = new Matrix())
            {
                m.Scale(_scale, _scale);
                _aim.RightRegion.Transform(m);
                _aim.LeftRegion.Transform(m);
                m.TransformPoints(_aim.Rect);
                m.TransformPoints(_aim.Circle);
            }
            //Заливка областей
            e.Graphics.FillPath(Brushes.GreenYellow, _aim.RightRegion);
            e.Graphics.FillPath(Brushes.GreenYellow, _aim.LeftRegion);
            //Прямоугольник
            e.Graphics.DrawPolygon(Pens.Red, _aim.Rect);
            //Окружность
            e.Graphics.DrawEllipse(Pens.Blue, RectangleF.FromLTRB(_aim.Circle[0].X, _aim.Circle[0].Y, _aim.Circle[1].X, _aim.Circle[2].Y));
            //Ось X со стрелкой
            var arrow = GetArrow(0, 0, w, 0);
            e.Graphics.DrawLine(Pens.Black, -w, 0, w, 0);
            e.Graphics.DrawLines(Pens.Black, arrow);
            //Ось Y со стрелкой
            arrow = GetArrow(0, 0, 0, -h);
            e.Graphics.DrawLine(Pens.Black, 0, -h, 0, h);
            e.Graphics.DrawLines(Pens.Black, arrow);
            //Надписи
            DrawText("X", new PointF(w - 15, 5), e.Graphics);
            DrawText("Y", new PointF(-15, -h), e.Graphics);
            DrawText(string.Format("-{0}",_aim.A), new PointF(-_aim.A * _scale, -15), e.Graphics);
            DrawText(string.Format("{0}", _aim.A), new PointF(_aim.A * _scale, -15), e.Graphics);
            DrawText(string.Format("{0}", _aim.B), new PointF(-15, -_aim.B * _scale), e.Graphics);
            DrawText(string.Format("-{0}", _aim.B), new PointF(-15, _aim.B * _scale), e.Graphics);
            var pt = new PointF(-_aim.R * _scale / _sq2, -_aim.R * _scale / _sq2);
            e.Graphics.DrawLine(Pens.Black, 0, 0, pt.X, pt.Y);
            e.Graphics.DrawLines(Pens.Black, GetArrow(0, 0, pt.X, pt.Y));
            DrawText(string.Format("{0}", _aim.R), new PointF(pt.X - 15, pt.Y - 15), e.Graphics);

        }

        private void DrawText(string s, PointF point, Graphics g)
        {
            g.DrawString(s, Font, Brushes.Black, point);
        }

        private void Nud_ValueChanged(object sender, EventArgs e)
        {
            var maxValue = Math.Max(Math.Max(rNud.Value, aNud.Value), bNud.Value);
            var minSize = Math.Min(panel1.ClientSize.Width, panel1.ClientSize.Height) * 0.95m;
            _scale = (float)(minSize / maxValue) / 2;
            _aim = new Aim((float)rNud.Value, (float)aNud.Value, (float)bNud.Value);
            panel1.Invalidate();
        }

        private static PointF[] GetArrow(float x1, float y1, float x2, float y2, float len = 10, float width = 4)
        {
            PointF[] result = new PointF[3];
            //направляющий вектор отрезка
            var n = new PointF(x2 - x1, y2 - y1);
            //Длина отрезка
            var l = (float)Math.Sqrt(n.X * n.X + n.Y * n.Y);
            //Единичный вектор
            var v1 = new PointF(n.X / l, n.Y / l);
            //Длина стрелки
            n.X = x2 - v1.X * len;
            n.Y = y2 - v1.Y * len;
            result[0] = new PointF(n.X + v1.Y * width, n.Y - v1.X * width);
            result[1] = new PointF(x2, y2);
            result[2] = new PointF(n.X - v1.Y * width, n.Y + v1.X * width);
            return result;
        }
    }
}
