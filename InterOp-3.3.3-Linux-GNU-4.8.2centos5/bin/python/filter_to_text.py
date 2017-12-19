import numpy
import sys
import os
import glob

#TODO: create scripts to generate extended_tile and pfgrid_metrics

def main():

    files = sys.argv[1:]
    new_files=[]
    for filename in files:
        more_files = glob.glob(filename)
        if len(more_files) > 1:
            new_files.extend(more_files)
        else:
            new_files.append(filename)
    files = new_files
    filter_type = 'filter' #'empty'
    for run_folder in files:
        locs_filename = os.path.join(run_folder, "Data", "Intensities", "s.locs")
        with open(locs_filename, 'rb') as fin:
            header1 = numpy.fromfile(fin, dtype=numpy.uint32, count=1)
            header2 = numpy.fromfile(fin, dtype=numpy.float32, count=1)
            cluster_count = numpy.fromfile(fin, dtype=numpy.uint32, count=1)[0]
            locs = numpy.fromfile(fin, dtype=numpy.float32)
            locs = locs.reshape((cluster_count, 2))
        if header1 != 1: raise ValueError("Invalid locs file 1 : %d"%header1)
        if header2 != 1.0: raise ValueError("Invalid locs file 2 : %d"%header2)
        numpy.savetxt(os.path.join(".", "s_locs.csv"), locs, fmt="%.6f", delimiter=',')


        filter_files = glob.glob(os.path.join(run_folder, "Data", "Intensities", "BaseCalls", "L*", "s_*_*.%s"%filter_type))
        for filter_file in filter_files:
            with open(filter_file, 'rb') as fin:
                header = numpy.fromfile(fin, dtype=numpy.uint32, count=3)
                empty = numpy.fromfile(fin, dtype=numpy.uint8)
            if header[0] != 0: raise ValueError("Invalid filter file 1 : %d"%header[0])
            if header[1] != 3: raise ValueError("Invalid filter file 2 : %d"%header[0])
            stem = os.path.splitext(os.path.basename(filter_file))[0]
            numpy.savetxt(os.path.join(".", stem+"_%s.csv"%filter_type), empty, fmt="%d", delimiter=',')

if __name__ == '__main__': main()
