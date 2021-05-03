//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#include "ECEditorController.h"
#include "ECEditorView.h"
#include <iostream>

using namespace std;

//Constructor add EditorController 
ECEditorView :: ECEditorView(string file): window(ECTextViewImp()), ctrl(ECEditorController(window, file)){
    window.Attach(&ctrl);
}

ECEditorView :: ~ECEditorView(){}


void ECEditorView :: Start(){
    //clearRows before showing the Document/Model
    window.InitRows();
    //Read from specified text file 
    ctrl.ReadFile();
    //display read file data
    ctrl.ViewLayout();
    //enter infinite loop to observe commands
    window.Show();
}

//Start Editor Program!
int main(int argc, char *argv[])
{
    //if no file name is specified when calling the editor
    if (argc != 2){
        cout << "ERROR: Please specify a file name -- e.g File.txt" << endl;
        return 1;
    }
    
    ECEditorView *Program = new ECEditorView(argv[1]);
    Program->Start();

    delete Program;

    return 0;
}