/** Plot the subtile flowcell map
 *
 *  @file
 *  @date 5/5/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include "interop/constants/enums.h"
#include "interop/model/run_metrics.h"
#include "interop/model/plot/filter_options.h"
#include "interop/model/plot/subtile_data.h"
#include "interop/logic/utils/metrics_to_load.h"

namespace illumina { namespace interop { namespace logic { namespace plot
{
    /** Find first valid tile in heat map
     *
     * @ingroup plot_logic
     * @param data output subtile map
     * @param found id of found tile
     */
    void find_first_valid(model::plot::subtile_data &data, model::metric_base::base_metric& found)
    throw(model::index_out_of_bounds_exception);
    /** Find first valid tile in heat map
     *
     * @ingroup plot_logic
     * @param data output subtile map
     * @param buffer preallocated memory for data
     * @param id_buffer preallocated memory for tile ids
     * @param found id of metric found
     */
    void find_first_valid(model::plot::subtile_data &data,
                            float *buffer,
                            ::uint32_t *id_buffer,
                            model::metric_base::base_metric& found)
    throw(model::index_out_of_bounds_exception,
    model::invalid_parameter);
    /** Select single tile to map
     *
     * @ingroup plot_logic
     * @param data output subtile map
     * @param lane lane index
     * @param tile tile index
     * @param tile_data_buffer preallocated memory for destination single tile values data
     */
    void select_tile_values(model::plot::subtile_data &data,
                            const size_t lane,
                            const size_t tile,
                            float *tile_data_buffer)
    throw(model::index_out_of_bounds_exception);
    /** Select single tile to map
     *
     * @ingroup plot_logic
     * @param data output subtile map
     * @param lane lane index
     * @param tile tile index
     * @param buffer preallocated memory for data
     * @param id_buffer preallocated memory for tile ids
     * @param tile_data_buffer preallocated memory for destination single tile values data
     */
    void select_tile_values(model::plot::subtile_data &data,
                            const size_t lane,
                            const size_t tile,
                            float *buffer,
                            ::uint32_t *id_buffer,
                            float *tile_data_buffer)
    throw(model::index_out_of_bounds_exception,
    model::invalid_parameter);


    /** Plot a subtile flowcell map
     *
     * @ingroup plot_logic
     * @param metrics run metrics
     * @param type specific metric value to plot in sub tile grid
     * @param options options to filter the data
     * @param data output subtile map
     * @param buffer preallocated memory for data
     * @param tile_buffer preallocated memory for tile ids
     */
    void plot_subtile_map(model::metrics::run_metrics &metrics,
                          const constants::metric_type type,
                          const model::plot::filter_options &options,
                          model::plot::subtile_data &data,
                          float *buffer = 0,
                          ::uint32_t *tile_buffer = 0)
    throw(model::invalid_filter_option,
    model::invalid_metric_type,
    model::index_out_of_bounds_exception);

    /** Plot a subtile flowcell map
     *
     * @ingroup plot_logic
     * @param metrics run metrics
     * @param metric_name specific metric name to plot in sub tile grid
     * @param options options to filter the data
     * @param data output flowcell map
     * @param buffer preallocated memory for data
     * @param tile_buffer preallocated memory for tile ids
     */
    void plot_subtile_map(model::metrics::run_metrics &metrics,
                          const std::string &metric_name,
                          const model::plot::filter_options &options,
                          model::plot::subtile_data &data,
                          float *buffer = 0,
                          ::uint32_t *tile_buffer = 0)
    throw(model::invalid_filter_option,
    model::invalid_metric_type,
    model::index_out_of_bounds_exception);

    /** List metric type names available for subtile
     *
     * @param types destination vector to fill with metric type names
     */
    void list_subtile_metrics(std::vector< logic::utils::metric_type_description_t > &types);

    /** List metric type names available for subtile
     *
     * @param metrics run metrics
     * @param types destination vector to fill with metric type names
     */
    void list_subtile_metrics(const model::metrics::run_metrics &metrics,
                              std::vector< logic::utils::metric_type_description_t > &types);
    /** Calculate the required buffer size
     *
     * @param metrics run metrics
     * @param type metric type
     * @param options options to filter the data
     */
    size_t calculate_subtile_buffer_size(const model::metrics::run_metrics& metrics,
                                         const constants::metric_type type,
                                         const model::plot::filter_options& options)
    throw(model::invalid_metric_type);


}}}}

