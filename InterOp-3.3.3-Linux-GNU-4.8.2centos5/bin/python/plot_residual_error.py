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
from collections import defaultdict
try:
    import py_interop_run
except:
    import sys
    sys.path.append(".")
    exepath = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(sys.argv[0]))))
    alt = os.path.abspath(os.path.join(exepath, "lib64", "python"))
    if os.path.exists(alt):
        sys.path.append(alt)
    import py_interop_run
import py_interop_metrics

_logger = logging.getLogger(__name__)

def create_plot_cycle(registration_metric_set, channel):
    ''' Generate the x and y for the plot

    TODO: add some type of filtering

    :param distortion_metric_set:
    :return: numpy array of curve for each model
    '''

    if registration_metric_set.empty():
        raise RuntimeError("No registration metrics")
    data = defaultdict(list)
    for i in xrange(registration_metric_set.size()):
        err = registration_metric_set.at(i).max_residual_radial_error() if channel == -1 else registration_metric_set.at(i).max_residual_radial_error(channel)
        if numpy.isnan(err): continue
        if err > 1: err = 1.1
        data[registration_metric_set.at(i).cycle()].append(err)
    meandata = []
    for cycle, errors in data.iteritems():
        meandata.append((cycle, numpy.mean(errors)))
    return numpy.asarray(meandata)

def create_plot_focus(registration_metric_set, extraction_metric_set, channel):
    ''' Generate the x and y for the plot

    TODO: add some type of filtering

    :param distortion_metric_set:
    :return: numpy array of curve for each model
    '''

    if registration_metric_set.empty():
        raise RuntimeError("No registration metrics")

    if extraction_metric_set.empty():
        raise RuntimeError("No Extraction metrics")
    data = {}
    for i in xrange(extraction_metric_set.size()):
        err = registration_metric_set.at(i).max_residual_radial_error() if channel == -1 else registration_metric_set.at(i).max_residual_radial_error(channel)
        focus = numpy.asarray(extraction_metric_set.at(i).focus_scores()).max()  if channel == -1 else extraction_metric_set.at(i).focus_score(channel)
        if numpy.isnan(err): continue
        if err > 1: err = 1.1
        data[extraction_metric_set.at(i).cycle_hash()] = (err, focus)
    return numpy.asarray(data.values())

def create_plot_q30(registration_metric_set, q_metric_set, channel):
    ''' Generate the x and y for the plot

    TODO: add some type of filtering

    :param distortion_metric_set:
    :return: numpy array of curve for each model
    '''

    if registration_metric_set.empty():
        raise RuntimeError("No registration metrics")

    if q_metric_set.empty():
        raise RuntimeError("No Q metrics")
    data = {}
    q30_index = q_metric_set.index_for_q_value(30)
    for i in xrange(q_metric_set.size()):
        err = registration_metric_set.at(i).max_residual_radial_error() if channel == -1 else registration_metric_set.at(i).max_residual_radial_error(channel)
        if numpy.isnan(err): continue
        if err > 1: err = 1.1
        data[q_metric_set.at(i).cycle_hash()] = (err, q_metric_set.at(i).percent_over_qscore(q30_index))
    return numpy.asarray(data.values())

def create_plot(registration_metric_set, error_metric_set, channel):
    ''' Generate the x and y for the plot

    TODO: add some type of filtering

    :param distortion_metric_set:
    :return: numpy array of curve for each model
    '''

    if registration_metric_set.empty():
        raise RuntimeError("No registration metrics")

    if error_metric_set.empty():
        raise RuntimeError("No Error metrics")
    data = {}
    for i in xrange(error_metric_set.size()):
        residual = registration_metric_set.at(i).max_residual_radial_error() if channel == -1 else registration_metric_set.at(i).max_residual_radial_error(channel)
        seqerror = error_metric_set.at(i).error_rate()
        if residual > 1: residual = 1.1
        if numpy.isnan(residual) or numpy.isnan(seqerror): continue
        data[error_metric_set.at(i).cycle_hash()] = (residual, seqerror)
    return numpy.asarray(data.values())


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

