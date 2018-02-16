namespace Flags
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
            this.menu = new System.Windows.Forms.MenuStrip();
            this.флагиToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.KNDRToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.UARToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menu.SuspendLayout();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.флагиToolStripMenuItem});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(284, 24);
            this.menu.TabIndex = 0;
            this.menu.Text = "menu";
            // 
            // флагиToolStripMenuItem
            // 
            this.флагиToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.KNDRToolStripMenuItem,
            this.UARToolStripMenuItem});
            this.флагиToolStripMenuItem.Name = "флагиToolStripMenuItem";
            this.флагиToolStripMenuItem.Size = new System.Drawing.Size(46, 20);
            this.флагиToolStripMenuItem.Text = "Флаг";
            // 
            // KNDRToolStripMenuItem
            // 
            this.KNDRToolStripMenuItem.Name = "KNDRToolStripMenuItem";
            this.KNDRToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.KNDRToolStripMenuItem.Text = "КНДР";
            this.KNDRToolStripMenuItem.Click += new System.EventHandler(this.KNDRToolStripMenuItem_Click);
            // 
            // UARToolStripMenuItem
            // 
            this.UARToolStripMenuItem.Name = "UARToolStripMenuItem";
            this.UARToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.UARToolStripMenuItem.Text = "ЮАР";
            this.UARToolStripMenuItem.Click += new System.EventHandler(this.UARToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.menu);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Flags";
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.ToolStripMenuItem флагиToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem KNDRToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem UARToolStripMenuItem;
    }
}

