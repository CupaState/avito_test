// local
#include "text_handler.h"

// std
#include <sstream>
#include <algorithm>

// Removes symbols excepting a-z and spaces
void TextHandler::filterText()
{
  std::string result = "";

  for (unsigned int i = 0; i < this->mText.size(); ++i)
    if (!(this->mText[i] >= 'a' && this->mText[i] <= 'z') && this->mText.at(i) != ' ')
      continue;
    else
      result += this->mText.at(i);

  this->mText = result;
}

// Casts all symbols to lower case
void TextHandler::toLower()
{
  for (unsigned int i = 0; i < this->mText.size(); ++i)
    this->mText[i] = ::tolower(this->mText[i]);
}

// Fills map with word and it`s quantity in text
std::map<std::string, unsigned int> TextHandler::fillMap()
{
  std::map<std::string, unsigned int> result;
  std::stringstream ss(this->mText);
  std::string word;

  while(std::getline(ss, word, ' '))
    if (!word.empty())
      result[word]++;
  return result;
}

// Sorts vector of pairs in DESCENDING
std::vector<std::pair<std::string, uint>> TextHandler::sortVectorDesc(std::map<std::string, uint>& m)
{
  std::vector<std::pair<std::string, uint>> result;

  for (auto it = m.begin(); it != m.end(); ++it)
    result.push_back(*it);

  std::sort(result.begin(), result.end(), [](const std::pair<std::string, uint> a, const std::pair<std::string, uint> b)
  {
    return a.second > b.second;
  });

  return result;
}

// Returns sorted frequencies of words, occurring in the text
std::vector<std::pair<std::string, uint>> TextHandler::getWordsFrequencies()
{
  this->toLower();
  this->filterText();
  std::map<std::string, unsigned int> m = this->fillMap();
  return this->sortVectorDesc(m);
}
