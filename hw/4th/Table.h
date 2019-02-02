#ifndef INC_4TH_TABLE_H
#define INC_4TH_TABLE_H


template <class T> class Table {
public:
    typedef unsigned int size_type;

    Table(){ this->create(); }
    Table(size_type row, size_type col) { this->create(row, col); }
    Table(size_type row, size_type col, const T &t) { this->create(row, col, t); }
    Table(const Table& table) { copy(table); }

    T* operator[](size_type i) { return t_data[i]; }
    const T* operator[](size_type i) const { return t_data[i]; }
    Table& operator=(const Table& table);

    ~Table() { this->reset(); };
    
    size_type numRows() const { return row; }
    size_type numColumns() const { return col; }

    const T& get(size_type row, size_type col) const;
    void set(size_type row, size_type col, const T &t);

    void push_back_column(std::vector<T> &v);
    void push_back_row(std::vector<T> &v);
    void pop_back_row();
    void pop_back_column();

    void print();
    
private:
    void create();
    void create(size_type row, size_type col);
    void create(size_type row, size_type col, const T &t);
    
    void copy(const Table<T> &t);

    bool isLegalIndex(size_type row, size_type col) const;
    void reset();

    size_type row;
    //size_type row_allocated;
    size_type col;
    //size_type col_allocated;
    T** t_data;
};

template <class T> void Table<T>::create()
{
    t_data = new T*[0];
    row = col = 0;
}

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

template <class T> Table<T>& Table<T>::operator=(const Table<T>& t)
{
    if (this != &t)
    {
        this->reset();
        this->copy(t);
    }

    return *this;
}

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

template <class T> void Table<T>::reset()
{
    for (size_type i = 0; i < row; i++)
    {
        delete [] t_data[i];
    }

    delete [] t_data;
}

template <class T> bool Table<T>::isLegalIndex(size_type row, size_type col) const
{
    return row <= this->row && col <= this->col;
}

// Public members
template <class T> const T& Table<T>::get(size_type row, size_type col) const
{
    if (isLegalIndex(row, col))
    {
        return t_data[row][col];
    }
    
    std::cerr << "Index out of bound!" << std::endl;
    exit(1);
}

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

template <class T> void Table<T>::push_back_column(std::vector<T> &v)
{
    if ((size_type)v.size() == row)
    {
        size_type newColNum = col + 1;

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
        std::cerr << "col length is not eq to the one in table." << std::endl;
        exit(1);
    }
}

template <class T> void Table<T>::push_back_row(std::vector<T> &v)
{
    if ((size_type)v.size() == col)
    {
        // Constructing Array
        T* currentRow = new T[col];
        size_type newRowNum = row + 1;
        for (size_type i = 0; i < col; i++)
        {
            currentRow[i] = v[i];
        }

        // We need to expend the array
        // Create new Array
        T** new_data = new T*[newRowNum];

        for (size_type i = 0; i < row; i++)
        {
            new_data[i] = t_data[i];
        }

        new_data[newRowNum - 1] = currentRow;

        // Delete old array
        delete [] t_data;

        // Assign new data
        t_data = new_data;
        row = newRowNum;

    } else {
        std::cerr << "row length is not eq to the ones in table." << std::endl;
        exit(1);
    }
}

template <class T> void Table<T>::pop_back_row()
{
    if (row > 0)
    {
        size_type newRowNum = row - 1;
        T** new_data = new T*[newRowNum];

        for (size_type i = 0; i < newRowNum; i++)
        {
            new_data[i] = t_data[i];
        }

        // Release the last row and the origin array
        delete [] t_data[row - 1];
        delete [] t_data;

        // Assign the new data
        row = newRowNum;
        t_data = new_data;

    } else {
        std::cerr << "row eq or smaller than 0 is not allowed to exec such action." << std::endl;
        exit(1);
    }
}

template <class T> void Table<T>::pop_back_column()
{
    if (col > 0)
    {
        size_type newCol = col - 1;
        for (size_type i = 0; i < row; i++)
        {
            // Copy and create new Col array
            T* currentCol = new T[newCol];
            for (size_type j = 0; j < newCol; j++)
            {
                currentCol[j] = t_data[i][j];
            }

            // Delete Origin Col
            delete [] t_data[i];

            // Assign new Col
            t_data[i] = currentCol;
        }

        col = newCol;
    } else {
        std::cerr << "col eq or smaller than 0 is not allowed to exec such action." << std::endl;
        exit(1);
    }
}

template <class T> void Table<T>::print()
{
    std::cout << "Table: " << row << " rows, "<< col <<" cols"<< std::endl;

    for (size_type i = 0; i < row; i++)
    {
        for (size_type j = 0; j < col; j++)
        {
            std::cout << t_data[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

#endif //INC_4TH_TABLE_H
