using System;
using System.Collections;
using System.Collections.Generic;
using System.Data.Common;
using System.Diagnostics.Eventing.Reader;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Program
    {

        private static int CountSymbols(string str)
        {
            HashSet<char> symbols = new HashSet<char>();
            foreach (char c in str)
            {
                symbols.Add(c);
            }
            return symbols.Count;
        }


        static void Main(string[] args)
        {
            LinkedList<string> deq = new LinkedList<string>();
            using (StreamReader sr =
                new StreamReader(@"C:\Users\ilya\Documents\Visual Studio 2015\Projects\c#\lab1\lab1\in.txt"))
            {
                while (!sr.EndOfStream)
                {
                    deq.AddLast(sr.ReadLine());
                }
            }
            var orderedResult = deq.OrderByDescending(s => { return CountSymbols(s); });
            deq = new LinkedList<string>(deq.OrderByDescending(s => { return CountSymbols(s); }));
            using (StreamWriter sw =
                new StreamWriter(@"C:\Users\ilya\Documents\Visual Studio 2015\Projects\c#\lab1\lab1\out.txt"))
            {
                foreach (string str in orderedResult)
                {
                    sw.WriteLine("{0}", str);
                }
            }
        }
    }
}