/** Logic to populate the run diagnostics table
 *
 *  @file
 *  @date  7/20/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <map>
#include <vector>
#include "interop/model/run_metrics.h"
#include "interop/model/table/run_diagnostics_column.h"
#include "interop/model/table/run_diagnostics_table.h"

namespace illumina { namespace interop { namespace logic { namespace table
{
    /** Define a row offset map */
    typedef std::map<model::metric_base::base_metric::id_t, ::uint64_t > row_offset_map_t;

    typedef std::vector< std::string > run_diagnostics_description_vector_t;
    /** Populate the run diagnostics table with all the metrics in the run
     *
     * @param metrics collection of all run metrics
     * @param columns vector of table columns
     * @param row_offset ordering for the rows
     * @param data_beg iterator to start of table data
     * @param n number of cells in the data table
     */
    void populate_run_diagnostics_table_data(const model::metrics::run_metrics& metrics,
                                             const std::vector<model::table::run_diagnostics_column>& columns,
                                             const row_offset_map_t& row_offset,
                                             ::uint64_t* data_beg, const size_t n);

    /** Count the number of rows in the run diagnostics table and setup an ordering
     *
     * @param metrics collections of InterOp metric sets
     * @param row_offset ordering for the rows
     */
    void count_run_diagnostics_table_rows(const model::metrics::run_metrics& metrics,
                                row_offset_map_t& row_offset);
    /** Count the total number of columns for the data table
     *
     * @param columns vector of table column descriptions
     * @return total number of columns including sub columns
     */
    size_t count_table_columns(const std::vector<model::table::run_diagnostics_column>& columns);
    /** Create a run diagnostics table from run metrics
     *
     * @param metrics source run metrics
     * @param table destination run diagnostics table
     */
    void create_run_diagnostics_table(model::metrics::run_metrics& metrics, model::table::run_diagnostics_table& table)
    throw(model::invalid_column_type, model::index_out_of_bounds_exception);

    /** Generate the list of possible events
     *
     * @param types vector that gets filled with the event list
     */
    void list_run_diagnostics_metrics(run_diagnostics_description_vector_t& types);
}}}}

