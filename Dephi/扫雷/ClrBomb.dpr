program ClrBomb;

uses
  Forms,
  Client in 'Client.pas' {CBomb};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'ËÀÔÂÉ¨À×';
  Application.CreateForm(TCBomb, CBomb);
  Application.Run;
end.
