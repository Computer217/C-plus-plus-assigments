#include "ECCommand.h"
#include <iostream>
using namespace std;


// ******************************************************
// Implement command history

ECCommandHistory :: ECCommandHistory(): present(-1){}

ECCommandHistory :: ~ECCommandHistory()
{
  for(auto Cmd: history){
    delete Cmd;
  }

  history.clear();
  present = -1;
}

void ECCommandHistory :: ExecuteCmd( ECCommand *pCmd ){

  pCmd->Execute();
  
  if(present >= -1){
      int temp = history.size();
      for(int i=present+1; i < temp; i++){
        delete history.back();
        history.pop_back();
      }
  }

  history.push_back(pCmd);
  present++;

}

bool ECCommandHistory :: Undo(){

  if (present < 0){
    return false;
  }

  history[present]->UnExecute();
  present--;
  return true;

}

bool ECCommandHistory :: Redo(){

  if (present >= (int)history.size()-1){
    return false;
  }

  present++;
  history[present]->Execute();
  return true;
}

