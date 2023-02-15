#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
// *** You need to open files using argumentmanager when submit your assignment ***
ArgumentManager am(argc, argv);
 ifstream ifs(am.get("input"));
 ifstream command(am.get("command")); ofstream ofs(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
   //ifstream ifs("input9.txt");
   //ifstream command("command9.txt");
  // ofstream ofs("output9.txt");

  string in = ""; //input string
  string out; //output string
  vector<string> ids; //vector string to hold ids

  map<char, string> charSet;

  if(!ifs.is_open()) {
    return 0;
  }
  if(!command.is_open()) {
    return 0;
  }
  if(!ofs.is_open()) {
    return 0;
  }

  while(getline(ifs, in)) { 
    
    // Clean up blank spaces, \n and \r, and skip blank lines
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if(in.size() == 0)
      continue;
    
    // continue to process the input below
    //cout << in << endl;

    //check if input is not blank
    if(in.empty() || in == "\n" || in == "\r" || in == " ") { 
      continue;
    }
    //cout << in << endl;
    
    //check for both ids and char set
    if(in.find("id:") == -1 || in.substr(0, 3) == "id:") { 
      //first part: checks if first index is "id:" which is invalid due to missing char set
      //second part: checks if input is missing "id:" which is invalid due to missing ids
      continue;
    }
      
    //cout << in << endl;
    
    out = "";

    //cout << out << endl;

    //pair together character to its corresponding number
    int i = 0; //index
    int semi; //semicolon index
    
    string num; //hold number of character

    while(in.substr(i, 3) != "id:") { //loops for how many semi colons
      //cout << in << endl;
      num = "";
      if(isalpha(in[i])) {
        semi = i;
        while(in[semi] != ';') {
          semi++;
        }
        num = in.substr(i + 2, semi - i - 2); //ex i = 0; substr(0 + 2, 5 - 2 - 0) -> substr(2, 3) a = 123;
        //cout << num << endl;
        charSet[in[i]] = num;
        //cout << charSet[in[i]] << endl;
        }
      i = semi + 1;
    }
  
    string toStr = "";

    //cout << in.length() << endl;
    for(i += 3; i < in.length(); i++) {
      if(isalpha(in[i])) {
          out += charSet[in[i]]; 
        //cout << out << endl;
        }
        else {
          out += in[i];
        }
      }
    
    string decoded = "";

    for(i = 0; i < out.size(); i++) {
      if(out[i] == '#'){
        toStr = to_string(i);
        decoded += toStr;
      }
      else {
        decoded += out[i];
      }
    }

    //cout << decoded << endl;
    ids.push_back(decoded);
    
    charSet.clear();
  
  }

  
  string cmd = "";

  vector<string> first4;
  vector<string> last4;
  string val;

  while(getline(command, cmd)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
    if(cmd.size() == 0)
      continue;
    
    // continue to process the command below
  
    //cout << cmd << endl;
    
    if(cmd.substr(0, 7) == "first4:") {
      val = "";
      val = cmd.substr(7, 4);
      first4.push_back(val);
    }

    if(cmd.substr(0, 6) == "last4:") {
      val = "";
      val = cmd.substr(6, 4);
      last4.push_back(val);
    }
  }

  //output the raw string without filtering
  if (cmd.empty()) {
    for (int i = 0; i < ids.size(); i++) {
      ofs << ids[i] << endl;
    }
  }

  //filter for both
  if(first4.size() >= 1 && last4.size() >= 1) {
  for (int i = 0; i < ids.size(); i++) {
    for(int j = 0; j < first4.size(); j++) {
      for(int k = 0; k < last4.size(); k++) {
      if ((ids[i].substr(0, 4) == first4.at(j)) && (ids[i].substr(ids[i].size()-4, ids[i].size()-1) == last4.at(k))) {
        ofs << ids[i] << endl;
      }
      else {
        continue;
          }
        }
      }
    }
  }
  
  //filter for first4
  if(first4.size() >= 1 && last4.size() == 0) {
  for (int i = 0; i < ids.size(); i++) {
    for(int j = 0; j < first4.size(); j++) {
      if (ids[i].substr(0, 4) == first4.at(j)) {
        ofs << ids[i] << endl;
      }
      else {
        continue;
        }
      }
    }
  }
  
//filter for last4
  if(first4.size() == 0 && last4.size() >= 1) {
  for (int i = 0; i < ids.size(); i++) {
    for(int j = 0; j < last4.size(); j++) {
      if (ids[i].substr(ids[i].size()-4, ids[i].size()-1) == last4.at(j)) {
        ofs << ids[i] << endl;
        //cout << ids[i] << endl;
      }
      else {
        continue;
        }
      }
    }
  }
  ifs.close();
  ofs.close();
  command.close();

  return 0;
}