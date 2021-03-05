//
//  ECTextDocumentTest.cpp
//  
//
//  Created by Yufeng Wu on 2/26/20.
//
//

#include <iostream>
#include "ECTextDocument.h"

using namespace  std;

static void Test1()
{
    //
    ECTextDocument doc;
    ECTextDocumentCtrl &docCtrl = doc.GetCtrl();
    vector<char> listText1;
    listText1.push_back('a');
    listText1.push_back('b');
    listText1.push_back('c');
    listText1.push_back('d');
    listText1.push_back('e');
    docCtrl.InsertTextAt(0, listText1);


    vector<char> listText2;
    listText2.push_back('f');
    listText2.push_back('g');
    listText2.push_back('h');
    int posIns = 2;
    docCtrl.InsertTextAt(posIns, listText2);

    int posDel = 1;
	int lenDel = 1;
	docCtrl.RemoveTextAt( posDel, lenDel );

        cout << "Text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;


	docCtrl.CapTextAt(2, 3);

        cout << "Text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;



	docCtrl.LowerTextAt(3,1);

        cout << "Text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;



	docCtrl.Undo();

    cout << "Text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;



	docCtrl.Undo();
	

    cout << "Text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;

    
    docCtrl.Redo();

    cout << "After redo, text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;


    docCtrl.Redo();
    cout << "After redo, text: ";
    for(int i=0; i<doc.GetDocLen(); ++i)
    {
        cout << doc.GetCharAt(i);
    }
    cout << endl;
}

int main()
{
    // test code
    Test1();
    
    return 0;
}

