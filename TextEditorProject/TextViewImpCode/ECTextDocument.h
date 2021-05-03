#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>
#include <string> 
#include <iostream>
using namespace std;

class ECTextDocument;

// **********************************************************
// Command Design Pattern
// Commands used to directly modify the model (document)
//Command classes used by DocCtrl 

// InsertTextAt() Command 
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

//RemoveTextat() Command
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


//Backspace() Command
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

//NewLine() Command
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

//RemoveLine() Command
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

//combine() command
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

//combineBackspace() command
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

//RemoveWords() command
class WordsCommand: public ECCommand {
    public:
        WordsCommand(ECTextDocument &document, string &SearchIn, string &ReplaceIn, int row_start, int row_end): doc(document), search(SearchIn), replace(ReplaceIn), row_start(row_start), row_end(row_end){}
        virtual void Execute();
        virtual void UnExecute();
    private:
        ECTextDocument &doc;
        string &search; 
        std::vector<string> string_search;
        string &replace;
        std::vector<string> string_replace;
        int row_start;
        int row_end;
};

// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument &docIn); // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl(); //DocCtrl Destructor

    //Commands
    void InsertTextAt(int row, int column, string &listCharsToIns); //insert a string at (row, column)
    void RemoveTextAt(int row, int column); // remove a char at (row,column)
    void Backspace(int row, int column); //Delete a char at (row,column)
    void NewLine(int row, string key); //insert a Line (key) at (row)
    void RemoveLine(int row); //Remove a Line at (row)
    void combine(int row, string key, int two_row, int two_col); //Combine commands for ENTER 
    void combineBackspace(int prev_row, int prev_column, string prev_string, int del_row); //Combine commands for Backspace
    void RemoveWords(string search, string replace, int row_start, int row_end); //Replace a search string with replace string
    bool Undo(); // undo any change you did to the text
    bool Redo(); // redo the change to the text
    
private:
    ECTextDocument &doc;
    ECCommandHistory histCmds;
};

// **********************************************************
// Document for text document

class ECTextDocument
{
public:
    ECTextDocument(); //document constructor
    virtual ~ECTextDocument(); // document destructor
    ECTextDocumentCtrl &GetCtrl(); // return document controller
    int GetDocLen() const { return listChars.size(); } 

    //listChars (document) Methods
    string GetCharAt(int row, int column); // get char at current position
    void InsertCharAt(int row, int column, string ch); // insert a single char at position
    void RemoveCharAt(int row, int column); //remove a single char at position 
    std::vector<string> GetChars(){return listChars;} //Get a copy of the document
    int GetLengthColumns(int pos); //Get the number of columns at row (pos)
    int GetLengthRows(); //Get the number of rows 
    void addrow(string value); //append a row to the document
    void removerow(); // remove the last line of the document
    void NewLine(int row, string key); //insert a specific line to the document at row
    void RemoveLineAt(int row); //remove a specific line of the document
    void EraseText(int row, int column); //delete the rest of the row from column.begin() to column.end()
    void AddText(int row, string text); //add text to an existing line located at row
    string GetStringAt(int row);  //Get the line at row
    string GetSubString(int row, int column); //get remainder of the line located at (row,column)

    //statusBar Methods
    std::vector<int> SearchColor(int row, string text); //Find the indexes of a _text_ in the line located at row

    //Replace occurances of search string with replace string
    void RemoveWords(string search, string replace, int row_start, int row_end); 


    std::vector<char> statusBar = {' '}; //status bar public since the user directly interacts with it.
    bool Search = false; //toggle between Insert and Search mode
    bool Find = true; //Toggle to highlight text inside the statusBar

private:
    ECTextDocumentCtrl docCtrl; //document controler
    std::vector<string> listChars = {""};

};


#endif /* ECTextDocument_h */