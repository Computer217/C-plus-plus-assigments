#include "ECTextDocument.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

// **********************************************************
// Created By Pablo Rodriguez 2/17/21
// Commands

// InsertTextAt Command ------------------------------
void InsertCommand :: Execute(){
  strvec.push_back(LCTI);
  doc.InsertCharAt(row, column, strvec[0]);
}

void InsertCommand :: UnExecute(){
  if (doc.GetLengthColumns(row) != 0){
    doc.RemoveCharAt(row, column+1);
  }
}

//RemoveTextAt Command ------------------------------
void RemoveCommand :: Execute(){
  strvec.push_back(LCTI);
  doc.EraseText(row, column);
}

void RemoveCommand :: UnExecute(){
  //RemoveTextAt Unexecute
  doc.AddText(row, strvec[0]);
}

//BackSpace Command ------------------------------
void BackspaceCommand :: Execute(){
  doc.RemoveCharAt(row, column);
}

void BackspaceCommand :: UnExecute(){
  //UnExecuteBackSpace
  doc.InsertCharAt(row,column-1, character);
  
}

//NewLine at row Command ------------------------------
void NewCommand :: Execute(){
  doc.NewLine(row, LCTI);
}

void NewCommand :: UnExecute(){
  doc.RemoveLineAt(row);
}

//RemoveLine Command ------------------------------
void RemoveLineCommand :: Execute(){
  //ADDED MIGHT BREAK-----
  strvec.push_back(LCTI);
  doc.RemoveLineAt(row);
}

void RemoveLineCommand :: UnExecute(){
  //UnExecuteBackSpace
  doc.NewLine(row, strvec[0]);
}

//Combine Command ------------------------------

void CombineCommand :: Execute(){
  //First Comand NewLine
  strvecc.push_back(LCTI);
  doc.NewLine(row, strvecc[0]);

  //Second Command RemoveTextAt
  strvec.push_back(two_LCTI);
  doc.EraseText(two_row, two_col);
}

void CombineCommand :: UnExecute(){
  //UnExecute Second Comand
  doc.AddText(two_row, strvec[0]);
  //UnExecute First Command
  doc.RemoveLineAt(row);
}

//BackSpace Comand ------------------------------

void CombineBackspaceCommand :: Execute(){
  //First Comand TextInsertAt
  strvec.push_back(LCTI);
  doc.InsertCharAt(row, col, strvec[0]);

  //Second Command RemoveLine
  strtwovec.push_back(two_LCTI);
  doc.RemoveLineAt(two_row);

}

void CombineBackspaceCommand :: UnExecute(){
  //UnExecute Second Comand
  doc.NewLine(two_row, strvec[0]);
  
  //UnExecute First Command
  doc.EraseText(row, col);
  
}

// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : doc(docIn){}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl(){}

void ECTextDocumentCtrl :: InsertTextAt(int row, int column, string &listCharsToIns)
{
  histCmds.ExecuteCmd(new InsertCommand(doc, row, column, listCharsToIns));
}

void ECTextDocumentCtrl :: RemoveTextAt(int row, int column)
{
  string text_removed = doc.GetSubString(row, column); 
  histCmds.ExecuteCmd(new RemoveCommand(doc, row, column, text_removed));
}

void ECTextDocumentCtrl :: NewLine(int row, string key)
{
  histCmds.ExecuteCmd(new NewCommand(doc, row, key));
}

void ECTextDocumentCtrl :: RemoveLine(int row)
{
  string text_removed = doc.GetStringAt(row);
  histCmds.ExecuteCmd(new RemoveLineCommand(doc, row, text_removed));
}

void ECTextDocumentCtrl :: Backspace(int row, int column)
{
  string character = doc.GetCharAt(row, column-1);
  histCmds.ExecuteCmd(new BackspaceCommand(doc, row, column, character));
}

void ECTextDocumentCtrl :: combine(int row, string key, int two_row, int two_col){
  string text_removed = doc.GetSubString(two_row, two_col); 
  histCmds.ExecuteCmd(new CombineCommand(doc, row, key, two_row, two_col, text_removed));
}

void ECTextDocumentCtrl :: combineBackspace(int prev_row, int prev_column, string prev_string, int del_row){
  string text_removed = doc.GetStringAt(del_row); 
  histCmds.ExecuteCmd(new CombineBackspaceCommand(doc, prev_row, prev_column, prev_string, del_row, text_removed));
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
