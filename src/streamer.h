/*
  Class to work with input output streams
*/

#pragma once

#include <string>
#include <vector>

typedef std::pair<std::string, unsigned int> strint_pair;

class FileStreamer
{
public:
  FileStreamer(const char* input_path, const char* output_path) : mInputPath(input_path), mOutputPath(output_path) {}
  ~FileStreamer() {}

  std::string readInputFile();
  void writeOutputFile(std::vector<strint_pair>&&);

private:
  const char* mInputPath;
  const char* mOutputPath;
};
