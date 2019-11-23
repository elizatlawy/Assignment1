
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/Action.h"
#include <bits/stdc++.h>
#include <unordered_map>
#include <fstream>
#include "iostream"


using namespace std;
using json = nlohmann::json;

// constructor
Session::Session(const string& configFilePath){
    // construct content file
    ifstream i(configFilePath);
    json jsonFile = json::parse(i);
    insertMovies(jsonFile);
    // TODO: insert Next Episode id!!!
    insertSeries(jsonFile);
    activeUser = new LengthRecommenderUser("default");
    userMap.insert(make_pair("default",activeUser));

} // end of sessions constructor

// copy constructor
Session::Session(const Session &other) {

//    for(auto& currContent : other.content)
//        content.push_back(new Movie(currContent);
//    for(auto& currActionLog : other.actionsLog)
//        actionsLog.push_back(currActionLog);
    // need to complete userMap + activeUser.


}




Session::~Session()
{
}

void Session::start() {
    cout << "SPLFLIX is now on!" << endl;
    getline(cin,lastUserInput);
        while (lastUserInput != "exit"){
            std::istringstream iss(lastUserInput);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                             std::istream_iterator<std::string>());
            userInputVector = results;
            // all action options
            // TODO: Change all if to work with the VectorInput!!
            if(lastUserInput.rfind("createuser", 0) == 0){
                CreateUser *createUserAction = new CreateUser();
                createUserAction->act(*this);
            }
            else if(lastUserInput.rfind("log", 0) == 0){
                PrintActionsLog *PrintActionLogAction = new PrintActionsLog();
                PrintActionLogAction->act(*this);
            }
            else if(lastUserInput.rfind("content", 0) == 0) {
                PrintContentList *PrintContentListAction = new PrintContentList();
                PrintContentListAction->act(*this);
                }

            getline(cin,lastUserInput);
            }
        }


// ################ Helper functions #################

// Getters
const vector<Watchable *> &Session::getContent() const {
    return content;
}

const vector<BaseAction *> &Session::getActionsLog() const {
    return actionsLog;
}

const unordered_map<std::string, User *> &Session::getUserMap() const {
    return userMap;
}

User *Session::getActiveUser() const {
    return activeUser;
}

const string &Session::getLastUserInput() const {
    return lastUserInput;
}

void Session::addActionLog(BaseAction *newAction) {
    actionsLog.push_back(newAction);
}

void Session::addUser(User &toAddUser) {
    userMap.insert(make_pair(toAddUser.getName(),&toAddUser));
}

const vector<std::string> &Session::getUserInputVector() const {
    return userInputVector;
}


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



