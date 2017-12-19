/** Plot an arbitrary cycle metric by cycle
 *
 *  @file
 *  @date  4/28/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/run_metrics.h"
#include "interop/model/plot/filter_options.h"
#include "interop/model/plot/plot_data.h"
#include "interop/model/plot/candle_stick_point.h"
#include "interop/constants/enums.h"
#include "interop/logic/utils/metrics_to_load.h"

namespace illumina { namespace interop { namespace logic { namespace plot
{
    /** Plot a specified metric value by cycle
     *
     * @ingroup plot_logic
     * @param metrics run metrics
     * @param options options to filter the data
     * @param distortion_curve_index selection for the specific curve to view
     * @param data output plot data
     */
    void plot_distortion(model::metrics::run_metrics& metrics,
                         const model::plot::filter_options& options,
                         const size_t distortion_curve_index,
                         model::plot::plot_data<model::plot::candle_stick_point>& data)
    throw(model::index_out_of_bounds_exception,
    model::invalid_channel_exception,
    model::invalid_filter_option,
    model::invalid_read_exception);


}}}}


