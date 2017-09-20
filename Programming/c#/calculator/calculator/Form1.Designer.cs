namespace calculator
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
            this.sum = new System.Windows.Forms.Button();
            this.sub = new System.Windows.Forms.Button();
            this.div = new System.Windows.Forms.Button();
            this.mult = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbN1 = new System.Windows.Forms.TextBox();
            this.tbN2 = new System.Windows.Forms.TextBox();
            this.tbRez = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.err1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.err1)).BeginInit();
            this.SuspendLayout();
            // 
            // sum
            // 
            this.sum.Location = new System.Drawing.Point(59, 131);
            this.sum.Name = "sum";
            this.sum.Size = new System.Drawing.Size(75, 23);
            this.sum.TabIndex = 0;
            this.sum.Text = "+";
            this.sum.UseVisualStyleBackColor = true;
            this.sum.Click += new System.EventHandler(this.sum_Click);
            // 
            // sub
            // 
            this.sub.Location = new System.Drawing.Point(150, 131);
            this.sub.Name = "sub";
            this.sub.Size = new System.Drawing.Size(75, 23);
            this.sub.TabIndex = 1;
            this.sub.Text = "-";
            this.sub.UseVisualStyleBackColor = true;
            this.sub.Click += new System.EventHandler(this.sub_Click);
            // 
            // div
            // 
            this.div.Location = new System.Drawing.Point(59, 169);
            this.div.Name = "div";
            this.div.Size = new System.Drawing.Size(75, 23);
            this.div.TabIndex = 2;
            this.div.Text = "/";
            this.div.UseVisualStyleBackColor = true;
            this.div.Click += new System.EventHandler(this.div_Click);
            // 
            // mult
            // 
            this.mult.Location = new System.Drawing.Point(150, 169);
            this.mult.Name = "mult";
            this.mult.Size = new System.Drawing.Size(75, 23);
            this.mult.TabIndex = 3;
            this.mult.Text = "*";
            this.mult.UseVisualStyleBackColor = true;
            this.mult.Click += new System.EventHandler(this.mult_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Первое число";
            // 
            // tbN1
            // 
            this.tbN1.Location = new System.Drawing.Point(34, 45);
            this.tbN1.Name = "tbN1";
            this.tbN1.Size = new System.Drawing.Size(100, 20);
            this.tbN1.TabIndex = 5;
            this.tbN1.Text = "0";
            this.tbN1.Validating += new System.ComponentModel.CancelEventHandler(this.tbN1_Validating);
            this.tbN1.Validated += new System.EventHandler(this.tbN1_Validated);
            // 
            // tbN2
            // 
            this.tbN2.Location = new System.Drawing.Point(150, 45);
            this.tbN2.Name = "tbN2";
            this.tbN2.Size = new System.Drawing.Size(100, 20);
            this.tbN2.TabIndex = 6;
            this.tbN2.Text = "0";
            this.tbN2.Validating += new System.ComponentModel.CancelEventHandler(this.tbN2_Validating);
            this.tbN2.Validated += new System.EventHandler(this.tbN2_Validated);
            // 
            // tbRez
            // 
            this.tbRez.Location = new System.Drawing.Point(95, 92);
            this.tbRez.Name = "tbRez";
            this.tbRez.ReadOnly = true;
            this.tbRez.Size = new System.Drawing.Size(100, 20);
            this.tbRez.TabIndex = 7;
            this.tbRez.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(147, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Второе число";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(112, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Результат";
            // 
            // err1
            // 
            this.err1.ContainerControl = this;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbRez);
            this.Controls.Add(this.tbN2);
            this.Controls.Add(this.tbN1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.mult);
            this.Controls.Add(this.div);
            this.Controls.Add(this.sub);
            this.Controls.Add(this.sum);
            this.MaximumSize = new System.Drawing.Size(300, 300);
            this.MinimumSize = new System.Drawing.Size(300, 300);
            this.Name = "Form1";
            this.Text = "Калькулятор";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.err1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button sum;
        private System.Windows.Forms.Button sub;
        private System.Windows.Forms.Button div;
        private System.Windows.Forms.Button mult;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbN1;
        private System.Windows.Forms.TextBox tbN2;
        private System.Windows.Forms.TextBox tbRez;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ErrorProvider err1;
    }
}

