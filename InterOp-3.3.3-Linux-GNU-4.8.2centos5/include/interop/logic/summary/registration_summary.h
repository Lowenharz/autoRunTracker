/** Summary logic for registration metrics
 *
 *  @file
 *  @date 1/3/17
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <vector>
#include "interop/util/exception.h"
#include "interop/model/model_exceptions.h"
#include "interop/logic/summary/summary_statistics.h"
#include "interop/model/metrics/registration_metric.h"
#include "interop/model/summary/run_summary.h"
#include "interop/model/summary/metric_average.h"
#include "interop/logic/utils/enums.h"

namespace illumina { namespace interop { namespace logic { namespace summary
{

    /** Summarize a collection registration metrics
    *
    * @note IUO
    *
    * @param beg iterator to start of a collection of registration metrics
    * @param end iterator to end of a collection of registration metrics
    * @param cycle_to_read map cycle to the read number and cycle within read number
    * @param naming_method tile naming convention
    * @param run destination run summary
    * @param first_channel channel to measure
    * @param skip_median skip the median calculation
    */
    template<typename I>
    void summarize_registration_metrics(I beg,
                                        I end,
                                        const read_cycle_vector_t &cycle_to_read,
                                        const constants::tile_naming_method naming_method,
                                        model::summary::run_summary &run,
                                        const size_t first_channel,
                                        const bool skip_median)
    {
        typedef summary_by_lane_read<model::metrics::registration_metric> summary_by_lane_read_t;
        typedef INTEROP_UNORDERED_MAP(::uint64_t, std::vector<model::metrics::registration_metric>) swath_map_t;
        if ( beg == end ) return;
        if ( run.size() == 0 )return;
        if(naming_method == constants::Absolute || naming_method == constants::UnknownTileNamingMethod)
        {
            INTEROP_THROW( model::invalid_run_info_exception,
                           "Naming method not supported: " << constants::to_string(naming_method));
        }
        const bool set_nan = true;
        // Collect tiles by lane/swath/surface/section
        swath_map_t swath_map;
        model::metrics::registration_metric swath_average_metric(*beg);
        for (; beg != end; ++beg)
        {
            if ((beg->cycle() - 1) >= cycle_to_read.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Cycle exceeds total cycles from Reads in the RunInfo.xml");
            const ::uint64_t read = cycle_to_read[beg->cycle() - 1].number;
            const ::uint64_t swath = beg->tile()-beg->number(naming_method);
            const ::uint64_t hash = model::metric_base::base_cycle_metric::create_id(beg->lane(), swath, read);
            swath_map[hash].push_back(*beg);
        }

        const size_t surface_count = run.surface_count();
        summary_by_lane_read_t read_lane_cache(run, std::distance(beg, end));
        summary_by_lane_read_t read_lane_surface_cache(run, std::distance(beg, end), surface_count);

        // Create derived metric containing mean over tiles in a specific lane/swath/surface/section
        for (typename swath_map_t::const_iterator it = swath_map.begin(); it != swath_map.end(); ++it)
        {
            const ::uint64_t read_id = model::metric_base::base_cycle_metric::cycle_from_id(it->first)-1;
            const ::uint32_t tile_id =
                    static_cast< ::uint32_t > (model::metric_base::base_cycle_metric::tile_from_id(it->first));
            const ::uint64_t surface = logic::metric::surface(tile_id, naming_method)-1;
            const size_t lane = model::metric_base::base_metric::lane_from_id(it->first) - 1;
            INTEROP_ASSERTMSG(read_id < read_lane_cache.size(), read_id << " < " << read_lane_cache.size() << " -> " << run.lane_count());
            if (read_id >= read_lane_cache.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Read exceeds read count in RunInfo.xml");
            if (lane >= read_lane_cache.lane_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            for(size_t channel=0, channel_count=swath_average_metric.channel_count();channel < channel_count;++channel)
            {
                const float avg_theta = util::nan_mean<float>(it->second.begin(),
                                                       it->second.end(),
                                                       util::op::const_member_function(
                                                              channel,
                                                              &model::metrics::registration_metric::theta));
                const float avg_shear = std::numeric_limits<float>::quiet_NaN();
                // TODO: Is this valuable?
                /*util::nan_mean<float>(it->second.begin(),
                                                       it->second.end(),
                                                       util::op::const_member_function(
                                                               channel,
                                                               &model::metrics::registration_metric::shear));*/
                const float avg_theta_z = util::nan_mean<float>(it->second.begin(),
                                                                it->second.end(),
                                                                util::op::const_member_function(
                                                               channel,
                                                               &model::metrics::registration_metric::theta_z));
                swath_average_metric.set_rotation(channel, avg_theta, avg_shear, avg_theta_z);
            }
            read_lane_cache(read_id, lane).push_back(swath_average_metric);
            if(surface_count < 2) continue;
            if (surface >= surface_count)
                INTEROP_THROW(model::index_out_of_bounds_exception, "Surface exceeds surface count in RunInfo.xml");
            read_lane_surface_cache(read_id, lane, surface).push_back(swath_average_metric);
        }



        model::summary::metric_average theta_z;
        model::summary::metric_average theta;
        for (size_t read = 0; read < run.size(); ++read)
        {
            INTEROP_ASSERT(read < run.size());
            model::summary::metric_average theta_z_by_read;
            model::summary::metric_average theta_by_read;
            for (size_t lane = 0; lane < run[read].size(); ++lane)
            {
                INTEROP_ASSERT(lane < run[read].size());
                model::summary::metric_stat stat;


                nan_summarize(read_lane_cache(read, lane).begin(),
                              read_lane_cache(read, lane).end(),
                              stat, util::op::const_member_function(first_channel,
                                                                    &model::metrics::registration_metric::theta_z),
                              util::op::const_member_function_less(first_channel,
                                                                   &model::metrics::registration_metric::theta_z),
                              skip_median,
                              set_nan);
                run[read][lane].theta_z(stat);
                theta_z_by_read += stat.mean();// Handles nans!
                nan_summarize(read_lane_cache(read, lane).begin(),
                              read_lane_cache(read, lane).end(),
                              stat, util::op::const_member_function(first_channel,
                                                                    &model::metrics::registration_metric::theta),
                              util::op::const_member_function_less(first_channel,
                                                                   &model::metrics::registration_metric::theta),
                              skip_median,
                              set_nan);
                run[read][lane].theta(stat);
                theta_by_read += stat.mean(); // Handles nans!
                if(surface_count < 2) continue;
                for(size_t surface=0;surface<surface_count;++surface)
                {
                    stat.clear();
                    nan_summarize(read_lane_surface_cache(read, lane, surface).begin(),
                                  read_lane_surface_cache(read, lane, surface).end(),
                                  stat, util::op::const_member_function(first_channel,
                                                                        &model::metrics::registration_metric::theta_z),
                                  util::op::const_member_function_less(first_channel,
                                                                       &model::metrics::registration_metric::theta_z),
                                  skip_median,
                                  set_nan);
                    run[read][lane][surface].theta_z(stat);
                    stat.clear();
                    nan_summarize(read_lane_surface_cache(read, lane, surface).begin(),
                                  read_lane_surface_cache(read, lane, surface).end(),
                                  stat, util::op::const_member_function(first_channel,
                                                                        &model::metrics::registration_metric::theta),
                                  util::op::const_member_function_less(first_channel,
                                                                       &model::metrics::registration_metric::theta),
                                  skip_median,
                                  set_nan);
                    run[read][lane][surface].theta(stat);
                }
            }
            run[read].summary().theta_z(theta_z_by_read);
            run[read].summary().theta(theta_by_read);
            theta_z += theta_z_by_read; // Handles nans!
            theta += theta_by_read; // Handles nans!
        }
        run.nonindex_summary().theta_z(theta_z);
        run.total_summary().theta_z(theta_z);
        run.nonindex_summary().theta(theta);
        run.total_summary().theta(theta);
    }

}}}}

