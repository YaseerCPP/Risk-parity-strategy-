#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

// Function to calculate the mean of a vector
double mean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Function to calculate the standard deviation of a vector
double standardDeviation(const std::vector<double>& data) {
    double avg = mean(data);
    double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
    return std::sqrt(sq_sum / data.size() - avg * avg);
}

// Function to normalize the weights so that they sum to 1
std::vector<double> normalizeWeights(const std::vector<double>& weights) {
    double sum = std::accumulate(weights.begin(), weights.end(), 0.0);
    std::vector<double> normalizedWeights;
    for (double weight : weights) {
        normalizedWeights.push_back(weight / sum);
    }
    return normalizedWeights;
}

// Function to calculate risk parity weights
std::vector<double> calculateRiskParityWeights(const std::vector<std::vector<double>>& returns) {
    size_t n = returns.size();
    std::vector<double> volatilities(n);
    std::vector<double> weights(n);

    // Calculate the volatility for each asset
    for (size_t i = 0; i < n; ++i) {
        volatilities[i] = standardDeviation(returns[i]);
    }

    // Calculate the initial weights as inverse of volatilities
    for (size_t i = 0; i < n; ++i) {
        weights[i] = 1.0 / volatilities[i];
    }

    // Normalize the weights to sum to 1
    return normalizeWeights(weights);
}

int main() {
    // Example historical returns data for 3 assets with different time periods
    std::vector<std::vector<double>> returns = {
        {0.01, 0.02, -0.01, 0.03, 0.02},       // Asset 1
        {0.02, 0.01, 0.03, 0.01, 0.04, 0.02},  // Asset 2
        {-0.01, 0.01, 0.02, 0.00, 0.01, -0.02, 0.03} // Asset 3
    };

    // Calculate risk parity weights
    std::vector<double> weights = calculateRiskParityWeights(returns);

    // Output the weights
    std::cout << "Risk Parity Weights:" << std::endl;
    for (size_t i = 0; i < weights.size(); ++i) {
        std::cout << "Asset " << i + 1 << ": " << weights[i] << std::endl;
    }

    return 0;
}
