#ifndef CSV_H
#define CSV_H
#include <vector>
#include <string>
#include "types.h"
void saveCSV(const std::string& filename,const std::vector<Measurement>& results);
#endif