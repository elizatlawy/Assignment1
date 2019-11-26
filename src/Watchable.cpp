
#include "../include/Watchable.h"
#include <vector>
using namespace std;

/*
 *  ####################### Watchable ########################
 */

// Constructors
Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}
//std::string Watchable::toString() const {}
Watchable* Watchable::getNextWatchable(Session & sess) const {}
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
// constructor
Movie::Movie(long id, const string& name, int length, const vector<string>& tags) :  Watchable(id, length, tags), name(name) {}
// copy constructor
Movie::Movie(const Movie &other) :  Watchable(other.getId(), other.getLength(), other.getTags()), name(other.getName()) {}
// getters
std::string Movie::getName() const {
    return name;
}

string Movie::toString() const {
    string tagsString = "";
    string separator;
    for(auto& tag: getTags()){
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string output = to_string(getId()) + ". " + name + " " + to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;
} //

std::string Movie::shortToString() const {
    string tagsString = "";
    string separator;
    for(auto& tag: getTags()){
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string output = to_string(getId()) + ". " + name ;
    return output;
}

Watchable* Movie::getNextWatchable(Session& sess) const {
    return sess.getActiveUser()->getRecommendation(sess);
}

/*
 *  ####################### Episode  #######################
 */
Episode::Episode(long id, const string& seriesName, int length, int season, int episode, const vector<string>& tags ) : Watchable(id, length, tags),
seriesName(seriesName), season(season), episode(episode), nextEpisodeId((long)(id+1)){};

std::string Episode::getName() const {
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
    string output = to_string(getId()) + ". " + seriesName + " " + "S" + printSeason + "E" + printEpisode + " " + to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;
}

Watchable* Episode::getNextWatchable(Session & sess) const {
    if(nextEpisodeId <= sess.getContent().size()){ // check if it is not the last Episode in content // TODO CHECK
        if(sess.getContent()[nextEpisodeId-1]->getName() == seriesName){ // check if it is not the last Episode in the serie
            return sess.getContent()[nextEpisodeId-1];
        }
        else
            sess.getActiveUser()->getRecommendation(sess);
    }
    else
        sess.getActiveUser()->getRecommendation(sess);
}

std::string Episode::shortToString() const {
    string tagsString = "";
    string separator;
    // TODO: MAKE THIS Helper function
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
    string output = to_string(getId()) + ". " + seriesName + " " + "S" + printSeason + "E" + printEpisode;
    return output;
}

void Episode::setNextEpisodeId(long nextEpisodeId) {
    Episode::nextEpisodeId = nextEpisodeId;
}

// end of Episode class