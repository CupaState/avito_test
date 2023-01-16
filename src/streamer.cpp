// local
#include "streamer.h"

// std
#include <fstream>

// Reads input file
std::string FileStreamer::readInputFile()
{
  std::string exception = std::string("Couldn`t open input file: ") + this->mInputPath;
  std::string result;
  
  std::ifstream input(this->mInputPath);
  if (!input.is_open())
    throw exception;

  result.assign((std::istreambuf_iterator<char>(input.rdbuf())), std::istreambuf_iterator<char>());


  input.close();
  return result;
}

// Writes result to output file
void FileStreamer::writeOutputFile(std::vector<strint_pair>&& v)
{
  std::ofstream out(this->mOutputPath);
  std::string exception = std::string("Couldn`t open output file: ") + this->mOutputPath;

  if (!out.is_open())
    throw exception;

  for (auto it = v.begin(); it != v.end(); ++it)
    out << it->second << " " << it->first << "\n";

  out.close();
}

