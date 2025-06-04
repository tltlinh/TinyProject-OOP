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

#define FEATURES 6
#define TOTAL_FEATURES FEATURES + 1
#define SAMPLES 209      // Total data samples

//tron du lieu
void shuffle(int* indices, int n) {
    for (int i = n - 1; i > 0; --i) {    
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }
}


int main() {
    double features[SAMPLES][FEATURES];  // Raw input features
    double targets[SAMPLES];            // Target values

    ifstream file("machine.data");
    if (!file) {
        cerr << "Error: Cannot open machine.data\n";
        return 1;
    }

    string line;
    int row = 0;
    while (getline(file, line) && row < SAMPLES) {
        stringstream ss(line);
        string token;
        // Bỏ qua 2 cột đầu
        getline(ss, token, ',');
        getline(ss, token, ',');

        //Features
        for (int i = 0; i < FEATURES; ++i) {
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
    int indices[SAMPLES];
    for (int i = 0; i < SAMPLES; ++i) indices[i] = i;
    srand(0);
    shuffle(indices, SAMPLES);

    // Chia 80/20 (train/test)
    int train_size = SAMPLES * 80 / 100;
    int test_size = SAMPLES - train_size;

    // Arrays to store mean and standard deviation for each feature
    double feature_means[FEATURES] = {0};
    double feature_stds[FEATURES] = {0};

    // Step 1: Compute mean and standard deviation for each feature (using training set only)
   
    for (int j = 0; j < FEATURES; ++j) {
        double sum = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            sum += features[idx][j];
        }
        feature_means[j] = sum / train_size;
    }
   
    // Calculate standard deviations
    for (int j = 0; j < FEATURES; ++j) {
        double sum_sq = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            double diff = features[idx][j] - feature_means[j];
            sum_sq += diff * diff;
        }
        feature_stds[j] = sqrt(sum_sq / train_size);
       
        // Handle constant features (avoid division by zero)
        if (feature_stds[j] < 1e-7) {
            feature_stds[j] = 1.0;
        }
    }


    // Initialize matrices with bias term
    Matrix A_train(train_size, TOTAL_FEATURES);
    Vector b_train(train_size);
    Matrix A_test(test_size, TOTAL_FEATURES);
    Vector b_test(test_size);

    // Step 2: Prepare training data with feature scaling and bias term
   
    for (int i = 0; i < train_size; ++i) {
        int idx = indices[i];
        // Add bias term (constant 1 in first column)
        A_train(i+1, 1)= 1.0; // bias
       
        // Add scaled features
        for (int j = 0; j < FEATURES; ++j) {
            // Standardize feature: (value - mean) / std_dev
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            A_train(i+1, j + 2)= scaled_value;  // j+1 to account for bias column
        }
        b_train(i+1)= targets[idx];
    }

    // Step 3: Prepare test data using same scaling parameters as training set
   
    for (int i = 0; i < test_size; ++i) {
        int idx = indices[train_size + i];        
        A_test(i+1, 1)= 1.0; //bias
       
        // Add scaled features using training set's mean and std
        for (int j = 0; j < FEATURES; ++j) {
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            A_test(i+1, j + 2)= scaled_value;  // j+1 to account for bias column
        }
        b_test(i+1) =targets[idx];
    }

    // Train and evaluate model
    LinearRegression model;
    model.train(A_train, b_train);
    Vector predictions = model.predict(A_test);
    double error = model.rmse(predictions, b_test);

    cout << "Root Mean Squared Error: " << error << "\n\n";
    model.printWeights();


    return 0;
}