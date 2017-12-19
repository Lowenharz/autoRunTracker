/** Enumeration constants used throughout InterOp
 *
 *  @file
 *  @date 9/27/15
 *  @version 1.0
 *  @copyright Illumina Use Only
 */

#pragma once

#include <climits>
#include <limits>
#include <string>
#include "interop/util/cstdint.h"

/** Sentinel for an unknown enum type */
#define INTEROP_UNKNOWN 0x200


/** Enumeration of specific features that can belong to a metric
 *
 * @note This macro requires the macro INTEROP_TUPLE_ASSIGN to be defined before use
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::metric_feature_type
 */
#define INTEROP_ENUM_METRIC_FEATURE_TYPE \
        INTEROP_TUPLE_ASSIGN(TileFeature, 0x01), \
        INTEROP_TUPLE_ASSIGN(CycleFeature, 0x02), \
        INTEROP_TUPLE_ASSIGN(ReadFeature, 0x04), \
        INTEROP_TUPLE_ASSIGN(BaseFeature, 0x08), \
        INTEROP_TUPLE_ASSIGN(ChannelFeature, 0x10), \
        INTEROP_TUPLE_ASSIGN(LaneFeature, 0x20), \
        /** IUO */\
        INTEROP_TUPLE_ASSIGN(SubtileFeature, 0x40), \
        INTEROP_TUPLE_ASSIGN(IUOFeature, 0x80), \
        INTEROP_TUPLE_ASSIGN(IntervalFeature, 0x100), \
        INTEROP_TUPLE1(UnknownMetricFeature)
//NOTE: if we add any more features above, we should update the unknown metric value below

/** Enumeration of each metric type
 *
 * @note This macro requires the macro INTEROP_TUPLE4 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::metric_type
 */
