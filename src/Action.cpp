
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * ########################## BaseAction ##########################
 */

// Constructors
BaseAction::BaseAction(): errorMsg(""), status(PENDING) {}
// copy constructor
BaseAction::BaseAction(const BaseAction &other): errorMsg(other.errorMsg), status(other.status){}
// destructor
BaseAction::~BaseAction() {}
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
BaseAction* CreateUser::clone() {
    CreateUser* newCreateUser = new CreateUser(*this);
    return newCreateUser;
}
std::string CreateUser::toString() const {
    return "CreateUser " + statusToString();
}
void CreateUser::act(Session &sess) {
    string userName = sess.getUserInputVector()[1];
    string algoName = sess.getUserInputVector()[2];
    // user is not exist in UserMap
    if(sess.getUserMap().find(userName) == sess.getUserMap().end()){
        if((algoName == "len") | (algoName == "rer") | (algoName == "gen")){
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
    sess.addActionLog(*this);

} // end of CreateUser


/*
 * ############################ ChangeActiveUser ############################
 */
BaseAction* ChangeActiveUser::clone() {
    ChangeActiveUser* newChangeActiveUser = new ChangeActiveUser(*this);
    return newChangeActiveUser;
}
std::string ChangeActiveUser::toString() const {
    return "ChangeUser " + statusToString();
}

void ChangeActiveUser::act(Session &sess) {
    string userNameToChange = sess.getUserInputVector()[1];
    // if the user exist
    if(sess.getUserMap().find(userNameToChange) != sess.getUserMap().end()){
        sess.setActiveUser(*sess.getUserMap().at(userNameToChange));
        complete();
    }
    // if the user does not exist in UserMap
    else{
        error("the user you have entered does not exist");
        cout << toString() << endl;
    }
    sess.addActionLog(*this);
}

/*
 * ############################# DeleteUser #################################
 */
BaseAction* DeleteUser::clone() {
    DeleteUser* newDeleteUser = new DeleteUser (*this);
    return newDeleteUser;
}
std::string DeleteUser::toString() const {
    return "DeleteUser " + statusToString();
}
void DeleteUser::act(Session &sess) {
    // TODO STILL NEED TO CHECK IT WAIT FOR Nadva Watch function
    string userNameToDelete = sess.getUserInputVector()[1];
    // if the user exist
    if(sess.getUserMap().find(userNameToDelete) != sess.getUserMap().end()){
        delete sess.getUserMap().at(userNameToDelete);
        // remove the user from userMap
        sess.removeUser(userNameToDelete);
        complete();
    }
    // if the user does not exist in UserMap
    else{
        error("the user you have entered does not exist");
        cout << toString() << endl;
    }
    sess.addActionLog(*this);
}


/*
 * ############################## DuplicateUser ##############################
 */
BaseAction* DuplicateUser::clone() {
    DuplicateUser* newDuplicateUser = new DuplicateUser(*this);
    return newDuplicateUser;
}
std::string DuplicateUser::toString() const {
    return "DuplicateUser " + statusToString();
}
void DuplicateUser::act(Session &sess) {
    string originalUserName = sess.getUserInputVector()[1];
    string newUserName = sess.getUserInputVector()[2];
    // check if the original user not exits & if the new user name is not already taken
    if((sess.getUserMap().find(newUserName) == sess.getUserMap().end()) & // if the new user name is no already taken
            (sess.getUserMap().find(originalUserName) != sess.getUserMap().end())){ // if the original user exits
       // copy old user data to new user
        User* newUser = sess.getUserMap().at(originalUserName)->clone(sess);
        // set new user name
        newUser->setName(newUserName);
        // add the user to the userMap
        sess.addUser(*newUser);
        complete();
    }
    else{
        error("the original user does not exits or the new user name is already taken");
        cout << toString() << endl;
    }
    sess.addActionLog(*this);

}

/*
 * ########################## PrintContentList ##############################
 */
BaseAction* PrintContentList::clone() {
    PrintContentList* newPrintContentList = new PrintContentList(*this);
    return  newPrintContentList;
}
std::string PrintContentList::toString() const {
    return "Content " + statusToString();
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
    sess.addActionLog(*this);

} // end of PrintContentList

/*
 *  ###################### ### PrintWatchHistory ############################
 */
BaseAction* PrintWatchHistory::clone() {
    PrintWatchHistory* newPrintWatchHistory = new PrintWatchHistory(*this);
    return newPrintWatchHistory;
}
std::string PrintWatchHistory::toString() const {
    return "Watchhist " + statusToString();
}
void PrintWatchHistory::act(Session &sess) {
    // history is not empty
    cout << "Watch history for " << sess.getActiveUser()->getName() << endl;
    if (sess.getActiveUser()->get_history().size() != 0) {
        int i = 1;
        for (Watchable *currWatch : sess.getActiveUser()->get_history()) {
            string tempName = currWatch->shortToString();
            int firstSpace = tempName.find(" ");
            cout << i << ". " << tempName.substr(firstSpace + 1) << endl;
            i++;
            complete();
        }
    }
    // add the action to the actions log
    sess.addActionLog(*this);
}

/*
 * ############################## Watch ######################################
 */
BaseAction* Watch::clone() {
    Watch* newWatch = new Watch(*this);
    return newWatch;
}
std::string Watch::toString() const {
    return "Watch " + statusToString();
}
void Watch::act(Session &sess) {
    string isAgreed = "y";
    int WatchableID = atoi(sess.getUserInputVector()[1].c_str());
    while(isAgreed == "y"){
       // if the WatchableID is illegal
        if ((WatchableID < 1) | (WatchableID >(signed) sess.getContent().size()) ){
            error("this content is not available on SPLFLIX");
            cout << toString() << endl;
            break;
        }
        // print "Watching <user_name> to the screen
        else {
            string tempName = sess.getContent()[WatchableID-1]->shortToString();
            int firstSpace = tempName.find(" ");
            cout << "Watching " << tempName.substr(firstSpace+1) << endl;
            // add to history
            sess.addToCurrentUserHistory(WatchableID-1);
            // recommend to the user what to see next
            Watchable *nextRecommendation = sess.getActiveUser()->get_history()[sess.getActiveUser()->get_history().size() - 1]->getNextWatchable(sess);
            // not have recommendation for the user
            if (nextRecommendation == nullptr){
                cout << "Sorry, we do not have any recommendation for you" << endl;
                break;
            }
            // have recommendation for the user
            else {
            firstSpace = nextRecommendation->shortToString().find(" ");
            cout << "We recommend watching " << nextRecommendation->shortToString().substr(firstSpace + 1)
                 << " ,continue watching" << " [y/n]" << endl;
            complete();
            WatchableID = nextRecommendation->getId();
            getline(cin,isAgreed);
            }
        }
        // add the action to the actions log
        sess.addActionLog(*this->clone());
    } // end of while
}

/*
 * ########################### PrintActionsLog ###############################
 */
BaseAction* PrintActionsLog::clone() {
    PrintActionsLog* newPrintActionsLog = new PrintActionsLog(*this);
    return newPrintActionsLog;
}
std::string PrintActionsLog::toString() const {
    return "ActionLog " + statusToString();
}
void PrintActionsLog::act(Session &sess) {
    for(int i = sess.getActionsLog().size()-1; i >=0; i--)
        cout << sess.getActionsLog()[i]->toString() << endl;
    complete();
}

/*
 * ################################ Exit ######################################
 */
BaseAction* Exit::clone() {
    Exit* newExit = new Exit(*this);
    return newExit;
}
std::string Exit::toString() const {
    return "Exit " + statusToString();
}
void Exit::act(Session &sess) {
    complete();
    sess.addActionLog(*this);
}



