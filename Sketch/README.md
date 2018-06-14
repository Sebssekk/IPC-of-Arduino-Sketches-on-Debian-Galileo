# Sketch Folder
Here you can find all codes of the project.

## How to use
To make it work you have to
- __Set up your Debian Galileo__

- __Create in your home a folder called `arduino`__

- __Copy in this folder the `hardware` folder found with Arduino IDE__

- __Copy in this folder all these file__

- __Compile .c file and Start__
```bash
gcc -c itostr.c
```
```bash
gcc itostr.o Message_Handler.c -o Message_Handler -lrt -lpthread
```
```bash
gcc Start.cpp -o Start -lpthread
```
- __Compile Sketches__  
  Changing last lines of SConstruct file with output name and input name as indicated (Blink.cpp is an easy example to test everything works) and run `scons`

- __Run `./Start` and let it go__
