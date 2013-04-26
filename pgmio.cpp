#include <stdio.h>
#include <string.h>

int readPGM(const char *filename,unsigned char *&image,int &xsize,int &ysize) {
  FILE *file;
  char line[81],word[81];

  //Initialize image sizes and pointer

  image=NULL; xsize=ysize=0;

  //Open input file for reading

  if (!(file=fopen(filename,"r"))) return 0;

  //Read PGM header

  fgets(line,81,file); sscanf(line,"%s",word);
  if (strcmp(word,"P5")) {fclose(file); return 0;}   //Check for PGM identifier

  do {fgets(line,81,file); sscanf(line,"%s",word);}  //Read past comments
  while (*word=='#');

  sscanf(line,"%d %d",&xsize,&ysize);                //Read image size

  fgets(line,81,file);                               //Read past rest of header

  if (xsize<=0 || ysize<=0) {fclose(file); xsize=ysize=0; return 0;}

  //Allocate space for image data

  image=new unsigned char[xsize*ysize];

  //Read image data from file

  if (fread(image,sizeof(unsigned char),xsize*ysize,file)<xsize*ysize)  {
    fclose(file); delete[] image; image=NULL; xsize=ysize=0; return 0;
  }

  //Close file and return

  fclose(file);
  return 1;
}

int writePGM(const char *filename,unsigned char *image,int xsize,int ysize) {
  FILE *file;

  //Open output file for writing

  if (!(file=fopen(filename,"w"))) return 0;

  //Write PGM header

  fprintf(file,"P5\n");
  fprintf(file,"# CREATOR: pgmio.C Rev: 11/04/01\n");
  fprintf(file,"%d %d\n",xsize,ysize);
  fprintf(file,"255\n");

  //Write image data to file

  fwrite(image,sizeof(unsigned char),xsize*ysize,file);

  //Close file and return

  fclose(file);
  return 1;
}
