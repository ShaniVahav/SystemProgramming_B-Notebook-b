//
// Created by barse on 3/22/2022.
//

#include "Notebook.hpp"
#include <unordered_map>
#include <array>
#include <cstring>
#include<math.h>
using namespace std ;
using ariel ::Direction;
const char HUNDRED = 100 ; 
const char MIN = 32 ;
const char MAX = 126; 
const char COL_NUMBER99 = 99;





void copy_vector( array<char,HUNDRED> & a_Src , array<char,HUNDRED> & a_dest){
    for(size_t i = 0 ; i <HUNDRED; i++){
        a_dest.at(i) = a_Src.at(i);
    }
}
void ariel::Notebook::write(int page, int row , int col, Direction dir, string str) {
 for(size_t i = 0 ; i < str.length(); i++){
    if ((str[i] < MIN) || (str[i] >MAX) || (str[i] == '~')) {
            throw "1";
    }
    if(str.length() == 0){
        throw "1";
    }
    }
    if(page < 0 || row < 0 || col < 0 || col> COL_NUMBER99 || str.find('\n') != -1 )  {
         throw "1";
    }
    if(((size_t)col + str.length() > COL_NUMBER99+1) && (dir == Direction::Horizontal)){
        throw "1";     
    }
    if (pages.find(page) == pages.end()) {
        unordered_map<int, array<char,HUNDRED>> specifyPage;  /// represt a page
        pages[page]= specifyPage;
    }
    ///// crreating c ;
    array<char,HUNDRED> c = {};
    for (size_t i = 0; i < HUNDRED; i++) {
        c.at(i) = '_';
    }
    //// creating rows which are not exist yet ;
    if (dir == Direction::Vertical) {
        for (int i = 0; i < str.length(); i++) {
            if (pages[page].find((size_t)(row + i)) == pages[page].end()){ ///// cheak if the row already exist - if so , dont create it again
                copy_vector(c,pages[page][row + i]);
            }
        }
        /// writing
        for (int i = 0; i < str.length(); i++) {
            if (pages[page][(size_t)(row + i)][(size_t)col] == '_'){
                pages[page][(size_t)(row + i)][(size_t)col] = str[(size_t)i];
            }
            else{
                throw "1";
            }
        }
    }
    // creating row which are not exist
    if (dir == Direction::Horizontal) {
        if (pages[page].find(row) == pages[page].end()){
            copy_vector(c,pages[page][row]);
        }
        /// writing
        for (size_t i = 0; i < str.length(); i++) {
            if (pages[page][row][(size_t)col + i] == '_'){
                pages[page][row][(size_t)col + i] = str[(size_t)i];
            }
            else{
                throw "not legal";
            }
        }
    }
}

string ariel::Notebook::read(int page, int row, int col, Direction dir, int len) {
    if(page < 0 || row < 0 || col < 0 || len < 0 || col > COL_NUMBER99){
         throw "1";             
    }
    if((col + len > COL_NUMBER99+1) && (dir == Direction::Horizontal)){ 
        throw "1";   
    }
    if(floor(page)!= page|| floor(row) != row || floor(col) != col || floor(len) !=len){
               throw "1";   
    }
    string str = string("");
    if (pages.find(page) == pages.end()) {
        //  returning an ___ if the page is we never wrote inside the page - beacuse he is not exist.
        for (int i = 0; i < len; i++) {
            str.push_back('_');
        }
        return str;
    }
    // if the page does exist - lets read inside of it .
    if (dir == Direction::Vertical) {
        for (int i = 0; i < len; i++) {
            if (pages[page].find(row + i) != pages[page].end()) {
                char c = pages[page][(size_t)(row + i)][(size_t)(col)];
                str.push_back(c);
            } 
            else{
                str.push_back('_');
            }
        }
    }
    if (dir == Direction::Horizontal) {
        if (pages[page].find(row) == pages[page].end()) {
            for (int i = 0; i < len; i++) {
                str.push_back('_');
            }
            return str;
        }
        //// if the row does exist - lets read from it
        for (size_t i = 0; i < len; i++) {
            char c = pages[page][row][(size_t)(col) +i];
            str.push_back(c);
        }
        return str;
    }
    return str ;
}


void ariel::Notebook::erase(int page, int row, int col, Direction dir, int len) {
     array<char,HUNDRED> c ={};
    if(page < 0 || row < 0 || col < 0 || len < 0 ||col >COL_NUMBER99){
          throw "l";
    }
    if( (col + len > COL_NUMBER99+1) && (dir == Direction::Horizontal )){ 
         throw "1";;     
    }
    if(len == 0){
        return;  
    }  
    for (size_t i = 0; i < HUNDRED; i++) {
        c.at(i) = '_';
    }
      if (pages.find(page) == pages.end()) {
        unordered_map<int, array<char,HUNDRED>> specifyPage;  /// represt a page
        pages[page]= specifyPage;
    }

    if (dir == Direction::Horizontal) {
        // create the row
         array<char,HUNDRED> c = {};
        if(pages[page].find(row) == pages[page].end()){
            copy_vector(c,pages[page][row]);
        }

        // delete the right places
        for(size_t i=0; i<len; i++){
           size_t COLLSECOND = (size_t)col;
            pages[page][row][(COLLSECOND+i)] = '~';
        }
    }
    if (dir == Direction::Vertical) {
        // create the column
        for (int i = 0; i < len; i++) {
            if (pages[page].find(row + i) == pages[page].end()){
                copy_vector(c,pages[page][row + i]);
            }
        }
        for(int i=0; i<len; i++){
            pages[page][(size_t)(row+i)][(size_t)col] = '~';
        }
    }
}

void ariel::Notebook::show(int page) {
     const int  SIX = 6 ;
    if(page < 0 ){
       throw "ilegal";
    }
    if (pages.find(page) == pages.end()) {
        for(int i=0; i<SIX; i++){
            cout<<"____________________________________________________________________________________________________"<<endl;
        }
    }

    else{
         array<char,HUNDRED> row ={};
        for(unordered_map<int, array<char,HUNDRED>>::iterator itr = pages[page].begin(); itr != pages[page].end(); ++itr){
            copy_vector(itr->second,row);
            cout <<  itr->first;
            for(size_t i=0; i<HUNDRED; i++){
                cout<< row.at(i);
            }
            cout<<endl;
        }
    }
    
}
