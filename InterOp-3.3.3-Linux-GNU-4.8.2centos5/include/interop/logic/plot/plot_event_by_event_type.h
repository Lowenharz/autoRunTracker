/** Plot all event interval timings by event type
 *
 *  @file
 *  @date 5/1/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include "interop/constants/enums.h"
#include "interop/model/run_metrics.h"
#include "interop/model/plot/filter_options.h"
#include "interop/model/plot/plot_data.h"
#include "interop/model/plot/candle_stick_point.h"
#include "interop/logic/utils/metrics_to_load.h"

namespace illumina { namespace interop { namespace logic { namespace plot
{
    /** Plot all event interval timings by event type
     *
     * @ingroup plot_logic
     * @param metrics run metrics
     * @param options options to filter the data
     * @param data output plot data
     * @param save_outliers if true, then save outliers
     */
    void plot_event_by_event_type(model::metrics::run_metrics &metrics,
                                  const model::plot::filter_options &options,
                                  model::plot::plot_data<model::plot::candle_stick_point> &data,
                                  const bool save_outliers=true)
            throw(model::index_out_of_bounds_exception,
            model::invalid_metric_type,
            model::invalid_filter_option);
}}}}

