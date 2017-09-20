using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Fraction;

namespace Fraction
{
    class Program
    {
        /// <summary>
        /// Функция для выбора действия c дробью
        /// </summary>
        static char option()
        {
            char n;
            Console.WriteLine("\n1 - Сумма дробей\n2 - Разность дробей\n3 - Умножение дробей\n4 - Деление дробей\n5 - Унарный минус\n0 - Выход");
            while ((n = Console.ReadKey().KeyChar) != '1' && n != '2' && n != '3' && n != '4' && n != '5' && n != '0') ;
            return n;
        }

        static void Main(string[] args)
        {
            Fraction f, d;
            Fraction rez = new Fraction();
            Console.WriteLine("Введите числитель, знаменатель первой дроби");
            long num1 = long.Parse(Console.ReadLine());
            long den1 = long.Parse(Console.ReadLine());
            try
            {
                f = new Fraction(num1, den1);
            }
            catch (ArgumentException e)
            {
                Console.WriteLine(e.Message);
                return;
            }
            Console.WriteLine("Введите числитель, знаменатель второй дроби");
            long num2 = long.Parse(Console.ReadLine());
            long den2 = long.Parse(Console.ReadLine());
            try
            {
                d = new Fraction(num2, den2);
            }
            catch (ArgumentException e)
            {
                Console.WriteLine(e.Message);
                return;
            }

            char choice;
            while (true)
            {
                choice = option();
                Console.Clear();
                if (choice != '0')
                {
                    switch (choice)
                    {
                        case '1':
                            rez = f + d;
                            Console.WriteLine("Сумма = {0}", (rez).ToString());
                            break;
                        case '2':
                            rez = f - d;
                            Console.WriteLine("Разность = {0}", (rez).ToString());
                            break;
                        case '3':
                            rez = f * d;
                            Console.WriteLine("Произведение = {0}", (rez).ToString());
                            break;
                        case '4':
                            {
                                try
                                {
                                    rez = f / d;
                                }
                                catch (ArgumentException e)
                                {
                                    Console.WriteLine(e.Message);
                                    break;
                                }
                                Console.WriteLine("Деление = {0:F}", (rez).ToString());
                            }
                            break;
                        case '5':
                            rez = -rez;
                            Console.WriteLine("Унарный минус = {0:F}", (rez).ToString());
                            break;
                    }
                }
                else
                    break;
            }
            Console.WriteLine("Знаменатель первой дроби до изменения равен {0:D}", f.numerator);
            f.numerator = 1;
            Console.WriteLine("Знаменатель первой дроби после изменения на 1 равен {0:D}", f.numerator);
            Console.WriteLine("Десятичная дробь {0:F} ", f.getValue());
        }
    }
}
