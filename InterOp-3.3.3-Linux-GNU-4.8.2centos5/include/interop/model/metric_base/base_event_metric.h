/** Base information shared by per cycle tile metrics
 *
 * Per cycle tile metrics include any metric calculated for a specific tile at a given cycle.
 *
 *  @file
 *  @date 8/5/2015
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <algorithm>
#include "interop/util/type_traits.h"
#include "interop/model/metric_base/base_cycle_metric.h"


namespace illumina { namespace interop { namespace model { namespace metric_base
{
    /** Defines default base header for metric */
    class base_event_metric_header : public empty_header
    {
    public:
        /** Define the base type */
        typedef constants::base_event_v2_t base_t;
        typedef base_metric::uint_t uint_t;
    public:
        /** Constructor */
        base_event_metric_header() : m_max_cycle(0)
        {}

    public:
        /** Generate a default header
         *
         * @return default header
         */
        static base_event_metric_header default_header()
        {
            return base_event_metric_header();
        }

    public:
        /** Get cycle
         *
         * @return cycle
         */
        base_metric::uint_t max_cycle() const
        { return m_max_cycle; }

        /** Clear the max_cycle
         */
        void clear()
        {
            m_max_cycle = 0;
        }

    protected:
        /** Update the max cycle
         *
         * @param metric cycle metric
         */
        template<class Metric>
        inline void update_max_cycle(const Metric &metric)
        {
            m_max_cycle = std::max(m_max_cycle, metric.cycle());
        }

    private:
        /** Maximum cycle read **/
        uint_t m_max_cycle;
    };

    /** Base class for InterOp classes that contain per cycle tile specific metrics
                 *
                 * These classes define both a lane, tile and cycle identifier.
                 */
    class base_event_metric : public base_cycle_metric
    {
    public:
        /** An event metric_set header
         */
        typedef base_event_metric_header header_type;
        /** Define the base type */
        typedef constants::base_event_v2_t base_t;
    public:
        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param event_type event type
         */
        base_event_metric(const uint_t lane = 0, const uint_t tile = 0, const uint_t cycle = 0,
                          const constants::event_type event_type = constants::UnknownEvent) :
                base_cycle_metric(lane, tile, cycle), m_event_type(event_type)
        {}

    public:
        /** Set id
         *
         * @note This is only supported to enable easier unit testing, this should not be used.
         * @param lane lane number
         * @param tile tile number
         */
        void set_base(const uint_t lane, const uint_t tile)
        {
            base_metric::set_base(lane, tile);
        }

        /** Set id
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param event_type event type
         */
        void set_base(const uint_t lane, const uint_t tile, const uint_t cycle, const constants::event_type event_type)
        {
            base_cycle_metric::set_base(lane, tile, cycle);
            m_event_type = event_type;
        }

        /** Set the base metric identifiers
         *
         * @param base layout base
         */
        template<class BaseEventMetric>
        void set_base(const BaseEventMetric &base)
        {
            base_cycle_metric::set_base(base);
            m_event_type = static_cast<constants::event_type>(base.event_type);
        }

        /** Event type
         *
         * @return event type
         */
        constants::event_type event_type() const
        { return m_event_type; }

        /** Event type
         *
         * @return event type, cast to a 64-bit uint
         */
        ::uint64_t event_type_long() const
        { return static_cast< ::uint64_t >(m_event_type); }


        /** Event type
        *
        * @return event type
        */
        void event_type(const constants::event_type event_type)
        { m_event_type = event_type; }

        /** Unique id created from the lane, tile, cycle, and event type
         *
         * @return unique id
         */
        id_t id() const
        {
            return create_id(lane(), tile(), cycle(), static_cast<id_t>(m_event_type));
        }

        /** Create unique id from the lane, tile and cycle
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param event_type type of event
         * @return unique id
         */
        static id_t create_id(const id_t lane, const id_t tile, const id_t cycle, const id_t event_type)
        {
            return base_cycle_metric::create_id(lane, tile, cycle) | (event_type << EVENT_BIT_SHIFT);
        }

    private:
        constants::event_type m_event_type;
    };


    /** Specialization for base_cycle_metric providing sentinel values*/
    template<>
    struct metric_attributes<base_event_metric> : public metric_attributes<base_metric>{};


}}}}
