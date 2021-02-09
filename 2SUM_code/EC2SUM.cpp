#include <vector>
#include <iostream>
using namespace std;

void EC2SUM( const vector<int> &listNumbers,
const vector<int> &listTargets, vector<bool> &list2SUMRes )
{
  // for each number x = listTargets[i], if there are two numbers 
  // in listNumbers that add up to x, then list2SUMres[i]=true 
  // otherwise, list2SUMRes[i]=false

  

  //for each number in listTargets
  for (int i=0; i < listTargets.size();i++){
    bool found = false;

    //cout<<"the listTarget is: "<< listTargets[i] << endl;

    //for each number in listNumbers
    for (int augend=0; augend < listNumbers.size(); augend++){
  
      //cout<< "first operator: "<< listNumbers[augend]<<endl;

      //see if second number in listNumbers adds up to listTrgets[i] f
      for (int addend=0; addend < listNumbers.size(); addend++){
        //cout<< "second operator: "<< listNumbers[addend]<<endl;
        //cout<< "result:"<< listNumbers[augend] + listNumbers[addend] << endl;

        if(augend == addend){
          continue;
        }
        //if two numbers (augend + addend) add to listTargets[i] 
        else if (listNumbers[augend] + listNumbers[addend] == listTargets[i]){
          //set list2SUMres[i] to true
          list2SUMRes.push_back(true);
          found = true;
          break;
        }

      }

      if (found == true){
        break;
      }
    }

    //for this iteration if there was no pair found set list2SUMres[i] to false
    if (found == false){
      list2SUMRes.push_back(false);
    }
  }

}


/* alternative with mergesort and binary search


void EC2SUM( const vector<int> &listNumbers,
const vector<int> &listTargets, vector<bool> &list2SUMRes )
{
  // for each number x = listTargets[i], if there are two numbers 
  // in listNumbers that add up to x, then list2SUMres[i]=true 
  // otherwise, list2SUMRes[i]=false

  

  //for each number in listTargets
  for (int i=0; i < listTargets.size();i++){
    bool found = false;

    //cout<<"the listTarget is: "<< listTargets[i] << endl;

    //for each number in listNumbers
    for (int augend=0; augend < listNumbers.size(); augend++){
  
      //cout<< "first operator: "<< listNumbers[augend]<<endl;

      //see if second number in listNumbers adds up to listTrgets[i] f
      for (int addend=0; addend < listNumbers.size(); addend++){
        //cout<< "second operator: "<< listNumbers[addend]<<endl;
        //cout<< "result:"<< listNumbers[augend] + listNumbers[addend] << endl;

        if(augend == addend){
          continue;
        }
        //if two numbers (augend + addend) add to listTargets[i] 
        else if (listNumbers[augend] + listNumbers[addend] == listTargets[i]){
          //set list2SUMres[i] to true
          list2SUMRes.push_back(true);
          found = true;
          break;
        }

      }

      if (found == true){
        break;
      }
    }

    //for this iteration if there was no pair found set list2SUMres[i] to false
    if (found == false){
      list2SUMRes.push_back(false);
    }
  }

}


int main(){

vector <int> listNumbers;
vector <int> listTargets;
vector <bool> list2SUM;

listNumbers.push_back(6);
listNumbers.push_back(3);
listNumbers.push_back(4);
listNumbers.push_back(1);
listNumbers.push_back(2);
listNumbers.push_back(0);

listTargets.push_back(5);
listTargets.push_back(100);
listTargets.push_back(13);

EC2SUM(listNumbers, listTargets, list2SUM);

cout<<"print"<<endl;

for (int i = 0; i<list2SUM.size(); i++){
  cout<<list2SUM[i]<<endl;
}

}
*/







