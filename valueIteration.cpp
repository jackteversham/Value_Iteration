
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "state.cpp"

using namespace std;


double bell_eqn(state & s, vector<state> & states, const double discount, string optimalPath){ //performs a single operation
    double expected_reward = 0.0;

    for(int i = 0; i< s.transitions.size(); i++){
        if(s.transitions[i]==0){
            continue;
        }else{
            int reward =0;
            if(s.transitions[i]==1){ //the '1' was just an indicator that a transition to this state was possible
                reward = 0;
            }else{
                reward = s.transitions[i];
            }
            if(s.id == 1){
                optimalPath += ("S"+to_string(i));
            }
            double newVal = reward + discount * states[i].prevValue;
            expected_reward = max(expected_reward, newVal);
        }
    }
    s.newValue = expected_reward; //update for the next iteration
   return expected_reward; 
}

void update(vector<state> & states){ //oldValue becomes the current new value
    for (auto &&s : states)
    {
        s.prevValue = s.newValue;
    }
}




int main(void){
vector<state> states;
string path;
//initialise states
state s1(1,{0,1,0,1,0,0});
state s2(2,{1,0,50,0,1,0});
state s3(3,{0,0,1,0,0,0});
state s4(4,{1,0,0,0,1,0});
state s5(5,{0,1,0,1,0,1});
state s6(6,{0,0,100,0,1,0});

states.push_back(s1);
states.push_back(s2);
states.push_back(s3);
states.push_back(s4);
states.push_back(s5);
states.push_back(s6);

bool converged = false;
int iterations = 0;

while(1){ //repeat until convergence
//check for convergence

if(!converged){

    for (auto &&s : states)  //for each state
{
    bell_eqn(s, states, 0.8, path); //compute bell eqn for each state, need to update after this
    
}//end for

} //end if


int countConverged = 0;
for (auto &&s : states){
    if(s.converged()){
        countConverged++; //if a state hasconverged, increment count
    }   
}

if(countConverged==states.size()){ //break if all states have converged
converged = true;
break;
}
update(states);
iterations ++;

} //end while

ofstream os("out.txt");

os <<"1.) Number of iterations to converge: "<< iterations<<endl<<endl;;
for (auto &&s : states){
    os <<"State: S"<<s.id<<",   V* = " <<s.prevValue <<endl;
}

os << "2.) " << path<<endl;


    return 0;
}