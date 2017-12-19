/** Distortion curve for each tile
 *
 * The distortion metric contains a set of coefficients that describes the optical distortion for each tile
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 9/14/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <numeric>
#include <algorithm>
#include "interop/model/metric_base/base_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/io/layout/base_metric.h"
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing the distortion curves for each tile
     *
     * @note This is an IUO metric
     */
    class distortion_metric_header : public metric_base::base_metric::header_type
    {
    public:
        /** Constructor
         *
         * @param dimensions shape of the coefficients
         * @param channel_count number of channels
         * @param image_width width of the tile image
         * @param image_height height of the tile image
         * @param type enumerated type indicating the type of distortion model
         */
        distortion_metric_header(const std::vector < size_t > &dimensions,
                                 const size_t channel_count,
                                 const size_t image_width,
                                 const size_t image_height,
                                 const constants::distortion_curve_type type) :
                m_dimensions(dimensions),
                m_image_width(image_width),
                m_image_height(image_height),
                m_channel_count(channel_count),
                m_type(type),
                m_total_size(0)
                ,m_total_coeff(0)
        {update_size();}

        /** Number of channels
         *
         * @return number of channels
         */
        size_t channel_count() const
        { return m_channel_count; }

        /** Number of curves
         *
         * @return number of curves
         */
        size_t curve_count() const
        { return m_dimensions.size(); }

        /** Number of coefficients for each curve
         *
         * @return number of coefficients
         */
        size_t coefficient_count(const size_t dim) const throw(model::index_out_of_bounds_exception)
        {
            if (dim >= m_dimensions.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Dimension out of bounds: "
                        << dim << " > " << m_dimensions.size());
            return m_dimensions[dim];
        }

        /** Get the type of the curve
         *
         * @return type of the curve
         */
        constants::distortion_curve_type type() const
        {
            return m_type;
        }
        /** Get the width of the image
         *
         * @return width of image
         */
        size_t image_width() const
        {
            return m_image_width;
        }
        /** Get the height of the image
         *
         * @return height of image
         */
        size_t image_height() const
        {
            return m_image_height;
        }

        /** Total number of coefficients for all channels and curves
         *
         * @return total number of coefficients
         */
        size_t total_number_of_coefficients() const
        {
            return m_total_size;
        }
        /** Get the offset into the coefficient buffer
         *
         * @param channel channel index
         * @param curve curve index
         * @param coeff coefficient index
         */
        size_t index(const size_t channel, const size_t curve, const size_t coeff) const throw(index_out_of_bounds_exception)
        {
            return begin(channel, curve) + coeff;
        }
        /** Get the start offset for a curve in the coefficient buffer
         *
         * @param channel channel index
         * @param curve curve index
         * @return start offset in coefficient buffer
         */
        size_t begin(const size_t channel, const size_t curve) const throw(index_out_of_bounds_exception)
        {
            if(curve > m_dimensions.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Index out of bounds");
            return channel*m_total_coeff + m_accumulated[curve];
        }
        /** Get the end offset for a curve in the coefficient buffer
         *
         * @param channel channel index
         * @param curve curve index
         * @return end offset in coefficient buffer
         */
        size_t end(const size_t channel, const size_t curve) const throw(index_out_of_bounds_exception)
        {
            if(curve > m_dimensions.size())
                INTEROP_THROW(index_out_of_bounds_exception, "Index out of bounds");
            return begin(channel, curve) + m_dimensions[curve];
        }

        /** Generate a default header
         *
         * @return default header
         */
        static distortion_metric_header default_header()
        {
            return distortion_metric_header(std::vector<size_t>(), 0, 0, 0, constants::UnknownDistortionCurve);
        }

        /** Clear the data
         */
        void clear()
        {
            m_dimensions.clear();
            m_accumulated.clear();
            m_image_width = 0;
            m_image_height = 0;
            m_channel_count=0;
            m_type=constants::UnknownDistortionCurve;
            m_total_size=0;
            m_total_coeff=0;
            metric_base::base_metric::header_type::clear();
        }

    private:
        void update_size()const
        {}
        void update_size()
        {
            m_accumulated.resize(m_dimensions.size(), 0);
            for(size_t i=1;i<m_dimensions.size();++i)
                m_accumulated[i]=m_dimensions[i-1]+m_accumulated[i-1];
            m_total_coeff=std::accumulate(m_dimensions.begin(), m_dimensions.end(), size_t(0));
            m_total_size=m_total_coeff*m_channel_count;
        }

    private:
        std::vector <size_t> m_dimensions;
        std::vector <size_t> m_accumulated;
        size_t m_image_width;
        size_t m_image_height;
        size_t m_channel_count;
        constants::distortion_curve_type m_type;
        size_t m_total_size;
        size_t m_total_coeff;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** Coefficients describing the optical distortion for each tile
     *
     * The distortion coefficients for each tile
     *
     * @note This is an IUO metric
     * @note Supported versions: 1
     */
    class distortion_metric : public metric_base::base_metric
    {
    public:
        /** Define 1D vector of curve coefficients */
        typedef std::vector<float> curve_vector_t;
        /** Distortion metric header */
        typedef distortion_metric_header header_type;
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::OpticalModel,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 1
        };
    public:
        /** Constructor
         */
        distortion_metric() :
                metric_base::base_metric(0, 0)
        {
        }

        /** Constructor
         *
         * @param header metric set header
         */
        distortion_metric(const header_type &header) :
                metric_base::base_metric(0, 0), m_coefficients(header.total_number_of_coefficients(), 0)
        {
        }

        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param coefficients curve coefficients
         */
        template<class Matrix>
        distortion_metric(const uint_t lane,
                          const uint_t tile,
                          const Matrix &coefficients) :
                metric_base::base_metric(lane, tile), m_coefficients(coefficients)
        {
        }

    public:
        /** Setter
         *
         * @param lane lane number
         * @param tile tile number
         * @param coefficients distortion coefficients for every lane/tile/cycle
         */
        template<class Collection>
        void set(const uint_t lane,
                 const uint_t tile,
                 const Collection &coefficients)
        {
            metric_base::base_metric::set_base(lane, tile);
            m_coefficients = coefficients;
        }

    public:
        /** @defgroup distortion_metric Distortion metric
         *
         * Per tile distortion curve
         *
         * @ref illumina::interop::model::metrics::distortion_metric "See full class description"
         * @{
         */
        /** Distortion coefficients
         *
         * @note Supported by all versions
         * @return distortion coefficients
         */
        const curve_vector_t &coefficients() const
        {
            return m_coefficients;
        }
        /** Get coefficient for specific channel, curve, and order
         *
         * @note The header will produce the proper index.
         * @return distortion coefficients
         */
        float coefficient_at(const size_t index) const throw(model::index_out_of_bounds_exception)
        {
            if(index >= m_coefficients.size())
                throw(model::index_out_of_bounds_exception("Coefficient out of bounds"));
            return m_coefficients[index];
        }
        /** Populate a set of coeffcients for a given channel and curve index
         *
         * @param header distortion metric set header
         * @param channel channel for curve
         * @param curve_index specific curve
         * @param coeff buffer for coefficients
         */
        void populate_coefficients_for(const header_type& header,
                                       const size_t channel,
                                       const size_t curve_index,
                                       std::vector<float>& coeff)const
        {
            if(coeff.size() < header.coefficient_count(curve_index))
                coeff.resize(header.coefficient_count(curve_index));
            populate_coefficients_for(header, channel, curve_index, &coeff.front(), coeff.size());
        }
        /** Populate a set of coeffcients for a given channel and curve index
         *
         * @param header distortion metric set header
         * @param channel channel for curve
         * @param curve_index specific curve
         * @param buffer coefficient buffer
         * param n size of coefficient buffer
         */
        void populate_coefficients_for(const header_type& header,
                                       const size_t channel,
                                       const size_t curve_index,
                                       float* buffer,
                                       const size_t /*n*/)const
        {
            std::copy(m_coefficients.begin()+header.begin(channel, curve_index),
                      m_coefficients.begin()+header.end(channel, curve_index),
                      buffer);
        }
        /** Calculate absolute distortion given the image width
         *
         * @param header distortion metric set header
         * @param channel channel for curve
         * @param curve_index specific curve
         * @param image_width width of the image
         * @return absolute distortion
         */
        float absolute_distortion(const header_type& header,
                                  const size_t channel,
                                  const size_t curve_index,
                                  const size_t image_width)const
        {
            const float lhs = evaluate_polynomial(
                    m_coefficients.begin()+header.begin(channel, curve_index),
                    m_coefficients.begin()+header.end(channel, curve_index), image_width/-2.0f);
            const float rhs = evaluate_polynomial(
                    m_coefficients.begin()+header.begin(channel, curve_index),
                    m_coefficients.begin()+header.end(channel, curve_index), image_width/2.0f);
            return std::max(std::abs(lhs), std::abs(rhs));
        }
        /** @} */
    private:
        template<typename I, typename F>
        static F evaluate_polynomial(I coeff_beg, I coeff_end, const F x)
        {
            F eval=0;
            for(;coeff_beg != coeff_end;++coeff_beg)
                eval = eval*x + *coeff_beg;
            eval *= x;
            return eval;
        }

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "OpticalQuality"
         */
        static const char *prefix()
        { return "OpticalModel"; }

    private:
        curve_vector_t m_coefficients;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

