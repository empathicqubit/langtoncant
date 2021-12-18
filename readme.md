A port of https://github.com/bjartwolf/ant to the high level language c

# Getting started

Install Vice emulator
In PowerShell on Windows, as... The GUI does not work in WSL2 yet.
```powershell
choco install winvice
```
Install cc65 in WSL2

https://cc65.github.io/doc/intro.html

```
sudo apt-get install cc65
```

Open in VS Code and install recommended extension.

Probably need powershell...
https://docs.microsoft.com/en-us/powershell/scripting/install/install-ubuntu?view=powershell-7.2

Not sure if I had a typo in my header or I have to import sudo apt-get install clang

I added "C:\ProgramData\chocolatey\lib\winvice\tools\WinVICE-3.1-x64" to the path on windows, then I could run 
```
cl65 hello.c -o hello.prg
x64.exe hello.prg 
```
to run hello world