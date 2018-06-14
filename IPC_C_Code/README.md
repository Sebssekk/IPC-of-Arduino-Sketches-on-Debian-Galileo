# IPC Idea
This are starting plain C code to understand IPC idea of this project.  

To check this just
- __compile all :__  
```bash
gcc -c itostr.c
```  
```bash
gcc itostr.o nodoWR.c -o nodoWR
```
```bash
gcc nodoRD.c -o nodoRD -lrt
```
```bash
gcc nodoRD_2.c -o nodoRD_2 -lrt
```
```bash
gcc itostr.o Message_Handler.c -o Message_Handler -lrt -lpthread
```

- __Run at the same time nodes__
