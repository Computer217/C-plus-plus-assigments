#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>
#include <string> 
using namespace std;

class ECTextDocument;

// **********************************************************
// Implements Commands for editing 


// your code goes here
class InsertCommand : public ECCommand {
    public:
        InsertCommand(ECTextDocument &document,  int row, int column, string &listCharsToIns): doc(document), row(row), column(column), LCTI(listCharsToIns){}
        virtual void Execute();
        virtual void UnExecute();

    private:
        ECTextDocument &doc;
        int row;
        int column;
        string &LCTI;

};

class AddCommand : public ECCommand {
    public:
        AddCommand(ECTextDocument &document, string value): doc(document), LCTI(value){}
        virtual void Execute();
        virtual void UnExecute();

    private:
        ECTextDocument &doc;
        string LCTI;

};

class NewCommand : public ECCommand {
    public:
        NewCommand(ECTextDocument &document, int row, string key): doc(document), row(row), LCTI(key){}
        virtual void Execute();
        virtual void UnExecute();

    private:
        ECTextDocument &doc;
        int row;
        string LCTI;

};

class RemoveCommand : public ECCommand {
    public:
        RemoveCommand(ECTextDocument &document, int row, int column): doc(document), row(row), column(column){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
        int column;
};

class BackspaceCommand: public ECCommand {
    public:
        BackspaceCommand(ECTextDocument &document, int row, int column): doc(document), row(row), column(column){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
        int column;
};

class RemoveLineCommand: public ECCommand {
    public:
        RemoveLineCommand(ECTextDocument &document, int row): doc(document), row(row){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
};

// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int row, int column, string &listCharsToIns);    // insert a list of characters starting at position
    void RemoveTextAt(int row, int column);
    void AddRow(string value);
    void NewLine(int row, string key);
    void RemoveLine(int row);
    void Backspace(int row, int column);
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
    string GetCharAt(int row, int column);          // get char at current position
    void InsertCharAt(int row, int column, string ch);    // insert a single char at position
    void RemoveCharAt(int row, int column);
    std::vector<string> GetChars(){return listChars;}
    int GetLengthColumns(int pos){
        return listChars[pos].size();
    }
    int GetLengthRows(){
        return listChars.size();
    }
    void addrow(string value){
        listChars.push_back(value);
    }
    void NewLine(int row, string key){
        listChars.insert(listChars.begin()+row, key);
    }
    void RemoveLineAt(int row){
        listChars.erase(listChars.begin()+row);
    }
    void EraseText(int row, int column){
        listChars[row].erase(listChars[row].begin() + column, listChars[row].end());
    }
    string GetStringAt(int row){
        return listChars[row];
    }

private:
    ECTextDocumentCtrl docCtrl;
    std::vector<string> listChars = {""};

};


#endif /* ECTextDocument_h */