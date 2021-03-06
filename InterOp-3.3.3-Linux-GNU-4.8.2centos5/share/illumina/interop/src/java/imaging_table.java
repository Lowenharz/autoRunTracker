/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public class imaging_table {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected imaging_table(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(imaging_table obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        interop_tableJNI.delete_imaging_table(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public imaging_table() {
    this(interop_tableJNI.new_imaging_table(), true);
  }

  public void set_data(long rows, imaging_column_vector cols, float_vector data) {
    interop_tableJNI.imaging_table_set_data(swigCPtr, this, rows, imaging_column_vector.getCPtr(cols), cols, float_vector.getCPtr(data), data);
  }

  public float at(long r, column_id c, long subcol) throws index_out_of_bounds_exception {
    return interop_tableJNI.imaging_table_at__SWIG_0(swigCPtr, this, r, c.swigValue(), subcol);
  }

  public float at(long r, column_id c) throws index_out_of_bounds_exception {
    return interop_tableJNI.imaging_table_at__SWIG_1(swigCPtr, this, r, c.swigValue());
  }

  public imaging_column_vector columns() {
    return new imaging_column_vector(interop_tableJNI.imaging_table_columns(swigCPtr, this), false);
  }

  public boolean empty() {
    return interop_tableJNI.imaging_table_empty(swigCPtr, this);
  }

  public void clear() {
    interop_tableJNI.imaging_table_clear(swigCPtr, this);
  }

  public imaging_column column_at(long col_index) throws index_out_of_bounds_exception {
    return new imaging_column(interop_tableJNI.imaging_table_column_at(swigCPtr, this, col_index), false);
  }

  public long column_count() {
    return interop_tableJNI.imaging_table_column_count(swigCPtr, this);
  }

  public long total_column_count() {
    return interop_tableJNI.imaging_table_total_column_count(swigCPtr, this);
  }

  public long row_count() {
    return interop_tableJNI.imaging_table_row_count(swigCPtr, this);
  }

}
