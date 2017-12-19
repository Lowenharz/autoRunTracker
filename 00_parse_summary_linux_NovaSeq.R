#! /illumina/scratch/OncoBU/ISIS/IsisTools/R/R-3.1.1_V7/bin/Rscript --vanilla

arg=commandArgs()
masterFile = unlist(strsplit(arg[ pmatch("--summaryCSV",arg)], "="))[2]
runsDir = unlist(strsplit(arg[ pmatch("--runsDir",arg)], "="))[2]


## Load libraries

library(stringr)
library(plyr)
library(XML)
source("/illumina/scratch/K2-I/software/auto_run_tracker/00_parse_summary_function_NovaSeq.R")

summaryInterop <- "/illumina/scratch/K2-I/software/auto_run_tracker/InterOp-3.3.3-Linux-GNU-4.8.2centos5/bin/summary"
indexInterop <- "/illumina/scratch/K2-I/software/auto_run_tracker/InterOp-3.3.3-Linux-GNU-4.8.2centos5/bin/index-summary"

# default is called run_summary_automated.csv
if( is.na(masterFile) ){
  masterFile <- "/illumina/scratch/K2-I/Runs/run_summary_automated.csv"  
}

if(file.exists(masterFile)){
  df.master <- read.csv(masterFile, header=T, stringsAsFactors = F)
  df.master <- df.master[!duplicated(df.master), ]
  already_run <- df.master$RunID[ df.master$Experiment_Name != "" ]
  already_run <- already_run[!is.na(already_run)]
}else{
  df.master <- c()
  already_run <- ""
}

# default is the K2 share
if( is.na(runsDir) ){
  lf <- Sys.glob("/illumina/scratch/K2-I/Runs/*/RTAComplete.txt")
}else{
  lf <- Sys.glob(file.path(runsDir, "*/RTAComplete.txt"))  
}

valid_RunFolders <- dirname(lf)
valid_RunFolders <- valid_RunFolders[!basename(valid_RunFolders) %in% already_run]
lf <- Sys.glob( file.path(valid_RunFolders, "[rR]unParameters.xml"))
cat(paste0("number of runs to process: ", length(valid_RunFolders), "\n"))
# valid_RunFolders <- valid_RunFolders[1:5]

df.final.all <- c()
for(k in 1:length(valid_RunFolders)){#length(valid_RunFolders)
  
  runFolder <- valid_RunFolders[k]
  f1 <- file.path(runFolder, "InterOp_Summary.csv")
  f2 <- file.path(runFolder, "InterOp_Index.csv")
  f3 <- lf[grep(runFolder, lf)[1]]
  f4 <- file.path(runFolder, "SampleSheet.csv")
  cat(k, "\n", f1, "\n", f2, "\n", f3, "\n", f4, "\n")
  
  if( !file.exists(f1) ){
    
    command1 <- paste(summaryInterop, runFolder, "--level=3 --csv=1 >", f1, sep=" ")
    t1 <- try(system(command1, intern = TRUE))
  }
  if( !file.exists(f2) ){
    
    command2 <- paste(indexInterop, runFolder, "--csv=1 >", f2, sep=" ")
    t2 <- try(system(command2, intern = TRUE))
  }
  
  df.final <- genSummaryPerRun(f1, f2, f3, f4)
  df.final.all <- rbind(df.final.all, df.final)
  
}

df.final.all <- rbind(df.master, df.final.all)
runID.all <- unique(df.final.all$RunID)
rows.to.keep <- c()
for(k in 1:length(runID.all)){
  current.runID <- runID.all[k]
  rows <- grep(current.runID, df.final.all$RunID)
  if( length(rows) == 1){
    rows.to.keep <- c(rows.to.keep, rows)
  }else{ #keep the more complete row
    rows.to.keep <- c(rows.to.keep, rows[which.max(rowSums(df.final.all[rows, 1:4]!=""))])
  }
}
rows.to.keep <- sort(rows.to.keep)
df.final.all <- df.final.all[rows.to.keep, ]
df.final.all <- df.final.all[order(df.final.all$RunID), ]
write.csv(df.final.all, file=masterFile, row.names=F, na = "")