unit Client;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, ExtCtrls, shellAPI;

type
  TCBomb = class(TForm)
    Aera: TStringGrid;
    Panel1: TPanel;
    Time: TEdit;
    Ipt_Y: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Ipt_X: TEdit;
    Label4: TLabel;
    Ipt_Bomb: TEdit;
    Submit: TButton;
    Timer: TTimer;
    Label5: TLabel;
    Rest: TEdit;
    Stop: TButton;
    Label6: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure floodfill(tmpx,tmpy:Longint);
    procedure SubmitClick(Sender: TObject);
    procedure TimerTimer(Sender: TObject);
    procedure makeBomb(Sender: TObject);
    procedure StopClick(Sender: TObject);
    procedure AeraMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure showDeathResult(sender: TObject;tmpx,tmpy:Longint);
    procedure GoThrough;
    procedure Label6Click(Sender: TObject);
    procedure Ipt_YKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  isStart: BOOL;
  CBomb: TCBomb;
  X,Y,Bomb,BombLeft,TCount: Integer;
  Map:array[0..99,0..99] of Integer;

implementation

{$R *.dfm}

procedure tCBomb.floodfill(tmpx,tmpy:Longint);
begin
  Aera.Cells[tmpx,tmpy]:='□';
  if (tmpx-1>=0) and (Map[tmpx-1,tmpy] > 0) then aera.cells[tmpx-1,tmpy]:=IntToStr(map[tmpx-1,tmpy]);
  if (tmpx+1<x) and (map[tmpx+1,tmpy] > 0) then Aera.Cells[tmpx+1,tmpy]:=IntToStr(map[tmpx+1,tmpy]);;
  if (tmpy-1>=0) and (map[tmpx,tmpy-1] > 0) then Aera.Cells[tmpx,tmpy-1]:=IntToStr(map[tmpx,tmpy-1]);;
  if (tmpy+1<y) and (map[tmpx,tmpy+1] > 0) then Aera.Cells[tmpx,tmpy+1]:=IntToStr(map[tmpx,tmpy]+1);;

  if (tmpx-1>=0) and (Map[tmpx-1,tmpy] = 0) and (Aera.cells[tmpx-1,tmpy] <> '□') then floodfill(tmpx-1,tmpy);
  if (tmpx+1<x) and (Map[tmpx+1,tmpy] = 0) and (Aera.cells[tmpx+1,tmpy] <> '□') then floodfill(tmpx+1,tmpy);
  if (tmpy-1>=0) and (Map[tmpx,tmpy-1] = 0) and (Aera.cells[tmpx,tmpy-1] <> '□') then floodfill(tmpx,tmpy-1);
  if (tmpy+1<y) and (Map[tmpx,tmpy+1] = 0) and (Aera.cells[tmpx,tmpy+1] <> '□') then floodfill(tmpx,tmpy+1);
end;

procedure TCBomb.FormCreate(Sender: TObject);
var
  i,j:Longint;
begin
  isStart:=False;
  x:=10;
  y:=10;
  for i:=0 to 9 do
    for j:=0 to 9 do Aera.Cells[i,j]:='■';
end;

procedure TCBomb.makeBomb(Sender: TObject);
var
  i,tmpx,tmpy,j,rbomb:Longint;
begin
  Randomize;
  FillChar(Map,sizeof(Map),0);
  for i:=1 to Bomb do
  begin
    repeat
      tmpx:=Random(X-1);
      tmpy:=random(y-1);
    until Map[tmpx,tmpy]=0;
    Map[tmpx,tmpy]:=-1;
  end;
  for i:=0 to x-1 do
    for j:=0 to y-1 do
    Begin
      rbomb:=0;
      if Map[i,j]<>-1 then
      begin
        if (i-1>=0) and (j-1>=0) and (Map[i-1,j-1]=-1) then Inc(rbomb);
        if (i-1>=0) and (Map[i-1,j]=-1) then Inc(rbomb);
        if (i-1>=0) and (j+1<y) and (Map[i-1,j+1]=-1) then Inc(rbomb);
        if (j-1>=0) and (Map[i,j-1]=-1) then Inc(rbomb);
        if (j+1<y) and (Map[i,j+1]=-1) then Inc(rbomb);
        if (i+1<x) and (j-1>=0) and (Map[i+1,j-1]=-1) then Inc(rbomb);
        if (i+1<x) and (Map[i+1,j]=-1) then Inc(rbomb);
        if (i+1<x) and (j+1<y) and (Map[i+1,j+1]=-1) then Inc(rbomb);
        //if rbomb <>0 then Aera.Cells[i,j]:=inttostr(rbomb)
        //else Aera.Cells[i,j]:='□';
        map[i,j]:=rbomb;
      end;
      //else Aera.Cells[i,j]:='※';
      Aera.Cells[i,j]:='■';
    end;
  isStart:=true;
end;

procedure TCBomb.SubmitClick(Sender: TObject);
var
  tmp:String;
  code,tmpint,err:integer;
