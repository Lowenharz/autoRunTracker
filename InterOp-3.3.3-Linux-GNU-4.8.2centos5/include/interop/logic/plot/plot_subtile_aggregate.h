/** Plot an arbitrary metric, aggregated across a subtile dimension
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


    /** Plot a specified metric value by subtile, aggregated over the subtile X or Y bin
     *
     * @ingroup plot_logic
     * @param metrics run metrics
     * @param type specific metric value to plot by lane
     * @param options options to filter the data
     * @param data_x output plot data aggregated in X
     * @param data_y output plot data aggregated in Y
     */
    void plot_subtile_aggregate(model::metrics::run_metrics& metrics,
                                const constants::metric_type type,
                                const model::plot::filter_options& options,
                                model::plot::plot_data<model::plot::candle_stick_point>& data_x,
                                model::plot::plot_data<model::plot::candle_stick_point>& data_y)
                            throw(model::index_out_of_bounds_exception,
                            model::invalid_metric_type,
                            model::invalid_filter_option);


    /** Plot a specified metric value by cycle
     *
     * @ingroup plot_logic
     * @todo Is this temporary?
     * @param metrics run metrics
     * @param metric_name name of metric value to plot by cycle
     * @param options options to filter the data
     * @param data_x output plot data aggregated in X
     * @param data_y output plot data aggregated in Y
     */
    void plot_subtile_aggregate(model::metrics::run_metrics& metrics,
                       const std::string& metric_name,
                       const model::plot::filter_options& options,
                       model::plot::plot_data<model::plot::candle_stick_point>& data_x,
                       model::plot::plot_data<model::plot::candle_stick_point>& data_y)
                        throw(model::index_out_of_bounds_exception,
                        model::invalid_metric_type,
                        model::invalid_filter_option);

}}}}

