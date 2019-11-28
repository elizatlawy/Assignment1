#include "../include/Watchable.h"
#include <vector>

using namespace std;

/*
 *  ####################### Watchable ########################
 */

// Constructors
Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}

// destructor
Watchable::~Watchable() {
    tags.clear();
}

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

/*
 *  ###################################### Movie  ####################################
 */
// constructor
Movie::Movie(long id, const string &name, int length, const vector<string> &tags) : Watchable(id, length, tags),
                                                                                    name(name) {}

Watchable *Movie::clone() {
    Movie *newMovie = new Movie(getId(), name, getLength(), getTags());
    return newMovie;
}

// getters
std::string Movie::getName() const {
    return name;
}

// functions
string Movie::toString() const {
    string tagsString = "";
    string separator;
    for (auto &tag: getTags()) {
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string output =
            to_string(getId()) + ". " + name + " " + to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;
}

std::string Movie::shortToString() const {
    string output = to_string(getId()) + ". " + name;
    return output;
}

Watchable *Movie::getNextWatchable(Session &sess) const {
    return sess.getActiveUser()->getRecommendation(sess);
}

/*
 *  ######################################### Episode  ##############################################
 */
// constructor
Episode::Episode(long id, const string &seriesName, int length, int season, int episode, const vector<string> &tags)
        : Watchable(id, length, tags),
          seriesName(seriesName), season(season), episode(episode), nextEpisodeId((long) (id + 1)) {}

Watchable *Episode::clone() {
    Episode *newEpisode = new Episode(getId(), seriesName, getLength(), season, episode, getTags());
    return newEpisode;
}

// getters
std::string Episode::getName() const {
    return seriesName;
}

// functions
string Episode::toString() const {
    string tagsString = "";
    string separator;
    for (auto &tag: getTags()) {
        tagsString = tagsString + separator + tag;
        separator = ", ";
    }
    string printSeason = to_string(season);
    string printEpisode = to_string(episode);
    if (season < 10)
        printSeason = "0" + printSeason;
    if (episode < 10)
        printEpisode = "0" + printEpisode;
    string output = to_string(getId()) + ". " + seriesName + " " + "S" + printSeason + "E" + printEpisode + " " +
                    to_string(getLength()) + " minutes [" + tagsString + "]" + "\n";
    return output;
}

Watchable *Episode::getNextWatchable(Session &sess) const {
    if (nextEpisodeId <=
        (signed) sess.getContent().size()) { // check if it is not the last Episode in content
        if (sess.getContent()[nextEpisodeId - 1]->getName() ==
            seriesName) { // check if it is not the last Episode in the serie
            return sess.getContent()[nextEpisodeId - 1];
        } else
            return sess.getActiveUser()->getRecommendation(sess);
    } else
        return sess.getActiveUser()->getRecommendation(sess);
}

std::string Episode::shortToString() const {
    string printSeason = to_string(season);
    string printEpisode = to_string(episode);
    if (season < 10)
        printSeason = "0" + printSeason;
    if (episode < 10)
        printEpisode = "0" + printEpisode;
    string output = to_string(getId()) + ". " + seriesName + " " + "S" + printSeason + "E" + printEpisode;
    return output;
}
