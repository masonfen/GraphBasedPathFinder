#include "sixdegrees.h"
#include <iostream>

#include <fstream>




int main(int argc, char* argv[]){
  if (argc != 3){
    std::cerr <<"Use by typing: ./sixdegrees <input_file> <output_file>"<<std::endl;
    return 1;
  }

  std::string input_file(argv[1]);
  std::string output_file(argv[2]);
  std::string movieListFile = "cleaned_movielist.txt";
  
  try{
    //intialize graph
    SixDegreesGraph graph(movieListFile);

    //open input and output files
    std::ifstream queries(input_file);
    if (!queries.is_open()) {               //input
      std::cerr << "err" << std::endl;
      return 1;
    }
    //open out results file for writing
    std::ofstream results(output_file);
    if (!results.is_open()) {
      std::cerr << "err" << std::endl;        //output
      return 1;
    }


    std::string line;
    //process eahc line from input file
    while (std::getline(queries, line)) {
      auto tokens = tokenizeLine(line);
      if (tokens.size() != 2) {
        results << "Not present" << std::endl;
        continue;
      }

      std::string actor1 = tokens[0];
      std::string actor2 = tokens[1];
      //find shortest path between 2 actors
      std::string path = graph.getShortestPath(actor1, actor2);
      //write result to output file
      results << path << std::endl;

    }


    queries.close();
    results.close();
  }
  catch (const std::exception& e) {
    //catch and display any exceptions during execution -->stackoverflow
    std::cerr << "exception: " <<e.what() << std::endl;
    return 1;
  }
    return 0;
}