#define INTEROP_ENUM_METRIC_TYPES \
        INTEROP_TUPLE7(Intensity, "Intensity", Extraction, CycleFeature|ChannelFeature, extraction_metric, max_intensity, channel)\
        INTEROP_TUPLE7(FWHM, "FWHM", Extraction, CycleFeature|ChannelFeature, extraction_metric, focus_score, channel)\
        INTEROP_TUPLE7(BasePercent, "% Base", CorrectedInt, CycleFeature|BaseFeature, corrected_intensity_metric, percent_base, base)\
        INTEROP_TUPLE7(PercentNoCall, "% NoCall", CorrectedInt, CycleFeature, corrected_intensity_metric, percent_nocall, Void)\
        INTEROP_TUPLE7(Q20Percent, "% >=Q20", Q, CycleFeature, q_collapsed_metric, percent_over_q20, Void)\
        INTEROP_TUPLE7(Q30Percent, "% >=Q30", Q, CycleFeature, q_collapsed_metric, percent_over_q30, Void)\
        INTEROP_TUPLE7(AccumPercentQ20, "% >=Q20 (Accumulated)", Q, CycleFeature, q_collapsed_metric, cumulative_percent_over_q20, Void)\
        INTEROP_TUPLE7(AccumPercentQ30, "% >=Q30 (Accumulated)", Q, CycleFeature, q_collapsed_metric, cumulative_percent_over_q30, Void)\
        INTEROP_TUPLE7(QScore, "Median QScore", Q, CycleFeature, q_collapsed_metric, median_qscore_flt, Void)\
        INTEROP_TUPLE7(Clusters, "Density", Tile, TileFeature, tile_metric, cluster_density_k, Void)\
        INTEROP_TUPLE7(ClustersPF, "Density PF", Tile, TileFeature, tile_metric, cluster_density_pf_k, Void)\
        INTEROP_TUPLE7(ClusterCount, "Cluster Count", Tile, TileFeature, tile_metric, cluster_count_m, Void)\
        INTEROP_TUPLE7(ClusterCountPF, "Clusters PF", Tile, TileFeature, tile_metric, cluster_count_pf_m, Void)\
        INTEROP_TUPLE7(ErrorRate, "Error Rate", Error, CycleFeature, error_metric, error_rate, Void)\
        INTEROP_TUPLE7(PercentPhasing, "% Phasing", Tile, ReadFeature, tile_metric, percent_phasing_at, read)\
        INTEROP_TUPLE7(PercentPrephasing, "% Prephasing", Tile, ReadFeature, tile_metric, percent_prephasing_at, read)\
        INTEROP_TUPLE7(PercentAligned, "% Aligned", Tile, ReadFeature, tile_metric, percent_aligned_at, read)\
        INTEROP_TUPLE7(Phasing, "Phasing", EmpiricalPhasing, CycleFeature, phasing_metric, phasing_weight, Void)\
        INTEROP_TUPLE7(PrePhasing, "PrePhasing", EmpiricalPhasing, CycleFeature, phasing_metric, prephasing_weight, Void)\
        INTEROP_TUPLE7(CorrectedIntensity, "Corrected Int", CorrectedInt, CycleFeature|BaseFeature, corrected_intensity_metric, corrected_int_all_float, base)\
        INTEROP_TUPLE7(CalledIntensity, "Called Int", CorrectedInt, CycleFeature|BaseFeature, corrected_intensity_metric, corrected_int_called, base)\
        INTEROP_TUPLE7(SignalToNoise, "Signal to Noise", CorrectedInt, CycleFeature, corrected_intensity_metric, signal_to_noise, Void)\
        /* IUO */ \
        INTEROP_TUPLE7(PercentPF, "% PF", Tile, TileFeature|IUOFeature, tile_metric, percent_pf, Void)\
        INTEROP_TUPLE7(MinContrast, "Min Contrast", Image, ChannelFeature|CycleFeature|IUOFeature, image_metric, min_contrast, channel)\
        INTEROP_TUPLE7(MaxContrast, "Max Contrast", Image, ChannelFeature|CycleFeature|IUOFeature, image_metric, max_contrast, channel)\
        INTEROP_TUPLE4(SubtilePFPercent, "% PF", PFGrid, SubtileFeature|IUOFeature)/*, pf_grid_metric, percent_pf, xybin)*/\
        INTEROP_TUPLE4(SubtileClustersPF, "Clusters PF", PFGrid, SubtileFeature|IUOFeature)/*, pf_grid_metric, pf_cluster_count, xybin)*/\
        INTEROP_TUPLE4(SubtileDensityPF, "Density PF", PFGrid, SubtileFeature|IUOFeature)/*, pf_grid_metric, pf_cluster_density_k, xybin)*/\
        INTEROP_TUPLE4(SubtileFwhm, "FWHM", FWHMGrid, SubtileFeature|CycleFeature|ChannelFeature|IUOFeature)/*, fwhm_grid_metric, focus_score, channel_xybin)*/\
        INTEROP_TUPLE4(SubtileQ30Percent, "% >= Q30", QGrid, SubtileFeature|ReadFeature|IUOFeature)/*, q_grid_metric, percent_q30, xybin)*/\
        INTEROP_TUPLE4(SubtileDensity, "Density", PFGrid, SubtileFeature|IUOFeature)/*, pf_grid_metric, raw_cluster_density_k, xybin)*/\
        INTEROP_TUPLE4(SubtileClusters, "Clusters", PFGrid, SubtileFeature|IUOFeature)/*, pf_grid_metric, raw_cluster_count, xybin)*/\
        INTEROP_TUPLE4(DistortionByTile, "Distortion By Tile", OpticalModel, ChannelFeature|TileFeature|IUOFeature)/*, distortion_metric, populate_coefficients_for, channel_curve)*/\
        INTEROP_TUPLE4(EventByCycle, "Event By Cycle", Event, CycleFeature|IUOFeature)/*, event_metric, elapsed_ms, Void)*/\
        INTEROP_TUPLE4(EventByType, "Event By Type", Event, IUOFeature)/*, event_metric, elapsed_ms, Void)*/\
        INTEROP_TUPLE7(MaxResidualR, "Max Residual Radius", Registration, CycleFeature|IUOFeature|ChannelFeature, registration_metric, max_residual_radial_error, channel)\
        INTEROP_TUPLE7(Theta, "Rotation (Deg)", Registration, CycleFeature|IUOFeature|ChannelFeature, registration_metric, theta, channel)\
        INTEROP_TUPLE7(ThetaZ, "Rotation on Z (Deg)", Registration, CycleFeature|IUOFeature|ChannelFeature, registration_metric, theta_z, channel)\
        INTEROP_TUPLE7(OccupiedCountK, "Occupied Count (K)", ExtendedTile, TileFeature|IUOFeature, extended_tile_metric, cluster_count_occupied_k, Void)\
        INTEROP_TUPLE7(PercentOccupied, "% Occupied", ExtendedTile, TileFeature|IUOFeature, extended_tile_metric, percent_occupied_lookup, tile_metrics)\
        INTEROP_TUPLE4(MetricTypeCount, "!!!!BAD!!!!", UnknownMetricGroup, UnknownMetricFeature)/*, base_metric, lane, Void)*/\
        INTEROP_TUPLE1(UnknownMetricType)/*, base_metric, lane, Void)*/

