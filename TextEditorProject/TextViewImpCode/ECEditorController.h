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


using namespace std;


class ECEditorController : public ECObserver
{
public:
    ECEditorController(ECTextViewImp &WndIn);
    virtual ~ECEditorController(){}

    //void Show(){window.Show();}

    void Update(); //modifying the model and then updating the view in update 
    void CursorUpdate(int key);
    void AddRowAt();
    void Backspace();
    void NewLine(int row, string key);
    void cursorLeft();
    void cursorRight();
    void cursorUp();
    void cursorDown();
    void CharUpdate(int key);
    void InsertText(int row, int column, string key);


private:
    ECTextViewImp &window;
    ECTextDocument document;
    ECTextDocumentCtrl &DocCtrl;

};

#endif /* ECEditorController_h */