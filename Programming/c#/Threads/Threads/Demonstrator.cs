using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace events
{


    public class ShootEventArgs : EventArgs
    {
        public Point shoot { get; private set; }

        public ShootEventArgs(Point ashoot)
        {
            shoot = ashoot;
        }
    }

    public delegate void DemonEventHandler(object sender, EventArgs e);
    public delegate void ShootEventHandler(object sender, ShootEventArgs e);

    class Demonstrator
    {
        public Aim aim;
        public event DemonEventHandler DemonEvent;
        public event CalcEventHandler CalcEvent;
        public event ShootEventHandler ShootEvent;
        private Calculator calculator;
        private int delay;
        private int maxX;
        private int maxY;
        private Thread shootThread;

        public Demonstrator(int a, int b, int r, int d, int _maxX, int _maxY)
        {
            aim = new Aim(r, a, b);
            maxX = _maxX;
            maxY = _maxY;
            delay = d;
        }

        /// <summary>
        /// Остановить вычисление
        /// </summary>
        public void StopCalculation()
        {
            DemonEvent?.Invoke(this, new EventArgs());
        }

        /// <summary>
        /// Остановить стрельбу
        /// </summary>
        public void StopShooting()
        {
            if (calculator.mainThread.IsAlive)
                throw new Exception("Вычислитель не остановлен");
            shootThread?.Abort();
        }

        /// <summary>
        /// Событие выстрела
        /// </summary>
        /// <param name="_shoot"></param>
        private void CreateShootEvent(Point _shoot)
        {
            ShootEvent?.Invoke(this, new ShootEventArgs(_shoot));
        }

        /// <summary>
        /// Начало стрельбы
        /// </summary>
        public void StartShooting()
        {
            shootThread = new Thread(Shooting);
            shootThread.Start();
        }

        /// <summary>
        /// Генерация выстрела
        /// </summary>
        private void Shooting()
        {
            Random rand = new Random();
            while (true)
            {
                Point xy = new Point
                {
                    X = rand.Next(-maxX, maxX + 1),
                    Y = rand.Next(-maxY, maxY + 1)
                };
                CreateShootEvent(xy);
                Thread.Sleep(delay);
            }
        }

        /// <summary>
        /// Подписка на событие
        /// </summary>
        /// <param name="calc"></param>
        public void SetCalculator(Calculator calc)
        {
            calculator = calc;
            calculator.SetDemonstrator(this);
            calculator.CalcEvent += new CalcEventHandler(Calculated);
        }

        /// <summary>
        /// Вызов события
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Calculated(object sender, CalculatorEventArgs e)
        {
            CalcEvent?.Invoke(this, e);
        }

        /// <summary>
        /// Старт
        /// </summary>
        public void Start()
        {
            calculator?.Start();
        }
    }
}
