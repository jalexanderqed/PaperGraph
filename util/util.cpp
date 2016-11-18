#include "util.h"

string myReadFile(string name) {
    ifstream ifs(name);
    string content((istreambuf_iterator<char>(ifs)),
                   (istreambuf_iterator<char>()));
    return content;
}