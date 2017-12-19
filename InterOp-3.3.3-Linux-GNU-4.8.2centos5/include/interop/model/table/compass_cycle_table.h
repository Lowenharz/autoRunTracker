/** Model for the compass cycle table
 *
 *  @file
 *  @date  11/18/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <iosfwd>
#include <vector>
#include <string>
#include "interop/model/model_exceptions.h"

namespace illumina { namespace interop { namespace model { namespace table
{

    /** Compass cycle table */
    class compass_cycle_table
    {
    public:
        /** Constructor */
        compass_cycle_table() : m_column_count(0), m_row_count(0){}

    public:
        /** Resize the data in the table
         *
         * @param row_count number of rows in table
         * @param col_count number of columns in table
         */
        void resize(const size_t row_count, const size_t col_count)
        {
            m_data.assign(row_count*col_count, std::numeric_limits<float>::quiet_NaN());
            m_headers.assign(row_count, "");
            m_row_count = row_count;
            m_column_count = col_count;
        }
        /** Get value of the cell at given row and column
         *
         * @param row row index in table
         * @param col column index in table
         * @return value of cell
         */
        float operator()(const size_t row, const size_t col)const throw(index_out_of_bounds_exception)
        {
            if(row >= m_row_count)
                INTEROP_THROW(index_out_of_bounds_exception, "Row exceeds row count: " << row << " >= " << m_row_count);
            if(col >= m_column_count)
                INTEROP_THROW(index_out_of_bounds_exception, "Column exceeds column count");
            const size_t idx = row*m_column_count + col;
            return m_data[idx];
        }

        /** Get reference to the cell at given row and column
         *
         * @param row row index in table
         * @param col column index in table
         * @return reference to cell
         */
        float& operator()(const size_t row, const size_t col) throw(index_out_of_bounds_exception)
        {
            if(row >= m_row_count)
                INTEROP_THROW(index_out_of_bounds_exception, "Row exceeds row count: " << row << " >= " << m_row_count);
            if(col >= m_column_count)
                INTEROP_THROW(index_out_of_bounds_exception, "Column exceeds column count");
            const size_t idx = row*m_column_count + col;
            return m_data[idx];
        }
        /** Get row label at given row index
         *
         * @param row index
         * @return label
         */
        const std::string& column_at(const size_t row)const throw(index_out_of_bounds_exception)
        {
            if(row >= m_row_count)
                INTEROP_THROW( index_out_of_bounds_exception, "Row exceeds row count: " << row << " >= " << m_row_count);
            return m_headers[row];
        }
        /** Get row label at given row index
         *
         * @param row index
         * @return label
         */
        std::string& column_at(const size_t row) throw(index_out_of_bounds_exception)
        {
            if(row >= m_row_count)
                INTEROP_THROW( index_out_of_bounds_exception, "Row exceeds row count: " << row << " >= " << m_row_count);
            return m_headers[row];
        }
        /** Get number of columns in table
         *
         * @return number of columns in table
         */
        size_t column_count()const
        {
            return m_column_count;
        }
        /** Get number of rows in table
         *
         * @return number of rows in table
         */
        size_t row_count()const
        {
            return m_row_count;
        }

    private:
        std::vector<float> m_data;
        std::vector<std::string> m_headers;
        size_t m_column_count;
        size_t m_row_count;
    };

}}}}
