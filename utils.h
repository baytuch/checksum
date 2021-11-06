
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdint.h>
#include <string>
#include <vector>

struct CheckSumPair {
  std::string path;
  std::string sum;
};

bool fileIsExist(const char *path);
bool fileCheckSum(const char *path, std::string &sum);
bool loadCheckSum(std::vector<CheckSumPair> &CheckSumPair);

#endif // UTILS_H_INCLUDED
