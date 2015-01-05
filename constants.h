#ifndef CONSTANTS_H
#define CONSTANTS_H

const QString APPLICATION_NAME = "screen_cap";
const QString ORGANIZATION_NAME = "Osmosys";

const QString FOLDER_DATE_FORMAT = "yyyy_MM_dd";
const QString FILE_DATE_FORMAT = "yyyy_MM_dd_HH_mm_ss";
const QString FILE_LOG_DATE_FORMAT = "yyyy-MM-dd HH:mm:ss";

const QString CAP_TIME = "capture_time";
const QString FILE_PATH =  "file_path";
const QString CAP_HEIGHT = "capture_height";
const QString CAP_WIDTH = "capture_width";
const QString CAP_IS_ON = "is_capturing";
const QString CAP_IS_RANDOM = "is_cap_random";
const QString IMG_FILE_FORMAT = "JPG";

const int DEF_CAP_TIME = 90;
const QString DEF_FILE_PATH =  "/home/abijeet/pictures/";
const int DEF_CAP_HEIGHT = 1024;
const int DEF_CAP_WIDTH = 768;
const int DEF_CAP_IS_ON = 1;
const int DEF_CAP_IS_OFF = 0;
const bool DEF_CAP_IS_RANDOM = false;
#endif // CONSTANTS_H
