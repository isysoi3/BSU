namespace events
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
            this.btS = new System.Windows.Forms.Button();
            this.btStopShoot = new System.Windows.Forms.Button();
            this.lbT = new System.Windows.Forms.Label();
            this.textBoxTime = new System.Windows.Forms.TextBox();
            this.lb = new System.Windows.Forms.Label();
            this.Target = new System.Windows.Forms.Panel();
            this.lbY = new System.Windows.Forms.Label();
            this.lbX = new System.Windows.Forms.Label();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.tbR = new System.Windows.Forms.TextBox();
            this.lbR = new System.Windows.Forms.Label();
            this.lbTime = new System.Windows.Forms.Label();
            this.textBoxTimeBetweenShoots = new System.Windows.Forms.TextBox();
            this.tbA = new System.Windows.Forms.TextBox();
            this.lbA = new System.Windows.Forms.Label();
            this.tbB = new System.Windows.Forms.TextBox();
            this.lbB = new System.Windows.Forms.Label();
            this.btStopClac = new System.Windows.Forms.Button();
            this.output = new System.Windows.Forms.TextBox();
            this.textBoxGoodShoots = new System.Windows.Forms.TextBox();
            this.textBoxMisses = new System.Windows.Forms.TextBox();
            this.lbHits = new System.Windows.Forms.Label();
            this.lbShots = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btS
            // 
            this.btS.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btS.Location = new System.Drawing.Point(381, 464);
            this.btS.Name = "btS";
            this.btS.Size = new System.Drawing.Size(90, 40);
            this.btS.TabIndex = 0;
            this.btS.Text = "Start";
            this.btS.UseVisualStyleBackColor = true;
            this.btS.Click += new System.EventHandler(this.btS_Click);
            // 
            // btStopShoot
            // 
            this.btStopShoot.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold);
            this.btStopShoot.Location = new System.Drawing.Point(595, 464);
            this.btStopShoot.Name = "btStopShoot";
            this.btStopShoot.Size = new System.Drawing.Size(90, 40);
            this.btStopShoot.TabIndex = 1;
            this.btStopShoot.Text = "Stop shooting";
            this.btStopShoot.UseVisualStyleBackColor = true;
            this.btStopShoot.Click += new System.EventHandler(this.btStopShoot_Click);
            // 
            // lbT
            // 
            this.lbT.AutoSize = true;
            this.lbT.Location = new System.Drawing.Point(12, 9);
            this.lbT.Name = "lbT";
            this.lbT.Size = new System.Drawing.Size(72, 13);
            this.lbT.TabIndex = 2;
            this.lbT.Text = "Частота (мс)";
            // 
            // textBoxTime
            // 
            this.textBoxTime.Location = new System.Drawing.Point(16, 25);
            this.textBoxTime.Name = "textBoxTime";
            this.textBoxTime.Size = new System.Drawing.Size(89, 20);
            this.textBoxTime.TabIndex = 3;
            this.textBoxTime.Text = "100";
            // 
            // lb
            // 
            this.lb.AutoSize = true;
            this.lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 12.25F);
            this.lb.Location = new System.Drawing.Point(34, 46);
            this.lb.Name = "lb";
            this.lb.Size = new System.Drawing.Size(0, 20);
            this.lb.TabIndex = 4;
            // 
            // Target
            // 
            this.Target.Location = new System.Drawing.Point(453, 51);
            this.Target.Name = "Target";
            this.Target.Size = new System.Drawing.Size(400, 400);
            this.Target.TabIndex = 6;
            // 
            // lbY
            // 
            this.lbY.AutoSize = true;
            this.lbY.Location = new System.Drawing.Point(648, 9);
            this.lbY.Name = "lbY";
            this.lbY.Size = new System.Drawing.Size(37, 13);
            this.lbY.TabIndex = 20;
            this.lbY.Text = "Ось Y";
            // 
            // lbX
            // 
            this.lbX.AutoSize = true;
            this.lbX.Location = new System.Drawing.Point(597, 9);
            this.lbX.Name = "lbX";
            this.lbX.Size = new System.Drawing.Size(37, 13);
            this.lbX.TabIndex = 19;
            this.lbX.Text = "Ось X";
            // 
            // textBoxY
            // 
            this.textBoxY.Location = new System.Drawing.Point(648, 25);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.Size = new System.Drawing.Size(37, 20);
            this.textBoxY.TabIndex = 18;
            this.textBoxY.Text = "150";
            this.textBoxY.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBoxX
            // 
            this.textBoxX.Location = new System.Drawing.Point(597, 25);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.Size = new System.Drawing.Size(45, 20);
            this.textBoxX.TabIndex = 17;
            this.textBoxX.Text = "150";
            this.textBoxX.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tbR
            // 
            this.tbR.Location = new System.Drawing.Point(450, 25);
            this.tbR.Name = "tbR";
            this.tbR.Size = new System.Drawing.Size(43, 20);
            this.tbR.TabIndex = 16;
            this.tbR.Text = "90";
            this.tbR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbR
            // 
            this.lbR.AutoSize = true;
            this.lbR.Location = new System.Drawing.Point(450, 9);
            this.lbR.Name = "lbR";
            this.lbR.Size = new System.Drawing.Size(21, 13);
            this.lbR.TabIndex = 15;
            this.lbR.Text = "R :";
            // 
            // lbTime
            // 
            this.lbTime.AutoSize = true;
            this.lbTime.Location = new System.Drawing.Point(702, 9);
            this.lbTime.Name = "lbTime";
            this.lbTime.Size = new System.Drawing.Size(130, 13);
            this.lbTime.TabIndex = 28;
            this.lbTime.Text = "Частота выстрелов (мс)";
            // 
            // textBoxTimeBetweenShoots
            // 
            this.textBoxTimeBetweenShoots.Location = new System.Drawing.Point(705, 25);
            this.textBoxTimeBetweenShoots.Name = "textBoxTimeBetweenShoots";
            this.textBoxTimeBetweenShoots.Size = new System.Drawing.Size(69, 20);
            this.textBoxTimeBetweenShoots.TabIndex = 27;
            this.textBoxTimeBetweenShoots.Text = "100";
            this.textBoxTimeBetweenShoots.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tbA
            // 
            this.tbA.Location = new System.Drawing.Point(499, 25);
            this.tbA.Name = "tbA";
            this.tbA.Size = new System.Drawing.Size(43, 20);
            this.tbA.TabIndex = 30;
            this.tbA.Text = "120";
            this.tbA.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbA
            // 
            this.lbA.AutoSize = true;
            this.lbA.Location = new System.Drawing.Point(499, 9);
            this.lbA.Name = "lbA";
            this.lbA.Size = new System.Drawing.Size(19, 13);
            this.lbA.TabIndex = 29;
            this.lbA.Text = "a :";
            // 
            // tbB
            // 
            this.tbB.Location = new System.Drawing.Point(548, 25);
            this.tbB.Name = "tbB";
            this.tbB.Size = new System.Drawing.Size(43, 20);
            this.tbB.TabIndex = 32;
            this.tbB.Text = "70";
            this.tbB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbB
            // 
            this.lbB.AutoSize = true;
            this.lbB.Location = new System.Drawing.Point(548, 9);
            this.lbB.Name = "lbB";
            this.lbB.Size = new System.Drawing.Size(19, 13);
            this.lbB.TabIndex = 31;
            this.lbB.Text = "b :";
            // 
            // btStopClac
            // 
            this.btStopClac.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold);
            this.btStopClac.Location = new System.Drawing.Point(16, 467);
            this.btStopClac.Name = "btStopClac";
            this.btStopClac.Size = new System.Drawing.Size(90, 40);
            this.btStopClac.TabIndex = 33;
            this.btStopClac.Text = "Stop calculating";
            this.btStopClac.UseVisualStyleBackColor = true;
            this.btStopClac.Click += new System.EventHandler(this.btStopClac_Click);
            // 
            // output
            // 
            this.output.Location = new System.Drawing.Point(12, 51);
            this.output.Multiline = true;
            this.output.Name = "output";
            this.output.ReadOnly = true;
            this.output.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.output.Size = new System.Drawing.Size(400, 400);
            this.output.TabIndex = 34;
            // 
            // textBoxGoodShoots
            // 
            this.textBoxGoodShoots.Location = new System.Drawing.Point(807, 483);
            this.textBoxGoodShoots.Name = "textBoxGoodShoots";
            this.textBoxGoodShoots.ReadOnly = true;
            this.textBoxGoodShoots.Size = new System.Drawing.Size(46, 20);
            this.textBoxGoodShoots.TabIndex = 38;
            this.textBoxGoodShoots.Text = "0";
            // 
            // textBoxMisses
            // 
            this.textBoxMisses.Location = new System.Drawing.Point(807, 464);
            this.textBoxMisses.Name = "textBoxMisses";
            this.textBoxMisses.ReadOnly = true;
            this.textBoxMisses.Size = new System.Drawing.Size(46, 20);
            this.textBoxMisses.TabIndex = 37;
            this.textBoxMisses.Text = "0";
            // 
            // lbHits
            // 
            this.lbHits.AutoSize = true;
            this.lbHits.Location = new System.Drawing.Point(735, 486);
            this.lbHits.Name = "lbHits";
            this.lbHits.Size = new System.Drawing.Size(66, 13);
            this.lbHits.TabIndex = 36;
            this.lbHits.Text = "Попадания:";
            // 
            // lbShots
            // 
            this.lbShots.AutoSize = true;
            this.lbShots.Location = new System.Drawing.Point(735, 467);
            this.lbShots.Name = "lbShots";
            this.lbShots.Size = new System.Drawing.Size(55, 13);
            this.lbShots.TabIndex = 35;
            this.lbShots.Text = "Промахи:";
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(865, 520);
            this.Controls.Add(this.textBoxGoodShoots);
            this.Controls.Add(this.textBoxMisses);
            this.Controls.Add(this.lbHits);
            this.Controls.Add(this.lbShots);
            this.Controls.Add(this.output);
            this.Controls.Add(this.btStopClac);
            this.Controls.Add(this.tbB);
            this.Controls.Add(this.lbB);
            this.Controls.Add(this.tbA);
            this.Controls.Add(this.lbA);
            this.Controls.Add(this.lbTime);
            this.Controls.Add(this.textBoxTimeBetweenShoots);
            this.Controls.Add(this.lbY);
            this.Controls.Add(this.lbX);
            this.Controls.Add(this.textBoxY);
            this.Controls.Add(this.textBoxX);
            this.Controls.Add(this.tbR);
            this.Controls.Add(this.lbR);
            this.Controls.Add(this.Target);
            this.Controls.Add(this.lb);
            this.Controls.Add(this.textBoxTime);
            this.Controls.Add(this.lbT);
            this.Controls.Add(this.btStopShoot);
            this.Controls.Add(this.btS);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(881, 558);
            this.MinimumSize = new System.Drawing.Size(881, 558);
            this.Name = "Form";
            this.Text = "Events";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btS;
        private System.Windows.Forms.Button btStopShoot;
        private System.Windows.Forms.Label lbT;
        private System.Windows.Forms.TextBox textBoxTime;
        public System.Windows.Forms.Label lb;
        private System.Windows.Forms.Panel Target;
        private System.Windows.Forms.Label lbY;
        private System.Windows.Forms.Label lbX;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.TextBox tbR;
        private System.Windows.Forms.Label lbR;
        private System.Windows.Forms.TextBox tbB;
        private System.Windows.Forms.Label lbB;
        private System.Windows.Forms.TextBox tbA;
        private System.Windows.Forms.Label lbA;
        private System.Windows.Forms.Label lbTime;
        private System.Windows.Forms.TextBox textBoxTimeBetweenShoots;
        private System.Windows.Forms.Button btStopClac;
        private System.Windows.Forms.TextBox output;
        private System.Windows.Forms.TextBox textBoxGoodShoots;
        private System.Windows.Forms.TextBox textBoxMisses;
        private System.Windows.Forms.Label lbHits;
        private System.Windows.Forms.Label lbShots;
    }
}

