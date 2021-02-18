# Virtual-CPU-Simulator
A side project designed to simulate the computations of a central processing unit. Instructions are 32-Bit.

## Custom CPU Architecture:

### CPU Pipeline:

1. Fetch/Decode (Fetch)
2. Dispatch/Read/Execute (Execute)
3. Writeback (Commit)

*While conventionally these steps are performed independently, for the sake of this simulator some steps will be combined together.*

### Operation Encoding:

  *operation destinationRegister OperandSource1 OperandSource2*

### Instruction Format:
  
  *Register:*
   
  | TYPE (2 Bits) | OPCODE (4 Bits) | Dest Reg (5 Bits) | Src Reg 1 (5 bits) | Src Reg 2 (5 Bits) | UNUSED (11 Bits) |
  
  *Immediate*
  
  | TYPE (2 Bits) | OPCODE (4 Bits) | Dest Reg (5 Bits) | Src Reg 1 (5 Bits) | Immediate (16 Bits) |
  
  *Jump*
  
  | TYPE (2 Bits) | Address (30 Bits) |
  
  *Prompt*
  
  | TYPE (2 Bits) | OPCODE (4 Bits) | Dest Reg (5 Bits) | User Prompt Immediate (21 Bits) |


### Instruction Types:
  1. Register: Operations between 2 registers 
  2. Immediate: Operation between 1 register and an immediate value
  3. Jump: Jumps execution to a specific point
  4. Prompt: Similar to a load, requests user input to load a register
  
  Type | Code
  ---- | ----
  Register | 00
  Immediate | 01
  Jump | 10
  Prompt | 11
  
### Supported Operations:

Operation | Opcode (Binary) | Opcode (Decimal)
--------- | --------------- | ----------------
ADD | 0000 | 0
SUB | 0001 | 1
MULT | 0010 | 2
DIV | 0011 | 3
MOD | 0100 | 4
BEQ (Branch Equals) | 0101 | 5
BNQ (Branch Not Equals) | 0110 | 6
MOV | 0111 | 7
PRINT | 1000 | 8

### Branching: BEQ and BNQ
```c++
  if( i == 5 ){
    ...
  } else {
    ...
  }

```

### Registers:

15 Registers: r0, r1, r2, ... r15

#### Dedicated Registers:

r0: Always holds 0 (READ ONLY)

r2: for storing paramteres from Prompt Type instructions (READ ONLY, Prompt Type instructions may WRITE AND READ)
  
## Compiling:

```shell
$ make #build

$ make clean #remove executables and object files
```

## Running:

Two Sample Programs: Fibonacci and Factorial

*See: Fibonacci.csv and Factorial.csv*

```shell
$ ./main
```

## Demo:

```
$ ./main
Enter Program Name: factorial.csv
Reading File factorial.csv

Thank You. Processing...
Enter a parameter for execution: 5

Final Result is: 120
Average Latency Per Insruction: 0.0714286ms
Average Throughput Per Instruction: 9
Enter Program Name: exit

```
