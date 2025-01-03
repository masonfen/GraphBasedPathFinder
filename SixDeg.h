#ifndef SIXDEGREES_H
#define SIXDEGREES_H


#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

//hash structure to handle pairs of strings
struct PairHash {
  std::size_t operator()(const std::pair<std::string, std::string>& pair) const;
};


std::vector<std::string> tokenizeLine(const std::string& input);

class SixDegreesGraph {
  public: //PUBLIC
    SixDegreesGraph(const std::string& movieListfile);

    std::string getShortestPath(const std::string& actorStart, const std::string& actorEnd) const;

  private: //PRIVATE
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyList;

    std::unordered_map<std::pair<std::string, std::string>, std::vector<std::string>, PairHash> movieConnections;

    bool performBFS(const std::string& start, const std::string& end, std::unordered_map<std::string, std::string>& predecessors, std::unordered_map<std::string, std::string>& connectingMovies) const;

};

#endif