//
// Created by zatlawy@wincs.cs.bgu.ac.il on 20/11/2019.
//

#include "../include/Session.h"
#include "../include/json.hpp"
#include <vector>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Session::Session(const string& configFilePath){
    ifstream i(configFilePath);
    json contentJson;
    i >> contentJson;
    int j = 0;
    for (json::iterator it = contentJson.begin(); it != contentJson.end(); ++it) {
        //std::cout << it.key() << " : " << it.value() << "\n";
        cout << it.value()[0]["length"] << endl;

    }
}

Session::~Session() {}

void Session::start() {
    cout << "SPLFLIX is now on!";
}


