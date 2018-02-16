using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PaMa
{
    class SayClass
    {
        private string word;
        private int repeats;
        private int delay;
        public static object lo = new object();

        public static int ToatalRepeats { private get; set; }

        public SayClass(string str, int r, int d)
        {
            word = str;
            repeats = r;
            delay = d;
        }

        public void Say()
        {
            for (int i = 0; i < repeats && ToatalRepeats > 0; ToatalRepeats--, i++)
            {
                Thread.Sleep(delay);
                lock (lo)
                {
                    if (ToatalRepeats <= 0)
                        break;
                    Console.Write(word + " ");
                }
            }
            //Thread.CurrentThread.Abort();
        }

        //public void Say()
        //{

        //    int tmp = repeats;
        //    while (ToatalRepeats != 0 && tmp != 0)
        //    {
        //        ToatalRepeats--;
        //        tmp--;
        //        Thread.Sleep(delay);
        //        Console.Write(word + " ");
        //    }

        //    Thread.CurrentThread.Abort();

        //}
    }


}

