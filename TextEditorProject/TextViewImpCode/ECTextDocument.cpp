#include "ECTextDocument.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

// **********************************************************
// Commands

// your code goes here 


// InsertCommand
void InsertCommand :: Execute(){
    int curr = column;
    
    for (auto c : LCTI){
        doc.InsertCharAt(row, curr, string(1, c));
        curr++;
    }
}

void InsertCommand :: UnExecute(){
  for (int i=0; i<LCTI.size(); i++){
    doc.RemoveCharAt(row, column);
  }
}

void RemoveCommand :: Execute(){
  doc.EraseText(row, column);
    
}

void RemoveCommand :: UnExecute(){
   //RemoveTextAt Unexecute
}

void AddCommand :: Execute(){
  doc.addrow(LCTI);
}

void AddCommand :: UnExecute(){
  //need to remove the LTCI
}

void NewCommand :: Execute(){
  doc.NewLine(row, LCTI);
}

void NewCommand :: UnExecute(){
  //need to remove the LTCI
}

void BackspaceCommand :: Execute(){
  doc.RemoveCharAt(row, column);
}

void BackspaceCommand :: UnExecute(){
  //UnExecuteBackSpace
  
}

void RemoveLineCommand :: Execute(){
  doc.RemoveLineAt(row);
}

void RemoveLineCommand :: UnExecute(){
  //UnExecuteBackSpace
  
}

// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : doc(docIn)
{
}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl()
{
}

void ECTextDocumentCtrl :: InsertTextAt(int row, int column, string &listCharsToIns)
{
  // your code
  //cout << "document controller" << endl;
  histCmds.ExecuteCmd(new InsertCommand(doc, row, column, listCharsToIns));

}

void ECTextDocumentCtrl :: RemoveTextAt(int row, int column){
    histCmds.ExecuteCmd(new RemoveCommand(doc, row, column));
}


void ECTextDocumentCtrl :: AddRow(string value)
{
  // your code
  //cout << "document controller" << endl;
  histCmds.ExecuteCmd(new AddCommand(doc, value));

}

void ECTextDocumentCtrl :: NewLine(int row, string key)
{
  // your code
  histCmds.ExecuteCmd(new NewCommand(doc, row, key));

}

void ECTextDocumentCtrl :: RemoveLine(int row)
{
  histCmds.ExecuteCmd(new RemoveLineCommand(doc, row));
}

void ECTextDocumentCtrl :: Backspace(int row, int column)
{
  // your code
  //cout << "document controller" << endl;
  histCmds.ExecuteCmd(new BackspaceCommand(doc, row, column));

}

bool ECTextDocumentCtrl :: Undo()
{
  // your code
  if (histCmds.Undo()){
    return true;
  }

  return false;
}

bool ECTextDocumentCtrl :: Redo()
{
  // your code
  if (histCmds.Redo()){
    return true;
  }

  return false;
}

// **********************************************************
// Document for text document


ECTextDocument :: ECTextDocument() : docCtrl(*this)
{
}

ECTextDocument :: ~ECTextDocument()
{
}

ECTextDocumentCtrl & ECTextDocument :: GetCtrl()
{
    return docCtrl;
}


string ECTextDocument :: GetCharAt(int row, int column)
{
    string List = listChars[row];
    string Char = string(1, List[column]);
    return Char;
}



void ECTextDocument :: InsertCharAt(int row, int column, string ch)
{
  // your code here

  listChars[row].insert(column, ch);

}

void ECTextDocument :: RemoveCharAt(int row, int column)
{
  listChars[row].erase(column-1,1);
  
}
