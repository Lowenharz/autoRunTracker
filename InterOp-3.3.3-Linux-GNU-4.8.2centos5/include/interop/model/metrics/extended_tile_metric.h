/** Extended tile metric
 *
 * The extended tile metric reports IUO tile metrics such as the occupancy aka number
 * of empty wells on a tile.
 *
 *  @note IUO metric
 *  @file
 *  @date 10/22/15
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include <limits>
#include "interop/model/metric_base/base_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/model/metric_base/point2d.h"
#include "interop/io/layout/base_metric.h"
#include "interop/io/format/generic_layout.h"
#include "interop/model/metrics/tile_metric.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Extended tile metric
     *
     * The extended tile metric reports IUO tile metrics such as the occupancy aka number
     * of empty wells on a tile.
     *
     * @note IUO metric
     * @note Supported versions: 1, 2 and 3
     */
    class extended_tile_metric : public metric_base::base_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::ExtendedTile,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 3
        };
    public:
        /** Constructor
         */
        extended_tile_metric() :
                metric_base::base_metric(0, 0), m_cluster_count_occupied(std::numeric_limits<float>::quiet_NaN())
        {
        }
        /** Constructor
         */
        extended_tile_metric(const header_type&) :
                metric_base::base_metric(0, 0),
                m_cluster_count_occupied(std::numeric_limits<float>::quiet_NaN())
        {
        }
        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param occupied number of occupied wells
         * @param upper_left coordinate of upper left fiducial
         */
        extended_tile_metric(const uint_t lane,
                             const uint_t tile,
                             const float occupied,
                             const point2d& upper_left=point2d()) :
                metric_base::base_metric(lane, tile), m_cluster_count_occupied(occupied), m_upper_left(upper_left)
        {
        }

    public:
        /** Setter
         *
         * @note Version 1 and 2
         * @param lane lane number
         * @param tile tile number
         * @param occupied number of occupied wells
         * @param upper_left coordinate of upper left fiducial
         */
        void set(const uint_t lane,
                 const uint_t tile,
                 const float occupied,
                 const point2d& upper_left=point2d())
        {
            metric_base::base_metric::set_base(lane, tile);
            m_cluster_count_occupied = occupied;
            m_upper_left = upper_left;
        }
        /** @defgroup extended_tile_metric Extended Tile Metrics
         *
         * Per tile occupancy metrics
         *
         * @ref illumina::interop::model::metrics::extended_tile_metric "See full class description"
         * @{
         */
        /** Number of clusters on the tile that are occupied
         *
         * @note Supported by all versions
         * @return number of occupied wells
         */
        float cluster_count_occupied() const
        {
            return m_cluster_count_occupied;
        }

        /** Number of thousands of clusters on the tile that are occupied
         *
         * @note Supported by all versions
         * @return number of occupied wells (in thousands)
         */
        float cluster_count_occupied_k() const
        {
            return m_cluster_count_occupied / 1000;
        }

        /** Percentage of clusters on the tile that are occupied
         *
         * @note Supported by all versions
         * @param cluster_count_k number of total clusters on the tile
         * @return percent of occupied wells
         */
        float percent_occupied(const float cluster_count_k) const
        {
            return (m_cluster_count_occupied / 1000) / cluster_count_k * 100;
        }

        /** Percentage of clusters on the tile that are occupied
         *
         * @note Supported by all versions
         * @param tile_metrics tile metric set
         * @return percent of occupied wells
         */
        float percent_occupied_lookup(const metric_base::metric_set<tile_metric>& tile_metrics) const
        {
            return percent_occupied(tile_metrics.get_metric(id()).cluster_count_k());
        }
        /** Get the coodinate of the upper left fiducial found on the first cycle
         *
         * @note supported in version 3 or later
         * @return upper left
         */
        const point2d& upper_left()const
        {
            return m_upper_left;
        }

        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "ExtendedTile"
         */
        static const char *prefix()
        { return "ExtendedTile"; }

    private:
        float m_cluster_count_occupied;
        point2d m_upper_left;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}