/** Enumeration of each metric group
 *
 * @note This macro requires the macro INTEROP_TUPLE2 to be defined before use
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::metric_group
 */
#define INTEROP_ENUM_METRIC_GROUPS \
        INTEROP_TUPLE2(CorrectedInt, CycleFeature|BaseFeature), \
        INTEROP_TUPLE2(Error, CycleFeature), \
        INTEROP_TUPLE2(Extraction, CycleFeature|ChannelFeature), \
        INTEROP_TUPLE2(Image, CycleFeature|ChannelFeature), \
        INTEROP_TUPLE2(Index, ReadFeature), \
        INTEROP_TUPLE2(Q, CycleFeature), \
        INTEROP_TUPLE2(Tile, TileFeature), \
        INTEROP_TUPLE2(QByLane, LaneFeature), \
        INTEROP_TUPLE2(QCollapsed, CycleFeature), \
        INTEROP_TUPLE2(EmpiricalPhasing, CycleFeature), \
        INTEROP_TUPLE2(DynamicPhasing, CycleFeature), \
        /* IUO */ \
        INTEROP_TUPLE2(ExtendedTile, TileFeature|IUOFeature), \
        INTEROP_TUPLE2(Event, CycleFeature|IntervalFeature|IUOFeature), \
        INTEROP_TUPLE2(Registration, ChannelFeature|CycleFeature|IUOFeature), \
        INTEROP_TUPLE2(BaseCalling, BaseFeature|CycleFeature|IUOFeature), \
        INTEROP_TUPLE2(Alignment, BaseFeature|CycleFeature|IUOFeature), \
        INTEROP_TUPLE2(PFGrid, TileFeature|SubtileFeature|IUOFeature), \
        INTEROP_TUPLE2(QGrid, ReadFeature|SubtileFeature|IUOFeature), \
        INTEROP_TUPLE2(FWHMGrid, CycleFeature|SubtileFeature|IUOFeature), \
        INTEROP_TUPLE2(StaticRun, IUOFeature), \
        INTEROP_TUPLE2(ColorMatrix, BaseFeature|CycleFeature|IUOFeature), \
        INTEROP_TUPLE2(OpticalModel, IUOFeature), \
        INTEROP_TUPLE2(RunDiagnostics, CycleFeature|IUOFeature), \
        INTEROP_TUPLE1(MetricCount), \
        INTEROP_TUPLE1(UnknownMetricGroup)


/** Enumeration of each metric data type
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::metric_data
 */
