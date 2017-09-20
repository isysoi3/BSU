namespace shooting
{
    partial class Form
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
            this.tbR = new System.Windows.Forms.TextBox();
            this.tba = new System.Windows.Forms.TextBox();
            this.tbb = new System.Windows.Forms.TextBox();
            this.btSG = new System.Windows.Forms.Button();
            this.lba = new System.Windows.Forms.Label();
            this.lbb = new System.Windows.Forms.Label();
            this.lbR = new System.Windows.Forms.Label();
            this.btShot = new System.Windows.Forms.Button();
            this.tbX = new System.Windows.Forms.TextBox();
            this.tbY = new System.Windows.Forms.TextBox();
            this.lbX = new System.Windows.Forms.Label();
            this.lbY = new System.Windows.Forms.Label();
            this.lbHit = new System.Windows.Forms.Label();
            this.lbMiss = new System.Windows.Forms.Label();
            this.lbSoots = new System.Windows.Forms.Label();
            this.tbSoots = new System.Windows.Forms.TextBox();
            this.err1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.err1)).BeginInit();
            this.SuspendLayout();
            // 
            // tbR
            // 
            this.tbR.Location = new System.Drawing.Point(635, 121);
            this.tbR.Name = "tbR";
            this.tbR.Size = new System.Drawing.Size(33, 20);
            this.tbR.TabIndex = 2;
            this.tbR.TabStop = false;
            this.tbR.Validating += new System.ComponentModel.CancelEventHandler(this.tbR_Validating);
            this.tbR.Validated += new System.EventHandler(this.tbR_Validated);
            // 
            // tba
            // 
            this.tba.Location = new System.Drawing.Point(635, 39);
            this.tba.Name = "tba";
            this.tba.Size = new System.Drawing.Size(33, 20);
            this.tba.TabIndex = 0;
            this.tba.TabStop = false;
            this.tba.Validating += new System.ComponentModel.CancelEventHandler(this.tba_Validating);
            this.tba.Validated += new System.EventHandler(this.tba_Validated);
            // 
            // tbb
            // 
            this.tbb.Location = new System.Drawing.Point(635, 76);
            this.tbb.Name = "tbb";
            this.tbb.Size = new System.Drawing.Size(33, 20);
            this.tbb.TabIndex = 1;
            this.tbb.TabStop = false;
            this.tbb.Validating += new System.ComponentModel.CancelEventHandler(this.tbb_Validating);
            this.tbb.Validated += new System.EventHandler(this.tbb_Validated);
            // 
            // btSG
            // 
            this.btSG.Location = new System.Drawing.Point(601, 208);
            this.btSG.Name = "btSG";
            this.btSG.Size = new System.Drawing.Size(75, 23);
            this.btSG.TabIndex = 4;
            this.btSG.TabStop = false;
            this.btSG.Text = "Start Game";
            this.btSG.UseVisualStyleBackColor = true;
            this.btSG.Click += new System.EventHandler(this.btSG_Click);
            // 
            // lba
            // 
            this.lba.AutoSize = true;
            this.lba.BackColor = System.Drawing.SystemColors.Window;
            this.lba.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lba.Location = new System.Drawing.Point(600, 37);
            this.lba.Name = "lba";
            this.lba.Size = new System.Drawing.Size(29, 20);
            this.lba.TabIndex = 5;
            this.lba.Text = "a :";
            // 
            // lbb
            // 
            this.lbb.AutoSize = true;
            this.lbb.BackColor = System.Drawing.SystemColors.Window;
            this.lbb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbb.Location = new System.Drawing.Point(600, 76);
            this.lbb.Name = "lbb";
            this.lbb.Size = new System.Drawing.Size(29, 20);
            this.lbb.TabIndex = 6;
            this.lbb.Text = "b :";
            // 
            // lbR
            // 
            this.lbR.AutoSize = true;
            this.lbR.BackColor = System.Drawing.SystemColors.Window;
            this.lbR.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbR.Location = new System.Drawing.Point(597, 119);
            this.lbR.Name = "lbR";
            this.lbR.Size = new System.Drawing.Size(32, 20);
            this.lbR.TabIndex = 7;
            this.lbR.Text = "R :";
            // 
            // btShot
            // 
            this.btShot.Enabled = false;
            this.btShot.Location = new System.Drawing.Point(601, 332);
            this.btShot.Name = "btShot";
            this.btShot.Size = new System.Drawing.Size(75, 23);
            this.btShot.TabIndex = 8;
            this.btShot.TabStop = false;
            this.btShot.Text = "Shot";
            this.btShot.UseVisualStyleBackColor = true;
            this.btShot.Click += new System.EventHandler(this.btShot_Click);
            // 
            // tbX
            // 
            this.tbX.Location = new System.Drawing.Point(580, 289);
            this.tbX.Name = "tbX";
            this.tbX.Size = new System.Drawing.Size(37, 20);
            this.tbX.TabIndex = 9;
            this.tbX.TabStop = false;
            this.tbX.Validating += new System.ComponentModel.CancelEventHandler(this.tbX_Validating);
            this.tbX.Validated += new System.EventHandler(this.tbX_Validated);
            // 
            // tbY
            // 
            this.tbY.Location = new System.Drawing.Point(656, 289);
            this.tbY.Name = "tbY";
            this.tbY.Size = new System.Drawing.Size(37, 20);
            this.tbY.TabIndex = 10;
            this.tbY.TabStop = false;
            this.tbY.Validating += new System.ComponentModel.CancelEventHandler(this.tbY_Validating);
            this.tbY.Validated += new System.EventHandler(this.tbY_Validated);
            // 
            // lbX
            // 
            this.lbX.AutoSize = true;
            this.lbX.BackColor = System.Drawing.SystemColors.Window;
            this.lbX.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbX.Location = new System.Drawing.Point(591, 266);
            this.lbX.Name = "lbX";
            this.lbX.Size = new System.Drawing.Size(21, 20);
            this.lbX.TabIndex = 11;
            this.lbX.Text = "X";
            // 
            // lbY
            // 
            this.lbY.AutoSize = true;
            this.lbY.BackColor = System.Drawing.SystemColors.Window;
            this.lbY.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbY.Location = new System.Drawing.Point(662, 266);
            this.lbY.Name = "lbY";
            this.lbY.Size = new System.Drawing.Size(21, 20);
            this.lbY.TabIndex = 12;
            this.lbY.Text = "Y";
            // 
            // lbHit
            // 
            this.lbHit.AutoSize = true;
            this.lbHit.Location = new System.Drawing.Point(572, 397);
            this.lbHit.Name = "lbHit";
            this.lbHit.Size = new System.Drawing.Size(40, 13);
            this.lbHit.TabIndex = 13;
            this.lbHit.Text = "Hits : 0";
            // 
            // lbMiss
            // 
            this.lbMiss.AutoSize = true;
            this.lbMiss.BackColor = System.Drawing.SystemColors.Window;
            this.lbMiss.Location = new System.Drawing.Point(653, 397);
            this.lbMiss.Name = "lbMiss";
            this.lbMiss.Size = new System.Drawing.Size(43, 13);
            this.lbMiss.TabIndex = 14;
            this.lbMiss.Text = "Miss : 0";
            // 
            // lbSoots
            // 
            this.lbSoots.AutoSize = true;
            this.lbSoots.BackColor = System.Drawing.SystemColors.Window;
            this.lbSoots.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbSoots.Location = new System.Drawing.Point(563, 160);
            this.lbSoots.Name = "lbSoots";
            this.lbSoots.Size = new System.Drawing.Size(66, 20);
            this.lbSoots.TabIndex = 15;
            this.lbSoots.Text = "Shots :";
            // 
            // tbSoots
            // 
            this.tbSoots.Location = new System.Drawing.Point(635, 162);
            this.tbSoots.Name = "tbSoots";
            this.tbSoots.Size = new System.Drawing.Size(33, 20);
            this.tbSoots.TabIndex = 3;
            this.tbSoots.TabStop = false;
            this.tbSoots.Validating += new System.ComponentModel.CancelEventHandler(this.tbSoots_Validating);
            this.tbSoots.Validated += new System.EventHandler(this.tbSoots_Validated);
            // 
            // err1
            // 
            this.err1.ContainerControl = this;
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(734, 482);
            this.Controls.Add(this.tbSoots);
            this.Controls.Add(this.lbSoots);
            this.Controls.Add(this.lbMiss);
            this.Controls.Add(this.lbHit);
            this.Controls.Add(this.lbY);
            this.Controls.Add(this.lbX);
            this.Controls.Add(this.tbY);
            this.Controls.Add(this.tbX);
            this.Controls.Add(this.btShot);
            this.Controls.Add(this.lbR);
            this.Controls.Add(this.lbb);
            this.Controls.Add(this.lba);
            this.Controls.Add(this.btSG);
            this.Controls.Add(this.tbb);
            this.Controls.Add(this.tba);
            this.Controls.Add(this.tbR);
            this.DoubleBuffered = true;
            this.MaximumSize = new System.Drawing.Size(750, 520);
            this.MinimumSize = new System.Drawing.Size(750, 520);
            this.Name = "Form";
            this.Text = "Target";
            ((System.ComponentModel.ISupportInitialize)(this.err1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbR;
        private System.Windows.Forms.TextBox tba;
        private System.Windows.Forms.TextBox tbb;
        private System.Windows.Forms.Button btSG;
        private System.Windows.Forms.Label lba;
        private System.Windows.Forms.Label lbb;
        private System.Windows.Forms.Label lbR;
        private System.Windows.Forms.Button btShot;
        private System.Windows.Forms.TextBox tbX;
        private System.Windows.Forms.TextBox tbY;
        private System.Windows.Forms.Label lbX;
        private System.Windows.Forms.Label lbY;
        private System.Windows.Forms.Label lbHit;
        private System.Windows.Forms.Label lbMiss;
        private System.Windows.Forms.Label lbSoots;
        private System.Windows.Forms.TextBox tbSoots;
        private System.Windows.Forms.ErrorProvider err1;
    }
}

