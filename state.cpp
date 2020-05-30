#include <vector>
#include <string>
#include "state.h"

using namespace std;
//class state {
//public:
    int id; //state name
    vector<double> transitions; //states to which it can move, all are deterministics with value of 1.0
    double prevValue; //previous value of maximum expected rewards
    double newValue; //new value


  //  state(int id, vector<double> transitions):id(id), transitions(transitions){prevValue=0.0; newValue=0.0;}

    bool state::converged(){
        if(prevValue == newValue) return true;
        else return false;
    }

    string state::bestPolicy(vector<state> &states){
        string policy = "State"+to_string(this->id);
        int currentState = this->id;
        state s = *this;

        while(currentState != 3){
            double maxReward = 0.0;
            int nextState = 0;
        for(int i = 0; i < states.size(); i++){
            if(s.transitions[i]>0 && (s.transitions[i]+states[i].newValue)>maxReward){ //i.e. we can move to that state and it has a beneficial reward
                //currentState = states[i].id;
                nextState = i;
                maxReward = s.transitions[i]+states[i].newValue;
            }
        }
        s = states[nextState];
        currentState = s.id;
        
        policy += " --> State"+ to_string(currentState);

        }

        return policy;
    }



