#include "matrix.hpp"
#include <iostream>
#include <new>

Row::Row(size_t cols)
{
    n_cols = cols;
    elems = new int[cols];
}

Row::~Row()
{
    delete[] elems;
}
Row &Row::operator=(const Row &other)
{
    n_cols = other.getColumns();
    elems = new int[n_cols];

    for (size_t i = 0; i < n_cols; i++)
    {

        elems[i] = other[i];
    }
}

bool Row::operator==(const Row &other) const
{
    for (size_t i = 0; i < n_cols; i++)
        if (elems[i] != other[i])
            return false;

    return true;
}
void Row::operator*=(int mult)
{
    for (size_t i = 0; i < n_cols; i++)
        elems[i] *= mult;
}
int &Row::operator[](const size_t i_col)
{

    if (i_col >= n_cols)
        throw std::out_of_range("");

    return elems[i_col];
}
const int &Row::operator[](const size_t i_col) const
{

    if (i_col >= n_cols)
        throw std::out_of_range("");

    return elems[i_col];
}

size_t Row::getColumns() const
{
    return n_cols;
}

Row::Row()
{
}

Matrix::Matrix(const size_t rows, const size_t cols)
{

    n_cols = cols;
    n_rows = rows;
    Rows = (Row*)new char [sizeof(Row)*rows];
    
    for (size_t i = 0 ; i < cols ; ++i)
        new (Rows + i ) Row(cols);
    


}

Matrix::~Matrix()
{
    for (size_t i = 0; i < n_cols; ++i)
        (Rows + i) ->~Row();
    delete [] (char*)Rows;
}

size_t Matrix::getColumns() const
{
    return n_cols;
}
size_t Matrix::getRows() const
{
    return n_rows;
}
Matrix &Matrix::operator*=(int mult)
{
    for (size_t i = 0; i < n_rows; i++)
        Rows[i] *= mult;
    return *this;
}
Row &Matrix::operator[](const size_t i_row)
{
    if (i_row >= n_rows)
        throw std::out_of_range("");
    return Rows[i_row];
}
const Row &Matrix::operator[](const size_t i_row) const
{
    if (i_row >= n_rows)
        throw std::out_of_range("");
    return Rows[i_row];
}
bool Matrix::operator==(const Matrix &other) const
{
    if (this == &other)
        return true;

    if (n_cols != other.getColumns() || n_rows != other.getRows())
        return false;
    for (size_t i = 0; i < n_rows; i++)
        if (!(Rows[i] == other[i]))
            return false;

    return true;
}
bool Matrix::operator!=(const Matrix &other) const
{

    return !(*(this) == (other));
}