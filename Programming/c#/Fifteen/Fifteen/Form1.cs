using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace fifteen
{
    public partial class Form1 : Form
    {
        private Fifteen sp;
        private DateTime time;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dgvGame.RowCount = 4;
            dgvGame.ColumnCount = 4;
            dgvGame.ColumnHeadersVisible = false;
            dgvGame.RowHeadersVisible = false;
            dgvGame.CellBorderStyle = DataGridViewCellBorderStyle.Raised;
            for (int i = 0; i < 4; i++)
            {
                dgvGame.Columns[i].Width = 60;
                dgvGame.Rows[i].Height = 60;
            }
            sp = new Fifteen();
        }

        private void ShowGame()
        {
            lb2.Text = string.Format("Clicks: {0:D}", sp.count);
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    if (sp.table[i, j] == 16)
                    {
                        dgvGame.Rows[i].Cells[j].Value = "";
                        dgvGame.Rows[i].Cells[j].Style.BackColor = Color.WhiteSmoke;
                    }
                    else
                    {
                        dgvGame.Rows[i].Cells[j].Style.BackColor = Color.FromArgb(234, 230, 202);
                        dgvGame.Rows[i].Cells[j].Style.Alignment = DataGridViewContentAlignment.MiddleCenter;
                        dgvGame.Rows[i].Cells[j].Style.Font = new Font("Arial", 20);
                        dgvGame.Rows[i].Cells[j].Value = sp.table[i, j].ToString();
                    }
                }
        }

        private void spGame_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            sp.ChangeLock(e.RowIndex, e.ColumnIndex);
            ShowGame();
            if (sp.IsFinished())
            {
                timer.Stop();
                MessageBox.Show(string.Format("Win!\nThe number of clicks : {0:D}\nTime : {1:mm:ss}", sp.count, time));
                dgvGame.Enabled = false;
            }
        }

        private void Start()
        {
            dgvGame.Enabled = true;
            time = new DateTime(0, 0);
            timer.Start();
            ShowGame();
        }

        private void repeatThisGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sp.RepeatGame();
            Start();
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            repeatThisGameToolStripMenuItem.Enabled = true;
            sp.NewGame();
            Start();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            time = time.AddSeconds(1);
            lb1.Text = string.Format("Time : {0:mm:ss}", time);
        }

        private void spGame_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Down || e.KeyCode == Keys.Up
                || e.KeyCode == Keys.Left || e.KeyCode == Keys.Right || e.KeyCode == Keys.Tab)
                e.SuppressKeyPress = true;
        }

        private void spGame_SelectionChanged(object sender, EventArgs e)
        {
            (sender as DataGridView).ClearSelection();
        }
    }
}