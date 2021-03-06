/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class static_run_metric_header extends base_static_run_metric_header {
  private transient long swigCPtr;

  protected static_run_metric_header(long cPtr, boolean cMemoryOwn) {
    super(interop_metricsJNI.static_run_metric_header_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(static_run_metric_header obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_metricsJNI.delete_static_run_metric_header(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static_run_metric_header(long curve_length, long curve_check) {
    this(interop_metricsJNI.new_static_run_metric_header(curve_length, curve_check), true);
  }

  public long curve_length() {
    return interop_metricsJNI.static_run_metric_header_curve_length(swigCPtr, this);
  }

  public long curve_check() {
    return interop_metricsJNI.static_run_metric_header_curve_check(swigCPtr, this);
  }

  public static static_run_metric_header default_header() {
    return new static_run_metric_header(interop_metricsJNI.static_run_metric_header_default_header(), true);
  }

  public void clear() {
    interop_metricsJNI.static_run_metric_header_clear(swigCPtr, this);
  }

}
