#!/usr/bin/env python2.7
'''

Works with Miniconda2 with matplotlib and pyInterOp

This script reads in a list of run folders and generates a plot of the distortion curves for each one

> plot_distortion_curves.py run-folder1 run-folder2 .... run-folderN
'''

import argparse
import os
import numpy
import pylab
import matplotlib
import matplotlib.cm as cm
import logging
try:
    from interop import py_interop_run
except:
    print("Install interop with: pip install -f https://ussd.artifactory.illumina.com/list/generic-bioinformatics/interop/pypi/ interop ")
    raise
from interop import py_interop_metrics
from interop import py_interop_run_metrics

_logger = logging.getLogger(__name__)

def create_plot_for_tile(metric, index_for_channels, x_values):
    ''' Generate the distortion curve for a tile

    :param metric: distortion metric
    :param index_for_channels mapping for coefficients to curve type and channel
    :return: numpy array of curve for each model
    '''

    curve_for_channels=[]
    for curve_for_channel in index_for_channels:
        curve_for_types=[]
        for curve_for_type in curve_for_channel:
            coeff = numpy.asarray([metric.coefficient_at(i) for i in curve_for_type])
            curve_for_types.append(numpy.polyval(list(coeff)+[0], x_values))
        curve_for_channels.append(curve_for_types)
    return metric.lane(), metric.tile(), curve_for_channels

def create_plot(distortion_metric_set):
    ''' Generate the x and y for the plot

    TODO: add some type of filtering

    :param distortion_metric_set:
    :return: numpy array of curve for each model
    '''

    if distortion_metric_set.empty():
        raise RuntimeError("No distortion metrics")

    if distortion_metric_set.type() != py_interop_run.DistortionXonX:
        raise RuntimeError("Distortion type not supported: %s"%distortion_metric_set.type())

    index_for_channels = []
    for channel in xrange(distortion_metric_set.channel_count()):
        index_for_types = []
        for curve in xrange(distortion_metric_set.curve_count()):
            index_of_coeff=[
                distortion_metric_set.index(channel, curve, coeff)
                for coeff in xrange(distortion_metric_set.coefficient_count(curve))
                ]
            index_for_types.append(numpy.asarray(index_of_coeff))
        index_for_channels.append(index_for_types)

    plots=[]
    image_width = distortion_metric_set.image_width()
    x_values = numpy.arange(-image_width/2, image_width/2+1)
    for i in xrange(distortion_metric_set.size()):
        curve = create_plot_for_tile(distortion_metric_set.at(i), index_for_channels, x_values)
        plots.append(curve)
    return plots, x_values

def parse_log_file(run_folder, run_info):
    ''' Parse the coefficients from the log file

    Legacy function, will be removed at some point in the future

    :param run_folder:
    :return:
    '''

    fin = open(os.path.join(run_folder, "Logs", "info_00000.log"))
    prefix = "New distortion coefficients: "
    prefix2 = "Final distortion coefficients are "
    tile_prefix="Tile "

    image_width=run_info.dimensions_of_image().width()
    x_values = numpy.arange(-image_width/2, image_width/2+1)

    curve = []
    for line in fin:
        n = line.find(prefix)
        if n==-1:
            n = line.find(prefix2)
            if n == -1: continue
            n += len(prefix2)
        else:
            n += len(prefix)

        b = line.find(tile_prefix)+len(tile_prefix)
        e = line.find(",", b+1)
        lane, tile = line[b:e].split('_')
        coefficients = numpy.asarray([float(v.strip()) for v in line[n:].replace(' ', ',').split(',') if v.strip() != ""])
        coefficients = coefficients.reshape((1, 2, coefficients.shape[0]/2))
        curve_for_channels=[]
        for curves_for_channel in coefficients:
            curve_for_types=[]
            for coeff in curves_for_channel:
                curve_for_types.append(numpy.polyval(list(coeff)+[0], x_values))
            curve_for_channels.append(curve_for_types)
        curve.append((lane, tile, curve_for_channels))
    fin.close()
    return curve, x_values

def create_figure(prefix, output=None, dpi=72, **extra):
    ''' Create a figure for display or write image to disk

    :param prefix: run folder name
    :param dpi: resolution
    :param extra:
    :return:
    '''

    fig = pylab.figure(dpi=dpi if output != "" else None, frameon=False)
    fig.suptitle(prefix)
    yield fig
    if output is not None:
        fig.savefig(os.path.join(os.path.dirname(output), prefix+"_"+os.path.basename(output)), dpi=dpi, bbox_inches='tight')

