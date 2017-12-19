# Auto Run Tracker

## Introduction 
Auto run tracker tracks runs and output basic metrics about the run. For questions and update suggestion, please contact Leo Liu (qliu2@illumina.com) or Chen Zhao (czhao@illumina.com).

## Usage 
First you need to qlogin in `qlogin`

## Command for summarizing runs
`
/illumina/scratch/K2-I/software/auto_run_tracker/00_parse_summary_linux_NovaSeq.R --summaryCSV=<location_of_output_csv> --runsDir=<directory_of_illumina_runs>
`
* `--summaryCSV` can be a new file or a file that has been created before using the run tracker 

* `--runsDir` is where the runs are located. The tracker currently supports Novaseq results as well

### Output
The run tracker will summarize and parse InterOp files and samplesheet to generate the following results.

The output header:

| RunID | Experiment | Investigator | Experiment_Name | UniqueSampleNames | numSamples | Read1_length | Read2_length | InstrumentID | RTAVersion | FlowCellRfidTag_SerialNumber | FlowCellRfidTag_PartNumber | FlowCellRfidTag_LotNumber | FlowCellRfidTag_ExpirationDate | PR2BottleRfidTag_SerialNumber | PR2BottleRfidTag_PartNumber | PR2BottleRfidTag_LotNumber | PR2BottleRfidTag_ExpirationDate | ReagentKitRfidTag_SerialNumber | ReagentKitRfidTag_PartNumber | ReagentKitRfidTag_LotNumber | ReagentKitRfidTag_ExpirationDate | YieldTotalG | Read1_Q30Percent | Read2_Q30Percent | Q30Percent | Read1_errorRate | Read2_errorRate | Read1_Intensity | Read2_Intensity | cluster_density | cluster_percent_Pf | total_PairedReads | total_PairedReadsPf | total_PairedReadsPf_demux | 
|-------|------------|--------------|-----------------|-------------------|------------|--------------|--------------|--------------|------------|------------------------------|----------------------------|---------------------------|--------------------------------|-------------------------------|-----------------------------|----------------------------|---------------------------------|--------------------------------|------------------------------|-----------------------------|----------------------------------|-------------|------------------|------------------|------------|-----------------|-----------------|-----------------|-----------------|-----------------|--------------------|-------------------|---------------------|---------------------------| 
