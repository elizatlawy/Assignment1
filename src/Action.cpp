
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"

#include <vector>
using namespace std;

/*
 * ########################## BaseAction ##########################
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
string BaseAction::getErrorMsg() const {
    return errorMsg;
}

std::string BaseAction::statusToString() const {
    if(getStatus() == COMPLETED)
        return "COMPLETED";
    else
        return "ERROR: " + getErrorMsg();

}

/*
 * #####################################CreateUser##################################
 */

std::string CreateUser::toString() const {
    return "CreateUser " + statusToString();
}
void CreateUser::act(Session &sess) {
    string tmpUserInput = sess.getLastUserInput();
    string userName = sess.getUserInputVector()[1];
    string algoName = sess.getUserInputVector()[2];
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
            cout << toString() << endl;
        }
    } // user already exist
    else{
        error("the new user name is already taken");
        cout << toString() << endl;
    }
    // add the action to the actions log
    sess.addActionLog(this);

} // end of CreateUser


/*
 * ############################ ChangeActiveUser ############################
 */

std::string ChangeActiveUser::toString() const {}
void ChangeActiveUser::act(Session &sess) {}

/*
 * ############################# DeleteUser #################################
 */
std::string DeleteUser::toString() const {}
void DeleteUser::act(Session &sess) {}

/*
 * ############################## DuplicateUser ##############################
 */

std::string DuplicateUser::toString() const {}
void DuplicateUser::act(Session &sess) {}

/*
 * ########################## PrintContentList ##############################
 */

std::string PrintContentList::toString() const {
    return "content " + statusToString();
}
void PrintContentList::act(Session &sess) {
    //content is not empty
    if (sess.getContent().size() != 0) {
        for (Watchable *currWatch : sess.getContent()) {
            cout << currWatch->toString() << endl;
            complete();
        }
    }
    // content is empty
    else {
        error("there is no content available right now, please try again later");
        cout << toString() << endl;
    }
    // add the action to the actions log
    sess.addActionLog(this);

} // end of PrintContentList

/*
 *  ###################### ### PrintWatchHistory ############################
 */

std::string PrintWatchHistory::toString() const {}
void PrintWatchHistory::act(Session &sess) {}

/*
 * ############################## Watch #####################################
 */
std::string Watch::toString() const {

}
void Watch::act(Session &sess) {

}

/*
 * ########################### PrintActionsLog ###############################
 */
std::string PrintActionsLog::toString() const {
// TODO ask forum
}
void PrintActionsLog::act(Session &sess) {
    for(int i = sess.getActionsLog().size()-1; i >=0; i--)
        cout << sess.getActionsLog()[i]->toString() << endl;
    complete();
}

/*
 * ################################ Exit #####################################
 */
std::string Exit::toString() const {}
void Exit::act(Session &sess) {}



