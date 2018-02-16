using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace fridge
{
    public partial class Form1 : Form
    {
        Fridge fr;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dgvGame.RowCount = 4;
            dgvGame.ColumnCount = 4;
            for(int i = 0; i < 4; i++)
            {
                dgvGame.Columns[i].Width = 40;
                dgvGame.Rows[i].Height = 40;
            }
            fr = new fridge.Fridge();
            showGame();
        }

        private void showGame()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (!fr.table[i, j])
                    {
                        dgvGame.Rows[i].Cells[j].Style.BackColor = Color.Red;
                        dgvGame.Rows[i].Cells[j].Value = "closed";
                    }
                    else
                    {
                        dgvGame.Rows[i].Cells[j].Style.BackColor = Color.Green;
                        dgvGame.Rows[i].Cells[j].Value = "open";
                    }
                    dgvGame.Rows[i].Cells[j].Selected = false;
                }
            }
        }

        private void dgvGame_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            fr.changeLock(e.RowIndex, e.ColumnIndex);
            showGame();
            if(fr.isFinished())
            {
                MessageBox.Show("We've opened the fridge!");
                Close();
            }
        }

        private void dgvGame_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
