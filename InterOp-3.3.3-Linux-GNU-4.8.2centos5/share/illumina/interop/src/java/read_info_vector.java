/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class read_info_vector {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected read_info_vector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(read_info_vector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_runJNI.delete_read_info_vector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public read_info_vector() {
    this(interop_runJNI.new_read_info_vector__SWIG_0(), true);
  }

  public read_info_vector(long n) {
    this(interop_runJNI.new_read_info_vector__SWIG_1(n), true);
  }

  public long size() {
    return interop_runJNI.read_info_vector_size(swigCPtr, this);
  }

  public long capacity() {
    return interop_runJNI.read_info_vector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    interop_runJNI.read_info_vector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return interop_runJNI.read_info_vector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    interop_runJNI.read_info_vector_clear(swigCPtr, this);
  }

  public void add(read_info x) {
    interop_runJNI.read_info_vector_add(swigCPtr, this, read_info.getCPtr(x), x);
  }

  public read_info get(int i) {
    return new read_info(interop_runJNI.read_info_vector_get(swigCPtr, this, i), false);
  }

  public void set(int i, read_info val) {
    interop_runJNI.read_info_vector_set(swigCPtr, this, i, read_info.getCPtr(val), val);
  }

}
