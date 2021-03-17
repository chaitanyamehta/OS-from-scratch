# OS from scratch

An OS built from scratch using x86 simulator bochs.

## Whats working
- Initialize global descriptor table.
- Initialize interrupt descriptor table.
- Function for printing using video memory.
- Keyboard input.
- Timer ISR.

## Running the program
1. Compile using make.
   ```console
   $ make
   ```
2. Run program.
   ```console
   $ bochs
   ```

## References
* Writing a simple operating system from scratch by Nick Blundell
* http://www.osdever.net/bkerndev/Docs/title.htm
* http://www.jamesmolloy.co.uk/tutorial.html
* https://github.com/ajaysa/MyOS_Blundell
