#include <iostream>
#include "../include/Session.h"
#include "../include/Watchable.h"


using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "usage splflix input_file" << endl;
        return 0;
    }
    Session *s = new Session(argv[1]);
    s->start();
    Session s2 = *s;
    delete (s);
    s2.start();
    return 0;
}

void test(int argc, char **argv) {
    Session s = Session(argv[1]);
    s.start();
//    Session* s3 = new Session(argv[1]);
    //Session* s2 = s; // copy constructor - - works!
    //Session s3(std::move(s2)); // move constructor - works!
    Session s3 = Session(argv[1]);
    s3.start();
    //s3 = std::move(s); // move assignment
    s3 = s; // copy assignment
    s3.start();
    //delete(s2);
//    delete (s3);
    //delete(s2);
    //   s2.start();
//    s2.start();

//    s3->start();
//    delete (s3);


//    Session* s2 = new Session(argv[1]);
//    s2->start();
//     s2 = s;
//    Session s3 = *s; // copy constructor
//    delete(s);
//    s3.start();

}