def process_files(run_folders, channel, **extra):
    ''' Read the InterOp data and plot the distortion curves for each input run folder

    :param run_folders: list of run folders to process
    :param output: output image name (optional)
    :param extra: unused arguments
    '''

    run_metrics = py_interop_metrics.run_metrics()
    valid_to_load = py_interop_run.uchar_vector(py_interop_run.MetricCount, 0)
    valid_to_load[py_interop_run.Registration]=1
    valid_to_load[py_interop_run.Q]=1
    valid_to_load[py_interop_run.Error]=1
    valid_to_load[py_interop_run.Extraction]=1
    channels=None
    for run_folder in run_folders:
        _logger.info("Parsing coefficients for %s"%run_folder)
        basename = os.path.basename(run_folder)
        try:
            run_metrics.read(run_folder, valid_to_load)
        except Exception, ex:
            _logger.warn("Skipping - cannot read RunInfo.xml: %s - %s"%(basename, str(ex)))
            continue
        if channels is None:
            channels = [name.lower() for name in run_metrics.run_info().channels()]
            try:
                selected_channel_index = channels.index(channel.lower())
            except:
                selected_channel_index=-1
        if basename == "": basename=os.path.basename(os.path.dirname(run_folder))
        try:
            data = create_plot_q30(run_metrics.registration_metric_set(), run_metrics.q_metric_set(), selected_channel_index)
            for fig in create_figure(basename+"_q30", **extra):
                pylab.title(basename)
                pylab.xlabel("Registration Error")
                pylab.ylabel("Q30")
                pylab.plot(data[:, 0], data[:, 1], marker='.', ls='None')
        except Exception, ex:
            _logger.error("Failed to read metric for %s - %s"%(basename, str(ex)))
        try:
            data_error = create_plot(run_metrics.registration_metric_set(), run_metrics.error_metric_set(), selected_channel_index)
            for fig in create_figure(basename+"_error", **extra):
                pylab.title(basename)
                pylab.xlabel("Registration Error")
                pylab.ylabel("PhiX Error")
                pylab.plot(data_error[:, 0], data_error[:, 1], marker='.', ls='None')
        except Exception, ex:
            _logger.error("Failed to read metric for %s - %s"%(basename, str(ex)))
        try:
            data_cycle = create_plot_cycle(run_metrics.registration_metric_set(), selected_channel_index)
            for fig in create_figure(basename+"_cycle", **extra):
                pylab.title(basename)
                pylab.xlabel("Cycle")
                pylab.ylabel("Registration Error")
                pylab.plot(data_cycle[:, 0], data_cycle[:, 1], marker='.', ls='None')
        except Exception, ex:
            _logger.error("Failed to read metric for %s - %s"%(basename, str(ex)))
            
        try:
            data_fwhm = create_plot_focus(run_metrics.registration_metric_set(), run_metrics.extraction_metric_set(), selected_channel_index)
            for fig in create_figure(basename+"_fwhm", **extra):
                pylab.title(basename)
                pylab.xlabel("Registration Error")
                pylab.ylabel("FWHM")
                pylab.plot(data_fwhm[:, 0], data_fwhm[:, 1], marker='.', ls='None')
            for fig in create_figure(basename+"_hist", **extra):
                pylab.title(basename)
                pylab.xlabel("Registration Error")
                pylab.ylabel("Number of tile/cycles")
                pylab.hist(data_fwhm[:, 0])
        except Exception, ex:
            _logger.error("Failed to read metric for %s - %s"%(basename, str(ex)))
        if extra['output'] == "": pylab.show()

def main():
    ''' Parse arguments from the command line
    '''

    matplotlib.rcParams['agg.path.chunksize'] = 10000

    logging.basicConfig(level=logging.INFO)
    distortionTypes = py_interop_run.string_vector()
    py_interop_run.list_distortion_curve_type(distortionTypes)

    parser = argparse.ArgumentParser(description="This script reads in a list of run folders and generates a plot of the distortion curves", add_help=True)
    parser.add_argument("run_folders", help="Input run folders", nargs="+")
    parser.add_argument("-o", "--output", help="Output image filename (if not specified, then a window is opened)", default="")
    parser.add_argument("-c", "--channel", help="Selected a specific channel, All means all", default="All")
    parser.add_argument("--dpi", help="Resolution of the output image", type=int, default=300)
    arguments = parser.parse_args()
    process_files(**vars(arguments))

if __name__ == '__main__':
    main()

