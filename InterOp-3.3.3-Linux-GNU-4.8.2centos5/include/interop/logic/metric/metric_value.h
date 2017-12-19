/** Logic to get a value from a metric
 *
 *  @file
 *  @date  4/29/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <vector>
#include <set>
#include "interop/util/exception.h"
#include "interop/model/metrics/tile_metric.h"
#include "interop/model/model_exceptions.h"
#include "interop/constants/enums.h"
#include "interop/model/metrics/extraction_metric.h"
#include "interop/model/metrics/q_metric.h"
#include "interop/model/metrics/error_metric.h"
#include "interop/model/metrics/corrected_intensity_metric.h"
#include "interop/model/metrics/phasing_metric.h"
// IUO
#include "interop/model/metrics/registration_metric.h"
#include "interop/model/metrics/pf_grid_metric.h"
#include "interop/model/metrics/q_grid_metric.h"
#include "interop/model/metrics/fwhm_grid_metric.h"
#include "interop/model/metrics/extended_tile_metric.h"
#include "interop/model/metrics/basecalling_metric.h"


namespace illumina { namespace interop { namespace logic { namespace metric
{

    /** This template class retrieves a value from a metric object based on the value of the
     * provided metric_type enum and possibly an index or other information.
     *
     * This template class must be specialized for each metric type.
     */
    template<class M>
    class metric_value;

    /** Specialization for model::metrics::extraction_metric
     *
     * Supports enums: Intensity and FWHM
     */
    template<>
    class metric_value<model::metrics::extraction_metric>
    {
    public:
        /** Constructor
         *
         * @param _channel specific channel to select
         */
        metric_value(const size_t _channel) : channel(_channel){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric extraction metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::extraction_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::Intensity:
                    return metric.max_intensity(channel);
                case constants::FWHM:
                    return metric.focus_score(channel);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const size_t channel;
    };


    /** Specialization for model::metrics::q_by_lane_metric
     *
     * Supports enums: PercentQ20, PercentQ30, AccumPercentQ20, AccumPercentQ30, and QScore
     */
    template<>
    class metric_value<model::metrics::q_by_lane_metric>
    {
        typedef model::metrics::q_by_lane_metric::uint_t uint_t;
    public:
        /** Constructor
         *
         * @param _index_for_qvalue Q20 or Q30 index
         * @param _bins bins for Q-value histogram
         */
        metric_value(const size_t _index_for_qvalue,
                     const model::metrics::q_by_lane_metric::qscore_bin_vector_type& _bins) :
                index_for_qvalue(static_cast<uint_t>(_index_for_qvalue)), bins(_bins){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric q-metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::q_by_lane_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::Q20Percent:
                case constants::Q30Percent:
                    return metric.percent_over_qscore(index_for_qvalue);
                case constants::AccumPercentQ20:
                case constants::AccumPercentQ30:
                    return metric.percent_over_qscore_cumulative(index_for_qvalue);
                case constants::QScore:
                {
                    const uint_t median = metric.median(bins);
                    if (median == std::numeric_limits<uint_t>::max() || median == 0)
                        return std::numeric_limits<float>::quiet_NaN();
                    return static_cast<float>(median);
                }
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const uint_t index_for_qvalue;
        const model::metrics::q_metric::qscore_bin_vector_type& bins;
    };

    /** Specialization for model::metrics::q_collapsed_metric
     *
     * Supports enums: PercentQ20, PercentQ30, AccumPercentQ20, AccumPercentQ30, and QScore
     */
    template<>
    class metric_value<model::metrics::q_collapsed_metric>
    {
        typedef model::metrics::q_collapsed_metric::uint_t uint_t;
    public:
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric q-metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::q_collapsed_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::Q20Percent:
                    return metric.percent_over_q20();
                case constants::Q30Percent:
                    return metric.percent_over_q30();
                case constants::AccumPercentQ20:
                    return metric.cumulative_percent_over_q20();
                case constants::AccumPercentQ30:
                    return metric.cumulative_percent_over_q30();
                case constants::QScore:
                {
                    const uint_t median = metric.median_qscore();
                    if (median == std::numeric_limits<uint_t>::max() || median == 0)
                        return std::numeric_limits<float>::quiet_NaN();
                    return static_cast<float>(median);
                }
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    };

    /** Specialization for model::metrics::error_metric
     *
     * Supports enums: ErrorRate
     */
    template<>
    class metric_value<model::metrics::error_metric>
    {
    public:
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric error metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::error_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::ErrorRate:
                    return metric.error_rate();
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    };

    /** Specialization for model::metrics::corrected_intensity_metric
     *
     * Supports enums: PercentBase, CorrectedIntensity, CalledIntensity, and SignalToNoise
     */
    template<>
    class metric_value<model::metrics::corrected_intensity_metric>
    {
    public:
        /** Constructor
         *
         * @param _base specific base to select
         */
        metric_value(const constants::dna_bases _base) : base(_base){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric error metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::corrected_intensity_metric& metric,
                         const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::BasePercent:
                    return metric.percent_base(base);
                case constants::CorrectedIntensity:
                {
                    const ::uint16_t corrected_int_all = metric.corrected_int_all(base);
                    if (corrected_int_all == std::numeric_limits< ::uint16_t>::max())
                        return std::numeric_limits<float>::quiet_NaN();
                    return static_cast<float>(corrected_int_all);
                }
                case constants::CalledIntensity:
                {
                    const float corrected_int_called = metric.corrected_int_called(base);
                    if (corrected_int_called == std::numeric_limits< ::uint16_t>::max() ||
                            std::isnan(corrected_int_called))
                        return std::numeric_limits<float>::quiet_NaN();
                    return corrected_int_called;
                }
                case constants::SignalToNoise:
                    return metric.signal_to_noise();
                case constants::PercentNoCall:
                    return metric.percent_nocall();
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const constants::dna_bases base;
    };


    /** Specialization for model::metrics::image_metric
     *
     * Supports enums: MinContrast, MaxContrast
     */
    template<>
    class metric_value<model::metrics::image_metric>
    {
    public:
        /** Constructor
         *
         * @param _channel specific channel to select
         */
        metric_value(const size_t _channel) : channel(_channel){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric extraction metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::image_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::MinContrast:
                    return metric.min_contrast(channel);
                case constants::MaxContrast:
                    return metric.max_contrast(channel);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const size_t channel;
    };

    /** Specialization for model::metrics::tile_metric
     *
     * Supports enums: PercentPF, DensityPF, Density, ClusterCount, ClusterCountPF, PercentAligned, PercentPhasing,
     * and PercentPrephasing
     */
    template<>
    class metric_value<model::metrics::tile_metric>
    {
    public:
        /** Constructor
         *
         * @param read specific read to select
         */
        metric_value(const size_t read) : m_read(read == 0 ? 1 : read){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric error metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::tile_metric& metric, const constants::metric_type type)const
        {
            const float density_scale = 1000;
            const float count_scale = 1000000;
            const float NaN = std::numeric_limits<float>::quiet_NaN();
            switch(type)
            {
                case constants::PercentPF:
                {
                    return metric.percent_pf();
                }
                case constants::ClustersPF://constants::DensityPF:
                {
                    return metric.cluster_density_pf() / density_scale;
                }
                case constants::Clusters://Density:
                {
                    return  metric.cluster_density() / density_scale;
                }
                case constants::ClusterCount:
                {
                    return metric.cluster_count() / count_scale;
                }
                case constants::ClusterCountPF:
                {
                    return metric.cluster_count_pf() / count_scale;
                }
                case constants::PercentAligned:
                {
                    for(size_t i=0;i<metric.read_metrics().size();++i)
                    {
                        if (m_read == metric.read_metrics()[i].read())
                        {
                            return metric.read_metrics()[i].percent_aligned();
                        }
                    }
                    return NaN;
                }
                case constants::PercentPhasing:
                {
                    for(size_t i=0;i<metric.read_metrics().size();++i)
                    {
                        if (m_read == metric.read_metrics()[i].read())
                        {
                            return metric.read_metrics()[i].percent_phasing();
                        }
                    }
                    return NaN;
                }
                case constants::PercentPrephasing:
                {
                    for(size_t i=0;i<metric.read_metrics().size();++i)
                    {
                        if (m_read == metric.read_metrics()[i].read())
                        {
                            return metric.read_metrics()[i].percent_prephasing();
                        }
                    }
                    return NaN;
                }
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const size_t m_read;
    };


    /** Specialization for model::metrics::phasing_metric
     *
     * Supports enums: Phasing, PrePhasing
     */
    template<>
    class metric_value<model::metrics::phasing_metric>
    {
    public:
        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric phasing metric to extract data from
         * @param type field we want to extract from the metric
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::phasing_metric& metric,
                         const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::Phasing:
                    return metric.phasing_weight();
                case constants::PrePhasing:
                    return metric.prephasing_weight();
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    };

    // IUO

    /** Specialization for model::metrics::extended_tile_metric
    *
    * Supports enums: % Occupancy, Occupied Count
    */
    template<>
    class metric_value<model::metrics::extended_tile_metric>
    {
        typedef model::metric_base::metric_set< model::metrics::tile_metric > tile_metric_set_t;
    public:
        /** Constructor
         *
         * @param tile_metric_set tile metric set
         */
        metric_value(const tile_metric_set_t& tile_metric_set) : m_tile_metric_set(tile_metric_set){}
        /** Get the metric value corresponding to the metric_type enum value
         *
         * @param metric error metric
         * @param type metric type
         * @return metric value
         */
        float operator()(const model::metrics::extended_tile_metric& metric, const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::OccupiedCountK:
                {
                    return metric.cluster_count_occupied_k();
                }
                case constants::PercentOccupied:
                {
                    if( m_tile_metric_set.has_metric(metric.id()) )
                    {
                        return metric.percent_occupied(m_tile_metric_set.get_metric(metric.id()).cluster_count_k());
                    }
                    return 0;
                }
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const tile_metric_set_t& m_tile_metric_set;
    };



    /** Specialization for model::metrics::pf_grid_metric
    *
    * Supports enums: SubtileClusters, SubtileClustersPF, SubtileDensity, SubtileDensityPF, and SubtilePFPercent
    */
    template<>
    class metric_value<model::metrics::pf_grid_metric>
    {
    public:
        /** Constructor
         *
         * @param area_in_mm2 cluster density (pixels per mm^2)
         * @return
         */
        metric_value(const float area_in_mm2) : m_area_in_mm2(area_in_mm2){}


        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric PF grid metric to extract data from
         * @param type field we want to extract from the metric
         * @param x_bin subtile bin index in X
         * @param y_bin subtile bin index in Y
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::pf_grid_metric& metric,
                         const constants::metric_type type,
                         const size_t x_bin,
                         const size_t y_bin)const
        {
            switch(type)
            {
                case constants::SubtileClusters:
                    return static_cast<float>(metric.raw_cluster_count(x_bin, y_bin));
                case constants::SubtileClustersPF:
                    return static_cast<float>(metric.pf_cluster_count(x_bin, y_bin));
                case constants::SubtileDensity:
                    return metric.raw_cluster_density_k(x_bin, y_bin, m_area_in_mm2);
                case constants::SubtileDensityPF:
                    return metric.pf_cluster_density_k(x_bin, y_bin, m_area_in_mm2);
                case constants::SubtilePFPercent:
                    return metric.percent_pf(x_bin, y_bin);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    private:
        const float m_area_in_mm2;
    };

    /** Specialization for model::metrics::fwhm_grid_metric
     *
     * Supports enums: SubtileFwhm
     */
    template<>
    class metric_value<model::metrics::fwhm_grid_metric>
    {
    public:
        /** Constructor
         *
         * @param channel specific channel to select
         */
        metric_value(const size_t channel) : m_channel(channel){}

        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric FWHM grid metric to extract data from
         * @param type field we want to extract from the metric
         * @param x_bin subtile bin index in X
         * @param y_bin subtile bin index in Y
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::fwhm_grid_metric& metric,
                         const constants::metric_type type,
                         const size_t x_bin,
                         const size_t y_bin)const
        {
            switch(type)
            {
                case constants::SubtileFwhm:
                    return metric.focus_score(m_channel, y_bin, x_bin);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }

    private:
        const size_t m_channel;
    };

    /** Specialization for model::metrics::q_grid_metric
     *
     * Supports enums: SubtileQ30Percent
     */
    template<>
    class metric_value<model::metrics::q_grid_metric>
    {
    public:
        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric Q grid metric to extract data from
         * @param type field we want to extract from the metric
         * @param x_bin subtile bin index in X
         * @param y_bin subtile bin index in Y
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::q_grid_metric& metric,
                         const constants::metric_type type,
                         const size_t x_bin,
                         const size_t y_bin)const
        {
            switch(type)
            {
                case constants::SubtileQ30Percent:
                    return metric.percent_q30(x_bin, y_bin);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    };

    /** Specialization for model::metrics::registration_metric
     *
     * Supports enums: MaxResidualR, MaxResidualX, MaxResidualY
     */
    template<>
    class metric_value<model::metrics::registration_metric>
    {
    public:
        /** Constructor
         *
         * @param _channel specific channel to select
         */
        metric_value(const size_t _channel) : channel(_channel){}
        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric registration metric to extract data from
         * @param type field we want to extract from the metric
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::registration_metric& metric,
                         const constants::metric_type type)const
        {
            switch(type)
            {
                case constants::MaxResidualR:
                    return metric.max_residual_radial_error(channel);
                case constants::Theta:
                    return metric.theta(channel);
                case constants::ThetaZ:
                    return metric.theta_z(channel);
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }

    private:
        size_t channel;
    };

    /** Specialization for model::metrics::run_diagnostics_metric
     *
     * Supports enums: MaxResidualR, MaxResidualX, MaxResidualY
     */
    template<>
    class metric_value<model::metrics::run_diagnostics_metric>
    {
    public:
        /** Get the metric value corresponding to the enum value represented by type
         *
         * @param metric run diagnostics metric to extract data from
         * @param type field we want to extract from the metric
         * @return float value representing the field value in the metric
         */
        float operator()(const model::metrics::run_diagnostics_metric& metric,
                         const constants::run_diagnostics_issue_type type)const
        {
            switch(type)
            {
                case constants::DeadTile:
                case constants::BlankImage:
                case constants::QOutliers:
                case constants::FailedCycle:
                    return static_cast<float>(metric.get_issue(type));
                //run_diagnostics_metric is a sparse representation - if the metric exists, then there's at least one issue
                case constants::AllIssues:
                {
                    return 1.0f;
                }
                default:
                    INTEROP_THROW(model::invalid_metric_type, "Unknown metric type " << constants::to_string(type));
            }
        }
    };

}}}}


