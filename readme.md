A work in progress port of https://github.com/bjartwolf/ant to the high level language c

This lets me run with CTRL+SHIFT+P, but I have given up any smoother workflows with debuggers for now...

![image](https://user-images.githubusercontent.com/88324093/146642839-ee385473-0e2e-40fc-993f-e62c057d0eb8.png)



# Getting started

I have set this up with WSL2 and then running latest nightly Vice in Windows.
I build and run with build tasks, gave up on make files.

Install Vice emulator
```powershell
choco install --version 3.5.2021010401 winvice-nightly
```


#Install cc65 in WSL2
https://cc65.github.io/doc/intro.html

```
sudo apt-get install cc65
```

Open in VS Code and install recommended extension.

Maybe need powershell... I installed in WSL2.
https://docs.microsoft.com/en-us/powershell/scripting/install/install-ubuntu?view=powershell-7.2

Not sure if I had a typo in my header or I have to import sudo apt-get install clang

I added "C:\ProgramData\chocolatey\lib\winvice-nightly\tools\GTK3VICE-3.5-win64\bin" to the path on windows, then I could run 
```
cl65 hello.c -o hello.prg
x64sc.exe hello.prg 
```
to run hello world.

In this project I use Run task (Ctrl+Shift+P) and the task called build and run.


Useful https://sta.c64.org/cbm64mem.html

Using template from, but gave up on it

https://github.com/empathicqubit/vscode-cc65-debugger/tree/master/src/__tests__/c-project-template

https://archive.org/details/The_Graphics_Book_for_the_Commodore_64/page/n25/mode/2up

http://www.appleoldies.ca/cc65/docs/shr/shrworld.pd