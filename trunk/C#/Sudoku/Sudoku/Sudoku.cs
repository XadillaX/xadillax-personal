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
    public partial class Sudoku : Form
    {
        private SButton[,] Nums = new SButton[9, 9];
        private int[,] mat = new int[9, 9];
        private bool gOK;
        private Random ran;

        /**
         * @brief 窗体画线函数
         */
        public void DrawLine(object sender, EventArgs e)
        {
            //this.BackColor = Color.Black;
        }

        /**
         * @brief 构造函数
         */
        public Sudoku()
        {
            InitializeComponent();
            ran = new Random(GetSeed());

            this.Paint += DrawLine;

            /** 开始按钮 */
            /*StartBtn = new Button();
            StartBtn.Size = new Size(80, 40);
            StartBtn.Left = (this.Width - 80) / 2;
            StartBtn.Top = 5;
            StartBtn.Text = "开始";
            StartBtn.BackColor = Color.White;
            StartBtn.Click += StartGame;
            this.Controls.Add(StartBtn);*/

            /** 数独按钮 */
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    Nums[i, j] = new SButton(i, j, mat);

                    //Nums[i, j].BackColor = Color.LightSeaGreen;
                    Nums[i, j].Top = (i + 1) * 50;
                    Nums[i, j].Left = (j + 1) * 50;
                    Nums[i, j].Size = new Size(50, 50);
                    Nums[i, j].Name = "Row" + i.ToString() + j.ToString();
                    
                    /** 按下事件增加PendWin函数 */
                    Nums[i, j].Click += PendWin;
                    Nums[i, j].MouseWheel += PendWin;

                    this.Controls.Add(Nums[i, j]);

                    /** 初始化矩阵 */
                    mat[i, j] = -1;
                }
            }
        }

        /**
         * @brief 数独按钮按下事件
         */
        public void PendWin(object sender, EventArgs e)
        {
            if (_PendWin())
            {
                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        Nums[i, j].Font = new Font("微软雅黑", 18);
                        Nums[i, j].Enabled = false;
                    }
                }

                alert("恭喜，你赢啦！");
            }
        }

        /**
         * @brief 判断赢
         */
        private bool _PendWin()
        {
            /** 九宫 */
            bool[] vis = new bool[9];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 9; k++) vis[k] = false;
                    for (int k = 0; k < 3; k++)
                    {
                        for (int l = 0; l < 3; l++)
                        {
                            if (mat[i * 3 + k, j * 3 + l] <= 0) return false;
                            if (vis[mat[i * 3 + k, j * 3 + l] - 1]) return false;
                            vis[mat[i * 3 + k, j * 3 + l] - 1] = true;
                        }
                    }
                }
            }

            /** 行列 */
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++) vis[j] = false;
                for (int j = 0; j < 9; j++)
                {
                    if (vis[mat[i, j] - 1]) return false;
                    vis[mat[i, j] - 1] = true;
                }
            }

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++) vis[j] = false;
                for (int j = 0; j < 9; j++)
                {
                    if (vis[mat[j, i] - 1]) return false;
                    vis[mat[j, i] - 1] = true;
                }
            }

            return true;
        }

        public void FindSolution(object sender, EventArgs e)
        {
            /** 重设矩阵 */
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    mat[i, j] = (Nums[i, j].Enabled) ? 0 : int.Parse(Nums[i, j].Text);
                }
            }

            gOK = false;
            _DFS(0, 0);

            /** 设置按钮 */
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (Nums[i, j].Enabled)
                    {
                        Nums[i, j].Text = mat[i, j].ToString();
                    }
                }
            }
        }

        /**
         * @brief 初始化游戏
         */
        public void StartGame(object sender, EventArgs e)
        {
            //Random ran = new Random(GetSeed());
            bool[] flag = new bool[9];

            /** 随机生成某种全状态 */
            Generator();

            /** 生成数独矩阵 */
            int toDelNum = ran.Next(40, 61);                    ///< 随机挖掉40到60个格子
            //toDelNum = 1;                                       ///< 挖掉1个格子（测试用）
            bool[] dflag = new bool[81];
            for (int i = 0; i < 81; i++) dflag[i] = false;
            for (int i = 0; i < toDelNum; i++)
            {
                int tmp = ran.Next(0, 81);
                while (dflag[tmp]) tmp = ran.Next(0, 81);

                dflag[tmp] = true;
                mat[tmp / 9, tmp % 9] = 0;
            }

            //alert(MatToString(mat));
            /** 对按钮操作 */
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    Nums[i, j].SetEffect(mat[i, j]);
                }
            }
        }

        /**
         * @brief 按钮移动
         */
        private void SButtonMove(object sender, EventArgs e)
        {
            //alert(sender.ToString());
        }

        /**
         * @brief 得到可能
         * 生成时，对于位置(y, x)得到所有可能性
         */
        private int[] GetPos(int y, int x)
        {
            bool[] flag = new bool[9];
            for (int i = 0; i < 9; i++) flag[i] = false;

            /** 九宫格 */
            int bx = x / 3;
            int by = y / 3;
            for(int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (mat[by * 3 + i, bx * 3 + j] != 0)
                        flag[mat[by * 3 + i, bx * 3 + j] - 1] = true;

            /** 行列 */
            for (int i = 0; i < 9; i++)
            {
                if (mat[y, i] != 0) flag[mat[y, i] - 1] = true;
                if (mat[i, x] != 0) flag[mat[i, x] - 1] = true;
            }

            int[] r = new int[9];
            for (int i = 0; i < 9; i++) r[i] = 0;
            
            int count = 0;
            for (int i = 0; i < 9; i++)
            {
                if (!flag[i]) r[count++] = i + 1;
            }

            return r;
        }

        /**
         * @brief 生成数独深搜
         */
        private void _DFS(int y, int x)
        {
            if (y >= 9)
            {
                gOK = true;
                return;
            }

            bool[] flag = new bool[9];
            for (int i = 0; i < 9; i++) flag[i] = false;

            if (mat[y, x] != 0 && mat[y, x] != -1)
            {
                int newx = x + 1;
                int newy = y;
                if (newx >= 9)
                {
                    newx = 0;
                    newy++;
                }
                _DFS(newy, newx);
                return;
            }

            int[] pos = GetPos(y, x);
            int count = 9;
            for (int i = 0; i < 9; i++)
            {
                if (pos[i] == 0)
                {
                    count = i;
                    break;
                }
            }

            //Random ran = new Random(GetSeed());
            for (int i = 0; i < count; i++)
            {
                int index = ran.Next(0, count);
                while (flag[index]) index = ran.Next(0, count);
                flag[index] = true;

                mat[y, x] = pos[index];
                int newx = x + 1;
                int newy = y;
                if (newx >= 9)
                {
                    newx = 0;
                    newy++;
                }
                _DFS(newy, newx);
                if (gOK) return;
                mat[y, x] = 0;
            }
        }

        /**
         * @brief 生成数独
         */
        public void Generator()
        {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) mat[i, j] = 0;
            
            gOK = false;
            _DFS(0, 0);
        }

        /**
         * @brief 弹窗
         */
        public void alert(string a)
        {
            MessageBox.Show(a);
        }

        /**
         * @brief 测试用
         */
        public string MatToString(int[,] arr)
        {
            string rst = "";
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++) rst += (arr[i, j].ToString() + ", ");
                rst += "\n";
            }

            return rst;
        }

        public int GetSeed()
        {
            //alert(unchecked((int)DateTime.Now.Ticks).ToString());
            return unchecked((int)DateTime.Now.Ticks);
        }

        private void Exit_XToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Clear_CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gOK = false;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    mat[i, j] = -1;
                    Nums[i, j].Enabled = true;
                    Nums[i, j].Text = "";
                }
            }
        }
    }
}
