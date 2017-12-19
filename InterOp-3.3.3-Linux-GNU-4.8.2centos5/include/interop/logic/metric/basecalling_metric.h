
/** Logic for basecalling metric
 *
 *  @file
 *  @date  1/16/17
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/metrics/basecalling_metric.h"
#include "interop/model/metrics/corrected_intensity_metric.h"

namespace illumina { namespace interop { namespace logic { namespace metric
{
    /** Populate called intensity in corrected intensity metrics from centroid radial distance
     *
     * @param basecalling_metrics basecalling metric set
     * @param corrected_intensity_metrics destination corrected intensity metric set
     */
    void populate_called_intensities(const model::metric_base::metric_set<model::metrics::basecalling_metric>& basecalling_metrics,
                                     model::metric_base::metric_set<model::metrics::corrected_intensity_metric>& corrected_intensity_metrics);
}}}}
