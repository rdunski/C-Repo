#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

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

class MaxClass {
public:
    int maxClass;
    int maxVal;
};

class MaxElem {
public:
    int maxAttr;
    int maxVal;
};

int main(){
  ifstream myfile;
  myfile.open("weather.nominal.arff");
  return 0;
}

// vector<any> predict(int* model, ){
//   std::vector<std::any> predictedList;
//   //any testData =
// }

int getMaxElements(vector<string> mainlist, int col){
    MaxClass max;
    vector<string> list;
    string maxKey;
    int maxValue;
    for (int i = 0; i < mainlist.size(); i++){
        for(int j = 0; i< list.size(); i++){
          if (mainlist[col] == list[j])
             list[col] = list[col] + 1;
          else
              list[col] = 1;
        }
      }
    maxValue = 0;
    maxKey = "";
    for (int i = 0; i< list.size();i++){
        if (maxValue <= i){
            maxValue = list[i]);
            maxKey = i;
          }
        }
    return maxKey;
}

int getMaxClass(vector<string> prismData, int y){
    return getMaxElements(prismData,y);
}

vector<string> model(vector<string> data){
  int n = data.size();
  int y = (data[0].size())-1;
  vector<string> prismData = data;
  vector<string> model;
  while (n >= 1){
    MaxClass maxClass = getMaxClass(prismData,y);
    vector<string> list = getRecords(prismData,maxClass.maxClass,y);
    rule = getRule(list,y,maxClass.maxClass,prismData);
  }
}

vector<string> getRecords(vector<string> prismData, int maxClass, int y){
    vector<string> list;
    for (int i=0;i<prismData.size();i++){
        if ((prismData[i])[y] == maxClass)
            list.push_back(data);
    }
    return list
  }

vector<string> getRule(vector<string>list, int y, int targetClass, vector<string> DataSet){
    vector<string> secondList;

    for (int i =0; i < y; i++){
        MaxElem s = getMaxElements(list,i);
        t = s.maxAttr,i;
        secondList[t]=s.maxVal;
      }
    sort(secondList);
    vector<string> rule;
    int validity = 0;
    while (validity==0){
        for (int i=0;i<secondList.size();i++){
            string attr = (secondList[i])[0];
            rule[attr[1]] = attr[0];
            validity = validateRule(rule, targetClass, DataSet, y);
            if (validity == 1)
                break;
            }
        if (validity == 1)
                break;
        else
            secondList=random.sample(sortedDict,sortedDict.size());
            rule.clear();
    }
    return rule;
}

vector<string> getList(int i, string val, vector<string> dataSet){
    vector<string> list;
    for (auto& row : dataSet){
        if (row[i] == val)
            list.push_back(row);
    }
    return list;
}

int checkList(int targetClass, vector<string> list, int classCol){
    vector<T> classVal;
    for (int i =0;i< list.size();i++)
        classVal.push_back(list[classCol]);
    auto val = classVal.size();
    if ((val == targetClass))
        return 1;
    else
        return 0;
}

int validRule(vector<string> rule, int targetClass, vector<string> dataSet, int y){
    vector<string> list = dataSet;
    for (int i =0; i< rule.size();i++)
        list = getList(i, rule[i], list);
    int found = checkList(targetClass, list, y);
    return found;
}

vector<string> checkInstances(vector<string> rule, vector<string> prismData){
    vector<string> list = prismData;
    for (int i=0;i<rule.size();i++)
        list = getList(i,prismData[i],list);
    return list;
}
