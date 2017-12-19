# Changes                                               {#changes}

## v3.3.4-iuo (Master)

## v3.3.3-iuo

Date       | Description
---------- | -----------
2017-05-26 | IPA-6541: Ensure index metric order matches file

## v3.3.2-iuo

Date       | Description
---------- | -----------
2017-05-12 | IPA-6065: Rev basecalling metrics to include determinant

## v3.3.1-iuo

Date       | Description
---------- | -----------
2017-05-11 | IPA-6419: Filter metric list by empty metric values
2017-05-08 | Refactor by-lane plot to use reflection-like enums
2017-05-02 | IPA-6440: Add percent PF to run summary
2017-05-02 | Refactor flowcell chart to use reflection-like enums
2017-04-29 | IPA-6413: Add C# exception unit tests
2017-04-28 | Refactor by-cycle to use reflection-like enums


## v3.2.9-iuo

Date       | Description
---------- | -----------
2017-04-26 | Fix list filename bug
2017-04-26 | Fix for non-rebaseline regression tests
2017-04-24 | Handle the new exception in the regression test


## v3.2.8-iuo

Date       | Description
---------- | -----------
2017-04-19 | Fix bug in color for IUO plots

## v3.2.7-iuo

Date       | Description
---------- | -----------
2017-04-19 | Add list InterOp filenames for all metrics
2017-04-19 | Expand number of colors for IUO plots

## v3.2.6-iuo

Date       | Description
---------- | -----------
2017-04-18 | IPA-6303: Log Aggregator Write Time to Event Metrics
2017-04-18 | IPA-6403: Ensure empty metrics return empty plots
2017-04-17 | Fix SWIG binding and add package test
2017-04-17 | IPA-6353: handle legacy HiSeq RunInfo rewrite
2017-04-14 | IPA-6395: Remove centroid area
2017-04-13 | Fix missing dependencies in Python
2017-04-12 | Support more portable Python build for Linux
2017-04-06 | IPA-5052: all lanes on the indexing tab
2017-04-06 | Fix legacy binning in QByLaneMetrics
2017-04-05 | Support Python 3.6 build of InterOp

## v3.2.5-iuo

Date       | Description
---------- | -----------
2017-03-24 | Fixed clearing bug in registration metrics and added unit test
2017-03-24 | Attempt to allow multi-platform Nuget packages
2017-03-22 | Add example using a Python Notebook

## v3.2.4-iuo

Date       | Description
---------- | -----------
2017-03-15 | IPA-6285: IPA-6285: Support CSV writing of summary
2017-03-15 | IPA-6274: Add imaging metrics to analysis panel

## v3.2.3-iuo

Date       | Description
---------- | -----------
2017-03-14 | IPA-6064: Add confusion matrix setter
2017-03-13 | Clarify documentation on usable cycles
2017-03-03 | IPA-6221: Add fiducial locations to header of registration metrics
2017-03-02 | IPA-6235: Add is_pair_end to run_info
2017-03-02 | IPA-6233: Release new non-polymorphic template function interface 
2017-03-01 | IPA-6220: Add upper left fiduical offset to extended tile metrics
2017-03-01 | IPA-6219: Add covariances to model and format

## v3.2.2-iuo

Date       | Description
---------- | -----------
2017-02-28 | Improve build cleanup to reduce disk space
2017-02-25 | Fixed the regression tests
2017-02-24 | IPA-6189: Fixed compute_buffer_size to handle mutli record format tile
2017-02-24 | IPA-6186: Clean up IUO documentation for applications
2017-02-23 | IPA-6188: Remove instrument type from load analysis metrics

## v3.2.1-iuo

