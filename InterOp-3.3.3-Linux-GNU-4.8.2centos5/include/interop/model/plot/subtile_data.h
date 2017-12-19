/** Encapsulates all the data for a subtile flowcell heat map
 *
 *  @file
 *  @date 5/6/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include "interop/model/model_exceptions.h"
#include "interop/util/exception.h"
#include "interop/util/assert.h"
#include "interop/model/plot/series.h"
#include "interop/model/plot/axes.h"
#include "interop/model/plot/flowcell_data.h"

namespace illumina { namespace interop { namespace model { namespace plot
{

    /** Encapsulates all data for a subtile flowcell heat map
     *
     * @todo refactor so it does not depend on 2-axes (from heatmap/chart_data)
     */
    class subtile_data : public flowcell_data
    {
    public:
        /** Constructor */
        subtile_data() : flowcell_data(), m_subtile_count_x(0), m_subtile_count_y(0)
        { }

        /** Destructor */
        virtual ~subtile_data()
        {
        }

    public:
        /** Resize the heat map to the given number of rows and columns
         *
         * @param data_buffer buffer to hold the flow cell values
         * @param id_buffer buffer to hold the tile ids
         */
        void set_buffer(float *data_buffer,
                        ::uint32_t *id_buffer) throw(invalid_parameter)
        {
            heatmap_data::set_buffer(data_buffer);
            flowcell_data::set_buffer(id_buffer);
        }
        /** Resize the heat map to the given number of rows and columns
         *
         * @param data_buffer buffer to hold the flow cell values
         * @param id_buffer buffer to hold the tile ids
         * @param lanes number of lanes
         * @param swaths number of swaths
         * @param tiles number of tiles
         * @param subtile_count_x number of subtile sections in x
         * @param subtile_count_y number of subtile sections in y
         */
        void set_buffer(float *data_buffer,
                        ::uint32_t *id_buffer,
                        const size_t lanes,
                        const size_t swaths,
                        const size_t tiles,
                        const size_t subtile_count_x,
                        const size_t subtile_count_y)
        {
            heatmap_data::set_buffer(data_buffer, lanes, swaths * tiles * subtile_count_x * subtile_count_y);
            flowcell_data::set_buffer(id_buffer, swaths, tiles);
            m_subtile_count_x = subtile_count_x;
            m_subtile_count_y = subtile_count_y;
        }

        /** Resize the subtile flowcell heat map to the given number of rows, columns, and subtile bins
         *
         * @param lanes number of lanes
         * @param swaths number of swaths
         * @param tiles number of tiles
         * @param subtile_count_x number of subtile bins in the X dimension
         * @param subtile_count_y number of subtile bins in the Y dimension
         */
        void resize(const size_t lanes,
                    const size_t swaths,
                    const size_t tiles,
                    const size_t subtile_count_x,
                    const size_t subtile_count_y)
        {
            m_subtile_count_x = subtile_count_x;
            m_subtile_count_y = subtile_count_y;
            heatmap_data::resize(lanes, swaths * tiles * subtile_count_x * subtile_count_y);
            flowcell_data::resize(swaths, tiles);
        }

        /** Set data at given location in the flowcell
         *
         * @param lane_idx lane index
         * @param tile_idx tile index within the lane
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @param tile_id id of the tile
         * @param value value of the metric
         */
        void set_data(const size_t lane_idx, const size_t tile_idx, const size_t bin_x, const size_t bin_y,
                      const ::uint32_t tile_id, const float value)
        throw(model::index_out_of_bounds_exception)
        {
            if(tile_idx> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");

            if (lane_idx >= lane_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane index out of bounds");
            const size_t loc = tile_idx * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (loc >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Location index out of bounds");
            //INTEROP_ASSERT(lane < m_data.size());
            heatmap_data::operator()(lane_idx, loc) = value;
            m_data[flowcell_data::index_of(lane_idx, loc)] = tile_id;
        }
        /** Populate a tile level buffer with subtile values
         *
         * @param buffer tile level buffer
         * @param buffer_size size of tile level buffer
         * @param lane_idx tile lane index (column)
         * @param tile_idx index of tile (row)
         */
        void populate_tile_data_at(float *buffer, const size_t buffer_size, const size_t lane_idx,
                                   const size_t tile_idx)
        {
            if (lane_idx >= lane_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane index out of bounds");
            if(tile_idx> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            const size_t loc = tile_idx * subtile_count_x();
            if (loc >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Location index out of bounds");
            if ((subtile_count_x() * subtile_count_y()) > buffer_size)
                INTEROP_THROW(model::index_out_of_bounds_exception, "Insufficient buffer size");
            // Todo: optimize this
            for (size_t bin_x = 0; bin_x < subtile_count_x(); ++bin_x)
            {
                for (size_t bin_y = 0; bin_y < subtile_count_y(); ++bin_y)
                {
                    const size_t buffer_idx = bin_x * subtile_count_y() + bin_y;
                    const size_t idx = loc + buffer_idx;
                    buffer[buffer_idx] = heatmap_data::operator()(lane_idx, idx);
                }
            }
        }


        /** Get value at given row and column
         *
         * @param row row index
         * @param col column index
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @return value
         */
        float operator()(const size_t row, const size_t col, const size_t bin_x,
                 const size_t bin_y) const throw(model::index_out_of_bounds_exception)
        {
            const size_t tile_idx = col * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (row >= row_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Row index out of bounds");
            if(col> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            //TODO: column_count() has sub-columns folded in for the subtile plot, so it's a bit of a misnomer
            if (tile_idx >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Column index out of bounds: "
                        << tile_idx << " >= " << column_count()
                        << " col: " << col << " bin_x: " << bin_x << " bin_y: " << bin_y);
            if (bin_x >= subtile_count_x())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index X out of bounds: "
                        << bin_x << " >= " << subtile_count_x());
            if (bin_y >= subtile_count_y())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index Y out of bounds: "
                        << bin_y << " >= " << subtile_count_y());
            return heatmap_data::operator()(row, tile_idx);
        }

        /** Get value at given row and column
         *
         * @param row row index
         * @param col column index
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @return value
         */
        float& operator()(const size_t row, const size_t col, const size_t bin_x,
                 const size_t bin_y) throw(model::index_out_of_bounds_exception)
        {
            const size_t tile_idx = col * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (row >= row_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Row index out of bounds");
            if(col> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            //TODO: column_count() has sub-columns folded in for the subtile plot, so it's a bit of a misnomer
            if (tile_idx >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Column index out of bounds: "
                        << tile_idx << " >= " << column_count()
                        << " col: " << col << " bin_x: " << bin_x << " bin_y: " << bin_y);
            if (bin_x >= subtile_count_x())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index X out of bounds: "
                        << bin_x << " >= " << subtile_count_x());
            if (bin_y >= subtile_count_y())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index Y out of bounds: "
                        << bin_y << " >= " << subtile_count_y());
            return heatmap_data::operator()(row, tile_idx);
        }

        /** Get value at given index
         *
         * @deprecated Will be removed in next feature version (use operator[] instead for C++ Code)
         * @param idx index
         * @return value
         */
        float at(const size_t idx) const throw(model::index_out_of_bounds_exception)
        {
            return flowcell_data::at(idx);
        }

        /** Get tile ID at given row and column, and sub tile positions
         *
         * @param row row index
         * @param col column index
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @return tile id
         */
        ::uint32_t tile_id(const size_t row,
                           const size_t col,
                           const size_t bin_x,
                           const size_t bin_y) const throw(model::index_out_of_bounds_exception)
        {
            const size_t tile_idx = col * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (row >= row_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Row index out of bounds");
            if(col> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            //TODO: column_count() has sub-columns folded in for the subtile plot, so it's a bit of a misnomer
            if (bin_x >= subtile_count_x())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index X out of bounds: "
                        << bin_x << " >= " << subtile_count_x());
            if (bin_y >= subtile_count_y())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index Y out of bounds: "
                        << bin_y << " >= " << subtile_count_y());
            if (tile_idx >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Column index out of bounds: "
                        << tile_idx << " >= " << column_count()
                        << " col: " << col << " bin_x: " << bin_x << " bin_y: " << bin_y);
            return flowcell_data::tile_id(row, tile_idx);
        }

        /** Get tile ID at given row and column, and sub tile positions
         *
         * @param row row index
         * @param col column index
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @return tile id
         */
        ::uint32_t& tile_id(const size_t row,
                            const size_t col,
                            const size_t bin_x,
                            const size_t bin_y) throw(model::index_out_of_bounds_exception)
        {
            const size_t tile_idx = col * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (row >= row_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Row index out of bounds");
            if(col> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            //TODO: column_count() has sub-columns folded in for the subtile plot, so it's a bit of a misnomer
            if (bin_x >= subtile_count_x())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index X out of bounds: "
                        << bin_x << " >= " << subtile_count_x());
            if (bin_y >= subtile_count_y())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index Y out of bounds: "
                        << bin_y << " >= " << subtile_count_y());
            if (tile_idx >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Column index out of bounds: "
                        << tile_idx << " >= " << column_count()
                        << " col: " << col << " bin_x: " << bin_x << " bin_y: " << bin_y);
            return flowcell_data::tile_id(row, tile_idx);
        }

        /** Get subtile count in X dimension
         *
         * @return number of subtiles in X
         */
        size_t subtile_count_x() const
        {
            return m_subtile_count_x;
        }

        /** Get subtile count in Y dimension
         *
         * @return number of subtiles in Y
         */
        size_t subtile_count_y() const
        {
            return m_subtile_count_y;
        }

        /** Clear the data
         */
        void clear()
        {
            flowcell_data::clear();
            m_subtile_count_x = 0;
            m_subtile_count_y = 0;
        }
        /** Get the index of the row and column in the array
         *
         * @param row row index
         * @param col column index
         * @param bin_x subtile X bin of the data point
         * @param bin_y subtile Y bin of the data point
         * @return index in array
         */
        size_t index_of(const size_t row, const size_t col, const size_t bin_x, const size_t bin_y) const
        throw(model::index_out_of_bounds_exception)
        {
            if (row >= row_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Row index out of bounds");
            if(col> total_tile_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Tile index out of bounds");
            //TODO: column_count() has sub-columns folded in for the subtile plot, so it's a bit of a misnomer
            if (bin_x >= subtile_count_x())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index X out of bounds: "
                        << bin_x << " >= " << subtile_count_x());
            if (bin_y >= subtile_count_y())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Subtile index Y out of bounds: "
                        << bin_y << " >= " << subtile_count_y());
            const size_t tile_idx = col * subtile_count_x() * subtile_count_y() + bin_x * subtile_count_y() + bin_y;
            if (tile_idx >= column_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Column index out of bounds: "
                        << tile_idx << " >= " << column_count()
                        << " col: " << col << " bin_x: " << bin_x << " bin_y: " << bin_y);
            return flowcell_data::index_of(row, tile_idx);
        }

        friend std::ostream& operator<<(std::ostream& out, const subtile_data& data)
        {
            out << static_cast<const flowcell_data&>(data);
            out << data.m_subtile_count_x << ",";
            out << data.m_subtile_count_y << ",";
            return out;
        }
        friend std::istream& operator>>(std::istream& in, subtile_data& data)
        {
            in >> static_cast<flowcell_data&>(data);
            std::string tmp;
            std::getline(in, tmp, ',');
            data.m_subtile_count_x = util::lexical_cast<size_t>(tmp);
            std::getline(in, tmp, ',');
            data.m_subtile_count_y = util::lexical_cast<size_t>(tmp);
            return in;
        }


    private:
        size_t m_subtile_count_x;
        size_t m_subtile_count_y;
    };

}}}}

