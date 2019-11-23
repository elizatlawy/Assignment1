
#include "../include/Watchable.h"
#include "../include/User.h"
#include "../include/Session.h"
#include <vector>
#include <utility>


using namespace std;

/*
 * #####################################User###################################
 */
User::User(const string& name) : name(name){
    history = {nullptr};
}
Watchable* User::getRecommendation(Session &s) {}
string User::getName() const {
    return name;
}
vector<Watchable*> User::get_history(
        ) const {
    return history;
}

/*
 * ##########################LengthRecommenderUser###########################
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

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {
// create 2 vectors -  the first ine holds the name of the tags and the second  holds the number of appearances in watchHistory
    vector<pair<string,int>> tagsVector;
    for (int i = 0; i < history.size(); i++) {
        for (int j = 0; j < history[i]->getTags().size(); j++) {
            string currTag = history[i]->getTags()[j];
            vector<pair<string,int>>::iterator itr = std::find(tagsVector.begin(), tagsVector.end(), make_pair(currTag,0)); // TODO: check if compare by name;
            if (itr != tagsVector.cend()) { //currTag is found
                int index = distance(tagsVector.begin(), itr);
                tagsVector[index].second++;
            }
            else{ // currTag is not found
                tagsVector.push_back(make_pair(currTag,1));
            }
        }
    }
    // sort tagsVector first by value, then by key.
    std::sort(tagsVector.begin(), tagsVector.end(),[](const pair<string,int>& x, const pair<string,int>& y) {
        // compare second value
        if (x.second != y.second)
            return x.second > y.second;
        // compare first only if second value is equal
        return x.first < y.first;
    });
    // going over the sorted tags vector by decreasing order.
    for (int i= 0 ; i < tagsVector.size() ; i++) {
        // going over each watchable* in content
        for (int j = 0; j < s.getContent().size(); j++) {
            // going over all tags of curr watchable*
            for (int k = 0; k < s.getContent()[j]->getTags().size(); k++) {
                string currTag = s.getContent()[j]->getTags()[k];
                if (tagsVector[i].first == currTag) {
                    vector<Watchable*>::iterator itr = std::find(history.begin(), history.end(), s.getContent()[j]);
                    if (itr == history.cend()) { //watchable* is not found
                        return s.getContent()[j];
                    }
                }
            }
        }
    }
    return nullptr;


} // end of GenreRecommendion
