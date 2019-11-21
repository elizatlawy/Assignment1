//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/json.hpp"
#include <vector>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Session::Session(const string& configFilePath){
    ifstream i(configFilePath);
    json Jsonfile;
    i >> Jsonfile;
    json moviesJson = Jsonfile["movies"];
    int id = 0;
    // inserts all movies form the Json file
    for (auto& currMovie : moviesJson.items()) {
        nlohmann::json movie = currMovie.value();
        Movie *newMovie = new Movie(id, movie["name"], movie["length"], movie["tags"]);
        content.push_back(newMovie);
        id++;
    }
    // inserts all series form the Json file
        json seriesJson = Jsonfile["series"];
        int seasonNumber = 1;
        for (auto& currSerie : seriesJson.items()) {
            nlohmann::json serie = currSerie.value();
            vector<int> seasons = serie["seasons]"];
            for (int seasonEpisodesNumber : seasons){
                for (int episodeNumber = 1; episodeNumber <= seasonEpisodesNumber; episodeNumber++){
                    Episode* newEpisode = new Episode(id, serie["name"], serie["episode_length"],seasonNumber,episodeNumber,serie["tags"]);
                    content.push_back(newEpisode);
                    id++;
                }
            }
            seasonNumber++;
    }

} // end of sessions constructor

Session::~Session() {}

void Session::start() {
    cout << "SPLFLIX is now on!";
}


