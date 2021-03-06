//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.10
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Illumina.InterOp.Table {

using System;
using System.Runtime.InteropServices;
using Illumina.InterOp.Metrics;
using Illumina.InterOp.Run;
using Illumina.InterOp.RunMetrics;

public class run_diagnostics_table : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal run_diagnostics_table(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(run_diagnostics_table obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~run_diagnostics_table() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          c_csharp_tablePINVOKE.delete_run_diagnostics_table(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public run_diagnostics_table() : this(c_csharp_tablePINVOKE.new_run_diagnostics_table(), true) {
  }

  public void set_data(uint rows, run_diagnostics_column_vector cols, ulong_vector data) {
    c_csharp_tablePINVOKE.run_diagnostics_table_set_data(swigCPtr, rows, run_diagnostics_column_vector.getCPtr(cols), ulong_vector.getCPtr(data));
    if (c_csharp_tablePINVOKE.SWIGPendingException.Pending) throw c_csharp_tablePINVOKE.SWIGPendingException.Retrieve();
  }

  public ulong at(uint r, run_diagnostics_column_id c) {
    ulong ret = c_csharp_tablePINVOKE.run_diagnostics_table_at(swigCPtr, r, (int)c);
    if (c_csharp_tablePINVOKE.SWIGPendingException.Pending) throw c_csharp_tablePINVOKE.SWIGPendingException.Retrieve();
    return ret;
    }

  public run_diagnostics_column_vector columns() {
    run_diagnostics_column_vector ret = new run_diagnostics_column_vector(c_csharp_tablePINVOKE.run_diagnostics_table_columns(swigCPtr), false);
    return ret;
  }

  public bool empty() {
    bool ret = c_csharp_tablePINVOKE.run_diagnostics_table_empty(swigCPtr);
    return ret;
  }

  public void clear() {
    c_csharp_tablePINVOKE.run_diagnostics_table_clear(swigCPtr);
  }

  public run_diagnostics_column column_at(uint col_index) {
    run_diagnostics_column ret = new run_diagnostics_column(c_csharp_tablePINVOKE.run_diagnostics_table_column_at(swigCPtr, col_index), false);
    if (c_csharp_tablePINVOKE.SWIGPendingException.Pending) throw c_csharp_tablePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint column_count() {
    uint ret = c_csharp_tablePINVOKE.run_diagnostics_table_column_count(swigCPtr);
    return ret;
  }

  public uint total_column_count() {
    uint ret = c_csharp_tablePINVOKE.run_diagnostics_table_total_column_count(swigCPtr);
    return ret;
  }

  public uint row_count() {
    uint ret = c_csharp_tablePINVOKE.run_diagnostics_table_row_count(swigCPtr);
    return ret;
  }

}

}
