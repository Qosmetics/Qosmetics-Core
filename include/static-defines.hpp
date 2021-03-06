#pragma once
#include "beatsaber-hook/shared/utils/utils-functions.h"
#define BASEPATH            "/sdcard/ModData/com.beatgames.beatsaber/Mods/Qosmetics/"

#define SABERPATH           string_format("%s%s", BASEPATH, "sabers/")
#define SABEREXT            "qsaber"

#define NOTEPATH            string_format("%s%s", BASEPATH, "notes/")
#define NOTEEXT             "qbloq"

#define WALLPATH            string_format("%s%s", BASEPATH, "walls/")
#define WALLEXT             "qwall"

#define UIPATH              string_format("%s/%s", BASEPATH, "UI/")
#define CONFIGPATH              string_format("%s/%s", BASEPATH, "Configs/")

#define DESCRIPTORCACHE     string_format("%s/%s", BASEPATH, "DescriptorCache")
#define CREATORCACHE        string_format("%s/%s", BASEPATH, "CreatorCache")