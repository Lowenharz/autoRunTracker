
## Test Status

| [Regression][tcreghome]       | [Coverity][tccovhome]     | [MSVC][tcmsvchome]      | [CentOs 7][tccentos7home]     |
| --- | --- | --- | --- |
| **[CentOs 5][tccentos5home]** | **[MinGW][tcmingwhome]**  | **[RTA3][tcrta3home]**  | **[SAV][tcsavhome]**          |

## Quick Start

The Illumina InterOp libraries are a set of common routines used for reading InterOp metric files produced by
Illumina sequencers including **NovaSeq**. These libraries are backwards compatible and capable of supporting prior releases of the software,
with one exception: GA systems have been excluded.

***
>  We now support an interface to Python 2.7 (UCS-4), 3.5 and 3.6 (see contents below)
***

The InterOp files supported by this library include:

  - CorrectedIntMetricsOut.bin
  - ErrorMetricsOut.bin
  - ExtractionMetricsOut.bin
  - ImageMetricsOut.bin
  - QMetricsOut.bin
  - TileMetricsOut.bin
  - IndexMetricsOut.bin
  - QMetrics2030Out.bin
  - QMetricsByLaneOut.bin
  - EmpiricalPhasingMetricsOut.bin

The `Illumina Use Only` InterOp files supported by this library include:

  - AlignmentMetricsOut.bin
  - BasecallingMetricsOut.bin
  - ColorMatrixMetricsOut.bin
  - EventMetricsOut.bin
  - ExtendedTileMetricsOut.bin
  - FWHMGridMetricsOut.bin
  - OpticalModelOut.bin
  - PFGridMetricsOut.bin
  - QGridMetricsOut.bin
  - RegistrationMetricsOut.bin
  - StaticRunMetricsOut.bin

This library is written in C++98 and provides bindings for C# using the SWIG interface. This
support includes examples and unit tests for both languages.


### Documentation

| Content                       | Description                                                                          |
| ----------------------------- | -------------------------------------------------------------------------------------|
| [Main][MainPage]              | Index page for the documentation                                                     |
| [Install][InstallPage]        | Describes how to install Illumina InterOp from binaries and the source code          |
| [Applications][AppsPage]      | Describes applications that transform binary InterOp data into text                  |
| [Examples][ExamplesPage]      | How to examples showing how to use the Illumina InterOp C++ API                      |
| [Modules][ModulesPage]        | Short descriptions of the most useful code in the Illumina InterOp API               |
| [Changes][ChangesPage]        | Changes between releases of the source code                                          |
| [Issues]                      | Have a question? Need a feature? Found a bug? Interact with the developers here.     |
| [Performance][PerfPage]       | Computation performance of the code                                                  |
| [Formats][BinaryFormats]      | Description of the binary formats for each InterOp file                              |
| [Python][PythonBinding]       | Step by step tutorial using the Python binding                                       |

[MainPage]: https://git.illumina.com/pages/Bioinformatics/interop/index.html
[InstallPage]: https://git.illumina.com/pages/Bioinformatics/interop/install.html
[AppsPage]: https://git.illumina.com/pages/Bioinformatics/interop/apps.html
[ExamplesPage]: https://git.illumina.com/pages/Bioinformatics/interop/examples.html
[ModulesPage]: https://git.illumina.com/pages/Bioinformatics/interop/modules.html
[ChangesPage]: https://git.illumina.com/pages/Bioinformatics/interop/changes.html
[Issues]: https://github.com/Illumina/interop/issues
[PerfPage]: https://git.illumina.com/pages/Bioinformatics/interop/perf.html
[BinaryFormats]: https://git.illumina.com/pages/Bioinformatics/interop/binary_formats.html
[PythonBinding]: https://git.illumina.com/pages/Bioinformatics/interop/python_binding.html

### Install

#### Python

Supported versions for binary distribution: 2.7 (UCS-4) and 3.6.

You should have NumPy already installed.

If you are new to Python or unsure what UCS-4 means, then please use
Anaconda or Miniconda.

~~~~~~~~~~~~~{.sh}
$ pip install -f https://ussd.artifactory.illumina.com/list/generic-bioinformatics/interop/pypi/ interop
~~~~~~~~~~~~~

#### From Source

~~~~~~~~~~~~~{.sh}
$ git clone https://git.illumina.com/Bioinformatics/interop
$ mkdir build
$ cd build
$ cmake ../interop
$ cmake --build .
~~~~~~~~~~~~~

#### Building with InterOp

GCC/Clang:

~~~~~~~~~~~~~{.sh}
g++ example1.cpp -l interop_lib -L <install_dir>/lib64 -I <install_dir>/include
~~~~~~~~~~~~~

For CLang, just substitute g++ with clang++. 


### Known Limitations

There are several known limitations to the current library:

  1. You cannot build a shared library on Windows. Our CMake build script disallows it for good reason, it currently
     does not work. You can still use a static library on Windows. There is one caveat, you can build a shared
     library for the SWIG bindings, e.g. C#.
  2. Microsoft .Net less than v4.0.30319 is currently not supported (Same for Mono)
  3. MinGW cannot compile the code when ENABLE_BACKWARDS_COMPATIBILITY=ON
  4. We do not support Mono on Windows
  5. If both Visual Studio and Mono are installed, the build script will only use Visual Studio for C#
  6. We do not support 32-bit builds
  7. MinGW W64 4.9.x and prior will not link properly
  8. Visual Studio 12 2013 is not supported for the C# Bindings (Results in heap corruption)

### SAV Analysis Tab

The following images were generated using the applications provided by
the InterOp package.

![Example Plots][example_image]
[example_image]:docs/images/example_plots.png



[tcistatus]:https://travis-ci.org/Illumina/interop.svg?branch=master
[tcihome]:https://travis-ci.org/Illumina/interop

[acistatus]:https://ci.appveyor.com/api/projects/status/5hwirymkc10uf13d/branch/master?svg=true
[acihome]:https://ci.appveyor.com/project/ezralanglois/interop/branch/master


[covstatus]:https://scan.coverity.com/projects/7744/badge.svg
[covhome]:https://scan.coverity.com/projects/illumina-interop

[tcregstatus]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_NightlyTests_RegressionTest)/statusIcon
[tcreghome]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_NightlyTests_RegressionTest

[tccovstatus]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_NightlyTests_RegressionTest)/statusIcon
[tccovhome]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_NightlyTests_RegressionTest

[tccentos5status]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_CentOS5)/statusIcon
[tccentos5home]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_CentOS5&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv

[tccentos7status]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_CentOS7)/statusIcon
[tccentos7home]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_CentOS7&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv

[tcmsvcstatus]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_Windows7msvc)/statusIcon
[tcmsvchome]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_Windows7msvc&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv

[tcmingwstatus]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_Windows7MinGW)/statusIcon
[tcmingwhome]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_Windows7MinGW&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv

[tcrta3status]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_IntegrationRta3)/statusIcon
[tcrta3home]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_IntegrationRta3&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv

[tcsavstatus]: http://ussd-prd-tcbf01/app/rest/builds/buildType:(id:InterOp_PullRequestTests_Sav)/statusIcon
[tcsavhome]: http://ussd-prd-tcbf01/viewType.html?buildTypeId=InterOp_PullRequestTests_Sav&branch_InterOp_PullRequestTests=%3Cdefault%3E&tab=buildTypeStatusDiv
