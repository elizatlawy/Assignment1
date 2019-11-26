
#include "../include/Watchable.h"
#include "../include/User.h"
#include "../include/Session.h"
#include <vector>
#include <utility>
#include <climits>
using namespace std;

/*
 * #####################################User###################################
 */
User::User(const string& name) : name(name){} // constructor
User::User(const User &other) { // copy constructor
    name = other.name;
    copyHistory(other);
}
User::User(User &&other) { // // move constructor
    name = other.name;
    history = other.history;
    other.history.clear();
}


User::~User() {
    // clear all history pointers
    history.clear();

}

User &User::operator=(const User &other) { // copy assignment
    // if try copy this just return this
    if(this == &other)
        return *this;
    // first destroy old history
    history.clear();
    name = other.name;
    copyHistory(other);
    return *this;
}

User &User::operator=(User &&other) { //  move assignment
    history.clear();
    copyHistory(other);
    other.history.clear();
    return *this;
}

// getters
Watchable* User::getRecommendation(Session &s) {}
string User::getName() const {
    return name;
}
vector<Watchable*> User::get_history() const {
    return  history;
}
void User::addToHistory(Watchable &currWatchable) {
    history.push_back(&currWatchable);
    //TODO check if currWatchable is saved as reference to content
}

void User::copyHistory(const User &other) {
    for(int i = 0; i < other.history.size(); i++)
        history.push_back(other.history.at(i));
}

void User::setName(const string &name) {
    User::name = name;
}


/*
 * ##########################LengthRecommenderUser###########################
 */
// TODO: CHECK if all algo have a null condition
LengthRecommenderUser::LengthRecommenderUser(const string& name) : User(name){} // constructor
User* LengthRecommenderUser::clone() {
    LengthRecommenderUser* toReturn = new LengthRecommenderUser(this->getName());
    for(int i = 0; i < this->history.size(); i++)
        toReturn->history.push_back(this->history.at(i));
    return toReturn;
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    Watchable* nextRecommendation = nullptr;
    double distance = INT_MAX;
    double avrLenOfHistory = 0 ;
    int sumOfAllContent = 0;
    // calculate the average length in history
    for (Watchable *x : history) {
        sumOfAllContent = sumOfAllContent + x->getLength();
    }
    avrLenOfHistory = (double) (sumOfAllContent) / history.size();
    // find if watchContent is in history
    for (auto& watchContent : s.getContent() ){
        if(std::find(history.begin(), history.end(), watchContent) == history.end()) {
            /* content does not contains watchContent */
           double tmpDistance = abs((double)(watchContent->getLength()-avrLenOfHistory));
           if(tmpDistance < distance){
               nextRecommendation = watchContent;
               distance = tmpDistance;
           }
        }
    }
    return  nextRecommendation;
}

/*
 * #####################RerunRecommenderUser########################
 */

RerunRecommenderUser::RerunRecommenderUser(const string& name) : User(name), lastRecommandedIndex(0){} // constructor
User* RerunRecommenderUser::clone() {
    RerunRecommenderUser* toReturn = new RerunRecommenderUser(this->getName());
    for(int i = 0; i < this->history.size(); i++)
        toReturn->history.push_back(this->history.at(i));
}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
    // if history is empty return null
    if (get_history().size() == 0)
        return nullptr;
    // if we reached the end of history return to history begin
    if (lastRecommandedIndex = history.size())
        lastRecommandedIndex = 0;
    int tempIndex = lastRecommandedIndex;
    lastRecommandedIndex++;
    return history[tempIndex];
}

/*
 * ########################GenreRecommenderUser#####################
 */

GenreRecommenderUser::GenreRecommenderUser(const string& name) : User(name){}

User* GenreRecommenderUser::clone() {
    GenreRecommenderUser* toReturn = new GenreRecommenderUser(this->getName());
    for(int i = 0; i < this->history.size(); i++)
        toReturn->history.push_back(this->history.at(i));
}

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {
    //create 2 vectors -  the first holds the name of the tags and the second  holds the number of appearances in watchHistory
    vector<pair<string, int>> tagsVector;
    for (int i = 0; i < history.size(); i++) {
        for (int j = 0; j < history[i]->getTags().size(); j++) {
            string currTag = history[i]->getTags()[j];
            vector<pair<string, int>>::iterator itr = std::find(tagsVector.begin(), tagsVector.end(),
                                                                make_pair(currTag, 0)); //TODO check if works
            if (itr != tagsVector.cend()) { //currTag is found
                int index = distance(tagsVector.begin(), itr);
                tagsVector[index].second++;
            } else { // currTag is not found
                tagsVector.push_back(make_pair(currTag, 1));
            }
        }
    }
    // sort tagsVector first by value, then by key.
    std::sort(tagsVector.begin(), tagsVector.end(), [](const pair<string, int> &x, const pair<string, int> &y) {
        // compare second value
        if (x.second != y.second)
            return x.second > y.second;
        // compare first only if second value is equal
        return x.first < y.first;
    });
    // going over the sorted tags vector by decreasing order.
    for (int i = 0; i < tagsVector.size(); i++) {
        // going over each watchable* in content
        for (int j = 0; j < s.getContent().size(); j++) {
            // going over all tags of curr watchable*
            for (int k = 0; k < s.getContent()[j]->getTags().size(); k++) {
                string currTag = s.getContent()[j]->getTags()[k];
                if (tagsVector[i].first == currTag) {
                    vector<Watchable *>::iterator itr = std::find(history.begin(), history.end(), s.getContent()[j]);
                    if (itr == history.cend()) { //watchable* is not found
                        return s.getContent()[j];
                    }
                }
            }
        }
    }


};// end of GenreRecommendion
