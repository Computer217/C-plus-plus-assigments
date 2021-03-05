//
//  ECTextDocument.cpp
//  
//
//  Created by Yufeng Wu on 2/26/20.
//
//

#include "ECTextDocument.h"
#include <iostream>
#include <cctype>

using namespace std;

// **********************************************************
// Commands

// your code goes here 


// InsertCommand
void InsertCommand :: Execute(){
  int curr = pos;

  for (char c : LCTI){
    doc.InsertCharAt(curr, c);
    curr++;
  }
}

void InsertCommand :: UnExecute(){
  for (int i = 0; i < LCTI.size();i++){
    doc.RemoveCharAt(pos);
  }
}

// ---------------------------------------------------------
//removeTextAt
void RemoveTextCommand :: Execute(){

  state.clear();
  for (int i=0; i < lenToRemove; i++){
    state.push_back(doc.GetCharAt(pos));
    doc.RemoveCharAt(pos);
  }
}

void RemoveTextCommand :: UnExecute(){
  if (state.size() == 0){
    cout << "RemoveTextAt: no action to Unexecute" << endl;
  }

  int curr = pos; 

  for (int i=0; i<lenToRemove; i++){
    doc.InsertCharAt(curr, state[i]);
    curr ++;
  }

}

// ---------------------------------------------------------
//CapTextAt

void CapTextCommand :: Execute(){
  //cout << "EXECUTE CapTextAt" << endl;

  int curr = pos;
  for (int i=0; i<lenToCap;i++){
    doc.CapCharAt(curr);
    curr++;
  }
}


//might need to maintain state.
void CapTextCommand :: UnExecute(){
  int curr = pos;
  for (int i=0; i<lenToCap;i++){
    doc.LowerCharAt(curr);
    curr++;
  }
}

// ---------------------------------------------------------
//CapLowerText

void LowerTextCommand :: Execute(){
  int curr = pos;
  for (int i=0; i<lenToLower;i++){
    doc.LowerCharAt(curr);
    curr++;
  }
}

void LowerTextCommand :: UnExecute(){
  int curr = pos;
  for (int i=0; i<lenToLower;i++){
    doc.CapCharAt(curr);
    curr++;
  }
}


// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : doc(docIn)
{
}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl()
{
}

void ECTextDocumentCtrl :: InsertTextAt(int pos, const std::vector<char> &listCharsToIns)
{
  // your code
  //cout << "document controller" << endl;
  histCmds.ExecuteCmd(new InsertCommand(doc,pos,listCharsToIns));

}

void ECTextDocumentCtrl :: RemoveTextAt(int pos, int lenToRemove)
{
  // your code
  histCmds.ExecuteCmd(new class RemoveTextCommand(doc,pos,lenToRemove));

}

void ECTextDocumentCtrl :: CapTextAt(int pos, int lenToCap)
{
  // your code
  //cout << "CapTextAt: enter Ctrl function call" << endl;
  histCmds.ExecuteCmd(new class CapTextCommand(doc,pos,lenToCap));
}

void ECTextDocumentCtrl :: LowerTextAt(int pos, int lenToLower)
{
  // your code
  histCmds.ExecuteCmd(new class LowerTextCommand(doc,pos,lenToLower));
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

char ECTextDocument :: GetCharAt(int pos) const
{
    return listChars[pos];
}

void ECTextDocument :: InsertCharAt(int pos, char ch)
{
  // your code here

  listChars.insert(listChars.begin()+pos, ch);

}

void ECTextDocument :: RemoveCharAt(int pos)
{
  // your code here

  listChars.erase(listChars.begin()+pos);

}

void ECTextDocument :: CapCharAt(int pos)
{
  // your code here
  listChars[pos] = toupper(listChars[pos]);

}

void ECTextDocument :: LowerCharAt(int pos)
{
  // your code here
  listChars[pos] = tolower(listChars[pos]);
}

