
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/Action.h"
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <iostream>


using namespace std;
using json = nlohmann::json;

// constructor
Session::Session(const string& configFilePath){
    // construct content file
    ifstream i(configFilePath);
    json jsonFile = json::parse(i);
    insertMovies(jsonFile);
    insertSeries(jsonFile);
    userMap.insert(make_pair("default",new LengthRecommenderUser("default")));
    activeUser = userMap.at("default");
}
// copy constructor
Session::Session(const Session &other) {
// TODO: check if we pass value or reference
    for(Watchable* currContent : other.content)
        content.push_back(currContent->clone());
    for(BaseAction* currAction : other.actionsLog)
         actionsLog.push_back(currAction->clone());
    for (pair<const basic_string<char>, User *> currUserPair : other.userMap)
        userMap.insert(make_pair(currUserPair.first,currUserPair.second->clone()));
    activeUser = other.activeUser->clone();
}
//move constructor
Session::Session(Session &&other) {
    CopySessResources(other);
    other.content.clear();
    other.actionsLog.clear();
    other.userMap.clear();
    delete other.activeUser;
}
// destructor
Session::~Session(){
    deleteSessResources();
}
// copy assignment
Session& Session::operator=(const Session &other) {
    // check for self assignment
    if (this == &other)
        return  *this;
    // first destroy old resources
    deleteSessResources();
    // copy resources of other
    CopySessResources(other);
}
//  move assignment
Session& Session::operator=(Session &&other) {
    // first destroy old resources
    deleteSessResources();
    // copy resources of other
    CopySessResources(other);
    // delete resources from other
    other.deleteSessResources();
}

void Session::deleteSessResources() {
    for (pair<const basic_string<char>, User *> currUserPair : userMap)
        delete currUserPair.second;
    for(Watchable* currContent : content)
        delete currContent;
    for(BaseAction* currAction : actionsLog)
        delete currAction;
    userInputVector.clear();
}
void Session::CopySessResources(const Session &other) {
    for(Watchable* currContent : other.content)
        content.push_back(currContent);
    for(BaseAction* currAction : other.actionsLog)
        actionsLog.push_back(currAction);
    for (pair<const basic_string<char>, User *> currUserPair : other.userMap)
        userMap.insert(make_pair(currUserPair.first,currUserPair.second));
    activeUser = other.activeUser;
}


void Session::start() {
    cout << "SPLFLIX is now on!" << endl;
    // TODO: DELETE latInputUser for session class
    // TODO: CREATE ALL THE ACTION OBJECTS ONLY ONCE BEFORE THE WHILE.
    // create all possible action objects
    getline(cin,lastUserInput);
        while (lastUserInput != "exit"){
            std::istringstream iss(lastUserInput);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                             std::istream_iterator<std::string>());
            userInputVector = results;
            // all action options
            if(userInputVector[0] == "createuser"){
                CreateUser *createUserAction = new CreateUser();
                createUserAction->act(*this);
            }
            else if(userInputVector[0] == "changeuser") {
                ChangeActiveUser *ChangeActiveUserAction = new ChangeActiveUser();
                ChangeActiveUserAction->act(*this);
            }
            else if(userInputVector[0] == "deleteuser") {
                DeleteUser *DeleteUserAction = new DeleteUser();
                DeleteUserAction->act(*this);
            }
            else if(userInputVector[0] == "dupuser") {
                DuplicateUser *DuplicateUserAction = new DuplicateUser();
                DuplicateUserAction->act(*this);
            }
            else if(userInputVector[0] == "log"){
                PrintActionsLog *PrintActionLogAction = new PrintActionsLog();
                PrintActionLogAction->act(*this);
                delete PrintActionLogAction;
            }
            else if(userInputVector[0] == "content") {
                PrintContentList *PrintContentListAction = new PrintContentList();
                PrintContentListAction->act(*this);
                }
            else if(userInputVector[0] == "watchhist") {
                PrintWatchHistory *PrintWatchHistoryAction = new PrintWatchHistory();
                PrintWatchHistoryAction->act(*this);
            }
            else if(userInputVector[0] == "watch") {
                Watch *WatchAction = new Watch();
                WatchAction->act(*this);
                delete WatchAction;
            }
            else{
                cout << "Illegal Command, Please Try Again" << endl;
            }
            getline(cin,lastUserInput);
            } // end of while

        Exit *exitAction = new Exit();
        exitAction->act(*this);
        }


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

// ################ Helper functions #################

void Session::addUser(User &toAddUser) {
    userMap.insert(make_pair(toAddUser.getName(),&toAddUser));
}

const vector<std::string> &Session::getUserInputVector() const {
    return userInputVector;
}

void Session::setActiveUser(User &activeUser) {
    Session::activeUser = &activeUser;
}

void Session::addActionLog(BaseAction &newAction) {
    actionsLog.push_back(&newAction);
}

void Session::addToCurrentUserHistory(int id) {
    activeUser->addToHistory(*content[id]);
}



// inserts all movies form the Json file
void Session::insertMovies(json &jsonFile) {
    json moviesJson = jsonFile["movies"];
    int id = content.size()+1;
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
    int id = content.size()+1;
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

void Session::removeUser(std::string& userName) {
    userMap.erase(userName);
}




