/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class invalid_parameter extends base_exception {
  private transient long swigCPtr;

  protected invalid_parameter(long cPtr, boolean cMemoryOwn) {
    super(interop_run_metricsJNI.invalid_parameter_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(invalid_parameter obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_run_metricsJNI.delete_invalid_parameter(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public invalid_parameter(String mesg) {
    this(interop_run_metricsJNI.new_invalid_parameter(mesg), true);
  }

}
