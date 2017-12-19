/** Logic for run diagnostics metrics
 *
 *  @file
 *  @date  7/7/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/run_metrics.h"
#include "interop/model/model_exceptions.h"
#include "interop/model/metric_base/metric_set.h"


namespace illumina { namespace interop { namespace logic { namespace metric
{

    /** Returns the array of all issues for the lane/tile/cycle
     *
     * @return the array of all issues for the lane/tile/cycle
     */
    void get_issue_labels(std::vector<std::string>& issue_labels);

    /** Populate the run diagnostics metrics data structure given the other InterOp data
     *
     * @param metrics run metrics object
     */
    void populate_run_diagnostics_metrics(model::metrics::run_metrics& metrics);

}}}}

