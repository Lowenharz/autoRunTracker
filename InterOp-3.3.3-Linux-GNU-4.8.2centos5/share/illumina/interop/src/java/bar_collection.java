/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class bar_collection {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected bar_collection(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(bar_collection obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_plotJNI.delete_bar_collection(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void push_back(bar_point point) {
    interop_plotJNI.bar_collection_push_back(swigCPtr, this, bar_point.getCPtr(point), point);
  }

  public bar_point at(long index) throws index_out_of_bounds_exception {
    return new bar_point(interop_plotJNI.bar_collection_at(swigCPtr, this, index), false);
  }

  public long size() {
    return interop_plotJNI.bar_collection_size(swigCPtr, this);
  }

  public void assign(long n, bar_point val) {
    interop_plotJNI.bar_collection_assign(swigCPtr, this, n, bar_point.getCPtr(val), val);
  }

  public void resize(long n) {
    interop_plotJNI.bar_collection_resize(swigCPtr, this, n);
  }

  public bar_collection() {
    this(interop_plotJNI.new_bar_collection(), true);
  }

}