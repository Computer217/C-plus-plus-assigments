//
//  ECTextDocument.h
//  
//
//  Created by Yufeng Wu on 2/26/20.
//
//

#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>
using namespace std;

class ECTextDocument;

// **********************************************************
// Implements Commands for editing 


// your code goes here

class InsertCommand : public ECCommand {
    public:
        InsertCommand(ECTextDocument &document,  int index, const std::vector<char> &listCharsToIns): doc(document), pos(index), LCTI(listCharsToIns){}
        virtual void Execute();
        virtual void UnExecute();

    private:
        ECTextDocument &doc;
        int pos;
        const std::vector<char> &LCTI;

};

class RemoveTextCommand : public ECCommand {
    public:
        RemoveTextCommand(ECTextDocument &document, int index, int len): doc(document), pos(index), lenToRemove(len){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int pos;
        int lenToRemove;
        vector<char> state;
        

};

class CapTextCommand : public ECCommand{
    public:
        CapTextCommand(ECTextDocument &document, int index, int len): doc(document), pos(index), lenToCap(len){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int pos;
        int lenToCap;
    
};

class LowerTextCommand : public ECCommand{
    public:
        LowerTextCommand(ECTextDocument &document, int index, int len): doc(document), pos(index), lenToLower(len){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int pos;
        int lenToLower;
        
};


// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int pos, const std::vector<char> &listCharsToIns);    // insert a list of characters starting at position
    void RemoveTextAt(int pos, int lenToRemove);                            // remove a segment of characters  of lenToRemove starting from pos
    void CapTextAt(int pos, int lenToCap);                                  // Capitalize the text of lenToCap long starting from pos
    void LowerTextAt(int pos, int lenToLower);                              // Lowercase the text of lenToLoer starting from pos
    bool Undo();                                                            // undo any change you did to the text
    bool Redo();                                                            // redo the change to the text
    
private:
    ECTextDocument &doc;
    ECCommandHistory histCmds;
};

// **********************************************************
// Document for text document

class ECTextDocument
{
public:
    ECTextDocument();
    virtual ~ECTextDocument();
    ECTextDocumentCtrl &GetCtrl();          // return document controller
    int GetDocLen() const { return listChars.size(); }
    char GetCharAt(int pos) const;          // get char at current position
    void InsertCharAt(int pos, char ch);    // insert a single char at position
    void RemoveCharAt(int pos);             // erase a single char at position
    void CapCharAt(int pos);                // capitalize the char at position
    void LowerCharAt(int pos);              // lowercase the char at position
    
private:
    ECTextDocumentCtrl docCtrl;
    std::vector<char> listChars;
};


#endif /* ECTextDocument_h */
