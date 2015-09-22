#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;


void pointer(void) {
  int* pi;
  int num = 100;
  pi = &num;

  cout << "01 num " << num << " address " << pi << " pi " << *pi << endl;

  *pi = 200;
  cout << "02 num " << num << " address " << pi << " pi " << *pi << endl;
}


void array(void) {
  int values[] = {1,2,4,8,16};
  int* ary = values;
  int i, max = 5;

  cout << "For loop ----" << endl;
  for (i = 0; i < max ;i++) {
    cout << "idx-> " << i << " value=> " << ary[i] << endl;
  }

  cout << "While loop ----" << endl;
  while (ary - values < max) {
    cout << "idx-> " << (ary - values) << " value=> " << *ary << endl;
    ary++;
  }

}

void mapCxx() {

  map<int,string> idnames;

  idnames.insert(map<int,string>::value_type(10, "aaaa"));

  map<int,string>::iterator itr = idnames.begin();
  while (itr != idnames.end()) {
    cout << "key " << (*itr).first << " value " << (*itr).second << endl;
    ++itr;
  }

}
