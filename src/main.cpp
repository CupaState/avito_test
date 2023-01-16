// local
#include "streamer.h"
#include "text_handler.h"

#include <iostream>
#include <exception>

void usage();

int main(int argc, char* argv[]) 
{
  if (argc < 3)
  {
    usage();
    return -1;
  }

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

  return 0;
}

// Usage message
void usage()
{
  std::cout << "Usage: freq <path_to_input_file> <path_to_output_file>\n";
}
