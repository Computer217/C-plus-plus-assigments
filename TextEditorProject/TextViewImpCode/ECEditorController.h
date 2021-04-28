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

    void Update(); //modifying the model and then updating the view in update 
    void Save();
    void ReadFile();
    void Undo();
    void Redo();
    void Search(int key);
    void CursorUpdate(int key);
    void Enter();
    void MidLineEnter(int cursorX, int cursorY, string remaining_line);
    void NewLine(int row, string key);
    void Backspace();
    void BackspaceMege(int prev_row, int prev_column, string prev_string, int row);
    void cursorLeft();
    void cursorRight();
    void cursorUp();
    void cursorDown();
    void CharUpdate(int key);
    void InsertText(int row, int column, string key);
    void ViewLayout();
    


private:
    ECTextViewImp &window;
    ECTextDocument document;
    ECTextDocumentCtrl &DocCtrl;
    int page;
    string file;
};

#endif /* ECEditorController_h */