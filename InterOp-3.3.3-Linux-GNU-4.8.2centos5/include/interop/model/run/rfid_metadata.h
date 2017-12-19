/** Meta data for the RFID
 *
 *  @file
 *  @date 2/3/15
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include <string>
#include "interop/util/cstdint.h"

namespace illumina { namespace interop { namespace model { namespace run
{

    /** Layout of the flow cell
     */
    class rfid_metadata
    {
    public:
        /** Unsigned long */
        typedef ::uint64_t ulong_t;
    public:
        /** Constructor
         */
        rfid_metadata() :
                m_expiration_date(0), m_part_number(""), m_serial_number("")
        {
        }

        /** Constructor
         *
         * @param expiration_date expiration date
         * @param part_number part number
         * @param serial_number serial number
         */
        rfid_metadata(const ulong_t expiration_date,
                      const std::string &part_number,
                      const std::string &serial_number) :
                m_expiration_date(expiration_date), m_part_number(part_number), m_serial_number(serial_number)
        {
        }

    public:
        /** Get the expiration date
         *
         * @return expiration date
         */
        ulong_t expiration_date() const
        { return m_expiration_date; }

        /** Get the part number
         *
         * @return part number
         */
        const std::string &part_number() const
        { return m_part_number; }

        /** Get the serial number
         *
         * @return serial number
         */
        const std::string &serial_number() const
        { return m_serial_number; }

    private:
        ulong_t m_expiration_date;
        std::string m_part_number;
        std::string m_serial_number;

        friend class parameters;
    };

}}}}


