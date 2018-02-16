using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;


namespace events
{
    delegate void EventCaclculatorHandler(int n, BigInteger s, int time);

    class Calculator
    {
        public event EventCaclculatorHandler EventEndCalculate;

        public static bool isActive { get; private set; }

        public static int PauseTime { get; private set; }

        public Calculator(int atime)
        {
            PauseTime = atime;
            isActive = true;
        }

        public static void StopHandler()
        {
            Form.thread.Abort();
            isActive = false;
            Form.output.Text = "STOP!!!\n\n" + Form.output.Text;
        }

        public void Calculate()
        {
            if (isActive)
            {
                Random rnd = new Random();
                int n = rnd.Next(0, 1000);

                BigInteger k = Schroder(n);

                EventEndCalculate?.Invoke(n, k, PauseTime);
            }
        }

        private Dictionary<int, BigInteger> Cache = new Dictionary<int, BigInteger>() { { 0, 1 } };

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

    }
}
