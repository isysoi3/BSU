using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Threading;


namespace events
{

    public class CalculatorEventArgs : EventArgs
    {
        public int amount { get; private set; }
        public BigInteger value { get; private set; }

        public CalculatorEventArgs(int number, BigInteger s)
        {
            amount = number;
            value = s;
        }
    }

    public delegate void CalcEventHandler(object sender, CalculatorEventArgs e);

    class Calculator
    {
        public event CalcEventHandler CalcEvent;
        public Thread mainThread;
        private Demonstrator demonstrator;
        private Dictionary<int, BigInteger> Cache = new Dictionary<int, BigInteger>() { { 0, 1 } };

        private static int sleepTime { get; set; }

        private void CreateEvent(int amount, BigInteger value)
        {
            CalcEvent?.Invoke(this, new CalculatorEventArgs(amount, value));
        }

        public Calculator(int atime)
        {
            sleepTime = atime;
        }

        public void Start()
        {
            mainThread = new Thread(Calculate);
            mainThread.Start();
        }

        private void Stop(object sender, EventArgs e)
        {
            mainThread?.Abort();
        }

        private void Calculate()
        {
            Random rnd = new Random();
            while (true)
            {
                int n = rnd.Next(0, 1000);
                BigInteger k = Schroder(n);
                Thread.Sleep(sleepTime);
                CreateEvent(n, k);
            }
        }

        private BigInteger Schroder(int n)
        {
            if (Cache.ContainsKey(n))
                return Cache[n];

            BigInteger s1 = Schroder(n - 1);
            BigInteger s = 0;
            for (int i = 0; i <= n - 1; i++)
            {
                s += Schroder(i) * Schroder(n - 1 - i);
            }

            return Cache[n] = s + s1;
        }

        /// <summary>
        /// Подписка на событие
        /// </summary>
        /// <param name="_demonstrator"></param>
        public void SetDemonstrator(Demonstrator _demonstrator)
        {
            demonstrator = _demonstrator;
            demonstrator.DemonEvent += new DemonEventHandler(Stop);
        }

    }
}
