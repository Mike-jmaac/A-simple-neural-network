//
// Created by Mike MA on 26/4/16.
//

#ifndef ASSIGNMENT2_NEURON_H
#define ASSIGNMENT2_NEURON_H

#include <math.h>
#include <vector>

#define ETA 0.5

using namespace std;

class neuron {
public:
    neuron(int input) {
        NumOfFeatures = input;
        initialize();

    }
    //Calculate the output of current neuron
    double calculate(vector<double> input) {
        double result = 0.0;
        for (int i = 0; i < NumOfFeatures; i++) {
            result += input[i] * (*features)[i];
            (*lastInput)[i] = input[i];
        }
        result = Sigmoid(result);
        lastResult = result;
        return result;
    }

    //Propagate error for each unit
    //Type: 1 for output unit, 2 for hidden unit
     double errorCalculate(double target, int type) {
        if (type == 1) {
            //for output Unit
            error = lastResult * (1 - lastResult) * (target - lastResult);
        }
        else if (type == 2) {
             //for hidden Unit
            error = lastResult * (1 - lastResult) * target;
        }
        else {
            cout << "Error is set to 0!" << endl;
        }
        return error;

    }
    //getters and setters
    double getFeature(int i) {
        return (*features)[i];
    }

    double getResult() {
        return lastResult;
    }
    void setError(double input)
    {
        error=input;
    }
    double getError() {
        return error;
    }
    //Update each feature
    bool update() {
        for (int i = 0; i < NumOfFeatures; i++)
            (*features)[i] = (*features)[i] + ETA * error * ((*lastInput)[i]);
        return true;
    }

private:

    vector<double> *features= nullptr;
    int NumOfFeatures;
    double lastResult;
    double error;
    vector<double> *lastInput= nullptr;

    //Activation function
    double Sigmoid(double netInput) {
        return (1 / (1 + exp(-netInput)));
    }

    //Initialize the neuron with given numOfFeatures
    //Features are initialize randomly.
    void initialize() {
        features = new vector<double>(NumOfFeatures);
        lastInput = new vector<double>(NumOfFeatures);
        for (int i = 0; i < NumOfFeatures; i++) {
            (*features)[i] = (2.0 * (double) rand() / RAND_MAX) - 1;
            (*lastInput)[i] = 0;
        }
        lastResult = 0.0;
        error = 0.0;
    }


};

#endif //ASSIGNMENT2_NEURON_H
