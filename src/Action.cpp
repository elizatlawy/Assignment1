
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"

#include <vector>
using namespace std;

/*
 * BaseAction
 */

// Constructors
BaseAction::BaseAction(): errorMsg(""), status(PENDING) {}

// public methods
ActionStatus BaseAction::getStatus() const {
    return status;
}
void BaseAction::act(Session &sess)  {
}

string BaseAction::toString() const {
    return "";
}

// protected functions
void BaseAction::complete() {
    status = COMPLETED;
}
void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
    BaseAction::errorMsg = errorMsg;

}
string BaseAction::getErrorMsg() const {}

std::string BaseAction::statusToString() const {
    if(getStatus() == COMPLETED)
        return "COMPLETED";
    else
        return "ERROR: " + getErrorMsg();

}

/*
 * CreateUser
 */

std::string CreateUser::toString() const {
    return "CreateUser " + statusToString();
//    if(getStatus() == ERROR){
//        output = output + "ERROR: " + getErrorMsg();
//    }
//    // status = COMPLETED
//    else{
//        output = output + "COMPLETED";
//    }
}
void CreateUser::act(Session &sess) {
    string tmpUserInput = sess.getLastUserInput();
    // TODO: Fix the userName cut it is not working!!
    string userName = tmpUserInput.substr(tmpUserInput.find(" "+1),tmpUserInput.find(" "));
    string algoName = tmpUserInput.substr(tmpUserInput.length()-3);

    // user is not exist in UserMap
    if(sess.getUserMap().find(userName) == sess.getUserMap().end()){
        if(algoName == "len" | algoName == "rer" | algoName == "gen"){
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
           complete();
        }
        // algo is incorrect
        else{
            error("invalid recommendation algorithm");
        }
    } // user already exist
    else{
        error("the new user name is already taken");
    }
    // add the action to the actions log
    sess.addActionLog(this);

} // end of CreateUser


/*
 *  ChangeActiveUser
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
std::string Watch::toString() const {

}
void Watch::act(Session &sess) {

}

/*
 * PrintActionsLog
 */
std::string PrintActionsLog::toString() const {

}
void PrintActionsLog::act(Session &sess) {
    for(auto& currAction : sess.getActionsLog())
        cout << currAction->toString() << endl;
    complete();
}

/*
 * Exit
 */
std::string Exit::toString() const {}
void Exit::act(Session &sess) {}



