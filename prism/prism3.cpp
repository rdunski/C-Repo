#include <iostream>
#include <string>
#include <fstream>

vector<string> __attr_not_in_R(attr, R){
    vector<string> list;
    for (int i = 0; i<attr.size();i++)
    {
      if (R.size() == 0)
        return attr;
      else
      {
        if(count(R.begin(),R.end(),attr[i]))
          continue;
        else
          list.push_back(attr[i]);
      }
    }
    return list;

  }

pair<vector<string>,vector<string>> __build_rule(vector<pair<string,vector<string>>> instances, vector<string> attributes, string label, string cls){
    vector<string> rules;
    float accuracy =-1.0;
    vector<pair<string,vector<string>>> rule_instances = instances;
    vector<string> avail_attr;
    for (int i = 0; i< attributes.size();i++)
      if(attributes[i] != label)
        avail_attr.push_back(attributes[i]);
    while(1){
      vector<string> allRules;
        // for A in self.__attr_not_in_R(avail_attr, rules):
        //     for X in self.__get_attr_values(rule_instances, A):
        //
        //         coverage = self.__apply_rule(rule_instances, [[A, X]])
        //         accuracy = self.__rule_accuracy(coverage, label, cls)
        //         allRules.append([A, X, accuracy[0], accuracy[1]])
        //
        // bestRule = self.__get_best_rule(allRules)
        //
        // R.append((bestRule[0][0], bestRule[0][1]))
        //
        // rule_instances = self.__apply_rule(rule_instances, R)
        //
        // if bestRule[0][2] == 1.0 or bestRule[0][3] < 1:
        //     break
    }

    return <rules, rule_instances>;
}
void skipLines(ifstream file, int numLines){
  string arbitraryLine;
  for (int i =0; i < numLines;i++)
    getline(file, arbitraryLine);
  return;
}

int __has_class_value(vector<pair<string,vector<string>>> instances, string label, string cls){
  vector<string> asd;
  for (int i =0; i< 5;i++)
    if(instances.at(i) == label)
      for (int j = 0; j< instance.at(i).second.size(); i++)
        if(instances.at(i).second[j] == cls)
          asd.push_back(instances.at(i).second[j]);
  return asd.size();
}
vector<pair<string,vector<string>>> getData(string file){
  vector<pair<string,vector<string>>> result;
  ifstream inputFile(file);
  string val;
  string text_line,colName;
  skipLines(2);
  if(file.good()){
    for (int i = 0; i< 5;i++){
      getline(file, line);
      stringstream ss(line);
      int count 0;
      while(getline(ss, colname, ' ')){
        if (count == 0)
          continue;
        else{
          result.push_back({colname, vector<string> {}});
          break;
          }
        }
      }
    skipLines(2);
    while (getline(file, text_line))
    {
      stringstream ss(line);
      int colIdx = 0;
        while(ss >> val){
            result.at(colIdx).second.push_back(val);
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }
      }
    }
  file.close();
  return result;
}

vector<string> fit(vector<pair<string,vector<string>>> data){
  vector<string> attributes;
  for (int i =0;i < 5;i++)
    attributes.push_back(data.at(i).first);
  string label = attributes[-1];
  vector<string> classes = data.at(-1).second;
	auto end = classes.end();
	for (auto it = classes.begin(); it != end; ++it)
		end = remove(it + 1, end, *it);
	classes.erase(end, v.end());
        vector<string> rules;
        for (int i=0; i< classes.size();i++){
            instances = data;
            while (self.__has_class_value(instances, label, classes[i]) > 0){
                rule, covered = self.__build_rule(instances, attributes, label, cls)
                R.append({cls: rule})
                instances = self.__remove_covered_instances(instances, covered)
        }
        return R, label
}

//     def __get_best_rule(self, rules):
//         rule = []
//
//         runningBest = []
//         maxAcc = 0
//         maxCov = 0
//         for potentRule in rules:
//             if potentRule[2] > maxAcc:
//                 maxAcc = potentRule[2]
//                 maxCov = potentRule[3]
//                 runningBest.append(potentRule)
//
//             elif potentRule[2] == maxAcc:
//                 if potentRule[3] > maxCov:
//                     runningBest.append(potentRule)
//
//         rule.append(runningBest[-1])
//         #---------------------------------------------------------------------------------
//         #THE ABOVE CODE COMPLETED BY DAHV REINHART - V00735279
//         #---------------------------------------------------------------------------------
//         return rule
//
//     def predict(test_data_file, rules):
//         test_data = pickle.load(open(test_data_file, 'rb'))
//         p = []
//         return p
//
//     # This method returns the instances covered by the set of rules
//     def __apply_rule(self, data, R):
//         coverage = data[:]
//         for r in R:
//             coverage = [i for i in coverage if i[r[0]] == r[1]]
//         return coverage
//
//     # This method remove all instances covered by the set of rules
//     def __remove_covered_instances(self, instances, covered):
//         return [i for i in instances if i not in covered]
//
//     # Computes p/t
//     def __rule_accuracy(self, coverage, label, cls):
//         accuracy = [i for i in coverage if i[label] == cls]
//         return float(len(accuracy))/len(coverage), len(accuracy)
//
//     # Returns a list of all possible values of a given attribute
//     def __get_attr_values(self, instances, attr):
//         return self.__unique([a[attr] for a in instances])
//
//     # Returns a list of all unique values of a list
//     def __unique(self, l):
//         return list(set(l))
//
//
// # Debugging function printing the set of rules in english
// def printRules(rules,label):
//     for rule in rules:
//         k = rule.keys()[0]
//         nbr = len(rule[k])
//
//         theRule = " IF "
//         for subrules in rule[k]:
//             nbr -= 1
//             theRule = theRule + str(subrules[0]) + " = " + subrules[1]
//             if nbr > 0:
//                 theRule = theRule + "\n\t AND "
//             else:
//                 theRule = theRule + "\n\t THEN " + label + " = " + k
//
//         print theRule +"\n"
//
//
// if __name__ == '__main__':
//     import sys
//     prism = Prism(sys.argv[1])
//     rules, label = prism.fit()
//
//     #printRules(rules,label)
//     print rules
//     # print p
