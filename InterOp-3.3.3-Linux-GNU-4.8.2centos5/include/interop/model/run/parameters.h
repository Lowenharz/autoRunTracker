/** Additional metadata describing a sequencing run
 *
 * The InterOp files parsed by this class include:
 *  - RunParameters.xml
 *
 *  @file
 *  @date 11/9/15
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <string>
#include <vector>
#include "interop/util/exception.h"
#include "interop/constants/enums.h"
#include "interop/util/xml_exceptions.h"
#include "interop/model/run/rfid_metadata.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4290)// MSVC warns that it ignores the exception specification.
#endif

namespace illumina { namespace interop { namespace model { namespace run
{

    /** Metadata describing sequencing run
     *
     * This class parses the RunParameters.xml XML file. It only provides
     * the instrument type and version of the XML file format. We do not plan
     * to support parsing any other values in this file.
     *
     * This class is only used on legacy platforms where:
     *  1. The channel names were not given in the RunInfo.xml
     *  2. The bins were not provided in the header of the QMetrics.bin (v4)
     *
     *  We do not support parsing this file on later platforms.
     */
    class parameters
    {
    public:
        /** Unsigned integer type */
        typedef ::uint32_t uint_t;
        /** Instrument type enum */
        typedef constants::instrument_type instrument_type_t;

    public:
        /** Constructor
         *
         * @param version XML format version
         * @param instrument_name name of the instrument
         * @param instrument_type type code of the instrument
         * @param experiment_name name of the experiment
         * @param chemistry name of the reagent kit
         * @param control_lane number of the control lane
         * @param flowcell_rfid RFID code for the flowcell
         * @param bottle_rfid RFID code for the bottle
         * @param bottle_barcode barcode for the bottle
         * @param reagent_rfid RFID code for the reagent kit
         * @param reagent_barcode barcode for the reagent kit
         */
        parameters(const uint_t version = 0,
                   const std::string &instrument_name = "",
                   const instrument_type_t instrument_type = constants::UnknownInstrument,
                   const std::string &experiment_name = "",
                   const std::string &chemistry = "",
                   const uint_t control_lane = 0,
                   const rfid_metadata &flowcell_rfid = rfid_metadata(),
                   const rfid_metadata &bottle_rfid = rfid_metadata(),
                   const std::string &bottle_barcode = "",
                   const rfid_metadata &reagent_rfid = rfid_metadata(),
                   const std::string &reagent_barcode = ""
        ) :
                m_version(version),
                m_instrument_name(instrument_name),
                m_instrument_type(instrument_type),
                m_experiment_name(experiment_name),
                m_chemistry(chemistry),
                m_control_lane(control_lane),
                m_flowcell_rfid(flowcell_rfid),
                m_bottle_rfid(bottle_rfid),
                m_bottle_barcode(bottle_barcode),
                m_reagent_rfid(reagent_rfid),
                m_reagent_barcode(reagent_barcode)
        {
        }

    public:
        /** Get the name of the instrument
         *
         * @return name of the instrument
         */
        const std::string &instrument_name() const
        { return m_instrument_name; }

        /** Get the type of instrument
         *
         * @return type of instrument
         */
        instrument_type_t instrument_type() const
        { return m_instrument_type; }

        /** Get the name of the experiment
         *
         * @return name of the experiment
         */
        const std::string &experiment_name() const
        { return m_experiment_name; }

        /** Get the name of the chemistry
         *
         * @return name of the chemistry
         */
        const std::string &chemistry() const
        { return m_chemistry; }

        /** Get the control lane
         *
         * @return control lane number
         */
        uint_t control_lane() const
        { return m_control_lane; }

        /** Get the version of the xml format
         *
         * @return version of the xml format
         */
        uint_t version() const
        { return m_version; }

        /** Get the RFID metadata for the flowcell
         *
         * @return RFID metadata
         */
        const rfid_metadata &flowcell_rfid() const
        { return m_flowcell_rfid; }

        /** Get the RFID metadata for the bottle
         *
         * @return RFID metadata
         */
        const rfid_metadata &bottle_rfid() const
        { return m_bottle_rfid; }

        /** Get the barcode metadata for the bottle
         *
         * @return barcode metadata
         */
        const std::string &bottle_barcode() const
        { return m_bottle_barcode; }

        /** Get the RFID metadata for the reagent kit
         *
         * @return RFID metadata
         */
        const rfid_metadata &reagent_rfid() const
        { return m_reagent_rfid; }

        /** Get the barcode metadata for the reagent kit
         *
         * @return barcode metadata
         */
        const std::string &reagent_barcode() const
        { return m_reagent_barcode; }

    public:
        /** Read run metadata from the given run folder
         *
         * @param run_folder run folder containing RunParameters.xml
         */
        void read(const std::string &run_folder) throw(xml::xml_file_not_found_exception,
        xml::bad_xml_format_exception,
        xml::empty_xml_format_exception,
        xml::missing_xml_element_exception,
        xml::xml_parse_exception);

        /** Read run metadata from the given XML file
         *
         * @param filename xml file
         */
        void read_file(const std::string &filename) throw(xml::xml_file_not_found_exception,
        xml::bad_xml_format_exception,
        xml::empty_xml_format_exception,
        xml::missing_xml_element_exception,
        xml::xml_parse_exception);

        /** String containing xml data
         *
         * @param data xml string data
         */
        void parse(char *data) throw(xml::xml_file_not_found_exception,
        xml::bad_xml_format_exception,
        xml::empty_xml_format_exception,
        xml::missing_xml_element_exception,
        xml::xml_parse_exception);

    public:
        /** Convert string representation of the time to a long
         *
         * The string should have the following format: 2012-10-09T00:00:00
         *
         * @param time_repr string representatino of the time
         * @return number of seconds
         */
        static rfid_metadata::ulong_t parse_time(const std::string &time_repr);

    private:
        void set_instrument_id(std::string &application_name, std::string &multi_surface);

    private:
        uint_t m_version;
        std::string m_instrument_name;
        instrument_type_t m_instrument_type;
        std::string m_experiment_name;
        std::string m_chemistry;
        uint_t m_control_lane;
        rfid_metadata m_flowcell_rfid;
        rfid_metadata m_bottle_rfid;
        std::string m_bottle_barcode;
        rfid_metadata m_reagent_rfid;
        std::string m_reagent_barcode;
    };

}}}}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

