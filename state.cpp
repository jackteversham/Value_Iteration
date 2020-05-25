#include <vector>
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



