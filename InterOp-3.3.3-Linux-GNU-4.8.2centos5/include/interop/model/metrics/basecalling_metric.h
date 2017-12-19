/** Basecalling metric
 *
 * The basecalling metric contains the centroids of each base cluster learned for each tile and cycle.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 12/15/15.
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/model/metric_base/point2d.h"
#include "interop/io/layout/base_metric.h"
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{

    /** Header information for a basecalling metric file
     *
     * @note This is an IUO metric
     */
    class basecalling_metric_header : public metric_base::base_cycle_metric::header_type
    {
    public:
        /** Attribute level */
        enum info_type {CENTROIDS=0, COVARIANCES=0x01, WEIGHTS=0x02, DETERMINANT=0x04};
    public:
        /** Constructor
         */
        basecalling_metric_header(const uint8_t info_level) : m_info_level(info_level)
        { }
        /** Information level in model
         *
         * @return information level
         */
        uint8_t info_level()const
        {
            return m_info_level;
        }
        /** Whether the format contains the covariances
         *
         * @return true if the model has the covariances
         */
        bool has_covariances() const
        { return (m_info_level&COVARIANCES) == COVARIANCES; }
        /** Whether the format contains the cloud weights
         *
         * @return true if the model has the cloud weights
         */
        bool has_weights() const
        { return (m_info_level& WEIGHTS) == WEIGHTS; }
        /** Whether the format contains the covariance determinant
         *
         * @return true if the model has the covariance determinant
         */
        bool has_determinant() const
        { return (m_info_level& DETERMINANT) == DETERMINANT; }
        /** Clear the data
         */
        void clear()
        {
            m_info_level=CENTROIDS;
            metric_base::base_cycle_metric::header_type::clear();
        }
        /** Generate a default header
         *
         * @return default header
         */
        static basecalling_metric_header default_header()
        {
            return basecalling_metric_header(CENTROIDS);
        }

    private:
        uint8_t m_info_level;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** BaseCalling metric
     *
     * The basecalling metric contains the centroids of each base cluster learned for each tile and cycle.
     *
     * @note This is an IUO metric
     * @note Supported versions: 1,2
     */
    class basecalling_metric : public metric_base::base_cycle_metric
    {
    public:
        /** Define a point 2D type */
        typedef point2d point2d_t;
        /** Vector of 2d points */
        typedef std::vector<point2d_t> point2d_vector;
        /** Vector of floats points */
        typedef std::vector<float> float_vector;
        /** Basecalling metricset header */
        typedef basecalling_metric_header header_type;
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::BaseCalling,
            /** Number of channels */
            DIM = 2,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 3
        };
    public:
        /** Constructor
         */
        basecalling_metric() :
                metric_base::base_cycle_metric(0, 0, 0),
                m_centroids(constants::NUM_OF_BASES * DIM, std::numeric_limits<float>::quiet_NaN())
        {
        }
        /** Constructor
         *
         * @param header metric set header
         */
        basecalling_metric(const header_type& header) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_centroids(constants::NUM_OF_BASES * DIM, std::numeric_limits<float>::quiet_NaN()),
                m_covariances(header.has_covariances() ?
                              constants::NUM_OF_BASES*DIM*DIM :
                              0,
                              std::numeric_limits<float>::quiet_NaN()),
                m_weights(header.has_weights() ?
                              constants::NUM_OF_BASES :
                              0,
                              std::numeric_limits<float>::quiet_NaN()),
                m_mean_determinant(std::numeric_limits<float>::quiet_NaN())
        {
        }

        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param centroids 2d point for each of the 4 base clouds
         * @param covariances covariances for the clouds
         * @param weights weights for the clouds
         * @param mean_determinant mean determinant for the clouds
         */
        basecalling_metric(const uint_t lane,
                           const uint_t tile,
                           const uint_t cycle,
                           const float_vector &centroids,
                           const float_vector &covariances=float_vector(),
                           const float_vector &weights=float_vector(),
                           const float mean_determinant=std::numeric_limits<float>::quiet_NaN()) :
                metric_base::base_cycle_metric(lane, tile, cycle),
                m_centroids(centroids),
                m_covariances(covariances),
                m_weights(weights),
                m_mean_determinant(mean_determinant)
        {
            INTEROP_ASSERT(m_centroids.size() == constants::NUM_OF_BASES * DIM);
        }

    public:
        /** Setter
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param centroids 2d point for each of the 4 base clouds
         * @param covariances covariances for the clouds
         * @param weights weights for the clouds
         * @param mean_determinant mean determinant for the clouds
         */
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const point2d_vector &centroids,
                 const float_vector& covariances=float_vector(),
                 const float_vector& weights=float_vector(),
                 const float mean_determinant=std::numeric_limits<float>::quiet_NaN())
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            INTEROP_ASSERT(m_centroids.size() == constants::NUM_OF_BASES * DIM);
            INTEROP_ASSERT(centroids.size() == constants::NUM_OF_BASES);
            for(size_t centroid_index = 0, float_index = 0; centroid_index < constants::NUM_OF_BASES; ++centroid_index)
            {
                m_centroids[float_index++] = centroids[centroid_index].x();
                m_centroids[float_index++] = centroids[centroid_index].y();
            }
            m_covariances = covariances;
            m_weights = weights;
            m_mean_determinant = mean_determinant;
        }

    public:
        /** @defgroup basecalling_metric Basecalling Metrics
         *
         * Per tile per cycle gaussian centroids
         *
         * @ref illumina::interop::model::metrics::basecalling_metric "See full class description"
         * @{
         */
        /** Gaussian center centroids
         *
         * Centroids found by the Gaussian Mixture model in 2-dye base calling
         *
         * Elements: X,Y
         * Order: A,C,G,T
         * Layout: Ax,Ay,Cx,Cy,Gx,Gy,Tx,Ty
         *
         * @note Supported by all versions
         * @return gaussian center centroids
         */
        const float_vector &centroids() const
        {
            return m_centroids;
        }
        /** Gaussian covariances
         *
         * Covariances found by the Gaussian Mixture model in 2-dye base calling
         *
         * Order: A,C,G,T
         * Layout: Axx,Axy,Ayx,Ayy, etc.
         *
         * @note Supported by v3 or later
         * @return gaussian center centroids
         */
        const float_vector &covariances() const
        {
            return m_covariances;
        }
        /** Gaussian cloud weights
         *
         * Weights on the clouds found by the Gaussian Mixture model in 2-dye base calling
         *
         * Order: A,C,G,T
         *
         * @note Supported by v3 or later
         * @return gaussian center centroids
         */
        const float_vector &weights() const
        {
            return m_weights;
        }
        /** Mean determinant of Gaussian clouds
         *
         *
         * @note Supported by v3 or later
         * @return mean determinant
         */
        float mean_determinant() const
        {
            return m_mean_determinant;
        }
        /** Radial distance of centroid from origin
         *
         * Centroids found by the Gaussian Mixture model in 2-dye base calling
         *
         * Order: A,C,G,T
         *
         * @note Supported by all versions
         * @param base_index index of base
         * @return radial distance of centroid
         */
        float radius(const size_t base_index) const
        {
            return std::sqrt(m_centroids[base_index*DIM + 0]*m_centroids[base_index*DIM + 0] +
                    m_centroids[base_index*DIM + 1]*m_centroids[base_index*DIM + 1]);
        }
        /** Area inside a 4-point polygon
         *
         * Derived from centroids found by the Gaussian Mixture model in 2-dye base calling
         *
         * Shoelace formula: https://en.wikipedia.org/wiki/Shoelace_formula
         *
         * @note Supported by all versions
         * @return area inside polygon
         */
        float area() const
        {
            const size_t x = 0;
            const size_t y = 1;

            const size_t A = 0*DIM;
            const size_t C = 1*DIM;
            const size_t G = 2*DIM;
            const size_t T = 3*DIM;
            const float area1 = m_centroids[A + x]*m_centroids[C + y] - m_centroids[A + y]*m_centroids[C + x];
            const float area2 = m_centroids[C + x]*m_centroids[G + y] - m_centroids[C + y]*m_centroids[G + x];
            const float area3 = m_centroids[G + x]*m_centroids[T + y] - m_centroids[G + y]*m_centroids[T + x];
            const float area4 = m_centroids[T + x]*m_centroids[A + y] - m_centroids[T + y]*m_centroids[A + x];
            return std::abs(area1 + area2 + area3 + area4) / 2.0f;
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "Basecalling"
         */
        static const char *prefix()
        { return "Basecalling"; }

    private:
        float_vector m_centroids;
        float_vector m_covariances;
        float_vector m_weights;
        float m_mean_determinant;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