#define INTEROP_ENUM_METRIC_DATA_TYPES \
        INTEROP_TUPLE1(IdType), \
        INTEROP_TUPLE1(ValueType), \
        INTEROP_TUPLE1(StructType), \
        INTEROP_TUPLE1(ChannelArray), \
        INTEROP_TUPLE1(BaseArray), \
        /* IUO */ \
        INTEROP_TUPLE1(UpperLeftPoint), \
        INTEROP_TUPLE1(AffineTransformArray), \
        INTEROP_TUPLE1(SubTileOffsetArray), \
        INTEROP_TUPLE1(BaseXYArray), \
        INTEROP_TUPLE1(Base2DArray), \
        INTEROP_TUPLE1(ColorMatrixArray), \
        INTEROP_TUPLE1(RunDiagnosticsArray), \
        INTEROP_TUPLE1(MetricDataCount), \
        INTEROP_TUPLE1(UnknownMetricData)

/** Enumeration of tile naming methods
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @see illumina::interop::constants::tile_naming_method
 */
#define INTEROP_ENUM_TILE_NAMING_METHODS \
        /** Four digit tiles for HiSeq and modern MiSeqs */\
        INTEROP_TUPLE1(FourDigit), \
        /** Five digit tiles for NextSeq and ... */\
        INTEROP_TUPLE1(FiveDigit), \
        /** Absolute naming for tiles GAs and old MiSeqs*/\
        INTEROP_TUPLE1(Absolute), \
        /** Number of naming methods */\
        INTEROP_TUPLE1(TileNamingMethodCount), \
        INTEROP_TUPLE1(UnknownTileNamingMethod)

/** Enumeration of DNA bases
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note This macro requires the macro INTEROP_TUPLE_ASSIGN to be defined before use
 * @see illumina::interop::constants::dna_bases
 */
#define INTEROP_ENUM_DNA_BASE_TYPES \
        /** No calls */ \
        INTEROP_TUPLE_ASSIGN(NC, -1), \
        /** DNA base adenine */ \
        INTEROP_TUPLE1(A), \
        /** DNA base cytosine */ \
        INTEROP_TUPLE1(C), \
        /** DNA base guanine */ \
        INTEROP_TUPLE1(G), \
        /** DNA base thymine */ \
        INTEROP_TUPLE1(T), \
        /** Number of bases */ \
        INTEROP_TUPLE1(NUM_OF_BASES), \
        /** Number of bases including no calls*/ \
        INTEROP_TUPLE1(NUM_OF_BASES_AND_NC), \
        /** Unknown base */ \
        INTEROP_TUPLE1(UnknownBase)

/** Enumeration of surface types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @see illumina::interop::constants::surface_type
 */
#define INTEROP_ENUM_SURFACE_TYPES \
        INTEROP_TUPLE1(SentinelSurface), \
        INTEROP_TUPLE1(Top), \
        INTEROP_TUPLE1(Bottom), \
        INTEROP_TUPLE1(UnknownSurface)


/** Enumeration of instrument types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @see illumina::interop::constants::instrument_type
 */
#define INTEROP_ENUM_INSTRUMENT_TYPES \
        INTEROP_TUPLE1(HiSeq), \
        INTEROP_TUPLE1(HiScan), \
        INTEROP_TUPLE1(MiSeq), \
        INTEROP_TUPLE1(NextSeq), \
        INTEROP_TUPLE1(MiniSeq), \
        INTEROP_TUPLE1(NovaSeq), \
        INTEROP_TUPLE1(InstrumentCount), \
        INTEROP_TUPLE1(UnknownInstrument)

/** Enumeration of metric types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::metric_base_type
 */
