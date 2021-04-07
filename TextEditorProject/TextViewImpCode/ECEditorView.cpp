//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#include "ECEditorController.h"
#include "ECEditorView.h"
#include <iostream>

using namespace std;

//Constructor add EditorController 
ECEditorView :: ECEditorView(): window(ECTextViewImp()), ctrl(ECEditorController(window)){
    window.Attach(&ctrl);
}

ECEditorView :: ~ECEditorView(){}

//StartView
int main(int argc, char *argv[])
{
    ECEditorView *Program = new ECEditorView();

    Program->Start();

    return 0;
}