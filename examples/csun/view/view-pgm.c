/* View video frames (IMGSRC camera) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <meas/meas.h>

#define HEIGHT 1280
#define WIDTH 960

unsigned char *rgb, *y16;

int main(int argc, char **argv) {

  double tstep, delay, t0;
  char filebase[512], filename[512];
  int fd, i;
  FILE *fp;
  unsigned int width, height;

  printf("Enter file basename: ");
  scanf("%s", filebase);
  sprintf(filename, "%s.info", filebase);
  if(!(fp = fopen(filename, "r"))) {
    fprintf(stderr, "Can't open info file.\n");
    exit(1);
  }
  fscanf(fp , "%le %le %*le %*le %*d %*le %*d", &t0, &tstep);
  fclose(fp);
  if(!(rgb = (unsigned char *) malloc(WIDTH * HEIGHT * 3))) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  if(!(y16 = (unsigned char *) malloc(WIDTH * HEIGHT * 4))) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  meas_graphics_open(0, MEAS_GRAPHICS_IMAGE, HEIGHT, WIDTH, 0, "video");
  meas_tty_raw();
  for(delay = t0; ; delay += tstep) {
    char chr;
    if((chr = meas_tty_read()) != 0) {
      switch(chr) {
      case ' ':
	while(meas_tty_read() != ' ') usleep(200);
	break;
      case '-':
	tstep = -fabs(tstep);
	break;
      case '+':
	tstep = fabs(tstep);
	break;
      case 'q':
	meas_tty_normal();
	exit(1);
      }
    }
    if(delay < 0.0) delay = 0.0;
    printf("Delay = %le ns.\n\r", delay*1E9);
    sprintf(filename, "%s-%le.pgm", filebase, delay);
    if(!(fp = fopen(filename, "r"))) {
      fprintf(stderr, "Error opening file.\n");
      meas_tty_normal();      
      exit(1);
    }
    if(meas_image_pgm_to_y16(fp, y16, &width, &height) < 0) {
      fprintf(stderr, "Error reading file.\n");
      meas_tty_normal();
      exit(1);
    }
    fclose(fp);
    meas_image_y16_to_rgb3(y16, rgb, WIDTH, HEIGHT);    
    meas_graphics_update_image(0, rgb);
    meas_graphics_update();
    usleep(100000);
  }
}
