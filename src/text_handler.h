/*
  Class to work with text
*/

#pragma once

// std
#include <vector>
#include <unordered_map>
#include <map>
#include <string>

class TextHandler
{
public:
  TextHandler(const std::string text) : mText(text) {}
  ~TextHandler() {}

  std::map<unsigned int, std::string> getWordsFrequencies();  

private:
  // methods
  void filterText();
  void toLower();
  std::unordered_map<std::string, unsigned int> fillMap();
  std::map<unsigned int, std::string> sortVectorDesc(std::unordered_map<std::string, unsigned int>&);

  // props
  std::string mText;
};
