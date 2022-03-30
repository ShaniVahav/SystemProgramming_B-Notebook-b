
#pragma once
#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
using namespace std;
using std::array;

namespace ariel {
    class Notebook {
        unordered_map<int, unordered_map<int, array<char,100>>> pages;
    public:
        Notebook()
           : pages() {
         }
        

        void write(int, int, int, Direction dir, string str );

        string read(int page, int row, int col, Direction dir, int len);

        void erase(int page, int row, int col, Direction dir, int len);

        void show(int page);

    };


}