/** PF grid metric
 *
 * The PF grid metric contains subtile information on raw and PF cluster counts.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 01/11/2016
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
    /** Header information for writing a PF grid metric set
     *
     * @note This is an IUO metric
     */
    class pf_grid_metric_header : public metric_base::base_metric::header_type
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
         * @param subtile_area_in_mm2 area of the location grid in mm^2
         */
        pf_grid_metric_header(const ushort_t num_bins_x, const ushort_t num_bins_y, const float subtile_area_in_mm2) :
                m_num_bins_x(num_bins_x), m_num_bins_y(num_bins_y), m_subtile_area_in_mm2(subtile_area_in_mm2)
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

        /** Area of one subtile in mm^2
         *
         * @return area in mm^2
         */
        float subtile_area_in_mm2() const
        { return m_subtile_area_in_mm2; }

        /** Generate a default header
         *
         * @return default header
         */
        static pf_grid_metric_header default_header()
        {
            return pf_grid_metric_header(0, 0, 0);
        }
        /** Clear the data
         */
        void clear()
        {
            m_num_bins_x=0;
            m_num_bins_y=0;
            m_subtile_area_in_mm2=0;
            metric_base::base_metric::header_type::clear();
        }


    private:
        ushort_t m_num_bins_x;
        ushort_t m_num_bins_y;
        float m_subtile_area_in_mm2;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** PF grid metric
     *
     * The PF grid metric contains a subtile distribution of raw and PF cluster counts
     *
     *
     * @note Supported versions: 1 and 2
     * @note This is an IUO metric
     */
    class pf_grid_metric : public metric_base::base_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::PFGrid,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };
        /** PF grid metric header
         */
        typedef pf_grid_metric_header header_type;
        /** Vector of uint32s
         */
        typedef std::vector<uint32_t> uint32_vector;
        /** Vector of uint32 vectors
         */
        typedef std::vector<uint32_vector> uint32_vector2d;
    public:
        /** Constructor
         */
        pf_grid_metric() :
                metric_base::base_metric(0, 0), m_raw_cluster_count(0), m_pf_cluster_count(0)
        { }
        /** Constructor
         *
         * @param header metric set header
         */
        pf_grid_metric(const header_type& header) :
                metric_base::base_metric(0, 0),
                m_raw_cluster_count(header.num_bins_x(), uint32_vector(header.num_bins_y())),
                m_pf_cluster_count(header.num_bins_x(), uint32_vector(header.num_bins_y()))
        { }

        /** Constructor
         *
         * @note Version 1
         * @param lane lane number
         * @param tile tile number
         * @param raw_count 2-D subtile map of the raw cluster count
         * @param pf_count 2-D subtile map of the PF cluster count
         */
        template<class Uint32Vector2D>
        pf_grid_metric(const uint_t lane,
                       const uint_t tile,
                       const Uint32Vector2D &raw_count,
                       const Uint32Vector2D &pf_count) :
                metric_base::base_metric(lane, tile), m_raw_cluster_count(raw_count), m_pf_cluster_count(pf_count)
        {
        }


        /** Constructor
         *
         * @note Version 1
         * @param num_bins_x number of subtile bins in the X dimension
         * @param num_bins_y number of subtile bins in the Y dimension
         */
        pf_grid_metric(const size_t num_bins_x,
                       const size_t num_bins_y) :
                metric_base::base_metric(0, 0), m_raw_cluster_count(num_bins_x, uint32_vector(num_bins_y))
                , m_pf_cluster_count(num_bins_x, uint32_vector(num_bins_y))
        {
        }

    public:
        /** Setter
        *
        * @note Version 1
        * @param lane lane number
        * @param tile tile number
        * @param raw_count 2-D subtile map of the raw cluster count
        * @param pf_count 2-D subtile map of the PF cluster count
        */
        template<class RawCountVector, class PfCountVector>
        void set(const uint_t lane,
                 const uint_t tile,
                 const RawCountVector &raw_count,
                 const PfCountVector &pf_count)
        {
            metric_base::base_metric::set_base(lane, tile);
            INTEROP_ASSERT(m_raw_cluster_count.size() == raw_count.size());
            INTEROP_ASSERT(m_pf_cluster_count.size() == pf_count.size());
            INTEROP_ASSERT(raw_count.size() == pf_count.size());

            for (size_t x_bin = 0; x_bin < raw_count.size(); ++x_bin)
            {
                m_raw_cluster_count[x_bin].assign(raw_count[x_bin].begin(), raw_count[x_bin].end());
                m_pf_cluster_count[x_bin].assign(pf_count[x_bin].begin(), pf_count[x_bin].end());
            }
        }

        /** @defgroup pf_grid_metric PF grid metric
         *
         * Per tile passed filter grid metrics
         *
         * @ref illumina::interop::model::metrics::pf_grid_metric "See full class description"
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
            INTEROP_ASSERT(x_bin < m_raw_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_raw_cluster_count[x_bin].size());
            return m_raw_cluster_count[x_bin][y_bin];
        }

        /** Return an element of the subtile PF cluster count grid
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @return PF cluster count corresponding to the bin index
         */
        uint32_t pf_cluster_count(const size_t x_bin, const size_t y_bin) const
        {
            INTEROP_ASSERT(x_bin < m_pf_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_pf_cluster_count[x_bin].size());
            return m_pf_cluster_count[x_bin][y_bin];
        }

        /** Return an element of the subtile raw cluster count grid, scaled by (1k pixels)/mm^2
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @param density the area of a pixel in mm^2
         * @return raw cluster density corresponding to the bin index
         */
        float raw_cluster_density_k(const size_t x_bin, const size_t y_bin, const float density) const
        {
            INTEROP_ASSERT(x_bin < m_pf_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_pf_cluster_count[x_bin].size());
            if (density == 0)
                return 0;
            return m_raw_cluster_count[x_bin][y_bin] / density / 1000;
        }

        /** Return an element of the subtile PF cluster count grid, scaled by (1k pixels)/mm^2
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @param density the area of a pixel in mm^2
         * @return PF cluster demsity corresponding to the bin index
         */
        float pf_cluster_density_k(const size_t x_bin, const size_t y_bin, const float density) const
        {
            INTEROP_ASSERT(x_bin < m_pf_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_pf_cluster_count[x_bin].size());
            if (density == 0)
                return 0;
            return m_pf_cluster_count[x_bin][y_bin] / density / 1000;
        }

        /** Return an element of a percent PF subtile grid
         *
         * @param x_bin the x index of the requested spatial bin
         * @param y_bin the y index of the requested spatial bin
         * @return Percent PF corresponding to the bin index
         */
        float percent_pf(const size_t x_bin, const size_t y_bin) const
        {
            INTEROP_ASSERT(x_bin < m_pf_cluster_count.size());
            INTEROP_ASSERT(y_bin < m_pf_cluster_count[x_bin].size());
            return static_cast<float>(m_pf_cluster_count[x_bin][y_bin]) / m_raw_cluster_count[x_bin][y_bin] * 100;
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "PFGrid"; }

    private:
        uint32_vector2d m_raw_cluster_count;
        uint32_vector2d m_pf_cluster_count;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

