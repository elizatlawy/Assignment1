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

//    double avrLenOfHistory;
//    int sumOfAllContent = 0;
//    for (Watchable& x : history) {
//        sumOfAllContent = sumOfAllContent + x.getLength();
//    }
//    avrLenOfHistory = (double) sumOfAllContent/history.size();
//    vector<Watchable*> c = s.getContent();
//    sort(c.begin(), c.end());
//    int biggerThanMe = 0;
//    int lowerThanMe = 0;
//    int i = 0;
//    int j = 0;
//    for (int i=0 ; i < s.getContent().size()-1 ; i++) {
//        while (s.getContent()[i]->getLength() < avrLenOfHistory) {
//            if ()
//                i++;
//        }
//    }
//    biggerThanMe = s.getContent()[i]->getLength();
//    while ( j<s.getContent().size()-1) {
//        if (s.getContent()[j]->getLength() > avrLenOfHistory)
//            j++;
//    }
//    lowerThanMe = s.getContent()[j]->getLength();

    }



/*
 * RerunRecommenderUser
 */

RerunRecommenderUser::RerunRecommenderUser(const string& name) : User(name){}

Watchable* RerunRecommenderUser::getRecommendation(Session &s) {}

/*
 * GenreRecommenderUser
 */

GenreRecommenderUser::GenreRecommenderUser(const string& name) : User(name){}

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {}