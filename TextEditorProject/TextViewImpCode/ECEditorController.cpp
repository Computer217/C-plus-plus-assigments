//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#include "ECTextViewImp.h"
#include "ECTextDocument.h"
#include "ECEditorController.h"
#include "ECCommand.h"
#include <iostream>
#include <string>
#include <algorithm>
#include<unistd.h>

using namespace std;


//Constructor
ECEditorController :: ECEditorController(ECTextViewImp &WndIn, string file): window(WndIn), document(ECTextDocument()), DocCtrl(document.GetCtrl()), page(0), file(file){}

//Destructor writes to the file
ECEditorController :: ~ECEditorController(){
    Save();
}

//Writting to file before quitting 
void ECEditorController :: Save(){
        fstream File;
        File.open(file, fstream::in | fstream::out | fstream::trunc );

        if (!File){
            File.open(file, fstream::out);

            //write to file
            for (int i = 0; i < document.GetLengthRows(); i++){
                File << document.GetStringAt(i) << endl;
            }

            File.close();
        }
        else{
            //write to file
            for (int i = 0; i < document.GetLengthRows(); i++){
                File << document.GetStringAt(i) << endl;
            }

            File.close();
        }
}  

//Read from file if file exists
void ECEditorController :: ReadFile(){
    fstream File;
    File.open(file, ios::in);
    string line;

    if(File.is_open()){
        while(getline(File, line)){
            DocCtrl.NewLine(document.GetLengthRows(),line);
        }
        File.close();
        DocCtrl.RemoveLine(0);
    }

}

//ReadKey from STDIO
void ECEditorController :: Update(){
    int key = window.GetPressedKey();

    //Key handling inside Search Mode
    if (document.Search){
        if (key == ESC){
            this->SearchOff();
        }
        else if (key == BACKSPACE){
            this->SearchBackspace();
        }
        else if (key == ENTER){
            this->SearchEnter();
        }
        else if (key>=32){
            this->SearchInput(key);
            //Stop Highlighting once '/' appears
            if (key == 47){document.Find = false;}
        }
        
        //highlight search
        if (document.Find){this->SearchFind();}
    }
    else{
        //Key handling in insert mode
        if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN || key == ENTER || key == BACKSPACE){
            this->CursorUpdate(key);
        }
        else if (key>=32){   
            this->CharUpdate(key);
        }
        else if (key == CTRL_Z){
            this->Undo();
        }
        else if (key == CTRL_R){
            this->Redo();
        }
        else if (key == CTRL_F){
            this->SearchOn();
        }
    }   
}

//Proccess/Read Key
void ECEditorController :: CursorUpdate(int key){

    switch (key) {
        case ENTER:
            Enter();
            break;
        case BACKSPACE:
            Backspace();
            break;
        case ARROW_RIGHT:
            cursorRight();
            break;
        case ARROW_LEFT:
            cursorLeft();
            break;
        case ARROW_UP:
            cursorUp();
            break;
        case ARROW_DOWN:
            cursorDown();
            break;
        default:
            break;

    }

    window.Refresh();
}

//AddRows() to the view depending on current window range
void ECEditorController :: ViewLayout(){

    //status bar text
    string status_text(document.statusBar.begin(), document.statusBar.end());

    if (document.Search){
        window.ClearStatusRows();
        window.AddStatusRow( "Search: " + status_text, "Page: " + to_string(page+1), true);
    }
    else{
        //Set the status Row with correct Page Display
        window.ClearStatusRows();
        window.AddStatusRow("Insert: ", "Page: " + to_string(page+1), true);
    }
   
    //Store copy of current page from document 
    vector<string> Temp_view = document.GetChars();

    int window_end;
    int window_start = page * window.GetRowNumInView();
    
    //If the WindowView is greater than the amount of rows in the model 
    if ((page+1) * window.GetRowNumInView() > document.GetLengthRows()){
        //Make the window as big as the document 
        window_end = document.GetLengthRows();

        //Populate View
        for(int i = window_start; i < window_end; i++){
                window.AddRow(Temp_view[i]);
        }
    }
    else{
        //Make the window as big as the windowView
        window_end = (page + 1) * window.GetRowNumInView();

        //Populate View
        for(int i = window_start; i < window_end; i++){
            window.AddRow(Temp_view[i]);
        }
    }

}

//CTRL_F Toggle to Search Mode 
void ECEditorController :: SearchOn(){
    //Toggle On
    document.Search = true;
    document.Find = true;
    document.statusBar.pop_back();

    //Update StatusRow
    window.ClearStatusRows();
    window.AddStatusRow( "Search: ", "Page: " + to_string(page+1), true);
}

