#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Regression.hpp"
using namespace std;

#define num_of_feature 6
#define total num_of_feature + 1
#define num_of_sample 209     

//tron du lieu
void Shuffle(int* index, int n) {
    for (int i = n - 1; i > 0; --i) {    
        int j = rand() % (i + 1);
        swap(index[i], index[j]);
    }
}


int main() {
    double features[num_of_sample][num_of_feature];  // Raw input features
    double targets[num_of_sample];            // Target values

    ifstream file("machine.data");
    if (!file) {
        cerr << "Error: Cannot open machine.data\n";
        return 1;
    }

    string line;
    int row = 0;
    while (getline(file, line) && row < num_of_sample) {
        stringstream ss(line);
        string token;
        // Bỏ qua 2 cột đầu
        getline(ss, token, ',');
        getline(ss, token, ',');

        //Features
        for (int i = 0; i < num_of_feature; ++i) {
            getline(ss, token, ',');
            features[row][i] = stod(token);
        }

        //PRP
        getline(ss, token, ',');
        targets[row] = stod(token);
        ++row;
    }
    file.close();

    //Shuffle
    int index[num_of_sample];
    for (int i = 0; i < num_of_sample; ++i){
        index[i] = i;
    } 
    srand(0);
    Shuffle(index, num_of_sample);

    // Chia 80/20 (train/test)
    int train_size = num_of_sample * 80 / 100;
    int test_size = num_of_sample - train_size;

    // Arrays to store mean and standard deviation for each feature
    double mean[num_of_feature] = {};
    double std[num_of_feature] = {};

    //Compute mean 
    for (int j = 0; j < num_of_feature; j++) {
        double sum = 0.0;
        for (int i = 0; i < train_size; i++) {
            int idx = index[i];
            sum += features[idx][j];
        }
        mean[j] = sum / train_size;
    }
   
    // Calculate standard deviations
    for (int j = 0; j < num_of_feature; j++) {
        double sum_sq = 0.0;
        for (int i = 0; i < train_size; i++) {
            int idx = index[i];
            double diff = features[idx][j] - mean[j];
            sum_sq += diff * diff;
        }
        std[j] = sqrt(sum_sq/train_size);
       
        if (std[j] < 1e-7) {
            std[j] = 1.0;
        }
    }

    Matrix A_train(train_size, total);
    Vector b_train(train_size);
    Matrix A_test(test_size, total);
    Vector b_test(test_size);

    // Step 2: Prepare training data with feature scaling and bias term
   
    for (int i = 0; i < train_size; i++) {
        int idx = index[i];
        // Add bias term (constant 1 in first column)
        A_train(i+1,1)= 1.0; // bias
       
        // Add scaled features
        for (int j = 0; j < num_of_feature; j++) {
            double scaled_value = (features[idx][j] - mean[j]) / std[j];
            A_train(i+1,j+2)= scaled_value;  
        }
        b_train(i+1)= targets[idx];
    }

    //Prepare data 
    for (int i = 0; i < test_size; i++) {
        int idx = index[train_size+i];        
        A_test(i+1,1)= 1.0; //bias
       
        // Add scaled features using training set's mean and std
        for (int j = 0; j < num_of_feature; j++) {
            double scaled_value = (features[idx][j] - mean[j]) / std[j];
            A_test(i+1,j+2)= scaled_value;  
        }
        b_test(i+1)=targets[idx];
    }

    LinearRegression model;
    model.train(A_train, b_train);
    Vector predictions = model.predict(A_test);
    double err = model.RMSE(predictions, b_test);

    cout << "Root Mean Squared Error: " << err << "\n";
    model.GetxVector();


    return 0;
}