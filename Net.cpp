//
// Created by Mike MA on 26/4/16.
//

#ifndef NET_H
#define NET_H

#include <iostream>
#include <vector>
#include <cassert>
#include "neuron.h"
#include "Net.h"
#include <cmath>

using namespace std;

    // constructor.
    Net::Net(const vector<unsigned> &topology, const double eta) {
        initialize();
    }

    // given an input sample inputVals, propagate input forward, compute the output of each neuron
    void Net::feedForward(const vector<double> &inputVals) {
        vector<double> temp(4);
        //Hidden layer
        for(int i=0;i<4;i++)
            temp[i]=hidden[i]->calculate(inputVals);
        //Output layer
        result=final->calculate(temp);

    }

    // given the vector targetVals (ground truth of output), propagate errors backward, and update each weights
    void Net::backProp(const vector<double> &targetVals){
        //Calculate the error
        target=targetVals[0];
        error=abs(target-final->getResult());
        error=error*error;
        //Propagate error
        final->errorCalculate(targetVals[0],1);
       // cout<<"Output error "<<final->getError()<<endl;
        for(int i=0;i<4;i++) {
            double tt=hidden[i]->errorCalculate(final->getFeature(i) * final->getError(), 2);
            hidden[i]->setError(tt);

        }
        //Update
        final->update();
        for(int i=0;i<4;i++)
            hidden[i]->update();
    }

    // output the prediction for the current sample to the vector resultVals
    void Net::getResults(vector<double> &resultVals) const {
        vector<double> *temp=&resultVals;
        temp->clear();
        temp->push_back(final->getResult());
    }

    // return the error of the current sample
    double Net::getError(void) const {
        return error;
    }



    //Initialize the net with 2 input, 4 hidden and 1 output
    //Structure is hardcode here.
    void Net::initialize() {
        for(int i=0;i<4;i++)
            hidden[i]=new neuron(2);
        final=new neuron(4);
    }



#endif//NET_H
