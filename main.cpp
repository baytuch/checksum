
#include <iostream>
#include "utils.h"


// find /home/pi/Downloads -type f -exec md5sum {} \; > md5sum.txt

int main() {
  bool status = false;
  std::vector<CheckSumPair> checksumlist;
  std::string sum;
  if (loadCheckSum(checksumlist)) {
    std::cout << "File containing checksums uploaded" << std::endl;
    status = true;
    for (const CheckSumPair checksumpair : checksumlist) {
      std::cout << "File check: " << checksumpair.path << std::endl;
      if (fileIsExist(checksumpair.path.c_str())) {
        if (fileCheckSum(checksumpair.path.c_str(), sum)) {
          if (sum == checksumpair.sum) {
            std::cout << "-> test passed!" << std::endl;
          } else {
            std::cout << "-> checksums do not match!" << std::endl;
            status = false;
          }
        } else {
          std::cout << "-> failure during test!" << std::endl;
          status = false;
        }
      } else {
        std::cout << "-> File not found - skiped" << std::endl;
      }
    }
  } else {
    std::cout << "Failure while loading a checksums file!" << std::endl;
  }
  std::cout << std::endl << std::endl;
  if (status) std::cout << "Everything is fine. Data is not corrupted!" << std::endl;
  else std::cout << "Warning: there were errors during the test!" << std::endl;
  return 0;
}
