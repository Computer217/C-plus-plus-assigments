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

//StartView
int main(int argc, char *argv[])
{
    if (argc != 2){
        cout << "ERROR: Please specify a file name -- e.g File.txt" << endl;
        return 1;
    }
    
    ECEditorView *Program = new ECEditorView(argv[1]);
    Program->Start();

    delete Program;

    return 0;
}