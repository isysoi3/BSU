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
            this.components = new System.ComponentModel.Container();
            this.btS = new System.Windows.Forms.Button();
            this.btF = new System.Windows.Forms.Button();
            this.lbT = new System.Windows.Forms.Label();
            this.textBoxTime = new System.Windows.Forms.TextBox();
            this.lb = new System.Windows.Forms.Label();
            this.error = new System.Windows.Forms.ErrorProvider(this.components);
            output = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.error)).BeginInit();
            this.SuspendLayout();
            // 
            // btS
            // 
            this.btS.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btS.Location = new System.Drawing.Point(433, 65);
            this.btS.Name = "btS";
            this.btS.Size = new System.Drawing.Size(90, 40);
            this.btS.TabIndex = 0;
            this.btS.Text = "Start";
            this.btS.UseVisualStyleBackColor = true;
            this.btS.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // btF
            // 
            this.btF.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btF.Location = new System.Drawing.Point(433, 150);
            this.btF.Name = "btF";
            this.btF.Size = new System.Drawing.Size(90, 40);
            this.btF.TabIndex = 1;
            this.btF.Text = "Finish";
            this.btF.UseVisualStyleBackColor = true;
            this.btF.Click += new System.EventHandler(this.buttonFinish_Click);
            // 
            // lbT
            // 
            this.lbT.AutoSize = true;
            this.lbT.Location = new System.Drawing.Point(430, 9);
            this.lbT.Name = "lbT";
            this.lbT.Size = new System.Drawing.Size(96, 13);
            this.lbT.TabIndex = 2;
            this.lbT.Text = "Pause Time(in ms):";
            // 
            // textBoxTime
            // 
            this.textBoxTime.Location = new System.Drawing.Point(433, 25);
            this.textBoxTime.Name = "textBoxTime";
            this.textBoxTime.Size = new System.Drawing.Size(89, 20);
            this.textBoxTime.TabIndex = 3;
            this.textBoxTime.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxTime_Validating);
            this.textBoxTime.Validated += new System.EventHandler(this.textBoxTime_Validated);
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
            // error
            // 
            this.error.ContainerControl = this;
            // 
            // output
            // 
            output.BackColor = System.Drawing.Color.Gainsboro;
            output.Location = new System.Drawing.Point(0, -1);
            output.Name = "output";
            output.ReadOnly = true;
            output.Size = new System.Drawing.Size(424, 220);
            output.TabIndex = 5;
            output.Text = "";
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(551, 220);
            this.Controls.Add(output);
            this.Controls.Add(this.lb);
            this.Controls.Add(this.textBoxTime);
            this.Controls.Add(this.lbT);
            this.Controls.Add(this.btF);
            this.Controls.Add(this.btS);
            this.Name = "Form";
            this.Text = "Events";
            this.Deactivate += new System.EventHandler(this.Form_Deactivate);
            ((System.ComponentModel.ISupportInitialize)(this.error)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btS;
        private System.Windows.Forms.Button btF;
        private System.Windows.Forms.Label lbT;
        private System.Windows.Forms.TextBox textBoxTime;
        private System.Windows.Forms.ErrorProvider error;
        public System.Windows.Forms.Label lb;
        public static System.Windows.Forms.RichTextBox output;
    }
}

