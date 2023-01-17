// local
#include "streamer.h"
#include "text_handler.h"

// std
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

  // object to handle files
  FileStreamer streamer(argv[1], argv[2]);
  std::string text;

  try
  {
    text = streamer.readInputFile();
  }
  catch (const std::exception& e)
  {
    printf("%s\n", e.what());
  }
  
  TextHandler tHandler(text);
  
  try
  {
    streamer.writeOutputFile(std::move(tHandler.getWordsFrequencies()));
  }
  catch (const std::exception& e)
  {
    printf("%s\n", e.what());
  }

  auto end = std::chrono::steady_clock::now();
  printf("PERFORMANCE: %ld seconds\n", std::chrono::duration_cast<std::chrono::seconds>(end - start).count()); 

  return 0;
}

// Usage message
void usage()
{
  printf("Usage: freq <path_to_input_file> <path_to_output_file>\n");
}
