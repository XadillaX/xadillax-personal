object CBomb: TCBomb
  Left = 334
  Top = 57
  BorderStyle = bsToolWindow
  Caption = #27515#26376#25195#38647
  ClientHeight = 330
  ClientWidth = 170
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Aera: TStringGrid
    Left = 0
    Top = 0
    Width = 170
    Height = 170
    Align = alTop
    BorderStyle = bsNone
    Color = clInfoText
    ColCount = 10
    DefaultColWidth = 16
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 10
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clTeal
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 0
    OnMouseDown = AeraMouseDown
  end
  object Panel1: TPanel
    Left = 0
    Top = 170
    Width = 170
    Height = 160
    Align = alBottom
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 36
      Height = 13
      Caption = #29992#26102#65306
    end
    object Label2: TLabel
      Left = 8
      Top = 48
      Width = 36
      Height = 13
      Caption = #34892#25968#65306
    end
    object Label3: TLabel
      Left = 8
      Top = 72
      Width = 36
      Height = 13
      Caption = #21015#25968#65306
    end
    object Label4: TLabel
      Left = 8
      Top = 96
      Width = 36
      Height = 13
      Caption = #38647#25968#65306
    end
    object Label5: TLabel
      Left = 8
      Top = 116
      Width = 36
      Height = 13
      Caption = #26242#21097#65306
    end
    object Label6: TLabel
      Left = 8
      Top = 144
      Width = 126
      Height = 13
      Cursor = crHandPoint
      Caption = #26417#20975#36842' Zukaidi@163.com'
      OnClick = Label6Click
    end
    object Time: TEdit
      Left = 48
      Top = 8
      Width = 49
      Height = 21
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = '00:00'
    end
    object Ipt_Y: TEdit
      Left = 48
      Top = 40
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '10'
      OnKeyPress = Ipt_YKeyPress
    end
    object Ipt_X: TEdit
      Left = 48
      Top = 64
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '10'
      OnKeyPress = Ipt_YKeyPress
    end
    object Ipt_Bomb: TEdit
      Left = 48
      Top = 88
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '20'
      OnKeyPress = Ipt_YKeyPress
    end
    object Submit: TButton
      Left = 104
      Top = 8
      Width = 59
      Height = 65
      Caption = #24320#22987'(&B)'
      TabOrder = 4
      OnClick = SubmitClick
    end
    object Rest: TEdit
      Left = 48
      Top = 112
      Width = 49
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '20'
    end
    object Stop: TButton
      Left = 103
      Top = 80
      Width = 59
      Height = 52
      Caption = #20572#27490'(&S)'
      Enabled = False
      TabOrder = 6
      OnClick = StopClick
    end
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 136
    Top = 176
  end
end
