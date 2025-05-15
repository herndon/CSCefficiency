# CRAB Submissions

To submit CRAB jobs, move to the [`submit/`](../submit/) directory and run `crabSubmit.sh`. To customize the job that is submitted (such as dataset, 
request name, etc.) edit the [`settings.cfg`](../submit/settings.cfg) file appropriately. If you want to submit a job with a pre-existing section's settings,
you can run the following:

```bash
crabSubmit.sh <SECTION_NAME>
```

Here, `<SECTION_NAME>` refers to the name of the section with the settings you want to apply. If the name is not found in the settings file, an error will print and it
will cancel the script. Unused sections (like a section configuring 2023 jobs) can be deleted freely, but note that the settings used for those jobs are not saved elsewhere. 
The following sections describe how to create new setting sections to configure your jobs.

## Configuring the job

To configure the job, you must edit the `settings.cfg` file to add a new config section corresponding to the dataset you wish to process. For example,
if you want to process the dataset `/Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO`, then you would add the following section:

```dosini
[Muon0/2025Bv1]
dataset: /Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO
globalTag: 150X_dataRun3_Prompt_v1 
```

The section name is merely a convention to keep things organized - you can name it whatever you'd like. Some sections may be fairly bare and only contain these
options, but certain defaults may need to be changed for some jobs. This way, the configuration for each job is saved in this file and we don't need to keep
multiple long files per job. The required options in these user-defined sections are defined as follows:

* `dataset`: The input dataset to be processed. 
* `globalTag`: The global tag for processing this dataset.

The appropriate global tag to process the data can be found on the Data Aggregation System (DAS) with the query `dataset=...`, where the desired dataset is provided.

**NOTE**: Once you've configured this new section, go to the `section` option in the `DEFAULT` section and change the value to the name of your newly created section.
This option controls what jobs are submitted - make sure to change this when you submit a new job. Alternatively, you can provide this name when running `crabSubmit.sh`.
Often, the values in the `DEFAULT` section need to be different for a job. The next section explains how to do so without disrupting other user-defined sections.

### Overwriting default options

Other than the `section` option, no values should be modified within the `DEFAULT` section itself! If you want to change one of these options for your analyis, add 
the value to your new section instead. For example, if you want to change the default `requestName`, your new section could look something like the following:

```dosini
[Muon0/2025Bv1]
dataset: /Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO
globalTag: 150X_dataRun3_Prompt_v1 
requestName: myNewRequestName
```

Note that the request name will always have the job attempt appended to it automatically. For example, when you submit the above example the request name will be set to
`myNewRequestName_1`. If you were to submit the request again, the script will notice you already have a CRAB directory for that name and will increment the attempt counter.
Then, the new job would be named `myNewRequestName_2`, and so on.

**NOTE**: The `psetName` option can be changed, but note that the `cmsDriver` file you use instead
may not be able to process the input config params from `crabConfig.py` appropriately.

The additional options in the `DEFAULT` section are defined as follows:

* `psetName`: The `cmsDriver` config file to run for processing. In most cases, this should not be overwritten.
* `unitsPerJob`: The number of files to include in each job.
* `appendDate`: Whether to append the current date (YYYY_MMDD) to the output dataset tag.
* `lumiMask`: A lumi-mask to apply to the input dataset before analysis.
* `runRange`: The runs and/or run ranges to process.
* `maxMemoryMB`: The maximum memory (in MB) a job is allowed to use. (Single-core max is 5000MB and multi-core is 2500 per core.)
* `numCores`: The number of requested cores per job. Note that the `maxMemoryMB` is *total* and will be divided equally per core.
* `dataID`: An identifier for the dataset being processed. Note that the default value uses values for `stream`, `era`, and `version`, which are
parsed from the input `dataset` option.
  * `stream`: The identifier for the split `Muon` primary dataset stream.
  * `era`: The acquisition era name of the dataset.
  * `version`: The processing version of the dataset.
* `requestName`: A name given to the request.
* `tag`: A custom string used in both the LFN of the output files and the publication dataset name.
* `outputFile`: The name of the output file to be passed to the `cmsRun` script.
* `section`: The config section in the file to pull process-specific options from for analysis. You can change this manually or by providing it as the
first argument when running `crabSubmit.sh`.
