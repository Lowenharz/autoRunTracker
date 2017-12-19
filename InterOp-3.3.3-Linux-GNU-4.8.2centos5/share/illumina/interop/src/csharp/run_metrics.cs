//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.10
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Illumina.InterOp.RunMetrics {

using System;
using System.Runtime.InteropServices;
using Illumina.InterOp.Run;
using Illumina.InterOp.Metrics;

public class run_metrics : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal run_metrics(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(run_metrics obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~run_metrics() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          c_csharp_run_metricsPINVOKE.delete_run_metrics(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public run_metrics() : this(c_csharp_run_metricsPINVOKE.new_run_metrics__SWIG_0(), true) {
  }

  public run_metrics(info run_info, parameters run_param) : this(c_csharp_run_metricsPINVOKE.new_run_metrics__SWIG_1(info.getCPtr(run_info), parameters.getCPtr(run_param)), true) {
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public run_metrics(info run_info) : this(c_csharp_run_metricsPINVOKE.new_run_metrics__SWIG_2(info.getCPtr(run_info)), true) {
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read(string run_folder, uint thread_count) {
    c_csharp_run_metricsPINVOKE.run_metrics_read__SWIG_0(swigCPtr, run_folder, thread_count);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read(string run_folder) {
    c_csharp_run_metricsPINVOKE.run_metrics_read__SWIG_1(swigCPtr, run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read(string run_folder, uchar_vector valid_to_load, uint thread_count, bool skip_loaded) {
    c_csharp_run_metricsPINVOKE.run_metrics_read__SWIG_2(swigCPtr, run_folder, uchar_vector.getCPtr(valid_to_load), thread_count, skip_loaded);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read(string run_folder, uchar_vector valid_to_load, uint thread_count) {
    c_csharp_run_metricsPINVOKE.run_metrics_read__SWIG_3(swigCPtr, run_folder, uchar_vector.getCPtr(valid_to_load), thread_count);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read(string run_folder, uchar_vector valid_to_load) {
    c_csharp_run_metricsPINVOKE.run_metrics_read__SWIG_4(swigCPtr, run_folder, uchar_vector.getCPtr(valid_to_load));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint read_xml(string run_folder) {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_read_xml(swigCPtr, run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void read_run_info(string run_folder) {
    c_csharp_run_metricsPINVOKE.run_metrics_read_run_info(swigCPtr, run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public uint read_run_parameters(string run_folder, bool force_load) {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_read_run_parameters__SWIG_0(swigCPtr, run_folder, force_load);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint read_run_parameters(string run_folder) {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_read_run_parameters__SWIG_1(swigCPtr, run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void finalize_after_load(uint count) {
    c_csharp_run_metricsPINVOKE.run_metrics_finalize_after_load__SWIG_0(swigCPtr, count);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void finalize_after_load() {
    c_csharp_run_metricsPINVOKE.run_metrics_finalize_after_load__SWIG_1(swigCPtr);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool empty() {
    bool ret = c_csharp_run_metricsPINVOKE.run_metrics_empty(swigCPtr);
    return ret;
  }

  public void legacy_channel_update(instrument_type type) {
    c_csharp_run_metricsPINVOKE.run_metrics_legacy_channel_update(swigCPtr, (int)type);
  }

  public void set_naming_method(tile_naming_method naming_method) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_naming_method(swigCPtr, (int)naming_method);
  }

  public uint count_legacy_bins(uint legacy_bin_count) {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_count_legacy_bins__SWIG_0(swigCPtr, legacy_bin_count);
    return ret;
  }

  public uint count_legacy_bins() {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_count_legacy_bins__SWIG_1(swigCPtr);
    return ret;
  }

  public bool is_run_parameters_required(uint legacy_bin_count) {
    bool ret = c_csharp_run_metricsPINVOKE.run_metrics_is_run_parameters_required__SWIG_0(swigCPtr, legacy_bin_count);
    return ret;
  }

  public bool is_run_parameters_required() {
    bool ret = c_csharp_run_metricsPINVOKE.run_metrics_is_run_parameters_required__SWIG_1(swigCPtr);
    return ret;
  }

  public info run_info() {
    info ret = new info(c_csharp_run_metricsPINVOKE.run_metrics_run_info__SWIG_0(swigCPtr), false);
    return ret;
  }

  public void run_info(info info) {
    c_csharp_run_metricsPINVOKE.run_metrics_run_info__SWIG_1(swigCPtr, info.getCPtr(info));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public parameters run_parameters() {
    parameters ret = new parameters(c_csharp_run_metricsPINVOKE.run_metrics_run_parameters__SWIG_0(swigCPtr), false);
    return ret;
  }

  public void run_parameters(parameters param) {
    c_csharp_run_metricsPINVOKE.run_metrics_run_parameters__SWIG_1(swigCPtr, parameters.getCPtr(param));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void list_filenames(metric_group group, string_vector files, string run_folder, bool use_out) {
    c_csharp_run_metricsPINVOKE.run_metrics_list_filenames__SWIG_0(swigCPtr, (int)group, string_vector.getCPtr(files), run_folder, use_out);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void list_filenames(metric_group group, string_vector files, string run_folder) {
    c_csharp_run_metricsPINVOKE.run_metrics_list_filenames__SWIG_1(swigCPtr, (int)group, string_vector.getCPtr(files), run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void list_filenames(string_vector files, string run_folder, bool bycycle, bool use_out) {
    c_csharp_run_metricsPINVOKE.run_metrics_list_filenames__SWIG_2(swigCPtr, string_vector.getCPtr(files), run_folder, bycycle, use_out);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void list_filenames(string_vector files, string run_folder, bool bycycle) {
    c_csharp_run_metricsPINVOKE.run_metrics_list_filenames__SWIG_3(swigCPtr, string_vector.getCPtr(files), run_folder, bycycle);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void list_filenames(string_vector files, string run_folder) {
    c_csharp_run_metricsPINVOKE.run_metrics_list_filenames__SWIG_4(swigCPtr, string_vector.getCPtr(files), run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void check_for_data_sources(string run_folder, uint last_cycle) {
    c_csharp_run_metricsPINVOKE.run_metrics_check_for_data_sources(swigCPtr, run_folder, last_cycle);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read_metrics(string run_folder, uint last_cycle, uint thread_count) {
    c_csharp_run_metricsPINVOKE.run_metrics_read_metrics__SWIG_0(swigCPtr, run_folder, last_cycle, thread_count);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read_metrics(string run_folder, uint last_cycle, uchar_vector valid_to_load, uint thread_count, bool skip_loaded) {
    c_csharp_run_metricsPINVOKE.run_metrics_read_metrics__SWIG_1(swigCPtr, run_folder, last_cycle, uchar_vector.getCPtr(valid_to_load), thread_count, skip_loaded);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read_metrics(string run_folder, uint last_cycle, uchar_vector valid_to_load, uint thread_count) {
    c_csharp_run_metricsPINVOKE.run_metrics_read_metrics__SWIG_2(swigCPtr, run_folder, last_cycle, uchar_vector.getCPtr(valid_to_load), thread_count);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void write_metrics(string run_folder, bool use_out) {
    c_csharp_run_metricsPINVOKE.run_metrics_write_metrics__SWIG_0(swigCPtr, run_folder, use_out);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void write_metrics(string run_folder) {
    c_csharp_run_metricsPINVOKE.run_metrics_write_metrics__SWIG_1(swigCPtr, run_folder);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void read_metrics_from_buffer(metric_group group, byte[] buffer, uint buffer_size) {
    unsafe{ fixed ( byte* swig_ptrTo_buffer = buffer ) {
    {
      c_csharp_run_metricsPINVOKE.run_metrics_read_metrics_from_buffer(swigCPtr, (int)group, (global::System.IntPtr)swig_ptrTo_buffer, buffer_size);
      if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    }
    }}
  }

  public void write_metrics_to_buffer(metric_group group, byte[] buffer, uint buffer_size) {
    unsafe{ fixed ( byte* swig_ptrTo_buffer = buffer ) {
    {
      c_csharp_run_metricsPINVOKE.run_metrics_write_metrics_to_buffer(swigCPtr, (int)group, (global::System.IntPtr)swig_ptrTo_buffer, buffer_size);
      if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    }
    }}
  }

  public uint calculate_buffer_size(metric_group group) {
    uint ret = c_csharp_run_metricsPINVOKE.run_metrics_calculate_buffer_size(swigCPtr, (int)group);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void validate() {
    c_csharp_run_metricsPINVOKE.run_metrics_validate(swigCPtr);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool is_group_empty(string group_name) {
    bool ret = c_csharp_run_metricsPINVOKE.run_metrics_is_group_empty__SWIG_0(swigCPtr, group_name);
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool is_group_empty(metric_group group_id) {
    bool ret = c_csharp_run_metricsPINVOKE.run_metrics_is_group_empty__SWIG_1(swigCPtr, (int)group_id);
    return ret;
  }

  public void populate_id_map(tile_metric_map map) {
    c_csharp_run_metricsPINVOKE.run_metrics_populate_id_map__SWIG_0(swigCPtr, tile_metric_map.getCPtr(map));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void populate_id_map(cycle_metric_map map) {
    c_csharp_run_metricsPINVOKE.run_metrics_populate_id_map__SWIG_1(swigCPtr, cycle_metric_map.getCPtr(map));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void populate_id_map(event_metric_map map) {
    c_csharp_run_metricsPINVOKE.run_metrics_populate_id_map__SWIG_2(swigCPtr, event_metric_map.getCPtr(map));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public void sort() {
    c_csharp_run_metricsPINVOKE.run_metrics_sort(swigCPtr);
  }

  public void clear() {
    c_csharp_run_metricsPINVOKE.run_metrics_clear(swigCPtr);
  }

  public void set_corrected_intensity_metric_set(base_corrected_intensity_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_corrected_intensity_metric_set(swigCPtr, base_corrected_intensity_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_corrected_intensity_metrics corrected_intensity_metric_set() {
    base_corrected_intensity_metrics ret = new base_corrected_intensity_metrics(c_csharp_run_metricsPINVOKE.run_metrics_corrected_intensity_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_error_metric_set(base_error_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_error_metric_set(swigCPtr, base_error_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_error_metrics error_metric_set() {
    base_error_metrics ret = new base_error_metrics(c_csharp_run_metricsPINVOKE.run_metrics_error_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_extraction_metric_set(base_extraction_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_extraction_metric_set(swigCPtr, base_extraction_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_extraction_metrics extraction_metric_set() {
    base_extraction_metrics ret = new base_extraction_metrics(c_csharp_run_metricsPINVOKE.run_metrics_extraction_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_image_metric_set(base_image_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_image_metric_set(swigCPtr, base_image_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_image_metrics image_metric_set() {
    base_image_metrics ret = new base_image_metrics(c_csharp_run_metricsPINVOKE.run_metrics_image_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_q_metric_set(base_q_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_q_metric_set(swigCPtr, base_q_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_q_metrics q_metric_set() {
    base_q_metrics ret = new base_q_metrics(c_csharp_run_metricsPINVOKE.run_metrics_q_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_tile_metric_set(base_tile_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_tile_metric_set(swigCPtr, base_tile_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_tile_metrics tile_metric_set() {
    base_tile_metrics ret = new base_tile_metrics(c_csharp_run_metricsPINVOKE.run_metrics_tile_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_index_metric_set(base_index_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_index_metric_set(swigCPtr, base_index_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_index_metrics index_metric_set() {
    base_index_metrics ret = new base_index_metrics(c_csharp_run_metricsPINVOKE.run_metrics_index_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_q_collapsed_metric_set(base_q_collapsed_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_q_collapsed_metric_set(swigCPtr, base_q_collapsed_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_q_collapsed_metrics q_collapsed_metric_set() {
    base_q_collapsed_metrics ret = new base_q_collapsed_metrics(c_csharp_run_metricsPINVOKE.run_metrics_q_collapsed_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_q_by_lane_metric_set(base_q_by_lane_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_q_by_lane_metric_set(swigCPtr, base_q_by_lane_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_q_by_lane_metrics q_by_lane_metric_set() {
    base_q_by_lane_metrics ret = new base_q_by_lane_metrics(c_csharp_run_metricsPINVOKE.run_metrics_q_by_lane_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_alignment_metric_set(base_alignment_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_alignment_metric_set(swigCPtr, base_alignment_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_alignment_metrics alignment_metric_set() {
    base_alignment_metrics ret = new base_alignment_metrics(c_csharp_run_metricsPINVOKE.run_metrics_alignment_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_basecalling_metric_set(base_basecalling_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_basecalling_metric_set(swigCPtr, base_basecalling_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_basecalling_metrics basecalling_metric_set() {
    base_basecalling_metrics ret = new base_basecalling_metrics(c_csharp_run_metricsPINVOKE.run_metrics_basecalling_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_color_matrix_metric_set(base_color_matrix_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_color_matrix_metric_set(swigCPtr, base_color_matrix_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_color_matrix_metrics color_matrix_metric_set() {
    base_color_matrix_metrics ret = new base_color_matrix_metrics(c_csharp_run_metricsPINVOKE.run_metrics_color_matrix_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_distortion_metric_set(base_distortion_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_distortion_metric_set(swigCPtr, base_distortion_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_distortion_metrics distortion_metric_set() {
    base_distortion_metrics ret = new base_distortion_metrics(c_csharp_run_metricsPINVOKE.run_metrics_distortion_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_dynamic_phasing_metric_set(base_dynamic_phasing_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_dynamic_phasing_metric_set(swigCPtr, base_dynamic_phasing_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_dynamic_phasing_metrics dynamic_phasing_metric_set() {
    base_dynamic_phasing_metrics ret = new base_dynamic_phasing_metrics(c_csharp_run_metricsPINVOKE.run_metrics_dynamic_phasing_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_event_metric_set(base_event_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_event_metric_set(swigCPtr, base_event_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_event_metrics event_metric_set() {
    base_event_metrics ret = new base_event_metrics(c_csharp_run_metricsPINVOKE.run_metrics_event_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_extended_tile_metric_set(base_extended_tile_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_extended_tile_metric_set(swigCPtr, base_extended_tile_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_extended_tile_metrics extended_tile_metric_set() {
    base_extended_tile_metrics ret = new base_extended_tile_metrics(c_csharp_run_metricsPINVOKE.run_metrics_extended_tile_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_fwhm_grid_metric_set(base_fwhm_grid_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_fwhm_grid_metric_set(swigCPtr, base_fwhm_grid_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_fwhm_grid_metrics fwhm_grid_metric_set() {
    base_fwhm_grid_metrics ret = new base_fwhm_grid_metrics(c_csharp_run_metricsPINVOKE.run_metrics_fwhm_grid_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_pf_grid_metric_set(base_pf_grid_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_pf_grid_metric_set(swigCPtr, base_pf_grid_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_pf_grid_metrics pf_grid_metric_set() {
    base_pf_grid_metrics ret = new base_pf_grid_metrics(c_csharp_run_metricsPINVOKE.run_metrics_pf_grid_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_phasing_metric_set(base_phasing_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_phasing_metric_set(swigCPtr, base_phasing_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_phasing_metrics phasing_metric_set() {
    base_phasing_metrics ret = new base_phasing_metrics(c_csharp_run_metricsPINVOKE.run_metrics_phasing_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_q_grid_metric_set(base_q_grid_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_q_grid_metric_set(swigCPtr, base_q_grid_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_q_grid_metrics q_grid_metric_set() {
    base_q_grid_metrics ret = new base_q_grid_metrics(c_csharp_run_metricsPINVOKE.run_metrics_q_grid_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_registration_metric_set(base_registration_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_registration_metric_set(swigCPtr, base_registration_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_registration_metrics registration_metric_set() {
    base_registration_metrics ret = new base_registration_metrics(c_csharp_run_metricsPINVOKE.run_metrics_registration_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_run_diagnostics_metric_set(base_run_diagnostics_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_run_diagnostics_metric_set(swigCPtr, base_run_diagnostics_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_run_diagnostics_metrics run_diagnostics_metric_set() {
    base_run_diagnostics_metrics ret = new base_run_diagnostics_metrics(c_csharp_run_metricsPINVOKE.run_metrics_run_diagnostics_metric_set(swigCPtr), false);
    return ret;
  }

  public void set_static_run_metric_set(base_static_run_metrics metrics) {
    c_csharp_run_metricsPINVOKE.run_metrics_set_static_run_metric_set(swigCPtr, base_static_run_metrics.getCPtr(metrics));
    if (c_csharp_run_metricsPINVOKE.SWIGPendingException.Pending) throw c_csharp_run_metricsPINVOKE.SWIGPendingException.Retrieve();
  }

  public base_static_run_metrics static_run_metric_set() {
    base_static_run_metrics ret = new base_static_run_metrics(c_csharp_run_metricsPINVOKE.run_metrics_static_run_metric_set(swigCPtr), false);
    return ret;
  }

}

}