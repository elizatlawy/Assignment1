//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//
#include "../include/Action.h"
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

/*
 * CreateUser
 */

std::string CreateUser::toString() const {}
void CreateUser::act(Session &sess) {}


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


