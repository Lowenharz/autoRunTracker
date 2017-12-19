/** Base information shared by tile metrics
 *
 * Tile metrics include any metric calculated for a specific tile.
 *
 *  @file
 *  @date 8/5/2015
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once

#include "interop/model/metric_base/base_metric.h"

namespace illumina { namespace interop { namespace model { namespace metric_base
{
    //forward declaration
    class base_static_run_metric;

    /** Defines default base header for metric */
    class base_static_run_metric_header : public empty_header
    {
    public:
        /** Define the base type */
        typedef constants::base_run_t base_t;
    protected:
        /** Update max cycle
         *
         * This does nothing, and is here for compatibility.
         */
        void update_max_cycle(const base_static_run_metric &)
        { }
        /** Does nothing
         *
         * @todo remove this method
         */
        void clear(){}
    };

    /** Base class for InterOp classes that contain static run specific metrics
     *
     * These classes define camera, channel, and distortion_type identifier.
     * Inherits from empty_metric
     */
    class base_static_run_metric : public empty_metric
    {
    public:
        /** Define the base type */
        typedef constants::base_run_t base_t;

        /** Unsigned int16_t
         */
        typedef ::uint16_t ushort_t;

        /** Unsigned byte */
        typedef ::uint16_t count_t;

        /** id_t type */
        typedef ::uint32_t id_t;

        /** Base metric header that adds no functionality
         */
        typedef base_static_run_metric_header header_type;

        enum
        {
            CHANNEL_BIT_SHIFT = 8, //for creating ID
            DISTORTION_BIT_SHIFT = 16 //for creating ID
        };

    public:
        /** Constructor
         *
         * @param camera camera
         * @param channel channel
         * @param distortion_type distortion_type
         */
        base_static_run_metric(const count_t camera, const count_t channel, const ushort_t distortion_type):
                m_camera(camera), m_channel(channel), m_distortion_type(distortion_type)
        { }

    public:

        /** Setter
         *
         * @param camera camera
         * @param channel channel
         * @param distortion_type
         */
        void set_base(const count_t camera, const count_t channel, const ushort_t distortion_type)
        {
            m_camera = static_cast<count_t> (camera);
            m_channel = static_cast<count_t> (channel);
            m_distortion_type = static_cast<ushort_t> (distortion_type);
        }
        /** Setter dummy
         * @todo see if this can be removed
         */
        template<typename T, typename U>
        void set_base(const T, const U)
        {

        }

        /** Get the metric name suffix
        *
        * @return empty string
        */
        static const char *suffix()
        { return ""; }

        /** Set the base metric identifiers
        *
        * @param base layout base
        */
        template<class BaseMetric>
        void set_base(const BaseMetric &base)
        {
            m_camera = static_cast<count_t> (base.camera);
            m_channel = static_cast<count_t> (base.channel);
            m_distortion_type = static_cast<ushort_t> (base.distortion_type);
        }

        /** Unique id created from camera, channel, and distortion type --> calls create_id
         * @return unique identifier
         */
        id_t id() const
        {
            return create_id(m_camera, m_channel, m_distortion_type);
        }

        /** Unique id creation from 3 params
         *
         * @param camera camera
         * @param channel channel
         * @param distortion_type distortion type
         *
         * @return unique id
         */
        static id_t create_id(const id_t camera, const id_t channel, const id_t distortion_type)
        {
            /** +1 makes camera 1-indexed, so create_id never returns 0 */
            return (camera | (channel << CHANNEL_BIT_SHIFT) | (distortion_type << DISTORTION_BIT_SHIFT)) + 1;
        }



        /** Get camera value
         * @return camera number
         */
        count_t camera() const
        { return m_camera;}

        /** Get channel value
         * @return channel number
         */
        count_t channel() const
        { return m_channel;}

        /** Get distortion type value
         *
         * @return distortion_type number
         */
        ushort_t distortion_type() const
        { return m_distortion_type;}

        /** Lane value as dummy to pass problems in metric stream.h
         *
         * @todo remove
         * @return lane
         */
        uint32_t lane() const
        { return 1;}
        /** Get tile value as dummy to pass problems in swig
         *
         * @todo remove
         * @return tile
         */
        uint32_t tile() const
        { return 1;}

    private:
        count_t m_camera;
        count_t m_channel;
        ushort_t m_distortion_type;
    };

    /** Specialization for base_cycle_metric providing sentinel values*/
    template<>
    struct metric_attributes<base_static_run_metric> : public metric_attributes<base_metric>{};


}}}}

