#ifndef USER_H_
#define USER_H_

#include "Watchable.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using  namespace std;
class Watchable;
class Session;

class User{
public:
    User(const std::string& name); // constructor
    virtual ~User(); // destructor
    virtual User* clone(const Session& s) = 0;
    User (const User& other); // copy constructor
    User (User&& other); // // move constructor
    User& operator=(const User& other);  // copy assignment
    User& operator=( User&& other); //  move assignment
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    void addToHistory (Watchable& currWatchable);
    void setName(const std::string &name);
protected:
    std::vector<Watchable*> history;
private:
    std::string name;
    void copyHistory(const User &other);


};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(const Session& s);

private:

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(const Session& s);

private:
    int lastRecommandedIndex;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(const Session& s);

private:
    vector<pair<string, int>> sortVectorTags(vector<pair<string, int>> tagsVector);
    vector<pair<string, int>> createVectorTags(Session &s);
};

#endif
