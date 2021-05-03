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
  if (strvec.size()==0){
    strvec.push_back(LCTI);
  }
  
  doc.InsertCharAt(row, column, strvec[0]);
}

void InsertCommand :: UnExecute(){
  if (doc.GetLengthColumns(row) != 0){
    doc.RemoveCharAt(row, column+1);
  }
}

//RemoveTextAt Command ------------------------------
void RemoveCommand :: Execute(){
  if (strvec.size()==0){
    strvec.push_back(LCTI);
  }

  doc.EraseText(row, column);
}

void RemoveCommand :: UnExecute(){
  doc.AddText(row, strvec[0]);
}

//BackSpace Command ------------------------------
void BackspaceCommand :: Execute(){
  doc.RemoveCharAt(row, column);
}

void BackspaceCommand :: UnExecute(){
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

  if (strvec.size()==0){
    strvec.push_back(LCTI);
  }

  doc.RemoveLineAt(row);
}

void RemoveLineCommand :: UnExecute(){
  doc.NewLine(row, strvec[0]);
}

//Combine Command ------------------------------

void CombineCommand :: Execute(){

  if (strvecc.size() == 0 && strvec.size()==0){
    strvecc.push_back(LCTI);
    strvec.push_back(two_LCTI);
  }

  //First Comand NewLine
  doc.NewLine(row, strvecc[0]);

  //Second Command RemoveTextAt
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

  if (strvec.size() == 0 && strtwovec.size()==0){
    strvec.push_back(LCTI);
    strtwovec.push_back(two_LCTI);
  }

  //First Comand TextInsertAt
  doc.InsertCharAt(row, col, strvec[0]);

  //Second Command RemoveLine
  doc.RemoveLineAt(two_row);

}

void CombineBackspaceCommand :: UnExecute(){
  //UnExecute Second Comand
  doc.NewLine(two_row, strvec[0]);
  
  //UnExecute First Command
  doc.EraseText(row, col);
  
}

//RemoveWords Comand ------------------------------

void WordsCommand :: Execute(){

  if (string_replace.size() == 0 && string_search.size()==0){
    string_search.push_back(search);
    string_replace.push_back(replace);
  }

  doc.RemoveWords(string_search[0], string_replace[0], row_start, row_end);
}
  
void WordsCommand :: UnExecute(){
  string_replace.push_back(replace);
  doc.RemoveWords(string_replace[0], string_search[0], row_start, row_end);
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

void ECTextDocumentCtrl :: RemoveWords(string search, string replace, int row_start, int row_end){
  histCmds.ExecuteCmd(new WordsCommand(doc, search, replace, row_start, row_end));
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
  Search = false;
  Find = true;
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


int ECTextDocument :: GetLengthColumns(int pos){
  return listChars[pos].size();
}

int ECTextDocument :: GetLengthRows(){
  return listChars.size();
}

void ECTextDocument :: addrow(string value){
  listChars.push_back(value);
}

void ECTextDocument :: removerow(){
  listChars.pop_back();
}

void ECTextDocument :: NewLine(int row, string key){
  listChars.insert(listChars.begin()+row, key);
}

void ECTextDocument :: RemoveLineAt(int row){
  listChars.erase(listChars.begin()+row);
}

void ECTextDocument :: EraseText(int row, int column){
  listChars[row].erase(listChars[row].begin() + column, listChars[row].end());
}

void ECTextDocument :: AddText(int row, string text){
  for (auto txt:text){
    listChars[row].push_back(txt);
  }
}

string ECTextDocument :: GetStringAt(int row){
  return listChars[row];
}

string ECTextDocument :: GetSubString(int row, int column){
  return listChars[row].substr(column);
}



std::vector<int> ECTextDocument :: SearchColor(int row, string text){

  size_t found = listChars[row].find(text);
  std::vector<int> results;
  int count = 0;
  int convertdata = 0;

  if (found == string::npos){

    return results;

  }
  else{

    while (found != string::npos){
      convertdata = static_cast<int>(found);
      results.push_back(convertdata);
      count++;
      found = listChars[row].find(text, found + count);
    }

    return results;
  }

  return results;
}

void ECTextDocument :: RemoveWords(string search, string replace, int row_start, int row_end){
  int index = 0;
    
  for (int i = row_start; i < row_end; i++){
    size_t found = listChars[i].find(search);

    if (found == string::npos){
      continue;
    }

    while (found != string::npos){
      listChars[i].replace(found, search.length(), replace);
      index++;
      found = listChars[i].find(search, found + index);
    }
  }
}