begin
  err:=0;

  tmp:=Ipt_Y.Text;
  Val(tmp,tmpint,code);
  if (code=1) or (tmpint>100) or (tmpint<1) then Inc(err);

  tmp:=Ipt_X.Text;
  Val(tmp,tmpint,code);
  if (code=1) or (tmpint>100) or (tmpint<1) then Inc(err);

  tmp:=Ipt_Bomb.Text;
  Val(tmp,tmpint,code);
  if (code=10) or (tmpint<1) then Inc(err);

  if (err=0) and (tmpint<y*x) then
  Begin
    tmp:=Ipt_Y.Text;
    y:=StrToInt(tmp);

    tmp:=Ipt_X.Text;
    x:=StrToInt(tmp);

    tmp:=Ipt_Bomb.Text;
    bomb:=StrToInt(tmp);

    TCount:=0;
    Timer.Enabled:=True;
    BombLeft:=Bomb;
    tmp:=IntToStr(BombLeft);
    Rest.Text:=tmp;
    CBomb.clientWidth:=x * 17;
    CBomb.clientHeight:=y * 17 + 160;
    Aera.RowCount:=Y;
    Aera.ColCount:=X;
    Aera.Width:=x * 17;
    Aera.Height:=y * 17;
    Ipt_Y.Enabled:=False;
    Ipt_X.enabled:=False;
    Ipt_Bomb.Enabled:=False;
    Stop.Enabled:=True;
    Submit.Enabled:=False;
    makeBomb(Sender);
  end
  else ShowMessage('您的输入有误，请检查。注意：行列大小在100以内！');
end;

procedure TCBomb.TimerTimer(Sender: TObject);
var
  m,s:Longint;
  sm,ss:String;
begin
  Inc(TCount);
  m:=TCount div 60;
  s:=TCount mod 60;
  sm:=IntToStr(m);
  ss:=IntToStr(s);
  if s < 10 then ss:='0'+ss;
  if m < 10 then sm:='0'+sm;
  Time.Text:=sm+':'+ss;
end;

procedure TCBomb.StopClick(Sender: TObject);
begin
  Aera.RowCount:=10;
  Aera.ColCount:=10;

  CBomb.ClientHeight:=330;
  CBomb.ClientWidth:=170;
  Aera.Width:=170;
  Aera.Height:=170;

  formcreate(Sender);
  Stop.Enabled:=False;
  Submit.Enabled:=True;
  Ipt_Y.Enabled:=True;
  Ipt_X.Enabled:=True;
  Ipt_Bomb.enabled:=True;
  Timer.enabled:=False;
  isStart:=False;
  //Time.Text:='00:00';
end;

procedure TCBomb.showDeathResult(sender: TObject;tmpx,tmpy:Longint);
var
  i,j:Longint;
begin
  //
  for i:=0 to x-1 do
    for j:=0 to y-1 do
    Begin
      if (Aera.Cells[i,j]='Ψ') and (Map[i,j]<>-1) then Aera.cells[i,j]:='错'
      else
      if (Aera.cells[i,j]='Ψ') and (Map[i,j]=-1) then Aera.Cells[i,j]:='对'
      else
      if Map[i,j]>0 then aera.Cells[i,j]:=IntToStr(MAP[i,j])
      else
      if Map[i,j]=0 then aera.Cells[i,j]:='□'
      else
      if (i=tmpx) and (j=tmpy) then aera.Cells[i,j]:='死'
      else aera.Cells[i,j]:='※';
    end;
end;

procedure TCBomb.GoThrough;
var
  i,j:Longint;
  tag:BOOL;
begin
  tag:=False;
  for i:=0 to x-1 do
    for j:=0 to y-1 do
    Begin
      if (Map[i,j]>=0) and ((Aera.Cells[i,j]='Ψ') or (Aera.Cells[i,j]='？') or (Aera.Cells[i,j]='■')) then
      Begin
        tag:=True;
        Break;
      end
      else
      if (Map[i,j]=0) and (Aera.Cells[i,j]<>'□') then
      Begin
        tag:=True;
        Break;
      end;
    end;

  if not(tag) then
  Begin
    ShowMessage('您太聪明啦！清除完毕！');
    Stop.Click;
  end;
end;

procedure TCBomb.AeraMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  ACol,ARow:Longint;
begin
  Aera.MouseToCell(X,Y,ACol,ARow);
  if (isStart) and (Button=mbLeft) and (Aera.cells[ACol,ARow]<>'Ψ') and (Aera.cells[ACol,ARow]<>'？') then
  begin
    if Map[ACol,ARow]>0 then Aera.Cells[ACol,ARow]:=IntToStr(MAP[ACol,ARow])
    else
    if Map[ACol,ARow]=0 then FloodFill(ACol,ARow)
    else
    Begin
      showDeathResult(Sender,ACol,ARow);
      ShowMessage('您被地雷炸飞啦！');
      Stop.Click;
    end;
  end;
  if (isStart) and (Button=mbRight) then
  Begin
    if aera.Cells[ACol,ARow]='Ψ' then Aera.Cells[ACol,ARow]:='？'
    else
    if Aera.Cells[ACol,ARow]='？' then
    Begin
      inc(BombLeft);
      Rest.text:=IntToStr(BombLeft);
      Aera.cells[ACol,ARow]:='■';
    end
    else
    if Aera.Cells[ACol,ARow]='■' then
    Begin
      dec(BombLeft);
      Rest.text:=IntToStr(BombLeft);
      Aera.cells[ACol,ARow]:='Ψ';
    end;
  end;
  GoThrough;
end;

procedure TCBomb.Label6Click(Sender: TObject);
begin
  ShellExecute(handle,nil,pchar('mailto:zukaidi@163.com'),nil,nil,SW_SHOWNORMAL);
end;

procedure TCBomb.Ipt_YKeyPress(Sender: TObject; var Key: Char);
begin
  if key=Chr(13) then SubmitClick(Sender);
end;

end.
