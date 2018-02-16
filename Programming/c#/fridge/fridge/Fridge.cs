using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fridge
{
    class Fridge
    {
        public  bool [,] table { get; private set; }
        
        public Fridge()//inisializing the array, random filling of the table, checking, that the game isn't won at the start
        {
            table = new bool[4, 4];
            newGame();
        }

        public void newGame()//we put this as a function to make an option new game in the menu
        {
            Random rnd = new Random();
            do
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        table[i, j] = (rnd.Next() % 2 == 0); //bit operation would be more effective and fast
                    } 
                }
            } while (isFinished()); //method, checking if the fridge is solved. public function
        }

        public bool isFinished()
        {
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(!table[i, j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public void changeLock(int r, int c)
        {
            for(int i = 0; i < 4; i++)
            {
                table[i, c] = !table[i, c];
                table[r, i] = !table[r, i];
            }
            table[r, c] = !table[r, c];
        }
    }
}
