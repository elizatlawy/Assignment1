#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"

using namespace std;

int main(int argc, char** argv){
//    vector<string> tags {"Fantasy","Drama"};
//    long l = 1;
//    Movie *Mov = new Movie(l, "my movie", 60, tags);
//    cout << Mov->toString() << endl;
//    cout << "test";
vector <int> v {1,2,3};
    if (std::find(v.begin(), v.end(), 4) == v.end())
        cout << "enter to if";
    else
        cout << " not enter to if";


	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
	Session s(argv[1]);
	s.start();
	return 0;
}