Date       | Description
---------- | -----------
2017-02-20 | IPA-6178: Fix another bug in flowcell loading from collapsed-q
2017-02-20 | IPA-6057: Replace polymorphic read functions with internal switch
2017-02-18 | IPA-6167: Fix bug in by cycle and flowcell plots for BaseSpace Collapsed Q Metrics
2017-02-17 | IPA-6166: Update example to include compass
2017-02-16 | IPA-6165: Add Python development example
2017-02-16 | IPA-6050: Add parse enum to SWIG binding
2017-02-16 | IPA-6059: Document regression set runs
2017-02-16 | IPA-6027: Support RunInfo writing
2017-02-08 | Platform specific interop loading for phasing metrics
2017-02-07 | IPA-6123: Fix bug in heatmap with q-by-lane
2017-02-06 | IPA-6108: Add try/catch inside openmp loop

## v3.2.0-iuo

Date       | Description
---------- | -----------
2017-02-01 | IPA-6066: Threaded performance test for reading
2017-01-30 | Fix Python install to ensure consistent library

## v3.1.6-iuo

Date       | Description
---------- | -----------
2017-01-26 | Fix Python build for Visual Studio
2017-01-24 | Package the Python InterOp library for artifactory
2017-01-24 | IPA-6036: Explicit exception for writing binned q-metric as unbinned
2017-01-24 | IPA-6026: Fix visual studio compile options for C#
2017-01-23 | IPA-6036: Fix collapsed q-metrics for BaseSpace
2017-01-19 | IPA-6019: Fix bugs in dumpbin and dumptext
2017-01-19 | Ipa 5731 add pip support
2017-01-18 | IPA-5967: Make registration error calculations handle >8 fiducials

## v3.1.5-iuo

Date       | Description
---------- | -----------
2017-01-17 | IPA-6005: Fix clearing issue in SAV
2017-01-17 | IPA-5981: Populate called intensity from centroids
2017-01-16 | IPA-5984: Add compass cycle logic to SWIG
2017-01-13 | IPA-5978: Add ability to plot occupancy
2017-01-13 | Fixes for compass metrics
2017-01-11 | IPA-5970: fix phasing slope comparison in the summary test

## v3.1.4-iuo

Date       | Description
---------- | -----------
2017-01-11 | Expose compass summary in SWIG
2017-01-11 | Update instrument name and fix registration issue


## v3.1.3-iuo

Date       | Description
---------- | -----------
2017-01-10 | Fixed pull request test
2017-01-09 | IPA-4455: run diagnostics plot logic
2017-01-09 | Update summary testing to cover IUO metrics


## v3.1.2-iuo

Date       | Description
---------- | -----------
2017-01-05 | IPA-5940: Add IUO metrics to analysis plots
2017-01-05 | Populate skew metrics and setup plot by cycle
2017-01-03 | Fixes to documentation and text writing
2017-01-03 | IPA-5909: Apex RunParameters parsing
2016-12-22 | IPA-5925: run diagnostics table logic
2016-12-22 | IPA-5873: Fixed Python SWIG warnings
2016-12-22 | Fix minimum fiducial count for registration error
2016-12-22 | Replace interop2csv with versioned dumptext
2016-12-20 | IPA-5871: Eliminate Swig warnings in C#
2016-12-20 | IPA-5923: Fix bug in legacy q-metric binning
2016-12-19 | Removes the coverity run from the build matrix for every pull request
2016-12-16 | IPA-5885: Ensure error summary matches requirements
2016-12-14 | Enhance C# version information (IUO)
2016-12-14 | Clean up enums IUO

## v3.1.1-iuo

