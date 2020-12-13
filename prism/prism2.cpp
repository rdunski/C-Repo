#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bits/basic_string.h>

/*
For each class C
  Initialize E to the instance set
  While E contains instances in class C
    Create a rule R with an empty left-hand side that predicts class C
    Until R is perfect (or there are no more attributes to use) do
       For each attribute A not mentioned in R, and each value v,
          Consider adding the condition A = v to the left-hand side of R
          Select A and v to maximize the accuracy p/t
           (break ties by choosing the condition with the largest p)
       Add A = v to R
   Remove the instances covered by R from E

t = total instances
p = positive instances
*/

using namespace std;

string removeNewLine(string str){
  unsigned shift=0;
  for (unsigned i=0; i<str.size(); ++i){
      if (str[i] == '\n')
          ++shift;
      else
          str[i-shift] = str[i];
  }
  str.resize(str.length() - shift);
  return str;
}

vector<string> getData(){
  ifstream myfile;
  myfile.open("");
  string str;
  vector<string> list;
  while(getline(myfile, str, ',')){
    str=removeNewLine(str);
    list.push_back(str);
  }
  return list;
}

vector<string> prism(vector<string> data){
  int n = data.size();
  int y = (data[0].size())-1;
  vector <string> prismData = data;
  vector <string> model;
  return prismData;
}

int main(){
  vector<string> data = getData();
  cout << "yes" << endl;
  vector<string> newData = prism(data);
  return 0;
}
