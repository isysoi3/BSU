using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BinaryTree;

namespace BST_Lab
{
    class Program
    {
        static void check(int x, MyTree tr)
        {
            if (tr.Find(x))
                Console.WriteLine("Найден");
            else
            {
                Console.WriteLine("Не найден");
            }
        }

        static void Main(string[] args)
        {
            MyTree tr = new MyTree();
            using (StreamReader sr = new StreamReader(@"test.txt"))
            {
                while (!sr.EndOfStream)
                {
                    tr.Insert(int.Parse(sr.ReadLine()));
                }
            }

            do
            {
                tr.Print();
                Console.ReadKey();
            } while (tr.DeleteMinMax());

        }
    }
}