//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/User.h"
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