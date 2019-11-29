
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Action.h"
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <iostream>


using namespace std;
using json = nlohmann::json;

// constructor
Session::Session(const string &configFilePath) : content(), actionsLog(), userMap(), activeUser(), userInputVector() {
    // construct content file
    ifstream i(configFilePath);
    json jsonFile = json::parse(i);
    insertMovies(jsonFile);
    insertSeries(jsonFile);
    userMap.insert(make_pair("default", new LengthRecommenderUser("default")));
    activeUser = userMap.at("default");
}

// copy constructor
Session::Session(const Session &other) : content(), actionsLog(), userMap(), activeUser(), userInputVector() {
    copySessResources(other);
}

//move constructor
Session::Session(Session &&other) : content(), actionsLog(), userMap(), activeUser(), userInputVector() {
    // copy resources of other
    stealSessResources(other);
    // delete the references of other
}

// destructor
Session::~Session() {
    deleteSessResources();
}

// copy assignment
Session &Session::operator=(Session &other) {
    // check for self assignment
    if (this == &other)
        return *this;
    // first destroy old resources
    deleteSessResources();
    // copy resources of other
    copySessResources(other);
    return *this;
}

//  move assignment
Session &Session::operator=(Session &&other) {
    // first destroy old resources
    deleteSessResources();
    // copy resources of other
    stealSessResources(other);
    // delete the references of other
    other.content.clear();
    other.actionsLog.clear();
    other.userMap.clear();
    other.activeUser = nullptr;
    return *this;
}

void Session::deleteSessResources() {
    for (const pair<const basic_string<char>, User *> &currUserPair : userMap) {
        delete currUserPair.second;
    }
    userMap.clear();
    for (Watchable *currContent : content)
        delete currContent;
    content.clear();
    for (BaseAction *currAction : actionsLog)
        delete currAction;
    actionsLog.clear();
    userInputVector.clear();
}

// copy others references
void Session::stealSessResources(const Session &other) {
    for (Watchable *currContent : other.content)
        content.push_back(currContent);
    for (BaseAction *currAction : other.actionsLog)
        actionsLog.push_back(currAction);
    for (const pair<const basic_string<char>, User *> &currUserPair : other.userMap)
        userMap.insert(make_pair(currUserPair.first, currUserPair.second));
    activeUser = other.activeUser;
    // clear other pointers

}

void Session::copySessResources(const Session &other) {
    for (Watchable *currContent : other.content)
        content.push_back(currContent->clone());
    for (BaseAction *currAction : other.actionsLog)
        actionsLog.push_back(currAction->clone());
    for (pair<const basic_string<char>, User *> currUserPair : other.userMap)
        userMap.insert(make_pair(currUserPair.first, currUserPair.second->clone(*this)));
    activeUser = userMap.at(other.getActiveUser()->getName());
}

void Session::start() {
    cout << "SPLFLIX is now on!" << endl;
    string lastUserInput;
    getline(cin, lastUserInput);
    while (lastUserInput != "exit") {
        // split the lastUserInput into vector by words
        std::istringstream iss(lastUserInput);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        userInputVector = results;
        // all action options
        if (userInputVector[0] == "createuser") {
            CreateUser *createUserAction = new CreateUser();
            createUserAction->act(*this);
        } else if (userInputVector[0] == "changeuser") {
            ChangeActiveUser *ChangeActiveUserAction = new ChangeActiveUser();
            ChangeActiveUserAction->act(*this);
        } else if (userInputVector[0] == "deleteuser") {
            DeleteUser *DeleteUserAction = new DeleteUser();
            DeleteUserAction->act(*this);
        } else if (userInputVector[0] == "dupuser") {
            DuplicateUser *DuplicateUserAction = new DuplicateUser();
            DuplicateUserAction->act(*this);
        } else if (userInputVector[0] == "log") {
            PrintActionsLog *PrintActionLogAction = new PrintActionsLog();
            PrintActionLogAction->act(*this);
        } else if (userInputVector[0] == "content") {
            PrintContentList *PrintContentListAction = new PrintContentList();
            PrintContentListAction->act(*this);
        } else if (userInputVector[0] == "watchhist") {
            PrintWatchHistory *PrintWatchHistoryAction = new PrintWatchHistory();
            PrintWatchHistoryAction->act(*this);
        } else if (userInputVector[0] == "watch") {
            Watch *WatchAction = new Watch();
            WatchAction->act(*this);
            // delete the extra watch action that does not goes to the actionLog
            delete WatchAction;
        } else {
            cout << "Illegal Command, Please Try Again" << endl;
        }
        getline(cin, lastUserInput);
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

// ################ Helper functions #################

void Session::addUser(User &toAddUser) {
    userMap.insert(make_pair(toAddUser.getName(), &toAddUser));
}

const vector<std::string> &Session::getUserInputVector() const {
    return userInputVector;
}

void Session::setActiveUser(User &activeUser) {
    Session::activeUser = &activeUser;
}

void Session::addActionLog(BaseAction &newAction) {
    Session::actionsLog.push_back(&newAction);
}

void Session::addToCurrentUserHistory(int id) {
    activeUser->addToHistory(content[id]);
}

// inserts all movies form the Json file
void Session::insertMovies(json &jsonFile) {
    json moviesJson = jsonFile["movies"];
    int id = content.size() + 1;
    for (auto &currMovie : moviesJson.items()) {
        json movie = currMovie.value();
        Movie *newMovie = new Movie(id, movie["name"], movie["length"], movie["tags"]);
        content.push_back(newMovie);
        id++;
    }
}

// inserts all series form the Json file
void Session::insertSeries(json &jsonFile) {
    json seriesJson = jsonFile["tv_series"];
    int id = content.size() + 1;
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

void Session::removeUser(std::string &userName) {
    userMap.erase(userName);
}




