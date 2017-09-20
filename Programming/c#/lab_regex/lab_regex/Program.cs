using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace lab_regex
{
    class Program
    {
        /// <summary>
        /// Проверка строки
        /// </summary>
        /// <param name="str"></param>
        /// <returns>Строка(путь к файлу)</returns>
        static string Check(string str)
        {
            //StringBuilder s = new StringBuilder(str);
            if (str.First() == '"' && str.Last() == '"')
            {
                str = str.Remove(0, 1);
                str = str.Remove(str.Length - 1, 1);
            }
            return str;
            //return s.ToString();
        }


        static void Main(string[] args)
        {
            Console.WriteLine("Введите имя файла");
            string file = Console.ReadLine();
            int count = 0;

            file = Check(file);

            if (File.Exists(file))
            {
                //\b(([1][0-9])|[1-9])\:([0-5][0-9]).[a|p]\.[m]\.
                string pattern = @"\b(([1]\d)|[1-9])\:([0-5]\d).[a|p]\.[m]\.";
                Regex regex = new Regex(pattern);
                using (StreamReader sr = new StreamReader(file))
                {
                    while (!sr.EndOfStream)
                    {
                        if (!regex.IsMatch(sr.ReadLine()))
                            count++;
                    }
                }
                Console.WriteLine("В {0:d} строках не найдено время в 12-часовом формате", count);
            }
            else
            {
                Console.Error.WriteLine("Не удалось открыть файл!");
            }

        }
    }
}
 