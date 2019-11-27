#include "../include/Watchable.h"
#include <vector>
#include <utility>
#include <climits>
using namespace std;

/*
 * #####################################User###################################
 */
// constructor
User::User(const string& name) : history(), name(name){}
// copy constructor
User::User(const User &other): history(), name(other.name){
    copyHistory(other);
}
// move constructor
User::User(User &&other): history(other.history), name(other.name){
//    name = other.name;
//    history = other.history;
    other.history.clear();
}
// destructor
User::~User() {
    // clear all history pointers
    history.clear();

}
// copy assignment
User &User::operator=(const User &other) {
    // if try copy this just return this
    if(this == &other)
        return *this;
    // first destroy old history
    history.clear();
    name = other.name;
    copyHistory(other);
    return *this;
}
//  move assignment
User &User::operator=(User &&other) {
    // first destroy old history
    history.clear();
    copyHistory(other);
    // delete other history
    other.history.clear();
    return *this;
}
// getters
string User::getName() const {
    return name;
}
vector<Watchable*> User::get_history() const {
    return  history;
}
// Helper Functions
void User::addToHistory(Watchable* currWatchable) {
    history.push_back(currWatchable);
}

void User::copyHistory(const User &other) {
    for(auto i : other.history)
        history.push_back(i);
}

void User::setName(const string &name) {
    User::name = name;
}

/*
 * ##########################LengthRecommenderUser###########################
 */
// TODO: CHECK if all algo have a null condition
LengthRecommenderUser::LengthRecommenderUser(const string& name) : User(name){} // constructor
User* LengthRecommenderUser::clone(const Session& s) {
    LengthRecommenderUser* toReturn = new LengthRecommenderUser(this->getName());
    for(int i = 0; i < (signed) this->history.size(); i++){
        int currWatchableID = history[i]->getId();
        toReturn->history.push_back(s.getContent()[currWatchableID-1]);
    }
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

User* RerunRecommenderUser::clone(const Session& s) {
    auto* toReturn = new RerunRecommenderUser(this->getName());
    for(int i = 0; i < (signed) this->history.size(); i++){
        int currWatchableID = history[i]->getId();
        toReturn->history.push_back(s.getContent()[currWatchableID-1]);
    }
    toReturn->lastRecommandedIndex = this->lastRecommandedIndex;
    return toReturn;
}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
    int tempIndex = lastRecommandedIndex;
    lastRecommandedIndex = (lastRecommandedIndex+1) % history.size();
    return history [tempIndex];
}
/*
 * ########################GenreRecommenderUser#####################
 */

GenreRecommenderUser::GenreRecommenderUser(const string& name) : User(name){}

User* GenreRecommenderUser::clone(const Session& s) {
    auto* toReturn = new GenreRecommenderUser(this->getName());
    for(int i = 0; i < (signed) this->history.size(); i++){
        int currWatchableID = history[i]->getId();
        toReturn->history.push_back(s.getContent()[currWatchableID-1]);
    }
    return toReturn;
}

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {
    // create tagsVector
    vector<pair<string, int>> tagsVector = createVectorTags(s);
    // sort tagsVector first by value, then by key.
    vector<pair<string, int>> SortedTagsVector;
    SortedTagsVector = sortVectorTags(tagsVector);
    // return recommendation by most common tag
    // going over the sorted tags vector by decreasing order.
    Watchable* nextRecommendation = nullptr;
    for (int i = 0; i < (signed) SortedTagsVector.size(); i++) {
        // going over each watchable* in content
        for (auto j : s.getContent()) {
            // going over all tags of curr watchable*
            for (int k = 0; k < (signed) j->getTags().size(); k++) {
                string currTag = j->getTags()[k];
                if (tagsVector[i].first == currTag) {
                    auto itr = std::find(history.begin(), history.end(), j);
                    if (itr == history.cend()) { //watchable* is not found
                        nextRecommendation = j;
                    }
                }
            }
        }
    }
    return nextRecommendation;
}

vector<pair<string, int>> GenreRecommenderUser::createVectorTags(Session &s) {
    vector<pair<string, int>> tagsVector;
    for (auto & i : history) {
        for (auto currTag : i->getTags()) {
            auto itr = std::find_if( tagsVector.begin(), tagsVector.end(),
                                                      [&currTag](const pair<string, int>& element){ return element.first == currTag;} );
            if (itr != tagsVector.cend()) { //currTag is found
                int index = distance(tagsVector.begin(), itr);
                tagsVector[index].second++;
            }
            else { // currTag is not found
                tagsVector.emplace_back(currTag, 1);
            }
        }
    }
    return tagsVector;
}
vector<pair<string, int>> GenreRecommenderUser::sortVectorTags(vector<pair<string, int>> tagsVector) {
    std::sort(tagsVector.begin(), tagsVector.end(), [](const pair<string, int> &x, const pair<string, int> &y) {
        // compare second value
        if (x.second != y.second)
            return x.second > y.second;
        // compare first only if second value is equal
        else
            return x.first < y.first;
    });
    return tagsVector;
}




