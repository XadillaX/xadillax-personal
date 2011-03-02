namespace Sudoku
{
    partial class Sudoku
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Sudoku));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.查看VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新游戏NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.求解ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.查看VToolStripMenuItem});
            resources.ApplyResources(this.menuStrip1, "menuStrip1");
            this.menuStrip1.Name = "menuStrip1";
            // 
            // 查看VToolStripMenuItem
            // 
            this.查看VToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新游戏NToolStripMenuItem,
            this.求解ToolStripMenuItem,
            this.退出XToolStripMenuItem});
            this.查看VToolStripMenuItem.Name = "查看VToolStripMenuItem";
            resources.ApplyResources(this.查看VToolStripMenuItem, "查看VToolStripMenuItem");
            // 
            // 新游戏NToolStripMenuItem
            // 
            this.新游戏NToolStripMenuItem.Name = "新游戏NToolStripMenuItem";
            resources.ApplyResources(this.新游戏NToolStripMenuItem, "新游戏NToolStripMenuItem");
            this.新游戏NToolStripMenuItem.Click += new System.EventHandler(this.StartGame);
            // 
            // 求解ToolStripMenuItem
            // 
            this.求解ToolStripMenuItem.Name = "求解ToolStripMenuItem";
            resources.ApplyResources(this.求解ToolStripMenuItem, "求解ToolStripMenuItem");
            this.求解ToolStripMenuItem.Click += new System.EventHandler(this.FindSolution);
            // 
            // 退出XToolStripMenuItem
            // 
            this.退出XToolStripMenuItem.Name = "退出XToolStripMenuItem";
            resources.ApplyResources(this.退出XToolStripMenuItem, "退出XToolStripMenuItem");
            this.退出XToolStripMenuItem.Click += new System.EventHandler(this.Exit_XToolStripMenuItem_Click);
            // 
            // Sudoku
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Sudoku";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 查看VToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新游戏NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 求解ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出XToolStripMenuItem;
    }
}