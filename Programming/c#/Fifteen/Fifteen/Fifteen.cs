using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fifteen
{
    class Fifteen
    {
        public int[,] table { get; private set; }
        private int[,] secondtable { get; set; }
        public int count { get; private set; }

        public Fifteen()
        {
            table = new int[4, 4];
            secondtable = new int[4, 4];
        }

        private static void Shuffle(int[,] array)
        {
            Random rnd = new Random();
            for (int i = 1; i < 16; i++)
            {
                int a = i / 4;
                int b = i % 4;

                int j = rnd.Next(i + 1);
                int a1 = j / 4;
                int b1 = j % 4;

                int temp = array[a, b];
                array[a, b] = array[a1, b1];
                array[a1, b1] = temp;
            }
        }

        public void NewGame()
        {
            count = 0;
            int k = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    table[i, j] = ++k;
            do
            {
                Shuffle(table);
            } while (!(IsCollected() || IsFinished()));
            secondtable = table.Clone() as int[,];
        }

        private bool IsCollected()
        {
            int k = 0;
            int num = 0;
            int[] mas = new int[16];
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    mas[k++] = table[i, j];
                }
            for (int i = 0; i < 16; i++)
                if (mas[i] != 16)
                {
                    for (int j = i; j < 16; ++j)
                        if (mas[i] > mas[j] && mas[j] != 16)
                            num++;
                }
                else
                    num += 1 + i / 4;
            return (num & 1) == 0;
        }

        public bool IsFinished()
        {
            int k = 1;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (table[i, j] != k++)
                        return false;
            return true;
        }

        private void Swap(ref int a, ref int b)
        {
            a = b;
            b = 16;
            count++;
        }

        public void ChangeLock(int r, int c)
        {
            if (r != 0 && table[r - 1, c] == 16)
            {
                Swap(ref table[r - 1, c], ref table[r, c]);
            }
            else if (r != 3 && table[r + 1, c] == 16)
            {
                Swap(ref table[r + 1, c], ref table[r, c]);
            }
            else if (c != 0 && table[r, c - 1] == 16)
            {
                Swap(ref table[r, c - 1], ref table[r, c]);
            }
            else if (c != 3 && table[r, c + 1] == 16)
            {
                Swap(ref table[r, c + 1], ref table[r, c]);
            }
        }

        public void RepeatGame()
        {
            count = 0;
            table = secondtable.Clone() as int[,];
        }
    }
}