#define INTEROP_ENUM_METRIC_BASE_TYPES \
        /** Tile base types are written out once for each tile */\
        INTEROP_TUPLE1(BaseTileType), \
        /** Cycle base types are written out once for each tile and cycle */\
        INTEROP_TUPLE1(BaseCycleType), \
        /** Read base types are written out once for each tile and read */\
        INTEROP_TUPLE1(BaseReadType), \
        /** Lane base types are written out once for each lane and cycle */\
        INTEROP_TUPLE1(BaseLaneType), \
        /** Metrics written out once per run */\
        INTEROP_TUPLE1(BaseRunType), \
        /*TODO: replace this and the V2 below with a more robust framework*/\
        /** Hack for reading broken event metric format */\
        INTEROP_TUPLE1(BaseEventV1Type), \
        /** Hack for reading broken event metric format */\
        INTEROP_TUPLE1(BaseEventV2Type), \
        INTEROP_TUPLE1(BaseMetricCount), \
        INTEROP_TUPLE1(UnknownBaseType)


/** Enumeration of channel colors (assuming expected order)
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::plot_colors
 */
#define INTEROP_ENUM_PLOT_COLORS \
        /** Color for red channel (or A) */\
        INTEROP_TUPLE1(Red), /*#FF0000*/\
        /** Color for green channel or (C) */\
        INTEROP_TUPLE1(Green), /*#00FF00*/\
        /** Color for G */\
        INTEROP_TUPLE1(Blue), /*#0000FF*/\
        /** Color for T */\
        INTEROP_TUPLE1(Black), /*#000000*/\
        INTEROP_TUPLE1(PlotColorCount), \
        INTEROP_TUPLE1(UnknownColor)

/** Enumeration of plot types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note Has IUO metrics
 * @see illumina::interop::constants::plot_types
 */
#define INTEROP_ENUM_PLOT_TYPES \
        /** Spatial plot by tile */\
        INTEROP_TUPLE1(FlowcellPlot), \
        /** Plot data aggrergated by cycle */\
        INTEROP_TUPLE1(ByCyclePlot), \
        /** Spatial plot aggrergated by lane */\
        INTEROP_TUPLE1(ByLanePlot), \
        /** Histogram of q-scores */\
        INTEROP_TUPLE1(QHistogramPlot), \
        /** Heatmap of q-scores by cycle */\
        INTEROP_TUPLE1(QHeatmapPlot), \
        /** Indexing tab plot */\
        INTEROP_TUPLE1(SampleQCPlot), \
        /* IUO */ \
        /** Plot distortion by tile */\
        INTEROP_TUPLE1(DistortionByTilePlot), \
        /** Plot sub tile aggregation in x */\
        INTEROP_TUPLE1(SubTileAggregateXPlot), \
        /** Plot sub tile aggregation in y */\
        INTEROP_TUPLE1(SubTileAggregateYPlot), \
        /** Plot sub tile flowcell and zoom */\
        INTEROP_TUPLE1(SubTileFlowCellPlot), \
        INTEROP_TUPLE1(EventByCyclePlot), \
        INTEROP_TUPLE1(EventByTypePlot), \
        /** Unknown plot type */\
        INTEROP_TUPLE1(UnknownPlotType)

/** Enumeration of bar plot options
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @see illumina::interop::constants::bar_plot_options
 */
#define INTEROP_ENUM_BAR_PLOT_OPTIONS \
        /** Bar centered on x-value */\
        INTEROP_TUPLE1(Centered), \
        /** Bar shifted to start on x-value */\
        INTEROP_TUPLE1(Shifted), \
        INTEROP_TUPLE1(UnknownBarPlotOption)

/////////////////////////////////////////////////////////////////////////////////////////////////////
// IUO
/////////////////////////////////////////////////////////////////////////////////////////////////////

/** Enumeration of affine transform components
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::affine_transform_type
 */
#define INTEROP_ENUM_AFFINE_TRANSFORM_TYPES \
        INTEROP_TUPLE1(TranslationX), \
        INTEROP_TUPLE1(TranslationY), \
        INTEROP_TUPLE1(MagnificationX), \
        INTEROP_TUPLE1(MagnificationY), \
        INTEROP_TUPLE1(ShearXY), \
        INTEROP_TUPLE1(ShearYX), \
        INTEROP_TUPLE1(AffineTransformComponentCount), \
        INTEROP_TUPLE1(UnknownAffineTransformType)

