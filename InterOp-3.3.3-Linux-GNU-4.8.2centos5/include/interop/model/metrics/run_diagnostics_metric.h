/** Run diagnostics metric
 *
 * The run diagnostics metric contains the metrics used in the run diagnostics tables and plots
 *
 *  @note This is an IUO metric
 *  @note This is not actually an InterOp written to disk, but is calculated from various InterOp files
 *  @file
 *  @date 10/22/15.
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <vector>
#include "interop/constants/enums.h"
#include "interop/model/metric_base/base_cycle_metric.h"
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Run diagnostics metric
     *
     * The run diagnostics metric contains various binary metrics on run state
     *
     * @note This is an IUO metric
     * @note Supported versions: 1
     */
    class run_diagnostics_metric : public metric_base::base_cycle_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::RunDiagnostics,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 1
        };
        /** Vector of floats
         */
        typedef std::vector<uint_t> uint_vector;

    public:
        /** Constructor
         */
        run_diagnostics_metric() :
                metric_base::base_cycle_metric(0, 0, 0), m_issues(constants::RunDiagnosticsIssueCount, 0)
        {
        }
        /** Constructor
         */
        run_diagnostics_metric(const uint_t lane, const uint_t tile, const uint_t cycle) :
                metric_base::base_cycle_metric(lane, tile, cycle), m_issues(constants::RunDiagnosticsIssueCount, 0)
        {
        }
        /** Constructor
         */
        run_diagnostics_metric(const header_type&) :
                metric_base::base_cycle_metric(0, 0, 0), m_issues(constants::RunDiagnosticsIssueCount, 0)
        {
        }


    public:
        /** @defgroup run_diagnostics Run Diagnostics Metrics
         *
         * Per tile per cycle binary events
         *
         * @ref illumina::interop::model::metrics::run_diagnostics_metric "See full class description"
         * @{
         */
        /** Flag indicating if at least one image is blank
         *
         * @param flag true if the at least one image is blank
         */
        void blank_image(const bool flag)
        {
            m_issues[constants::BlankImage] = flag;
        }

        /** Flag indicating if the tile has no raw or passing filter clusters
         *
         * @param flag true if the tile has no raw or passing filter clusters
         */
        void dead_tile(const bool flag)
        {
            m_issues[constants::DeadTile] = flag;
        }

        /** Flag indicating if the lane/tile/cycle will not contribute to the final yield
         *
         * @param flag true if the lane/tile/cycle will not contribute to the final yield
         */
        void failed_tile_cycle(const bool flag)
        {
            m_issues[constants::FailedCycle] = flag;
        }

        /** Flag indicating if the tile/cycle is an outlier relative to other tiles on the same lane with respect to Q-scores
         *
         * @param flag true if the tile/cycle is an outlier relative to other tiles on the same lane with respect to Q-scores
         */
        void q_outlier(const bool flag)
        {
            m_issues[constants::QOutliers] = flag;
        }

        /** Returns the array of all issues for the lane/tile/cycle
         *
         * @return the array of all issues for the lane/tile/cycle
         */
        const uint_vector& get_issues_for_entry() const
        {
            return m_issues;
        }

        /** Returns the array of all issues for the lane/tile/cycle
         *
         * @return the array of all issues for the lane/tile/cycle
         */
        uint_t get_issue(const size_t type_index) const
        {
            return m_issues[type_index];
        }
        /** @} */

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return "RunDiagnostics"
         */
        static const char *prefix()
        { return "RunDiagnostics"; }

    private:
        uint_vector m_issues;
        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

