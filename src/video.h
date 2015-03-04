#include <linux/videodev2.h>

/* Maximum number of devices that can be open simultaneously */
#define MEAS_VIDEO_MAXDEV 4

/* Special exposure times */
#define MEAS_VIDEO_AUTO_EXPOSURE_ON  (-1)
#define MEAS_VIDEO_AUTO_EXPOSURE_OFF (-2)

/* Property types */
#define MEAS_VIDEO_TYPE_INTEGER V4L2_CTRL_TYPE_INTEGER
#define MEAS_VIDEO_TYPE_BOOLEAN V4L2_CTRL_TYPE_BOOLEAN
#define MEAS_VIDEO_TYPE_MENU    V4L2_CTRL_TYPE_MENU
#define MEAS_VIDEO_TYPE_INTEGER_MENU V4L2_CTRL_TYPE_INTEGER_MENU
#define MEAS_VIDEO_TYPE_BITMASK V4L2_CTRL_TYPE_BITMASK

/* Data types */
#define 
