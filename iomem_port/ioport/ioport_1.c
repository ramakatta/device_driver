/*
 * example.c: very simple example of port I/O
 *
 * This code does nothing useful, just a port write, a pause,
 * and a port read. Compile with `gcc -O2 -o example example.c',
 * and run as root with `./example'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define BASEPORT 0x70 /* lp1 */

int main()
{
  char val = 0;
  /* Get access to the ports */
  if (ioperm(BASEPORT, 4, 1)) {perror("ioperm"); exit(1);}
  
  val = inb(BASEPORT+1);
  printf("seconds:%x\n",val); 
  
  /* Read from the status port (BASE+1) and display the result 
  printf("val2: %d\n", inb(BASEPORT + 2));
  printf("val3: %d\n", inb(BASEPORT + 3));*/

  /* We don't need the ports anymore */
  if (ioperm(BASEPORT, 3, 0)) {perror("ioperm"); exit(1);}
  return 0;
}
