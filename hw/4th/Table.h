#ifndef INC_4TH_TABLE_H
#define INC_4TH_TABLE_H
#include <iomanip>

template <class T> class Table {
public:
    typedef unsigned int size_type;

    // Constructors
    Table(){ this->create(); }
    Table(size_type row, size_type col) { this->create(row, col); }
    Table(size_type row, size_type col, const T &t = T()) { this->create(row, col, t); }
    Table(const Table& table) { this->copy(table); }

    // Operators
    T* operator[](size_type i) { return t_data[i]; }
    const T* operator[](size_type i) const { return t_data[i]; }
    Table& operator=(const Table& table);
    size_type getLongestElementLength() const;

    // Deconstructors
    ~Table() { this->destroy(); };
    void destroy();

    // Accessors
    size_type numRows() const { return row; }
    size_type numColumns() const { return col; }

    const T& get(size_type row, size_type col) const;
    bool isLegalIndex(size_type row, size_type col) const;

    // Mutators
    void set(size_type row, size_type col, const T &t);

    void push_back_column(const std::vector<T> &v);
    void push_back_row(const std::vector<T> &v);

    void pop_back_row();
    void pop_back_column();

    // Extra Credits
    void push_back_columns(const Table<T> &t);
    void push_back_rows(const Table<T> &t);

    void print();
    
private:
    void create();
    void create(size_type row, size_type col);
    void create(size_type row, size_type col, const T &t);
    
    void copy(const Table<T> &t);

    size_type row;
    size_type col;
    T** t_data;
};

// Private Member Methods
/**
 * Create new Table with with no Args: Init 0 row and 0 col
 */
template <class T> void Table<T>::create()
{
    t_data = new T*[0];
    row = col = 0;
}

/**
 * Create new Table with Row and Col; allocate memory in heap as needed.
 * @tparam T
 * @param row
 * @param col
 */
template <class T> void Table<T>::create(size_type row, size_type col)
{
    this->row = row;
    this->col = col;

    t_data = new T*[row];

    for (size_type i = 0; i < row; i++)
    {
        t_data[i] = new T[col];
    }
}

/**
 * Create Table and Assign Given Value to every element in the table
 * @tparam T
 * @param row
 * @param col
 * @param t Given Value
 */
template <class T> void Table<T>::create(size_type row, size_type col, const T &t)
{
    create(row, col);
    
    for (size_type i = 0; i < row; i++)
    {
        for (size_type j = 0; j < col; j++)
        {
            t_data[i][j] = t;
        }
    }
}

/**
 * When assign table, do self clean-up and copy given table.
 * @tparam T
 * @param t
 * @return
 */
template <class T> Table<T>& Table<T>::operator=(const Table<T>& t)
{
    if (this != &t)
    {
        this->destroy();
        this->copy(t);
    }

    return *this;
}

/**
 * Get the longest element's length (Human-readable print)
 * @tparam T
 * @return 0
 */
template <class T> typename Table<T>::size_type Table<T>::getLongestElementLength() const
{
    return 0; // By default, we can't determine the length.
}

/**
 * Get the longest element's length when Table contains integer
 * @return
 */
template <> typename Table<int>::size_type Table<int>::getLongestElementLength() const
{
    unsigned int result = 1;
    for (unsigned int i = 0; i < numRows(); i++)
    {
        for (unsigned int j = 0; j < numColumns(); j++)
        {
            unsigned int l = (unsigned int)std::to_string(get(i, j)).length();
            if (l > result)
            {
                result = l;
            }
        }
    }

    return result;
}

/**
 * Get longest element's length when Table contains std::string
 * @return
 */
template <> typename Table<std::string>::size_type Table<std::string>::getLongestElementLength() const
{
    unsigned int result = 0;
    for (unsigned int i = 0; i < numRows(); i++)
    {
        for (unsigned int j = 0; j < numColumns(); j++)
        {
            unsigned int l = (unsigned int)get(i, j).length();
            if (l > result)
            {
                result = l;
            }
        }
    }

    return result;
}

