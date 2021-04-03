#include "ECCommand.h"
#include <iostream>
using namespace std;


// ******************************************************
// Implement command history

ECCommandHistory :: ECCommandHistory(): present(0)
{
}

ECCommandHistory :: ~ECCommandHistory()
{
  for(auto Cmd: history){
    delete Cmd;
  }
}

void ECCommandHistory :: ExecuteCmd( ECCommand *pCmd ){
  //call execute method
  //cout << "ExecuteCmd: Execute Commands" << endl;
  //cout << "current command: " << present << endl;
  history.push_back(pCmd);
  pCmd->Execute();
  present++;
}

bool ECCommandHistory :: Undo(){
  if (history.size() > 0){
    //cout << "Undo: Unexecute last";
    history[present-1]->UnExecute();
    present--;
    return true;
  }

  return false;

}

bool ECCommandHistory :: Redo(){
  if (present + 1 <= history.size()){
    //cout << "Redo: Unexecute last";
    history[present]->Execute();
    present++;
    return true;
  }

  return false;
}