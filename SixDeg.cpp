#include "sixdegrees.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <stdexcept>


//implement hash function for a pair of strings
std::size_t PairHash::operator()(const std::pair<std::string, std::string>& pair) const{
  return std::hash<std::string>()(pair.first) ^ (std::hash<std::string>()(pair.second) << 1);

}

//split a string into tokens seperated by a white space
std::vector<std::string> tokenizeLine(const std::string& input) {
  std::vector<std::string> tokens;
  std::istringstream stream(input);
  std::string token;
  while (stream >> token) {
    tokens.emplace_back(token);
  }
  return tokens;
}

//build the graph from the inpuit file
SixDegreesGraph::SixDegreesGraph(const std::string& movieListFile){
  std::ifstream infile(movieListFile);

  if(!infile.is_open()){
    throw std::runtime_error("cant open movie list file" + movieListFile);
  }

  std::string currentLine;
  while (std::getline(infile, currentLine)) {
    auto tokens = tokenizeLine(currentLine);
    if (tokens.size() < 2) continue; //skip invalid lines
    std::string movie = tokens[0];
    std::vector<std::string> actors(tokens.begin() + 1, tokens.end());

    //connect each pair of actors and map them to their cooresponding movie
    for(size_t i = 0; i < actors.size(); ++i) {
      for(size_t j = i + 1; j < actors.size(); ++j) {
        const std::string& actorA = actors[i];
        const std::string& actorB = actors[j];

        //update adjacency list
        adjacencyList[actorA].insert(actorB);
        adjacencyList[actorB].insert(actorA);

        //ensure consistent ordering for pair
        std::pair<std::string, std::string> actorPair = (actorA < actorB) ? std::make_pair(actorA, actorB) : std::make_pair(actorB, actorA);

        //map actor pair to connecting movie
        movieConnections[actorPair].push_back(movie);
      }
    }
  }
  infile.close();
}



//BFS to find shortest path
bool SixDegreesGraph::performBFS(const std::string& start, const std::string& end, std::unordered_map<std::string, std::string>& predecessors,std::unordered_map<std::string, std::string>& connectingMovies) const {
  if(adjacencyList.find(start) == adjacencyList.end() ||adjacencyList.find(end) == adjacencyList.end()){
    return false;
  }

  std::queue<std::string> searchQueue;
  std::unordered_set<std::string> visited;

  searchQueue.push(start);
  visited.insert(start);
  predecessors[start] = ""; //start has no predecessors

  while (!searchQueue.empty()) {
    std::string currentActor = searchQueue.front();
    searchQueue.pop();

    for (const auto& neighbor : adjacencyList.at(currentActor)) {
      if (visited.find(neighbor) == visited.end()){
        visited.insert(neighbor);
        predecessors[neighbor] = currentActor;


        //determine the movie connecting curr actor and neighbor
        std::pair<std::string, std::string> actorPair = (currentActor < neighbor) ? std::make_pair(currentActor, neighbor) : std::make_pair(neighbor, currentActor);

        auto movieIt = movieConnections.find(actorPair);
        if (movieIt != movieConnections.end() && !movieIt->second.empty()){
          connectingMovies[neighbor] = movieIt->second[0];
        } else {
          connectingMovies[neighbor] = "Unknown";
        }

        searchQueue.push(neighbor);

        if(neighbor == end){
          return true; //PATH HAS BEEN FOUND yay
        }
      }
    }
  }
  return false; //no path found
}


std::string SixDegreesGraph::getShortestPath(const std::string& actorStart, const std::string& actorEnd) const {
  if (actorStart == actorEnd) {
    return actorStart;
  }

  std::unordered_map<std::string, std::string> predecessors;
  std::unordered_map<std::string, std::string> connectingMovies;

  bool pathExists = performBFS(actorStart, actorEnd, predecessors, connectingMovies);

  if(!pathExists){
    return "Not present";
  }

  //reconstruct the path from end to start
  std::vector<std::string> path;
  std::string current = actorEnd;
  while(current != actorStart) {
    path.emplace_back(current);
    current = predecessors[current];
    if(current.empty()){
      break; //just in case
    }
}
  path.emplace_back(actorStart);

  //reverse path to get from start to end
  std::reverse(path.begin(), path.end());

  //build output string w required format
  std::string output = path[0];
  for (size_t i = 1; i < path.size(); ++i){
    output += " -(" + connectingMovies[path[i]] + ")- " + path[i];
  }

  return output;
}