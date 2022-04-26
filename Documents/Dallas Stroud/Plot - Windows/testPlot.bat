@echo on

set /p DATAFILE="Enter the Data File: "
dir /b/s %DATAFILE%|findstr %DATAFILE% > tmp.txt
set /p DATA=<tmp.txt
dir "\plot.exe" /b/s > tmp.txt
set /p EXEFILE=<tmp.txt
del tmp.txt
"%EXEFILE%" "%DATA%"