/** Registration metric
 *
 * The registration metric contains both the affine transform as well as the subregion offsets and their corresponding
 * scores.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 8/21/2015
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/util/statistics.h"
#include "interop/io/format/generic_layout.h"
#include "interop/io/layout/base_metric.h"
#include "interop/constants/enums.h"
#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/model/metric_base/point2d.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing a registration metric set
     *
     * @note This is an IUO metric
     */
    class registration_metric_header : public metric_base::base_cycle_metric::header_type
    {
    public:
        /** Unsigned int16_t
         */
        typedef ::uint16_t ushort_t;
        /** Define a vector of points */
        typedef std::vector<point2d> point2d_vector_t;
    public:
        /** Constructor
         *
         * @param channel_count number of color channels
         * @param fiducial_locations locations of each fiducial in a tile image
         * @param fiducial_layout layout of fiducials
         */
        template<class Point2D_T>
        registration_metric_header(const ushort_t channel_count,
                                   const std::vector<Point2D_T>& fiducial_locations,
                                   const constants::layout_type fiducial_layout) :
                m_channel_count(channel_count),
                m_region_count(fiducial_locations.size()),
                m_fiducial_locations(fiducial_locations.begin(), fiducial_locations.end()),
                m_fiducial_layout(fiducial_layout)
        { }
        /** Constructor
         *
         * @param channel_count number of color channels
         * @param fiducial_locations locations of each fiducial in a tile image
         * @param fiducial_layout layout of fiducials
         */
        registration_metric_header(const ushort_t channel_count,
                                   const point2d_vector_t& fiducial_locations,
                                   const constants::layout_type fiducial_layout) :
                m_channel_count(channel_count),
                m_region_count(static_cast<ushort_t>(fiducial_locations.size())),
                m_fiducial_locations(fiducial_locations),
                m_fiducial_layout(fiducial_layout)
        { }
        /** Constructor
         *
         * @param channel_count number of color channels
         * @param subregion_count number of fiducials on the image
         * @param fiducial_layout layout of fiducials
         */
        registration_metric_header(const ushort_t channel_count,
                                   const ushort_t subregion_count,
                                   const constants::layout_type fiducial_layout) :
                m_channel_count(channel_count),
                m_region_count(subregion_count),
                m_fiducial_layout(fiducial_layout)
        { }

        /** Number of channels
         *
         * @return number of channels
         */
        ushort_t channel_count() const
        { return m_channel_count; }

        /** Number of sub regions
         *
         * @return number of sub regions
         */
        ushort_t region_count() const
        { return m_region_count; }
        /** Get the fiducial locations in pixels
         *
         * @note available in version 3 or later
         * @return fiducial locations in pixels
         */
        const point2d_vector_t& fiducial_locations()const
        {
            return m_fiducial_locations;
        }
        /** Get the layout of the fiducials
         *
         * @note available in version 3 or later
         * @return layout type of the fiducials
         */
        constants::layout_type fiducial_layout()const
        {
            return m_fiducial_layout;
        }
        /** Generate a default header
         *
         * @return default header
         */
        static registration_metric_header default_header()
        {
            return registration_metric_header(0, point2d_vector_t(), constants::SquareLayout);
        }
        /** Clear the data
         */
        void clear()
        {
            m_channel_count=0;
            m_region_count=0;
            m_fiducial_layout = constants::SquareLayout;
            m_fiducial_locations.clear();
            metric_base::base_cycle_metric::header_type::clear();
        }

    private:
        ushort_t m_channel_count;
        ushort_t m_region_count;
        point2d_vector_t m_fiducial_locations;// In pixels
        constants::layout_type m_fiducial_layout;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** Registration metric
     *
     * The registration metric contains both the affine transform as well as the subregion offsets and their corresponding
     * scores.
     *
     * @note Supported versions: 1, 2 and 3
     * @note This is an IUO metric
     */
    class registration_metric : public metric_base::base_cycle_metric // TODO create sub region offset class
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::Registration,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 3,
            /** Length of the affine transform (6 elements) */
            AFFINE_LENGTH = 6,
            /** Length of the subregion registration parameters (3 elements) */
            SUBREGION_PARAM_LENGTH = 3
        };
        /** Registration metric header
         */
        typedef registration_metric_header header_type;
        /** Vector of floats
         */
        typedef std::vector<float> float_vector;
        /** Vector of float vectors
         */
        typedef std::vector<std::vector<float> > float_vector2d;
    public:
        /** Constructor
         */
        registration_metric(const size_t channel_count = 0, const size_t subregion_count = 0) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_affine_transform(channel_count * AFFINE_LENGTH),
                m_sub_tile_offsets(channel_count * subregion_count * SUBREGION_PARAM_LENGTH),
                m_predicted_error(channel_count * subregion_count*2, std::numeric_limits<float>::quiet_NaN()),
                m_sub_region_count(static_cast<ushort_t>(subregion_count)),
                m_theta_z(channel_count, std::numeric_limits<float>::quiet_NaN()),
                m_theta(channel_count, std::numeric_limits<float>::quiet_NaN()),
                m_shear(channel_count, std::numeric_limits<float>::quiet_NaN())
        { }
        /** Constructor
         *
         * @param header metric set header
         */
        registration_metric(const header_type& header) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_affine_transform(header.channel_count() * AFFINE_LENGTH),
                m_sub_tile_offsets(header.channel_count() * header.region_count() * SUBREGION_PARAM_LENGTH),
                m_predicted_error(header.channel_count() * header.region_count() * 2, std::numeric_limits<float>::quiet_NaN()),
                m_sub_region_count(header.region_count()),
                m_theta_z(header.channel_count(), std::numeric_limits<float>::quiet_NaN()),
                m_theta(header.channel_count(), std::numeric_limits<float>::quiet_NaN()),
                m_shear(header.channel_count(), std::numeric_limits<float>::quiet_NaN())
        { }

        /** Constructor
         *
         * @note Version 1
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param sub_region_count number of subregions
         * @param affine affine transform for each channel
         * @param offsets subregion offsets and scores for each region in each channel
         */
        template<class FloatVector>
        registration_metric(const uint_t lane,
                            const uint_t tile,
                            const uint_t cycle,
                            const ushort_t sub_region_count,
                            const FloatVector &affine,
                            const FloatVector &offsets) :
                metric_base::base_cycle_metric(lane, tile, cycle),
                m_affine_transform(affine),
                m_sub_tile_offsets(offsets),
                m_predicted_error(offsets.size()/SUBREGION_PARAM_LENGTH*2, std::numeric_limits<float>::quiet_NaN()),
                m_sub_region_count(sub_region_count),
                m_theta_z(channel_count(), std::numeric_limits<float>::quiet_NaN()),
                m_theta(channel_count(), std::numeric_limits<float>::quiet_NaN()),
                m_shear(channel_count(), std::numeric_limits<float>::quiet_NaN())
        {
        }

    public:
        /** Setter
         *
         * @note Version 1
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param affine_matrices affine transform for each channel
         * @param sub_region_offsets subregion offsets and scores for each region in each channel
         */
        template<class AffineMatrix, class OffsetVector>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const AffineMatrix &affine_matrices,
                 const OffsetVector &sub_region_offsets)
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            INTEROP_ASSERT(m_affine_transform.size() >= affine_matrices.size());
            INTEROP_ASSERT(m_sub_tile_offsets.size() >= sub_region_offsets.size());

            INTEROP_ASSERT(m_affine_transform.size() == affine_matrices.size() * AFFINE_LENGTH);
            for (size_t channel = 0; channel < affine_matrices.size(); channel++)
            {
                m_affine_transform[channel * AFFINE_LENGTH + 0] = static_cast<float>(affine_matrices[channel][6]);
                m_affine_transform[channel * AFFINE_LENGTH + 1] = static_cast<float>(affine_matrices[channel][7]);
                m_affine_transform[channel * AFFINE_LENGTH + 2] = static_cast<float>(affine_matrices[channel][0] - 1);
                m_affine_transform[channel * AFFINE_LENGTH + 3] = static_cast<float>(affine_matrices[channel][4] - 1);
                m_affine_transform[channel * AFFINE_LENGTH + 4] = static_cast<float>(affine_matrices[channel][1]);
                m_affine_transform[channel * AFFINE_LENGTH + 5] = static_cast<float>(affine_matrices[channel][3]);
                INTEROP_ASSERT(m_sub_tile_offsets.size() == SUBREGION_PARAM_LENGTH * sub_region_offsets.size() * sub_region_offsets[channel].size());
                for (size_t region = 0; region < sub_region_offsets[channel].size(); region++)
                {
                    m_sub_tile_offsets[channel * m_sub_region_count * SUBREGION_PARAM_LENGTH + region * SUBREGION_PARAM_LENGTH + 0] = sub_region_offsets[channel][region].dx;
                    m_sub_tile_offsets[channel * m_sub_region_count * SUBREGION_PARAM_LENGTH + region * SUBREGION_PARAM_LENGTH + 1] = sub_region_offsets[channel][region].dy;
                    m_sub_tile_offsets[channel * m_sub_region_count * SUBREGION_PARAM_LENGTH + region * SUBREGION_PARAM_LENGTH + 2] = sub_region_offsets[channel][region].score;
                }
                m_sub_region_count = sub_region_offsets[channel].size();
            }
        }

    public:
        /** @defgroup registration_metric Registration metric
         *
         * Per tile per cycle rigid registration metrics
         *
         * @ref illumina::interop::model::metrics::registration_metric "See full class description"
         * @{
         */

        /** Return an element of the 6 value affine transform for a given
         * channel.
         *
         * @param channel target image channel
         * @param n element of affine transforms
         * @return value of affine transform
         */
        float affine_transform(const size_t channel, const size_t n) const
        {
            INTEROP_ASSERT(channel < m_affine_transform.size());
            INTEROP_ASSERT(n < AFFINE_LENGTH);
            return m_affine_transform[channel * AFFINE_LENGTH + n];
        }

        /** Return the affine transforms across all channels
         *
         * @return value of affine transforms
         */
        const float_vector& affine_transform() const
        {
            return m_affine_transform;
        }

        /** Return the error of the registration for each subregion in each channel
         *
         * @return predicted error vector
         */
        const float_vector& predicted_error() const
        {
            return m_predicted_error;
        }

        /** Return an element of the subregion registration parameters, which include
         * offsets (dx, dy) and the score.
         *
         * These offets are used to build the affine transform, so there must be at
         * least 3.
         *
         * @param channel target image channel
         * @param region select one of 3 or more regions.
         * @param n element of subregion offset
         * @return value of registration parameters
         */
        float sub_tile_offsets(const size_t channel, const size_t region, const size_t n) const
        {
            INTEROP_ASSERT(channel < m_sub_tile_offsets.size());
            INTEROP_ASSERT(region < static_cast<size_t>(m_sub_region_count * SUBREGION_PARAM_LENGTH));
            return m_sub_tile_offsets[channel * SUBREGION_PARAM_LENGTH * m_sub_region_count
                                      + region * SUBREGION_PARAM_LENGTH + n];
        }

        /** Return the subregion registration parameters, which include offsets (dx, dy) and the score.
         *
         * These offets are used to build the affine transform, so there must be at
         * least 3.
         *
         * @return value of subtile offset parameters
         */
        const float_vector& sub_tile_offsets() const
        {
            return m_sub_tile_offsets;
        }

        /** Number of channels
         *
         * This is usually 2 or 4.
         *
         * @return number of channels
         */
        size_t channel_count() const
        { return m_affine_transform.size() / AFFINE_LENGTH; }

        /** Number of subregions
         *
         * This is usually 3 or more.
         *
         * @return number of subregions
         */
        size_t sub_region_count() const
        { return m_sub_region_count; }

        /** Set predicted error at given index
         *
         * @param index destination index
         * @param err error value
         */
        void set_predicted_error(const size_t index, const float err)
        {
            INTEROP_ASSERTMSG(index < m_predicted_error.size(), index << " < " << m_predicted_error.size() << " - " << m_sub_region_count << " - " << channel_count());
            m_predicted_error[index] = err;
            INTEROP_ASSERTMSG(std::isnan(err) || std::abs(err) < 1000, err << " -> " << lane() << "_" << tile() << " @ " << cycle());
        }

        /** Calculate the maximum residual for each channel
         *
         * @return vector of maximum residual radial errors for each channel
         */
        std::vector<float> max_residual_radial_errors()const
        {
            std::vector<float> errors(channel_count());
            for(size_t channel=0;channel < channel_count();++channel)
                errors[channel] = max_residual_radial_error(channel);
            return errors;
        }

        /** Calculate the maximum residual radial error for the lane/tile/cycle
         *
         * @return maximum residual radial error over both channels
         */
        float max_residual_radial_error()const
        {
            float max_residual = -1;
            for(size_t channel=0;channel < channel_count();++channel)
                max_residual = std::max(max_residual, max_residual_radial_error(channel));
            if(max_residual == -1) return std::numeric_limits<float>::quiet_NaN();
            return max_residual;
        }

        /** Calculate the maximum residual radial error for the lane/tile/cycle
         *
         * @param channel channel index
         * @return maximum residual radial error
         */
        float max_residual_radial_error(const size_t channel)const
        {
            const float x = max_residual_x_error(channel);
            const float y = max_residual_y_error(channel);
            return std::sqrt(x*x+y*y);
        }

        /** Calculate the maximum residual error in x for the lane/tile/cycle
         *
         * @param channel channel index
         * @return maximum residual error in x
         */
        float max_residual_x_error(const size_t channel)const
        {
            return mean_error(channel, 0);
        }

        /** Calculate the maximum residual error in y for the lane/tile/cycle
         *
         * @param channel channel index
         * @return maximum residual error in y
         */
        float max_residual_y_error(const size_t channel)const
        {
            return mean_error(channel, 1);
        }
        /** Get the shearing term of the affine transform
         *
         * @note This is averaged over both channels
         * @param channel channel index
         * @return shear
         */
        float shear(const size_t channel)const throw(index_out_of_bounds_exception)
        {
            if( channel >= m_shear.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Channel index exceeds channel count");
            return m_shear[channel];
        }
        /** Get the angle of rotation around an outside axis (Z)
         *
         * This metric is derived from the shearing term of the  affine transform and measures target rotation.
         *
         * @note This is averaged over both channels
         * @param channel channel index
         * @return rotation around z-axis
         */
        float theta_z(const size_t channel)const throw(index_out_of_bounds_exception)
        {
            if( channel >= m_theta_z.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Channel index exceeds channel count");
            return m_theta_z[channel];
        }
        /** Get the angle of rotation
         *
         * This metric is derived from the shearing term of the affine transform and measures angle of rotation.
         *
         * @note This is averaged over both channels
         * @param channel channel index
         * @return rotation
         */
        float theta(const size_t channel)const throw(index_out_of_bounds_exception)
        {
            if( channel >= m_theta.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Channel index exceeds channel count");
            return m_theta[channel];
        }
        /** Set the rotation angles
         *
         * @note This is averaged over both channels
         * @param channel channel index
         * @param theta angle of rotation
         * @param shear shear term of affine transform
         * @param theta_z angle of rotation around z-axis
         */
        void set_rotation(const size_t channel, const float theta, const float shear, const float theta_z) throw(index_out_of_bounds_exception)
        {
            if(channel >= m_theta.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Channel index exceeds channel count");
            m_theta[channel] = theta;
            m_theta_z[channel] = theta_z;
            m_shear[channel] = shear;
        }

        /** Determine if any channel failed registration for the lane/tile/cycle
         *
         * @return true if any channel failed registration for the lane/tile/cycle
         */
        bool is_any_channel_registration_failure() const
        {
            const float kRegistrationFailureSentinel = -1000;
            for(size_t channel = 0; channel < channel_count(); ++channel)
            {
                //TODO: come up with a better threshold
                if(affine_transform(channel, 0) < kRegistrationFailureSentinel)
                    return true;
            }
            return false;
        }
        /** @} */

    private:
        float mean_error(const size_t channel, size_t dim)const
        {
            const size_t offset = channel*2*m_sub_region_count;
            float max_error = 0;
            size_t error_count = 0;
            for(size_t subregion_index=offset+dim, count=offset+m_sub_region_count;subregion_index<count;subregion_index+=2)
            {
                if(std::isnan(m_predicted_error[subregion_index])) continue;
                max_error += std::abs(m_predicted_error[subregion_index]);
                error_count++;
            }
            if(error_count == 0) return std::numeric_limits<float>::quiet_NaN();
            return max_error/error_count;
        }

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "Registration"; }

    private:
        float_vector m_affine_transform;
        float_vector m_sub_tile_offsets;
        float_vector m_predicted_error;
        size_t m_sub_region_count;

    private:
        float_vector m_theta_z;
        float_vector m_theta;
        float_vector m_shear;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}


