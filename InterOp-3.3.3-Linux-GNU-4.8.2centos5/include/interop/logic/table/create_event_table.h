/** Logic to populate the event table
 *
 *  @file
 *  @date  7/20/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <vector>
#include "interop/model/run_metrics.h"
#include "interop/model/table/event_column.h"
#include "interop/model/table/event_table.h"

namespace illumina { namespace interop { namespace logic { namespace table
{
    /** Define a row offset map */
    typedef std::map<model::metric_base::base_metric::id_t, ::uint64_t > row_offset_map_t;

    typedef std::vector< std::string > event_description_vector_t;

    /** Populate the event table with all the metrics in the run
     *
     * @param metrics collection of all run metrics
     * @param columns vector of table columns
     * @param row_offset ordering for the rows
     * @param data_beg iterator to start of table data
     * @param n number of cells in the data table
     */
    void populate_event_table_data(const model::metrics::run_metrics& metrics,
                                     const std::vector<model::table::event_column>& columns,
                                     const row_offset_map_t& row_offset,
                                     ::uint64_t* data_beg, const size_t n);
    /** Count the number of rows in the event table and setup an ordering
     *
     * @param metrics collections of InterOp metric sets
     * @param row_offset ordering for the rows
     */
    void count_event_table_rows(const model::metrics::run_metrics& metrics,
                                row_offset_map_t& row_offset);
    /** Count the total number of columns for the data table
     *
     * @param columns vector of table column descriptions
     * @return total number of columns including sub columns
     */
    size_t count_table_columns(const std::vector<model::table::event_column>& columns);
    /** Create an event table from run metrics
     *
     * @param metrics source run metrics
     * @param table destination event table
     */
    void create_event_table(model::metrics::run_metrics& metrics, model::table::event_table& table)
    throw(model::invalid_column_type, model::index_out_of_bounds_exception);

    /** Generate the list of possible events
     *
     * @param types vector that gets filled with the event list
     */
    void list_event_metrics(event_description_vector_t& types);
}}}}

