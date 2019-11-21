//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//
#include "../include/Watchable.h"
#include <vector>
#include <iterator>
using namespace std;

/*
 *  ####################### Watchable ########################
 */

Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}
//std::string Watchable::toString() const {}
Watchable* Watchable::getNextWatchable(Session &) const {}
Watchable::~Watchable() {}

const long Watchable::getId() const {
    return id;
}
int Watchable::getLength() const {
    return length;
}
const vector<std::string> &Watchable::getTags() const {
    return tags;
}

/*
 * Movie
 */

Movie::Movie(long id, const string& name, int length, const vector<string>& tags) :  Watchable(id, length, tags), name(name) {}
string Movie::toString() const {
    string tagsString = "";
    for(auto& tag: getTags())
        tagsString = tagsString + tag + ", ";
    string output = to_string(getId()) + ". " + name + " " + to_string(getLength()) + " minutes [" + tagsString + "]";
    return output;
}
Watchable* Movie::getNextWatchable(Session &) const {}

/*
 * Episode
 */
Episode::Episode(long id, const string& name, int length, int season, int episode, const vector<string>& tags ) : Watchable(id, length, tags), season(season), episode(episode){};
string Episode::toString() const {}
Watchable* Episode::getNextWatchable(Session &) const {}