/** Enumeration of subtile offset components
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::sub_tile_offset_type
 */
#define INTEROP_ENUM_SUB_TILE_OFFSET_TYPES \
        INTEROP_TUPLE1(OffsetX), \
        INTEROP_TUPLE1(OffsetY), \
        INTEROP_TUPLE1(Score), \
        INTEROP_TUPLE1(SubTileOffsetComponentCount), \
        INTEROP_TUPLE1(UnknownSubTileOffsetType)

/** Enumeration of subtile offset region IDs
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::sub_tile_region_names
 */
#define INTEROP_ENUM_SUB_TILE_REGION_NAMES \
        INTEROP_TUPLE1(NNW), \
        INTEROP_TUPLE1(NNE), \
        INTEROP_TUPLE1(NW), \
        INTEROP_TUPLE1(NE), \
        INTEROP_TUPLE1(SW), \
        INTEROP_TUPLE1(SE), \
        INTEROP_TUPLE1(SSW), \
        INTEROP_TUPLE1(SSE), \
        INTEROP_TUPLE1(SubTileRegionCount), \
        INTEROP_TUPLE1(UnknownSubTileRegionName)


/** Enumeration of bar plot options
 *
 * @note This macro requires the macros INTEROP_TUPLE_FEATURE and INTEROP_TUPLE_ASSIGN_AND_FEATURE to be defined before use
 * @note IUO
 * @see illumina::interop::constants::bar_plot_options
 */
