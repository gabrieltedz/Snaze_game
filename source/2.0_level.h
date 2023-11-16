#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <fstream>
#include <vector>

class Level{
private:
    int lines;
    int columns;
    char** matrix;
public:
    Level(int n_lines, int n_columns, char** matrix_data) : lines(n_lines), columns(n_columns) {
        // Allocate memory for the matrix
        matrix = new char*[lines];
        for (int i = 0; i < lines; ++i) {
            matrix[i] = new char[columns];
        }

        // Copy the matrix data
        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = matrix_data[i][j];
            }
        }

        // Additional constructor code, if needed
    }

    ~Level() {
        // Deallocate memory for the matrix in the destructor
        for (int i = 0; i < lines; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void read_level_map();
};

#endif