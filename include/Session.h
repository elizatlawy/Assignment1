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

class Session{
public:
    Session(const std::string &configFilePath);
    Session(const Session& other);
    ~Session();

    void start();

    const std::vector<Watchable *> &getContent() const;

    const std::vector<BaseAction *> &getActionsLog() const;

    const std::unordered_map<std::string, User *> &getUserMap() const;

    User *getActiveUser() const;

    const std::string &getLastUserInput() const;
    void addUser (User& toAddUser);
    void addActionLog (BaseAction& newAction);

    const std::vector<std::string> &getUserInputVector() const;
    void setActiveUser(User& activeUser);
    void removeUser(std::string& userName);
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    void insertMovies (json& jsonFile);
    void insertSeries (json& jsonFile);
    std::string lastUserInput;
    std::vector<std::string> userInputVector;

};
#endif
