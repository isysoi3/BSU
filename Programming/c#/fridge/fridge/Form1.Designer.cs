namespace fridge
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
            this.dgvGame = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.dgvGame)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvGame
            // 
            this.dgvGame.AllowUserToAddRows = false;
            this.dgvGame.AllowUserToDeleteRows = false;
            this.dgvGame.AllowUserToResizeColumns = false;
            this.dgvGame.AllowUserToResizeRows = false;
            this.dgvGame.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvGame.ColumnHeadersVisible = false;
            this.dgvGame.Location = new System.Drawing.Point(1, 2);
            this.dgvGame.Name = "dgvGame";
            this.dgvGame.ReadOnly = true;
            this.dgvGame.RowHeadersVisible = false;
            this.dgvGame.Size = new System.Drawing.Size(283, 259);
            this.dgvGame.TabIndex = 0;
            this.dgvGame.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvGame_CellClick);
            this.dgvGame.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvGame_CellContentClick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.dgvGame);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvGame)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvGame;
    }
}

