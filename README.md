# How to setup Allegro with vscode

Ensure you have C++ installed. Follow this [guide](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites) if not.

This is a project with allegro installed and `build.bat` file written for easier compilation.
Important lines of that script are 2nd and 5th. 2nd has all files that project requires, while 5th has all libraries that Allegro provides connected.

### To install allegro manually:

1) Download Allegro prebuild from its [github](https://github.com/liballeg/allegro5/releases).

2) Put Allegro files into the folder with a project.

3) Build your project while connecting all necessary libs. Be sure that built executable is located in the same dir with all `allegro/bin/*.dll` files.