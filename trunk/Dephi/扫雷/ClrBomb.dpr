program ClrBomb;

uses
  Forms,
  Client in 'Client.pas' {CBomb};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '����ɨ��';
  Application.CreateForm(TCBomb, CBomb);
  Application.Run;
end.
