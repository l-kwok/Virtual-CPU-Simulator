#include <string>

using namespace std;

class Exception{

public: 
    Exception(const string& msg) : error(msg) {};

private:
    string error;    

};