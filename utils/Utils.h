#ifndef UTILS_H
#define UTILS_H

#include <sys/stat.h>
#include <string>

inline bool fileExists(const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

#endif // UTILS_H