def process_files(run_folders, channel, curve_type, **extra):
    ''' Read the InterOp data and plot the distortion curves for each input run folder

    :param run_folders: list of run folders to process
    :param output: output image name (optional)
    :param extra: unused arguments
    '''

    run_metrics = py_interop_run_metrics.run_metrics()
    valid_to_load = py_interop_run.uchar_vector(py_interop_run.MetricCount, 0)
    valid_to_load[py_interop_run.OpticalModel]=1
    run_coeff_map={}
    channels=None
    selected_channel_index=-1
    for run_folder in run_folders:
        _logger.info("Parsing coefficients for %s"%run_folder)
        basename = os.path.basename(run_folder)
        try:
            run_metrics.read(run_folder, valid_to_load)
        except:
            _logger.warn("Skipping - cannot read RunInfo.xml: %s"%basename)
            continue
        if channels is None:
            channels = [name.lower() for name in run_metrics.run_info().channels()]
            try:
                selected_channel_index = channels.index(channel.lower())
            except:
                selected_channel_index=-1
                if channel != "All": raise RuntimeError("Channel not found: %s not in %s"%(channel, ",".join(channels)))
        if basename == "": basename=os.path.basename(os.path.dirname(run_folder))
        if run_metrics.distortion_metric_set().empty():
            _logger.info("No distortion coefficients found: Parsing log file")
            try:
                run_coeff_map[basename]=parse_log_file(run_folder, run_metrics.run_info())
            except:
                _logger.warn("Skipping - cannot parse log file: %s"%basename)
                continue
        else:
            run_coeff_map[basename]=create_plot(run_metrics.distortion_metric_set())

    if len(run_coeff_map) == 0:
        raise Exception("No run folders read")
    if selected_channel_index == -1:
        raise NotImplementedError("All channels is not implemented")

    colormap = cm.cool
    lane_count = run_metrics.run_info().flowcell().lane_count()
    surface_count = run_metrics.run_info().flowcell().surface_count()
    lane_surface_norm=matplotlib.colors.Normalize(vmin=0, vmax=surface_count*lane_count)
    for run_folder, (y_values, x_values) in run_coeff_map.iteritems():
        _logger.info("Drawing curves for %s, %d"%(run_folder, len(y_values)))
        if len(y_values) == 0:
            _logger.warn("Skipping %s - missing curve"%run_folder)
            continue
        for fig in create_figure(run_folder, **extra):
            pylab.title(run_folder)
            pylab.xlabel("Distance from Center of Image")
            pylab.ylabel("Distortion (Pixels)")
            has_label={}
            for lane, tile, y_for_channel in y_values:
                surface=int(str(tile)[0])
                lane = int(lane)
                lane_surface = (surface-1)*lane_count+lane-1
                label = None
                if lane_surface not in has_label:
                    has_label[lane_surface]=True
                    label = "%d_%d"%(lane, surface)
                pylab.plot(x_values, y_for_channel[selected_channel_index][curve_type], color=colormap(lane_surface_norm(lane_surface)), label=label)
            pylab.legend(loc='upper center')
        if extra['output'] == "": pylab.show()

def main():
    ''' Parse arguments from the command line
    '''

    logging.basicConfig(level=logging.INFO)
    distortionTypes = py_interop_run.string_vector()
    py_interop_run.list_distortion_curve_type(distortionTypes)
    distortionTypes = [distortionTypes[i] for i in xrange(len(distortionTypes))]

    parser = argparse.ArgumentParser(description="This script reads in a list of run folders and generates a plot of the distortion curves", add_help=True)
    parser.add_argument("run_folders", help="Input run folders", nargs="+")
    parser.add_argument("-o", "--output", help="Output image filename (if not specified, then a window is opened)", default="")
    parser.add_argument("-c", "--channel", help="Selected a specific channel, All means all", default="All")
    parser.add_argument("-t", "--curve-type", help="Index of plot to select (default: 0 and -1 selects all) - available: "+",".join(distortionTypes[:-1]), type=int, default=0)
    parser.add_argument("--dpi", help="Resolution of the output image", type=int, default=300)
    arguments = parser.parse_args()
    process_files(**vars(arguments))

if __name__ == '__main__':
    main()

