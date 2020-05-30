
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "state.cpp"

using namespace std;


double bell_eqn(state & s, vector<state> & states, const double discount){ //performs a single operation
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

void runValueIteration(vector<state> &states, bool converged, int & iterations, double discountF){
        while(1){ //repeat until convergence
//check for convergence

    if(!converged){
     for (auto &&s : states)  //for each state
    {
         bell_eqn(s, states, discountF); //compute bell eqn for each state, need to update after this
    }//end for

}    //end if

    int countConverged = 0;
    for(auto &&s : states){
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
    
}


int main(void){
vector<state> states;
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
double discountF = 0.8;

runValueIteration(states, converged, iterations, discountF);


ofstream os("out.txt");

os <<"1.) Number of iterations to converge: "<< iterations<<endl<<endl;;
for (auto &&s : states){
    os <<"State: S"<<s.id<<",   V* = " <<s.prevValue <<endl;
}

os << "\n2.) " << s1.bestPolicy(states) <<endl;

os << "\n3.) Yes.\nBy changing the discount factor, the agent cares less/more about future rewards, and thus V* (optimal value) will change however, the optimal policy may not necessarily change.\n"
<<"If discount factor = 0.5 instead of 0.8 for example, the optimal policy from state 1 is the same as for question 2. The optimal values of each state changes (shown below:)"<<endl;


converged = false;
discountF = 0.5;
iterations = 0;

runValueIteration(states, converged, iterations, discountF); //run again with different discount factor


os << "\n" << s1.bestPolicy(states) <<"   The optimal policy has remained the same." ;


os <<"\n\nNumber of iterations to converge: "<< iterations<<endl<<endl;;
for (auto &&s : states){
    os <<"State: S"<<s.id<<",   V* = " <<s.prevValue <<endl;
}
converged = false;
discountF = 0.8;
iterations = 0;
states[3].transitions = {20,0,0,0,10,0}; //change the reward for transitions to other states from state 4
runValueIteration(states, converged, iterations, discountF); //run again with different discount factor

os<< "\nIf we change the reward values for the given transitions of a state (state 4 in this case), and leave the discount factor the same, we get:"<<endl;

os << "\n" << s1.bestPolicy(states) <<"   The optimal policy has remained the same." ;

os <<"\n\nNumber of iterations to converge: "<< iterations<<endl<<endl;;
for (auto &&s : states){
    os <<"State: S"<<s.id<<",   V* = " <<s.prevValue <<endl;
}

os.close();

    return 0;
}