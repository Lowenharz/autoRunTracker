/** Static run metric
 *
 * The static run metric contains information on distortion values against x-position.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 07/08/2016
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/io/format/generic_layout.h"
#include "interop/io/layout/base_metric.h"
#include "interop/model/metric_base/base_static_run_metric.h"
#include "interop/model/metric_base/metric_set.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing a static run metric set
     *
     * @note This is an IUO metric
     */
    class static_run_metric_header : public metric_base::base_static_run_metric::header_type
    {
    public:
        /** Unsigned int32_t type */
        typedef ::uint32_t uint_t;

    public:
        /** Constructor
         *
         * @param curve_length curve length -> corresponds to length of the x-array
         * @param curve_check curve check -> corresponds to length of the y-array
         */
        static_run_metric_header(const uint_t curve_length, const uint_t curve_check) :
                m_curve_length(curve_length), m_curve_check(curve_check)
        { }

        /** Curve length
         *
         * @return curve length
         */
        uint_t curve_length() const
        { return m_curve_length; }

        /** Curve check
         *
         * @return curve check
         */
        uint_t curve_check() const
        { return m_curve_check; }

        /** Default header for static_run_metric_header */
        static static_run_metric_header default_header()
        {
            return static_run_metric_header(0, 0);
        }
        /** Clear the data
         */
        void clear()
        {
            m_curve_length=0;
            m_curve_check=0;
            metric_base::base_static_run_metric::header_type::clear();
        }

    private:
        uint_t m_curve_length;
        uint_t m_curve_check;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** Static run metric
     *
     * The static run metric contains distortion values by camera, channel
     * and distortion_type.
     *
     * @note Supported versions: 1
     * @note This is an IUO metric
     */
    class static_run_metric : public metric_base::base_static_run_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
                    TYPE = constants::StaticRun,
            /** Latest version of the InterOp format */
                    LATEST_VERSION = 1
        };

        /** Static run metric header */
        typedef static_run_metric_header header_type;

        /** Vector of floats */
        typedef std::vector<float> float_vector;

        /** ubyte_t type */
        typedef uint8_t ubyte_t;

        /** ushort_t type */
        typedef uint16_t ushort_t;

        /** uint_t type */
        typedef uint32_t uint_t;

    public:
        /** Constructor */
        static_run_metric() :
                base_static_run_metric(0,0,0), m_x_values(0), m_y_values(0)
        { }
        /** Constructor */
        static_run_metric(const header_type& header) :
                base_static_run_metric(0,0,0),
                m_x_values(header.curve_length()),
                m_y_values(header.curve_check())
        { }

        /** Constructor
         *
         * @note Version 1
         * @param camera camera
         * @param channel channel
         * @param distortion_type distortion type
         * @param x_values float vector of the x-values
         * @param y_values float vector of the y-values
         */
        static_run_metric(const ubyte_t camera,
                      const ubyte_t channel,
                      const ushort_t distortion_type,
                      const float_vector &x_values,
                      const float_vector &y_values) :
                base_static_run_metric(camera, channel, distortion_type),
                m_x_values(x_values), m_y_values(y_values)
        {}

        /** Constructor
         *
         * @note Version 1
         * @param curve_length dimension of the x-axis
         * @param curve_check dimension of the y-axis
         */
        static_run_metric(const size_t curve_length,
                      const size_t curve_check) :
                base_static_run_metric(0, 0, 0),
                m_x_values(curve_length),
                m_y_values(curve_check)
        {}

    public:
        /** Setter
        *
        * @note Version 1
        * @param camera ubyte_t camera
        * @param channel ubyte_t channel
        * @param distortion_type ushort_t distortion_type
        * @param x_values X_Values_Vector x_values
        * @param y_values Y_Values_Vector y_values
        */
        template<class X_Values_Vector, class Y_Values_Vector>
        void set(const ubyte_t camera, const ubyte_t channel, const ushort_t distortion_type,
                 const X_Values_Vector &x_values,
                 const Y_Values_Vector &y_values)
        {
            metric_base::base_static_run_metric::set_base(camera, channel, distortion_type);
            m_x_values = x_values;
            m_y_values = y_values;
        }

        /** @defgroup static_run_metric Run distortion metric
         *
         * Per run distortion metrics
         *
         * @ref illumina::interop::model::metrics::static_run_metric "See full class description"
         * @{
         */

        /** Return an element of x_values
         *
         *  @param curve_length parameter for the x-dimension
         */
        float x_values(const size_t curve_length) const
        {
            if(curve_length >= m_x_values.size())
                INTEROP_THROW(index_out_of_bounds_exception, "curve length out of bounds ");
            INTEROP_ASSERT(curve_length < m_x_values.size());
            return m_x_values[curve_length];
        }

        /** Return an element of y_values
         *
         *  @param curve_check parameter for the y-dimension
         */
        float y_values(const size_t curve_check) const
        {
            if(curve_check >= m_y_values.size())
                INTEROP_THROW(index_out_of_bounds_exception, "curve check out of bounds ");
            INTEROP_ASSERT(curve_check < m_y_values.size());
            return m_y_values[curve_check];
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "StaticRun"; }

    private:
        float_vector m_x_values;
        float_vector m_y_values;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

