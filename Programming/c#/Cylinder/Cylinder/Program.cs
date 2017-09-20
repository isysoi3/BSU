using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cylinder { 
    /// <summary>
    /// расчет объема цилиндра
    /// </summary>
    class Program
    {
        private static double R, h, V;
        private static string str;
        /// <summary>
        /// стартовый проект
        /// </summary>
        static void Main()
        {
            Console.WriteLine("Введите радиус основания цилиндра:");
            str = Console.ReadLine();
            R = Double.Parse(str);
            Console.WriteLine("Введите высоту:");
            str = Console.ReadLine();
            h = Double.Parse(str);

            V = Math.PI * R * R * h;
            Console.WriteLine("Объем цилиндра равен : {0:#.#####}", V);
        } // Main
    } // class
} // namespace