void ECEditorController :: SearchOff(){
    //Toggle Off
    document.Search = false;
    document.Find = false;
    SearchClear();
    document.statusBar.clear();
    document.statusBar.push_back(' ');

    //Update StatusRow
    window.ClearStatusRows();
    window.AddStatusRow( "Insert: ", "Page: " + to_string(page+1), true);
}

//DELETE characters from the search needle in the status bar
void ECEditorController :: SearchBackspace(){

    //Remove char if there is one in the status bar
    if (document.statusBar.size() > 0){
        window.InitRows(); 

        //Remove last character highlight
        if (document.statusBar.size() == 1){
            SearchClear(string(1, document.statusBar[0]));
        }

        //Remove Char
        document.statusBar.pop_back();
        ViewLayout();
        window.Refresh();
    }
}

//ENTER, replace search word with replace word
void ECEditorController :: SearchEnter(){

    // Get slash index
    auto iter = find(document.statusBar.begin(),document.statusBar.end(), '/');

    //if no slash is found, there was an invalid search, exit search mode
    if ( iter == document.statusBar.end()){
        SearchOff();
        return;
    }
    else{
        //Replace search_Word with replace_word
        int index = iter - document.statusBar.begin();
        string search_word(document.statusBar.begin(), document.statusBar.begin() + index);
        string replace_word(document.statusBar.begin() + index + 1, document.statusBar.end());

        SearchReplace(search_word, replace_word);
    }
}

//replace search_word with replace_word
void ECEditorController :: SearchReplace(string search_word, string replace_word){
    //Clear highlight when you press ENTER
    window.InitRows();
    SearchClear(search_word);

    //Replace
    int page_start = (page * window.GetRowNumInView());
    DocCtrl.RemoveWords(search_word, replace_word, page_start, page_start+window.GetRowNumInView());

    //make replace_word the new search_word
    document.Find = true;
    document.statusBar.clear();
    for (char letter : replace_word){
        document.statusBar.push_back(letter);
    }

    //refresh view
    ViewLayout();
    window.Refresh();
}

//In SearchMode insert the search needle in the status bar
void ECEditorController :: SearchInput(int key){
    window.InitRows(); 
    document.statusBar.push_back(char(key));

    //Refresh the view
    ViewLayout();
    window.Refresh();
}

//Find and highlight the searchword
void ECEditorController :: SearchFind(){

    int page_start = (page * window.GetRowNumInView());

    //No text to highlight
    if (document.statusBar.size() == 0){
        return;
    }

    //Clear current highlight
    for (auto character : document.statusBar){
        SearchClear(string(1, character));
    }

    //Highlight
    string status_text(document.statusBar.begin(), document.statusBar.end());
    vector<int> indexes; //indexes where to highlight

    for (int row = page_start; row < page_start+window.GetRowNumInView(); row++){
        indexes.clear();
        indexes = document.SearchColor(row, status_text);

        if (indexes.size() == 0){
            continue;
        }
        for (int col : indexes){
            window.SetColor(row - page_start, col, col+status_text.size()-1, TEXT_COLOR_GREEN);
            
        }  
    }
}

//Clear the highlight from the search string.
void ECEditorController :: SearchClear(string text){

    int page_start = (page * window.GetRowNumInView());
 
    //if no specified text, clear highlight using string in statusBar
    if (text == ""){
        string status_text(document.statusBar.begin(), document.statusBar.end());
        vector<int> indexes;

        for (int row = page_start; row < page_start+window.GetRowNumInView(); row++){
            indexes.clear();
            indexes = document.SearchColor(row, status_text);

            if (indexes.size() == 0){
                continue;
            }
            for (int col : indexes){
                window.SetColor(row - page_start, col, col+status_text.size()-1, TEXT_COLOR_DEF);
            
            }  
        }
    }
    else{
        //if there is a string text then clear highlight for the passed in text 
        vector<int> indexes;

        for (int row = page_start; row < page_start+window.GetRowNumInView(); row++){
            indexes.clear();
            indexes = document.SearchColor(row, text);

            if (indexes.size() == 0){
                continue;
            }
            for (int col : indexes){
                window.SetColor(row - page_start, col, col+text.size()-1, TEXT_COLOR_DEF);
            
            }  
        }
    } 
}

//CTRL_Z undo most recent model modification
void ECEditorController :: Undo(){
    int cursorY = window.GetCursorY();

    //UNDO
    window.InitRows();
    DocCtrl.Undo();

    //Cursor Managment
    window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY));
    if (cursorY > document.GetLengthRows()){
        window.SetCursorY(document.GetLengthRows());
    }

    //Refresh the view
    ViewLayout();
    window.Refresh();
}

