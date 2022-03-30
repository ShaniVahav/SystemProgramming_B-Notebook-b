#include "Notebook.hpp"
#include <unordered_map>
#include <array>
#include <cstring>
#include<math.h>
using namespace std ;
using ariel ::Direction;


const char minValidChar = 32 ;
const char maxValidChar = 126; 
const char ROW_SIZE = 100 ; 

void vector_init( array<char,ROW_SIZE> & a_Src , array<char,ROW_SIZE> & a_dest){
    for(size_t i = 0 ; i <ROW_SIZE; i++){
        a_dest.at(i) = a_Src.at(i);
    }
}

void ariel::Notebook::write(int page, int row , int col, Direction dir, string str) {
 for(size_t i = 0 ; i < str.length(); i++){
    if ((str[i] < minValidChar) || (str[i] >maxValidChar) || (str[i] == '~')) {
            throw "Invalid!";
    }

    }
    if(page < 0 || row < 0 || col < 0 || col> ROW_SIZE-1 || str.find('\n') != -1)  {
         throw "Invalid!";
    }
    if( floor(page)!= page|| floor(row) != row || floor(col) != col || str.length() == 0){
        throw "Invalid!";
    }
    if (pages.find(page) == pages.end()) {
        unordered_map<int, array<char,ROW_SIZE>> newPage;
        pages[page]= newPage;
    }

    array<char,ROW_SIZE> c = {};
    for (size_t i = 0; i < ROW_SIZE; i++) {
        c.at(i) = '_';
    }

    if (dir == Direction::Horizontal) {
    if (pages[page].find(row) == pages[page].end()){
        vector_init(c,pages[page][row]);
    }
    /// writing
    for (size_t i = 0; i < str.length(); i++) {
        if (pages[page][row][(size_t)col + i] == '_'){
            pages[page][row][(size_t)col + i] = str[(size_t)i];
        }
        else{
            throw "Invalid!";
        }
    }
}

    if (dir == Direction::Vertical) {
        for (int i = 0; i < str.length(); i++) {
            if (pages[page].find((size_t)(row + i)) == pages[page].end()){ ///// cheak if the row already exist - if so , dont create it again
                vector_init(c,pages[page][row + i]);
            }
        }
        /// writing
        for (int i = 0; i < str.length(); i++) {
            if (pages[page][(size_t)(row + i)][(size_t)col] == '_'){
                pages[page][(size_t)(row + i)][(size_t)col] = str[(size_t)i];
            }
            else{
                throw "Invalid!";
            }
        }
    }
    // creating row which are not exist
  
}

string ariel::Notebook::read(int page, int row, int col, Direction dir, int len) {
    if(page < 0 || row < 0 || col < 0 || len < 0 || col > ROW_SIZE-1){
         throw "Invalid!";             
    }
    if((col + len > ROW_SIZE) && (dir == Direction::Horizontal)){ 
        throw "Invalid!";   
    }
    if(floor(page)!= page|| floor(row) != row || floor(col) != col || floor(len) !=len){
               throw "Invalid!";   
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
 
        for (size_t i = 0; i < len; i++) {
            char c = pages[page][row][(size_t)(col) +i];
            str.push_back(c);
        }
        return str;
    }
    return str ;
}


void ariel::Notebook::erase(int page, int row, int col, Direction dir, int len) {
    if(page < 0 || row < 0 || col < 0 || len < 0 ||col >ROW_SIZE-1){
          throw "Invalid!";
    }
    if((col + len > ROW_SIZE) && (dir == Direction::Horizontal ) ){ 
         throw "Invalid!";;     
    }
    if(len == 0){
        return;  
    }  
    array<char,ROW_SIZE> c ={};
    for (size_t i = 0; i < ROW_SIZE; i++) {
        c.at(i) = '_';
    }
  
      if (pages.find(page) == pages.end()) {
        unordered_map<int, array<char,ROW_SIZE>> specifyPage;  /// represt a page
        pages[page]= specifyPage;
    }

    if (dir == Direction::Horizontal) {
         array<char,ROW_SIZE> c = {};
        if(pages[page].find(row) == pages[page].end()){
            vector_init(c,pages[page][row]);
        }

        for(size_t i=0; i<len; i++){
           size_t col2 = (size_t)col;
            pages[page][row][(col2+i)] = '~';
        }
    }

    if (dir == Direction::Vertical) {
        for (int i = 0; i < len; i++) {
            if (pages[page].find(row + i) == pages[page].end()){
                vector_init(c,pages[page][row + i]);
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
            cout<<"_____________________________________________"<<endl;
        }
    }

    else{
         array<char,ROW_SIZE> row ={};
        for(unordered_map<int, array<char,ROW_SIZE>>::iterator itr = pages[page].begin(); itr != pages[page].end(); ++itr){
            vector_init(itr->second,row);
            for(size_t i=0; i<ROW_SIZE; i++){
                cout<<row.at(i);
            }
            cout<<endl;
        }
    }
    
}