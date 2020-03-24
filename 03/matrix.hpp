#pragma once

typedef unsigned int size_t;

class Row
{

public:
    Row(size_t cols);
    bool operator==(Row &other) const;
    void operator*=(int mult);
    int &operator[](const size_t i_col);
    Row &operator=(Row &other);
    size_t getColumns() const;
    ~Row();

private:
    Row();
    int *elems = nullptr;
    size_t n_cols = 0;

    friend class Matrix;
};

class Matrix
{

public:
    Matrix(const size_t rows, const size_t cols);
    size_t getColumns() const;
    size_t getRows() const;
    void operator*=(int mult);
    Row &operator[](const size_t i_row);
    Row &operator[](const size_t i_row) const;
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    ~Matrix();

private:
    Row *Rows = nullptr;
    size_t n_cols = 0;
    size_t n_rows = 0;
};