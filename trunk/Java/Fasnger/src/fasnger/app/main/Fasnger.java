package fasnger.app.main;

import android.app.Activity;
import android.app.AlertDialog.Builder;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.widget.Button;
import android.view.View.OnClickListener;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.LineNumberReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.StreamTokenizer;
import java.nio.IntBuffer;
import java.util.Timer;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import java.util.TimerTask;
import android.os.Handler;
import android.os.Message;

enum rs{
	NOT_RUNNING,
	RUNNING,
	FINISHED
};

public class Fasnger extends Activity {
    private rs run_state = rs.NOT_RUNNING;						///< 运行状态
    private Window app_window = null;							///< 程序窗口
    private Button game_button = null;							///< 背景按钮
    public TextView time_view = null;							///< 状态文字
    private int hits = 0;										///< 点击数
    public Timer timer = new Timer();							///< 计时器
    public int tot_time = 30;									///< 总时间
    public int now_time = 0;									///< 当前时间
    private File data_path;										///< 路径
    private File data_file;										///< 文件
    private boolean can_open = true;							///< 文件是否能打开
    private int highest = 0;									///< 最高分
    private boolean pause = false;
    private int[] voice;
    MediaPlayer mPlayer = null;
    
    /**
     * @brief 按钮按下
     */
    private OnClickListener game_button_onClick = new OnClickListener() {
		@Override
    	public void onClick(View v) {
			if(run_state == rs.NOT_RUNNING)
			{
				StartGame();
				_PlayV();
			}
			else
			if(run_state == rs.RUNNING)
			{
				hits++;
				UpdateTextView();
				_PlayV();
			}
    	}
	};
	
	private void _PlayV() {
		if(null != mPlayer)
		{
			if(mPlayer.isPlaying()) return;
		}
		mPlayer = MediaPlayer.create(getApplicationContext(), voice[(int)(Math.random() * 13)]);
		
		mPlayer.setLooping(false);
		mPlayer.start();
	}
	
	/**
	 * @brief 更新状态文字
	 */
	private void UpdateTextView() {
		time_view.setText("状态 —— 倒计时：" + (tot_time - now_time) + "	点击：" + hits + "	最高分：" + highest);
	}
	
	/**
	 * @brief 计时句柄
	 */
	private Handler timer_handler;
	
	/**
	 * @brief 任务句柄
	 */
	private TimerTask tt;
	
	/**
	 * @brief 结束游戏
	 */
	private void FinishGame() {
		if(hits > highest)
		{
			if(!WriteData()) Alert("文件写入错误，新纪录将不能被写入。", "错误", false);
			highest = hits;
		}
		
		Alert("在30秒内点击 " + hits + " 次，历史最高 " + highest + " 次。", "Time up", true);
	}
	
	protected void Alert(String msg, String title, boolean btn) {
		Builder builder = new Builder(Fasnger.this);
		
		builder.setMessage(msg);
		builder.setTitle(title);
		
		if(btn)
		{
			android.content.DialogInterface.OnClickListener alert_ocl = new android.content.DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
					notStart();
				}
			};
			