/**
 * Get longest Length of element when Table contains char
 * @return
 */
template <> typename Table<char>::size_type Table<char>::getLongestElementLength() const
{
    return 1; // By default, char should only have length 1
}

/**
 * Create Space and Copy into current Space
 * @tparam T
 * @param t Given Table
 */
template <class T> void Table<T>::copy(const Table<T> &t)
{
    create(t.row, t.col);

    for (size_type i = 0; i < row; i++)
    {
        for (size_type j = 0; j < col; j++)
        {
            t_data[i][j] = t[i][j];
        }
    }
}

// Public members
/**
 * Identify given row and col is legal to current table.
 * No need to worried about negative integer as we uses unsigned int
 * @tparam T
 * @param row
 * @param col
 * @return true if current Index is within range, false otherwise.
 */
template <class T> bool Table<T>::isLegalIndex(size_type row, size_type col) const
{
    return row <= this->row && col <= this->col;
}

/**
 * Deallocate current Table
 * @tparam T
 */
template <class T> void Table<T>::destroy()
{
    for (size_type i = 0; i < row; i++)
    {
        delete [] t_data[i];
    }

    delete [] t_data;
}

/**
 * Get elements by index
 * @tparam T
 * @param row
 * @param col
 * @return T Requested Value
 */
template <class T> const T& Table<T>::get(size_type row, size_type col) const
{
    if (isLegalIndex(row, col))
    {
        return t_data[row][col];
    }
    
    std::cerr << "Index out of bound!" << std::endl;
    exit(1);
}

/**
 * Set given location to given value
 * @tparam T
 * @param row
 * @param col
 * @param t
 */
template <class T> void Table<T>::set(size_type row, size_type col, const T &t)
{
    if (isLegalIndex(row, col))
    {
        t_data[row][col] = t;
    } else {
        std::cerr << "Index out of bound!" << std::endl;
        exit(1);
    }
}

/**
 * Push given vector's elements to the back of each row
 * @tparam T
 * @param v
 */
template <class T> void Table<T>::push_back_column(const std::vector<T> &v)
{
    if ((size_type)v.size() == row)
    {
        size_type newColNum = col + 1;

        // Loop over each row and copy value
        for (size_type i = 0; i < row; i++)
        {
            // Construct new Row Array
            T* currentRow = new T[newColNum];
            for (size_type j = 0; j < col; j++)
            {
                currentRow[j] = t_data[i][j];
            }

            currentRow[col] = v[i];

            // Delete old Row
            delete [] t_data[i];

            // Add new Row
            t_data[i] = currentRow;
        }

        col = newColNum;
    } else {
        std::cerr << "row length is not eq to the one in table." << std::endl;
        exit(1);
    }
}

/**
 * Push given table's elements to the back of each row
 * @tparam T
 * @param t
 */
template <class T> void Table<T>::push_back_columns(const Table<T> &t)
{
    if (t.numRows() == row)
    {
        size_type newColNum = col + t.numColumns();

        // Loop through each row
        for (size_type i = 0; i < row; i++)
        {
            // Construct new Row Array
            T* currentRow = new T[newColNum];
            for (size_type j = 0; j < col; j++)
            {
                currentRow[j] = t_data[i][j];
            }

            // Combine new Cols to Table
            for (size_type j = 0; j < t.numColumns(); j++)
            {
                currentRow[col + j] = t[i][j];
            }

            // Delete old Row
            delete [] t_data[i];

            // Assign new Row
            t_data[i] = currentRow;
        }

        col = newColNum;
    } else {
        std::cerr << "row length is not eq to the one in table." << std::endl;
        exit(1);
    }
}

/**
 * Push back a new row to current table
 * @tparam T
 * @param v
 */
