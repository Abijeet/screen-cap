#ifndef CONSTANTS_H
#define CONSTANTS_H

#define JPG_FORMAT 1
#define PNG_FORMAT 2

const QString APPLICATION_NAME = "screen_cap";
const QString ORGANIZATION_NAME = "Osmosys";

const QString FOLDER_DATE_FORMAT = "yyyy_MM_dd";
const QString FILE_DATE_FORMAT = "yyyy_MM_dd_HH_mm_ss";
const QString FILE_LOG_DATE_FORMAT = "yyyy-MM-dd HH:mm:ss";

const int MIN_DIMENSION_HEIGHT = 30;
const QString DLG_FONT_FAMILY = "Monospace";

// Image formats.
const QList<QString> IMG_FORMATS = QList<QString>() << "jpg" << "png";
const QList<int> IMG_FORMAT_KEYS = QList<int>() << JPG_FORMAT << PNG_FORMAT;

// Image Quality
const QList<int> IMG_QUALITY = QList<int>() << 100 << 80 << 60 << 50 << 40 << 30;
const QList<QString> IMG_QUALITY_NAME = QList<QString>() << "100%" << "80%" << "60%" << "50%" << "40%" << "30%";

// Setting keys
const QString CAP_TIME = "capture_time";
const QString FILE_PATH =  "file_path";
const QString CAP_DIMENSIONS = "capture_dimensions";
const QString CAP_IS_ON = "is_capturing";
const QString CAP_IS_RANDOM = "is_cap_random";
const QString MINIMIZE_TO_TRAY = "minimize_to_true";
const QString START_MINIMIZED = "start_minimized";
const QString CAP_STARTUP = "capture_startup";
const QString CAP_IMG_FORMAT = "img_format";
const QString CAP_IMG_QUALITY = "img_quality";

// Setting default values
const int DEF_CAP_TIME = 90;
const QString DEF_FILE_PATH =  "/home/abijeet/pictures/";
const int DEF_CAP_DIMENSIONS = 100;
const int DEF_CAP_IS_ON = 1;
const int DEF_CAP_IS_OFF = 0;
const bool DEF_CAP_IS_RANDOM = false;
const bool DEF_MINIMIZE_TO_TRAY = false;
const bool DEF_START_MINIMIZED = false;
const bool DEF_CAP_STARTUP = false;
const int DEF_IMG_FORMAT = JPG_FORMAT;
const int DEF_IMG_QUALITY = 50;
#endif // CONSTANTS_H
