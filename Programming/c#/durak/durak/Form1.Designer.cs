namespace durak
{
    partial class Fool
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
            this.lbQuestion = new System.Windows.Forms.Label();
            this.btYes = new System.Windows.Forms.Button();
            this.btNo = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbQuestion
            // 
            this.lbQuestion.AutoSize = true;
            this.lbQuestion.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lbQuestion.Location = new System.Drawing.Point(91, 47);
            this.lbQuestion.Name = "lbQuestion";
            this.lbQuestion.Size = new System.Drawing.Size(155, 31);
            this.lbQuestion.TabIndex = 4;
            this.lbQuestion.Text = "Ты дурак?";
            this.lbQuestion.MouseMove += new System.Windows.Forms.MouseEventHandler(this.lbQuestion_MouseMove);
            // 
            // btYes
            // 
            this.btYes.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btYes.Location = new System.Drawing.Point(45, 135);
            this.btYes.Name = "btYes";
            this.btYes.Size = new System.Drawing.Size(65, 27);
            this.btYes.TabIndex = 0;
            this.btYes.Text = "Да";
            this.btYes.UseVisualStyleBackColor = true;
            this.btYes.Click += new System.EventHandler(this.btYes_Click);
            this.btYes.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btYes_MouseMove);
            this.btYes.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.btYes_PreviewKeyDown);
            // 
            // btNo
            // 
            this.btNo.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btNo.Location = new System.Drawing.Point(226, 135);
            this.btNo.Name = "btNo";
            this.btNo.Size = new System.Drawing.Size(65, 27);
            this.btNo.TabIndex = 2;
            this.btNo.TabStop = false;
            this.btNo.Text = "Нет";
            this.btNo.UseVisualStyleBackColor = true;
            this.btNo.Click += new System.EventHandler(this.btNo_Click);
            this.btNo.MouseEnter += new System.EventHandler(this.btNo_MouseEnter);
            // 
            // Fool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 312);
            this.Controls.Add(this.btNo);
            this.Controls.Add(this.btYes);
            this.Controls.Add(this.lbQuestion);
            this.KeyPreview = true;
            this.MaximumSize = new System.Drawing.Size(350, 350);
            this.MinimumSize = new System.Drawing.Size(350, 350);
            this.Name = "Fool";
            this.Text = "Дурак";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Form_KeyPress);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form_MouseMove);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbQuestion;
        private System.Windows.Forms.Button btYes;
        private System.Windows.Forms.Button btNo;
    }
}