#define INTEROP_ENUM_EVENT_TYPE \
        INTEROP_TUPLE_FEATURE(RtaStarted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(CycleStarted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(TemplateGenerationStarted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(TemplateGenerationCompleted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(PostTemplateMaxClustersInit, IUOFeature), \
        INTEROP_TUPLE_FEATURE(SystemMemoryAvailableGigabyte, IUOFeature), \
        INTEROP_TUPLE_FEATURE(RegistrationAndExtraction, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(NeighborCorrection, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(ColorMatrixCorrection, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(TemplateGeneration, IUOFeature), \
        INTEROP_TUPLE_FEATURE(BasecallingAndQualityScoring, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(SequenceAlignment, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(BclWriting, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(ReadStarted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(ReadCompleted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(FilterAlignStarted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(FilterAlignCompleted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(CycleCompleted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(RtaCompleted, IUOFeature), \
        INTEROP_TUPLE_FEATURE(IntensityFileReading, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(IntensityFileWriting, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(TemplateGenerationImageStored, IUOFeature), /*Last RTA2 Legacy Enum*/ \
        INTEROP_TUPLE_FEATURE(RegistrationDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(ExtractionDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(SpatialNormalizationDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(PhasingCorrectionDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(RtaReadyToProcess, IUOFeature),/* Last RTA3 Legacy Enum */ \
        INTEROP_TUPLE_FEATURE(CalibrateDistortionDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(FocusEstimationDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(AddBCLDuration, IntervalFeature|IUOFeature), /*Zipping and PF filtering time*/\
        INTEROP_TUPLE_FEATURE(AddFilterFileDuration, IntervalFeature|IUOFeature),/*Hard disk write time*/\
        INTEROP_TUPLE_FEATURE(WriteThumbNailDuration, IntervalFeature|IUOFeature),/*Hard disk write time*/\
        INTEROP_TUPLE_FEATURE(WriteFullImageDuration, IntervalFeature|IUOFeature),/*Hard disk write time*/\
        INTEROP_TUPLE_FEATURE(SharpeningDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(BasecallReportingDuration, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(EventTypeCount, IUOFeature), \
        INTEROP_TUPLE_ASSIGN_AND_FEATURE(BasecallingAndQualityScoringDuration, BasecallingAndQualityScoring, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_ASSIGN_AND_FEATURE(SequenceAlignmentDuration, SequenceAlignment, IntervalFeature|IUOFeature), \
        INTEROP_TUPLE_FEATURE(UnknownEvent, IUOFeature)

/** Enumeration of distortion types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::distortion_type
 * @see illumina::interop::model::metrics::static_run_metric.h
 */
#define INTEROP_ENUM_DISTORTION_TYPE \
        INTEROP_TUPLE1(XFieldOfViewYDistortion), \
        INTEROP_TUPLE1(XFieldOfViewXDistortion), \
        INTEROP_TUPLE1(Radial), \
        INTEROP_TUPLE1(UnknownDistortion)

/** Enumeration of distortion curve types
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::distortion_curve_type
 * @see illumina::interop::model::metrics::distortion_metric.h
 */
#define INTEROP_ENUM_DISTORTION_CURVE_TYPE \
        INTEROP_TUPLE1(DistortionXonX), \
        INTEROP_TUPLE1(DistortionXYonX), \
        INTEROP_TUPLE1(UnknownDistortionCurve)

/** Enumeration of run diagnostics issues
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note This macro requires the macro INTEROP_TUPLE_ASSIGN to be defined before use
 * @note IUO
 * @see illumina::interop::constants::run_diagnostics_issue_type
 * @see illumina::interop::model::metrics::run_diagnostics_metric.h
 */
#define INTEROP_ENUM_RUN_DIAGNOSTICS_ISSUE_TYPE \
        INTEROP_TUPLE_ASSIGN(AllIssues, -1), \
        INTEROP_TUPLE1(DeadTile), \
        INTEROP_TUPLE1(BlankImage), \
        INTEROP_TUPLE1(FailedCycle), \
        INTEROP_TUPLE1(QOutliers), \
        INTEROP_TUPLE1(RunDiagnosticsIssueCount), \
        INTEROP_TUPLE1(UnknownRunDiagnosticsIssueType)


/** Enumeration of common layout types for locs or fiducials
 *
 * @note This macro requires the macro INTEROP_TUPLE1 to be defined before use
 * @note IUO
 * @see illumina::interop::constants::layout_type
 * @see illumina::interop::model::metrics::registration_metric
 */
#define INTEROP_ENUM_LAYOUT_TYPE \
        INTEROP_TUPLE1(SquareLayout), \
        INTEROP_TUPLE1(HexLayout), \
        INTEROP_TUPLE1(LayoutCount), \
        INTEROP_TUPLE1(UnknownLayout)

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Define x-macros
/////////////////////////////////////////////////////////////////////////////////////////////////////


/** This temp macro converts a enum/description pair into the an enum (first element of the pair) */
#define INTEROP_TUPLE7(X, Unused1, Unused2, Unused3, Unused4, Unused5, Unused6) X,
/** This temp macro converts a enum/description pair into the an enum (first element of the pair) */
#define INTEROP_TUPLE4(X, Y, Z, A) X,
/** This temp macro converts a enum/description pair into the an enum (first element of the pair) */
#define INTEROP_TUPLE3(X, Y, Z) X
/** This temp macro converts an enum to an enum */
#define INTEROP_TUPLE1(X) X
/** This temp macro converts an enum/value pair to an enum */
#define INTEROP_TUPLE2(X, V) X
/** This temp macro converts an enum/value pair to an enum */
#define INTEROP_TUPLE_ASSIGN(X, V) X=V
/** This temp macro assigns the second element to equal the first, and sets a description for the 3rd element */
#define INTEROP_TUPLE_ASSIGN_AND_FEATURE(X, V, Z) X=V
/** This temp macro sets a description for the 2nd element */
#define INTEROP_TUPLE_FEATURE(X, Y) X


namespace illumina { namespace interop { namespace constants
{
    /** Common codes for all enums */
    enum common
    {
        Unknown = INTEROP_UNKNOWN
    };
    /** Codes for each metric type */
    enum metric_type
    {
        INTEROP_ENUM_METRIC_TYPES = INTEROP_UNKNOWN
    };
    /** Codes for each metric group */
    enum metric_group
    {
        INTEROP_ENUM_METRIC_GROUPS = INTEROP_UNKNOWN
    };
    /** Tile naming conventions used in various Illumina Platforms */
    enum tile_naming_method
    {
        INTEROP_ENUM_TILE_NAMING_METHODS = INTEROP_UNKNOWN
    };
    /** DNA base constants */
    enum dna_bases
    {
        INTEROP_ENUM_DNA_BASE_TYPES = INTEROP_UNKNOWN
    };
    /** Flow cell surface code */
    enum surface_type
    {
        INTEROP_ENUM_SURFACE_TYPES = INTEROP_UNKNOWN
    };
    /** Instrument type */
    enum instrument_type
    {
        INTEROP_ENUM_INSTRUMENT_TYPES = INTEROP_UNKNOWN
    };
    /** Base types for each metric */
    enum metric_base_type
    {
        INTEROP_ENUM_METRIC_BASE_TYPES = INTEROP_UNKNOWN
    };
    /** Color codes for plotting */
    enum plot_colors
    {
        INTEROP_ENUM_PLOT_COLORS = INTEROP_UNKNOWN
    };
    /** Options for a bar plot */
    enum bar_plot_options
    {
        INTEROP_ENUM_BAR_PLOT_OPTIONS = INTEROP_UNKNOWN
    };
    /** Options for a bar plot */
    enum metric_data
    {
        INTEROP_ENUM_METRIC_DATA_TYPES = INTEROP_UNKNOWN
    };
    /** Options describing metric features */
    enum metric_feature_type
    {
        INTEROP_ENUM_METRIC_FEATURE_TYPE = INTEROP_UNKNOWN
    };
    /** Options for a bar plot */
    enum plot_types
    {
        INTEROP_ENUM_PLOT_TYPES = INTEROP_UNKNOWN
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // IUO
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Affine transform components for registration metrics
     * @note IUO
     */
    enum affine_transform_type
    {
        INTEROP_ENUM_AFFINE_TRANSFORM_TYPES = INTEROP_UNKNOWN
    };
    /** Sub-tile offset components for registration metrics
     * @note IUO
     */
    enum sub_tile_offset_type
    {
        INTEROP_ENUM_SUB_TILE_OFFSET_TYPES = INTEROP_UNKNOWN
    };
    /** Sub-tile region names for registration metrics
     * @note IUO
     */
    enum sub_tile_region_name
    {
        INTEROP_ENUM_SUB_TILE_REGION_NAMES = INTEROP_UNKNOWN
    };
    /** Event types
     * @note IUO
     */
    enum event_type
    {
        INTEROP_ENUM_EVENT_TYPE = INTEROP_UNKNOWN
    };

    /** Options describing distortion types
     * @note IUO
     */
    enum distortion_type
    {
        INTEROP_ENUM_DISTORTION_TYPE = INTEROP_UNKNOWN
    };
    /** Options describing distortion curve types
     * @note IUO
     */
    enum distortion_curve_type
    {
        INTEROP_ENUM_DISTORTION_CURVE_TYPE = INTEROP_UNKNOWN
    };
    /** Options describing run diagnostics issue types
     * @note IUO
     */
    enum run_diagnostics_issue_type
    {
        INTEROP_ENUM_RUN_DIAGNOSTICS_ISSUE_TYPE = INTEROP_UNKNOWN
    };
    /** Enumeration of common layout types for locs or fiducials
     *
     * @note IUO
     * @see illumina::interop::model::metrics::registration_metric
     */
    enum layout_type
    {
        INTEROP_ENUM_LAYOUT_TYPE = INTEROP_UNKNOWN
    };
}}}

#undef INTEROP_TUPLE1
#undef INTEROP_TUPLE2
#undef INTEROP_TUPLE3
#undef INTEROP_TUPLE4
#undef INTEROP_TUPLE7
#undef INTEROP_TUPLE_ASSIGN
#undef INTEROP_TUPLE_ASSIGN_AND_FEATURE
#undef INTEROP_TUPLE_FEATURE
