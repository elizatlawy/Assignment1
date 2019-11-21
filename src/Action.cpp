
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"

#include <vector>
using namespace std;

/*
 * BaseAction
 */

ActionStatus BaseAction::getStatus() const {}
void BaseAction::act(Session &sess) {}
string BaseAction::toString() const {}
void BaseAction::complete() {}
void BaseAction::error(const std::string &errorMsg) {}
string BaseAction::getErrorMsg() const {}

void BaseAction::setErrorMsg(const string &errorMsg) {
    BaseAction::errorMsg = errorMsg;
}

void BaseAction::setStatus(ActionStatus status) {
    BaseAction::status = status;
}

/*
 * CreateUser
 */

std::string CreateUser::toString() const {}
void CreateUser::act(Session &sess) {
    string tmpUserInput = sess.getLastUserInput();
    string userName = tmpUserInput.substr(tmpUserInput.find(" "+1),tmpUserInput.find(" "));
    string algoName = tmpUserInput.substr(tmpUserInput.length()-3);

    if((sess.getUserMap().find(userName) != sess.getUserMap().end() ) & (algoName == "len" | algoName == "rer" | algoName == "gen" )){
        if(algoName == "len"){
            LengthRecommenderUser *toAddUser = new LengthRecommenderUser(userName);
            sess.addUser(*toAddUser);
        }
        if(algoName == "rer"){
            RerunRecommenderUser *toAddUser = new RerunRecommenderUser(userName);
            sess.addUser(*toAddUser);
        }
        if(algoName == "gen"){
            GenreRecommenderUser *toAddUser = new GenreRecommenderUser(userName);
            sess.addUser(*toAddUser);
        }
        setStatus(COMPLETED);

    }
    else{
        setStatus(ERROR);
        // check what about PENDING?


    }


} // end of CreateUser




/*
 * ChangeActiveUser
 */

std::string ChangeActiveUser::toString() const {}
void ChangeActiveUser::act(Session &sess) {}

/*
 * DeleteUser
 */
std::string DeleteUser::toString() const {}
void DeleteUser::act(Session &sess) {}

/*
 * DuplicateUser
 */

std::string DuplicateUser::toString() const {}
void DuplicateUser::act(Session &sess) {}

/*
 * PrintContentList
 */

std::string PrintContentList::toString() const {}
void PrintContentList::act(Session &sess) {}

/*
 * PrintWatchHistory
 */

std::string PrintWatchHistory::toString() const {}
void PrintWatchHistory::act(Session &sess) {}

/*
 * Watch
 */
std::string Watch::toString() const {}
void Watch::act(Session &sess) {}

/*
 * PrintActionsLog
 */
std::string PrintActionsLog::toString() const {}
void PrintActionsLog::act(Session &sess) {}

/*
 * Exit
 */
std::string Exit::toString() const {}
void Exit::act(Session &sess) {}



