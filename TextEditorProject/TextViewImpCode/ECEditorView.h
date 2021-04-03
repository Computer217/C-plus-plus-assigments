//****************************************
//Created By Pablo Rodriguez on 03/25/21 *
//****************************************

#ifndef ECEditorView_h
#define ECEditorView_h

#include "ECTextViewImp.h"
#include "ECEditorController.h"
#include <iostream>

using namespace std;


class ECEditorView{
    public:
        ECEditorView();
        virtual ~ECEditorView();
        //void Show();

        void Start(){
            //clearRows before showing document()
            window.InitRows();
            //enter infinite loop
            window.AddStatusRow("TextEditor", "Pablo", true);
            window.Show();
        }
    
    private:
        ECTextViewImp window;
        ECEditorController ctrl;

};



#endif /* ECEditorView_h */