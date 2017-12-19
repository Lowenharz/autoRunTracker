/** Event metric
 *
 * The InterOp files parsed by this class include:
 *  - InterOp/EventMetrics.bin
 *  - InterOp/EventMetricsOut.bin
 *
 *  @file
 *  @date 6/28/2016
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <ctime>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "interop/util/exception.h"
#include "interop/util/time.h"
#include "interop/io/format/generic_layout.h"
#include "interop/model/metric_base/metric_set.h"

namespace illumina { namespace interop { namespace model { namespace metrics
{
    /** Event metrics
     *
     * @note Supported versions: 1 and 2
     */
    class event_metric : public metric_base::base_event_metric
    {
    public:
        enum
        {
            /** Unique type code for metric */
            TYPE = constants::Event,
            /** Latest version of the InterOp format */
            LATEST_VERSION = 2
        };

        /** Defines uint_t type */
        typedef ::uint32_t uint_t;

        /** Defines ulong_t type */
        typedef ::uint64_t ulong_t;

        /** Define map between read ids and read metrics */
        typedef std::vector<event_metric> event_metric_vector;

        /** Define a const read iterator */
        typedef event_metric_vector::const_iterator const_iterator;

    public:

        /** Default Constructor
         *
         */
        event_metric() : metric_base::base_event_metric(0, 0, 0, constants::UnknownEvent),
                         m_date_time(0),
                         m_point_ticks(0),
                         m_date_time_csharp(0),
                         m_event_value(0),
                         m_elapsed_ms(0),
                         m_elapsed_ticks(0)
        { }
        /** Constructor
         */
        event_metric(const header_type&) : metric_base::base_event_metric(0, 0, 0, constants::UnknownEvent),
                m_date_time(0),
                m_point_ticks(0),
                m_date_time_csharp(0),
                m_event_value(0),
                m_elapsed_ms(0),
                m_elapsed_ticks(0)
        { }

        /** Constructor
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param date_time date time (C++ time)
         * @param event_type event type enumeration
         * @param elapsed_ms elapsed milliseconds
         * @param event_value value returned from an event (if applicable)
         * @param point_ticks point ticks
         * @param elapsed_ticks elapsed ticks on clock
         */
        event_metric(const uint_t lane,
                     const uint_t tile,
                     const uint_t cycle,
                     const ulong_t date_time,
                     const constants::event_type event_type,
                     const double elapsed_ms,
                     const uint_t event_value=0,
                     const ulong_t point_ticks=0,
                     const ulong_t elapsed_ticks=0
        ) :
                metric_base::base_event_metric(lane, tile, cycle, event_type),
                m_date_time(date_time),
                m_point_ticks(point_ticks),
                m_date_time_csharp(util::csharp_date_time::to_csharp(date_time)),
                m_event_value(event_value),
                m_elapsed_ms(elapsed_ms),
                m_elapsed_ticks(elapsed_ticks)
        { }

    public:
        /** Setter
         *
         * @note Version 2
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param date_time date time (C++ time)
         * @param event_type event type enumeration
         * @param event_value value returned from an event (if applicable)
         */
        void set(const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const ulong_t date_time,
                 const constants::event_type event_type,
                 const uint_t event_value)
        {
            metric_base::base_event_metric::set_base(lane, tile, cycle, event_type);
            m_date_time = date_time;
            m_point_ticks = 0;
            m_date_time_csharp = util::csharp_date_time::to_csharp(date_time);
            m_event_value = event_value;
            m_elapsed_ms = 0;
            m_elapsed_ticks = 0;
        }
        /** Setter
         *
         * @note Version 1
         * @param date_time date and time (C++ time)
         * @param point_ticks point ticks
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param event_type event type number/code
         * @param event_value value returned from an event (if applicable)
         * @param elapsed_ms elapsed milliseconds
         * @param elapsed_ticks elapsed ticks on clock
         */
        void set(const ulong_t date_time,
                 const ulong_t point_ticks,
                 const uint_t lane,
                 const uint_t tile,
                 const uint_t cycle,
                 const constants::event_type event_type,
                 const uint_t event_value,
                 const double elapsed_ms,
                 const ulong_t elapsed_ticks)
        {
            metric_base::base_event_metric::set_base(lane, tile, cycle, event_type);
            m_date_time = date_time;
            m_point_ticks = point_ticks;
            m_date_time_csharp = util::csharp_date_time::to_csharp(date_time);
            m_event_value = event_value;
            m_elapsed_ms = elapsed_ms;
            m_elapsed_ticks = elapsed_ticks;
        }

        /** Set the base event metric identifiers
        *
        * @param base layout base
        */
        template<class BaseEventMetric>
        void set_base(const BaseEventMetric &base)
        {
            typedef typename BaseEventMetric::base_t layout_base_t;
            metric_base::base_event_metric::set_base(base);
            set_base_workaround(base, layout_base_t::null());
        }
        /** Set id
         *
         * @note This is only supported to enable easier unit testing, this should not be used.
         * @param lane lane number
         * @param tile tile number
         */
        void set_base(const uint_t lane, const uint_t tile)
        {
            metric_base::base_cycle_metric::set_base(lane, tile);
        }
        /** Create unique id from the lane, tile, cycle and event type
         *
         * @param lane lane number
         * @param tile tile number
         * @param cycle cycle number
         * @param event_type event type
         * @return unique id
         */
        static id_t create_id(const id_t lane, const id_t tile, const id_t cycle, const id_t event_type=0)
        {
            // The cycle number is most metrics is a 32-bit integer. Here the full 32-bit cycle integer is divided into
            // two 16-bit integers: event_type, cycle
            return metric_base::base_cycle_metric::create_id(lane, tile, cycle) | event_type;
        }
        /** Get the cycle from the unique lane/tile/cycle id
         *
         * @param id unique lane/tile/cycle id
         * @return cycle number
         */
        static id_t event_from_id(const id_t id)
        {
            // 1. Shift off lane, tile, and cycle
            // 2. Shift back
            return (id << (LANE_BIT_COUNT+TILE_BIT_COUNT+CYCLE_BIT_COUNT)) >> (LANE_BIT_COUNT+TILE_BIT_COUNT+CYCLE_BIT_COUNT);
        }

    private:
        template<class BaseEventMetric>
        void set_base_workaround(const BaseEventMetric &base, const constants::base_event_v1_t::pointer_t)
        {
            m_date_time = base.date_time;
            m_point_ticks = base.point_ticks;
            event_type(static_cast<constants::event_type>(base.event_type));
        }
        template<class BaseEventMetric>
        void set_base_workaround(const BaseEventMetric &, const void*){}

    public:
        /** @defgroup event_metric Event Metrics
         *
         * Per tile per cycle per event metric
         *
         * @ref illumina::interop::model::metrics::event_metric "See full class description"
         *
         * @ingroup run_metrics
         * @note All metrics in this class are supported by all versions
         */

        /** Get time stamp
         *
         * @note supported by all versions
         * @return date_time
         */
        ulong_t date_time() const
        {
            return m_date_time;
        }

        /** Get number of point ticks
         *
         * note supported by version 1
         * @return point_ticks
         */
        ulong_t point_ticks() const
        {
            return m_point_ticks;
        }
        /**
         * @note C# DataTime.ToBinary int64 format
         *
         * @return date time code
         */
        const util::csharp_date_time &date_time_csharp() const
        {
            return m_date_time_csharp;
        }

        /** Get the value corresponding to the event type
         *
         * @note supported by all versions
         * @return value corresponding to the event
         */
        uint_t event_value() const
        {
            return m_event_value;
        }

        /** Get the number of milliseconds that have elapsed
         *
         * @note supported by version 1
         * @return elapsed milliseconds
         */
        double elapsed_ms() const
        {
            return m_elapsed_ms;
        }

        /** Get the number of elapsed ticks
         *
         * @note supported by version 1
         * @return elapsed ticks
         */
        ulong_t elapsed_ticks() const
        {
            return m_elapsed_ticks;
        }

    public:
        /** Get the prefix of the InterOp filename
         *
         * @return prefix
         */
        static const char *prefix()
        { return "Event"; }


    private:
        ulong_t m_date_time; //C++ time
        ulong_t m_point_ticks;
        util::csharp_date_time m_date_time_csharp;
        uint_t m_event_value;
        double m_elapsed_ms;
        ulong_t m_elapsed_ticks;

        template<class MetricType, int Version>
        friend
        struct io::generic_layout;
    };
}}}}

