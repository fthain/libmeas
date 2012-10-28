#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <meas/meas.h>
#include "csun.h"

unsigned char r[640 * 480], g[640 * 480], b[640 * 480];

int main(int argc, char **argv) {

  double tstep, delay;
  char filebase[512], filename[512];
  int fd;
  FILE *fp;

  printf("Enter output file name: ");
  scanf("%s", filebase);
  printf("Enter time step (ns): ");
  scanf(" %le", &tstep);
  printf("Running... press ctrl-c to stop.\n");
  tstep *= 1E-9;
  meas_graphics_init(0, MEAS_GRAPHICS_IMAGE, 640, 480, 0, "video");
  fd = meas_video_open("/dev/video0");
  surelite_delay(0.0);
  minilite_delay(delay);
  laser_set_delays();
  laser_start();
  for(delay = 0.0; ; delay += tstep) {
    printf("Delay = %le ns.\n", delay*1E9);
    // need to stop lasers for this?
    surelite_delay(0.0);  // ablation
    minilite_delay(delay);// flash
    laser_set_delays();
    meas_video_start(fd);
    meas_video_read_rgb(fd, r, g, b);
    meas_video_stop(fd);
    meas_graphics_update_image(0, r, g, b);
    meas_graphics_update();
    sprintf(filename, "%s-%le.img", filebase, delay);
    if(!(fp = fopen(filename, "w"))) {
      fprintf(stderr, "Error writing file.\n");
      exit(1);
    }
    fwrite((void *) r, sizeof(unsigned char) * 640 * 480, 1, fp);
    fwrite((void *) g, sizeof(unsigned char) * 640 * 480, 1, fp);
    fwrite((void *) b, sizeof(unsigned char) * 640 * 480, 1, fp);
    fclose(fp);
  }
}
