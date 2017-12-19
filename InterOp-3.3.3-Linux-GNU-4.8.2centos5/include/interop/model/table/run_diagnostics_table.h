/** Model for the run diagnostics table
 *
 *  @file
 *  @date  5/12/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <iosfwd>
#include "interop/model/table/run_diagnostics_column.h"


namespace illumina { namespace interop { namespace model { namespace table
{
    /** Describes the run diagnostics table, row data, column headers and boolean filled */
    class run_diagnostics_table
    {
    public:
        /** Define the type of a table entry */
        typedef ::uint64_t data_t;
        /** Define a column vector */
        typedef std::vector< run_diagnostics_column> column_vector_t;
        /** Define a data vector */
        typedef std::vector< data_t > data_vector_t;

    private:
        /** Define a data vector */
        typedef std::vector< size_t > offset_vector_t;

    public:
        /** Constructor */
        run_diagnostics_table() : m_row_count(0), m_col_count(0){}

    public:
        /** Reserve space for the rows
         *
         * @param rows number of rows
         * @param cols column vector
         * @param data table cell data
         */
        void set_data(const size_t rows, column_vector_t& cols, data_vector_t& data)
        {
            if(cols.empty())
            {
                clear();
                return;
            }
            m_columns.swap(cols);
            m_data.swap(data);
            m_row_count = rows;
            m_col_count = m_columns.back().column_count();
            m_enum_to_index.assign(RunDiagnosticsColumnCount, static_cast<size_t>(RunDiagnosticsColumnCount));
            for(size_t i=0;i<m_columns.size();++i)
                m_enum_to_index[m_columns[i].id()] = i;
        }
        /** Get a reference to a row
         *
         * @param r row row index
         * @param c col column index
         * @return cell value
         */
        ::uint64_t operator()(const size_t r, const run_diagnostics_column_id c)const throw(model::index_out_of_bounds_exception)
        {
            if(static_cast<size_t>(c) >= m_enum_to_index.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Invalid enum id for column");
            const size_t col = m_enum_to_index[static_cast<size_t>(c)];
            if(col >= m_enum_to_index.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Invalid enum - column not filled");
            return at(r, col);
        }
        /** Get a reference to a row
         *
         * @param r row row index
         * @param c col column index
         * @return cell value
         */
        ::uint64_t operator()(const size_t r, const size_t c)const throw(model::index_out_of_bounds_exception)
        {
            return at(r, c);
        }
        /** Get a reference to a row
         *
         * @param r row row index
         * @param c col column index
         * @param subcol sub column offset
         * @return cell value
         */
        ::uint64_t operator()(const size_t r, const size_t c, const size_t subcol=0)const throw(model::index_out_of_bounds_exception)
        {
            if(r >=m_row_count) INTEROP_THROW(model::index_out_of_bounds_exception, "Row out of bounds");
            if(c >=m_columns.size()) INTEROP_THROW(model::index_out_of_bounds_exception, "Column out of bounds");
            const size_t col = m_columns[c].offset()+subcol;
            if(col >=m_col_count) INTEROP_THROW(model::index_out_of_bounds_exception, "Column data offset out of bounds");
            const size_t index = r*m_col_count+col;
            INTEROP_ASSERT(index < m_data.size());
            return m_data[index];
        }
        /** Get a reference to a row
         *
         * @deprecated Will be removed in next feature version (use operator() instead for C++ Code)
         * @param r row row index
         * @param c col column index
         * @return cell value
         */
        ::uint64_t at(const size_t r, const size_t c)const throw(model::index_out_of_bounds_exception)
        {
            if(r >=m_row_count) INTEROP_THROW(model::index_out_of_bounds_exception, "Row out of bounds");
            if(c >=m_columns.size()) INTEROP_THROW(model::index_out_of_bounds_exception, "Column out of bounds");
            const size_t col = m_columns[c].offset();
            if(col >=m_col_count) INTEROP_THROW(model::index_out_of_bounds_exception, "Column data offset out of bounds");
            const size_t index = r*m_col_count+col;
            INTEROP_ASSERT(index < m_data.size());
            return m_data[index];
        }
        /** Get a vector of column headers
         *
         * @return column headers
         */
        const column_vector_t& columns()const
        {
            return m_columns;
        }
        /** Test if the table is empty
         *
         * @return true if empty
         */
        bool empty()const
        {
            return m_data.empty();
        }
        /** Clear the contents of the table
         */
        void clear()
        {
            m_data.clear();
            m_columns.clear();
            m_col_count = 0;
            m_row_count = 0;
        }
        /** Get the current column description (which may have subcolumns)
         *
         * @param col_index index of column description
         * @return column description
         */
        const run_diagnostics_column& column_at(const size_t col_index)throw(model::index_out_of_bounds_exception)
        {
            if( col_index >= m_columns.size()) INTEROP_THROW(model::index_out_of_bounds_exception, "Column index of out bounds");
            return m_columns[col_index];
        }

    public:
        /** Number of columns
         *
         * @return column count
         */
        size_t column_count()const
        {
            return m_columns.size();
        }
        /** Number of columns including subcolumns in the table
         *
         * @return column count
         */
        size_t total_column_count()const
        {
            return m_col_count;
        }
        /** Number of rows in the table
         *
         * @return row count
         */
        size_t row_count()const
        {
            return m_row_count;
        }

    private:
        friend std::istream& operator>>(std::istream& in, run_diagnostics_table& table);
        friend std::ostream& operator<<(std::ostream& out, const run_diagnostics_table& table);
    private:
        data_vector_t m_data;
        column_vector_t m_columns;
        offset_vector_t m_enum_to_index;
        size_t m_row_count;
        size_t m_col_count;
    };
}}}}

