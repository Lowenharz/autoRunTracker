/** Model for the event table
 *
 *  @file
 *  @date  5/12/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <iosfwd>
#include "interop/util/math.h"
#include "interop/model/table/event_column.h"


namespace illumina { namespace interop { namespace model { namespace table
{
    /** Describes an event table, row data, column headers and boolean filled */
    class event_table
    {
    public:
        /** Define the type of a table entry */
        typedef ::uint64_t data_t;
        /** Define a column vector */
        typedef std::vector< event_column> column_vector_t;
        /** Define a data vector */
        typedef std::vector< data_t > data_vector_t;

    private:
        /** Define a data vector */
        typedef std::vector< size_t > offset_vector_t;

    public:
        /** Constructor */
        event_table() : m_row_count(0), m_col_count(0){}

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
            m_enum_to_index.assign(EventColumnCount, static_cast<size_t>(EventColumnCount));
            for(size_t i=0;i<m_columns.size();++i)
                m_enum_to_index[m_columns[i].id()] = i;
            INTEROP_ASSERT(m_data.size() == rows*m_columns.size());
        }
        /** Get a reference to a row
         *
         * @param r row row index
         * @param c col column index
         * @return cell value
         */
        ::uint64_t operator()(const size_t r, const event_column_id c)const  throw(model::index_out_of_bounds_exception)
        {
            if(static_cast<size_t>(c) >= m_enum_to_index.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Invalid enum id for column");
            const size_t col = m_enum_to_index[static_cast<size_t>(c)];
            if(col >= m_enum_to_index.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Invalid enum - column not filled");
            return operator()(r, col);
        }
        /** Get a reference to a row
         *
         * @param r row row index
         * @param c col column index
         * @return cell value
         */
        ::uint64_t operator()(const size_t r, const size_t c)const  throw(model::index_out_of_bounds_exception)
        {
            if(r >=m_row_count) INTEROP_THROW(model::index_out_of_bounds_exception, "Row out of bounds");
            if(c >=m_columns.size()) INTEROP_THROW(model::index_out_of_bounds_exception, "Column out of bounds");
            const size_t col = m_columns[c].offset();
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
        const event_column& column_at(const size_t col_index)throw(model::index_out_of_bounds_exception)
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
        friend std::istream& operator>>(std::istream& in, event_table& table);
        friend std::ostream& operator<<(std::ostream& out, const event_table& table);
    private:
        data_vector_t m_data;
        column_vector_t m_columns;
        offset_vector_t m_enum_to_index;
        size_t m_row_count;
        size_t m_col_count;
    };
    /** Compare two row indicies to determine which id in the table is less than another row
     */
    struct event_table_id_less
    {
        /** Constructor
         *
         * @param table reference to an imaging table
         */
        event_table_id_less(const event_table& table) : m_table(table){}

        /** Test if one row is less than another in terms of the tile id/cycle/event ordering
         *
         * @param lhs_row index to one row
         * @param rhs_row index to another row
         * @return true if the id in the first row is less than the second
         */
        bool operator()(const size_t lhs_row, const size_t rhs_row)const
        {
            const size_t lhs_ticks = static_cast<size_t>(m_table(lhs_row, PointTicksEventColumn));
            const size_t rhs_ticks = static_cast<size_t>(m_table(rhs_row, PointTicksEventColumn));
            if(lhs_ticks == rhs_ticks)
            {
                const size_t lhs_lane = static_cast<size_t>(m_table(lhs_row, LaneEventColumn));
                const size_t rhs_lane = static_cast<size_t>(m_table(rhs_row, LaneEventColumn));
                if (lhs_lane == rhs_lane)
                {
                    const size_t lhs_tile = static_cast<size_t>(m_table(lhs_row, TileEventColumn));
                    const size_t rhs_tile = static_cast<size_t>(m_table(rhs_row, TileEventColumn));
                    if (lhs_tile == rhs_tile)
                    {
                        const size_t lhs_cycle = static_cast<size_t>(m_table(lhs_row, CycleEventColumn));
                        const size_t rhs_cycle = static_cast<size_t>(m_table(rhs_row, CycleEventColumn));
                        if (lhs_cycle == rhs_cycle)
                        {
                            const size_t lhs_event = static_cast<size_t>(m_table(lhs_row, EventEventColumn));
                            const size_t rhs_event = static_cast<size_t>(m_table(rhs_row, EventEventColumn));
                            return lhs_event < rhs_event;
                        }
                        return lhs_cycle < rhs_cycle;
                    }
                    return lhs_tile < rhs_tile;
                }
                return lhs_lane < rhs_lane;
            }
            return lhs_ticks < rhs_ticks;
        }

    private:
        const event_table& m_table;
    };

}}}}

