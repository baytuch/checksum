
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "md5.h"
#include "utils.h"


bool fileIsExist(const char *path) {
  bool res = false;
  FILE *fd;
  fd = fopen(path, "r");
  if (fd != NULL) {
    res = true;
    fclose(fd);
  }
  return res;
}

bool fileCheckSum(const char *path, std::string &sum) {
  const int buff_size = 1024;
  sum.clear();
  bool res = false;
  int c;
  int buff_n = 0;
  uint8_t buff[buff_size];
  MD5 md5;
  memset(buff, 0x00, (size_t) buff_size);
  FILE *fd;
  fd = fopen(path, "r");
  if (fd != NULL) {
    while (true) {
      c = fgetc(fd);
      if (c != EOF) {
        buff[buff_n] = (uint8_t) c;
        buff_n++;
      }
      if (buff_n >= buff_size || c == EOF) {
        md5.update(buff, buff_n);
        if (!res && buff_n > 0) res = true;
        memset(buff, 0x00, (size_t) buff_size);
        buff_n = 0;
      }
      if (c == EOF) break;
    }
    if (res) {
      md5.finalize();
      sum = md5.toString();
    }
    fclose(fd);
  }
  return res;
}

bool loadCheckSum(std::vector<CheckSumPair> &checksumlist) {
  const char *md5sum_file_name = "md5sum.txt";
  const char end_sub = '\n';
  const size_t sum_lenght = 32;
  checksumlist.clear();
  int c;
  std::string buff;
  CheckSumPair data;
  FILE *fd;
  fd = fopen(md5sum_file_name, "r");
  if (fd != NULL) {
    while (true) {
      c = fgetc(fd);
      if (c != EOF) {
        char sub_target = (char) c;
        if (sub_target != end_sub) {
          buff += sub_target;
        } else {
          bool status = false;
          data = {"", ""};
          data.sum = buff.substr(0, sum_lenght);
          for (const char sum_sub : data.sum) {
            if ((sum_sub >= 0x30 && sum_sub <= 0x39) ||
                (sum_sub >= 0x41 && sum_sub <= 0x46) ||
                (sum_sub >= 0x61 && sum_sub <= 0x66)) {
              status = true;
            }
          }
          if (status) {
            data.path = buff.substr(sum_lenght + 2);
            checksumlist.push_back(data);
          } else {
            checksumlist.clear();
            break;
          }
          buff.clear();
        }
      } else {
        break;
      }
    }
    fclose(fd);
  }
  if (checksumlist.size() > 0) return true;
  else return false;
}
