#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 81

int main(void)
{
  char mystr[LENGTH];
  int mychar = 0;
  FILE *pfile = NULL;
  char *filename = "myfile.txt";

  printf("Enter an interesting string of up to %d characters:\n", LENGTH - 1);

  if(!fgets(mystr, LENGTH, stdin))
  {
    printf_s("Input form keyboard failed.\n");
    exit(1);
  }
  
  if(fopen_s(&pfile, filename, "w"))
  {
    printf_s("Error opening %s for writing. Program terminated.\n", filename);
    exit(1);
  }

  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);
  
  int i = 0;

  for(i = strnlen_s(mystr, LENGTH)-1 ; i >= 0; --i)
    fputc(mystr[i], pfile);

  fclose(pfile);

  if(fopen_s(&pfile, filename, "r"))
    {
      printf_s("Error opening %s for reading. Program terminated.", filename);
      exit(1);
    }

  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

  print_s("the data read from the file is: \n");
  while((mychar = fgetc(pfile)) != EOF)
    putchar(mychar);
  putchar('\n');
 
  fclose(pfile);
  pfile = NULL;
  remove(filename);
  return 0;
}
