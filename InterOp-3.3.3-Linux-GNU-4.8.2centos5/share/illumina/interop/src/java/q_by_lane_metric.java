/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class q_by_lane_metric extends q_metric {
  private transient long swigCPtr;

  protected q_by_lane_metric(long cPtr, boolean cMemoryOwn) {
    super(interop_metricsJNI.q_by_lane_metric_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(q_by_lane_metric obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_metricsJNI.delete_q_by_lane_metric(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public q_by_lane_metric() {
    this(interop_metricsJNI.new_q_by_lane_metric__SWIG_0(), true);
  }

  public q_by_lane_metric(q_score_header header) {
    this(interop_metricsJNI.new_q_by_lane_metric__SWIG_1(q_score_header.getCPtr(header), header), true);
  }

  public q_by_lane_metric(long lane, long tile, long cycle, uint_vector qscore_hist) {
    this(interop_metricsJNI.new_q_by_lane_metric__SWIG_2(lane, tile, cycle, uint_vector.getCPtr(qscore_hist), qscore_hist), true);
  }

  public void accumulate_by_lane(q_metric metric) {
    interop_metricsJNI.q_by_lane_metric_accumulate_by_lane(swigCPtr, this, q_metric.getCPtr(metric), metric);
  }

  public static String suffix() {
    return interop_metricsJNI.q_by_lane_metric_suffix();
  }

  public final static int TYPE = interop_metricsJNI.q_by_lane_metric_TYPE_get();
  public final static int LATEST_VERSION = interop_metricsJNI.q_by_lane_metric_LATEST_VERSION_get();

}