Date       | Description
---------- | -----------
2016-12-12 | Fix SWIG/Java Memory leak, upcast unsigned int64 on Linux
2016-12-12 | Ensure Summary tab calculations are consistent with Docs
2016-12-09 | IPA-5883: Fix possible memory issue in MSVC12
2016-12-08 | Don't clear InterOps if we're switching tabs
2016-12-07 | IPA-4647: Add support for the absolute naming convention
2016-12-07 | IPA-5869: Add section filtering for sub tile plots
2016-12-06 | IPA-5734: Refactor IUO for synchronization with master
2016-12-05 | Fix for writing bugs, regression test problems, nuget packaging, packaging scripts
2016-12-02 | IPA-5798: Calculate error in registration
2016-12-01 | IPA-5796: Add unit/regression test for event metric plot
2016-11-30 | IPA-5795: Regression/unit test event metric table
2016-11-30 | IPA-5835: Unique NuGet Build for Linux
2016-11-29 | Fixes a bug in the regression test DistortionByTile plot
2016-11-28 | Fix for by cycle failure when IndexMetricsOut.bin is present
2016-11-28 | IPA-5773: Add unit tests for imaging table reading/writing
2016-11-28 | IPA-5831: Package SWIG generated sources
2016-11-28 | IPA-5830: Fix tile naming bug for on demand datasets
2016-11-28 | IPA-5809: Move run metric set wrapping to SWIG

## v3.1.0-iuo

Date       | Description
---------- | -----------
2016-11-23 | Fix native DLL copy in NuGet package
2016-11-22 | Event Metrics SWIG changes

## v3.0.36-iuo

Date       | Description
---------- | -----------
2016-11-21 | IPA-5807: Add method to list all possible InterOp filenames
2016-11-21 | IPA-4460: Event Metrics plot logic
2016-11-21 | IPA-5240: Clean up compass metrics
2016-11-17 | Speed-up InterOp with new map
2016-11-17 | Fix for the indexing regression test
2016-11-16 | IPA-4460: event metrics table logic
2016-11-15 | Load native libraries from JNI wrapper classes
2016-11-14 | IPA-5184: Add indexing summary regression test
2016-11-14 | Fix compile issue under OSX clang
2016-11-14 | IPA-5692: Add version to DLL
2016-11-14 | IPA-5239: Add unit tests for compass metrics
2016-11-14 | Fix heat map regression test
2016-11-11 | IPA-5735: Improve Java binding unit testing

## v3.0.35-iuo

Date       | Description
---------- | -----------
2016-11-11 | Updated version history
2016-11-11 | Ensure large heat map tests do not log too many errors
2016-11-10 | Reverted change to header size function
2016-11-11 | Force Google Test to exit if an error occurs during rebase
2016-11-10 | Fix V2 event metrics model, and tests
2016-11-10 | Reverted change to header size function

## v3.0.34-iuo

Date       | Description
---------- | -----------
2016-11-09 | Fixed bug in header size calculation
2016-11-09 | Added EventTypeCount to event type enums
2016-11-09 | IPA-5733: Audit clearing logic in the model
2016-11-07 | IPA-5183: Add plotting regression tests (IUO)
2016-11-07 | IPA-5709: Add plots for q-score histogram, heatmap and flowcell
2016-11-07 | IPA-5194: Create NuGet Package for C++ InterOp
2016-11-03 | Avoid linking JNI library with libawt
2016-11-02 | Ensure corrected intensity does not print 0


## v3.0.33-iuo

Date       | Description
---------- | -----------
2016-11-02 | Fix by cycle reader and unit test
2016-11-02 | IPA-5662: Report summary % occupied for sage


## v3.0.32-iuo (Broken for ByCycle InterOps)

Date       | Description
---------- | -----------
2016-11-01 | IPA-5710: Speed up by cycle interop reading
2016-10-31 | IPA-5182: Add plotting regression tests
2016-10-28 | IPA-5678: make subtile density consistent between platforms
2016-10-27 | IPA-5679: always load phasing metrics with tile metrics
2016-10-27 | IPA-5680: fix affine transform precision
2016-10-26 | IPA-5686: making subtile density consistent with tile-level density
2016-10-26 | Bug fixes to phasing (100x multiplier and 25 cycle regression calculation)
2016-10-26 | IPA-5690: Refactor RTA filenames


## v3.0.31-iuo

Date       | Description
---------- | -----------
2016-10-25 | Fix the regression test framework
2016-10-25 | Check all sub-bins for nonzero entries with subtile zoom
2016-10-24 | Fix Python Exceptions
2016-10-24 | Add cycles to metric set to support FWHM filter options
2016-10-24 | IPA-5654: Add distortion curve plotting


