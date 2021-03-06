/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public final class metric_feature_type {
  public final static metric_feature_type TileFeature = new metric_feature_type("TileFeature", interop_runJNI.TileFeature_get());
  public final static metric_feature_type CycleFeature = new metric_feature_type("CycleFeature", interop_runJNI.CycleFeature_get());
  public final static metric_feature_type ReadFeature = new metric_feature_type("ReadFeature", interop_runJNI.ReadFeature_get());
  public final static metric_feature_type BaseFeature = new metric_feature_type("BaseFeature", interop_runJNI.BaseFeature_get());
  public final static metric_feature_type ChannelFeature = new metric_feature_type("ChannelFeature", interop_runJNI.ChannelFeature_get());
  public final static metric_feature_type LaneFeature = new metric_feature_type("LaneFeature", interop_runJNI.LaneFeature_get());
  public final static metric_feature_type SubtileFeature = new metric_feature_type("SubtileFeature", interop_runJNI.SubtileFeature_get());
  public final static metric_feature_type IUOFeature = new metric_feature_type("IUOFeature", interop_runJNI.IUOFeature_get());
  public final static metric_feature_type IntervalFeature = new metric_feature_type("IntervalFeature", interop_runJNI.IntervalFeature_get());
  public final static metric_feature_type UnknownMetricFeature = new metric_feature_type("UnknownMetricFeature", interop_runJNI.UnknownMetricFeature_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static metric_feature_type swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + metric_feature_type.class + " with value " + swigValue);
  }

  private metric_feature_type(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private metric_feature_type(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private metric_feature_type(String swigName, metric_feature_type swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static metric_feature_type[] swigValues = { TileFeature, CycleFeature, ReadFeature, BaseFeature, ChannelFeature, LaneFeature, SubtileFeature, IUOFeature, IntervalFeature, UnknownMetricFeature };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

