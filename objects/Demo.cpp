/**
 * Demo program for notebook exercise.
 *
 * Author: Erel Segal-Halevi
 * Edited by: Tal Zichlinsky
 * Since : 2022-01
 */

#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

string IntToString (int a)
{
    stringstream temp;
    temp<<a;
    return temp.str();
}



int main() {
    ariel::Notebook notebook;
    try{
        for(int i = 1 ; i < 11 ; i ++){
            for(int j = 0 ; j < 100 ; j ++){
                int a = i*j;
                notebook.write(100, i, j ,Direction::Horizontal,"a" );
            }
        }
        notebook.read(100,99,0,Direction::Horizontal,100);
        for(int i = 1 ; i < 11 ; i = i +2 ){
            notebook.erase(100,i,0,Direction::Horizontal,100);
        }
        notebook.show(100);
    }catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }
}