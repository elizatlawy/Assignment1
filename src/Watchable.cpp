
#include "../include/Watchable.h"
#include <vector>
#include <iterator>
using namespace std;

/*
 *  ####################### Watchable ########################
 */

// Constructors
Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}
std::string Watchable::toString() const {}
Watchable* Watchable::getNextWatchable(Session &) const {}
Watchable::~Watchable() {}

// Getters

const long Watchable::getId() const {
    return id;
}
int Watchable::getLength() const {
    return length;
}
const vector<std::string> &Watchable::getTags() const {
    return tags;
}

bool Watchable::operator==(const Watchable &rhs) const {
    return id == rhs.id;
}

bool Watchable::operator!=(const Watchable &rhs) const {
    return !(rhs == *this);
}

/*
 *  ####################### Movie  #######################
 */

Movie::Movie(long id, const string& name, int length, const vector<string>& tags) :  Watchable(id, length, tags), name(name) {}
// copy constructor
Movie::Movie(const Movie &other) :  Watchable(other.getId(), other.getLength(), other.getTags()), name(other.getName()) {}

const string &Movie::getName() const {
    return name;
}

string Movie::toString() const {
    string tagsString = "";
    string separator;
    for(auto& tag: getTags()){
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string output = to_string(getId()+1) + ". " + name + " " + to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;
} //

// relation operands
bool Watchable::operator<(const Watchable &rhs) const {
    return length < rhs.length;
}

bool Watchable::operator>(const Watchable &rhs) const {
    return rhs < *this;
}

bool Watchable::operator<=(const Watchable &rhs) const {
    return !(rhs < *this);
}

bool Watchable::operator>=(const Watchable &rhs) const {
    return !(*this < rhs);
}

Watchable* Movie::getNextWatchable(Session &) const {}

/*
 *  ####################### Episode  #######################
 */
Episode::Episode(long id, const string& seriesName, int length, int season, int episode, const vector<string>& tags ) : Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode){};

const string &Episode::getSeriesName() const {
    return seriesName;
}

int Episode::getSeason() const {
    return season;
}

int Episode::getEpisode() const {
    return episode;
}

long Episode::getNextEpisodeId() const {
    return nextEpisodeId;
}

string Episode::toString() const {
    string tagsString = "";
    string separator;
    for(auto& tag: getTags()){
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string printSeason = to_string(season);
    string printEpisode = to_string(episode);
    if (season < 10)
        printSeason = "0" + printSeason;
    if(episode < 10)
        printEpisode = "0" + printEpisode;
    string output = to_string(getId()+1) + ". " + seriesName + " " + "S" + printSeason + "E" + printEpisode + " " + to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;

}


Watchable* Episode::getNextWatchable(Session &) const {}

// end of Episode class