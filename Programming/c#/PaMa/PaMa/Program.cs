using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PaMa
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Введите общее количество повторений: ");
            SayClass.ToatalRepeats = int.Parse(Console.ReadLine());
            
            SayClass w1 = new SayClass("Папа", 2, 150);
            SayClass w2 = new SayClass("Мама", 2, 100);
            SayClass w3 = new SayClass("Я", 7, 10);

            Thread t1 = new Thread(w1.Say);
            Thread t2 = new Thread(w2.Say);
            Thread t3 = new Thread(w3.Say);

            t1.Start();
            t2.Start();
            t3.Start();
        }
    }
}
