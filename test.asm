// Program: add2v2.asm
// Computes: RAM[2] = RAM[0] + RAM[1]
// Usage: put values in RAM[0], RAM[1]

  @0
  D=M	// D = RAM[0]

  @1
  D=D+M // D = D + RAM[1]

   @2
  M=D	// RAM[2] = D

  D-1;JEQ
  D+1
@6
0;JMP
