//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//
#include "../include/Watchable.h"
#include "../include/User.h"
#include "../include/Session.h"
#include <vector>
using namespace std;

/*
 * User
 */
User::User(const string& name) : name(name){
    history = {nullptr};
}
Watchable* User::getRecommendation(Session &s) {

}
string User::getName() const {}
vector<Watchable*> User::get_history() const {}

/*
 * LengthRecommenderUser
 */

LengthRecommenderUser::LengthRecommenderUser(const string& name) : User(name){}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {

    double avrLenOfHistory;
    int sumOfAllContent = 0;
    for (Watchable *x : history) {
        sumOfAllContent = sumOfAllContent + x->getLength();
    }
    avrLenOfHistory = (double) (sumOfAllContent) / history.size();
    vector<Watchable *> contentCopy = s.getContent();
    // sort vector contentCopy
    sort(contentCopy.begin(), contentCopy.end());
    int i = 0;
    int j = contentCopy.size() - 1;
    while (contentCopy[i]->getLength() < avrLenOfHistory) {
        i++;
    }
    while (contentCopy[j]->getLength() > avrLenOfHistory) {
        j--;
    }
    // find the closest bigger length to avrLenOfHistory that is not in history
    if (binary_search(history.begin(), history.end(), contentCopy[i]))
        i--;
    // find the closest lower length to avrLenOfHistory that is not in history
    if (binary_search(history.begin(), history.end(), contentCopy[j]))
        j++;
    // find the minimum length between them
    double resultLower = (double) (avrLenOfHistory) - contentCopy[i]->getLength();
    double resultUpper = contentCopy[j]->getLength() - (double) (avrLenOfHistory);
    int result;
    if (resultLower < resultUpper)
        return contentCopy[i];
    else
        return contentCopy[j];

}

/*
 * #####################RerunRecommenderUser########################
 */

RerunRecommenderUser::RerunRecommenderUser(const string& name) : User(name), lastRecommandedIndex(0){}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
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

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {}