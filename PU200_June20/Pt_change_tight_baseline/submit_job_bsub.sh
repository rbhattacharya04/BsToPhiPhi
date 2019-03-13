#!/bin/bash
for filename in submit_job_Signal*.sh; do
 bsub -q 1nh $filename
done
for filename in submit_job_bkg*.sh; do
 bsub -q 8nh $filename
done

