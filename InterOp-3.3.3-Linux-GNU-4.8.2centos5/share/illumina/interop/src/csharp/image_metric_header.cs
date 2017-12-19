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

public class image_metric_header : base_cycle_metric_header {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal image_metric_header(global::System.IntPtr cPtr, bool cMemoryOwn) : base(c_csharp_metricsPINVOKE.image_metric_header_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(image_metric_header obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~image_metric_header() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          c_csharp_metricsPINVOKE.delete_image_metric_header(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public image_metric_header(ushort channel_count) : this(c_csharp_metricsPINVOKE.new_image_metric_header(channel_count), true) {
  }

  public ushort channelCount() {
    ushort ret = c_csharp_metricsPINVOKE.image_metric_header_channelCount(swigCPtr);
    return ret;
  }

  public ushort channel_count() {
    ushort ret = c_csharp_metricsPINVOKE.image_metric_header_channel_count__SWIG_0(swigCPtr);
    return ret;
  }

  public void channel_count(uint channel_count) {
    c_csharp_metricsPINVOKE.image_metric_header_channel_count__SWIG_1(swigCPtr, channel_count);
  }

  public new static image_metric_header default_header() {
    image_metric_header ret = new image_metric_header(c_csharp_metricsPINVOKE.image_metric_header_default_header(), true);
    return ret;
  }

  public new void clear() {
    c_csharp_metricsPINVOKE.image_metric_header_clear(swigCPtr);
  }

  public static readonly int MAX_CHANNELS = c_csharp_metricsPINVOKE.image_metric_header_MAX_CHANNELS_get();

}

}