## v3.0.30-iuo

Date       | Description
---------- | -----------
2016-10-21 | Bug fixes for the summary regression test to support surface[m
2016-10-20 | Bug in NaN support


## v3.0.29-iuo

Date       | Description
---------- | -----------
2016-10-20 | Fixes for documentation and metrics
2016-10-19 | Remove time from imaging table
2016-10-19 | Bug fix for summary metrics
2016-10-19 | IPA-5639: Windows regression test powershell script
2016-10-19 | IPA-5547: Support 25-cycle phasing for ApeX
2016-10-18 | Fix single-surface summary calculations

## v3.0.28-iuo

Date       | Description
---------- | -----------
2016-10-18 | IPA-5595: Fixed bug in summary logic exposed by short read, tile v3
2016-10-17 | Fixed bug in reading binary interop files and populating imaging
2016-10-17 | IPA-5566: Rev all InterOp formats

## v3.0.27-iuo

Date       | Description
---------- | -----------
2016-10-07 | Fix the distortion curve enum


## v3.0.26-iuo

Date       | Description
---------- | -----------
2016-10-07 | IPA-5253: Add tile count to surface for summary
2016-10-07 | Fixes a bug in the distortion plot
2016-10-04 | Fixed some warnings found in 32-bit build
2016-10-03 | IPA-5211: Create python script to plot distortion curves

## v3.0.25-iuo

Date       | Description
---------- | -----------
2016-09-30 | Fix surface summary bug

## v3.0.24-iuo

Date       | Description
---------- | -----------
2016-09-29 | IPA-5213: Create per surface summary model/logic/app

## v3.0.23-iuo

Date       | Description
---------- | -----------
2016-09-26 | IPA-5210: Create CSV parsable summary output
2016-09-26 | IPA-5194: Create nuspec package file
2016-09-22 | Refactor unit tests to improve regression testing

## v3.0.22-iuo

Date       | Description
---------- | -----------
2016-09-16 | Fix index metric-based tests
2016-09-16 | IPA-5155: Fix by cycle bug in SAV/InterOp on demand loading
2016-09-16 | Ipa 5140 - plot logic tests assorted
2016-09-16 | IPA-5158: Fix read bug when vector is empty

## v3.0.21-iuo

Date       | Description
---------- | -----------
2016-09-15 | Fix reading in by cycle InterOps
2016-09-14 | IPA-5135: Add a setter method to occupied
2016-09-14 | Fixed error at cycle mean
2016-09-14 | IPA-5070: Add optional flag to skip median for summary
2016-09-14 | Add fallback version information for zip archives
2016-09-13 | Ensure code is ANSI C++ Compatible

## v3.0.20-iuo

Date       | Description
---------- | -----------
2016-09-12 | Fixed bug in q-score heatmap and q-score clearing
2016-09-12 | Added summary regression test, fixed regression test framework, fixed runParameters reading
2016-09-09 | Added sentinel for missing values in the heatmap type plots
2016-09-12 | Compass bug fix
2016-09-12 | Initialize missing plot data values to NaN
2016-09-09 | Ipa 5102 - improve unit tests plot logic(channel_test.h, plot_logic.h, and enum_parsing,h)
2016-09-09 | Fix SAV crash with double free
2016-09-08 | IPA-5068: Add missing value sentinel
2016-09-08 | Fixes problems found by coverity
2016-09-08 | IPA-5101: Fix MSVC bug in vector type loading 
2016-09-07 | IPA-4285: color matrix metrics
2016-09-06 | IPA-5098: Improved speed of InterOp loading
2016-09-02 | Ipa 5051 compass called intensity change - accommodating Compass re quest to use P90 Intensity instead of Called Intensity. 
2016-09-02 | Compass non-cycle metrics
2016-09-01 | Bug fix for SWIG in on-demand loading

## v3.0.19-iuo

Date       | Description
---------- | -----------
2016-09-01 | Fixeds for bugs found by coverity
2016-09-01 | Fixed a bug in QMetrics V6 Unbinned, added unit test and C# example
2016-09-01 | IPA-5069: Support on demand loading for SAV (IUO)
2016-09-01 | Bug fix clearing the summary stat prior to setting it
2016-08-30 | Various minor fixes to get public working with Clang3.4 and MSVC12
2016-08-30 | Bug fix to RunInfo section validation
2016-08-29 | Bug fixes to IUO imaging and summary calculations
2016-08-26 | Fix missing exception specification
2016-08-26 | IPA-5028: Add RunInfo and InterOp validation (IUO)
2016-08-25 | IPA-5028: Add subtile combobox filling logic
2016-08-25 | IPA-4461: IUO imaging logic

## v3.0.18-iuo

Date       | Description
---------- | -----------
2016-08-16 | IPA-5028: Improve API for combo box filling
2016-08-16 | IPA-4462: Add IUO summary logic
2016-08-19 | More robust way to disable tests
2016-08-19 | IPA 4894- Compass Cycle Summary
2016-08-19 | This bug causes RTA to fail to properly build InterOp

## v3.0.17-iuo

Date       | Description
---------- | -----------
2016-08-19 | Fixes the initial sorting in the imaging table

## v3.0.16-iuo

Date       | Description
---------- | -----------
2016-08-04 | IPA-4465: subtile aggregate plot logic + app
2016-08-04 | Merge from master
2016-08-03 | Add subtile id function
2016-08-02 | Clean buffers
2016-07-22 | IPA-4679: fix camel cases in IUO branch
2016-07-22 | IPA-4453: adding in subtile grid logic
2016-07-13 | Fixed a couple of VS warnings
2016-07-08 | IPA-4287 static run metrics
2016-07-01 | IPA-4288 event metrics


## v1.0.13

Date       | Description
---------- | -----------
2016-11-30 | Removed Win32 build testing - this is not supported
2016-11-28 | IPA-5830: Fix tile naming bug for on demand datasets
2016-10-19 | Remove time from imaging table
2016-09-27 | IPA-5213: Create per surface summary model/logic/app


## v1.0.12

Date       | Description
---------- | -----------
2016-09-26 | IPA-5210: Create CSV parsable summary output
2016-09-23 | IPA-5194: Create nuspec package file
2016-09-17 | Refactor individual metric unit tests
2016-09-17 | Refactor metric stream tests
2016-09-14 | Reorganized code into own stat util file
2016-09-14 | Fixes error rate at a specific cycle when tiles are at different cycles
2016-09-14 | Add version information for zip archives
2016-09-14 | IPA-5070: Add optional flag to skip median for summary
2016-09-13 | Ensure ANSI build is being tested


## v1.0.11

Date       | Description
---------- | -----------
2016-09-12 | Fixed bug in q-score heatmap and q-score clearing
2016-09-12 | Added summary regression test, fixed regression test framework, fixed runParameters reading
2016-09-09 | Added sentinel for missing values in the heatmap type plots
2016-09-09 | Fixed invalid pointer deference and double free in MSVC
2016-09-08 | Added sentinel for missing values in the imaging table
2016-09-08 | Fixed potential problem found by coverity
2016-09-07 | IPA-5101: Fix MSVC bug in vector type loading (Master)
2016-09-02 | Added buffered reader to improve loading speed
2016-09-01 | Bug fix for SWIG in on-demand loading

## v1.0.10

Date       | Description
---------- | -----------
2016-09-01 | Bug fix clearing the summary stat prior to setting it
2016-09-01 | Fixed a bug in QMetrics V6 Unbinned, added unit test and C# example
2016-08-31 | IPA-5069: Flush out on demand loading further for each tab
2016-08-30 | Various minor fixes to get public working with Clang3.4 and MSVC12
2016-08-30 | Bug fix to RunInfo section validation
2016-08-30 | IPA-5069: Support on demand loading for SAV (Part 1)
2016-08-26 | IPA-5028: Add RunInfo and InterOp validation

## v1.0.9

Date       | Description
---------- | -----------
2016-08-26 | Refactor CSharp code into additional library
2016-08-26 | IPA-5028: Add RunInfo and InterOp validation
2016-08-19 | Fix sorting in imaging table
2016-08-18 | Cleanup code
2016-08-17 | Fix the read ID
2016-08-16 | IPA-5009: Add sorting to imaging table
2016-08-16 | IPA-5007: Fix combo boxes on analysis tab
2016-08-16 | Fix msvc warning and some script differences
2016-08-15 | Add clear function to run metrics
2016-08-15 | IPA-4799: Create Internal Coverity Build
2016-08-11 | Refactor unit tests to make more flexible for regression testing
2016-08-08 | IPA-4922: Move logic code from header to cpp
2016-08-05 | IPA-4827: Make run info parsing more robust
2016-08-03 | Refactor code and add test build script
2016-08-02 | Add big object support for unit tests
2016-08-02 | Clean buffers in the heatmap and flowcell
2016-08-02 | Update travis-ci to GCC-5
2016-07-28 | Added float array backing to heat map
2016-07-25 | IPA-4752: Replace InterOp 1.x Code with InterOp 2.x Code - Imaging Tab
2016-07-22 | Fix camel case
2016-07-22 | IPA-4751: Integrated InterOp2.x with Analysis Tab
2016-07-22 | Github Issue 74: Compiler warning as error unsigned/signed comp
2016-07-21 | Bug fixes for flowcell chart and more recent versions of GCC
2016-07-17 | Added coverity online scan and fixed some issues found

## v1.0.8

Commit  | Description
------- | -----------
b74024d | Added support for paths with spaces in the build system
d76117a | Remove support for 32-bit builds
27c1942 | IPA-4778: Fixed issues found by coverity
ad8cac0 | Updated the documentation

## v1.0.7

Commit  | Description
------- | -----------
2d8480c | Fixed C# binding and filter_option validation
32daedd | Added package target to CMake build script
36ca197 | Add command line parser and update plotting apps
6cc52c2 | Continue refactoring SWIG C# binding and fix exceptions
5e01ff3 | Update tolerances to properly handle floating-point differences due to rounding
5e85cf0 | IPA-4608: Ensure cumulative q-metrics does not overflow
c60caa9 | IPA-4598: Regression test for imaging table
616e6e8 | IPA-4695: Setup framework to reuse unit test code for regression testing
839191c | Quick floor -> round bug fix for indexing plot y-max value
8fa8cfe | Test for larger CollapsedQ size
cbe3540 | IPA-4505: Fixed writing to buffer
76521e3 | IPA-4505: Fix summary tab, index tab and bs q-metrics
03867f0 | IPA-4598: Added imaging metrics and precision of numbers reported
8f5cf70 | IPA-4505: Fix empty PlotQC
fd5e265 | IPA-4505: Replace median, fixed missing percent aligned and fixed collapsed q-metrics
e2d1c80 | IPA-4505: Tile convention checking
e841107 | IPA-4598: Bind imaging logic to C# and test
37e6e21 | IPA-4505: Fix channel order in by cycle
23f1dca | IPA-4505: Fixed by cycle and q-bin index
987d02c | IPA-4595: Add index out of bounds checking to metrics
18e0ef7 | IPA-4505: Fix q-score median
d815021 | IPA-4595: Map plot metric types to input types
01f08c6 | IPA-4497: Fix camel case in metric_format
9cce9b9 | IPA-4486: Refactor code to use INTEROP_TUPLEX
37899c9 | IPA-4493: Replace q-metrics with collapsed q-metrics in logic
cb999ae | IPA-4485: Simplify mapping between constant types
333909f | IPA-4419: Add collapsed q-score logic
68d1b6a | IPA-4286: Add collapsed qscore metrics
2c82c4a | IPA-4292: Add imaging model and logic
c5aad38 | IPA-4292: Refactor to prepare code for imaging model and logic
d9e5a83 | IPA-4290: Add index summary logic
050a9ee | IPA-4447: Add index summary model
fc5d190 | IPA-4408: Plot sample QC for indexing tab
f05a2a3 | IPA-4406: Plot Logic - flowcell map
4eb6568 | IPA-4407: Plot Logic - plot q-score histogram
9706b24 | IPA-4404: Add plot logic - plot by lane
56bb897 | IPA-4384: Prototype PlotDataByCycle to build initial framework
9c8e8d8 | IPA-4384: Model for plot by cycle prototype (Part 1)
6c1fbc5 | IPA-4382: Refactor code to make naming more consistent
9a45340 | IPA-4383: Add filter options to support plot logic
b11e736 | IPA-4382: Create reflection-like interface for enums to support plot logic
d9deeea | IPA-4246: Add search for non Out interop files
3f2f2bf | Reorganize modules in doxygen
202d6ef | IPA-4146: Add summary logic and application
6c5a30d | IPA-4146: Added metric and channel logic and more statistics
735cda2 | IPA-4146: Refactor of the metric set
         
## v1.0.6

Commit  | Description
------- | -----------
57be79c | Update all cycle states and bug fix for legacy q-metrics
0b4304a | Refactor to remove and mark deprecated code
647cc9e | Add utility for creating unit tests
9d82333 | Add search for non Out interop files

## v1.0.5

Commit  | Description
------- | -----------
7380f29 | Bug fixes for q-metrics and compilation error on Mac OSX

## v1.0.4

Commit  | Description
------- | -----------
50e8e2a | Update documentation
50e8e2a | Update documentation
0b22102 | Added summary tests
13f1fb4 | Added summary logic
339a914 | Added summary model
aca0152 | Added run metrics
6516098 | Added metric and channel logic as well as more statistics functions
221028a | Added parsers for RunInfo.xml and RunParameters.xml
5a7ca8f | Remove legacy error metric fields

## v1.0.3

Commit  | Description
------- | -----------
5bf14ca | Fix for reading multiple reads with tile metrics
2cef41a | Fixing tile metric phasing/prephasing scale to match SAV
a11a3e1 | Fixed tile_number_for_lane
29905ea | Fixed clear for all metric sets
9af35c4 | Added simple statistical functions: mean and variance
2f04b3f | Added C# performance test
d8b79b0 | Added example program for simulating InterOps at a specific cycle

## v1.0.2

Commit  | Description
------- | -----------
27a7eab | Fixed unclear error message when InterOp is empty
7f93166 | Improvements to the documentation website theme
ade1187 | Ensure CMake configure script throws error of system does not support 32-bit float
096c817 | Made CMake configure script more robust to missing dependencies
498efc3 | Ensure proper cast to record_size_t
286c66c | Added header size calculation
06f567d | Added record size calculation
d35f6bf | Added new filename function without assuming directory
fc94e9f | Added links to Issues on webpage
08f579c | Updated documentation and build script building and deployment

## v1.0.1

Commit  | Description
------- | -----------
450b7e6 | Bundle RapidXML and update deployment scripts
b9cc4b0 | Add change log
f74a702 | Deploy binaries for Windows/Linux/OSX and major compilers
    -   | Ensure only Mono .Net 4.x compiler is used
  -     | Ensure only SWIG 3.x or later is used
3958559 | Setup Appveyor build script
f063b81 | Setup TravisCI build script
586f9d1 | Build C# examples by default
553856c | Updated documentation
03522ff | Fixed build issues
78881f4 | Disable C# examples when swig is disabled
b70f775 | Clean up documentation
216ea62 | Ensure C# compiler matches C++ 32/64-bit
6871246 | Switch to bootstrap theme for documentation

