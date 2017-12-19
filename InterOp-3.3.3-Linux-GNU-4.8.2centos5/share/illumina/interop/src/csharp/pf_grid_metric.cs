//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.10
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Illumina.InterOp.Metrics {

using System;
using System.Runtime.InteropServices;
using Illumina.InterOp.Run;

public class pf_grid_metric : base_metric {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal pf_grid_metric(global::System.IntPtr cPtr, bool cMemoryOwn) : base(c_csharp_metricsPINVOKE.pf_grid_metric_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(pf_grid_metric obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~pf_grid_metric() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          c_csharp_metricsPINVOKE.delete_pf_grid_metric(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public pf_grid_metric() : this(c_csharp_metricsPINVOKE.new_pf_grid_metric__SWIG_0(), true) {
  }

  public pf_grid_metric(pf_grid_metric_header header) : this(c_csharp_metricsPINVOKE.new_pf_grid_metric__SWIG_1(pf_grid_metric_header.getCPtr(header)), true) {
    if (c_csharp_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public pf_grid_metric(uint num_bins_x, uint num_bins_y) : this(c_csharp_metricsPINVOKE.new_pf_grid_metric__SWIG_3(num_bins_x, num_bins_y), true) {
  }

  public uint raw_cluster_count(uint x_bin, uint y_bin) {
    uint ret = c_csharp_metricsPINVOKE.pf_grid_metric_raw_cluster_count(swigCPtr, x_bin, y_bin);
    return ret;
  }

  public uint pf_cluster_count(uint x_bin, uint y_bin) {
    uint ret = c_csharp_metricsPINVOKE.pf_grid_metric_pf_cluster_count(swigCPtr, x_bin, y_bin);
    return ret;
  }

  public float raw_cluster_density_k(uint x_bin, uint y_bin, float density) {
    float ret = c_csharp_metricsPINVOKE.pf_grid_metric_raw_cluster_density_k(swigCPtr, x_bin, y_bin, density);
    return ret;
  }

  public float pf_cluster_density_k(uint x_bin, uint y_bin, float density) {
    float ret = c_csharp_metricsPINVOKE.pf_grid_metric_pf_cluster_density_k(swigCPtr, x_bin, y_bin, density);
    return ret;
  }

  public float percent_pf(uint x_bin, uint y_bin) {
    float ret = c_csharp_metricsPINVOKE.pf_grid_metric_percent_pf(swigCPtr, x_bin, y_bin);
    return ret;
  }

  public static string prefix() {
    string ret = c_csharp_metricsPINVOKE.pf_grid_metric_prefix();
    return ret;
  }

  public static readonly int TYPE = c_csharp_metricsPINVOKE.pf_grid_metric_TYPE_get();
  public static readonly int LATEST_VERSION = c_csharp_metricsPINVOKE.pf_grid_metric_LATEST_VERSION_get();

}

}