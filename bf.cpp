
#include <fstream>
#include <iterator>
#include <iostream>
#include <cstdio>

using namespace std;
const char * program;
char * dataTable;
inline const char & fetch(){ return *program;}
inline void incrementDP(const unsigned & delta=1){ dataTable+=delta;}
inline void decrementDP(const unsigned & delta=1){ dataTable-=delta;}
inline void incrementData(const unsigned & delta=1){ (*dataTable)+=delta;}
inline void decrementData(const unsigned & delta=1){ (*dataTable)-=delta;}
inline void outputData(){ cout << *dataTable << flush ;}
inline void inputData(){ cin>> noskipws >> *dataTable ;}
inline void jumpForwardZero(){
    if(*dataTable == 0){
        int otherBrackets = 1;
        while(otherBrackets> 0){
            ++program;
            if(fetch()== ']')--otherBrackets;
            else if(fetch()== '[') ++otherBrackets;
        }
    }
}
inline void jumpBackwardNZero(){
    if(*dataTable != 0){
        int otherBrackets = 1;
        while(otherBrackets>0){
            --program;
            if( fetch()=='[') --otherBrackets;
            else if(fetch() == ']') ++otherBrackets;
        }
    }
}
inline void execute(const char & i,int n=1){
    switch(i){
     case '<': decrementDP(n);break;
     case '>': incrementDP(n);break;
     case '+': incrementData(n);break;
     case '-': decrementData(n); break;
     case '[': jumpForwardZero();break;
     case ']': jumpBackwardNZero();break;
     case '.': outputData();break;
     case ',': inputData();break;
     default: {
                 ++program;
                 execute(fetch(),i-48);
              }
    }
}
inline void cycle(const char & i){
    execute(i);
    ++program;
}
void runProgram(){
    char i ;
    while( i=fetch() ){
        cycle(i);
    }
}

string removeComments(string s){
   string result;
   for(auto c: s){
      if(c=='>'||c=='<'||c=='+'||c=='-'||c=='.'||c==','||c=='['||c==']')
      result+=c;
   }
    return result;
}

string compress(string s){
    string result;
    for(int i=0;i<s.size()-1;++i){
         char c = s.at(i);
         if(c=='>'||c=='<'||c=='+'||c=='-'){
             int count = 1;
             while(i<s.size()-1&&s.at(++i)==c&&count<9){
                 ++count;
             }
             --i;
             result+=to_string(count);
             result+=c;
         }else{
             result+=c;
         }
    }
    result+=s.at(s.size()-1);
    return result;
}

int main(int argc, char ** argv){
    if(argc <=1) exit(1);
    const char * filename = argv[1];
    ifstream file{filename};
    const string str (istreambuf_iterator<char>(file ),(istreambuf_iterator<char>()) );
    file.close();
    string nocomments = removeComments(str);
    string compressed = compress(nocomments);
    program = compressed.c_str();
    char dt[30000]{0};
    dataTable = dt;
    runProgram();
    return 0;
}







