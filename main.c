#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXPROGRAMSIZE 100
#define BUFFERSIZE 500

typedef struct Instruction
{
  int opCode, deviceOrAddress;

} Instruction;

typedef struct instructionNode InstructionNode;
typedef InstructionNode *InstructionNodePtr;
void tinyMachine(Instruction *programMemory);
void readFile(char *fileName);
void fetch(int *pCounter, int *MAR, Instruction *MDR, Instruction *IR, Instruction *programMemory);
void printHeader(int pCounter, int accumulator, int *dataMemory);


int main(int argc, char **argv)
{
  readFile(argv[1]);

  return 0;
}

void readFile(char *fileName)
{
  FILE *file = fopen("elf.txt", "r");

  char *error;
  char *line;
  char *token;
  int fieldCounter = 0;
  int i = 10;
  Instruction programMemory[MAXPROGRAMSIZE];

  if (file == NULL)
  {
    printf("ERROR: could not open file\n");
  }

  else
  {
    line = malloc(BUFFERSIZE * sizeof(char));
    printf("Assembling Program...\n");
    printf("Program Assembled.\n\n");
    printf("Run.\n\n");

    while(fgets(line, BUFFERSIZE, file) != NULL)
        {
          if(strcmp(line,"\n"))
          {
            token = strtok(line, " ");

            while(token != NULL)
             {

                if(fieldCounter == 0)
                {

                  programMemory[i].opCode = atoi(token);
                }
                if(fieldCounter == 1)
                {
                  programMemory[i].deviceOrAddress = atoi(token);
                }

               fieldCounter++;
               token = strtok(NULL, " ");
             }
             fieldCounter = 0;
             i++;
           }
        }
   
    tinyMachine(programMemory);
  }
}


void tinyMachine(Instruction *programMemory)
{
  int pCounter = 10;
  int MAR; 
  Instruction MDR;
  int accumulator = 0;
  int dataMemory[10] = { 0 }; 
  Instruction IR;
  int userInput;

  for(;;)
  {
    printHeader(pCounter, accumulator, dataMemory);
    fetch(&pCounter, &MAR, &MDR, &IR, programMemory);

    switch(IR.opCode)
    {
      case 1:
      {
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to accumulator*/\n", MAR);
        accumulator = dataMemory[MAR];
        break;
      }
      case 2:
      {
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to be added to accumulator value %d*/\n", MAR, accumulator);
        accumulator+=dataMemory[MAR];
        break;
      }
      case 3:
      {
        MAR = IR.deviceOrAddress;
        printf("/*storing accumulator in memory location %d\n", MAR);
        dataMemory[MAR] = accumulator;
        break;
      }
      case 4:
      {
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to be subtracted from accumulator value %d*/\n", MAR, accumulator);
        accumulator = accumulator - dataMemory[MAR];
        break;
      }
      case 5:
      {
        printf("/*input value*/\n");
        scanf("%d", &accumulator);
        break;
      }
      case 6:
      {
        printf("/*outputting accumulator to screen*/\n");
        printf("%d\n\n", accumulator);
        break;
      }
      case 7:
      {
        printf("Program complete.\n");
        break;
      }
      case 8:
      {
        MAR = IR.deviceOrAddress;
        printf("/*jumping to memory location %d*/\n", MAR);
        pCounter = MAR;
        break;
      }
      case 9:
      {
        if(accumulator == 0)
          pCounter++;
        break;
      }
      default:
      {
        break;
      }
    }
    if(IR.opCode == 7)
      break;
  }
}


void fetch(int *pCounter, int *MAR, Instruction *MDR, Instruction *IR, Instruction *programMemory)
{
  *MAR = *pCounter; 

  MDR->opCode = programMemory[(*MAR)].opCode;
  MDR->deviceOrAddress = programMemory[(*MAR)].deviceOrAddress;
  *IR = *MDR;
  (*pCounter)++;
}

void printHeader(int pCounter, int accumulator, int *dataMemory)
{
 
  printf("PC = %d | A = %d, MEM = [", pCounter, accumulator);

  for(int i = 0; i < 10; i++)
  {
    printf("%d", *(dataMemory + i));
    if (i <= 8){
        printf(",");
    }
  }
  printf("]\n\n");
}