
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include <vector>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Session::Session(const string& configFilePath){
    // construct content file
    ifstream i(configFilePath);
    json jsonFile = json::parse(i);
    insertMovies(jsonFile);
    insertSeries(jsonFile);




} // end of sessions constructor


// inserts all movies form the Json file
void Session::insertMovies(json &jsonFile) {
    json moviesJson = jsonFile["movies"];
    int id = content.size();
    for (auto& currMovie : moviesJson.items()) {
        json movie = currMovie.value();
        Movie *newMovie = new Movie(id, movie["name"], movie["length"], movie["tags"]);
        content.push_back(newMovie);
        id++;
    }
}

// inserts all series form the Json file
void Session::insertSeries(json &jsonFile) {
    json seriesJson = jsonFile["tv_series"];
    int id = content.size();
    for (auto &currSerie : seriesJson.items()) {
        int seasonNumber = 1;
        json serie = currSerie.value();
        vector<int> seasons = serie["seasons"];
        for (int seasonEpisodesNumber : seasons) { // for each season
            for (int episodeNumber = 1; episodeNumber <= seasonEpisodesNumber; episodeNumber++) { // for each episode
                Episode *newEpisode = new Episode(id, serie["name"], serie["episode_length"], seasonNumber,
                                                  episodeNumber, serie["tags"]);
                content.push_back(newEpisode);
                id++;
            }
            seasonNumber++;
        }
    }
}

    Session::~Session()
    {
    }

    void Session::start() {
        cout << "SPLFLIX is now on!" << endl;
        for(auto& x : content){
            cout << x->toString() << endl;
        }
    }