//CTRL_R re-do the most recent consecutive undo()'s
void ECEditorController :: Redo(){
    int cursorY = window.GetCursorY();

    //REDO
    window.InitRows();
    DocCtrl.Redo();

    //Cursor Managment
    window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY));
    if (cursorY > document.GetLengthRows()){
        window.SetCursorY(document.GetLengthRows());
    }

    //Refresh the view
    ViewLayout();
    window.Refresh();

}

//ENTER key behavior
//EnterKey Function Handles:
//MidLine Enter
//Endline Enter
//Frontline Enter
void ECEditorController :: Enter(){
    
    string empty_line = "";
    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    //Midline Enter 
    if(cursorX < document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY) && cursorX != 0){
        window.InitRows(); 
        string remaining_line = "";
        
        //Create Newline with remaining Text
        for (int i = cursorX; i < document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY); i++){
            remaining_line += document.GetCharAt((page * window.GetRowNumInView()) + cursorY, i);
        }

        //Combine two commands
        MidLineEnter(cursorX, cursorY, remaining_line);

        //Refresh View
        ViewLayout();

    }
    else{
        //Endline Enter 
        if (cursorY == window.GetRowNumInView()-1){
            //Enter at the end of the current page

            window.InitRows();
            
            //Increase Pages
            page += 1; 

            //Add a new line to top of next page
            NewLine(0, empty_line);

            //Cursor Managment 
            window.SetCursorX(0);
            window.SetCursorY(0);

            ViewLayout();

        }
        else if(cursorX == document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY)){
            //Endline Enter mid document
            window.InitRows(); 

            //Add a row below
            NewLine(window.GetCursorY()+1, empty_line);

            window.SetCursorX(0);
            window.SetCursorY(window.GetCursorY()+1);
            //Refresh the view
            ViewLayout();

        }
        else{
            //FrontLine Enter
            window.InitRows(); 
            NewLine(cursorY, empty_line);
            window.SetCursorX(0);
            window.SetCursorY(cursorY);
            ViewLayout();
            
        }     
    }
}

//ENTER in midline, split the text
//midline Enter merges two commands DocCtrl.NewLine() and DocCtrl.RemoveTextAt()
void ECEditorController :: MidLineEnter(int cursorX, int cursorY, string remaining_line){
    //row for NewLine()
    int row_num_one = (page * window.GetRowNumInView())+window.GetCursorY()+1;

    //row for RemoveTextAt()
    int row_num_two = (page * window.GetRowNumInView()) + cursorY;
    
    //DocumentCtrl combines these two commands for Undo() & Redo()
    DocCtrl.combine(row_num_one, remaining_line, row_num_two, cursorX);    
}

//Add a Newline to the Model and View
void ECEditorController :: NewLine(int row, string key){
    DocCtrl.NewLine((page * window.GetRowNumInView()) + row, key);
}

//DELETE key behavior
//Delete Chars and Lines
void ECEditorController :: Backspace(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    //Clear the view to change the model
    window.InitRows(); 

    //If at top of document; Do Nothing
    if (cursorY == 0 && cursorX == 0 && page == 0){
        ViewLayout();
        return;
    }
    else if (document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY) == 0){
        //If Backspace pressed on emptyline, line is removed
        DocCtrl.RemoveLine((page * window.GetRowNumInView()) + cursorY);
        cursorUp();
    }
    else if (cursorX == 0){
        //if cursor at beginning of the line
        //merge the two lines 
        
        //If cursor not at top of document
        if ((page * window.GetRowNumInView()) + cursorY != 0){
            
            //Row, Column, String
            int prev_row = (page * window.GetRowNumInView()) + cursorY - 1;
            int prev_column = document.GetLengthColumns(prev_row);
            string prev_string = document.GetStringAt((page * window.GetRowNumInView()) + cursorY);

            BackspaceMege(prev_row, prev_column, prev_string, (page * window.GetRowNumInView()) + cursorY);

            //Move Cursor Up in correct column 
            window.SetCursorY(cursorY - 1);
            window.SetCursorX(prev_column);

        }
    }
    else{
        //Backspace() Deletes one char based on cursor position
        DocCtrl.Backspace((page * window.GetRowNumInView()) + cursorY, cursorX);

        //Move the cursor accordingly 
        window.SetCursorX(cursorX-1);  
    }
    
    //Refresh the view
    ViewLayout();
}

//DELETE at front of line, merge lines; Combine InsertTextAt() & RemoveLine() commands
void ECEditorController :: BackspaceMege(int prev_row, int prev_column, string prev_string, int del_row){
    DocCtrl.combineBackspace(prev_row, prev_column, prev_string, del_row);
}

