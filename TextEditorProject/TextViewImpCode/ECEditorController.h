//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#ifndef ECEditorController_h
#define ECEditorController_h

#include "ECTextViewImp.h"
#include "ECObserver.h"
#include "ECTextDocument.h"
#include "ECCommand.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ECEditorController : public ECObserver
{
public:
    ECEditorController(ECTextViewImp &WndIn, string file);
    virtual ~ECEditorController();

    //I/O File Handling
    void Save(); //Save the contents of the file before exiting the program
    void ReadFile(); //read from specified file and populate model and update view 

    //Stdin Key handling
    void Update(); //modifying the model and update the view
    void CursorUpdate(int key); //Update the position of the cursor
    void ViewLayout(); //Update the view with text with respect to page number

    //SearchMode Methods
    void SearchOn(); //CTRL_F Toggle to Search Mode 
    void SearchOff(); //ESC Toggle to insert Mode
    void SearchBackspace(); //DELETE characters from the search needle in the status bar
    void SearchEnter(); //ENTER, replace search word with replace word
    void SearchReplace(string search_word, string replace_word); //replace search word with replace word (Command)
    void SearchInput(int key); //In SearchMode insert the search needle in the status bar
    void SearchFind(); //Find and highlight the searchword
    void SearchClear(string text = ""); //Clear the highlight from the search string.

    //InsertMode Methods (Commands)
    void Undo(); //CTRL_Z undo most recent model modification
    void Redo(); //CTRL_Y re-do the most recent consecutive undo()'s
    void Enter(); //ENTER key behavior
    void MidLineEnter(int cursorX, int cursorY, string remaining_line); //ENTER in midline, split the text
    void NewLine(int row, string key); //Add a Newline to the Model and View
    void Backspace(); //DELETE key behavior
    void BackspaceMege(int prev_row, int prev_column, string prev_string, int row);//DELETE at front of line, merge lines
    void CharUpdate(int key); //Update the view & model with text 
    void InsertText(int row, int column, string key); //CharUpdate Helper function

    //Cursor Movement Methods
    void cursorLeft(); //ARROW_LEFT behavior
    void cursorRight(); //ARROW_RIGHT behavior
    void cursorUp(); //ARROW_UP behavior
    void cursorDown(); //ARROW_DOWN behavior

private:
    ECTextViewImp &window; //View
    ECTextDocument document; //Model
    ECTextDocumentCtrl &DocCtrl; //Controller
    int page; //Pages
    string file; //File
};

#endif /* ECEditorController_h */