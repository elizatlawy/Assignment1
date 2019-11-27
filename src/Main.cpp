#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"


using namespace std;

int main(int argc, char** argv){
//    vector<string> tags = {"tag1", "tag2"};
//    Episode* ep1 = new Episode(1,"name",10,1,1,tags);
//    cout << ep1->toString();
//    Episode* ep2 = ep1;
//    delete ep1;
//    cout << ep2->toString();

	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
    Session* s = new Session(argv[1]);
    s->start();
    Session* s3 = new Session(argv[1]);
    Session s2 = *s;
    delete(s);
//    //s2.start();
//    s3 = std::move(&s2);
//    s3->start();


//    Session* s2 = new Session(argv[1]);
//    s2->start();
//     s2 = s;
//    Session s3 = *s; // copy constructor
//    delete(s);
//    s3.start();
    return 0;
}



