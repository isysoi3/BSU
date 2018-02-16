using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace events
{
    delegate void StopHandler();
    delegate void TextInvokeHandler(string text);

    class Demonstrator
    {
        public event StopHandler StopCalculate;

        public void Stop()
        {
            StopCalculate?.Invoke();
        }

        public static void Message(int n, BigInteger s, int time)
        {
            String str;
            str = String.Format("The {0}-th Schroders number is {1}\n", n, s);
            textInvoke = new TextInvokeHandler(ShowText);
            Form.output.Invoke(textInvoke, str);
            Thread.Sleep(time);

            Calculator calculate = new Calculator(time);
            calculate.EventEndCalculate += Demonstrator.Message;
            calculate.Calculate();

        }
        
        private static TextInvokeHandler textInvoke;

        private static void ShowText(string text)
        {
            Form.output.Text = text + "\n" + Form.output.Text;
        }
    }
}
