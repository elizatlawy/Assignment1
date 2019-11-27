#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"


using namespace std;

int main(int argc, char** argv){

	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
    Session* s = new Session(argv[1]);
    s->start();
//    Session* s2 = new Session(argv[1]);
//    s2->start();
//     s2 = s;
    Session s3 = *s; // copy constructor
    delete(s);
    s3.start();
    return 0;
}



