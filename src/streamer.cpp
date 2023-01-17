// local
#include "streamer.h"

// std
#include <fstream>
#include <string>
#include <chrono>

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
  void* mmapres;
  const char* mapped;
  
  int fd = open(this->mInputPath, O_RDONLY);
  if (fd < 0)
    throw openException;

  if (fstat(fd, & s) < 0)
    throw "fstat()";

  mmapres = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (mmapres == MAP_FAILED)
    throw "mmap()";

  if (close(fd) < 0)
    throw closeException;

  return (const char*) mmapres;
}

// Writes result to output file
void FileStreamer::writeOutputFile(std::vector<strint_pair>&& v)
{
  auto start = std::chrono::steady_clock::now();
  std::ofstream out(this->mOutputPath);
  std::string exception = std::string("Couldn`t open output file: ") + this->mOutputPath;

  if (!out.is_open())
    throw exception;

  for (auto it = v.begin(); it != v.end(); ++it)
    out << it->second << " " << it->first << "\n";

  out.close();

  auto end = std::chrono::steady_clock::now();
  printf("WRITE FILE: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
}

