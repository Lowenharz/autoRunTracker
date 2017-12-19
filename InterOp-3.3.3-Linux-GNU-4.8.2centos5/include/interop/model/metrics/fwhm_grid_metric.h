/** Set of FWHM grid metrics
 *
 * The InterOp files parsed by this class include:
 *  - InterOp/FWHMGridMetrics.bin
 *  - InterOp/FWHMGridMetricsOut.bin
 *
 * The FWHMGrid represents a spatial representation of the full-width half-max value for an image. Each image
 * is split up into one or more subgrids, and the average full-width half-max is calculated and reported
 * for each of these subgrids.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 05/25/2016
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/io/format/generic_layout.h"
#include "interop/io/layout/base_metric.h"
#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/model/metric_base/metric_set.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing a FWHM grid metric set
     *
     * @note This is an IUO metric
     */
    class fwhm_grid_metric_header : public metric_base::base_cycle_metric::header_type
    {
    public:
        /** Unsigned 16-bit integer used for bin and channel counts
         */
        typedef ::uint16_t ushort_t;
    public:
        /** Constructor
         *
         * @param num_bins_x number of bins in the X dimension
         * @param num_bins_y number of bins in the Y dimension
         * @param channel_count number of channels
         */
        fwhm_grid_metric_header(const ushort_t num_bins_x, const ushort_t num_bins_y, const ushort_t channel_count) :
                m_num_bins_x(num_bins_x), m_num_bins_y(num_bins_y), m_channel_count(channel_count)
        { }

        /** Number of bins in the X dimension
         *
         * @return number of bins
         */
        ushort_t num_bins_x() const
        { return m_num_bins_x; }

        /** Number of bins in the Y dimension
         *
         * @return number of bins
         */
        ushort_t num_bins_y() const
        { return m_num_bins_y; }

        /** Number of channels
         *
         * @return number of channels
         */
        ushort_t channel_count() const
        { return m_channel_count; }

        /** Generate a default header
         *
         * @return default header
         */
        static fwhm_grid_metric_header default_header()
        {
            return fwhm_grid_metric_header(0, 0, 0);
        }
        /** Clear the data
         */
        void clear()
        {
            m_num_bins_x=0;
            m_num_bins_y=0;
            m_channel_count=0;
            metric_base::base_cycle_metric::header_type::clear();
        }


    private:
        ushort_t m_num_bins_x;
        ushort_t m_num_bins_y;
        ushort_t m_channel_count;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** @brief FWHM grid metric
     *
     * Each image is split up into one or more subgrids, and the average full-width half-max is calculated and reported
     * for each of these subgrids. This is reported on a per-image level (lane/tile/cycle/channel)
     *
     * For speed and memory reasons, we only report this for the first and last cycle of each read.
     *
     * @note Supported version: 1 and 2
     * @note This is an IUO metric
     */
    class fwhm_grid_metric : public metric_base::base_cycle_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::FWHMGrid,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };
        /** FWHM grid metric header
         */
        typedef fwhm_grid_metric_header header_type;
        /** Vector of floats
         */
        typedef std::vector<float> float_vector;
        /** Vector of float vectors
         */
        typedef std::vector<float_vector> float_vector2d;
        /** Vector of 2D float vectors
        */
        typedef std::vector<float_vector2d> float_vector3d;

    public:
        /** Constructor
         */
        fwhm_grid_metric() :
                metric_base::base_cycle_metric(0, 0, 0)
        { }
        /** Constructor
         *
         * @param header metric set header
         */
        fwhm_grid_metric(const header_type& header) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_fwhm_grid(header.channel_count(),
                            float_vector2d(header.num_bins_y(), float_vector(header.num_bins_x())))
        { }

        /** Constructor
         *
         * @note Version 1
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param fwhm_grid 3-D subtile map of the FWHM for a lane/tile/cycle (channels x 2-D subtile grid)
         */
        template<class FloatVector3D>
        fwhm_grid_metric(const uint_t lane,
                         const uint_t tile,
                         const uint_t cycle,
                         const FloatVector3D &fwhm_grid) :
                metric_base::base_cycle_metric(lane, tile, cycle),
                m_fwhm_grid(fwhm_grid)
        {
        }


        /** Constructor
         *
         * @note Version 1
         * @param channel_count number of channels
         * @param num_bins_x number of subtile bins in the X dimension
         * @param num_bins_y number of subtile bins in the Y dimension
         */
        fwhm_grid_metric(const size_t channel_count,
                         const size_t num_bins_x,
                         const size_t num_bins_y) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_fwhm_grid(channel_count, float_vector2d(num_bins_y, float_vector(num_bins_x)))
        {
        }

    public:
        /** Setter
       *
       * @note Version 1
       * @param lane lane number
       * @param tile tile number
       * @param cycle cycle number
       * @param fwhm_grid 3-D (channels x 2-D subtile grid) map of the FWHM
       */
        template<class FwhmVector>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const FwhmVector& fwhm_grid)
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            INTEROP_ASSERT(m_fwhm_grid.size() == fwhm_grid.size());
            INTEROP_ASSERT(m_fwhm_grid[0].size() == fwhm_grid[0].size());
            INTEROP_ASSERT(m_fwhm_grid[0][0].size() == fwhm_grid[0][0].size());

            for(size_t channel_index = 0; channel_index < m_fwhm_grid.size(); ++channel_index)
            {
                for (size_t row_bin = 0; row_bin < m_fwhm_grid[channel_index].size(); ++row_bin)
                {
                    m_fwhm_grid[channel_index][row_bin].assign(fwhm_grid[channel_index][row_bin].begin(),
                                                               fwhm_grid[channel_index][row_bin].end());
                }
            }
        }

        /** @defgroup fwhm_grid_metric FWHM grid metric
         *
         * Per tile per cycle focus grid metrics
         *
         * Most platforms only report the first and last cycle of each read
         *
         * @ref illumina::interop::model::metrics::fwhm_grid_metric "See full class description"
         * @{
         */
        /** Return an element of the subtile FWHM grid
         *
         * @param channel the channel index
         * @param row_bin the x index of the requested spatial bin
         * @param col_bin the y index of the requested spatial bin
         * @return the FWHM value corresponding to the bin index in the channel
         */
        float focus_score(const size_t channel,
                          const size_t row_bin,
                          const size_t col_bin) const throw(index_out_of_bounds_exception)
        {
            if (channel >= m_fwhm_grid.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Channel out of bounds for FWHMGrid: "
                        << " channel: " << channel << " > " << m_fwhm_grid.size());
            if (row_bin >= m_fwhm_grid[channel].size())
                INTEROP_THROW(index_out_of_bounds_exception, "X-bin out of bounds for FWHMGrid: "
                         << " row_bin: " << row_bin << " > " << m_fwhm_grid[channel].size());
            if (col_bin >= m_fwhm_grid[channel][row_bin].size())
                INTEROP_THROW(index_out_of_bounds_exception, "Y-bin out of bounds for FWHMGrid: "
                        << " col_bin: " << col_bin << " > " << m_fwhm_grid[channel][row_bin].size());
            return m_fwhm_grid[channel][row_bin][col_bin];
        }

        /** Returns the number of channels in the subtile FWHM grid
          *
          * @return channel count
          */
        size_t channel_count() const
        {
            return m_fwhm_grid.size();
        }

        /** Returns the number of rows in the subtile FWHM grid
        *
        * @return row count
        */
        size_t num_bins_row() const
        {
            return m_fwhm_grid.size() == 0 ? 0 : m_fwhm_grid[0].size();
        }

        /** Returns the number of columns in the subtile FWHM grid
         *
         * @return column count
         */
        size_t num_bins_col() const
        {
            return (m_fwhm_grid.size() == 0 || m_fwhm_grid[0].size() == 0) ? 0 : m_fwhm_grid[0][0].size();
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "FWHMGrid"; }

    private:
        float_vector3d m_fwhm_grid;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

