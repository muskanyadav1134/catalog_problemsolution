#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Function to convert a string of a given base to decimal
int baseToDecimal(string value, int base) {
    int result = 0;
    for (int i = 0; i < value.size(); ++i) {
        result = result * base + (value[i] - '0');
    }
    return result;
}

// Function to perform Gaussian Elimination
vector<double> gaussianElimination(vector<vector<double>>& matrix) {
    int n = matrix.size();

    // Forward elimination
    for (int i = 0; i < n; ++i) {
        // Make the diagonal element 1
        double diagElement = matrix[i][i];
        for (int j = 0; j <= n; ++j) {
            matrix[i][j] /= diagElement;
        }

        // Make the elements below the diagonal 0
        for (int k = i + 1; k < n; ++k) {
            double factor = matrix[k][i];
            for (int j = 0; j <= n; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // Back substitution
    vector<double> result(n);
    for (int i = n - 1; i >= 0; --i) {
        result[i] = matrix[i][n];
        for (int j = i + 1; j < n; ++j) {
            result[i] -= matrix[i][j] * result[j];
        }
    }

    return result;
}

int main() {
    // Input the number of points (n) and degree + 1 (k)
    int n, k;
    cout << "Enter number of points (n): ";
    cin >> n;
    cout << "Enter minimum number of points to solve (k): ";
    cin >> k;
   
    vector<pair<int, int>> points;  // To store the x and y values as pairs

    // Read points from user input
    for (int i = 0; i < n; ++i) {
        int x, base;
        string valueStr;
       
        cout << "Enter x for point " << i + 1 << ": ";
        cin >> x;
        cout << "Enter base for y value (e.g., 10 for decimal, 2 for binary): ";
        cin >> base;
        cout << "Enter y value as a string: ";
        cin >> valueStr;

        // Decode y value from the given base
        int y = baseToDecimal(valueStr, base);

        // Store the (x, y) pair
        points.push_back(make_pair(x, y));
    }

    // We need at least 'k' points to solve for a polynomial of degree 'k-1'
    if (points.size() < k) {
        cerr << "Error: Insufficient number of points provided!" << endl;
        return 1;
    }

    // Create the matrix for Gaussian elimination
    vector<vector<double>> matrix(k, vector<double>(k + 1, 0));

    // Fill the matrix with equations using the points
    for (int i = 0; i < k; ++i) {
        int x = points[i].first;
        int y = points[i].second;

        // Fill each row with the powers of x
        for (int j = 0; j < k; ++j) {
            matrix[i][j] = pow(x, k - 1 - j);
        }
        matrix[i][k] = y;  // The result (y value)
    }

    // Solve the system using Gaussian elimination
    vector<double> coefficients = gaussianElimination(matrix);

    // Output the coefficients of the polynomial
    cout << "The polynomial coefficients are:" << endl;
    for (int i = 0; i < coefficients.size(); ++i) {
        cout << "a_" << (k - 1 - i) << " = " << coefficients[i] << endl;
    }

    // The constant term 'c' is the last coefficient
    cout << "The constant term (c) is: " << coefficients[k - 1] << endl;

    return 0;
}