template <class T> void Table<T>::push_back_row(const std::vector<T> &v)
{
    if ((size_type)v.size() == col)
    {
        size_type newRowNum = row + 1;
        // Constructing new main Array
        T** new_data = new T*[newRowNum];

        // Copy old Pointers to new main Array
        for (size_type i = 0; i < row; i++)
        {
            new_data[i] = t_data[i];
        }

        // Create new Array and copy elements from given vector
        T* currentRow = new T[col];
        for (size_type i = 0; i < col; i++)
        {
            currentRow[i] = v[i];
        }

        // Assign new Row to main Array
        new_data[newRowNum - 1] = currentRow;

        // Delete old Array
        delete [] t_data;

        // Assign new data Array
        t_data = new_data;
        row = newRowNum;

    } else {
        std::cerr << "col length is not eq to the ones in table." << std::endl;
        exit(1);
    }
}

/**
 * Copy Given Table and push back to current table as new rows
 * @tparam T
 * @param t
 */
template <class T> void Table<T>::push_back_rows(const Table<T> &t)
{
    if (t.numColumns() == col)
    {

        size_type newRowNum = row + t.numRows();

        // Expend the main Array
        T** new_data = new T*[newRowNum];

        // Copy old main Array
        for (size_type i = 0; i < row; i++)
        {
            new_data[i] = t_data[i];
        }

        // Loop through given Table
        for (size_type i = 0; i < t.numRows(); i++)
        {
            T* currentRow = new T[col];

            // Copy new Table row's elements
            for (size_type j = 0; j < col; j++)
            {
                currentRow[j] = t[i][j];
            }

            // Add row to the back of current Table
            new_data[row + i] = currentRow;
        }

        // Delete old main array
        delete [] t_data;

        // Assign new main Array
        t_data = new_data;
        row = newRowNum;
    } else {
        std::cerr << "col length is not eq to the ones in table." << std::endl;
        exit(1);
    }
}

/**
 * Remove the last line of the table
 * @tparam T
 */
template <class T> void Table<T>::pop_back_row()
{
    if (row > 0)
    {
        size_type newRowNum = row - 1;

        // Create new main Array
        T** new_data = new T*[newRowNum];

        // Copy old pointers, except the last one
        for (size_type i = 0; i < newRowNum; i++)
        {
            new_data[i] = t_data[i];
        }

        // Release the last row and the origin Array
        delete [] t_data[row - 1];
        delete [] t_data;

        // Assign the new main Array
        row = newRowNum;
        t_data = new_data;

    } else {
        std::cerr << "row eq or smaller than 0 is not allowed to exec such action." << std::endl;
        exit(1);
    }
}

/**
 * Remove the last element of every row (Change by Row)
 * @tparam T
 */
template <class T> void Table<T>::pop_back_column()
{
    if (col > 0)
    {
        size_type newCol = col - 1;

        // Loop through Rows
        for (size_type i = 0; i < row; i++)
        {
            // Create new Row array
            T* currentRow = new T[newCol];

            // Copy old element, except the last one
            for (size_type j = 0; j < newCol; j++)
            {
                currentRow[j] = t_data[i][j];
            }

            // Delete old Row
            delete [] t_data[i];

            // Assign new Row
            t_data[i] = currentRow;
        }

        col = newCol;
    } else {
        std::cerr << "col eq or smaller than 0 is not allowed to exec such action." << std::endl;
        exit(1);
    }
}

/**
 * Print Current Table
 * @tparam T
 */
template <class T> void Table<T>::print()
{
    size_type l = getLongestElementLength();
    std::cout << "Table: " << row << " rows, "<< col <<" cols"<< std::endl;
    std::cout << std::left;

    for (size_type i = 0; i < row; i++)
    {
        for (size_type j = 0; j < col; j++)
        {
            std::cout << std::setw(l) << t_data[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

#endif //INC_4TH_TABLE_H
