library(stringr)
library(plyr)
library(XML)

genSummaryPerRun <- function(f1, f2, f3, f4){
  #f1 is InterOp_Summary.txt
  #f2 is InterOp_Index.txt
  #f3 is RunParameters.xml
  #f4 is sample sheet
  tmp1 <- readLines(f1)
  
  YieldTotalG <- NA
  Q30Percent <- NA
  Read1_Q30Percent <- NA
  Read2_Q30Percent <- NA
  Read1_errorRate <- NA
  Read2_errorRate <- NA
  Read1_Intensity <- NA    
  Read2_Intensity <- NA
  cluster_density <- NA
  cluster_percent_Pf <- NA
  
  
  total_PairedReads <- NA
  total_PairedReadsPf <- NA
  total_PairedReadsPf_demux <- NA
  
  if(file.info(f1)$size > 300){
    summary.start <- 3
    summary.end <- grep("Total", tmp1)[1]
    
    if(length(tmp1) > 20){
      df.summary <- read.csv(f1, skip=2, header=T, stringsAsFactors = F, nrows = summary.end - summary.start)
      df.summary$Read <- ""
      df.summary$Read[ df.summary$Level == "Read 1"] <- "R1"
      if( length(grep("Read 4", df.summary$Level)) > 0 ){
        df.summary$Read[ df.summary$Level == "Read 4"] <- "R2"  
      }else{
        df.summary$Read[ df.summary$Level == "Read 2"] <- "R2"
      }
      
      YieldTotalG <- df.summary$Yield[ df.summary$Level == "Non-indexed"]
      Q30Percent <- df.summary$X...Q30[ df.summary$Level == "Non-indexed"]
      Read1_Q30Percent <- df.summary$X...Q30[ df.summary$Read == "R1"]
      Read2_Q30Percent <- df.summary$X...Q30[ df.summary$Read == "R2"]
      Read1_errorRate <- df.summary$Error.Rate[ df.summary$Read == "R1"]
      Read2_errorRate <- df.summary$Error.Rate[ df.summary$Read == "R2"]
      Read1_Intensity <- df.summary$Intensity.C1[ df.summary$Read == "R1"]    
      Read2_Intensity <- df.summary$Intensity.C1[ df.summary$Read == "R2"]
      
      
      Read1.start <- grep("Read 1", tmp1)[2]
      Read1.end <- grep("Read 2", tmp1)[2]
      df.lane <- read.csv(f1, skip=Read1.start, header=T, stringsAsFactors = F, nrows = Read1.end - Read1.start - 2)
      cluster_density <- round(mean(as.numeric(sapply(df.lane$Density, function(x) strsplit(x, " ")[[1]][1])), na.rm = T), 1)
      cluster_percent_Pf <- round(mean(as.numeric(sapply(df.lane$Cluster.PF, function(x) strsplit(x, " ")[[1]][1])), na.rm = T),1)
      
      YieldTotalG <- ifelse(is.null(YieldTotalG), NA, YieldTotalG)
      Q30Percent <- ifelse(is.null(Q30Percent), NA, Q30Percent)
      Read1_Q30Percent <- ifelse(is.null(Read1_Q30Percent), NA, Read1_Q30Percent)
      Read2_Q30Percent <- ifelse(is.null(Read2_Q30Percent), NA, Read2_Q30Percent)
      Read1_errorRate <- ifelse(is.null(Read1_errorRate), NA, Read1_errorRate)
      Read2_errorRate <- ifelse(is.null(Read2_errorRate), NA, Read2_errorRate)
      Read1_Intensity <- ifelse(is.null(Read1_Intensity), NA, Read1_Intensity)   
      Read2_Intensity <- ifelse(is.null(Read2_Intensity), NA, Read2_Intensity)
      
    }

  }
  
  if(file.info(f2)$size > 100){
    tmp2 <- readLines(f2)
    if(length(tmp2) > 2){
      unique.lanes <- tmp2[ grep("Lane", tmp2)]
      tmp3 <- tmp2[ grep("Lane", tmp2) + 2 ]
      total_PairedReads <- round(sum(as.numeric(sapply(tmp3, function(x) strsplit(x, ",")[[1]][1])), na.rm=T)/2/1e6, 1)
      total_PairedReadsPf <- round(sum(as.numeric(sapply(tmp3, function(x) strsplit(x, ",")[[1]][2])), na.rm=T)/2/1e6, 1)
      total_PairedReadsPf_demux <- round(sum(as.numeric(sapply(tmp3, function(x) strsplit(x, ",")[[1]][2])) * as.numeric(sapply(tmp3, function(x) strsplit(x, ",")[[1]][3])) / 100, na.rm=T)/2/1e6, 1)
    }
  }
  
  df.out <- data.frame(YieldTotalG=YieldTotalG,
                       Read1_Q30Percent=Read1_Q30Percent, Read2_Q30Percent=Read2_Q30Percent, Q30Percent=Q30Percent,
                       Read1_errorRate=Read1_errorRate, Read2_errorRate=Read2_errorRate,
                       Read1_Intensity = Read1_Intensity, Read2_Intensity=Read2_Intensity,
                       cluster_density = cluster_density, cluster_percent_Pf = cluster_percent_Pf,
                       total_PairedReads=total_PairedReads, 
                       total_PairedReadsPf=total_PairedReadsPf,
                       total_PairedReadsPf_demux = total_PairedReadsPf_demux,
                       stringsAsFactors = F)
  
  data <- xmlParse(f3)
  xml_data <- xmlToList(data)
  
  RunID <- c(xml_data$RunID, xml_data$Setup$RunID, xml_data$RunId)
  InstrumentID <- c(xml_data$InstrumentID, xml_data$Setup$InstrumentID, xml_data$InstrumentName)
  if(is.null(InstrumentID)){ # runParameters.xml do not always have InstrumentID recorded, e.g. for HiSeq4000 runs
    InstrumentID <- strsplit(basename(dirname(f3)), "_")[[1]][2]
  }
  RTAVersion <- ifelse(is.null(c(xml_data$RTAVersion, xml_data$Setup$RTAVersion, xml_data$RtaVersion)),NA,c(xml_data$RTAVersion, xml_data$Setup$RTAVersion, xml_data$RtaVersion))
  ExperimentName <- getValue(xml_data$ExperimentName, xml_data$Setup$ExperimentName)
  
  Read1_length <- as.numeric(c(as.numeric(xml_data$Setup$Read1), xml_data$Read1NumberOfCycles))
  Read2_length <- as.numeric(c(as.numeric(xml_data$Setup$Read2), xml_data$Read2NumberOfCycles))
  if (length(Read1_length) == 0L) {
    Read1_length<-NA
  }
  if (length(Read2_length) == 0L) {
    Read2_length<-NA
  }
  
  FlowCellRfidTag_SerialNumber <- ifelse(is.null(xml_data$FlowCellRfidTag$SerialNumber), NA, xml_data$FlowCellRfidTag$SerialNumber)
  FlowCellRfidTag_PartNumber <- ifelse(is.null(xml_data$FlowCellRfidTag$PartNumber), NA, xml_data$FlowCellRfidTag$PartNumber)
  FlowCellRfidTag_LotNumber <- ifelse(is.null(xml_data$FlowCellRfidTag$LotNumber), NA, xml_data$FlowCellRfidTag$LotNumber)
  FlowCellRfidTag_ExpirationDate <- ifelse(is.null(xml_data$FlowCellRfidTag$ExpirationDate), NA, xml_data$FlowCellRfidTag$ExpirationDate)
  
  PR2BottleRfidTag_SerialNumber <- ifelse(is.null(xml_data$PR2BottleRfidTag$SerialNumber), NA, xml_data$PR2BottleRfidTag$SerialNumber)
  PR2BottleRfidTag_PartNumber <- ifelse(is.null(xml_data$PR2BottleRfidTag$PartNumber), NA, xml_data$PR2BottleRfidTag$PartNumber)
  PR2BottleRfidTag_LotNumber <- ifelse(is.null(xml_data$PR2BottleRfidTag$LotNumber), NA, xml_data$PR2BottleRfidTag$LotNumber)
  PR2BottleRfidTag_ExpirationDate <- ifelse(is.null(xml_data$PR2BottleRfidTag$ExpirationDate), NA, xml_data$PR2BottleRfidTag$ExpirationDate)
  
  ReagentKitRfidTag_SerialNumber <- ifelse(is.null(xml_data$ReagentKitRfidTag$SerialNumber), NA, xml_data$ReagentKitRfidTag$SerialNumber)
  ReagentKitRfidTag_PartNumber <- ifelse(is.null(xml_data$ReagentKitRfidTag$PartNumber), NA, xml_data$ReagentKitRfidTag$PartNumber)
  ReagentKitRfidTag_LotNumber <- ifelse(is.null(xml_data$ReagentKitRfidTag$LotNumber), NA, xml_data$ReagentKitRfidTag$LotNumber)
  ReagentKitRfidTag_ExpirationDate <- ifelse(is.null(xml_data$ReagentKitRfidTag$ExpirationDate), NA, xml_data$ReagentKitRfidTag$ExpirationDate)
  
  df.exp <- getExpName(f4) # parse sample sheet for exp name and investigator
  
  df.out2 <- data.frame(RunID,
                        Experiment = ExperimentName,
                        Investigator = df.exp$Investigator,
                        Experiment_Name = df.exp$Experiment_Name,
                        UniqueSampleNames = df.exp$sampleNames,
                        numSamples = df.exp$numSamples,
                        Read1_length,
                        Read2_length,
                        InstrumentID,
                        RTAVersion,
                        FlowCellRfidTag_SerialNumber,
                        FlowCellRfidTag_PartNumber,
                        FlowCellRfidTag_LotNumber,
                        FlowCellRfidTag_ExpirationDate,
                        PR2BottleRfidTag_SerialNumber,
                        PR2BottleRfidTag_PartNumber,
                        PR2BottleRfidTag_LotNumber,
                        PR2BottleRfidTag_ExpirationDate,
                        ReagentKitRfidTag_SerialNumber,
                        ReagentKitRfidTag_PartNumber,
                        ReagentKitRfidTag_LotNumber,
                        ReagentKitRfidTag_ExpirationDate,
                        stringsAsFactors = F)

  
  df.final <- cbind(df.out2, df.out)
  return(df.final)
}

