/** Model for the imaging table column
 *
 *  @file
 *  @date  7/20/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <string>
#include <iosfwd>
#include <vector>
#include "interop/util/assert.h"
#include "interop/util/length_of.h"
#include "interop/util/string.h"
#include "interop/constants/enums.h"
#include "interop/logic/utils/enums.h"
#include "interop/model/table/table_exceptions.h"


/** Mapping of data for the imaging table
 *
 * Column 1:
 *  - Name of the field in the table_entry class
 *  - Converted to column header in imaging table
 *  - Suffixed with 'Column' when used as an enum, e.g. Lane -> LaneColumn
 * Column 2:
 *  - metric that holds the column data
 * Column 3:
 *  - method in metric that holds the column data
 * Column 4:
 *  - Parameter taken by metric method
 *      e.g. percent_aligned requires a read number, which can be taken from table_entry
 *      e.g. percent_over_qscore needs to know the index of the bin to use
 *      e.g. surface needs to know the tile naming convention to properly parse the name
 * Column 5:
 *  - Data type for the field in table_entry
 * Column 6:
 *  - Flag for properties for this field
 * Column 7:
 *  - Number of decimal places to round to
 *
 *  The metrics marked "dummy" are populated not in the update function, but in the constructor.
 *
 * @note This macro requires the macro INTEROP_TUPLE7 to be defined before use
 * @see illumina::interop::model::table::table_entry
 * @see illumina::interop::logic::table::imaging_table_column_names
 */
#define INTEROP_EVENT_COLUMN_TYPES \
        INTEROP_TUPLE7(Lane,          metric_base::base_metric,        lane,              Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(Tile,          metric_base::base_metric,        tile,              Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(Cycle,         metric_base::base_cycle_metric,  cycle,             Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(ElapsedTicks,  metrics::event_metric,           elapsed_ticks,     Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(Event,         metric_base::base_event_metric,  event_type_long,   Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(PointTicks,    metrics::event_metric,           point_ticks,       Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(PointTime,     metrics::event_metric,           date_time,         Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(Value,         metrics::event_metric,           event_value,       Void, UInt, IdType, 0)\
        INTEROP_TUPLE7(Surface,       metric_base::base_metric,        surface,           NamingConvention, UInt, IdType, 0)\
        INTEROP_TUPLE7(Swath,         metric_base::base_metric,        swath,             NamingConvention, UInt, IdType, 0)\
        INTEROP_TUPLE7(Section,       metric_base::base_metric,        section,           NamingConvention, UInt, IdType, 0)\
        INTEROP_TUPLE7(TileNumber,    metric_base::base_metric,        number,            NamingConvention, UInt, IdType, 0)

namespace illumina { namespace interop { namespace model { namespace table
{
#   define INTEROP_TUPLE7(Id, Ignored1, Ignored2, Ignored3, Ignored4, Ignored5, Ignored6) Id##EventColumn,
    /** Map column index to name. Note, the enum has a 'Column' suffix added to the name above*/
    enum event_column_id{ INTEROP_EVENT_COLUMN_TYPES EventColumnCount, UnknownEventColumnId=INTEROP_UNKNOWN};
#   undef INTEROP_TUPLE7

    /** Information describing a single column or a group of columns
     */
    class event_column
    {
    public:
        /** Constructor */
        event_column() : m_id(UnknownEventColumnId), m_offset(0) {}
        /** Constructor
         *
         * @param id column id
         */
        event_column(const event_column_id id) :
                m_id(id),
                m_name(to_header(m_id)),
                m_offset(static_cast<size_t>(id))
        {
            INTEROP_ASSERT(id < EventColumnCount);
        }
        /** Constructor
         *
         * @param index column id
         */
        event_column(const size_t index) :
                m_id(static_cast<event_column_id>(index)),
                m_name(to_header(m_id)),
                m_offset(index)
        {
            INTEROP_ASSERT(index < EventColumnCount);
        }

    public:
        /** Get the column id enum
         *
         * @return column id enum
         */
        event_column_id id()const
        {
            return m_id;
        }
        /** Get the name of the column
         *
         * @return name of the column
         */
        const std::string& name()const
        {
            return m_name;
        }
        /** Get the offset into the data array
         *
         * @return offset into the data array
         */
        size_t offset()const
        {
            return m_offset;
        }

    public:
        /** Update the offset of the column
         *
         * @param off new offset into data array
         */
        void offset(const size_t off)
        {
            m_offset = off;
        }
        /** Update the offset of the column
         *
         * @param val new id
         */
        void id(const event_column_id val)
        {
            m_id = val;
        }
        /** Update the offset of the column
         *
         * @param header header description for new id
         */
        void parse_header_for_id(const std::string& header)
        {
            id(constants::parse<event_column_id>(to_name(header)));
        }

    public:
        /** Get total number of subcolumns
         *
         * @return total number of subcolumns
         */
        size_t size()const
        {
            return 1;
        }
        /** Get total number of columns in the data up to this column
         *
         * @return total number of columns in the data up to this column
         */
        size_t column_count()const
        {
            return m_offset + size();
        }

    public:
        /** Convert a column id enum to the string representation
         *
         * @param id column id enum
         * @return header representation
         */
        static std::string to_header(const event_column_id id)
        {
            return to_header(constants::to_string(id));
        }
        /** Convert name to header
         *
         * @param name column name
         * @return header representation
         */
        static std::string to_header(const std::string& name)
        {
            std::string header = name;
            util::camel_to(header);
            return header;
        }
        /** Convert header to name
         *
         * @param header column header name
         * @return column name
         */
        static std::string to_name(const std::string& header)
        {
            std::string name = header;
            util::camel_from(name);
            return name;
        }
        /** Convert header to name
         *
         * @param header column header
         * @return column name
         */
        static std::string to_name(const model::table::event_column& header)
        {
            return to_name(header.name());
        }

    private:
        friend std::istream& operator>>(std::istream& in, event_column& column);
        friend std::ostream& operator<<(std::ostream& out, const event_column& column);

    private:
        event_column_id m_id;
        std::string m_name;
        size_t m_offset;
    };


}}}}

