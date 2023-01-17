// local
#include "streamer.h"

// std
#include <fstream>

// posix
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Reads input file
std::string FileStreamer::readInputFile()
{
  const std::string openException = std::string("Couldn`t open input file: ") + this->mInputPath;
  const std::string closeException = std::string("Couldn`t close input file: ") + this->mInputPath;
  
  struct stat s;
  void* mapped;
  
  int fd = open(this->mInputPath, O_RDONLY);
  if (fd < 0)
    throw openException;

  if (fstat(fd, & s) < 0)
    throw "fstat()";

  mapped = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (mapped == MAP_FAILED)
    throw "mmap()";

  if (close(fd) < 0)
    throw closeException;

  return (const char*) mapped;
}

// Writes result to output file
void FileStreamer::writeOutputFile(std::map<unsigned int, std::string>&& v)
{
  std::ofstream out(this->mOutputPath);
  std::string exception = std::string("Couldn`t open output file: ") + this->mOutputPath;

  if (!out.is_open())
    throw exception;

  // write in descending order
  for (auto it = v.crbegin(); it != v.crend(); ++it)
    out << it->first << " " << it->second << "\n";

  out.close();
}

