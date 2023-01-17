// local
#include "streamer.h"

// std
#include <fstream>
#include <map>
#include <iostream>
#include <string>

// Reads input file
std::string FileStreamer::readInputFile()
{
  const std::string openException = std::string("Couldn`t open input file: ") + this->mInputPath;
  const std::string closeException = std::string("Couldn`t close input file: ") + this->mInputPath;

  std::string result;
  std::map<char*, uint> res;
  
  FILE* in = fopen(this->mInputPath, "r");
  if (!in)
    throw openException;

  while(true)
  {
    char word[30];
    if (fscanf(in, " %30s", word) != 1)
      break;
    //puts(word);
    //printf("%s\n", word);
    res.insert(std::make_pair<char*, uint>(word, res[word]++));
  }

  //for (auto& el : res)
  std::cout << res.size() << "\n";

  if (fclose(in) == -1)
    throw closeException;
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

