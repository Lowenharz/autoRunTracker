/** Summary statistics by read, total and non-indexed
 *
 *  @file
 *  @date  3/14/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/io/format/generic_layout.h"

namespace illumina { namespace interop { namespace model { namespace summary {

    /**  Summary statistics by read, total and non-indexed
     *
     * @todo: use this is lane_summary too
     */
    class metric_summary
    {

    public:
        typedef std::vector<float> float_vector_t; /** IUO */

    public:
        /** Constructor
         */
        metric_summary(const size_t channel_count) :
                m_error_rate(std::numeric_limits<float>::quiet_NaN()),
                m_percent_aligned(0), // TODO: Update logic to allow this to be NaN!
                m_first_cycle_intensity(std::numeric_limits<float>::quiet_NaN()),
                m_percent_gt_q30(std::numeric_limits<float>::quiet_NaN()),
                m_yield_g(0), // TODO: Update logic to allow this to be NaN!
                m_projected_yield_g(0), // TODO: Update logic to allow this to be NaN!
                /** IUO **/
                m_percent_gt_q30_last_10_cycles(std::numeric_limits<float>::quiet_NaN()),
                m_percent_occupied(std::numeric_limits<float>::quiet_NaN()),
                m_theta_z(std::numeric_limits<float>::quiet_NaN()),
                m_theta(std::numeric_limits<float>::quiet_NaN()),
                /** Compass **/
                m_cluster_density(std::numeric_limits<float>::quiet_NaN()),
                m_cluster_density_pf(std::numeric_limits<float>::quiet_NaN()),
                m_percent_base(constants::NUM_OF_BASES, std::numeric_limits<float>::quiet_NaN()),
                m_phasing(std::numeric_limits<float>::quiet_NaN()),
                m_prephasing(std::numeric_limits<float>::quiet_NaN()),
                m_percent_no_call(std::numeric_limits<float>::quiet_NaN()),
                m_fwhm(channel_count, std::numeric_limits<float>::quiet_NaN()),
                m_resynthesis(channel_count, std::numeric_limits<float>::quiet_NaN())

        {}
    public:
        /** @defgroup metric_summary Metric summary
         *
         * Summary of key metrics
         *
         * @ingroup run_summary
         * @ref illumina::interop::model::summary::metric_summary "See full class description"
         * @{
         */
        /** Get the error rate of PHIX for the run over all "usable cycles".
         *
         * A "usable cycle" is a cycle that is fully corrected, so the last cycle of a read is excluded.
         *
         * @return error rate of PHIX for run over all "usable cycles".
         */
        float error_rate()const
        {
            return m_error_rate;
        }
        /** Get the percent aligned PHIX for the run
         *
         * @return percent aligned PHIX
         */
        float percent_aligned()const
        {
            return m_percent_aligned;
        }
        /** Get the first cycle intensity
         *
         * @return first cycle intensity
         */
        float first_cycle_intensity()const
        {
            return m_first_cycle_intensity;
        }
        /** Get the percent of bases greater than or equal to Q30 over all "usable cycles"
         *
         * A "usable cycle" is a cycle that is fully corrected, so the last cycle of a read is excluded.
         *
         * @return percent of bases greater than or equal to Q30 over all "usable cycles"
         */
        float percent_gt_q30()const
        {
            return m_percent_gt_q30;
        }
        /** Get the yield of the run in gigabases over all "usable cycles"
         *
         * A "usable cycle" is a cycle that is fully corrected, so the last cycle of a read is excluded.
         *
         * @return yield of the run in gigabases over all "usable cycles"
         */
        float yield_g()const
        {
            return m_yield_g;
        }

        /** Get the projected yield of the run in gigabases over all "usable cycles"
         *
         * A "usable cycle" is a cycle that is fully corrected, so the last cycle of a read is excluded.
         *
         * @return projected yield of the run in gigabases over all "usable cycles"
         */
        float projected_yield_g()const
        {
            return m_projected_yield_g;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IUO
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /** Get the percent of bases greater than or equal to Q30 in the last 10 usable cycles of each read
         *
         * @return percent of bases greater than or equal to Q30 in the last 10 usable cycles of each read
         */
        float percent_gt_q30_last_10_cycles()const
        {
            return m_percent_gt_q30_last_10_cycles;
        }
        /** Get the percent occupied
         *
         * @return percent occupied
         */
        float percent_occupied()const
        {
            return m_percent_occupied;
        }
        /** Get the average rotation around the z-axis
         *
         * @return average rotation around the z-axis
         */
        float theta_z()const
        {
            return m_theta_z;
        }
        /** Get the average rotation of the affine transform
         *
         * @return average rotation of the affine transform
         */
        float theta()const
        {
            return m_theta;
        }
        
        /** @} */
        /** Set the first cycle intensity
         *
         * @param val first cycle intensity
         */
        void first_cycle_intensity(const float val)
        {
            m_first_cycle_intensity = val;
        }
        /** Set the error rate of PHIX for the run
         *
         * @param val error rate of PHIX for run
         */
        void error_rate(const float val)
        {
            m_error_rate = val;
        }
        /** Set the percent aligned PHIX for the run
         *
         *  @param val percent aligned PHIX
         */
        void percent_aligned(const float val)
        {
            m_percent_aligned = val;
        }
        /** Set the percent of bases greater than or equal to Q30
         *
         * @param val percent of bases greater than or equal to Q30
         */
        void percent_gt_q30(const float val)
        {
            m_percent_gt_q30 = val;
        }

        /** Set the yield of the run in gigabases
         *
         * @param val yield of the run in gigabases
         */
        void yield_g(const float val)
        {
            m_yield_g = val;
        }
        /** Set the projected yield of the run in gigabases
         *
         * @param val projected yield of the run in gigabases
         */
        void projected_yield_g(const float val)
        {
            m_projected_yield_g = val;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IUO
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /** Set the percent of bases greater than or equal to Q30 in the last 10 usable cycles of each read in the run
         *
         * @param val percent of bases greater than or equal to Q30 in the last 10 usable cycles of each read in the run
         */
        void percent_gt_q30_last_10_cycles(const float val)
        {
            m_percent_gt_q30_last_10_cycles = val;
        }
        /** Set the percent occupied
         *
         * @param val percent occupied
         */
        void percent_occupied(const float val)
        {
            m_percent_occupied = val;
        }

        /** Set the average rotation around the z-axis
         *
         * @param val average rotation around the z-axis
         */
        void theta_z(const float val)
        {
            m_theta_z = val;
        }
        /** Set the average rotation of the affine transform
         *
         * @param val average rotation of the affine transform
         */
        void theta(const float val)
        {
            m_theta = val;
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Compass
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /** Get the percent PF
         *
         * @return percent PF
         */
        float percent_pf()const
        {
            return m_cluster_density_pf/m_cluster_density*100.0f;
        }
        /** Get the cluster density
         *
         * @return cluster density
         */
        float cluster_density()const
        {
            return m_cluster_density;
        }

        /** Get the cluster density PF
         *
         * @return cluster density PF
         */
        float cluster_density_pf()const
        {
            return m_cluster_density_pf;
        }
        /** Get the percent bases by base
         *
         * @return % bases by base
         */
        const float_vector_t& percent_base()const
        {
            return m_percent_base;
        }

        /** Get the phasing value for read
         *
         * @return phasing val
         */
        float phasing()const
        {
            return m_phasing;
        }

        /** Get the prephasing value for read
         *
         * @return prephasing val
         */
        float prephasing()const
        {
            return m_prephasing;
        }

        /** Get the percent no call value for run
         *
         * @return % no call val for run
         */
        float percent_no_call()const
        {
            return m_percent_no_call;
        }

        /** Get the FWHM value for the read / run
         *
         * @return FWHM value for read / run
         */
        const float_vector_t& fwhm()const
        {
            return m_fwhm;
        }

        /** Get the resynthesis value for the run
         *
         * @return resynthesis rate
         */
        const float_vector_t& resynthesis()const
        {
            return m_resynthesis;
        }

        /** Set the FWHM value for the read / run
         *
         * @param channel index of channel
         * @param val FWHM value for read / run
         */
        void fwhm(const size_t channel, const float val)
        {
            INTEROP_ASSERTMSG(channel < m_fwhm.size(), channel << " < " << m_fwhm.size());
            m_fwhm[channel] = val;
        }

        /** Set the resynthesis value (proportion of read 1 cycle 1 to read 2 cycle 1)
         *
         * @param channel channel index
         * @param val resynthesis rate
         */
        void resynthesis(const size_t channel, const float val)
        {
            INTEROP_ASSERTMSG(channel < m_resynthesis.size(), channel << " < " << m_resynthesis.size());
            m_resynthesis[channel] = val;
        }

        /** Set the percent base by base
         *
         * @param channel channel index
         * @param val percent base by base
         */
        void percent_base(const size_t channel, const float val)
        {
            INTEROP_ASSERTMSG(channel < m_percent_base.size(), channel << " < " << m_percent_base.size());
            m_percent_base[channel] = val;
        }

        /** Set the phasing value of the read
         *
         * @param val phasing value of read
         */
        void phasing(const float val)
        {
            m_phasing = val;
        }

        /** Set the prephasing value of the read
         *
         * @param val prephasing value of read
         */
        void prephasing(const float val)
        {
            m_prephasing = val;
        }

        /** Set the no call percent for the run
         *
         * @param val no call percent for run
         */
        void percent_no_call(const float val)
        {
            m_percent_no_call = val;
        }
        /** Set the cluster density of the run
         *
         * @param val cluster density of the run.
         */
        void cluster_density(const float val)
        {
            m_cluster_density = val;
        }
        /** Set the cluster density PF of the run
         *
         * @param val cluster density PF of the run.
         */
        void cluster_density_pf(const float val)
        {
            m_cluster_density_pf = val;
        }
        /** Resize the underlying arrays
         *
         * @param channel_count channel count
         */
        void resize(const size_t channel_count)
        {
            const float kNaN = std::numeric_limits<float>::quiet_NaN();
            m_fwhm.resize(channel_count, kNaN);
            m_resynthesis.resize(channel_count, kNaN);
        }

    private:
        float m_error_rate;
        float m_percent_aligned;
        float m_first_cycle_intensity;
        float m_percent_gt_q30;
        float m_yield_g;
        float m_projected_yield_g;

        // IUO
        float m_percent_gt_q30_last_10_cycles;
        float m_percent_occupied;
        float m_theta_z;
        float m_theta;

        // Compass
        float m_cluster_density;
        float m_cluster_density_pf;
        float_vector_t m_percent_base;
        float m_phasing;
        float m_prephasing;
        float m_percent_no_call;
        float_vector_t m_fwhm;
        float_vector_t m_resynthesis;
        template<class MetricType, int Version>
        friend struct io::generic_layout;
    };



}}}}

