/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.illumina.interop;

public final class affine_transform_type {
  public final static affine_transform_type TranslationX = new affine_transform_type("TranslationX");
  public final static affine_transform_type TranslationY = new affine_transform_type("TranslationY");
  public final static affine_transform_type MagnificationX = new affine_transform_type("MagnificationX");
  public final static affine_transform_type MagnificationY = new affine_transform_type("MagnificationY");
  public final static affine_transform_type ShearXY = new affine_transform_type("ShearXY");
  public final static affine_transform_type ShearYX = new affine_transform_type("ShearYX");
  public final static affine_transform_type AffineTransformComponentCount = new affine_transform_type("AffineTransformComponentCount");
  public final static affine_transform_type UnknownAffineTransformType = new affine_transform_type("UnknownAffineTransformType", interop_runJNI.UnknownAffineTransformType_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static affine_transform_type swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + affine_transform_type.class + " with value " + swigValue);
  }

  private affine_transform_type(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private affine_transform_type(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private affine_transform_type(String swigName, affine_transform_type swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static affine_transform_type[] swigValues = { TranslationX, TranslationY, MagnificationX, MagnificationY, ShearXY, ShearYX, AffineTransformComponentCount, UnknownAffineTransformType };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

