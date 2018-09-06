#include <SD.h>
#include <SPI.h>

#include "const.h"

struct PathSDInfo;
extern PathSDInfo cleanSD_(PathSDInfo);
extern String cleanSD(int = SD_PIN, String = ROOT);
extern PathSDInfo listSD_(PathSDInfo);
extern String listSD(int = SD_PIN, String = ROOT);
