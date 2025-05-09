# CRAB Submissions

To submit CRAB jobs, move to the [`submit/`](CSCEfficiency/submit/.) directory and run `crabSubmit.sh`. To customize the job that is submitted (such as dataset, 
request name, etc.) edit the [`settings.cfg`](CSCEfficiency/submit/settings.cfg) file appropriately. The following sections describe how to do so.

## Configuring the job

To configure the job, you must edit the `settings.cfg` file to add a new config section corresponding to the dataset you wish to process. For example,
if you want to process the dataset `/Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO`, then you would add the following section:

```dosini
[Muon0/2025Bv1]
stream: 0
era: 2025B
version: 1
globalTag: 150X_dataRun3_Prompt_v1 
```

The section name is merely a convention to keep things organized - you can name it whatever you'd like. Possible options in these user-defined sections are 
defined as follows:

* `stream`: The integer identifier of the split `Muon` primary dataset streams. (e.g. 0 or 1 corresponding to `Muon0` and
`Muon1`, respectively)
* `era`: The acquisition era name of the dataset, without the "Run" prefix.
* `version`: The processing version of the dataset.
accordingly.
* `globalTag`: The global tag for processing this dataset.

All of these can be found on the Data Aggregation System (DAS) with the appropriate query. For example, here we
would search `dataset=/Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO` and hit the "show" button next to the listed dataset.

**NOTE**: Once you've configured this new section, go to the `section` option in the `DEFAULT` section and change the value to the name of your newly created section.
This option controls what jobs are submitted - make sure to change this when you submit a new job.

### Overwriting default options

Other than the `section` option, no values should be modified within the `DEFAULT` section itself! If you want to change one of these options for your analyis, add 
the value to your new section instead. For example, if you want to change the default `requestName`, your new section could look something like the following:

```dosini
[Muon0/2025Bv1]
stream: 0
era: 2025B
version: 1
globalTag: 150X_dataRun3_Prompt_v1 
requestName: myNewRequestName
```

Note that the request name will always have the job attempt appended to it automatically. For example, when you submit the above example the request name will be set to
`myNewRequestName_1`. If you were to submit the request again, the script will notice you already have a CRAB directory for that name and will increment the attempt counter.
Then, the new job would be named `myNewRequestName_2`, and so on.

**NOTE**: The `dataset` option should not be overwritten in your new section! This analysis can only work with a specific dataset as input, so the
python script determines this from the settings provided in your new section. The `psetName` option can be changed, but note that the `cmsDriver` file you use instead
may not be able to process the input config params from `crabConfig.py` appropriately.

The additional options in the `DEFAULT` section are defined as follows:

* `dataset`: The dataset name for processing. (**NOTE**: Do not overwrite!)
* `psetName`: The `cmsDriver` config file to run for processing. In most cases, this should not be overwritten.
* `unitsPerJob`: The number of files to include in each job.
* `appendDate`: Whether to append the current date (YYYY_MMDD) to the output dataset tag.
* `lumiMask`: A lumi-mask to apply to the input dataset before analysis.
* `maxMemoryMB`: The maximum memory (in MB) a job is allowed to use.
* `dataID`: An identifier for the dataset being processed.
* `requestName`: A name given to the request.
* `tag`: A custom string used in both the LFN of the output files and the publication dataset name.
* `section`: The config section in the file to pull process-specific options from for analysis.
