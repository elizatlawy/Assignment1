#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){

//    string tmpUserInput = "createuser Martsiano2 gen";
//    std::istringstream iss(tmpUserInput);
//    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
//                                     std::istream_iterator<std::string>());
//    for(auto& word : results)
//        cout << word << endl;
//    string userName = tmpUserInput.substr(tmpUserInput.find(" "),tmpUserInput.find(" "));
//    userName = userName.substr(1);
//    cout << userName;
	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
	Session s(argv[1]);
	s.start();
	return 0;
}
