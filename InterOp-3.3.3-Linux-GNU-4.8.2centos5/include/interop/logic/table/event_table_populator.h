/** Logic to populate the event table
 *
 *  @file
 *  @date  7/22/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <vector>
#include <string>
#include "interop/util/exception.h"
#include "interop/util/constant_mapping.h"
#include "interop/util/string.h"
#include "interop/util/length_of.h"
#include "interop/constants/enums.h"
#include "interop/model/run_metrics.h"
#include "interop/model/model_exceptions.h"
#include "interop/model/table/event_column.h"
#include "interop/model/table/event_table.h"
#include "interop/logic/utils/enums.h"
#include "interop/logic/table/table_util.h"
#include "interop/logic/table/create_event_table_columns.h"

namespace illumina { namespace interop { namespace logic { namespace table
{
    /** Populate a table with data from a single InterOp
     */
    class table_populator
    {
        enum VoidType
        {
            Void
        };
    public:
        /** Populate the ID columns of the table
         *
         * @param metric metric with source data
         * @param naming_method tile naming method enum
         * @param columns vector of table columns
         * @param data_it iterator to current row of table data
         * @param data_end iterator to end of table data
         */
        template<class Metric, typename OutputIterator>
        static void populate_id(const Metric &metric,
                                const constants::tile_naming_method naming_method,
                                const std::vector <size_t> &columns,
                                OutputIterator data_it, OutputIterator data_end)
        {
            populate(static_cast<const model::metric_base::base_metric &>(metric),
                     naming_method,
                     columns,
                     data_it,
                     data_end);
            populate(static_cast<const model::metric_base::base_cycle_metric &>(metric),
                     naming_method,
                     columns,
                     data_it,
                     data_end);
            populate(static_cast<const model::metric_base::base_event_metric &>(metric),
                     naming_method,
                     columns,
                     data_it,
                     data_end);
            (void) data_end;
        }

        /** Populate the data columns of the table
         *
         * @param metric metric with source data
         * @param naming_method tile naming method enum
         * @param columns vector of table columns
         * @param data_it iterator to current row of table data
         * @param data_end iterator to end of table data
         */
        template<class Metric, typename OutputIterator>
        static void populate(const Metric &metric,
                             const constants::tile_naming_method naming_method,
                             const std::vector <size_t> &columns,
                             OutputIterator data_it, OutputIterator data_end)
        {
            /* For every entry in INTEROP_EVENT_COLUMN_TYPES
             * Add a method call to update each field with the given `metric`
             *
             * Example:
             * INTEROP_TUPLE7(Lane, metric_base::base_metric, lane, Void, UInt, IdType) ->
             *
             * update_laneVoid(metric, q20_idx, q30_idx, naming_convention);
             */
#           define INTEROP_TUPLE7(Ignore1, Ignore2, Method, Param, Ignore4, Ignore5, Ignored6) \
                    populate_##Method##Param(metric, naming_method, columns, data_it, data_end);
            INTEROP_EVENT_COLUMN_TYPES
#           undef INTEROP_TUPLE7 // Reuse this for another conversion
        }

    private:
        /* For every entry in INTEROP_EVENT_COLUMN_TYPES
         * This macro creates two functions, one to populate a field/column with the data from the correspond metric
         * and an empty method to ignore a group
         *
         * Example:
         * INTEROP_TUPLE7(Lane, metric_base::base_metric, lane, Void, UInt, IdType) ->
         *
         * void update_laneVoid(const model::metric_base::base_metric& metric, const size_t Q20, const size_t Q30, const naming_method NamingConvention)
         * void update_laneVoid(const model::metric_base::empty_metric&)
         *
         * @note Param can be can field in this class, e.g. Read, or the function parameters Q20, Q30 or NamingConvention
         */
#       define INTEROP_TUPLE7(Id, Metric, Method, Param, Type, Kind, Round) \
                template<typename OutputIterator>\
                static void populate_##Method##Param(const model:: Metric& metric,\
                                                     const constants::tile_naming_method NamingConvention,\
                                                     const std::vector<size_t>& columns,\
                                                     OutputIterator data_it, OutputIterator data_end)\
                {\
                    INTEROP_ASSERT( model::table:: Id##EventColumn < columns.size() ); \
                    const size_t index = columns[model::table:: Id##EventColumn];\
                    if(!is_valid(index)) return; /*Missing column */ \
                    copy_to(data_it+index, data_end, call_adapter(metric, Param, &model:: Metric::Method));\
                    (void)NamingConvention;\
                }\
                template<class MetricType, typename OutputIterator>\
                static void populate_##Method##Param(const MetricType&,\
                                                     const constants::tile_naming_method,\
                                                     const std::vector<size_t>&,\
                                                     OutputIterator,OutputIterator){}
        INTEROP_EVENT_COLUMN_TYPES
#       undef INTEROP_TUPLE7 // Reuse this for another conversion

    private:
        /** Assign a value to an iterator
         *
         * @param destination reference to iterator value
         * @param end iterator to end of destination collection
         * @param source  value to assign
         * @param num_digits number of digits after the decimal
         */
        template<typename T, typename U>
        static void assign(T &destination, const U source)
        {
            if(is_valid(source))
                destination = static_cast<T>(source);
        }

    private:
        /** Assign a value to an iterator
         *
         * @param destination iterator to desination collection
         * @param end iterator to end of destination collection
         * @param source  value to assign
         * @param num_digits number of digits after the decimal
         */
        template<typename OutputIterator, typename U>
        static void copy_to(OutputIterator destination, OutputIterator end, const U source)
        {
            INTEROP_ASSERT(destination < end);
            (void) end;
            assign(*destination, source);
        }

        /** Test if a metric type is valid
         *
         * @param val integral value
         * @return true
         */
        template<typename T>
        static bool is_valid(const T val)
        {
            return val < std::numeric_limits<T>::max();
        }
    };
}}}}

