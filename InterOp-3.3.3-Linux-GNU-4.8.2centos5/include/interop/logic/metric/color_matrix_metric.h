/** Logic for color matrix metrics
 *
 *  @file
 *  @date  9/2/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include <vector>
#include <string>

namespace illumina { namespace interop { namespace logic { namespace metric
{
    /** Get the labels for color matrix indices given channel names
     *
     * @param channels channel names
     * @param color_matrix_labels destination list of strings containing labels of color matrix elements
     */
    void get_color_matrix_labels(const std::vector<std::string>& channels, std::vector<std::string>& color_matrix_labels);
}}}}

