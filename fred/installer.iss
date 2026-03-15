[Setup]
AppName=Fred Runtime
AppVersion=1.0
AppPublisher=Your Name
DefaultDirName={autopf}\Fred
DefaultGroupName=Fred
OutputDir=installer
OutputBaseFilename=FredSetup
Compression=lzma
SolidCompression=yes
ChangesEnvironment=yes
AppId={{FRED-RUNTIME-UNIQUE-ID-001}
CloseApplications=yes
PrivilegesRequired=lowest

[Files]
Source: "build\fred.exe"; DestDir: "{app}"
Source: "build\libgcc_s_seh-1.dll"; DestDir: "{app}"
Source: "build\libstdc++-6.dll"; DestDir: "{app}"
Source: "build\libwinpthread-1.dll"; DestDir: "{app}"

[Registry]
; Store install path so we can find it on update
Root: HKCU; Subkey: "Software\FredRuntime"; ValueType: string; ValueName: "InstallPath"; ValueData: "{app}"; Flags: uninsdeletekey

[Tasks]
Name: modifypath; Description: "Add Fred to PATH (recommended)"

[Code]
// Adds Fred's install directory to PATH
procedure AddToPath(Path: string);
var
  CurrentPath: string;
begin
  if not RegQueryStringValue(HKEY_CURRENT_USER, 'Environment', 'PATH', CurrentPath) then
    CurrentPath := '';
  if Pos(LowerCase(Path), LowerCase(CurrentPath)) = 0 then
  begin
    if CurrentPath <> '' then
      CurrentPath := CurrentPath + ';';
    CurrentPath := CurrentPath + Path;
    RegWriteStringValue(HKEY_CURRENT_USER, 'Environment', 'PATH', CurrentPath);
  end;
end;

procedure RemoveFromPath(Path: string);
var
  CurrentPath: string;
  NewPath: string;
  P: Integer;
  Part: string;
begin
  if not RegQueryStringValue(HKEY_CURRENT_USER, 'Environment', 'PATH', CurrentPath) then
    Exit;

  NewPath := '';
  CurrentPath := CurrentPath + ';';

  while CurrentPath <> '' do
  begin
    P := Pos(';', CurrentPath);
    Part := Copy(CurrentPath, 1, P - 1);
    CurrentPath := Copy(CurrentPath, P + 1, Length(CurrentPath));

    if LowerCase(Part) <> LowerCase(Path) then
    begin
      if NewPath <> '' then NewPath := NewPath + ';';
      NewPath := NewPath + Part;
    end;
  end;

  RegWriteStringValue(HKEY_CURRENT_USER, 'Environment', 'PATH', NewPath);
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    if WizardIsTaskSelected('modifypath') then
      AddToPath(ExpandConstant('{app}'));
  end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usPostUninstall then
    RemoveFromPath(ExpandConstant('{app}'));
end;