getValue <- function(x, y){
  if(is.null(x) && is.null(y)){
    v <- NA
  }else{
    v <- union(x, y)
  }
  return(v)
}

# f <- "K:/software/auto_run_tracker/218 NRUMI_NextSeq_SampleSheet.csv"
getExpName <- function(f){
  if( file.exists(f) ){
    df.SS <- readLines(f)
    if(!is.na(grep("Investigator", df.SS, ignore.case = T)[1])){
      Investigator <- strsplit(df.SS[grep("Investigator", df.SS, ignore.case = T)[1]], ",")[[1]][2]
    }else{
      Investigator <- ""
    }
    if(!is.na(grep("Experiment Name", df.SS, ignore.case = T)[1])){
      Experiment_Name <- strsplit(df.SS[grep("Experiment Name", df.SS, ignore.case = T)[1]], ",")[[1]][2]
    }else{
      Experiment_Name <- ""
    }
    data.row <- grep("^\\[Data\\]", df.SS)
    df.data <- read.csv(f, header=T, skip=data.row, stringsAsFactors = F)
    df.data <- df.data[df.data$Sample_ID != "", ]
    sampleNames <- paste(unique(unname(sapply(as.character(df.data$Sample_ID), function(x) strsplit(x, "[_|-]")[[1]][1]))), collapse = ", ")
    numSamples <- length(df.data$Sample_ID[ df.data$Sample_ID !="" ])
  }else{
    Investigator <- NA
    Experiment_Name <- NA
    sampleNames <- NA
    numSamples <- NA
  }
  

  return(data.frame(Investigator=Investigator, Experiment_Name=Experiment_Name, 
                    sampleNames=sampleNames, numSamples=numSamples,
                    stringsAsFactors = F))
}