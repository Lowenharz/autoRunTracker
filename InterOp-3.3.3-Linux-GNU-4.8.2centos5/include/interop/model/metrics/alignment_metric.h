/** Alignment metric
 *
 * The alignment metric contains the 4x4 confusion matrix of basecalls for every lane/tile/cycle aligned.
 *
 *  @note This is an IUO metric
 *  @file
 *  @date 6/14/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <cstring>
#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/model/metric_base/metric_set.h"
#include "interop/io/layout/base_metric.h"
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{

    /** Alignment metric
     *
     * The alignment metric contains the 4x4 confusion matrix of basecalls for every lane/tile/cycle aligned.
     *
     * @note This is an IUO metric
     * @note Supported versions: 1, 2
     */
    class alignment_metric : public metric_base::base_cycle_metric
    {
    public:
        /** Define called count type */
        typedef ::uint32_t call_count_t;
        /** Define 1D vector of called counts */
        typedef std::vector<call_count_t> confusion_matrix_t;
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::Alignment,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };
    public:
        /** Constructor
         */
        alignment_metric() :
                metric_base::base_cycle_metric(0, 0, 0),
                m_confusion_matrix(static_cast<size_t>(constants::NUM_OF_BASES * constants::NUM_OF_BASES), 0)
        {
        }
        /** Constructor
         */
        alignment_metric(const header_type&) :
                metric_base::base_cycle_metric(0, 0, 0),
                m_confusion_matrix(static_cast<size_t>(constants::NUM_OF_BASES * constants::NUM_OF_BASES), 0)
        {
        }

        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param confusion_matrix 4x4 confusion matrix of basecalls for every lane/tile/cycle aligned
         */
        template<class Matrix>
        alignment_metric(const uint_t lane,
                         const uint_t tile,
                         const uint_t cycle,
                         const Matrix &confusion_matrix) :
                metric_base::base_cycle_metric(lane, tile, cycle), m_confusion_matrix(confusion_matrix)
        {
            INTEROP_ASSERT(m_confusion_matrix.size() == constants::NUM_OF_BASES * constants::NUM_OF_BASES);
        }

    public:
        /** Setter
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param confusion_matrix 4x4 confusion matrix of basecalls for every lane/tile/cycle aligned
         */
        template<class Matrix>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const Matrix &confusion_matrix)
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            m_confusion_matrix = confusion_matrix;
        }
        /** Setter
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param confusion_matrix_beg iterator to start of 4x4 confusion matrix
         * @param confusion_matrix_end iterator to end of 4x4 confusion matrix
         */
        template<class ValueIterator>
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 ValueIterator confusion_matrix_beg,
                 ValueIterator confusion_matrix_end)
        {
            metric_base::base_cycle_metric::set_base(lane, tile, cycle);
            m_confusion_matrix.assign(confusion_matrix_beg, confusion_matrix_end);
        }

    public:
        /** @defgroup alignment_metric Alignment Metrics
         *
         * Per tile per cycle error rate confusion matrix
         *
         * @ref illumina::interop::model::metrics::alignment_metric "See full class description"
         * @{
         */
        /** Confusion matrix
         *
         * Confusion matrix returned by the PhiX aligner of true reference sequence to basecalls
         *
         * Order: A,C,G,T
         *
         * @note Supported by all versions
         * @return confusion matrix
         */
        const confusion_matrix_t &confusion_matrix() const
        {
            return m_confusion_matrix;
        }
        /** Get number of rows in buffer
         *
         * @return row count
         */
        size_t row_count()const
        {
            return constants::NUM_OF_BASES;
        }
        /** Get number of column in buffer
         *
         * @return column count
         */
        size_t column_count()const
        {
            return constants::NUM_OF_BASES;
        }
        /** Get total number of cells in the matrix
         *
         * @return number of cells
         */
        size_t total_count()const
        {
            return row_count()*column_count();
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "Alignment"
         */
        static const char *prefix()
        { return "Alignment"; }

    private:
        confusion_matrix_t m_confusion_matrix;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

