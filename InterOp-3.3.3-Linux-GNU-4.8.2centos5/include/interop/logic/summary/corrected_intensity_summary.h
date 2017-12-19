/** Summary logic for corrected intensity metrics
 *
 *  @file
 *  @date  8/29/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <vector>
#include "interop/util/exception.h"
#include "interop/model/model_exceptions.h"
#include "interop/logic/summary/summary_statistics.h"
#include "interop/model/metrics/corrected_intensity_metric.h"
#include "interop/logic/summary/map_cycle_to_read.h"
#include "interop/model/summary/run_summary.h"


namespace illumina { namespace interop { namespace logic { namespace summary
{
     /** Summarize a collection of compass metrics
     *
     * @sa model::summary::lane_summary::no_call
     * @sa model::summary::read_summary::no_call
     * @sa model::summary::run_summary::no_call
     *
     * @param beg iterator to start of a collection of extraction metrics
     * @param end iterator to end of a collection of extraction metrics
     * @param cycle_to_read map cycle to the read number and cycle within read number
     * @param run destination run summary
     */
    template<typename I>
    void summarize_no_call_metric(I beg,
                                  I end,
                                  const read_cycle_vector_t &cycle_to_read,
                                  model::summary::run_summary &run)
    throw(model::index_out_of_bounds_exception)
    {
        typedef summary_by_lane_read<float> summary_by_lane_read_t;
        if (beg == end) return;
        if (run.size() == 0)return;
        summary_by_lane_read_t temp_no_calls(run, std::distance(beg, end));
        summary_by_lane_read_t temp_total_calls(run, std::distance(beg, end));

        for (; beg != end; ++beg)
        {
            if ((beg->cycle() - 1) >= cycle_to_read.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Cycle exceeds total cycles from Reads in the RunInfo.xml");
            const size_t read = cycle_to_read[beg->cycle() - 1].number - 1;
            INTEROP_ASSERT(read < temp_no_calls.read_count());
            const size_t lane = beg->lane() - 1;
            if (lane >= temp_no_calls.lane_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            temp_no_calls(read, lane).push_back(static_cast<float>(beg->no_calls()));
            temp_total_calls(read, lane).push_back(static_cast<float>(beg->total_calls()));
        }

        float no_call = 0;
        float no_call_called_counts = 0;
        for (size_t read = 0; read < run.size(); ++read)
        {
            INTEROP_ASSERT(read < temp_no_calls.read_count());
            INTEROP_ASSERT(read < run.size());
            float no_call_by_read = 0;
            float total_calls_by_read = 0;

            for (size_t lane = 0; lane < run[read].size(); ++lane)
            {
                INTEROP_ASSERT(lane < temp_no_calls.lane_count());
                INTEROP_ASSERT(lane < run[read].size());

                no_call_by_read += std::accumulate(temp_no_calls(read, lane).begin(),
                                                                 temp_no_calls(read, lane).end(),
                                                                 float(0));
                total_calls_by_read += std::accumulate(temp_total_calls(read, lane).begin(),
                                                   temp_total_calls(read, lane).end(),
                                                   float(0));
            }
            run[read].summary().percent_no_call((100 * divide(no_call_by_read, total_calls_by_read)));
            no_call += no_call_by_read;
            no_call_called_counts += total_calls_by_read;
        }
        run.total_summary().percent_no_call(100 * divide(no_call, no_call_called_counts));
    }

    /** Summarize and aggregate the percent_base metric by base
     *
     * @sa model::summary::lane_summary::percent_base
     * @sa model::summary::read_summary::percent_base
     * @sa model::summary::run_summary::percent_base
     *
     * @param beg iterator to start of a collection of extraction metrics
     * @param end iterator to end of a collection of extraction metrics
     * @param cycle_to_read map cycle to the read number and cycle within read number
     * @param naming_method tile naming convention
     * @param run destination run summary
     * @param base_index the index of the base array you're accessing.
     */
    template<typename I>
    void summarize_base_percent_metric(I beg,
                                       I end,
                                       const read_cycle_vector_t &cycle_to_read,
                                       const constants::tile_naming_method naming_method,
                                       model::summary::run_summary &run,
                                       const size_t base_index)
                throw(model::index_out_of_bounds_exception)
    {
        typedef summary_by_lane_read<float> summary_by_lane_read_t;
        const size_t surface_count = run.surface_count();
        summary_by_lane_read_t temp_called_counts(run, std::distance(beg, end));
        summary_by_lane_read_t temp_total_calls(run, std::distance(beg, end));
        const constants::dna_bases base_array [] = {constants::A, constants::C,
                                                        constants::G, constants::T};
        summary_by_lane_read_t temp_called_counts_surface(run, std::distance(beg, end), surface_count);
        summary_by_lane_read_t temp_total_calls_surface(run, std::distance(beg, end), surface_count);

        for (; beg != end; ++beg)
        {
            if ((beg->cycle() - 1) >= cycle_to_read.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Cycle exceeds total cycles from Reads in the RunInfo.xml");
            const size_t read = cycle_to_read[beg->cycle() - 1].number - 1;
            INTEROP_ASSERT(read < temp_called_counts.read_count());
            const size_t lane = beg->lane() - 1;
            if (lane >= temp_called_counts.lane_count())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            temp_called_counts(read, lane).push_back(static_cast<float>(beg->called_counts(base_array[base_index])));
            temp_total_calls(read, lane).push_back(static_cast<float>(beg->total_calls()));
            if(surface_count < 2) continue;
            const size_t surface = beg->surface(naming_method)-1;
            temp_called_counts_surface(read, lane, surface).push_back(static_cast<float>(beg->called_counts(base_array[base_index])));
            temp_total_calls_surface(read, lane, surface).push_back(static_cast<float>(beg->total_calls()));
        }

        float percent_base_called_counts = 0;
        float percent_base_total_calls = 0;
        for (size_t read = 0; read < run.size(); ++read)
        {
            INTEROP_ASSERT(read < temp_called_counts.read_count());
            INTEROP_ASSERT(read < run.size());
            float called_counts_by_read = 0;
            float total_calls_by_read = 0;
            for (size_t lane = 0; lane < run[read].size(); lane++)
            {
                INTEROP_ASSERT(lane < temp_called_counts.lane_count());
                INTEROP_ASSERT(lane < run[read].size());

                const float called_count = std::accumulate(temp_called_counts(read, lane).begin(),
                                                        temp_called_counts(read, lane).end(),
                                                        float(0));
                const float total_calls = std::accumulate(temp_total_calls(read, lane).begin(),
                                                         temp_total_calls(read, lane).end(),
                                                         float(0));
                run[read][lane].percent_base(base_index, 100.0f * divide(called_count, total_calls));
                called_counts_by_read += called_count;
                total_calls_by_read += total_calls;
                if(surface_count < 2) continue;
                for (size_t surface = 0; surface < surface_count; ++surface)
                {
                    const float called_count_s = std::accumulate(temp_called_counts_surface(read, lane, surface).begin(),
                                                                 temp_called_counts_surface(read, lane, surface).end(),
                                                                 float(0));
                    const float total_calls_s = std::accumulate(temp_total_calls_surface(read, lane, surface).begin(),
                                                                temp_total_calls_surface(read, lane, surface).end(),
                                                                float(0));
                    run[read][lane][surface].percent_base(base_index, 100.0f * divide(called_count_s, total_calls_s));
                }
            }

            run[read].summary().percent_base(base_index, 100.0f * divide(called_counts_by_read, total_calls_by_read));
            percent_base_called_counts += called_counts_by_read;
            percent_base_total_calls += total_calls_by_read;
        }
        run.total_summary().percent_base(base_index,
                                         100.0f * divide(percent_base_called_counts, percent_base_total_calls));
    }
}}}}

