#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>
#include "../include/Session.h"
#include "../include/User.h"
using namespace std;


class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags); // constructor
    virtual ~Watchable(); // destructor
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session& sess) const = 0;
    virtual std::string shortToString() const = 0;
    virtual std::string getName() const = 0;
    virtual Watchable* clone() = 0;
    const long getId() const;
    int getLength() const;
    const std::vector<std::string> &getTags() const;

    bool operator==(const Watchable &rhs) const;
    bool operator!=(const Watchable &rhs) const;

private:
    const long id;
    int length;
    std::vector<std::string> tags;

};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags); // constructor
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    virtual std::string getName() const;
    virtual std::string shortToString () const;
    virtual Watchable* clone();

private:
    std::string name;

};

class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags); // constructor
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    virtual std::string shortToString () const;
    virtual std::string getName() const;
    virtual Watchable* clone();

    int getSeason() const;

    int getEpisode() const;

    long getNextEpisodeId() const;

    void setNextEpisodeId(long nextEpisodeId);

private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;

};
#endif

