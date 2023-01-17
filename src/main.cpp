// local
#include "streamer.h"
#include "text_handler.h"

// std
#include <iostream>
#include <exception>
#include <chrono>

void usage();

int main(int argc, char* argv[]) 
{
  if (argc < 3)
  {
    usage();
    return -1;
  }

  auto start = std::chrono::steady_clock::now();

  setlocale(LC_ALL, NULL);

  // object to handle files
  FileStreamer streamer(argv[1], argv[2]);
  std::string text;

  try
  {
    text = streamer.readInputFile();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
  TextHandler tHandler(text);
  
  try
  {
    streamer.writeOutputFile(std::move(tHandler.getWordsFrequencies()));
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  auto end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "\n";

  return 0;
}

// Usage message
void usage()
{
  std::cout << "Usage: freq <path_to_input_file> <path_to_output_file>\n";
}
