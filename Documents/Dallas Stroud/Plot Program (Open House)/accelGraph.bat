<# : accelGraph.bat
@echo off
setlocal

:Prompt user to select the data log file and extract the file path
echo Select log file to plot:
for /f "delims=" %%I in ('powershell -noprofile "iex (${%~f0} | out-string)"') do (
	set textFile=%%~I
)

:Pass data file to plotting program and execute application
.\accelPlot.exe "%textFile%"
PAUSE
goto :EOF

:end Batch portion / begin PowerShell hybrid chimera #>

Add-Type -AssemblyName System.Windows.Forms
$F = new-object Windows.Forms.OpenFileDialog
$f.InitalDirectory = pwd
$f.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*"
$f.ShowHelp = $true
$f.Multiselect = $false
[void]$f.ShowDialog() 
if ($f.Multiselect) { $f.FileNames } else { $f.FileName }