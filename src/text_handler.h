/*
  Class to work with text
*/

#pragma once

// std
#include <vector>
#include <map>
#include <string>

class TextHandler
{
public:
  TextHandler(const std::string text) : mText(text) {}
  ~TextHandler() {}

  std::vector<std::pair<std::string, uint>> getWordsFrequencies();  

private:
  // methods
  void filterText();
  void toLower();
  std::map<std::string, uint> fillMap();
  std::vector<std::pair<std::string, uint>> sortVectorDesc(std::map<std::string, uint>&);

  // props
  std::string mText;
};
