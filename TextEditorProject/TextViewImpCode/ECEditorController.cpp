//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#include "ECTextViewImp.h"
#include "ECTextDocument.h"
#include "ECEditorController.h"
#include "ECCommand.h"


//Constructor
ECEditorController :: ECEditorController(ECTextViewImp &WndIn): window(WndIn), document(ECTextDocument()), DocCtrl(document.GetCtrl()){}        // conroller constructor takes the document as input

//ReadKey from STDIO
void ECEditorController :: Update(){
    int key = window.GetPressedKey();

    if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN || key == ENTER){
        this->CursorUpdate(key);
    }
    else if (key>=32){   
        this->CharUpdate(key);
    }
}

//Proccess Read Key
void ECEditorController :: CursorUpdate(int key){

    switch (key) {
        case ENTER:
            AddRowAt();
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

//EnterKey Function Handles:
//Endline Enter
//MidLine Enter
void ECEditorController :: AddRowAt(){
    
    string empty_line = "";
    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    if(cursorX < document.GetLengthColumns(cursorY)){
        window.InitRows(); 
        string remaining_line = "";
        
        //Create Newline with remaining Text
        for (int i = cursorX; i < document.GetLengthColumns(cursorY); i++){
            remaining_line += document.GetCharAt(cursorY, i);
        }
        NewLine(window.GetCursorY()+1,remaining_line);

        //Remove Remaining text from current line 
        DocCtrl.RemoveTextAt(cursorY, cursorX);


        //Refresh View
        for (auto str : document.GetChars()){
            window.AddRow(str);
        }

    }
    else{
        //Endline Enter Function [WORKING]
        window.InitRows(); 

        //string test = " TEST";

        NewLine(window.GetCursorY()+1, empty_line);

        //set cursor down [WORKING]
        window.SetCursorX(0);
        window.SetCursorY(window.GetCursorY()+1);

        for (auto str : document.GetChars()){
            window.AddRow(str);
        }
            
    }

}

/*    else if (window.GetCursorX() == document.GetLengthColumns(window.GetCursorY())){
        //at end of line, add line below current line
        

        if (window.GetCursorY() == document.GetLengthRows()-1){
            DocCtrl.AddRow(empty_line);
            window.AddRow(empty_line);

            window.SetCursorX(0);
            window.SetCursorY(window.GetCursorY()+1);
            
        }
        */

//Create a new Line, using document/view controller
void ECEditorController :: NewLine(int row, string key){
    DocCtrl.NewLine(row, key);
}
    
//Move the cursor Left
void ECEditorController :: cursorLeft(){

    int cursorX = window.GetCursorX();

    if(cursorX > 0){
        window.SetCursorX(cursorX-1);
    }
}

//Move the cursor Right
void ECEditorController :: cursorRight(){

    int cursorX = window.GetCursorX();
    int cursorY = window.GetCursorY();

    if(cursorX < document.GetLengthColumns(cursorY)){
        window.SetCursorX(cursorX + 1);
    }
    else{
        //check if last line, make new line and set cursor
        if (cursorY < document.GetLengthRows() - 1){
            window.SetCursorY(cursorY - 1);
        }
    }
    
}

//Move the cursor Up 
void ECEditorController :: cursorUp(){
    
    int cursorY = window.GetCursorY();

    if(cursorY > 0){
        window.SetCursorY(cursorY - 1);
        window.SetCursorX(document.GetLengthColumns(cursorY-1));
    }

}

//Move the cursor Down 
void ECEditorController :: cursorDown(){

    int cursorY = window.GetCursorY();

    if(cursorY < document.GetLengthRows()){
        window.SetCursorY(cursorY + 1);
        window.SetCursorX(document.GetLengthColumns(cursorY+1));

    }
}

//Handle insertig text
void ECEditorController :: CharUpdate(int key){
    window.InitRows(); //clear view
    string text = string(1, char(key));    
    InsertText(window.GetCursorY(), window.GetCursorX(), text);
    
    
    for (auto str : document.GetChars()){
        window.AddRow(str);
    }
    

    window.Refresh();
}

//CharUpdate Helper function
void ECEditorController :: InsertText(int row, int column, string key){
    DocCtrl.InsertTextAt(row, column, key);
    window.SetCursorX(column + 1);
}
