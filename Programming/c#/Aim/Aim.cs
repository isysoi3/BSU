using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace Aim
{
    class Aim
    {
        //Параметры графика

        public float R { get; private set; }
        public float A { get; private set; }

        public float B { get; private set; }

        //Правая закрашенная область
        private readonly GraphicsPath _rightRegion;
        //Левая закрашенная область
        private readonly GraphicsPath _leftRegion;
        //Вершины прямоугольника, ограничивающего окружность
        private readonly PointF[] _circle;
        //Вершины прямоугольника
        private readonly PointF[] _rect;

        public Aim(float r, float a, float b)
        {
            B = b;
            A = a;
            R = r;
            _circle = new[]
                     {
                         new PointF(-R,-R),
                         new PointF(R,-R),
                         new PointF(R,R),
                         new PointF(-R,R),
                     };
            _rect = new[]
                    {
                        new PointF(-A,-B),
                        new PointF(A,-B),
                        new PointF(A,B),
                        new PointF(-A,B),
                    };
            _rightRegion = GetRightRegion();
            _leftRegion = GetLeftRegion();
        }

        public GraphicsPath RightRegion
        {
            get
            {
                return _rightRegion;
            }
        }

        public GraphicsPath LeftRegion
        {
            get
            {
                return _leftRegion;
            }
        }

        public PointF[] Circle
        {
            get
            {
                return _circle;
            }
        }

        public PointF[] Rect
        {
            get
            {
                return _rect;
            }
        }

        private GraphicsPath GetRightRegion()
        {
            var gp = new GraphicsPath();
            var angle = (float)(Math.Asin(B / R) * 180 / Math.PI);
            gp.AddArc(RectangleF.FromLTRB(_circle[0].X, _circle[0].Y, _circle[1].X, _circle[2].Y), -angle, angle);
            gp.AddLine(R, 0, A, 0);
            gp.AddLine(A, 0, A, -B);
            gp.CloseAllFigures();
            return gp;
        }

        private GraphicsPath GetLeftRegion()
        {
            var gp = new GraphicsPath();
            var angle = (float)(Math.Asin(B / R) * 180 / Math.PI);
            gp.AddArc(RectangleF.FromLTRB(_circle[0].X, _circle[0].Y, _circle[1].X, _circle[2].Y), 180 - angle, angle);
            gp.AddLine(-R, 0, 0, 0);
            gp.AddLine(0, 0, 0, B);
            gp.CloseAllFigures();
            return gp;
        }

    }
}