			builder.setNegativeButton("确定", alert_ocl);
		}
		
		builder.create().show();
	}
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app_window = getWindow();
        
        /** 设置全屏 */
        setFullScreen();
        
        /** 载入Layout */
        setContentView(R.layout.main);
        
        /** 初始化组件 */
        initWidget();
        
        /** 读取数据 */
        ReadData();
        
        /** 载入声音 */
        LoadVoiceData();
        
        /** 初始化游戏 */
        notStart();
    }
    
    private void LoadVoiceData() {
    	voice = new int[14];
    	
    	voice[0] = R.raw.snd_01;
    	voice[1] = R.raw.snd_02;
    	voice[2] = R.raw.snd_03;
    	voice[3] = R.raw.snd_04;
    	voice[4] = R.raw.snd_05;
    	voice[5] = R.raw.snd_06;
    	voice[6] = R.raw.snd_07;
    	voice[7] = R.raw.snd_08;
    	voice[8] = R.raw.snd_09;
    	voice[9] = R.raw.snd_10;
    	voice[10] = R.raw.snd_11;
    	voice[11] = R.raw.snd_12;
    	voice[12] = R.raw.snd_13;
    }
    
    /**
     * @brief 开始游戏
     */
    public void StartGame() {
    	hits = 1;
    	now_time = 0;
    	run_state = rs.RUNNING;
    	
    	/** 消息句柄 */
    	timer_handler = new Handler() {
    		public void handleMessage(Message msg) {
    			if(!pause)
    			{
	    			switch(msg.what) {
	    			/** 计时中... */
	    			case 1:
	    				{
	    					now_time++;
	    					UpdateTextView();
	    					
	    					/** 时间到... */
	    					if(now_time >= tot_time)
	    					{
	    						run_state = rs.FINISHED;
	    						timer.cancel();
	    						FinishGame();
	    					}
	    				}
	    			}
    			}
    			
    			super.handleMessage(msg);
    		}
    	};
    	
    	/** 任务 */
	 	tt = new TimerTask() {
			public void run() {
				Message msg = new Message();
				msg.what = 1;
				timer_handler.sendMessage(msg);
			}
		};
    	
    	timer = new Timer();
    	timer.schedule(tt, 0, 1000);
    }
    
    /**
     * @brief 设置未开始游戏
     */
    private void notStart() {
    	//time_view.setText(data_file.toString());
    	time_view.setText("从第一次点击\"我\"开始计时。");
    	//if(!can_open) time_view.setText("can't");
    	
    	run_state = rs.NOT_RUNNING;
    }
    
    /**
     * @brief 初始化组件
     */
    private void initWidget() {
    	game_button = (Button)findViewById(R.id.game_button);
    	time_view = (TextView)findViewById(R.id.time_view);
    	
    	game_button.setOnClickListener(game_button_onClick);
    }
    
    /**
     * @brief 全屏函数
     */
    private void setFullScreen() {
    	/** 无TitleBar */
    	requestWindowFeature(Window.FEATURE_NO_TITLE);
    	
    	/** 设置全屏 */
    	app_window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
    }
    
    private void ReadData() {
    	data_path = getExternalFilesDir("main");
        data_file = new File(data_path, "highscore");
        
        /** 不存在data_file */
        if(!data_file.exists())
        {
        	try {
				data_file.createNewFile();
			} catch (IOException e) {
				can_open = false;
			}
			
			/** 创建成功 */
			if(can_open) {
				try {
					FileOutputStream out = new FileOutputStream(data_file);
					PrintStream p = new PrintStream(out);
					
					p.println(0);
				} catch (FileNotFoundException e) {
					can_open = false;
				}
			}
        }
        
        if(can_open) {
        	try {
				//FileInputStream in = new FileInputStream(data_file);
				LineNumberReader lnr = new LineNumberReader(new FileReader(data_file));
				
				lnr.setLineNumber(1);
				StreamTokenizer stok = new StreamTokenizer(lnr);
				stok.parseNumbers();
				stok.eolIsSignificant(true);
				try {
					stok.nextToken();
				} catch (IOException e) {
					can_open = false;
					return;
				}
				
				if(stok.ttype != StreamTokenizer.TT_EOF) {
					if(stok.ttype != StreamTokenizer.TT_EOL) {
						if(stok.ttype == StreamTokenizer.TT_NUMBER)
							highest = (int)stok.nval;
					}
				}
				
				try {
					lnr.close();
				} catch (IOException e) {
					Alert("Error: " + e, "Error", false);
					can_open = false;
				}
			} catch (FileNotFoundException e) {
				can_open = false;
			}
        }
    }
    
    private boolean WriteData() {
    	if(!can_open) return false;
    	try {
			FileOutputStream out = new FileOutputStream(data_file);
			PrintStream p = new PrintStream(out);
			
			p.println(hits);
			
			try {
				out.close();
			} catch (IOException e) {
				Alert("Error: " + e, "Error", false);
				return false;
			}
		} catch (FileNotFoundException e) {
			can_open = false;
			return false;
		}
		
		return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	if(item.getItemId() == 1) {
    		System.exit(0);
    	}
    	else
    	if(item.getItemId() == 2) {
    		Alert("Fasnger ver 1.0\nFast Finger\nAuthor: xcoder\nhttp://xcoder.in/\n2011-03-18", "关于", false);
    	}
    	
		return true;
    }
    
    /** 创建菜单 */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add(0, 1, 1, "退出");
        menu.add(0, 2, 2, "关于");
        return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public void onPause() {
    	super.onPause();
    	if(run_state == rs.RUNNING)
    	{
    		pause = true;
    	}
    }
    
    @Override
    public void onResume() {
    	super.onResume();
    	if(run_state == rs.RUNNING)
    	{
    		pause = false;
    	}
    }
}

