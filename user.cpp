#include <signal.h>
#include <string.h>

#include "simpi.h"
#define MATRIX_DIMENSION_X 50
#define MATRIX_DIMENSION_Y 50

int par_id;

void segfault_printer(int dummy)
{
  char buf[20];
  sprintf(buf, "%d: segfaulted\n", par_id);
  write(STDOUT_FILENO, buf, strlen(buf));
  exit(1);
}

int main(int argc, char* argv[])
{
  printf("user starting...\n");
  signal(SIGSEGV, segfault_printer);
  par_id = atoi(argv[1]);
  int num_workers = atoi(argv[2]);
  int num_workstations = atoi(argv[3]);
  int workstationid = atoi(argv[4]);
  SIMPI_INIT(par_id, num_workers, num_workstations, workstationid);
  matrix A(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
  matrix B(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
  matrix C(MATRIX_DIMENSION_X, MATRIX_DIMENSION_Y);
  vector D(10);
  SIMPI_SYNCH();

  for (int y = 0; y < MATRIX_DIMENSION_Y; y++) {
    for (int x = 0; x < MATRIX_DIMENSION_X; x++) {
      A.get(x, y) = rand()%10 + 1;
    }
  }
  for (int y = 0; y < MATRIX_DIMENSION_Y; y++) {
    for (int x = 0; x < MATRIX_DIMENSION_X; x++) {
      B.get(x, y) = rand()%10 + 1;
    }
  }
  SIMPI_SYNCH();

  
  //std::cout << A;
  
  //std::cout << B;
  C= A * B;
  //std::cout << C;
  SIMPI_DISTRIBUTE(C);
  //std::cout fsdf << C;
  //C= A.inverse();

  //std::cout << C; 
  //SIMPI_FINALIZE();
  exit(0);
}