//Update the view & model with text 
void ECEditorController :: CharUpdate(int key){

        window.InitRows(); //clear view
        string text = string(1, char(key));    
        InsertText(window.GetCursorY(), window.GetCursorX(), text);
    
        //Refresh the view
        ViewLayout();
        window.Refresh();
}

//CharUpdate Helper function
void ECEditorController :: InsertText(int row, int column, string key){
    DocCtrl.InsertTextAt((page * window.GetRowNumInView()) + row, column, key);
    window.SetCursorX(column + 1);
}


//ARROW_LEFT behavior
void ECEditorController :: cursorLeft(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();
    int curr_row = (page * window.GetRowNumInView()) + cursorY;

    //press left at top of page & there is a previous page
    if(cursorY == 0 && cursorX == 0 && page != 0){
            //clear view
            window.InitRows();
            
            //decrease current page
            page -= 1; 
            
            //if last line from previous page has text, set cursor accordingly
            window.SetCursorY(window.GetRowNumInView()-1);
            window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + (window.GetRowNumInView()-1)));
            

            //Refresh the view
            ViewLayout();
    }
    else if (cursorX == 0 && cursorY != 0){
        //if left pressed at beginning of line mid-document, move up one line
        window.SetCursorY(cursorY-1);
        window.SetCursorX(document.GetLengthColumns(curr_row-1));
    }
    else if(cursorX > 0){
        //if left pressed in a sentence, move cursor to left
        window.SetCursorX(cursorX-1);
    }
    else{
        return;
    }
}

//ARROW_RIGHT behavior
void ECEditorController :: cursorRight(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();
    int curr_row = (page * window.GetRowNumInView()) + cursorY;

    //Press ARROW_RIGHT at end of current page and line; Go to next page
    if ( cursorX == document.GetLengthColumns(curr_row) && curr_row == window.GetRowNumInView()-1 && curr_row != document.GetLengthRows()){
        
        window.InitRows();
            
        page += 1; 

        window.SetCursorY(0);
        window.SetCursorX(0);

        ViewLayout();

    }
    else if (cursorX == document.GetLengthColumns(curr_row) && curr_row != document.GetLengthRows()-1){
        //if right pressed at end of line mid-document; move down one line
        window.SetCursorY(cursorY+1);
        window.SetCursorX(0);
    
    }
    else if(cursorX < document.GetLengthColumns(curr_row)){
        //right pressed mid-line; move cursor to right 
        window.SetCursorX(cursorX + 1);
    }
    else{
        return;
    }
    
}

//ARROW_UP behavior
void ECEditorController :: cursorUp(){
    
    int cursorY = window.GetCursorY();

    //if at top of page and there is a previous page
    if(cursorY == 0 && page != 0){
            window.InitRows();
            
            //decrease current page
            page -= 1; 
            
            
            if (document.GetLengthColumns((page * window.GetRowNumInView())) == 0){
                //if last line from previous page is null set cursor
                window.SetCursorX(0);
                window.SetCursorY(window.GetRowNumInView()-1);

            }
            else{
                //if last line from previous page has text, set cursor accordingly
                window.SetCursorY(window.GetRowNumInView()-1);
                window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + (window.GetRowNumInView()-1)));
            }

            //Refresh the view
            ViewLayout();
    }
    else if(cursorY > 0){
        //Standard Up cursor movement
        window.SetCursorY(cursorY - 1);
        window.SetCursorX(document.GetLengthColumns(((page * window.GetRowNumInView()) + cursorY) - 1));
    }

}

//ARROW_DOWN behavior
void ECEditorController :: cursorDown(){

    int cursorY = window.GetCursorY();
    int curr_row = (page * window.GetRowNumInView()) + cursorY;

    //if at bottom of page and there is a next page
    if (cursorY == window.GetRowNumInView()-1 && curr_row != document.GetLengthRows()){
        window.InitRows();
            
        //decrease current page    
        page += 1; 

        if (document.GetLengthColumns(page * window.GetRowNumInView()) == 0){
            //set cursor to beginning of next line if the line is null
            window.SetCursorY(0);
            window.SetCursorX(0);
        }
        else{     
            window.SetCursorY(0);
            window.SetCursorX(document.GetLengthColumns(page * window.GetRowNumInView()));
        }

        ViewLayout();

    }
    else if(curr_row+1 < document.GetLengthRows()){
        //Standard down cursor movement
        window.SetCursorY(cursorY + 1);
        window.SetCursorX(document.GetLengthColumns(curr_row + 1));

    }
}


