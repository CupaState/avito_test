/*
  Class to work with input output streams
*/

#pragma once

#include <string>
#include <vector>
#include <map>

typedef std::pair<std::string, unsigned int> strint_pair;

class FileStreamer
{
public:
  FileStreamer(const char* input_path, const char* output_path) : mInputPath(input_path), mOutputPath(output_path) {}
  ~FileStreamer() {}

  std::string readInputFile();
  void writeOutputFile(std::map<unsigned int, std::string>&&);

private:
  const char* mInputPath;
  const char* mOutputPath;
};
