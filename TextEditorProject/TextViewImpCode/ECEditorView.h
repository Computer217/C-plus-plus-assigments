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
        ECEditorView(string file);
        virtual ~ECEditorView();
        //void Show();

        void Start(){
            //clearRows before showing document()
            window.InitRows();

            //Read from specified text file 
            ctrl.ReadFile();
            ctrl.ViewLayout();

            //enter infinite loop to observe commands
            window.Show();
        }
    
    private:
        ECTextViewImp window;
        ECEditorController ctrl;

};



#endif /* ECEditorView_h */