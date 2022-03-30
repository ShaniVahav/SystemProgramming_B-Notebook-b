include "Notebook.hpp"
include <iostream>
include <string>

Notebook note;

int page;
string str;
cout<<"Insert a page number"<<endl;
cin>>page;

cout<<"Insert string"<<endl;
cin>>str;

int row = rand() % 100;
int col = rand() % 100;

note.write(page, row, col, len(str));
note.show((page, row, col, len(str));
