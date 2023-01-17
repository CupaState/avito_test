// local
#include "text_handler.h"

// std
#include <sstream>
#include <algorithm>
#include <chrono>

// Removes symbols excepting a-z and spaces
void TextHandler::filterText()
{
  auto start = std::chrono::steady_clock::now();
  std::string result = "";

  for (unsigned int i = 0; i < this->mText.size(); ++i)
    if (!(this->mText[i] >= 'a' && this->mText[i] <= 'z') && this->mText.at(i) != ' ')
      continue;
    else
      result += this->mText.at(i);

  this->mText.assign(result);

  auto end = std::chrono::steady_clock::now();
  printf("filterText: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
}

// Casts all symbols to lower case
void TextHandler::toLower()
{
  auto start = std::chrono::steady_clock::now();

  for (unsigned int i = 0; i < this->mText.size(); ++i)
    this->mText[i] = ::tolower(this->mText[i]);

  auto end = std::chrono::steady_clock::now();
  printf("toLower: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
}

// Fills map with word and it`s quantity in text
std::unordered_map<std::string, unsigned int> TextHandler::fillMap()
{
  auto start = std::chrono::steady_clock::now();

  std::unordered_map<std::string, unsigned int> result;
  std::stringstream ss(this->mText);
  std::string word;

  while(std::getline(ss, word, ' '))
    if (!word.empty())
      result[word]++;

  auto end = std::chrono::steady_clock::now();
  printf("fillMap: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
  return result;
}

// Sorts vector of pairs in DESCENDING
std::vector<std::pair<std::string, uint>> TextHandler::sortVectorDesc(std::unordered_map<std::string, uint>& m)
{
  std::vector<std::pair<std::string, uint>> result;

  auto start = std::chrono::steady_clock::now();

  for (auto it = m.begin(); it != m.end(); ++it)
    result.push_back(*it);

  std::sort(result.begin(), result.end(), [](const std::pair<std::string, uint> a, const std::pair<std::string, uint> b)
  {
    return a.second > b.second;
  });

  auto end = std::chrono::steady_clock::now();
  printf("sortVectorDesc: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());

  return result;
}

// Returns sorted frequencies of words, occurring in the text
std::vector<std::pair<std::string, uint>> TextHandler::getWordsFrequencies()
{
  this->toLower();
  this->filterText();
  std::unordered_map<std::string, unsigned int> m = this->fillMap();
  return this->sortVectorDesc(m);
}
