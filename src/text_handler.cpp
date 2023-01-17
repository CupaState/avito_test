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
  {
    const char ch = this->mText[i];
    if (!(ch >= 'a' && ch <= 'z') && ch != ' ')
      continue;
    result += ch;
  }

  this->mText.assign(result);

  auto end = std::chrono::steady_clock::now();
  printf("filterText: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
}

// Casts all symbols to lower case
void TextHandler::toLower()
{
  auto start = std::chrono::steady_clock::now();

  for (unsigned int i = 0; i < this->mText.size(); ++i)
    this->mText[i] |= 0x20;

  auto end = std::chrono::steady_clock::now();
  printf("toLower: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
}

// Fills map with word and it`s quantity in text
std::unordered_map<std::string, unsigned int> TextHandler::fillMap()
{
  auto start = std::chrono::steady_clock::now();

  std::unordered_map<std::string, unsigned int> result;
  std::istringstream ss(this->mText);
  std::string word;

  while(std::getline(ss, word, ' '))
    if (!word.empty())
      result[word]++;

  auto end = std::chrono::steady_clock::now();
  printf("fillMap: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
  return result;
}

// Sorts vector of pairs in DESCENDING
std::map<unsigned int, std::string> TextHandler::sortVectorDesc(std::unordered_map<std::string, unsigned int>&& m)
{
  std::map<unsigned int, std::string> result;
  auto start = std::chrono::steady_clock::now();

  for (auto& el : m)
    result.emplace(el.second, el.first);

  auto end = std::chrono::steady_clock::now();
  printf("sortVectorDesc: %ld\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());

  return result;
}

// Returns sorted frequencies of words, occurring in the text
std::map<unsigned int, std::string> TextHandler::getWordsFrequencies()
{
  this->toLower();
  this->filterText();
  return this->sortVectorDesc(std::move(this->fillMap()));
}
