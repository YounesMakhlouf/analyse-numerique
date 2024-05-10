#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<vector<double>> calculateDividedDifferences(const vector<double> &x, const vector<double> &f, int n) {
    vector<vector<double>> dividedDifferences(n + 1, vector<double>(n + 1));
    for (int i = 0; i <= n; i++) {
        dividedDifferences[i][0] = f[i];
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i <= n - k; i++) {
            dividedDifferences[i][k] =
                    (dividedDifferences[i + 1][k - 1] - dividedDifferences[i][k - 1]) / (x[i + k] - x[i]);
        }
    }
    return dividedDifferences;
}

double newtonInterpolation(const vector<double> &a, const vector<double> &x, double val, int n) {
    double result = a[n];
    for (int k = 1; k <= n; k++) {
        result = a[n - k] + (val - x[n - k]) * result;
    }
    return result;
}

// Helper function to read vector values from input.
void readVectorValues(vector<double> &vec, const string &prompt) {
    cout << prompt << endl;
    for (double &val: vec) {
        cin >> val;
    }
}

vector<vector<double>> calculateFiniteDifferences(const vector<double> &f, int n) {
    vector<vector<double>> finiteDifferences(n + 1, vector<double>(n + 1));
    for (int i = 0; i <= n; i++) {
        finiteDifferences[i][0] = f[i];
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i <= n - k; i++) {
            finiteDifferences[i][k] = (finiteDifferences[i + 1][k - 1] - finiteDifferences[i][k - 1]);
        }
    }
    return finiteDifferences;
}

int main() {
    int degree;
    cout << "Enter the degree (n) of the polynomial: ";
    while (!(cin >> degree) || degree < 0) {
        cout << "Invalid input. Please enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<double> values(degree + 1), points(degree + 1);

    readVectorValues(points, "Enter the x values (separated by space or newline):");
    readVectorValues(values, "Enter the f(x) values corresponding to each x (separated by space or newline):");

    auto dividedDifferences = calculateDividedDifferences(points, values, degree);

    cout << "Divided Differences Table:" << endl;
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree - i; j++) {
            cout << dividedDifferences[i][j] << " ";
        }
        cout << endl;
    }

    double estimationPoint;
    cout << "Enter the x value where you want to estimate f(x): ";
    cin >> estimationPoint;

    double estimatedValue = newtonInterpolation(dividedDifferences[0], points, estimationPoint, degree);
    cout << "Estimated f(x) at x = " << estimationPoint << " is: " << estimatedValue << endl;
    return 0;
}