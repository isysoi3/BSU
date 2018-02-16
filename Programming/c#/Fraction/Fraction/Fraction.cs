using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fraction
{
    class Fraction
    {
        private long _denominator;
        private long _numerator;

        public long numerator
        {
            get
            {
                return num;
            }
            set
            {
                num = value;
                reduce();
            }
        }

        public override string ToString()
        {
            if (den == 1)
                return num.ToString();
            return num + "/" + den;
        }

        private long num
        {
            get
            {
                return _numerator;
            }
            set
            {
                _numerator = value;
            }
        }

        private long den
        {
            get { return _denominator; }
            set
            {
                if (value <= 0)
                    throw new ArgumentException("Знаменатель <= 0");
                _denominator = value;
            }
        }

        public long denominator
        {
            get
            {
                return den;
            }
            set
            {
                den = value;
                reduce();
            }
        }

        /// <summary>
        /// Консруктор, задающий числитель и знаменатель.
        /// </summary>
        /// <param name="_num">Числитель</param>
        /// <param name="_den">Знаменатель</param>
        public Fraction(long _num = 1, long _den = 1)
        {
            num = _num;
            den = _den;
            reduce();
        }

        /// <summary>
        /// Метод для сокращения числителя и знаменателя дроби
        /// </summary>
        private void reduce()
        {
            if (num != 0)
            {
                long x = Math.Abs(num);
                long y = _denominator;
                while (y != 0)
                {
                    y = x % (x = y);
                }
                num /= x;
                den /= x;
            }
        }

        /// <summary>
        /// Метод для вывода значения дроби в формате double
        /// </summary>
        /// <returns>Значение дроби в формате double</returns>
        public double getValue()
        {
            return Convert.ToDouble(_numerator) / _denominator;
        }

        /// <summary>
        /// Перегрузка операции сложения
        /// </summary>
        /// <param name="first">Первое слогаемое</param>
        /// <param name="second">Второе слогаемое</param>
        /// <returns>Сумма двух слагаемых</returns>
        public static Fraction operator +(Fraction first, Fraction second)
        {
            return new Fraction(first.num * second.den + second.num * first.den, first.den * second.den);
        }

        /// <summary>
        /// Перегрузка операции вычитания через сложение и унарынй минус
        /// </summary>
        /// <param name="first">Первое слогаемое</param>
        /// <param name="second">Второе слогаемое</param>
        /// <returns>Разность двух слагаемых</returns>
        public static Fraction operator -(Fraction first, Fraction second)
        {
            return first + (-second);
        }

        /// <summary>
        /// Перегрузка операции умножения
        /// </summary>
        /// <param name="first">Первое слогаемое</param>
        /// <param name="second">Второе слогаемое</param>
        /// <returns>Произведение</returns>
        public static Fraction operator *(Fraction first, Fraction second)
        {
            return new Fraction(first.num * second.num, first.den * second.den);
        }

        /// <summary>
        /// Перегрузка операции деления
        /// </summary>
        /// <param name="first">Первое слогаемое</param>
        /// <param name="second">Второе слогаемое</param>
        /// <returns>Результат деления двух слагаемых</returns>
        public static Fraction operator /(Fraction first, Fraction second)
        {
            if (second.num < 0)
            {
                return new Fraction(-first.num * second.den, -first.den * second.num);
            }
            return new Fraction(first.num * second.den, first.num * second.den);
        }

        /// <summary>
        /// Перегрузка операции унарного минуса
        /// </summary>
        /// <param name="first">Дробь</param>
        /// <returns>Дробь с противоположным знаком</returns>
        public static Fraction operator -(Fraction first)
        {
            return new Fraction(-first.num, first.den);
        }
    }
}
