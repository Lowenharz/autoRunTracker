/** Q grid metric
 *
 * The Q grid metric contains subtile information on Q-score counts.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 6/22/2016
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/io/format/generic_layout.h"
#include "interop/io/layout/base_metric.h"
#include "interop/model/metric_base/base_metric.h"
#include "interop/model/metric_base/metric_set.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing a Q grid metric set
     *
     * @note This is an IUO metric
     */
    class q_grid_metric_header : public metric_base::base_metric::header_type
    {
    public:
        /** Unsigned int16_t
         */
        typedef ::uint16_t ushort_t;
    public:
        /** Constructor
         *
         * @param num_bins_x number of bins in the X dimension
         * @param num_bins_y number of bins in the Y dimension
         */
        q_grid_metric_header(const ushort_t num_bins_x, const ushort_t num_bins_y) :
                m_num_bins_x(num_bins_x), m_num_bins_y(num_bins_y)
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

        static q_grid_metric_header default_header()
        {
            return q_grid_metric_header(0, 0);
        }
        /** Clear the data
         */
        void clear()
        {
            m_num_bins_x=0;
            m_num_bins_y=0;
            metric_base::base_metric::header_type::clear();
        }


    private:
        ushort_t m_num_bins_x;
        ushort_t m_num_bins_y;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** Q grid metric
     *
     * The Q grid metric contains a subtile distribution of Q30+ counts
     *
     *
     * @note Supported versions: 1 and 2
     * @note This is an IUO metric
     */
    class q_grid_metric : public metric_base::base_read_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::QGrid,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };
        /** Q grid metric header
         */
        typedef q_grid_metric_header header_type;
        /** Vector of floats
         */
        typedef std::vector<uint32_t> uint32_vector;
        /** Vector of float vectors
         */
        typedef std::vector<uint32_vector> uint32_vector2d;
    public:
        /** Constructor
         */
        q_grid_metric() :
                metric_base::base_read_metric(0, 0, 0),
                m_raw_cluster_count(0), m_q30_cluster_count(0)
        { }
        /** Constructor
         *
         * @param header metric set header
         */
        q_grid_metric(const header_type& header) :
                metric_base::base_read_metric(0, 0, 0),
                m_raw_cluster_count(header.num_bins_x(), uint32_vector(header.num_bins_y())),
                m_q30_cluster_count(header.num_bins_x(), uint32_vector(header.num_bins_y()))
        { }

        /** Constructor
         *
         * @note Version 1
         * @param lane lane number
         * @param tile tile number
         * @param read read number
         * @param raw_cluster_count 2-D subtile map of the raw cluster count
         * @param q30_cluster_count 2-D subtile map of the Q30 cluster count
         */
        template<class UIntVector>
        q_grid_metric(const uint_t lane,
                      const uint_t tile,
                      const uint_t read,
                      const UIntVector &raw_cluster_count,
                      const UIntVector &q30_cluster_count) :
                metric_base::base_read_metric(lane, tile, read),
                m_raw_cluster_count(raw_cluster_count),
                m_q30_cluster_count(q30_cluster_count)
        {
        }

        /** Constructor
         *
         * @note Version 1
         * @param num_bins_x number of subtile bins in the X dimension
         * @param num_bins_y number of subtile bins in the Y dimension
         */
        q_grid_metric(const size_t num_bins_x,
                      const size_t num_bins_y) :
                metric_base::base_read_metric(0, 0, 0),
                m_raw_cluster_count(num_bins_x, uint32_vector(num_bins_y)),
                m_q30_cluster_count(num_bins_x, uint32_vector(num_bins_y))
        {
        }

    public:
        /** Setter
        *
        * @note Version 1
        * @param lane lane number
        * @param tile tile number
        * @param read read number
        * @param raw_cluster_count 2-D subtile map of the raw cluster count
        * @param q30_cluster_count 2-D subtile map of the Q30 cluster count
        */
        template<class RawClusterCountVector, class Q30ClusterCountVector>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t read,
                 const RawClusterCountVector &raw_cluster_count,
                 const Q30ClusterCountVector &q30_cluster_count)
        {
            metric_base::base_read_metric::set_base(lane, tile, read);
            INTEROP_ASSERT(m_raw_cluster_count.size() == raw_cluster_count.size());
            INTEROP_ASSERT(m_q30_cluster_count.size() == q30_cluster_count.size());
            INTEROP_ASSERT(raw_cluster_count.size() == q30_cluster_count.size());

            for (size_t x_bin = 0; x_bin < raw_cluster_count.size(); ++x_bin)
            {
                m_raw_cluster_count[x_bin].assign(raw_cluster_count[x_bin].begin(),
                                                raw_cluster_count[x_bin].end());
                m_q30_cluster_count[x_bin].assign(q30_cluster_count[x_bin].begin(),
                                                q30_cluster_count[x_bin].end());
            }
        }

        /** @defgroup q_grid_metric Q grid metric
         *
         * Per tile per read Q30 grid metrics
         *
         * @ref illumina::interop::model::metrics::q_grid_metric "See full class description"
         * @{
         */

        /** Return an element of the subtile raw cluster count grid
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @return raw cluster count corresponding to the bin index
         */
        uint32_t raw_cluster_count(const size_t x_bin, const size_t y_bin) const
        {
            if(x_bin >= m_raw_cluster_count.size())
                INTEROP_THROW(index_out_of_bounds_exception, "x-bin number out of bounds");
            if(y_bin >= m_raw_cluster_count[x_bin].size())
                INTEROP_THROW(index_out_of_bounds_exception, "y-bin number out of bounds");
            INTEROP_ASSERT(x_bin < m_raw_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_raw_cluster_count[x_bin].size());
            return m_raw_cluster_count[x_bin][y_bin];
        }

        /** Return an element of the subtile Q30+ grid
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @return Q30 cluster count corresponding to the bin index
         */
        uint32_t q30_cluster_count(const size_t x_bin, const size_t y_bin) const
        {
            if(x_bin >= m_q30_cluster_count.size())
                INTEROP_THROW(index_out_of_bounds_exception, "x-bin number out of bounds");
            if(y_bin >= m_q30_cluster_count[x_bin].size())
                INTEROP_THROW(index_out_of_bounds_exception, "y-bin number out of bounds");
            INTEROP_ASSERT(x_bin < m_q30_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_q30_cluster_count[x_bin].size());
            return m_q30_cluster_count[x_bin][y_bin];
        }

        /** Return an element of a %Q30 subtile grid
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @return %Q30 corresponding to the bin index
         */
        float percent_q30(const size_t x_bin, const size_t y_bin) const throw(index_out_of_bounds_exception)
        {
            if(x_bin >= m_q30_cluster_count.size())
                INTEROP_THROW(index_out_of_bounds_exception, "x-bin number out of bounds");
            if(y_bin >= m_q30_cluster_count[x_bin].size())
                INTEROP_THROW(index_out_of_bounds_exception, "y-bin number out of bounds");
            INTEROP_ASSERT(x_bin < m_q30_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_q30_cluster_count[x_bin].size());
            return static_cast<float>(m_q30_cluster_count[x_bin][y_bin]) / m_raw_cluster_count[x_bin][y_bin] * 100;
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "QGrid"; }

    private:
        uint32_vector2d m_raw_cluster_count;
        uint32_vector2d m_q30_cluster_count;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

