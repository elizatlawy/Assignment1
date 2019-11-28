#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "../include/json.hpp"

using json = nlohmann::json;

class User;

class Watchable;

class Session {
public:
    Session(const std::string &configFilePath);

    Session(const Session &other); // copy constructor
    ~Session(); // destructor
    Session &operator=(Session &other);  // copy assignment
    Session &operator=(Session &&other); //  move assignment
    Session(Session &&other); // move constructor

    void start();

    const std::vector<Watchable *> &getContent() const;

    const std::vector<BaseAction *> &getActionsLog() const;

    const std::unordered_map<std::string, User *> &getUserMap() const;

    User *getActiveUser() const;

    void addUser(User &toAddUser);

    void addActionLog(BaseAction &newAction);

    void addToCurrentUserHistory(int id);

    const std::vector<std::string> &getUserInputVector() const;

    void setActiveUser(User &activeUser);

    void removeUser(std::string &userName);

private:
    std::vector<Watchable *> content;
    std::vector<BaseAction *> actionsLog;
    std::unordered_map<std::string, User *> userMap;
    User *activeUser;

    void insertMovies(json &jsonFile);

    void insertSeries(json &jsonFile);

    std::vector<std::string> userInputVector;

    void deleteSessResources();

    void stealSessResources(const Session &other);

    void copySessResources(const Session &other);

};

#endif
