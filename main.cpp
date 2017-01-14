#include <stdlib.h>
#include <time.h>
#include "CustomProgram.h"



CustomProgram * g_pProgram = NULL;




// Main function
int main(int argc, const char * argv[])
{
  srand (time(NULL));
  g_pProgram = new CustomProgram(1024,768,false);
  while (g_pProgram->HandleEvents())
  {




  }

  delete g_pProgram;
  return 0;
}





