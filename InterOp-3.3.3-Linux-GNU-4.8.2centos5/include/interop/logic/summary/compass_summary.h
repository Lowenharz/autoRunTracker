/** Summary logic for compass metrics
 *
 *  @file
 *  @date   11/18/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/model_exceptions.h"
#include "interop/model/summary/run_summary.h"
#include "interop/model/run_metrics.h"
#include "interop/logic/utils/metrics_to_load.h"
#include "interop/model/table/compass_cycle_table.h"
#include "interop/model/plot/plot_exceptions.h"


namespace illumina { namespace interop { namespace logic { namespace summary
{
    /** Summarize a collection of compass metrics
     *
     * @ingroup summary_logic
     * @param metrics source collection of all metrics
     * @param summary destination run summary
     * @param skip_median skip the median calculation
     * @param clear flag indicating whether to clear the summary model (default: true)
     */
    void summarize_compass_run_metrics(model::metrics::run_metrics& metrics,
                                       model::summary::run_summary& summary,
                                       const bool skip_median=false,
                                       const bool clear=true)
    throw( model::index_out_of_bounds_exception,
    model::invalid_channel_exception );

    /** Summarize compass cycle metrics into a table
     *
     * @param metrics run metrics
     * @param table data table
     */
    void summarize_compass_cycle_metrics(model::metrics::run_metrics &metrics, model::table::compass_cycle_table& table)
    throw(model::index_out_of_bounds_exception,
    model::invalid_metric_type,
    model::invalid_channel_exception,
    model::invalid_filter_option,
    model::invalid_read_exception);


}}}}


