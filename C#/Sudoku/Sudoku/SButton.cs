using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sudoku
{
    class SButton : Button
    {
        private int[,] mat;
        public int x;
        public int y;
        public SButton(int _y, int _x, int[,] arr)
        {
            /** 增加事件 */
            this.Click += On_Click;
            this.MouseWheel += RollNum;
            this.MouseMove += Hover;
            this.KeyDown += m_KeyDown;

            mat = arr;
            x = _x;
            y = _y;
        }

        public void m_KeyDown(object sender, KeyEventArgs e)
        {
            //alert(e.KeyCode.ToString());
        }

        public void Hover(object sender, EventArgs e)
        {
            this.Focus();
        }

        public void RollNum(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                On_Click(sender, e);
            }
            else
            {
                for (int i = 0; i < 8; i++) On_Click(sender, e);
            }
        }

        /**
         * @brief 类本身鼠标按下事件
         */
        public void On_Click(object sender, EventArgs e)
        {
            if (mat[y, x] < 0) return;

            mat[y, x]++;
            if (mat[y, x] > 9) mat[y, x] = 1;

            this.Text = mat[y, x].ToString();
        }

        public void SetEffect(int num)
        {
            if (num != 0)
            {
                this.Font = new Font("微软雅黑", 18);
                this.Text = num.ToString();
            }
            else
            {
                this.Font = new Font("微软雅黑", 18);
                this.Text = "";
            }

            this.Enabled = (num == 0) ? true : false;
        }

        public void alert(string a)
        {
            MessageBox.Show(a);
        }
    }
}
