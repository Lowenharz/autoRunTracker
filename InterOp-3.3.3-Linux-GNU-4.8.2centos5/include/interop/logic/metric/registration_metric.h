/** Logic to populate registration predicted error
 *
 *  @file
 *  @date  11/28/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/metrics/registration_metric.h"
#include "interop/model/model_exceptions.h"
#include "interop/model/metric_base/metric_set.h"

namespace illumina { namespace interop { namespace logic { namespace metric
{

    /** Populate the populate registration predicted error
     *
     * @param registration_metrics registration metric set
     * @param fiducial_locations locations of the fiducials
     * @param score_tolerance tolerance for registration
     * @param skip_first_cycle skip the first cycle
     * @param use_loo use leave one out error estimation (self-consistency used by default)
     */
    void populate_registration_error_metrics(model::metric_base::metric_set<model::metrics::registration_metric>& registration_metrics,
                                             const model::metrics::registration_metric_header::point2d_vector_t& fiducial_locations,
                                             const float score_tolerance,
                                             const bool skip_first_cycle=true,
                                             const bool use_loo=false) throw(model::index_out_of_bounds_exception);

    /** Populate the populate registration predicted error
     *
     * @param registration_metrics registration metric set
     * @param use_loo use leave one out error estimation (self-consistency used by default)
     */
    void populate_registration_error_metrics(model::metric_base::metric_set<model::metrics::registration_metric>& registration_metrics,
                                             const bool use_loo=false)
    throw(model::index_out_of_bounds_exception);

    /** Get the labels for affine transform matrix
     *
     * @param channels channel names
     * @param labels destination list of strings containing labels of affine transform matrix elements
     */
    void get_affine_matrix_labels(const std::vector<std::string>& channels, std::vector<std::string>& labels);

    /** Get the labels for the sub tile offsets
     *
     * @param channels channel names
     * @param region_count number of regions
     * @param fiducial_layout layout of fiducials: Square, hex, etc.
     * @param labels destination list of strings containing labels of sub tile offsets
     */
    void get_subtile_offset_labels(const std::vector<std::string>& channels,
                                   const size_t region_count,
                                   const constants::layout_type fiducial_layout,
                                   std::vector<std::string>& labels)throw(model::invalid_parameter);

}}}}
