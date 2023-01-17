// local
#include "text_handler.h"

// std
#include <sstream>

static const int size = 10000000;


// Removes symbols excepting a-z and spaces
void TextHandler::filterText()
{
  std::string result = "";
  result.reserve(size * 100);

  for (unsigned int i = 0; i < this->mText.size(); ++i)
  {
    const char ch = this->mText[i];
    if (!(ch >= 'a' && ch <= 'z') && ch != ' ')
      continue;
    result += ch;
  }

  this->mText.assign(result);
}

// Casts all symbols to lower case
void TextHandler::toLower()
{
  for (unsigned int i = 0; i < this->mText.size(); ++i)
    this->mText[i] |= 0x20;
}

// Fills map with word and it`s quantity in text
std::unordered_map<std::string, unsigned int> TextHandler::fillMap()
{
  std::unordered_map<std::string, unsigned int> result;
  result.reserve(std::move(size));

  std::istringstream ss(this->mText);
  std::string word;

  while(std::getline(ss, word, ' '))
  {
    if (word.empty())
      continue;
    result[word]++;
  }

  return result;
}

// Sorts vector of pairs in DESCENDING ORDER
std::map<unsigned int, std::string> TextHandler::sortDesc(std::unordered_map<std::string, unsigned int>&& m)
{
  std::map<unsigned int, std::string> result;
  for (auto& el : m)
    result.emplace(el.second, el.first);
  return result;
}

// Returns sorted frequencies of words, occurring in the text
std::map<unsigned int, std::string> TextHandler::getWordsFrequencies()
{
  this->toLower();
  this->filterText();
  return this->sortDesc(std::move(this->fillMap()));
}
