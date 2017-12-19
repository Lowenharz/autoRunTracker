/** Color matrix metric
 *
 * The color matrix metric contains elements of the color correction/normalization matrix for every 4-channel lane/tile/cycle.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 9/2/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/io/layout/base_metric.h"
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Header information for writing a color matrix metric set
     *
     * @note This is an IUO metric
     */
    class color_matrix_metric_header : public metric_base::base_cycle_metric::header_type
    {
    public:
        /** Unsigned 16-bit integer used for record counts
         */
        typedef ::uint16_t ushort_t;
    public:
        /** Constructor
         *
         * @param number_of_entries number of entries
         */
        color_matrix_metric_header(const ushort_t number_of_entries) :
                m_number_of_entries(number_of_entries)
        { }

        /** Number of entries
         *
         * @return number of entries
         */
        ushort_t number_of_entries() const
        { return m_number_of_entries; }

        /** Generate a default header
         *
         * @return default header
         */
        static color_matrix_metric_header default_header()
        {
            return color_matrix_metric_header(0);
        }
        /** Clear the data
         */
        void clear()
        {
            m_number_of_entries=0;
            metric_base::base_cycle_metric::header_type::clear();
        }


    private:
        ushort_t m_number_of_entries;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };

    /** Color matrix metric
     *
     * The color matrix metric contains elements of the color correction/normalization matrix for every 4-channel lane/tile/cycle.
     *
     * @note This is an IUO metric
     * @note Supported versions: 1
     */
    class color_matrix_metric : public metric_base::base_cycle_metric
    {
    public:
        /** Define color matrix type */
        typedef float color_matrix_element_t;
        /** Define 1D vector of color matrix elements */
        typedef std::vector<color_matrix_element_t> color_matrix_t;
        /** color matrix metric header */
        typedef color_matrix_metric_header header_type;
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::ColorMatrix,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };
    public:
        /** Constructor
         */
        color_matrix_metric() :
                metric_base::base_cycle_metric(0, 0, 0),
                m_color_matrix()
        {
        }

        /** Constructor
         *
         * @param header metric set header
         */
        color_matrix_metric(const header_type& header) :
                metric_base::base_cycle_metric(0, 0, 0), m_color_matrix(header.number_of_entries(), 0)
        {
        }

        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param color_matrix color matrix of basecalls for every lane/tile/cycle
         */
        template<class Matrix>
        color_matrix_metric(const uint_t lane,
                         const uint_t tile,
                         const uint_t cycle,
                         const Matrix &color_matrix) :
                metric_base::base_cycle_metric(lane, tile, cycle), m_color_matrix(color_matrix)
        {
        }

    public:
        /** Setter
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param color_matrix color matrix for every lane/tile/cycle
         */
        template<class Matrix>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const Matrix &color_matrix)
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            m_color_matrix = color_matrix;
        }

    public:
        /** @defgroup color_matrix_metric Color Matrix Metrics
         *
         * Per tile per cycle color matrix
         *
         * @ref illumina::interop::model::metrics::color_matrix_metric "See full class description"
         * @{
         */
        /** Color matrix
         *
         * Order depends on channel order in RunInfo.xml
         *
         * @note Supported by all versions
         * @return color matrix
         */
        const color_matrix_t &color_matrix() const
        {
            return m_color_matrix;
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "ColorMatrix"
         */
        static const char *prefix()
        { return "ColorMatrix"; }

    private:
        color_matrix_t m_color_matrix;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

