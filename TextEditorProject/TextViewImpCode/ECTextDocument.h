#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>
#include <string> 
using namespace std;

class ECTextDocument;

// **********************************************************
// Implements Commands for editing 


// InsertTextAt Command 
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
        std::vector<string> strvec;
};

//RemoveCommand
class RemoveCommand : public ECCommand {
    public:
        RemoveCommand(ECTextDocument &document, int row, int column, string &strRemoved): doc(document), row(row), column(column), LCTI(strRemoved){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
        int column;
        string &LCTI; 
        std::vector<string> strvec;
};


//Delete Key Command
class BackspaceCommand: public ECCommand {
    public:
        BackspaceCommand(ECTextDocument &document, int row, int column, string characterIn): doc(document), row(row), column(column), character(characterIn){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
        int column;
        string character;
};

//NewLine (Add a Line at an index)
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

class RemoveLineCommand: public ECCommand {
    public:
        RemoveLineCommand(ECTextDocument &document, int row, string &key): doc(document), row(row), LCTI(key) {}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        int row;
        string &LCTI; 
        std::vector<string> strvec;
};

class CombineCommand: public ECCommand {
    public:
        CombineCommand(ECTextDocument &document, int row, string &key, int two_row, int two_col, string &str): doc(document), row(row), LCTI(key), two_row(two_row), two_col(two_col), two_LCTI(str){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        //first command
        int row;
        string &LCTI; 
        std::vector<string> strvecc;
        //Second Command
        int two_row;
        int two_col;
        string &two_LCTI;
        std::vector<string> strvec;
};

class CombineBackspaceCommand: public ECCommand {
    public:
        CombineBackspaceCommand(ECTextDocument &document, int row, int col, string &key, int two_row, string &str): doc(document), row(row), col(col), LCTI(key), two_row(two_row), two_LCTI(str){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        //first command
        int row;
        int col;
        string &LCTI; 
        std::vector<string> strvec;
        //Second Command
        int two_row;
        string &two_LCTI;
        std::vector<string> strtwovec;
};

// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();                      //DocCtrl Destructor
    void InsertTextAt(int row, int column, string &listCharsToIns);    // insert a string at (row, column)
    void Backspace(int row, int column);                //Delete chars
    void RemoveTextAt(int row, int column);
    void NewLine(int row, string key);
    void RemoveLine(int row);
    void combine(int row, string key, int two_row, int two_col);
    void combineBackspace(int prev_row, int prev_column, string prev_string, int del_row);
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
    void removerow(){
        listChars.pop_back();
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
    void AddText(int row, string text){
        for (auto txt:text){
            listChars[row].push_back(txt);
        }
    }
    string GetStringAt(int row){
        return listChars[row];
    }
    string GetSubString(int row, int column){
        return listChars[row].substr(column);
    }

private:
    ECTextDocumentCtrl docCtrl;
    std::vector<string> listChars = {""};
    std::vector<string> statusBar = {""};

};


#endif /* ECTextDocument_h */