namespace Calc
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
            this.sum = new System.Windows.Forms.Button();
            this.difference = new System.Windows.Forms.Button();
            this.division = new System.Windows.Forms.Button();
            this.multiplication = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbN1 = new System.Windows.Forms.TextBox();
            this.tbN2 = new System.Windows.Forms.TextBox();
            this.tbN3 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // sum
            // 
            this.sum.Location = new System.Drawing.Point(69, 169);
            this.sum.Name = "sum";
            this.sum.Size = new System.Drawing.Size(75, 23);
            this.sum.TabIndex = 0;
            this.sum.Text = "+";
            this.sum.UseVisualStyleBackColor = true;
            this.sum.Click += new System.EventHandler(this.button1_Click);
            // 
            // difference
            // 
            this.difference.Location = new System.Drawing.Point(165, 169);
            this.difference.Name = "difference";
            this.difference.Size = new System.Drawing.Size(75, 23);
            this.difference.TabIndex = 1;
            this.difference.Text = "-";
            this.difference.UseVisualStyleBackColor = true;
            this.difference.Click += new System.EventHandler(this.button2_Click);
            // 
            // division
            // 
            this.division.Location = new System.Drawing.Point(69, 208);
            this.division.Name = "division";
            this.division.Size = new System.Drawing.Size(75, 23);
            this.division.TabIndex = 2;
            this.division.Text = "/";
            this.division.UseVisualStyleBackColor = true;
            this.division.Click += new System.EventHandler(this.button3_Click);
            // 
            // multiplication
            // 
            this.multiplication.Location = new System.Drawing.Point(165, 208);
            this.multiplication.Name = "multiplication";
            this.multiplication.Size = new System.Drawing.Size(75, 23);
            this.multiplication.TabIndex = 3;
            this.multiplication.Text = "*";
            this.multiplication.UseVisualStyleBackColor = true;
            this.multiplication.Click += new System.EventHandler(this.button4_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(41, 63);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Первое число";
            // 
            // tbN1
            // 
            this.tbN1.CausesValidation = false;
            this.tbN1.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.tbN1.Location = new System.Drawing.Point(44, 79);
            this.tbN1.Name = "tbN1";
            this.tbN1.Size = new System.Drawing.Size(100, 20);
            this.tbN1.TabIndex = 5;
            this.tbN1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            this.tbN1.Validating += new System.ComponentModel.CancelEventHandler(this.tbN1_Validating);
            // 
            // tbN2
            // 
            this.tbN2.Location = new System.Drawing.Point(165, 79);
            this.tbN2.Name = "tbN2";
            this.tbN2.Size = new System.Drawing.Size(100, 20);
            this.tbN2.TabIndex = 6;
            this.tbN2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            this.tbN2.Validating += new System.ComponentModel.CancelEventHandler(this.tbN2_Validating);
            // 
            // tbN3
            // 
            this.tbN3.ForeColor = System.Drawing.Color.YellowGreen;
            this.tbN3.Location = new System.Drawing.Point(102, 124);
            this.tbN3.Name = "tbN3";
            this.tbN3.ReadOnly = true;
            this.tbN3.Size = new System.Drawing.Size(100, 20);
            this.tbN3.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(165, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Второе число";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(102, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Результат";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(326, 296);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbN3);
            this.Controls.Add(this.tbN2);
            this.Controls.Add(this.tbN1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.multiplication);
            this.Controls.Add(this.division);
            this.Controls.Add(this.difference);
            this.Controls.Add(this.sum);
            this.Name = "Form1";
            this.Text = "Калькулятор";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button sum;
        private System.Windows.Forms.Button difference;
        private System.Windows.Forms.Button division;
        private System.Windows.Forms.Button multiplication;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbN1;
        private System.Windows.Forms.TextBox tbN2;
        private System.Windows.Forms.TextBox tbN3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}

