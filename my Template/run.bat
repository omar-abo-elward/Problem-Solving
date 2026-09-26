@echo off
g++ %1.cpp -o a.exe
if %errorlevel% equ 0 (
    powershell -Command "$p = Start-Process -FilePath 'cmd.exe' -ArgumentList '/c a.exe < input.txt > output.txt' -NoNewWindow -PassThru; $p.WaitForExit(); $real = $p.ExitTime - $p.StartTime; $user = $p.UserProcessorTime; $sys = $p.PrivilegedProcessorTime; function fmt($ts) { '{0}m{1:0.000}s' -f [math]::Floor($ts.TotalMinutes), ($ts.TotalSeconds %% 60) }; $t = [char]9; Write-Host ('real' + $t + (fmt $real)); Write-Host ('user' + $t + (fmt $user)); Write-Host ('sys' + $t + (fmt $sys))"
)