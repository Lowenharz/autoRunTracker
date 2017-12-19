/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class tile_metric_header extends base_metric_header {
  private transient long swigCPtr;

  protected tile_metric_header(long cPtr, boolean cMemoryOwn) {
    super(interop_metricsJNI.tile_metric_header_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(tile_metric_header obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_metricsJNI.delete_tile_metric_header(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public tile_metric_header(float density) {
    this(interop_metricsJNI.new_tile_metric_header(density), true);
  }

  public float density() {
    return interop_metricsJNI.tile_metric_header_density(swigCPtr, this);
  }

  public static tile_metric_header default_header() {
    return new tile_metric_header(interop_metricsJNI.tile_metric_header_default_header(), true);
  }

  public void clear() {
    interop_metricsJNI.tile_metric_header_clear(swigCPtr, this);
  }

}