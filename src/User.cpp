
#include "../include/Watchable.h"
#include "../include/User.h"

#include <vector>
#include <utility>
#include <climits>
using namespace std;

/*
 * #####################################User###################################
 */
// constructor
User::User(const string& name) : name(name){}
// copy constructor
User::User(const User &other) {
    name = other.name;
    copyHistory(other);
}
// move constructor
User::User(User &&other) {
    name = other.name;
    history = other.history;
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
Watchable* User::getRecommendation(Session &s) {}
string User::getName() const {
    return name;
}
vector<Watchable*> User::get_history() const {
    return  history;
}
// Helper Functions
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
    int tempIndex = lastRecommandedIndex;
    lastRecommandedIndex = (lastRecommandedIndex+1) % history.size();
    return history [tempIndex];
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
    //create vector of pairs - the key holds the name of the tags and the key holds the number of appearances in watchHistory
    vector<pair<string, int>> tagsVector;
    tagsVector = createVectorTags(s);
    // sort tagsVector first by value, then by key.
    vector<pair<string, int>> SortedTagsVector;
    SortedTagsVector = sortVectorTags(tagsVector);
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
}


vector<pair<string, int>> GenreRecommenderUser::createVectorTags(Session &s) {
    vector<pair<string, int>> tagsVector;
    for (int i = 0; i < history.size(); i++) {
        for (int j = 0; j < history[i]->getTags().size(); j++) {
            string currTag = history[i]->getTags()[j];
            vector<pair<string, int>>::iterator itr = std::find(tagsVector.begin(), tagsVector.end(),
                                                                make_pair(currTag, 0));
            if (itr != tagsVector.cend()) { //currTag is found
                int index = distance(tagsVector.begin(), itr);
                tagsVector[index].second++;
            }
            else { // currTag is not found
                tagsVector.push_back(make_pair(currTag, 1));
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




