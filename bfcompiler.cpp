/*
author: Paul Caron
date: Sept 2021
a brainfuck compiler to c
use like:
./a.out filename.bf

then it will create a file named "compiled.c"

compile this file like
gcc compiled.c -o compiled -O3

enjoy
*/


#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

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

void compile(string program, ofstream & file){
    for(int i; i<program.size(); ++i){
        char instruction = program[i];
        switch (instruction){
            case '+': file << "*dataPtr += 1;" << endl; break;
            case '-': file << "*dataPtr -= 1;" << endl; break;
            case '>': file << "dataPtr += 1;" << endl; break;
            case '<': file << "dataPtr -= 1;" << endl; break;
            case '.': file << "write(1,dataPtr,1);" << endl; break;
            case ',': file << "read(0,dataPtr,1);" << endl; break;
            case '[': file << "while(*dataPtr){" << endl; break;
            case ']': file << "}" << endl; break;
            default: {
                           char count = instruction;
                           instruction = program[++i];
                           switch (instruction){
                                case '+': file << "*dataPtr += " << count <<";"<< endl; break;
                                case '-': file << "*dataPtr -= " << count <<";"<< endl; break;
                                case '>': file << "dataPtr += " << count << ";"<< endl; break;
                                case '<': file << "dataPtr -= " << count << ";" <<  endl; break;
                           }
                     }
        }
    }
}

int main(int argc, char ** argv){
    if(argc <=1) exit(1);
    const char * inputFilename = argv[1];
    ifstream file{inputFilename};
    const string str (istreambuf_iterator<char>(file ),(istreambuf_iterator<char>()) );
    file.close();
    string nocomments = removeComments(str);
    string compressed = compress(nocomments);
    const char * outputFilename = "compiled.c";
    ofstream outFile{outputFilename};
    outFile << "#include <unistd.h>" << endl
            << "char data[30000]={0}, *dataPtr=data;" << endl
            << "int main(){" << endl;
    compile(compressed, outFile);
    outFile << "return 0;" << endl
            << "}" << endl;
    outFile.close();
    return 0;
}







