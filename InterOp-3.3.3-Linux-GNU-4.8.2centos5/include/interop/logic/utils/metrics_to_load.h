/** Collection of utilities for metric listing
 *
 *  @file
 *  @date  4/28/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <vector>
#include "interop/constants/enums.h"
#include "interop/constants/enum_description.h"
#include "interop/model/model_exceptions.h"

namespace illumina { namespace interop { namespace logic { namespace utils
{
    /** Define a metric type description */
    typedef constants::enum_description< constants::metric_type> metric_type_description_t;
    /** List the required on demand metrics
     *
     * @param group specific metric group to load
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param is_iuo display IUO metrics
     */
    void list_metrics_to_load(const constants::metric_group group,
                              std::vector<unsigned char>& valid_to_load,
                              const constants::instrument_type instrument,
                              const bool is_iuo);
    /** List the required on demand metrics
     *
     * @param type specific metric type to load
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param is_iuo display IUO metrics
     */
    void list_metrics_to_load(const constants::metric_type type,
                              std::vector<unsigned char>& valid_to_load,
                              const constants::instrument_type instrument,
                              const bool is_iuo);
    /** List the required on demand metrics
     *
     * @param groups collection of specific metric groups to load
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param is_iuo display IUO metrics
     */
    void list_metrics_to_load(const std::vector<constants::metric_group>& groups,
                              std::vector<unsigned char>& valid_to_load,
                              const constants::instrument_type instrument,
                              const bool is_iuo);
    /** List the required on demand metrics
     *
     * @param types collection of specific metric types to load
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param is_iuo display IUO metrics
     */
    void list_metrics_to_load(const std::vector<constants::metric_type>& types,
                              std::vector<unsigned char>& valid_to_load,
                              const constants::instrument_type instrument,
                              const bool is_iuo);
    /** List the required on demand metrics
     *
     * @param metric_name name of metric value to load
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param is_iuo display IUO metrics
     */
    void list_metrics_to_load(const std::string& metric_name,
                              std::vector<unsigned char>& valid_to_load,
                              const constants::instrument_type instrument,
                              const bool is_iuo)
    throw(model::invalid_metric_type);

    /** List all required metric groups
     *
     * @param groups destination group list
     * @param instrument instrument type
     * @param show_iuo display IUO metrics
     */
    void list_summary_metric_groups(std::vector<constants::metric_group>& groups,
                                    const constants::instrument_type instrument,
                                    const bool show_iuo=false);

    /** List all required metric groups
     *
     * @param groups destination group list
     */
    void list_index_summary_metric_groups(std::vector<constants::metric_group>& groups);


    /** List all required metric groups for the summary tab
     *
     * @param valid_to_load list of metrics to load on demand
     * @param instrument instrument type
     * @param show_iuo display IUO metrics
     */
    void list_summary_metrics_to_load(std::vector<unsigned char>& valid_to_load,
                                      const constants::instrument_type instrument=constants::NovaSeq,
                                      const bool show_iuo=false);

    /** List all required metric groups for the index tab
     *
     * @param valid_to_load list of metrics to load on demand
     */
    void list_index_metrics_to_load(std::vector<unsigned char>& valid_to_load);

    /** List all required metric groups for the analysis tab
     *
     * @param valid_to_load list of metrics to load on demand
     * @param show_iuo display IUO metrics
     */
    void list_analysis_metrics_to_load(std::vector<unsigned char>& valid_to_load,
                                       const bool show_iuo=false);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // IUO
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** List the required metrics to load for the event metrics tab
     *
     * @param valid_to_load list of metrics to load on demand
     */
    void list_event_metrics_to_load(std::vector<unsigned char>& valid_to_load);

    /** List all required metric groups for the subtile tab
     *
     * @param valid_to_load list of metrics to load on demand
     */
    void list_subtile_metrics_to_load(std::vector<unsigned char>& valid_to_load);

    /** List all required metric groups for the run diagnostics tab
     *
     * @param valid_to_load list of metrics to load on demand
     */
    void list_run_diagnostics_metrics_to_load(std::vector<unsigned char>& valid_to_load);

    /** List the required metric groups to load for the run diagnostics table
     *
     * @param groups list of metric groups to load on demand
     */
    void list_run_diagnostics_metric_groups(std::vector<constants::metric_group>& groups);

}}}}

