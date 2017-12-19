/** Utility functions for building a table
 *
 * @note These functions were move here as a work around for SWIG
 *
 *  @file
 *  @date  6/13/16
 *  @version 1.0
 *  @copyright Illumina Use Only
 */
#pragma once
#include "interop/model/table/imaging_column.h"
/** IUO */
#include "interop/model/table/event_column.h"
#include "interop/model/table/run_diagnostics_column.h"

namespace illumina { namespace interop { namespace logic { namespace table
{

    /** Function interface for method call with single parameter
     *
     * @note This is necessary because you cannot pass anything into an function that expects no arguments, not even void
     *
     * @param obj object corresponding to the method
     * @param param1 first value to function
     * @param func pointer to member function
     * @return functor wrapper
     */
    template<class T, typename R, typename P1, typename P2>
    R call_adapter(const T& obj, P2 param1, R (T::*func )(P1)const)
    {
        return (obj.*func)(param1);
    }
    /** Function interface for method call with single dummy parameter
     *
     * @note This is necessary because you cannot pass anything into an function that expects no arguments, not even void
     *
     * @param obj object corresponding to the method
     * @param func pointer to member function
     * @return functor wrapper
     */
    template<class T, typename R, typename P1>
    R call_adapter(const T& obj, P1, R (T::*func )()const)
    {
        return (obj.*func)();
    }


}}}}


/** This macro maps an enum to a string/enum pair */
#define INTEROP_TUPLE7(X, Ignore1, Ignore2, Ignore3, Ignore4, Ignore5, Ignored6) name_type_pair_t(#X, model::table:: X##Column),
namespace illumina { namespace interop {  namespace constants {

    /** Specialization that maps imaging column types to a string */
    template<>
    class enumeration_string_mapping<model::table::column_id>
    {
        typedef std::pair<std::string, model::table::column_id> name_type_pair_t;
    public:
        /** Pass an array of string, enum pairs and its length to the given function
         *
         * @param func pointer to a function that takes an array of string/enum pairs as a parameter
         * @return the value returned by the given function (in the case of `parse` and `to_string` the return value is a singleton)
         */
        template<typename R, typename F>
        static R setup(F func)
        {
            static const name_type_pair_t name_types[] = {INTEROP_IMAGING_COLUMN_TYPES  name_type_pair_t("Dummy", model::table::ImagingColumnCount)};
            return func(name_types, util::length_of(name_types));
        }
    };
}}}
#undef INTEROP_TUPLE7 // Reuse this for another conversion

/** IUO */

/** This macro maps an enum to a string/enum pair */
#define INTEROP_TUPLE7(X, Ignore1, Ignore2, Ignore3, Ignore4, Ignore5, Ignored6) name_type_pair_t(#X, model::table:: X##EventColumn),
namespace illumina { namespace interop {  namespace constants {

            /** Specialization that maps event column types to a string
             * @note IUO
             */
            template<>
            class enumeration_string_mapping<model::table::event_column_id>
            {
                typedef std::pair<std::string, model::table::event_column_id> name_type_pair_t;
            public:
                /** Pass an array of string, enum pairs and its length to the given function
                 *
                 * @param func pointer to a function that takes an array of string/enum pairs as a parameter
                 * @return the value returned by the given function (in the case of `parse` and `to_string` the return value is a singleton)
                 */
                template<typename R, typename F>
                static R setup(F func)
                {
                    static const name_type_pair_t name_types[] = {INTEROP_EVENT_COLUMN_TYPES  name_type_pair_t("Dummy", model::table::EventColumnCount)};
                    return func(name_types, util::length_of(name_types));
                }
            };
        }}}
#undef INTEROP_TUPLE7 // Reuse this for another conversion

/** This macro maps an enum to a string/enum pair */
#define INTEROP_TUPLE7(X, Ignore1, Ignore2, Ignore3, Ignore4, Ignore5, Ignored6) name_type_pair_t(#X, model::table:: X##RunDiagnosticsColumn),
namespace illumina { namespace interop {  namespace constants {

    /** Specialization that maps event column types to a string
     * @note IUO
     */
    template<>
    class enumeration_string_mapping<model::table::run_diagnostics_column_id >
    {
        typedef std::pair<std::string, model::table::run_diagnostics_column_id> name_type_pair_t;
    public:
        /** Pass an array of string, enum pairs and its length to the given function
         *
         * @param func pointer to a function that takes an array of string/enum pairs as a parameter
         * @return the value returned by the given function (in the case of `parse` and `to_string` the return value is a singleton)
         */
        template<typename R, typename F>
        static R setup(F func)
        {
            static const name_type_pair_t name_types[] = {INTEROP_RUN_DIAGNOSTICS_COLUMN_TYPES  name_type_pair_t("Dummy", model::table::RunDiagnosticsColumnCount)};
            return func(name_types, util::length_of(name_types));
        }
    };
}}}
#undef INTEROP_TUPLE7 // Reuse this for another conversion
