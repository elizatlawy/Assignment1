#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"

using namespace std;

int main(int argc, char** argv){
    vector<string> tags {"Fantasy","Drama"};
    long l = 1;
    Movie *Mov = new Movie(l, "my movie", 60, tags);
    cout << Mov->toString() << endl;
    cout << "test";

	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
	Session s(argv[1]);
	s.start();
	return 0;
}
