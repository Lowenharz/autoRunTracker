/** Summary logic for tile metrics
 *
 *  @file
 *  @date  3/6/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <vector>
#include "interop/util/exception.h"
#include "interop/model/model_exceptions.h"
#include "interop/logic/summary/summary_statistics.h"
#include "interop/model/metrics/tile_metric.h"
#include "interop/model/summary/run_summary.h"

namespace illumina { namespace interop { namespace logic { namespace summary
{
    /** Use the cached data to update a stat summary
     *
     * @param tile_data cached tile data
     * @param stat_summary destination stat summary to update
     * @param skip_median skip the median calculation
     */
    template<class TileVector>
    void update_tile_summary_from_cache(std::vector<TileVector>& tile_data,
                                        model::summary::stat_summary& stat_summary,
                                        const bool skip_median)
    {
        model::summary::metric_stat stat;
        nan_summarize(tile_data.begin(),
                  tile_data.end(),
                  stat,
                  util::op::const_member_function(&model::metrics::tile_metric::cluster_density),
                  util::op::const_member_function_less(&model::metrics::tile_metric::cluster_density),
                  skip_median);
        stat_summary.density(stat);
        stat.clear();
        nan_summarize(tile_data.begin(),
                  tile_data.end(),
                  stat,
                  util::op::const_member_function(&model::metrics::tile_metric::cluster_density_pf),
                  util::op::const_member_function_less(&model::metrics::tile_metric::cluster_density_pf),
                  skip_median);
        stat_summary.density_pf(stat);
        stat.clear();
        nan_summarize(tile_data.begin(),
                  tile_data.end(),
                  stat,
                  util::op::const_member_function(&model::metrics::tile_metric::cluster_count),
                  util::op::const_member_function_less(&model::metrics::tile_metric::cluster_count),
                  skip_median);
        stat_summary.cluster_count(stat);
        stat.clear();
        nan_summarize(tile_data.begin(),
                  tile_data.end(),
                  stat,
                  util::op::const_member_function(&model::metrics::tile_metric::cluster_count_pf),
                  util::op::const_member_function_less(&model::metrics::tile_metric::cluster_count_pf),
                  skip_median);
        stat_summary.cluster_count_pf(stat);
        stat.clear();
        nan_summarize(tile_data.begin(),
                  tile_data.end(),
                  stat,
                  util::op::const_member_function(&model::metrics::tile_metric::percent_pf),
                  util::op::const_member_function_less(&model::metrics::tile_metric::percent_pf),
                  skip_median);
        stat_summary.percent_pf(stat);
        stat_summary.reads(std::accumulate(tile_data.begin(),
                                           tile_data.end(),
                                           float(0),
                                           util::op::const_member_function(
                                                   &model::metrics::tile_metric::cluster_count)));
        stat_summary.reads_pf(std::accumulate(tile_data.begin(),
                                              tile_data.end(),
                                              float(0),
                                              util::op::const_member_function(
                                                      &model::metrics::tile_metric::cluster_count_pf)));
    }
    /** Update the stat summary with cached read metrics
     *
     * @param read_data_cache read metric cache
     * @param stat_summary stat summary
     * @param skip_median skip the median calculation
     * @return number of non-NaN aligned entries
     */
    inline size_t update_read_summary(summary_by_lane_read<model::metrics::read_metric>::vector_t& read_data_cache,
                               model::summary::stat_summary& stat_summary,
                               const bool skip_median)
    {
        model::summary::metric_stat stat;
        const size_t non_nan = nan_summarize(read_data_cache.begin(),
                                             read_data_cache.end(),
                                             stat,
                                             util::op::const_member_function(
                                                     &model::metrics::read_metric::percent_aligned),
                                             util::op::const_member_function_less(
                                                     &model::metrics::read_metric::percent_aligned),
                                             skip_median);
        stat_summary.percent_aligned(stat);
        stat.clear();
        nan_summarize(read_data_cache.begin(),
                      read_data_cache.end(),
                      stat,
                      util::op::const_member_function(&model::metrics::read_metric::percent_prephasing),
                      util::op::const_member_function_less(&model::metrics::read_metric::percent_prephasing),
                      skip_median);
        stat_summary.prephasing(stat);
        stat.clear();
        nan_summarize(read_data_cache.begin(),
                      read_data_cache.end(),
                      stat,
                      util::op::const_member_function(&model::metrics::read_metric::percent_phasing),
                      util::op::const_member_function_less(&model::metrics::read_metric::percent_phasing),
                      skip_median);
        stat_summary.phasing(stat);
        return non_nan;
    }
    /** Summarize a collection tile metrics
    *
    * @sa model::summary::lane_summary::density
    * @sa model::summary::lane_summary::density_pf
    * @sa model::summary::lane_summary::cluster_count
    * @sa model::summary::lane_summary::cluster_count_pf
    * @sa model::summary::lane_summary::percent_pf
    * @sa model::summary::lane_summary::reads
    * @sa model::summary::lane_summary::reads_pf
    * @sa model::summary::lane_summary::percent_aligned
    * @sa model::summary::lane_summary::prephasing
    * @sa model::summary::lane_summary::phasing
    *
    * @sa model::summary::read_summary::percent_aligned
    * @sa model::summary::run_summary::percent_aligned
    *
    * @param beg iterator to start of a collection of tile metrics
    * @param end iterator to end of a collection of tile metrics
    * @param naming_method tile naming convention
    * @param run destination run summary
    * @param skip_median skip the median calculation
    */
    template<typename I>
    void summarize_tile_metrics(I beg,
                                I end,
                                const constants::tile_naming_method naming_method,
                                model::summary::run_summary &run,
                                const bool skip_median=false)
                                    throw(model::index_out_of_bounds_exception)
    {
        typedef typename model::metrics::tile_metric::read_metric_vector read_metric_vector_t;
        typedef typename read_metric_vector_t::const_iterator const_read_metric_iterator;
        typedef std::vector<model::metrics::tile_metric> tile_vector_t;
        typedef std::vector<tile_vector_t> tile_by_lane_vector_t;

        if (beg == end) return;
        if (run.size() == 0)return;
        const size_t surface_count = run.surface_count();
        const ptrdiff_t n = std::distance(beg, end);

        tile_by_lane_vector_t tile_data_by_lane(run.lane_count());
        reserve(tile_data_by_lane.begin(), tile_data_by_lane.end(), n);
        tile_by_lane_vector_t tile_data_by_lane_surface(run.lane_count()*surface_count);
        reserve(tile_data_by_lane_surface.begin(), tile_data_by_lane_surface.end(), n);

        summary_by_lane_read<model::metrics::read_metric> read_data_by_lane_read(run, n);
        summary_by_lane_read<model::metrics::read_metric> read_data_by_surface_lane_read(run, n, surface_count);

        for (; beg != end; ++beg)
        {
            const size_t surface = beg->surface(naming_method);
            INTEROP_ASSERT(surface > 0);
            const size_t lane = beg->lane() - 1;
            if (lane >= tile_data_by_lane.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            tile_data_by_lane[beg->lane() - 1].push_back(*beg);// TODO: make more efficient by copying only tile data
            for (const_read_metric_iterator rb = beg->read_metrics().begin(), re = beg->read_metrics().end();
                 rb != re; ++rb)
            {
                const size_t read = rb->read() - 1;
                if (read >= read_data_by_lane_read.read_count())
                    INTEROP_THROW(model::index_out_of_bounds_exception,
                                  "Read exceeds read count in RunInfo.xml: "
                                          << read << " >= " << read_data_by_lane_read.read_count());
                read_data_by_lane_read(read, lane).push_back(*rb);
                if(surface_count < 2) continue;
                read_data_by_surface_lane_read(read, lane, surface-1).push_back(*rb);
            }
            if(surface_count < 2) continue;
            const size_t index = lane*surface_count+(surface-1);
            tile_data_by_lane_surface[index].push_back(*beg);// TODO: make more efficient by copying only tile data
        }


        //reads and reads pf
        // percent pf
        INTEROP_ASSERT(run.size() > 0);

        model::summary::metric_stat stat;
        for (size_t lane = 0; lane < run[0].size(); ++lane)
        {
            INTEROP_ASSERT(lane < tile_data_by_lane.size());
            INTEROP_ASSERT(lane < run[0].size());
            update_tile_summary_from_cache(tile_data_by_lane[lane], run[0][lane], skip_median);

            for (size_t read = 1; read < run.size(); ++read)
            {
                INTEROP_ASSERT(read < run.size());
                run[read][lane].density(run[0][lane].density());
                run[read][lane].density_pf(run[0][lane].density_pf());
                run[read][lane].cluster_count(run[0][lane].cluster_count());
                run[read][lane].cluster_count_pf(run[0][lane].cluster_count_pf());
                run[read][lane].percent_pf(run[0][lane].percent_pf());
                run[read][lane].reads(run[0][lane].reads());
                run[read][lane].reads_pf(run[0][lane].reads_pf());
            }
            if(surface_count < 2) continue;
            for(size_t surface=0;surface<surface_count;++surface)
            {

                update_tile_summary_from_cache(tile_data_by_lane_surface[lane * surface_count + surface],
                                               run[0][lane][surface], skip_median);
                for (size_t read = 1; read < run.size(); ++read)
                {
                    INTEROP_ASSERT(read < run.size());
                    run[read][lane][surface].density(run[0][lane][surface].density());
                    run[read][lane][surface].density_pf(run[0][lane][surface].density_pf());
                    run[read][lane][surface].cluster_count(run[0][lane][surface].cluster_count());
                    run[read][lane][surface].cluster_count_pf(run[0][lane][surface].cluster_count_pf());
                    run[read][lane][surface].percent_pf(run[0][lane][surface].percent_pf());
                    run[read][lane][surface].reads(run[0][lane][surface].reads());
                    run[read][lane][surface].reads_pf(run[0][lane][surface].reads_pf());
                }
            }
        }
        float percent_aligned = 0;
        size_t total = 0;
        float percent_aligned_nonindex = 0;
        size_t total_nonindex = 0;
        for (size_t read = 0; read < run.size(); ++read)
        {
            INTEROP_ASSERT(read < run.size());
            float percent_aligned_by_read = 0;
            size_t total_by_read = 0;
            for (size_t lane = 0; lane < run[read].size(); ++lane)
            {
                INTEROP_ASSERT(lane < run[0].size());
                const size_t non_nan = update_read_summary(read_data_by_lane_read(read, lane),
                                                           run[read][lane],
                                                           skip_median);
                INTEROP_ASSERT(!std::isnan(run[read][lane].percent_aligned().mean()));
                percent_aligned_by_read += run[read][lane].percent_aligned().mean() * non_nan;
                total_by_read += non_nan;
                if(surface_count < 2) continue;
                for(size_t surface=0;surface<surface_count;++surface)
                {
                    update_read_summary(read_data_by_surface_lane_read(read, lane, surface),
                                     run[read][lane][surface],
                                     skip_median);
                }
            }
            run[read].summary().percent_aligned(divide(percent_aligned_by_read, float(total_by_read)));
            percent_aligned += percent_aligned_by_read;
            total += total_by_read;
            if (!run[read].read().is_index())
            {
                percent_aligned_nonindex += percent_aligned_by_read;
                total_nonindex += total_by_read;
            }
        }
        run.nonindex_summary().percent_aligned(divide(percent_aligned_nonindex, static_cast<float>(total_nonindex)));
        run.total_summary().percent_aligned(divide(percent_aligned, static_cast<float>(total)));
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // IUO
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Summarize a collection extended tile metrics
     *
     * @note This must be called after summarize_tile_metrics!
     * @note IUO
     *
     * @param beg iterator to start of a collection of extended tile metrics
     * @param end iterator to end of a collection of extended tile metrics
     * @param naming_method tile naming convention
     * @param run destination run summary
     */
    template<typename I>
    void summarize_extended_tile_metrics(I beg,
                                         I end,
                                         const constants::tile_naming_method naming_method,
                                         model::summary::run_summary &run)
    throw(model::index_out_of_bounds_exception)
    {
        typedef std::vector<model::metrics::extended_tile_metric> tile_vector_t;
        typedef std::vector<tile_vector_t> tile_by_lane_vector_t;
        if (beg == end) return;
        if (run.size() == 0)return;
        const size_t surface_count = run.surface_count();
        const ptrdiff_t n = std::distance(beg, end);
        tile_by_lane_vector_t tile_data_by_lane(run.lane_count());
        reserve(tile_data_by_lane.begin(), tile_data_by_lane.end(), n);
        tile_by_lane_vector_t tile_data_by_lane_surface(run.lane_count()*surface_count);
        reserve(tile_data_by_lane_surface.begin(), tile_data_by_lane_surface.end(), n);

        for (; beg != end; ++beg)
        {
            const size_t surface = beg->surface(naming_method);
            INTEROP_ASSERT(surface > 0);
            const size_t lane = beg->lane() - 1;
            if (lane >= tile_data_by_lane.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            tile_data_by_lane[beg->lane() - 1].push_back(*beg);// TODO: make more efficient by copying only tile data
            if(surface_count < 2) continue;
            const size_t index = lane*surface_count+(surface-1);
            tile_data_by_lane_surface[index].push_back(*beg);// TODO: make more efficient by copying only tile data
        }


        model::summary::metric_stat count_stat;
        float total_cluster_occupied = 0;
        float total_cluster_count = 0;
        for (size_t lane = 0; lane < run[0].size(); ++lane)
        {
            INTEROP_ASSERT(lane < tile_data_by_lane.size());
            INTEROP_ASSERT(lane < run[0].size());

            tile_vector_t& tile_lane_data = tile_data_by_lane[lane];
            tile_vector_t::iterator tile_lane_end = util::remove_nan(tile_lane_data.begin(), tile_lane_data.end(),
                                                           util::op::const_member_function(&model::metrics::extended_tile_metric::cluster_count_occupied));
            const float occupied_mean =
                    util::mean<float>(tile_lane_data.begin(),
                                      tile_lane_end,
                                      util::op::const_member_function(
                                              &model::metrics::extended_tile_metric::cluster_count_occupied));
            count_stat = run[0][lane].cluster_count();
            run[0][lane].percent_occupied(divide(occupied_mean, count_stat.mean())*100);
            if(!std::isnan(count_stat.mean()) && !std::isnan(occupied_mean))
            {
                total_cluster_count += count_stat.mean();
                total_cluster_occupied += occupied_mean;
            }

            for (size_t read = 1; read < run.size(); ++read)
            {
                INTEROP_ASSERT(read < run.size());
                run[read][lane].percent_occupied(run[0][lane].percent_occupied());
            }
            if(surface_count < 2) continue;
            for(size_t surface=0;surface<surface_count;++surface)
            {
                tile_vector_t& tile_surface_data = tile_data_by_lane_surface[lane * surface_count + surface];
                tile_vector_t::iterator tile_surface_end = util::remove_nan(tile_surface_data.begin(), tile_surface_data.end(),
                                                               util::op::const_member_function(&model::metrics::extended_tile_metric::cluster_count_occupied));
                const float surface_occupied_mean =
                        util::mean<float>(tile_surface_data.begin(),
                                          tile_surface_end,
                                          util::op::const_member_function(
                                                  &model::metrics::extended_tile_metric::cluster_count_occupied));
                count_stat = run[0][lane][surface].cluster_count();
                run[0][lane][surface].percent_occupied(divide(surface_occupied_mean, count_stat.mean())*100);
                for (size_t read = 1; read < run.size(); ++read)
                {
                    INTEROP_ASSERT(read < run.size());
                    run[read][lane][surface].percent_occupied(run[0][lane][surface].percent_occupied());
                }
            }
        }
        for (size_t read = 0; read < run.size(); ++read)
        {
            run[read].summary().percent_occupied(divide(total_cluster_occupied, total_cluster_count)*100);
        }
        run.nonindex_summary().percent_occupied(divide(total_cluster_occupied, total_cluster_count)*100);
        run.total_summary().percent_occupied(divide(total_cluster_occupied, total_cluster_count)*100);
    }

   /** Summarize and aggregate a collection of compass tile metrics
    *
    * @sa model::summary::lane_summary::density
    * @sa model::summary::lane_summary::density_pf
    * @sa model::summary::lane_summary::prephasing
    * @sa model::summary::lane_summary::phasing
    *
    * @note IUO Compass Metrics
    *
    * @param beg iterator to start of a collection of tile metrics
    * @param end iterator to end of a collection of tile metrics
    * @param run destination run summary
    * @param skip_median skip the median calculation
    */
    template<typename I>
    void summarize_compass_tile_metrics(I beg,
                                        I end,
                                        model::summary::run_summary &run,
                                        const bool skip_median=false)
    throw(model::index_out_of_bounds_exception)
    {
        typedef typename model::metrics::tile_metric::read_metric_vector read_metric_vector_t;
        typedef typename read_metric_vector_t::const_iterator const_read_metric_iterator;
        typedef std::vector<model::metrics::tile_metric> tile_vector_t;
        typedef std::vector<tile_vector_t> tile_by_lane_vector_t;

        if (beg == end) return;
        if (run.size() == 0)return;
        const ptrdiff_t n = std::distance(beg, end);

        tile_by_lane_vector_t tile_data_by_lane(run.lane_count());
        reserve(tile_data_by_lane.begin(), tile_data_by_lane.end(), n);

        summary_by_lane_read<model::metrics::read_metric> read_data_by_lane_read(run, n);
        for (; beg != end; ++beg)
        {
            const size_t lane = beg->lane() - 1;
            if (lane >= tile_data_by_lane.size())
                INTEROP_THROW(model::index_out_of_bounds_exception, "Lane exceeds lane count in RunInfo.xml");
            tile_data_by_lane[lane].push_back(*beg);// TODO: make more efficient by copying only tile data
            for (const_read_metric_iterator rb = beg->read_metrics().begin(), re = beg->read_metrics().end();
                 rb != re; ++rb)
            {
                const size_t read = rb->read() - 1;
                if (read >= read_data_by_lane_read.read_count())
                    INTEROP_THROW(model::index_out_of_bounds_exception, "Read exceeds read count in RunInfo.xml");
                read_data_by_lane_read(read, lane).push_back(*rb);
            }
        }


        //density and density pf
        INTEROP_ASSERT(run.size() > 0);
        model::summary::metric_stat stat;
        model::summary::metric_stat stat_pf;
        float density = 0;
        float density_total = 0;
        float density_pf = 0;
        float density_total_pf = 0;
        for (size_t read = 0; read < run.size(); ++read)
        {
            INTEROP_ASSERT(read < run.size());
            float density_by_read = 0;
            float total_by_read = 0;
            float density_by_read_pf = 0;
            float total_by_read_pf = 0;
            for (size_t lane = 0; lane < run[read].size(); ++lane)
            {
                INTEROP_ASSERT(lane < tile_data_by_lane.size());
                INTEROP_ASSERT(lane < run[0].size());
                nan_summarize(tile_data_by_lane[lane].begin(), tile_data_by_lane[lane].end(), stat,
                          util::op::const_member_function(&model::metrics::tile_metric::cluster_density),
                          util::op::const_member_function_less(&model::metrics::tile_metric::cluster_density),
                          skip_median);
                run[read][lane].density(stat);
                density_by_read += stat.mean();
                total_by_read++;

                nan_summarize(tile_data_by_lane[lane].begin(), tile_data_by_lane[lane].end(),
                          stat_pf, util::op::const_member_function(&model::metrics::tile_metric::cluster_density_pf),
                          util::op::const_member_function_less(&model::metrics::tile_metric::cluster_density_pf),
                          skip_median);
                run[read][lane].density_pf(stat_pf);
                density_by_read_pf += stat_pf.mean();
                total_by_read_pf++;
            }
            run[read].summary().cluster_density(divide(density_by_read, total_by_read));
            run[read].summary().cluster_density_pf(divide(density_by_read_pf, total_by_read_pf));
            density += density_by_read;
            density_total += total_by_read;
            density_pf += density_by_read_pf;
            density_total_pf += total_by_read_pf;
        }
        run.total_summary().cluster_density(divide(density, density_total));
        run.total_summary().cluster_density_pf(divide(density_pf, density_total_pf));


        model::summary::metric_stat stat_phasing;
        model::summary::metric_stat stat_prephasing;
        float phasing = 0;
        float phasing_total = 0;
        float prephasing = 0;
        float prephasing_total = 0;
        for (size_t read = 0; read < run.size(); ++read)
        {
            float phasing_by_read = 0;
            float total_phasing_by_read = 0;
            float prephasing_by_read = 0;
            float total_prephasing_by_read = 0;
            INTEROP_ASSERT(read < run.size());
            for (size_t lane = 0; lane < run[read].size(); ++lane)
            {
                INTEROP_ASSERT(lane < run[0].size());
                if(0 == nan_summarize(read_data_by_lane_read(read, lane).begin(),
                              read_data_by_lane_read(read, lane).end(), stat_phasing,
                              util::op::const_member_function(&model::metrics::read_metric::percent_phasing),
                              util::op::const_member_function_less(&model::metrics::read_metric::percent_phasing),
                                      skip_median))
                {
                    run[read][lane].phasing(std::numeric_limits<float>::quiet_NaN());
                }
                else
                {
                    run[read][lane].phasing(stat_phasing);
                    phasing_by_read += stat_phasing.mean();
                    total_phasing_by_read++;
                }

                if(0 == nan_summarize(read_data_by_lane_read(read, lane).begin(),
                              read_data_by_lane_read(read, lane).end(), stat_prephasing,
                              util::op::const_member_function(&model::metrics::read_metric::percent_prephasing),
                              util::op::const_member_function_less(&model::metrics::read_metric::percent_prephasing),
                                      skip_median))
                {
                    run[read][lane].prephasing(std::numeric_limits<float>::quiet_NaN());
                }

                else
                {
                    run[read][lane].prephasing(stat_prephasing);
                    prephasing_by_read += stat_prephasing.mean();
                    total_prephasing_by_read++;
                }
            }

            run[read].summary().phasing(divide(phasing_by_read, total_phasing_by_read));
            run[read].summary().prephasing(divide(prephasing_by_read, total_prephasing_by_read));
            phasing += phasing_by_read;
            phasing_total += total_phasing_by_read;
            prephasing += prephasing_by_read;
            prephasing_total += total_prephasing_by_read;
        }
        run.total_summary().phasing(divide(phasing, phasing_total));
        run.total_summary().prephasing(divide(prephasing, prephasing_total));
     }

}}}}

