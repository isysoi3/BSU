namespace fifteen
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.dgvGame = new System.Windows.Forms.DataGridView();
            this.menu = new System.Windows.Forms.MenuStrip();
            this.newGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.repeatThisGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.lb1 = new System.Windows.Forms.Label();
            this.lb2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvGame)).BeginInit();
            this.menu.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvGame
            // 
            this.dgvGame.AllowUserToAddRows = false;
            this.dgvGame.AllowUserToDeleteRows = false;
            this.dgvGame.AllowUserToResizeColumns = false;
            this.dgvGame.AllowUserToResizeRows = false;
            this.dgvGame.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvGame.Enabled = false;
            this.dgvGame.Location = new System.Drawing.Point(0, 40);
            this.dgvGame.MultiSelect = false;
            this.dgvGame.Name = "dgvGame";
            this.dgvGame.ReadOnly = true;
            this.dgvGame.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.dgvGame.Size = new System.Drawing.Size(284, 259);
            this.dgvGame.StandardTab = true;
            this.dgvGame.TabIndex = 0;
            this.dgvGame.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.spGame_CellClick);
            this.dgvGame.SelectionChanged += new System.EventHandler(this.spGame_SelectionChanged);
            this.dgvGame.KeyDown += new System.Windows.Forms.KeyEventHandler(this.spGame_KeyDown);
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newGameToolStripMenuItem,
            this.repeatThisGameToolStripMenuItem});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(241, 24);
            this.menu.TabIndex = 1;
            this.menu.Text = "menuStrip1";
            // 
            // newGameToolStripMenuItem
            // 
            this.newGameToolStripMenuItem.Name = "newGameToolStripMenuItem";
            this.newGameToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.newGameToolStripMenuItem.Text = "New game";
            this.newGameToolStripMenuItem.Click += new System.EventHandler(this.newGameToolStripMenuItem_Click);
            // 
            // repeatThisGameToolStripMenuItem
            // 
            this.repeatThisGameToolStripMenuItem.Enabled = false;
            this.repeatThisGameToolStripMenuItem.Name = "repeatThisGameToolStripMenuItem";
            this.repeatThisGameToolStripMenuItem.Size = new System.Drawing.Size(110, 20);
            this.repeatThisGameToolStripMenuItem.Text = "Repeat this game";
            this.repeatThisGameToolStripMenuItem.Click += new System.EventHandler(this.repeatThisGameToolStripMenuItem_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // lb1
            // 
            this.lb1.AutoSize = true;
            this.lb1.Location = new System.Drawing.Point(12, 24);
            this.lb1.Name = "lb1";
            this.lb1.Size = new System.Drawing.Size(66, 13);
            this.lb1.TabIndex = 2;
            this.lb1.Text = "Time : 00:00";
            // 
            // lb2
            // 
            this.lb2.AutoSize = true;
            this.lb2.Location = new System.Drawing.Point(147, 24);
            this.lb2.Name = "lb2";
            this.lb2.Size = new System.Drawing.Size(50, 13);
            this.lb2.TabIndex = 3;
            this.lb2.Text = "Clicks : 0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(241, 282);
            this.Controls.Add(this.lb2);
            this.Controls.Add(this.lb1);
            this.Controls.Add(this.dgvGame);
            this.Controls.Add(this.menu);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MainMenuStrip = this.menu;
            this.MaximumSize = new System.Drawing.Size(257, 320);
            this.MinimumSize = new System.Drawing.Size(257, 320);
            this.Name = "Form1";
            this.Text = "Fifteen ";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvGame)).EndInit();
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvGame;
        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.ToolStripMenuItem newGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem repeatThisGameToolStripMenuItem;
        private System.Windows.Forms.Label lb1;
        private System.Windows.Forms.Label lb2;
    }
}

