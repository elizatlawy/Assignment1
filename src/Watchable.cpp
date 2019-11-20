//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//
#include "../include/Watchable.h"
#include <vector>
using namespace std;

/*
 * Watchable
 */
Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}
//std::string Watchable::toString() const {}
//Watchable* Watchable::getNextWatchable(Session &) const {}
Watchable::~Watchable() {}

/*
 * Movie
 */
Movie::Movie(long id, const string& name, int length, const vector<string>& tags) :  Watchable(id, length, tags), name(name) {}
string Movie::toString() const {}
Watchable* Movie::getNextWatchable(Session &) const {}

/*
 * Episode
 */
Episode::Episode(long id, const string& name, int length, int season, int episode, const vector<string>& tags ) : Watchable(id, length, tags), season(season), episode(episode){};
string Episode::toString() const {}
Watchable* Episode::getNextWatchable(Session &) const {}








