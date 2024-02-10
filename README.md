Tiny Virtual Machine
one paragraph stating what is your program doing
The program acts as a machine that takes in set of instructions and executing it. 
It reads a .txt file with set of instructions containing opcodes line by line, then
storing it into an array of instructions (Program Memory). After all the instructions
are read in, it calls a simulator. It then call the fetch cycle to move everything
to MDR then MDR to IR. The simulator then uses opcodes to pick cases.

what opcodes does your tiny virtual machine adhere to?

Opcode  mnemonic    meaning
01      LOAD X      A <— DM[x]
02      ADD X       A <— A + DM[x]
03      STORE X     DM[x] <— A 
04      SUB X       A <— A - DM[x]
05      IN          A <— read from Device
06      OUT         A <— output to Device
07      HALT        STOP
08      JMP X       PC <— x
09      SKIPZ       if Z = 1 Skip next instruction


Assignment: Programming Project 3 (Tiny Harvard Architecture ISA)

Author: Tuyen Huynh & Kendall Ng 

School: University of Central Florida

Professor:  Euripides Montagne
Class:      CGS3269
Due date:   11/28/2023

Language: C

To Compile: gcc main.c
To Execute: ./a.exe

When: First there must be a valid .txt file to run. The next is that it must contain opcodes in number pairs.

Note: Program counter is set to 10 similar to the one in the homework file. 