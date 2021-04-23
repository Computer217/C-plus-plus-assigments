//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#include "ECTextViewImp.h"
#include "ECTextDocument.h"
#include "ECEditorController.h"
#include "ECCommand.h"
#include <iostream>
#include <string>
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
}

void ECEditorController :: Undo(){
    int cursorY = window.GetCursorY();
    //int cursorX = window.GetCursorX(); need to do vertical positioning

    window.InitRows();
    DocCtrl.Undo();

    window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY));

    //Refresh the view
    ViewLayout();
    window.Refresh();
}

void ECEditorController :: Redo(){
    int cursorY = window.GetCursorY();
    //int cursorX = window.GetCursorX(); need to do vertical positioning

    window.InitRows();
    DocCtrl.Redo();

    window.SetCursorX(document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY));

    //Refresh the view
    ViewLayout();
    window.Refresh();

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

    //Set the status Row with correct Page Display
    window.ClearStatusRows();
    window.AddStatusRow("Pablo's TextEditor", "Page: " + to_string(page+1) + " ", true);

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

//EnterKey Function Handles:
//MidLine Enter
//Endline Enter
//Frontline Enter

void ECEditorController :: Enter(){
    
    string empty_line = "";
    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    //Midline Enter [WORKING]
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
        //Endline Enter Function [WORKING]
        //***********************
        //PAGE LAYOUT MANAGMENT *
        //***********************
        //-1 because it needs to account for index vs size
        if (cursorY == window.GetRowNumInView()-1){
            window.InitRows();
            
            //Increase Pages
            page += 1; 

            NewLine(0, empty_line);

            window.SetCursorX(0);
            window.SetCursorY(0);

            ViewLayout();

        }
        else if(cursorX == document.GetLengthColumns((page * window.GetRowNumInView()) + cursorY)){
            //Endline Enter
            window.InitRows(); 

            //Add a row on top
            NewLine(window.GetCursorY()+1, empty_line);

            window.SetCursorX(0);
            window.SetCursorY(window.GetCursorY()+1);
            //Refresh the view
            ViewLayout();

        }
        else{
            //FrontLine Enter
            window.InitRows(); 

            //Add a row on top
            NewLine(window.GetCursorY()-1, empty_line);

            window.SetCursorX(0);
            window.SetCursorY(window.GetCursorY()-1);
            //Refresh the view
            ViewLayout();
        }     
    }
}

//midline Enter
void ECEditorController :: MidLineEnter(int cursorX, int cursorY, string remaining_line){

    DocCtrl.combine((page * window.GetRowNumInView())+window.GetCursorY()+1,remaining_line, (page * window.GetRowNumInView()) + cursorY, cursorX);

    /*
    DocCtrl.NewLine((page * window.GetRowNumInView())+window.GetCursorY()+1, remaining_line);
    //Remove Remaining text from current line 
    DocCtrl.RemoveTextAt((page * window.GetRowNumInView()) + cursorY, cursorX);
    */
    
}

//Create a new Line
void ECEditorController :: NewLine(int row, string key){
    DocCtrl.NewLine((page * window.GetRowNumInView()) + row, key);
}

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

//midline Enter
void ECEditorController :: BackspaceMege(int prev_row, int prev_column, string prev_string, int del_row){

    DocCtrl.combineBackspace(prev_row, prev_column, prev_string, del_row);

    /*
        //Append current row to previous Row
        DocCtrl.InsertTextAt(prev_row, prev_column, prev_string);

        //delete current row
        DocCtrl.RemoveLine((page * window.GetRowNumInView()) + cursorY);
    
    */
    
}
    
//Move the cursor Left
void ECEditorController :: cursorLeft(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    if (cursorX == 0 && cursorY != 0){
        window.SetCursorY(cursorY-1);
        window.SetCursorX(document.GetLengthColumns(cursorY-1));
    }
    else if(cursorX > 0){
        window.SetCursorX(cursorX-1);
    }
    else{
        return;
    }
}

//Move the cursor Right
void ECEditorController :: cursorRight(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    if (cursorX == document.GetLengthColumns(cursorY) && cursorY != document.GetLengthRows()-1){
        window.SetCursorY(cursorY+1);
        window.SetCursorX(0);
    
    }
    else if(cursorX < document.GetLengthColumns(cursorY)){
        window.SetCursorX(cursorX + 1);
    }
    else{
        return;
    }
    
}

//Move the cursor Up 
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

//Move the cursor Down 
void ECEditorController :: cursorDown(){

    int cursorY = window.GetCursorY();

    //***********************
    //PAGE LAYOUT MANAGMENT *
    //***********************
    if (cursorY == window.GetRowNumInView()-1 && cursorY*page != document.GetLengthRows()){
        window.InitRows();
            
        page += 1; 

        if (document.GetLengthColumns(page * window.GetRowNumInView()) == 0){
            window.SetCursorY(0);
            window.SetCursorX(0);
        }
        else{
            window.SetCursorY(0);
            window.SetCursorX(document.GetLengthColumns(page * window.GetRowNumInView()));
        }

        ViewLayout();

    }
    else if(cursorY < document.GetLengthRows()){
        //Regular DownMovement
        window.SetCursorY(cursorY + 1);
        window.SetCursorX(document.GetLengthColumns(((page * window.GetRowNumInView()) + cursorY) + 1));

    }
}

//Handle insertig text to the document
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
